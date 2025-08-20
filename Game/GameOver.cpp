#include "stdafx.h"
#include "GameOver.h"
#include "Title.h"
#include "sound/SoundEngine.h"

GameOver::GameOver()
{
	m_GameOver.Init("Assets/sprite/GameOver.dds", 1920.0f, 1080.0f);

	//�^�C�g����BGM��ǂݍ��ށB
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/gameover.wav");
	//�^�C�g����BGM���Đ��B
	gameoverBGM = NewGO<SoundSource>(0);
	gameoverBGM->Init(0);
	gameoverBGM->Play(true);
}

GameOver::~GameOver()
{
	//BGM�̍폜�B
	DeleteGO(gameoverBGM);
}

void GameOver::Update()
{
	if (g_pad[0]->IsTrigger(enButtonSelect))
	{
		//�^�C�g���I�u�W�F�N�g�����B
		NewGO<Title>(0, "title");
		//���g�̍폜�B
		DeleteGO(this);
	}
}

void GameOver::Render(RenderContext& rc)
{
	m_GameOver.Draw(rc);
}