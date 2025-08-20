#include "stdafx.h"
#include "GameClear.h"
#include "Title.h"
#include "sound/SoundEngine.h"

GameClear::GameClear()
{
	m_spriteRender.Init("Assets/sprite/Gameclear.dds", 1920.0f, 1080.0f);

	//�N���A��BGM��ǂݍ��ށB
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/gameclear.wav");
	//�^�C�g����BGM���Đ��B
	clearBGM = NewGO<SoundSource>(0);
	clearBGM->Init(0);
	clearBGM->Play(true);
}

GameClear::~GameClear()
{
	//BGM�̍폜�B
	DeleteGO(clearBGM);
}

//�X�V�����B
void GameClear::Update()
{
	//A�{�^���������ꂽ��B
	if (g_pad[0]->IsTrigger(enButtonSelect))
	{
		//�^�C�g���̃I�u�W�F�N�g�����B
		
		//���g���폜�B
		DeleteGO(this);
		NewGO<Title>(0, "title");
	}
}

//�`�揈���B
void GameClear::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}