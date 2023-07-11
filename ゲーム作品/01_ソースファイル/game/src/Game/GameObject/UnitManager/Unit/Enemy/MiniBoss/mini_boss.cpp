#include "mini_boss.h"

#include "../../../unit_manager.h"
#include "../../../../BulletManager/bullet_manager.h"

const int	CMiniBoss::	m_max_life_point		= 150;
const float CMiniBoss::	m_fire_interval			= 0.5f;
const float CMiniBoss::	m_easing_time			= 0.7f;
const float CMiniBoss::	m_random_angle			= 6;
const aqua::CVector2 CMiniBoss::m_unit_scale	= { 1.0f,1.0f };
const aqua::CVector2 CMiniBoss::m_max_scale		= { 2.0f,2.0f };
const float CMiniBoss::	m_rotation_angle		= 25.0f;
const float CMiniBoss::	m_shot_speed			= 10.0f;
const float CMiniBoss::	m_move_acceleration		= 1.0f;
const float CMiniBoss::	m_move_deceleration		= 0.035f;
const float CMiniBoss::	m_move_upand_down		= 300.0f;
const float CMiniBoss::	m_spwan_time			= 5.0f;
const float CMiniBoss::	m_homing_time			= 3.0f;
const float CMiniBoss::	m_escape_time			= 30.0f;
const float CMiniBoss::	m_move_speed			= 10.0f;
const int CMiniBoss::	m_laser_speed_50		= 15;
const float CMiniBoss::	m_laser_time_50			= 2.0f;
const int CMiniBoss::	m_laser_speed_20		= 20;
const float CMiniBoss::	m_laser_time_20			= 1.0f;
const float CMiniBoss::	m_hit_radius			= 200.0f;

CMiniBoss::CMiniBoss(IGameObject* parent)
	// parent(CGameMain)
	: IEnemy(parent, "MiniBoss")
	, m_LaserSpeed(0)
	, m_Angle(0)
{
}

void CMiniBoss::Initialize(void)
{
	// 画像の生成＆設定
	CreateSprite("data/texture/unit/mini_boss.png");

	// ユニット体力設定
	m_LifePoint = m_max_life_point;

	// 弾の速度
	m_ShotSpeed = m_shot_speed;

	// 発射間隔設定
	m_FireTimer.Setup(m_fire_interval);

	// イージングタイマー設定
	m_EasingTimer.Setup(m_easing_time);

	// エネミー出現間隔タイマー設定
	m_EnemySpawnTimer.Setup(m_spwan_time);

	// ホーミングレーザー間隔タイマー設定
	m_HomingTimer.Setup(m_homing_time);

	// 逃走までの時間設定
	m_EscapeTimer.Setup(m_escape_time);

	// ユニットスプライトサイズ変更
	m_UnitSprite.scale = m_unit_scale;

	// ユニットの移動速度設定
	m_MoveSpeed = m_move_speed;

	// レーザー初期スピード
	m_LaserSpeed = m_shot_speed;
}

void CMiniBoss::Update(void)
{
	// タイマー更新
	TimerUpdate();

	// 出現時効果
	SpawanEffect();

	// 動きの処理
	Movement();

	// 射撃処理
	Fire();
}

void CMiniBoss::SpawanEffect(void)
{
	// 出現時に徐々に画像サイズ小さくなっていくように出現させる
	m_UnitSprite.scale.x = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), m_max_scale.x, m_unit_scale.x);
	m_UnitSprite.scale.y = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), m_max_scale.y, m_unit_scale.y);
}

void CMiniBoss::Movement(void)
{
	// ユニット画像を回転させる
	m_UnitSprite.rotation += aqua::DegToRad(m_rotation_angle);

	// 出現時はゆっくり移動速度を遅くする
	if (m_MoveSpeed >= 0) m_MoveSpeed -= m_move_deceleration;

	// 速度が0以下になったら
	else
	{
		// 停止させる
		m_MoveSpeed = 0;

		// 上下に動かすための角度＋
		m_Angle++;

		// サイン波のように上下に動き続ける
		m_Position.y = sin(aqua::DegToRad(m_Angle)) * m_move_upand_down + m_move_upand_down;

		// 敵出現タイマー更新
		m_EnemySpawnTimer.Update();

		// ホーミングレーザータイマー更新
		m_HomingTimer.Update();
	}

	// 体力が５０％以下になった場合
	if (m_LifePoint <= m_max_life_point * 0.5f)
	{
		// レーザーの速度を速くする
		m_LaserSpeed = m_laser_speed_50;

		// ホーミングレーザーの間隔を短くする
		m_HomingTimer.Setup(m_laser_time_50);
	}

	// 体力が２０％以下になった場合
	if (m_LifePoint <= m_max_life_point * 0.2f)
	{
		// レーザーの速度をさらに速くする
		m_LaserSpeed = m_laser_speed_20;

		// ホーミングレーザーの間隔をさらに短くする
		m_HomingTimer.Setup(m_laser_time_20);
	}

	// 時間切れでボスが逃げる
	if (m_EscapeTimer.Finished())
	{
		m_MoveSpeed += m_move_acceleration;
	}

	// 速度分移動を行う
	m_Position.x -= m_MoveSpeed;

	// 画像の移動
	m_UnitSprite.position = m_Position;
}

void CMiniBoss::Fire(void)
{
	// 発射タイマーが０になったら
	if (m_FireTimer.Finished())
	{
		// ノーマル弾を発射
		m_BulletManager_P->CreateBullet(CATEGORY_ID::ENEMY, BULLET_ID::NORMAL, GetCenterPosition(), m_ShotSpeed, 180 + aqua::Rand(m_random_angle) - m_random_angle / 2);

		// 発射タイマーリセット
		m_FireTimer.Reset();
	}

	// 敵出現タイマーが０になったら
	if (m_EnemySpawnTimer.Finished())
	{
		// 花火敵を生成
		//m_UnitManager_P->CreateUnit(UNIT_ID::FIRE_WORK, GetCenterPosition());

		// スポーンタイマーリセット
		m_EnemySpawnTimer.Reset();
	}

	// ホーミングレーザータイマー
	if (m_HomingTimer.Finished())
	{
		// ホーミングレーザー発射
		m_BulletManager_P->CreateBullet(CATEGORY_ID::ENEMY, BULLET_ID::HOMING, GetCenterPosition(), m_LaserSpeed, 0);

		// タイマーリセット
		m_HomingTimer.Reset();
	}
}

float CMiniBoss::GetRadius(void)
{
	return m_hit_radius;
}
