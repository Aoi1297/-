#include "firework_bullet.h"

const float CFireWorkBullet::m_easing_time			= 0.5f;
const float CFireWorkBullet::m_max_bullet_speed		= 5.0f;
const float CFireWorkBullet::m_bullet_deceleration	= 1.0f;
const int   CFireWorkBullet::m_add_alpha			= 10;
const int   CFireWorkBullet::m_reset_alpha			= 110;

CFireWorkBullet::CFireWorkBullet(IGameObject* parent)
	// parent(CBulletManager)
	: IBullet(parent, "FireWorkBullet")
{
}

void CFireWorkBullet::Initialize(void)
{
	IBullet::CreateSprite("data/texture/bullet/fire_work_red.png");

	// 発光用の弾スプライトを生成
	m_FlashSprite.Create("data/texture/bullet/fire_work_green.png");

	// 発光用スプライトの初期化
	{
		// 基準点を中心にする
		m_FlashSprite.anchor = m_BulletSprite.anchor;

		// 発光用のスプライトを透明にする
		m_FlashSprite.color.alpha = 0;
	}

	// イージングタイマー設定
	m_EasingTimer.Setup(m_easing_time);
}

void CFireWorkBullet::OriginalMovement(void)
{
	// イージングタイマー更新
	if (!m_EasingTimer.Finished())
	{
		m_EasingTimer.Update();
	}

	// 弾出現時徐々に小さくなるようなイージング処理を行う
	m_BulletSprite.scale.x = m_FlashSprite.scale.x = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), 20, 2);
	m_BulletSprite.scale.y = m_FlashSprite.scale.y = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), 20, 2);

	// 発光用のスプライトの透明なら徐々に不透明にしていく
	if (m_FlashSprite.color.alpha <= 255) m_FlashSprite.color.alpha += m_add_alpha;

	// 半透明になったら一度透明にする
	else if (m_FlashSprite.color.alpha >= m_reset_alpha) m_FlashSprite.color.alpha = 0;

	// 弾を徐々に遅くする
	if (m_BulletSpeed > m_max_bullet_speed) m_BulletSpeed -= m_bullet_deceleration;

	// 弾の位置更新
	m_FlashSprite.position = m_Position;
}

void CFireWorkBullet::Draw(void)
{
	m_FlashSprite.Draw();

	m_BulletSprite.Draw();
}

void CFireWorkBullet::Finalize(void)
{
	m_FlashSprite.Delete();

	m_BulletSprite.Delete();
}
