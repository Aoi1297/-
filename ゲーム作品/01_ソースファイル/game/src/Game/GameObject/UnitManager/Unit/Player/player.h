#pragma once

#include "aqua.h"

#include "../unit.h"

// 前方宣言
enum class BULLET_ID;
enum class ITEM_ID;

enum class DIRECTION_ID
{
	FRONT,
	DOUBLE,
	TRIPLE,
	QUAD,
	DOUBLE_DOUBLE,
	TRIPLE_TRIPLE,
	QUAD_QUAD,
	FINAL,
};

enum class POWER_UP_ID
{
	DIRECTION,
	SPEED,
	INTERVAL,
	LASER,
};

class CPlayer : public IUnit
{
public:	// 公開オーバーライド関数

	// コンストラクタ
	CPlayer			(IGameObject* parent);

	// デストラクタ
	~CPlayer		(void)	override = default;

	// 初期化関数
	void Initialize	(void)	override;

	// 更新関数
	void Update		(void)	override;

public:	// 公開メンバ関数

	// アイテム取得効果処理
	void		 PowerUp		(ITEM_ID item_id);

	// レーザー発動中フラグ
	inline void  SetLaserFlag	(void) { m_LaserShotFlag = true; };

	// レーザーポイント取得
	inline int   GetLaserPoint	(void) { return m_LaserPoint; };

	// レーザー発動中フラグ取得
	inline bool  GetLaserFlag	(void) { return m_LaserShotFlag; };

	// プレイヤー体力取得
	inline int   GetHitPoint	(void) { return m_LifePoint; };

	// プレイヤー最大体力
	inline int   GetMaxHitPoint(void) { return m_max_life_point; };

	// 視界不良状態に設定（フラグ）
	inline void  SetDarknessFlag(void) { m_DarknessFlag = true; };

	// 視界不良状態フラグ取得
	inline bool	 GetDarknessFlag(void) { return m_DarknessFlag; };

	// レーザー時間取得
	inline float GetLaserTime	(void) { return m_laser_time; };

	// 軌道エフェクトフラグ取得
	inline bool  GetEffectFlag	(void) { return m_EffectFlag; };

	// 当たり判定取得
	float		 GetRadius(void)override;

private: // 非公開メンバ関数

	// プレイヤー操作
	void Controller	(void);

	// 弾発射処理
	void Fire		(void);

private: // 非公開メンバ変数

	// タイマー変数
	aqua::CTimer	m_FireInterval;	// !< 弾発射間隔
	aqua::CTimer	m_DarknessTimer;// !< 視界不良時間
	aqua::CTimer	m_LaserTimer;	// !< レーザー発射時間

	DIRECTION_ID	m_DirectionId;	// !< 弾方向ID
	float			m_ShotInterval;	// !< 発射間隔
	int				m_LaserPoint;	// !< レーザーポイント
	float			m_LaserSpeed;	// !< レーザースピード
	int				m_ShotSpeed;	// !< 弾の速度
	bool			m_LaserShotFlag;// !< レーザー発射中フラグ
	bool			m_DarknessFlag;	// !< 視界不良状態フラグ
	bool			m_EffectFlag;	// !< 軌道エフェクトフラグ

private: // 非公開メンバ定数

	static const int			m_max_life_point;		// !< プレイヤーの最大体力
	static const float			m_move_speed;			// !< プレイヤーの移動速度
	static const float			m_max_laser_speed;		// !< 最大レーザー速度
	static const float			m_max_shot_interval;	// !< 最大発射間隔
	static const float			m_start_shot_interval;	// !< 初期段階反射間隔
	static const DIRECTION_ID	m_start_direction_id;	// !< 初期段階方向ID
	static const BULLET_ID		m_start_bullet_id;		// !< 初期段階発射弾ID
	static const float			m_start_laser_speed;	// !< 初期段階レーザースピード
	static const float			m_normal_bullet_speed;	// !< 弾発射速度
	static const float			m_iecrease_interval;	// !< 発射間隔の減少量
	static const float			m_laser_time;			// !< レーザー時間
	static const float			m_darkness_time;		// !< 視界不良時間
	static const float			m_add_speed;			// !< レーザースピード増加速度
	static const int			m_bonus_score;			// !< ボーナススコア
	static const float			m_limit_position_x;		// !< 限界移動可能位置（X）
	static const float			m_limit_position_y;		// !< 限界移動可能位置（Y）
	static const float			m_random_angle;			// !< 弾がぶれる角度
	static const float			m_first_angle;			// !< １つ目の追加方向
	static const float			m_second_angle;			// !< ２つ目の追加方向
	static const float			m_third_angle;			// !< ３つ目の追加方向
	static const float			m_fourth_angle;			// !< ４つ目の追加方向
	static const float			m_fifth_angle;			// !< ５つ目の追加方向
	static const float			m_fifth_angle;			// !< ５つ目の追加方向
	static const float			m_sixth_angle;			// !< ６つ目の追加方向
};