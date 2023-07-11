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

	// �����p�̒e�X�v���C�g�𐶐�
	m_FlashSprite.Create("data/texture/bullet/fire_work_green.png");

	// �����p�X�v���C�g�̏�����
	{
		// ��_�𒆐S�ɂ���
		m_FlashSprite.anchor = m_BulletSprite.anchor;

		// �����p�̃X�v���C�g�𓧖��ɂ���
		m_FlashSprite.color.alpha = 0;
	}

	// �C�[�W���O�^�C�}�[�ݒ�
	m_EasingTimer.Setup(m_easing_time);
}

void CFireWorkBullet::OriginalMovement(void)
{
	// �C�[�W���O�^�C�}�[�X�V
	if (!m_EasingTimer.Finished())
	{
		m_EasingTimer.Update();
	}

	// �e�o�������X�ɏ������Ȃ�悤�ȃC�[�W���O�������s��
	m_BulletSprite.scale.x = m_FlashSprite.scale.x = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), 20, 2);
	m_BulletSprite.scale.y = m_FlashSprite.scale.y = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), 20, 2);

	// �����p�̃X�v���C�g�̓����Ȃ珙�X�ɕs�����ɂ��Ă���
	if (m_FlashSprite.color.alpha <= 255) m_FlashSprite.color.alpha += m_add_alpha;

	// �������ɂȂ������x�����ɂ���
	else if (m_FlashSprite.color.alpha >= m_reset_alpha) m_FlashSprite.color.alpha = 0;

	// �e�����X�ɒx������
	if (m_BulletSpeed > m_max_bullet_speed) m_BulletSpeed -= m_bullet_deceleration;

	// �e�̈ʒu�X�V
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
