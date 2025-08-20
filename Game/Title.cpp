#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "sound/SoundEngine.h"

Title::Title()
{
	//画像読み込み。
	m_spriteRender.Init("Assets/sprite/Title.dds", 1920.0f, 1080.0f);

	//タイトルBGMを読み込む。
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/title.wav");
	//タイトルのBGMを再生。
	titleBGM = NewGO<SoundSource>(0);
	titleBGM->Init(0);
	titleBGM->Play(true);
}

Title::~Title()
{
	//BGMの削除。
	DeleteGO(titleBGM);
}

void Title::Update()
{
	if (g_pad[0]->IsTrigger(enButtonStart))
	{
		NewGO<Game>(0,"game");
		DeleteGO(this);
	}
}

void Title::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}