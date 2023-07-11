#pragma once

#include "aqua.h"

#include "../enemy.h"

class CStar : public IEnemy
{
public:	// 公開オーバーライド関数

	// コンストラクタ
	CStar(IGameObject* parent);

	// デストラクタ
	~CStar(void)	override = default;

	// 初期化関数
	void Initialize(void)  override;

	// 更新関数
	void Update(void)	override;

	// 当たり判定取得
	float GetRadius(void)override;

private: // 非公開メンバ関数

	// 出現時のエフェクト
	void SpawanEffect(void)override;

	// 動き処理
	void Movement(void)override;

	// 射撃処理
	void Fire(void)override;

private: // 非公開メンバ定数

	static const int			m_max_life_point;		// !< ユニット最大体力
	static const float			m_fire_interval;		// !< 射撃間隔
	static const float			m_easing_time;			// !< 出現時のイージング時間
	static const aqua::CVector2 m_unit_scale;			// !< ユニットサイズ
	static const aqua::CVector2	m_max_scale;			// !< ユニット最大サイズ
	static const float			m_random_angle;			// !< 弾のブレの最大角度
	static const float			m_rotation_angle;		// !< ユニットの回転角度
	static const float			m_shot_speed;			// !< 弾の速度
	static const float			m_move_acceleration;	// !< ユニットの加速度
	static const float			m_hit_radius;			// !< ユニットの当たり判定
};