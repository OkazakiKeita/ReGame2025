#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

GameCamera::GameCamera()
{
	/*g_camera3D->SetNear(250.0f);
	g_camera3D->SetFar(900.0f);*/
}

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{
	//�����_���王�_�܂ł̃x�N�g����ݒ�B
	m_toCameraPos.Set(0.0f, 150.0f, -250.0f);
	//�v���C���[�̃C���X�^���X��T���B
	m_player = FindGO<Player>("BattleCharacter");

	//�J�����̃j�A�N���b�v�ƃt�@�[�N���b�v��ݒ肷��B
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(10000.0f);

	return true;
}

void GameCamera::Update()
{
	//�J�������X�V�B
	//�����_���v�Z����B
	Vector3 target = m_player->m_position;
	//�v���C���[�̑������炿����Ə�𒍎��_�Ƃ���B
	target.y += 80.0f;

	Vector3 toCameraPosOld = m_toCameraPos;

	//���_���v�Z����B
	Vector3 pos = target + m_toCameraPos;
	//���C���J�����ɒ����_�Ǝx�X��ݒ肷��B
	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);

	//�J�����̍X�V�B
	g_camera3D->Update();
}