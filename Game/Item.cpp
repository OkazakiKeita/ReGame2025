#include "stdafx.h"
#include "Item.h"
#include "Player.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

Item::Item()
{
	//���f���̓ǂݍ��݁B
	m_modelRender.Init("Assets/modelData/Item.tkm");

	//�v���C���[�̃I�u�W�F�N�g��T���Ď����Ă���B
	m_player = FindGO<Player>("BattleCharacter");

	//���ʉ��̃t�@�C����ǂݍ��ށB
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/StarGet.wav");
}
Item::~Item()
{

}

void Item::Update()
{
	//�ړ������B
	Move();

	//��]�����B
	Rotation();

	//�G�`���̍X�V�����B
	m_modelRender.Update();

	//�v���C���[����A�C�e���Ɍ������x�N�g�����v�Z�B
	Vector3 diff = m_player->m_position - m_position;
	//�x�N�g���̒���50.0f��菬����������B
	if (diff.Length() <= 50.0f)
	{
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(1);
		se->Play(false);
		se->SetVolume(3.5f);

		//�J�E���g��+1����B
		m_player->m_itemCount += 1;

		//���g�������B
		DeleteGO(this);
	}
	if (m_player->m_position.y < -1000.0f)
	{
		DeleteGO(this);
	}
}

void Item::Move()
{
	m_modelRender.SetPosition(m_position);
}

//��]�����B
void Item::Rotation()
{
	//��]�����Z����B
	m_rotation.AddRotationDegY(2.0f);

	//�G�`���ɉ�]��������B
	m_modelRender.SetRotation(m_rotation);
}

void Item::Render(RenderContext& rc)
{
	//�`�悷��B
	m_modelRender.Draw(rc);
}