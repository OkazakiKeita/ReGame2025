#include "stdafx.h"
#include "Item.h"
#include "Player.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

Item::Item()
{
	//モデルの読み込み。
	m_modelRender.Init("Assets/modelData/Item.tkm");

	//プレイヤーのオブジェクトを探して持ってくる。
	m_player = FindGO<Player>("BattleCharacter");

	//効果音のファイルを読み込む。
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/StarGet.wav");
}
Item::~Item()
{

}

void Item::Update()
{
	//移動処理。
	Move();

	//回転処理。
	Rotation();

	//絵描きの更新処理。
	m_modelRender.Update();

	//プレイヤーからアイテムに向かうベクトルを計算。
	Vector3 diff = m_player->m_position - m_position;
	//ベクトルの長さ50.0fより小さかったら。
	if (diff.Length() <= 50.0f)
	{
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(1);
		se->Play(false);
		se->SetVolume(3.5f);

		//カウントを+1する。
		m_player->m_itemCount += 1;

		//自身を消す。
		DeleteGO(this);
	}
	if (m_player->m_position.y < -1000.0f)
	{
		DeleteGO(this);
	}
}

void Item::Move()
{
	m_modelRender.SetPosition(m_position);
}

//回転処理。
void Item::Rotation()
{
	//回転を加算する。
	m_rotation.AddRotationDegY(2.0f);

	//絵描きに回転を教える。
	m_modelRender.SetRotation(m_rotation);
}

void Item::Render(RenderContext& rc)
{
	//描画する。
	m_modelRender.Draw(rc);
}