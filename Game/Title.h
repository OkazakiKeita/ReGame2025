#pragma once
#include "sound/SoundSource.h"
class Title:public IGameObject
{
public:
	Title();
	~Title();
	//�`��֐��B
	void Render(RenderContext& rc);
	//�X�V�����B
	void Update();

	SpriteRender m_spriteRender;
	SoundSource* titleBGM;
};

