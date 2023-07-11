#pragma once

#include "aqua.h"

#include "../enemy.h"

// 前方宣言
class CUnitManager;

class CMiniBoss : public IEnemy
{
public:	// 公開オーバーライド関数

	// コンストラクタ
	CMiniBoss(IGameObject* parent);

	// デストラクタ
	~CMiniBoss(void)	override = default;

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

private: // 非公開メンバ変数

	aqua::CTimer	m_EnemySpawnTimer;	// !< エネミー出現間隔

	aqua::CTimer	m_HomingTimer;		// !< ホーミング間隔

	aqua::CTimer	m_EscapeTimer;		// !< ボス逃走タイマー

	float			m_Angle;			// !< サイン波のための角度

	float			m_LaserSpeed;		// !< レーザー速度

	CUnitManager*	m_UnitManager_P;	// !< ユニットマネージャークラスポインタの取得

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
	static const float			m_move_deceleration;	// !< ユニットの減速度
	static const float			m_move_upand_down;		// !< 上下移動幅
	static const float			m_spwan_time;			// !< ユニット生成速度
	static const float			m_homing_time;			// !< ホーミング間隔
	static const float			m_escape_time;			// !< ボス逃走時間
	static const float			m_move_speed;			// !< ボス逃走時間
	static const int			m_laser_speed_50;		// !< 体力５０％以下時のホーミングレーザー速度
	static const float			m_laser_time_50;		// !< 体力５０％以下時のホーミングレーザー発射間隔
	static const int			m_laser_speed_20;		// !< 体力２０％以下時のホーミングレーザー速度
	static const float			m_laser_time_20;		// !< 体力２０％以下時のホーミングレーザー発射間隔
	static const float			m_hit_radius;			// !< ユニットの当たり判定
};