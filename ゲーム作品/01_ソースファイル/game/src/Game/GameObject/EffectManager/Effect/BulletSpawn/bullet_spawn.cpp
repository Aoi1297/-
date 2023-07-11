#include "bullet_spawn.h"

#include "../../../UnitManager/unit_manager.h"

const float CSpawn::m_easing_time	= 0.75f;
const float CSpawn::m_sprite_size	= 0.5f;
const int CSpawn::m_alpha_decrease	= 7;
const int CSpawn::m_delete_num		= 4;

CSpawn::CSpawn(IGameObject* parent)
	// parent(CEffectManager)
	: IEffect(parent, "BulletSpawnEffect")
{
}

void CSpawn::Initialize(void)
{
	// プレイヤーが生成したエフェクトの場合
	if (m_Category == CATEGORY_ID::PLAYER)
	{
		// ランダムで色変更
		if (aqua::Rand(1))
		{
			// 青色のスプライトを生成
			m_EffectSprite.Create("data/texture/effect/Trajectory_blue.png");
		}
		else
		{
			// 緑色のスプライトを生成
			m_EffectSprite.Create("data/texture/effect/Trajectory_green.png");
		}
	}

	// 敵が生成したエフェクトの場合
	if (m_Category == CATEGORY_ID::ENEMY)
	{
		// ランダムで色変更
		if (aqua::Rand(1))
		{
			// 赤色のスプライトを生成
			m_EffectSprite.Create("data/texture/effect/Trajectory_red.png");
		}
		else
		{
			// 桃色のスプライトを生成
			m_EffectSprite.Create("data/texture/effect/Trajectory_pink.png");
		}
	}

	// エフェクトスプライトのブレンドモードを（加算合成）にする
	m_EffectSprite.blend_mode = aqua::ALPHABLEND::ADD;

	// イージングタイマーの設定
	m_EasingTimer.Setup(m_easing_time);

	// エフェクトのサイズ
	m_EffectSprite.scale = { m_sprite_size,m_sprite_size };

	// 回転値を０に設定
	m_Rotation = 0.0f;
}

void CSpawn::Update(void)
{
	// タイマーが終了していないなら更新する
	if (!m_EasingTimer.Finished()) m_EasingTimer.Update();

	// 徐々に小さくなるような効果を与える
	m_EffectSprite.scale.x = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), aqua::CVector2::ONE.x, m_sprite_size);
	m_EffectSprite.scale.y = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), aqua::CVector2::ONE.y, m_sprite_size);

	// 回転値を＋１する
	m_Rotation++;

	// 回転値に応じて画像を角度を更新する
	m_EffectSprite.rotation += aqua::DegToRad(m_Rotation);

	// 画像を徐々に透明にする
	m_EffectSprite.color.alpha -= m_alpha_decrease;

	// 一定の値未満になったらこのクラスオブジェクトを削除する
	if (m_EffectSprite.color.alpha < m_delete_num) IGameObject::DeleteObject();

	// エフェクトの位置更新
	m_EffectSprite.position = m_Position;
}