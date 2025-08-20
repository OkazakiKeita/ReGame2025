#include "stdafx.h"
#include "GameOver.h"
#include "Title.h"
#include "sound/SoundEngine.h"

GameOver::GameOver()
{
	m_GameOver.Init("Assets/sprite/GameOver.dds", 1920.0f, 1080.0f);

	//タイトルのBGMを読み込む。
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/gameover.wav");
	//タイトルのBGMを再生。
	gameoverBGM = NewGO<SoundSource>(0);
	gameoverBGM->Init(0);
	gameoverBGM->Play(true);
}

GameOver::~GameOver()
{
	//BGMの削除。
	DeleteGO(gameoverBGM);
}

void GameOver::Update()
{
	if (g_pad[0]->IsTrigger(enButtonSelect))
	{
		//タイトルオブジェクトを作る。
		NewGO<Title>(0, "title");
		//自身の削除。
		DeleteGO(this);
	}
}

void GameOver::Render(RenderContext& rc)
{
	m_GameOver.Draw(rc);
}