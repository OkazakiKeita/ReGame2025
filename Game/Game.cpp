#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "Item.h"
#include "GameClear.h"
#include "GameOver.h"
#include "sound/SoundEngine.h"

Game::Game()
{ 
	//キャラクター。
	m_player = NewGO<Player>(0, "BattleCharacter");
	//カメラ。
	m_gameCamera = NewGO<GameCamera>(0, "GameCamera");
	//ステージ。
	m_backGround=NewGO<BackGround>(0, "yuka");
	//空のオブジェクト。
	m_skyCube = NewGO<SkyCube>(0, "skycube");
	//アイテム。
	Item* item1 = NewGO<Item>(0, "item");
	item1->m_position = { 0.0f,25.0f,1100.0f };
	Item* item2 = NewGO<Item>(0, "item");
	item2->m_position = { 0.0f,420.0f,2460.0f };
	Item* item3 = NewGO<Item>(0, "item");
	item3->m_position = { 0.0f,740.0f,3950.0f };
	Item* item4 = NewGO<Item>(0, "item");
	item4->m_position = { 0.0f,-870.0f,4100.0f };
	Item* item5 = NewGO<Item>(0, "item");
	item5->m_position = { 0.0f,-380.0f,6500.0f };

	//BGMの読み込み。
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/gameBGM.wav");
	//BGMを再生。
	gameBGM = NewGO<SoundSource>(1);
	gameBGM->Init(1);
	gameBGM->Play(true);
}

Game::~Game()
{
	DeleteGO(m_player);
	DeleteGO(m_gameCamera);
	DeleteGO(m_backGround);
	DeleteGO(m_item);
	DeleteGO(m_skyCube);
	DeleteGO(gameBGM);
}

void Game::Update()
{
	if (m_player->m_position.y < -1000.0f)
	{
		NewGO<GameOver>(0, "gameover");
		DeleteGO(this);
	}

	if (m_player->m_itemCount == 5)
	{

		NewGO<GameClear>(0, "gameclear");
		DeleteGO(this);
	}
}