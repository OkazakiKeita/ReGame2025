#pragma once
#include "sound/SoundSource.h"
class GameClear:public IGameObject
{
public:
	GameClear();
	~GameClear();
	//�X�V�����B
	void Update();
	//�`�揈���B
	void Render(RenderContext& rc);

	//�����o�ϐ��B
	SpriteRender m_spriteRender;
	SoundSource* clearBGM;
};

