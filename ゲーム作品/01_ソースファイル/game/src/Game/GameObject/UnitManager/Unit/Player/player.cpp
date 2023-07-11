#include "player.h"

#include "../../../BulletManager/bullet_manager.h"
#include "../../../ItemManager/item_manager.h"
#include "../../../InterfaceManager/ui_manager.h"
#include "../../../InterfaceManager/UI/Score/score.h"
#include "../../../UnitManager/unit_manager.h"

const int CPlayer::			m_max_life_point		= 20;
const float CPlayer::		m_move_speed			= 5.0f;
const float CPlayer::		m_start_shot_interval	= 1.0f;
const float CPlayer::		m_start_laser_speed		= 10.0f;
const DIRECTION_ID CPlayer::m_start_direction_id	= DIRECTION_ID::FRONT;
const BULLET_ID CPlayer::	m_start_bullet_id		= BULLET_ID::NORMAL;
const float CPlayer::		m_laser_time			= 3.0f;
const float CPlayer::		m_darkness_time			= 6.0f;
const float CPlayer::		m_max_laser_speed		= 30.0f;
const float CPlayer::		m_add_speed				= 2.0f;
const int CPlayer::			m_bonus_score			= 10000;
const float CPlayer::		m_max_shot_interval		= 0.135f;
const float CPlayer::		m_iecrease_interval		= 0.08f;
const float CPlayer::		m_normal_bullet_speed	= 25.0f;
const float CPlayer::		m_limit_position_x		= 1420;
const float CPlayer::		m_limit_position_y		= 150;
const float CPlayer::		m_random_angle			= 6.0f;
const float CPlayer::		m_first_angle			= -15.0f;
const float CPlayer::		m_second_angle			= 15.0f;
const float CPlayer::		m_third_angle			= -45.0f;
const float CPlayer::		m_fourth_angle			= 45.0f;
const float CPlayer::		m_fifth_angle			= -135.0f;
const float CPlayer::		m_sixth_angle			= 135.0f;

CPlayer::CPlayer(aqua::IGameObject* parent)
	// parent(CGameMain)
	: IUnit				(parent, "Player")
	, m_LaserSpeed		(0.0f)
	, m_ShotInterval	(0.0f)
	, m_LaserPoint		(0)
	, m_LaserShotFlag	(false)
	, m_DarknessFlag	(false)
	, m_EffectFlag		(true)
{
}

void CPlayer::Initialize(void)
{
	// �摜�̐����������ݒ�
	CreateSprite("data/texture/unit/player.png");

	// ���g�̃|�C���^���Z�b�g
	SetPlayerPointer();

	// �̗͂�ݒ�
	m_LifePoint = m_max_life_point;

	// �����i�K�̔��ˑ��x
	{
		m_ShotInterval = m_start_shot_interval;
		m_FireInterval.Setup(m_start_shot_interval);
	}

	// ���[�U�[�X�s�[�h�ݒ�
	m_ShotSpeed = m_normal_bullet_speed;

	// �e���ˑ��x�ݒ�
	m_LaserSpeed = m_start_laser_speed;

	// �����i�K�̔��˕����ݒ�
	m_DirectionId = m_start_direction_id;

	// �e�̎�ސݒ�
	m_ShotKind = m_start_bullet_id;

	// ���[�U�[���Ԑݒ�
	m_LaserTimer.Setup(m_laser_time);

	// �ÈŎ��Ԑݒ�
	m_DarknessTimer.Setup(m_darkness_time);
}

void CPlayer::Update(void)
{
	// �v���C���[����
	Controller();

	// �ˌ�
	Fire();
}

void CPlayer::PowerUp(ITEM_ID item_id)
{
	switch (item_id)
	{
		// �uP�v�A�C�e����������ꍇ
	case ITEM_ID::LASER:
	{
		// UI��\��
		m_UiManager_P->ShowMessage(ITEM_ID::LASER);

		// ���[�U�[�|�C���g�A�b�v
		m_LaserPoint++;
	}break;

	// �uS�v�A�C�e����������ꍇ
	case ITEM_ID::SPEED:
	{
		// UI��\��
		m_UiManager_P->ShowMessage(ITEM_ID::SPEED);

		// �ő呬�x�𒴂��Ă��Ȃ���Α��x��ǉ�����
		if (m_LaserSpeed <= m_max_laser_speed) m_LaserSpeed += m_add_speed;
		else
		{
			// �ő呬�x�𒴂�����ő呬�x�ɂ���
			m_LaserSpeed = m_max_laser_speed;

			// �{�[�i�X�X�R�A��ǉ�
			m_Score_P->AddScore(m_bonus_score);
		}
	}break;

	// �u���v�A�C�e����������ꍇ
	case ITEM_ID::DIRECTION:
	{
		// UI��\��
		m_UiManager_P->ShowMessage(ITEM_ID::DIRECTION);

		// ���˕��������i�K���P���₷
		switch (m_DirectionId)
		{
		case DIRECTION_ID::FRONT:			m_DirectionId = DIRECTION_ID::DOUBLE;		break;
		case DIRECTION_ID::DOUBLE:			m_DirectionId = DIRECTION_ID::TRIPLE;		break;
		case DIRECTION_ID::TRIPLE:			m_DirectionId = DIRECTION_ID::QUAD;			break;
		case DIRECTION_ID::QUAD:			m_DirectionId = DIRECTION_ID::DOUBLE_DOUBLE; break;
		case DIRECTION_ID::DOUBLE_DOUBLE:	m_DirectionId = DIRECTION_ID::TRIPLE_TRIPLE; break;
		case DIRECTION_ID::TRIPLE_TRIPLE:	m_DirectionId = DIRECTION_ID::QUAD_QUAD;	break;
		case DIRECTION_ID::QUAD_QUAD:		m_DirectionId = DIRECTION_ID::FINAL;		break;

			// �ŏI�i�K���ł̓{�[�i�X�X�R�A���ǉ������
		default:m_Score_P->AddScore(m_bonus_score); break;
		}
	}break;

	// �uI�v�A�C�e����������ꍇ
	case ITEM_ID::INTERVAL:
	{
		// UI��\��
		m_UiManager_P->ShowMessage(ITEM_ID::INTERVAL);

		// ���ˊԊu��������
		if (m_ShotInterval > m_max_shot_interval)
		{
			// ���ˊԊu����
			m_ShotInterval -= m_iecrease_interval;

			// ���ˊԊu�^�C�}�[�Z�b�g
			m_FireInterval.Setup(m_ShotInterval);
		}
		else
		{
			// ���ɂ����O���G�t�F�N�g�𖳌���
			m_EffectFlag = false;

			// ���ˊԊu���ő�l�𒴂����璴���Ȃ��悤�ɐݒ�
			m_ShotInterval = m_max_shot_interval;

			// �{�[�i�X�X�R�A��ǉ�����
			m_Score_P->AddScore(m_bonus_score);
		}
	}break;
	}
}

float CPlayer::GetRadius(void)
{
	return m_UnitSprite.GetTextureHeight() / 2;
}

void CPlayer::Controller(void)
{
	// ���E�s�Ǐ�ԂȂ�
	if (m_DarknessFlag)
	{
		// ���E�s�ǎ��Ԍv��
		m_DarknessTimer.Update();
	}
	if (m_DarknessTimer.Finished())
	{
		// ���E�s�ǎ��ԃ��Z�b�g
		m_DarknessFlag = false;
		m_DarknessTimer.Reset();
	}

	// ��Ɉړ�����
	if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::W) || aqua::keyboard::Button(aqua::keyboard::KEY_ID::UP))
		m_Position.y -= m_move_speed;
	
	// ���Ɉړ�����
	if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::A) || aqua::keyboard::Button(aqua::keyboard::KEY_ID::LEFT))
		m_Position.x -= m_move_speed;

	// ���Ɉړ�����
	if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::S) || aqua::keyboard::Button(aqua::keyboard::KEY_ID::DOWN))
		m_Position.y += m_move_speed;

	// �E�Ɉړ�����
	if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::D) || aqua::keyboard::Button(aqua::keyboard::KEY_ID::RIGHT))
		m_Position.x += m_move_speed;

	// ��ʍ��[���ړ����Ȃ�
	if (m_Position.x <= 0)
	{
		m_Position.x = 0;
	}

	// ���̈ʒu�܂łł����ړ��ł��Ȃ��悤�ɂ���i�E�����j
	if (m_Position.x >= m_limit_position_x - m_UnitSprite.GetTextureWidth())
	{
		m_Position.x = m_limit_position_x - m_UnitSprite.GetTextureWidth();
	}

	// ���UI�܂ł̈ʒu�ȏ�i�߂Ȃ��悤�ɂ���
	if (m_Position.y <= m_limit_position_y)
	{
		m_Position.y = m_limit_position_y;
	}

	// ����UI�܂ł̈ʒu�ȏ�i�߂Ȃ��悤�ɂ���
	if (m_Position.y >= aqua::GetWindowHeight() - m_limit_position_y - m_UnitSprite.GetTextureHeight())
	{
		m_Position.y = aqua::GetWindowHeight() - m_limit_position_y - m_UnitSprite.GetTextureHeight();
	}

	// �v���C���[�摜�̈ړ�����
	m_UnitSprite.position = m_Position;
}

void CPlayer::Fire(void)
{
	// ���[�U�[���Ȃ烌�[�U�[�^�C�}�[���N��
	if (m_LaserShotFlag) m_LaserTimer.Update();

	// �E���������Ă����
	if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::SPACE))
	{
		// ���������Ă���Ԃ̓^�C�}�[���N��
		m_FireInterval.Update();

		// �v��I�������e�𔭎˂���
		if (m_FireInterval.Finished())
		{
			// �v���C���[�̒��S�ʒu
			aqua::CVector2 center_position = GetCenterPosition();

			// ���݂̔��˕���ID�ɉ����ĕ��ʂ������ς���
			switch (m_DirectionId)
			{
			case DIRECTION_ID::FRONT:
			{
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, aqua::Rand(m_random_angle) - m_random_angle / 2);
			}break;
			case DIRECTION_ID::DOUBLE:
			{
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, aqua::Rand(m_random_angle) - m_random_angle / 2);
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, aqua::Rand(m_random_angle));
			}break;
			case DIRECTION_ID::TRIPLE:
			{
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, aqua::Rand(m_random_angle) - m_random_angle / 2);
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_first_angle - aqua::Rand(m_random_angle));
			}break;
			case DIRECTION_ID::QUAD:
			{
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, aqua::Rand(m_random_angle) - m_random_angle / 2);
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_first_angle - aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_second_angle - aqua::Rand(m_random_angle));
			}break;
			case DIRECTION_ID::DOUBLE_DOUBLE:
			{
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, aqua::Rand(m_random_angle) - m_random_angle / 2);
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_first_angle - aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_second_angle - aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_third_angle - aqua::Rand(m_random_angle));
			}break;
			case DIRECTION_ID::TRIPLE_TRIPLE:
			{
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, aqua::Rand(m_random_angle) - m_random_angle / 2);
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_first_angle - aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_second_angle - aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_third_angle - aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_fourth_angle - aqua::Rand(m_random_angle));
			}break;
			case DIRECTION_ID::QUAD_QUAD:
			{
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, aqua::Rand(m_random_angle) - m_random_angle / 2);
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_first_angle - aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_second_angle - aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_third_angle - aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_fourth_angle - aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_fifth_angle - aqua::Rand(m_random_angle));
			}break;
			case DIRECTION_ID::FINAL:
			{
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, aqua::Rand(m_random_angle) - m_random_angle / 2);
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_first_angle - aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_second_angle - aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_third_angle - aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_fourth_angle - aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_fifth_angle - aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_sixth_angle - aqua::Rand(m_random_angle));
			}break;
			}

			// ���[�U�[���Ԃ��I�����Ă��Ȃ�������@���@���[�U�[�����ǂ���
			if (!m_LaserTimer.Finished() && m_LaserShotFlag)
			{
				// �z�[�~���O���[�U�[�����
				m_BulletManager_P->CreateBullet(m_UnitCategory, BULLET_ID::HOMING, center_position, m_LaserSpeed, 0);
			}

			// ���[�U�[���Ԃ��I�����Ă�����
			else if (m_LaserTimer.Finished())
			{
				// ���[�U�[��~
				m_LaserShotFlag = false;

				// ���[�U�[�^�C�}�[���Z�b�g
				m_LaserTimer.Reset();

				// ���[�U�[�|�C���g���Z�b�g
				m_LaserPoint = 0;
			}

			// �e���ł��I������甭�ˊԊu�^�C�}�[�����Z�b�g����
			m_FireInterval.Reset();
		}
	}
}