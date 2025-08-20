#pragma once

class Player;
class Item:public IGameObject
{
public:
	Item();
	~Item();
	//更新処理。
	void Update();
	//描画処理。
	void Render(RenderContext& rc);
	//移動処理。
	void Move();
	//回転処理。
	void Rotation();

	//メンバ変数。
	ModelRender m_modelRender;
	Vector3 m_position;
	Quaternion m_rotation;
	Player* m_player;
};

