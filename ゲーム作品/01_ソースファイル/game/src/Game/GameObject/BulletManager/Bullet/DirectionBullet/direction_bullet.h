#pragma once

#include "../bullet.h"

class CDirectionBullet : public IBullet
{
public: // 公開メンバ関数

	// コンストラクタ
	CDirectionBullet		(IGameObject* parent);

	// デストラクタ
	~CDirectionBullet		(void) = default;

	// 初期化
	void Initialize			(void)	override;

	// 弾の特徴的な動き処理
	void OriginalMovement	(void)	override;

private: // 非公開メンバ変数

	// イージングタイマー更新
	aqua::CTimer m_EasingTimer;

	// プレイヤー角度
	aqua::CVector2 m_PlayerNormalize;

private: // 非公開メンバ定数

	static const float m_easing_time;
	static const float m_move_speed;
};