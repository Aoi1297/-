#pragma once

#include "../bullet.h"

class CFireWorkBullet : public IBullet
{
public: // 公開メンバ関数

	// コンストラクタ
	CFireWorkBullet			(IGameObject* parent);

	// デストラクタ
	~CFireWorkBullet		(void) = default;

	// 初期化
	void Initialize			(void)	override;

	// 弾の特徴的な動き処理
	void OriginalMovement	(void)	override;

	// 描画
	void Draw				(void)	override;

	// 解放
	void Finalize			(void)	override;

private: // 非公開メンバ変数

	// イージングタイマー
	aqua::CTimer m_EasingTimer;

private: // 非公開メンバ定数

	static const float m_easing_time;
	static const float m_max_bullet_speed;
	static const float m_bullet_deceleration;
	static const int m_add_alpha;
	static const int m_reset_alpha;
};