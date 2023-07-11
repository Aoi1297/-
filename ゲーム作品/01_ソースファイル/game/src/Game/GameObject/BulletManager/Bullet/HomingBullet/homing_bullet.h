#pragma once

#include "../bullet.h"

class CHomingBullet : public IBullet
{
public: // 公開メンバ関数

	// コンストラクタ
	CHomingBullet(IGameObject* parent);

	// デストラクタ
	~CHomingBullet(void) = default;

	// 初期化
	void Initialize(void)	override;

	// 弾の特徴的な動き処理
	void OriginalMovement(void)	override;

private: // 非公開メンバ変数

	// ホーミング時間
	aqua::CTimer m_HomingTimer;

private: // 非公開メンバ定数

	static const float m_homing_time;		// !< ホーミング時間
	static const float m_start_position;	// !< ホーミング場所をずらす（値）
	static const float m_homing_angle;		// !< ホーミング角度
};