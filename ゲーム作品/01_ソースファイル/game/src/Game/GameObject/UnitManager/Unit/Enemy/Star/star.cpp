#include "star.h"

#include "../../../unit_manager.h"
#include "../../../../BulletManager/bullet_manager.h"

const int	CStar::m_max_life_point			= 10;
const float CStar::m_fire_interval			= 1.7f;
const float CStar::m_easing_time			= 0.7f;
const float CStar::m_random_angle			= 6;
const aqua::CVector2 CStar::m_unit_scale	= { 1.0f,1.0f };
const aqua::CVector2 CStar::m_max_scale		= { 15.0f,15.0f };
const float CStar::m_rotation_angle			= 5.0f;
const float CStar::m_shot_speed				= 5.0f;
const float CStar::m_move_acceleration		= 0.01f;

CStar::CStar(IGameObject* parent)
	// parent(CGameMain)
	: IEnemy(parent, "Star")
{
}

void CStar::Initialize(void)
{
	// 画像の生成＆設定
	CreateSprite("data/texture/unit/star.png");

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

void CStar::Update(void)
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

float CStar::GetRadius(void)
{
	return m_UnitSprite.GetTextureHeight() / 2 * m_unit_scale.y;
}

void CStar::SpawanEffect(void)
{
	// 出現時に徐々に画像サイズ小さくなっていくように出現させる
	m_UnitSprite.scale.x = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), m_max_scale.x, m_unit_scale.x);
	m_UnitSprite.scale.y = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), m_max_scale.y, m_unit_scale.y);
}

void CStar::Movement(void)
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

void CStar::Fire(void)
{
	// 発射タイマーが０になったら
	if (m_FireTimer.Finished())
	{
		// ノーマル弾を発射
		m_BulletManager_P->CreateBullet(CATEGORY_ID::ENEMY, BULLET_ID::DIRECTION, GetCenterPosition(), m_ShotSpeed, 180 + aqua::Rand(m_random_angle) - m_random_angle / 2);

		// 発射タイマーリセット
		m_FireTimer.Reset();
	}
}
