#include "homing_bullet.h"

#include "../../../EffectManager/effect_manager.h"
#include "../../../UnitManager/unit_manager.h"
#include "../../../SoundManager/sound_creater.h"

const float CHomingBullet::m_homing_time	= 1.0f;
const float CHomingBullet::m_start_position = 100.0f;
const float CHomingBullet::m_homing_angle	= 5.0f;

CHomingBullet::CHomingBullet(IGameObject* parent)
	// parent(CBulletManager)
	: IBullet(parent, "HomingBullet")
{
}

void CHomingBullet::Initialize(void)
{
	// �z�[�~���O�e�̉摜����
	IBullet::CreateSprite("data/texture/bullet/normal_bullet_blue.png");

	// ���ʉ���炷
	((CSoundCreater*)aqua::FindGameObject("SoundManager"))->Play(SOUND_ID::EFFECT_LASER);

	// �z�[�~���O�^�C�}�[�̐ݒ�
	m_HomingTimer.Setup(m_homing_time);

	// �z�[�~���O�ʒu�����炷
	m_Position.y -= m_start_position;
}

void CHomingBullet::OriginalMovement(void)
{
	// �z�[�~���O�^�C�}�[�X�V
	m_HomingTimer.Update();

	// ���[�U�[�G�t�F�N�g�𖈃t���[����������
	m_EffectManager->CreateEffect(EFFECT_ID::LASER, GetCenterPosition(), m_Category);

	// �z�[�~���O�^�C�}�[���I�����Ă��Ȃ���΁@���@�v���C���[���������ꍇ
	if (!(m_HomingTimer.Finished()) && m_Category == CATEGORY_ID::PLAYER)
	{
		// �v���C���[�ȊO�̈�ԋ߂��ɂ��郆�j�b�g�̃N���X�|�C���^���擾����
		IUnit* unit = ((CUnitManager*)aqua::FindGameObject("UnitManager"))->FindNearUnit(this);

		// �擾�������j�b�g�̃N���X�|�C���^��NULL�`�F�b�N���s��
		if (unit == nullptr) return;

		// ��ԋ߂��ɂ������j�b�g�ƃz�[�~���O�e�̋��������߂�
		const aqua::CVector2 distance = unit->GetCenterPosition() - GetCenterPosition();

		// �����̒e���i�s�����ɑ΂��ĉE�����ɂ��邩���ׂ�
		const float direction = aqua::CVector2::Cross(distance, m_Velocity);

		if (direction > 0.0f)
		{
			m_Direction -= m_homing_angle;
		}
		else
		{
			m_Direction += m_homing_angle;
		}

		// �e�̔��ˊp�x�Ɍ������Đi�ނ悤�Ɍv�Z����
		m_Velocity.x = cos(aqua::DegToRad(m_Direction));
		m_Velocity.y = sin(aqua::DegToRad(m_Direction));
	}

	// �G���������ꍇ�@���@�z�[�~���O�^�C�}�[���I�����Ă��Ȃ��Ƃ�
	if (m_Category == CATEGORY_ID::ENEMY && !(m_HomingTimer.Finished()))
	{
		// ���j�b�g�}�l�[�W���[���X�g�̐擪�̓v���C���[���i�[����Ă��邽��
		const auto& it = ((CUnitManager*)aqua::FindGameObject("UnitManager"))->GetChildList()->begin();

		// �v���C���[�N���X�I�u�W�F�N�g�̎擾
		IUnit* player = (IUnit*)*it;

		// �v���C���[NULL�`�F�b�N
		if (player == nullptr)return;

		// �v���C���[�ƒe�̋��������߂�
		const aqua::CVector2 distance = player->GetCenterPosition() - GetCenterPosition();

		// �v���C���[�ɑ΂��Ēe���E���������ɂ���̂��𒲂ׂ�
		const float direction = aqua::CVector2::Cross(distance, m_Velocity);

		if (direction > 0.0f)
		{
			m_Direction -= m_homing_angle;
		}
		else
		{
			m_Direction += m_homing_angle;
		}

		// �e�̔��ˊp�x�Ɍ������Đi�ނ悤�Ɍv�Z����
		m_Velocity.x = cos(aqua::DegToRad(m_Direction));
		m_Velocity.y = sin(aqua::DegToRad(m_Direction));
	}

	// �e�̍X�V�������s��
	m_BulletSprite.position = m_Position;
}