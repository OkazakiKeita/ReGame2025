#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	m_animationClips[enAnimationClip_Jump].SetLoopFlag(false);
	m_animationClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
	m_animationClips[enAnimationClip_Run].SetLoopFlag(true);
	//���f���̏������B
	m_modelRender.Init("Assets/modelData/UnityChan.tkm", m_animationClips, enAnimationClip_Num, enModelUpAxisY);
	//�L�����R���̏������B
	m_characterController.Init(25.0f, 75.0f, m_position);
}

Player::~Player()
{

}
//�X�V�����B
void Player::Update()
{
	//�ړ������B
	Move();

	//��]�����B
	Rotation();

	//�X�e�[�g�Ǘ��B
	ManageState();
	
	//�A�j���[�V�����̍Đ��B
	PlayAnimation();

	m_modelRender.Update();
}
//�ړ������B
void Player::Move()
{
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//�J�����̑O�����ƉE�����̃x�N�g���Ɏ����Ă���B
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	//y�����ɂ͈ړ������Ȃ��B
	forward.y = 0.0f;
	right.y = 0.0f;

	//���X�e�B�b�N�̓��͗ʂ�120.0f����Z�B
	right *= stickL.x * 120.0f;
	forward *= stickL.y * 120.0f;

	//�ړ����x�ɏ�L�Ōv�Z�����x�N�g�������Z�B
	m_moveSpeed += right + forward;

	if (g_pad[0]->IsPress(enButtonB))
	{
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;

		Vector3 stickL;
		stickL.x = g_pad[0]->GetLStickXF();
		stickL.y = g_pad[0]->GetLStickYF();

		m_moveSpeed.x += stickL.x * 200.0f;
		m_moveSpeed.z += stickL.y * 200.0f;

		//�J�����̑O�����ƉE�����̃x�N�g���Ɏ����Ă���B
		Vector3 forward = g_camera3D->GetForward();
		Vector3 right = g_camera3D->GetRight();
		//y�����ɂ͈ړ������Ȃ��B
		forward.y = 0.0f;
		right.y = 0.0f;

		//���X�e�B�b�N�̓��͗ʂ�120.0f����Z�B
		right *= stickL.x * 200.0f;
		forward *= stickL.y * 200.0f;

		//�ړ����x�ɏ�L�Ōv�Z�����x�N�g�������Z�B
		m_moveSpeed += right + forward;
	}
	
	//�n�ʂɕt���Ă�����B
	if (m_characterController.IsOnGround())
	{
		//�d�͂��Ȃ����B
		m_moveSpeed.y = 0.0f;
		m_junp = 0;
		//A�{�^���������ꂽ��B
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			//�W�����v������B
			m_moveSpeed.y =700.0f;
			m_junp += 1;
		}
	}
	//�n�ʂɕt���Ă��Ȃ�������B
	else
	{
		if (m_junp ==1 and g_pad[0]->IsTrigger(enButtonA))
		{
			m_moveSpeed.y =700.0f;
			m_junp = 0;
		}
		//�d�͂𔭐��B
		m_moveSpeed.y -= 20.0f;
	}

	m_position = m_characterController.Execute(m_moveSpeed, 1.0f / 60.0f);

	m_modelRender.SetPosition(m_position);
}
//��]�����B
void Player::Rotation()
{
	//�X�e�B�b�N�̓��͂���������B
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//�L�����N�^�[�̕�����ς���B
		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
		//�G�`������ɉ�]��������B
		m_modelRender.SetRotation(m_rotation);
	}
}
//�X�e�[�g�Ǘ��B
void Player::ManageState()
{
	//�n�ʂɕt���Ă��Ȃ�������B
	if (m_characterController.IsOnGround() == false)
	{
		//�X�e�[�g��1�ɂ���B
		m_playerState = 1;
		//������ManageState�֐��̏������I��点��B
		return;
	}

	//�n�ʂɕt���Ă�����B
	//x��z�̈ړ����x����������(�X�e�B�b�N�̓��͂���������)�B
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//�X�e�[�g��2�ɂ���B
		m_playerState = 2;
		if (g_pad[0]->IsPress(enButtonB))
		{
			m_playerState = 3;
		}
	}
	else
	{
		m_playerState = 0;
	}
}
//�A�j���[�V�����̍Đ��B
void Player::PlayAnimation()
{
	switch (m_playerState)
	{
	case 0:
		m_modelRender.PlayAnimation(enAnimationClip_Idle);
		break;
	case 1:
		m_modelRender.PlayAnimation(enAnimationClip_Jump);
		break;
	case 2:
		m_modelRender.PlayAnimation(enAnimationClip_Walk);
		break;
	case 3:
		m_modelRender.PlayAnimation(enAnimationClip_Run);
		break;
	}
}
//�`�揈���B
void Player::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}