#include "normal_bullet.h"

#include "../../../UnitManager/unit_manager.h"
#include "../../../EffectManager/effect_manager.h"
#include "../../../SoundManager/sound_creater.h"
#include "../../../UnitManager/Unit/Player/player.h"

const float CNormalBullet::	m_effect_time				= 0.01f;
const float CNormalBullet::	m_easing_time				= 0.5f;
const float CNormalBullet::	m_effect_time_for_enemy		= 0.05f;
const int CNormalBullet::	m_bullet_size				= 2;
const int CNormalBullet::	m_bullet_boss_max_size		= 30;
const int CNormalBullet::	m_bullet_enemy_max_size		= 20;
const int CNormalBullet::	m_bullet_player_max_size	= 7;
const int CNormalBullet::	m_bullet_max_speed			= 30;
const float CNormalBullet::	m_bullet_deceleration		= 1.0f;

CNormalBullet::CNormalBullet(IGameObject* parent)
	// parent(CBulletManager)
	: IBullet(parent, "NormalBullet")
{
}

void CNormalBullet::Initialize(void)
{
	// 発射したユニットが敵なら以下の初期化を行う
	if ((m_Category == CATEGORY_ID::ENEMY || m_Category == CATEGORY_ID::BOSS))
	{
		// エフェクト時間を設定
		m_EffectTimer.Setup(m_effect_time_for_enemy);

		// ランダムで弾の色を変更する
		{
			if (aqua::Rand(1))
			// 弾の色を赤色にする
			IBullet::CreateSprite("data/texture/bullet/normal_bullet_red.png");

			// 弾の色をオレンジにする
			else IBullet::CreateSprite("data/texture/bullet/normal_bullet_orange.png");
		}
	}

	// 発射したユニットがプレイヤーなら以下の初期化を行う
	if (m_Category == CATEGORY_ID::PLAYER)
	{
		// エフェクト時間の設定
		m_EffectTimer.Setup(m_effect_time);

		// 効果音を鳴らす
		((CSoundCreater*)aqua::FindGameObject("SoundManager"))->Play(SOUND_ID::EFFECT_FIRE);

		// ランダムで弾の色を変更する
		{
			if (aqua::Rand(1))
			{
				// 弾の色を青にする
				IBullet::CreateSprite("data/texture/bullet/normal_bullet_blue.png");
			}
			else
			{
				if (aqua::Rand(1))
				{
					// 弾の色を緑にする
					IBullet::CreateSprite("data/texture/bullet/normal_bullet_green.png");
				}
				else
				{
					// 弾の色を紫にする
					IBullet::CreateSprite("data/texture/bullet/normal_bullet_purple.png");
				}
			}
		}
	}

	m_EasingTimer.Setup(m_easing_time);
}

void CNormalBullet::OriginalMovement(void)
{
	// イージングタイマー更新
	if (!m_EasingTimer.Finished())
	{
		m_EasingTimer.Update();
	}

	// 弾出現時徐々に小さくなるようなイージング処理を行う

	// 雑魚敵の場合のイージング
	if (m_Category == CATEGORY_ID::ENEMY)
	{
		m_BulletSprite.scale.x = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), m_bullet_boss_max_size, m_bullet_size);
		m_BulletSprite.scale.y = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), m_bullet_boss_max_size, m_bullet_size);
	}

	// ボスの場合のイージング
	if (m_Category == CATEGORY_ID::BOSS)
	{
		m_BulletSprite.scale.x = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), m_bullet_enemy_max_size, m_bullet_size);
		m_BulletSprite.scale.y = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), m_bullet_enemy_max_size, m_bullet_size);
	}

	// プレイヤーの場合のイージング
	else
	{
		m_BulletSprite.scale.x = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), m_bullet_player_max_size, m_bullet_size);
		m_BulletSprite.scale.y = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), m_bullet_player_max_size, m_bullet_size);
	}

	// 弾の速度を徐々に遅くする
	if (m_BulletSpeed > m_bullet_max_speed) m_BulletSpeed -= m_bullet_deceleration;

	// エフェクトタイマー更新
	m_EffectTimer.Update();

	// エフェクトタイマー終了時
	if (m_EffectTimer.Finished())
	{
		if (!((CPlayer*)aqua::FindGameObject("Player"))->GetEffectFlag())
			return;

		// エフェクトを生成
		m_EffectManager->CreateEffect(EFFECT_ID::BULLET_SPAWN, GetCenterPosition(), m_Category);

		// タイマーリセット
		m_EffectTimer.Reset();
	}
}

void CNormalBullet::Draw(void)
{
	m_BulletSprite.Draw();
}

void CNormalBullet::Finalize(void)
{
	m_BulletSprite.Delete();
}
