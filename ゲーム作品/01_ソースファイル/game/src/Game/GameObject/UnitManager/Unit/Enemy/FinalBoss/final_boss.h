#pragma once

#include "aqua.h"

#include "../enemy.h"

// 前方宣言
class CUnitManager;

class CFinalBoss : public IEnemy
{
public:	// 公開オーバーライド関数

	// コンストラクタ
	CFinalBoss(IGameObject* parent);

	// デストラクタ
	~CFinalBoss		(void)	override = default;

	// 初期化関数
	void Initialize	(void)  override;

	// 更新関数
	void Update		(void)	override;

	// 描画関数
	void Draw		(void)	override;

	// 解放関数
	void Finalize	(void)	override;

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

	// 第二形態用スプライト
	aqua::CSprite	m_SecondFormSprite;

	// 第一砲撃発射間隔
	aqua::CTimer	m_1stFireTimer;

	// 第二砲撃発射間隔
	aqua::CTimer	m_2ndFireTimer;

	// 敵出現タイマー
	aqua::CTimer	m_EnemySpawanTimer;

	// 形態変化による初期化を行うためのフラグ
	bool			m_FormChangeInitializeFlag;

	// ユニットマネージャークラスオブジェクトのポインタ変数
	CUnitManager*	m_UnitManager_P;

private: // 非公開メンバ定数

	static const int			m_max_life_point;		// !< ユニット最大体力
	static const float			m_fire_interval;		// !< 射撃間隔
	static const float			m_enemy_spawan_interval;// !< 雑魚敵出現間隔
	static const float			m_easing_time;			// !< 出現時のイージング時間
	static const aqua::CVector2 m_unit_scale;			// !< ユニットサイズ
	static const aqua::CVector2	m_max_scale;			// !< ユニット最大サイズ
	static const float			m_random_angle;			// !< 弾のブレの最大角度
	static const float			m_rotation_angle;		// !< ユニットの回転角度
	static const float			m_shot_speed;			// !< 弾の速度
	static const float			m_move_acceleration;	// !< ユニットの加速度
	static const float			m_hit_radius;			// !< ユニットの当たり判定
	static const float			m_1st_angle;			// !< 第一形態回転角度
	static const float			m_one;					// !< 1.0fの増減用の値
	static const float			m_spawan_position_y;	// !< 敵出現最低位置
	static const float			m_spawan_random_num;	// !< 出現時の最大ランダム値
	static const int			m_1st_change_hp;		// !< 一回目の形態変化に至るまでのHP
	static const int			m_2nd_change_hp;		// !< 二回目の形態変化に至るまでのHP
	static const int			m_3rd_change_hp;		// !< 三回目の形態変化に至るまでのHP
	static const int			m_4th_change_hp;		// !< 四回目の形態変化に至るまでのHP
	static const int			m_5th_change_hp;		// !< 五回目の形態変化に至るまでのHP
	static const int			m_6th_change_hp;		// !< 六回目の形態変化に至るまでのHP
	static const int			m_7th_change_hp;		// !< 七回目の形態変化に至るまでのHP
	static const int			m_8th_change_hp;		// !< 八回目の形態変化に至るまでのHP
};
