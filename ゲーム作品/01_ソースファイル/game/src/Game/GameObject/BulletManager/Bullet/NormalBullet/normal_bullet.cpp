#include "normal_bullet.h"

#include "../../../UnitManager/unit_manager.h"
#include "../../../EffectManager/effect_manager.h"
#include "../../../SoundManager/sound_creater.h"
#include "../../../UnitManager/Unit/Player/player.h"

const float CNormalBullet::	m_effect_time				= 0.01f;
const float CNormalBullet::	m_easing_time				= 0.5f;
const float CNormalBullet::	m_effect_time_for_enemy		= 0.05f;
const int CNormalBullet::	m_bullet_size				= 2;
const int CNormalBullet::	m_bullet_boss_max_size		= 30;
const int CNormalBullet::	m_bullet_enemy_max_size		= 20;
const int CNormalBullet::	m_bullet_player_max_size	= 7;
const int CNormalBullet::	m_bullet_max_speed			= 30;
const float CNormalBullet::	m_bullet_deceleration		= 1.0f;

CNormalBullet::CNormalBullet(IGameObject* parent)
	// parent(CBulletManager)
	: IBullet(parent, "NormalBullet")
{
}

void CNormalBullet::Initialize(void)
{
	// ���˂������j�b�g���G�Ȃ�ȉ��̏��������s��
	if ((m_Category == CATEGORY_ID::ENEMY || m_Category == CATEGORY_ID::BOSS))
	{
		// �G�t�F�N�g���Ԃ�ݒ�
		m_EffectTimer.Setup(m_effect_time_for_enemy);

		// �����_���Œe�̐F��ύX����
		{
			if (aqua::Rand(1))
			// �e�̐F��ԐF�ɂ���
			IBullet::CreateSprite("data/texture/bullet/normal_bullet_red.png");

			// �e�̐F���I�����W�ɂ���
			else IBullet::CreateSprite("data/texture/bullet/normal_bullet_orange.png");
		}
	}

	// ���˂������j�b�g���v���C���[�Ȃ�ȉ��̏��������s��
	if (m_Category == CATEGORY_ID::PLAYER)
	{
		// �G�t�F�N�g���Ԃ̐ݒ�
		m_EffectTimer.Setup(m_effect_time);

		// ���ʉ���炷
		((CSoundCreater*)aqua::FindGameObject("SoundManager"))->Play(SOUND_ID::EFFECT_FIRE);

		// �����_���Œe�̐F��ύX����
		{
			if (aqua::Rand(1))
			{
				// �e�̐F��ɂ���
				IBullet::CreateSprite("data/texture/bullet/normal_bullet_blue.png");
			}
			else
			{
				if (aqua::Rand(1))
				{
					// �e�̐F��΂ɂ���
					IBullet::CreateSprite("data/texture/bullet/normal_bullet_green.png");
				}
				else
				{
					// �e�̐F�����ɂ���
					IBullet::CreateSprite("data/texture/bullet/normal_bullet_purple.png");
				}
			}
		}
	}

	m_EasingTimer.Setup(m_easing_time);
}

void CNormalBullet::OriginalMovement(void)
{
	// �C�[�W���O�^�C�}�[�X�V
	if (!m_EasingTimer.Finished())
	{
		m_EasingTimer.Update();
	}

	// �e�o�������X�ɏ������Ȃ�悤�ȃC�[�W���O�������s��

	// �G���G�̏ꍇ�̃C�[�W���O
	if (m_Category == CATEGORY_ID::ENEMY)
	{
		m_BulletSprite.scale.x = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), m_bullet_boss_max_size, m_bullet_size);
		m_BulletSprite.scale.y = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), m_bullet_boss_max_size, m_bullet_size);
	}

	// �{�X�̏ꍇ�̃C�[�W���O
	if (m_Category == CATEGORY_ID::BOSS)
	{
		m_BulletSprite.scale.x = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), m_bullet_enemy_max_size, m_bullet_size);
		m_BulletSprite.scale.y = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), m_bullet_enemy_max_size, m_bullet_size);
	}

	// �v���C���[�̏ꍇ�̃C�[�W���O
	else
	{
		m_BulletSprite.scale.x = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), m_bullet_player_max_size, m_bullet_size);
		m_BulletSprite.scale.y = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), m_bullet_player_max_size, m_bullet_size);
	}

	// �e�̑��x�����X�ɒx������
	if (m_BulletSpeed > m_bullet_max_speed) m_BulletSpeed -= m_bullet_deceleration;

	// �G�t�F�N�g�^�C�}�[�X�V
	m_EffectTimer.Update();

	// �G�t�F�N�g�^�C�}�[�I����
	if (m_EffectTimer.Finished())
	{
		if (!((CPlayer*)aqua::FindGameObject("Player"))->GetEffectFlag())
			return;

		// �G�t�F�N�g�𐶐�
		m_EffectManager->CreateEffect(EFFECT_ID::BULLET_SPAWN, GetCenterPosition(), m_Category);

		// �^�C�}�[���Z�b�g
		m_EffectTimer.Reset();
	}
}

void CNormalBullet::Draw(void)
{
	m_BulletSprite.Draw();
}

void CNormalBullet::Finalize(void)
{
	m_BulletSprite.Delete();
}
