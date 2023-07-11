#include "fire_work.h"


#include "../../../unit_manager.h"
#include "../../../../BulletManager/bullet_manager.h"
#include "..\FireWorkTough\fire_work_tough.h"

const int	CFireWork::m_max_life_point			= 5;
const float CFireWork::m_fire_interval			= 1.7f;
const float CFireWork::m_easing_time			= 0.7f;
const float CFireWork::m_random_angle			= 6;
const aqua::CVector2 CFireWork::m_unit_scale	= { 2.0f,2.0f };
const aqua::CVector2 CFireWork::m_max_scale		= { 15.0f,15.0f };
const float CFireWork::m_rotation_angle			= 35.0f;
const float CFireWork::m_shot_speed				= 10.0f;
const float CFireWork::m_move_acceleration		= 0.01f;
const float CFireWork::m_hit_radius				= 40.0f;

CFireWork::CFireWork(IGameObject* parent)
	// parent(CGameMain)
	: IEnemy(parent, "FireWork")
{
}

void CFireWork::Initialize(void)
{
	// 画像の生成＆設定
	CreateSprite("data/texture/unit/fire_work.png");

	// ユニット体力設定
	m_LifePoint = m_max_life_point;

	// 弾の速度
	m_ShotSpeed = m_shot_speed;

	// 発射間隔設定
	m_FireTimer.Setup(m_fire_interval);

	// イージングタイマー設定
	m_EasingTimer.Setup(m_easing_time);

	// ユニットスプライトサイズ変更
	m_UnitSprite.scale = m_unit_scale;
}

void CFireWork::Update(void)
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

float CFireWork::GetRadius(void)
{
	return m_hit_radius;
}

void CFireWork::SpawanEffect(void)
{
	// 出現時に徐々に画像サイズ小さくなっていくように出現させる
	m_UnitSprite.scale.x = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), m_max_scale.x, m_unit_scale.x);
	m_UnitSprite.scale.y = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), m_max_scale.y, m_unit_scale.y);
}

void CFireWork::Movement(void)
{
	// ユニット画像を回転させる
	m_UnitSprite.rotation += aqua::DegToRad(m_rotation_angle);

	// 徐々に移動速度が加速していく
	m_MoveSpeed += m_move_acceleration;

	// 速度分移動を行う
	m_Position.x -= m_MoveSpeed;

	// 画像の移動
	m_UnitSprite.position = m_Position;
}


void CFireWork::Fire(void)
{
	// 発射タイマーが０になったら
	if (m_FireTimer.Finished())
	{
		// 花火弾を発射
		m_BulletManager_P->CreateBullet(CATEGORY_ID::ENEMY, BULLET_ID::FIREWORK, GetCenterPosition(), m_ShotSpeed, aqua::RadToDeg(m_UnitSprite.rotation));
		m_BulletManager_P->CreateBullet(CATEGORY_ID::ENEMY, BULLET_ID::FIREWORK, GetCenterPosition(), m_ShotSpeed, aqua::RadToDeg(m_UnitSprite.rotation) + 30);
		m_BulletManager_P->CreateBullet(CATEGORY_ID::ENEMY, BULLET_ID::FIREWORK, GetCenterPosition(), m_ShotSpeed, aqua::RadToDeg(m_UnitSprite.rotation) + 90);
		m_BulletManager_P->CreateBullet(CATEGORY_ID::ENEMY, BULLET_ID::FIREWORK, GetCenterPosition(), m_ShotSpeed, aqua::RadToDeg(m_UnitSprite.rotation) + 120);
		m_BulletManager_P->CreateBullet(CATEGORY_ID::ENEMY, BULLET_ID::FIREWORK, GetCenterPosition(), m_ShotSpeed, aqua::RadToDeg(m_UnitSprite.rotation) + 150);
		m_BulletManager_P->CreateBullet(CATEGORY_ID::ENEMY, BULLET_ID::FIREWORK, GetCenterPosition(), m_ShotSpeed, aqua::RadToDeg(m_UnitSprite.rotation) + 210);
		m_BulletManager_P->CreateBullet(CATEGORY_ID::ENEMY, BULLET_ID::FIREWORK, GetCenterPosition(), m_ShotSpeed, aqua::RadToDeg(m_UnitSprite.rotation) + 240);
		m_BulletManager_P->CreateBullet(CATEGORY_ID::ENEMY, BULLET_ID::FIREWORK, GetCenterPosition(), m_ShotSpeed, aqua::RadToDeg(m_UnitSprite.rotation) + 270);
		m_BulletManager_P->CreateBullet(CATEGORY_ID::ENEMY, BULLET_ID::FIREWORK, GetCenterPosition(), m_ShotSpeed, aqua::RadToDeg(m_UnitSprite.rotation) + 330);
		m_BulletManager_P->CreateBullet(CATEGORY_ID::ENEMY, BULLET_ID::FIREWORK, GetCenterPosition(), m_ShotSpeed, aqua::RadToDeg(m_UnitSprite.rotation) + 360);
		m_FireTimer.Reset();

		// 発射タイマーリセット
		m_FireTimer.Reset();
	}
}
