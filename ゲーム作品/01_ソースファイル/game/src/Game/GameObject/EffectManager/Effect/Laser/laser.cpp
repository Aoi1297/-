#include "laser.h"

#include "../../../UnitManager/unit_manager.h"

const aqua::CVector2 CLaser::m_effect_size = { 1.5f,1.5f };
const float CLaser::m_effect_decrease_size = 0.01f;
const int CLaser::m_effect_decrease_alpha = 7;
const int CLaser::m_effect_delete_alpha = 4;

CLaser::CLaser(IGameObject* parent)
	// parent(CEffectManager)
	: IEffect(parent, "LaserEffect")
{
}

void CLaser::Initialize(void)
{
	// ランダムで生成する色を変更する

	// プレイヤーがホーミング弾を放った場合
	if (m_Category == CATEGORY_ID::PLAYER)
	{
		if (aqua::Rand(1))
		{
			// 青色のエフェクトを生成する
			m_EffectSprite.Create("data/texture/effect/laser_blue.png");
		}
		else
		{
			// 緑色のエフェクトを生成する
			m_EffectSprite.Create("data/texture/effect/laser_blue.png");
		}
	}

	// 敵がホーミングを放った場合
	if (m_Category == CATEGORY_ID::ENEMY)
	{
		if (aqua::Rand(1))
		{
			// 桃色のエフェクトを生成する
			m_EffectSprite.Create("data/texture/effect/laser_pink.png");
		}
		else
		{
			// オレンジ色のエフェクトを生成する
			m_EffectSprite.Create("data/texture/effect/laser_orange.png");
		}
	}

	// エフェクトスプライトのブレンドモードを加算合成にする
	m_EffectSprite.blend_mode = aqua::ALPHABLEND::ADD;

	// エフェクトスプライトの基準点を中心に設定
	m_EffectSprite.anchor = { (float)m_EffectSprite.GetTextureWidth() / 2,(float)m_EffectSprite.GetTextureHeight() / 2 };

	// エフェクトのサイズを設定
	m_EffectSprite.scale = m_effect_size;
}

void CLaser::Update(void)
{
	// 徐々に透明にする
	m_EffectSprite.color.alpha -= m_effect_decrease_alpha;

	// 透明度が一定未満になったらこのクラスオブジェクトを削除する
	if (m_EffectSprite.color.alpha < m_effect_delete_alpha) IGameObject::DeleteObject();

	// エフェクトのサイズ（Y方向のみ）徐々に小さくする
	m_EffectSprite.scale.y -= m_effect_decrease_size;

	// エフェクトの位置更新
	m_EffectSprite.position = m_Position;
}

void CLaser::Draw(void)
{
	m_EffectSprite.Draw();
}

void CLaser::Finalize(void)
{
	m_EffectSprite.Delete();
}
