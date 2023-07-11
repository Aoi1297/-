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

	// �v���C���[�̈ʒu�ƒe�̊p�x�𐳋K�������l���i�[����
	m_PlayerNormalize = (((CPlayer*)aqua::FindGameObject("Player"))->GetCenterPosition() - GetCenterPosition()).Normalize();

	// �C�[�W���O���Ԑݒ�
	m_EasingTimer.Setup(m_easing_time);
}

void CDirectionBullet::OriginalMovement(void)
{
	// �C�[�W���O�^�C�}�[�X�V
	if (!m_EasingTimer.Finished()) m_EasingTimer.Update();

	// ���X�ɏ������Ȃ�悤�ɃC�[�W���O��������
	m_FlashSprite.scale.x = m_BulletSprite.scale.x = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), 20, 4);
	m_FlashSprite.scale.y = m_BulletSprite.scale.y = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), 20, 4);

	// �e�ړ�����
	m_Position += m_PlayerNormalize * m_move_speed;

	// �ʒu�X�V
	m_BulletSprite.position = m_Position;
}