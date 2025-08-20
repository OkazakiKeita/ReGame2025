#pragma once

class Player;
class Item:public IGameObject
{
public:
	Item();
	~Item();
	//�X�V�����B
	void Update();
	//�`�揈���B
	void Render(RenderContext& rc);
	//�ړ������B
	void Move();
	//��]�����B
	void Rotation();

	//�����o�ϐ��B
	ModelRender m_modelRender;
	Vector3 m_position;
	Quaternion m_rotation;
	Player* m_player;
};

