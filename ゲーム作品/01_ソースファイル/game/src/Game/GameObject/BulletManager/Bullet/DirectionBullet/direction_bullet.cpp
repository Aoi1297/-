#include "direction_bullet.h"

#include "../../../UnitManager/unit_manager.h"
#include "../../../UnitManager/Unit/Player/player.h"

const float CDirectionBullet::m_easing_time = 0.5f;
const float CDirectionBullet::m_move_speed	= 9.0f;

CDirectionBullet::CDirectionBullet(IGameObject* parent)
	// parent(CBulletManager)
	: IBullet(parent, "DirectionBullet")
{
}

void CDirectionBullet::Initialize(void)
{
	IBullet::CreateSprite("data/texture/bullet/star_red.png");

	// プレイヤーの位置と弾の角度を正規化した値を格納する
	m_PlayerNormalize = (((CPlayer*)aqua::FindGameObject("Player"))->GetCenterPosition() - GetCenterPosition()).Normalize();

	// イージング時間設定
	m_EasingTimer.Setup(m_easing_time);
}

void CDirectionBullet::OriginalMovement(void)
{
	// イージングタイマー更新
	if (!m_EasingTimer.Finished()) m_EasingTimer.Update();

	// 徐々に小さくなるようにイージングをかける
	m_FlashSprite.scale.x = m_BulletSprite.scale.x = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), 20, 4);
	m_FlashSprite.scale.y = m_BulletSprite.scale.y = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), 20, 4);

	// 弾移動処理
	m_Position += m_PlayerNormalize * m_move_speed;

	// 位置更新
	m_BulletSprite.position = m_Position;
}