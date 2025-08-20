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
	//モデルの初期化。
	m_modelRender.Init("Assets/modelData/UnityChan.tkm", m_animationClips, enAnimationClip_Num, enModelUpAxisY);
	//キャラコンの初期化。
	m_characterController.Init(25.0f, 75.0f, m_position);
}

Player::~Player()
{

}
//更新処理。
void Player::Update()
{
	//移動処理。
	Move();

	//回転処理。
	Rotation();

	//ステート管理。
	ManageState();
	
	//アニメーションの再生。
	PlayAnimation();

	m_modelRender.Update();
}
//移動処理。
void Player::Move()
{
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//カメラの前方向と右方向のベクトルに持ってくる。
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	//y方向には移動させない。
	forward.y = 0.0f;
	right.y = 0.0f;

	//左スティックの入力量と120.0fを乗算。
	right *= stickL.x * 120.0f;
	forward *= stickL.y * 120.0f;

	//移動速度に上記で計算したベクトルを加算。
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

		//カメラの前方向と右方向のベクトルに持ってくる。
		Vector3 forward = g_camera3D->GetForward();
		Vector3 right = g_camera3D->GetRight();
		//y方向には移動させない。
		forward.y = 0.0f;
		right.y = 0.0f;

		//左スティックの入力量と120.0fを乗算。
		right *= stickL.x * 200.0f;
		forward *= stickL.y * 200.0f;

		//移動速度に上記で計算したベクトルを加算。
		m_moveSpeed += right + forward;
	}
	
	//地面に付いていたら。
	if (m_characterController.IsOnGround())
	{
		//重力をなくす。
		m_moveSpeed.y = 0.0f;
		m_junp = 0;
		//Aボタンが押されたら。
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			//ジャンプさせる。
			m_moveSpeed.y =700.0f;
			m_junp += 1;
		}
	}
	//地面に付いていなかったら。
	else
	{
		if (m_junp ==1 and g_pad[0]->IsTrigger(enButtonA))
		{
			m_moveSpeed.y =700.0f;
			m_junp = 0;
		}
		//重力を発生。
		m_moveSpeed.y -= 20.0f;
	}

	m_position = m_characterController.Execute(m_moveSpeed, 1.0f / 60.0f);

	m_modelRender.SetPosition(m_position);
}
//回転処理。
void Player::Rotation()
{
	//スティックの入力があったら。
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//キャラクターの方向を変える。
		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
		//絵描きさんに回転を教える。
		m_modelRender.SetRotation(m_rotation);
	}
}
//ステート管理。
void Player::ManageState()
{
	//地面に付いていなかったら。
	if (m_characterController.IsOnGround() == false)
	{
		//ステートを1にする。
		m_playerState = 1;
		//ここでManageState関数の処理を終わらせる。
		return;
	}

	//地面に付いていたら。
	//xかzの移動速度があったら(スティックの入力があったら)。
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//ステートを2にする。
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
//アニメーションの再生。
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
//描画処理。
void Player::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}