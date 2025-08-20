#pragma once
#include "sound/SoundSource.h"

class Player;
class BackGround;
class GameCamera;
class Item;

class Game:public IGameObject
{
public:
	Game();
	~Game();
	void Update();

	Player* m_player;
	GameCamera* m_gameCamera;
	BackGround* m_backGround;
	Item* m_item;
	SkyCube* m_skyCube;
	SoundSource* gameBGM;
};

