#include "stdafx.h"
#include "GameClear.h"
#include "Title.h"
#include "sound/SoundEngine.h"

GameClear::GameClear()
{
	m_spriteRender.Init("Assets/sprite/Gameclear.dds", 1920.0f, 1080.0f);

	//クリアのBGMを読み込む。
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/gameclear.wav");
	//タイトルのBGMを再生。
	clearBGM = NewGO<SoundSource>(0);
	clearBGM->Init(0);
	clearBGM->Play(true);
}

GameClear::~GameClear()
{
	//BGMの削除。
	DeleteGO(clearBGM);
}

//更新処理。
void GameClear::Update()
{
	//Aボタンが押されたら。
	if (g_pad[0]->IsTrigger(enButtonSelect))
	{
		//タイトルのオブジェクトを作る。
		
		//自身を削除。
		DeleteGO(this);
		NewGO<Title>(0, "title");
	}
}

//描画処理。
void GameClear::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}