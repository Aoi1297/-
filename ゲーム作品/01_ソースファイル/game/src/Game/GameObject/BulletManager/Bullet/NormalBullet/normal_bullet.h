#pragma once

#include "../bullet.h"

class CNormalBullet : public IBullet
{
public: // 公開メンバ関数

	// コンストラクタ
	CNormalBullet			(IGameObject* parent);

	// デストラクタ
	~CNormalBullet			(void) = default;

	// 初期化
	void Initialize			(void)	override;

	// 弾の特徴的な動き処理
	void OriginalMovement	(void)	override;

	// 描画関数
	void Draw				(void)	override;

	// 解放関数
	void Finalize			(void)	override;

private: // 非公開メンバ変数

	// イージングタイマー
	aqua::CTimer m_EasingTimer;
	aqua::CTimer m_EffectTimer;

private: // 非公開メンバ定数

	static const float	m_effect_time;				// !< エフェクト時間
	static const float	m_easing_time;				// !< イージング時間
	static const float	m_effect_time_for_enemy;	// !< 敵のエフェクト時間
	static const int	m_bullet_size;				// !< 弾のサイズ
	static const int	m_bullet_boss_max_size;		// !< 弾の最大サイズ（ボス）
	static const int	m_bullet_enemy_max_size;	// !< 弾の最大サイズ（敵）
	static const int	m_bullet_player_max_size;	// !< 弾の最大サイズ（プレイヤー）
	static const int	m_bullet_max_speed;			// !< 弾の最大速度
	static const float	m_bullet_deceleration;		// !< 弾の初期角度
};