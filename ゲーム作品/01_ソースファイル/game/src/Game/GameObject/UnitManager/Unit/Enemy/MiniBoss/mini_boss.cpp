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
	// �摜�̐������ݒ�
	CreateSprite("data/texture/unit/mini_boss.png");

	// ���j�b�g�̗͐ݒ�
	m_LifePoint = m_max_life_point;

	// �e�̑��x
	m_ShotSpeed = m_shot_speed;

	// ���ˊԊu�ݒ�
	m_FireTimer.Setup(m_fire_interval);

	// �C�[�W���O�^�C�}�[�ݒ�
	m_EasingTimer.Setup(m_easing_time);

	// �G�l�~�[�o���Ԋu�^�C�}�[�ݒ�
	m_EnemySpawnTimer.Setup(m_spwan_time);

	// �z�[�~���O���[�U�[�Ԋu�^�C�}�[�ݒ�
	m_HomingTimer.Setup(m_homing_time);

	// �����܂ł̎��Ԑݒ�
	m_EscapeTimer.Setup(m_escape_time);

	// ���j�b�g�X�v���C�g�T�C�Y�ύX
	m_UnitSprite.scale = m_unit_scale;

	// ���j�b�g�̈ړ����x�ݒ�
	m_MoveSpeed = m_move_speed;

	// ���[�U�[�����X�s�[�h
	m_LaserSpeed = m_shot_speed;
}

void CMiniBoss::Update(void)
{
	// �^�C�}�[�X�V
	TimerUpdate();

	// �o��������
	SpawanEffect();

	// �����̏���
	Movement();

	// �ˌ�����
	Fire();
}

void CMiniBoss::SpawanEffect(void)
{
	// �o�����ɏ��X�ɉ摜�T�C�Y�������Ȃ��Ă����悤�ɏo��������
	m_UnitSprite.scale.x = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), m_max_scale.x, m_unit_scale.x);
	m_UnitSprite.scale.y = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), m_max_scale.y, m_unit_scale.y);
}

void CMiniBoss::Movement(void)
{
	// ���j�b�g�摜����]������
	m_UnitSprite.rotation += aqua::DegToRad(m_rotation_angle);

	// �o�����͂������ړ����x��x������
	if (m_MoveSpeed >= 0) m_MoveSpeed -= m_move_deceleration;

	// ���x��0�ȉ��ɂȂ�����
	else
	{
		// ��~������
		m_MoveSpeed = 0;

		// �㉺�ɓ��������߂̊p�x�{
		m_Angle++;

		// �T�C���g�̂悤�ɏ㉺�ɓ���������
		m_Position.y = sin(aqua::DegToRad(m_Angle)) * m_move_upand_down + m_move_upand_down;

		// �G�o���^�C�}�[�X�V
		m_EnemySpawnTimer.Update();

		// �z�[�~���O���[�U�[�^�C�}�[�X�V
		m_HomingTimer.Update();
	}

	// �̗͂��T�O���ȉ��ɂȂ����ꍇ
	if (m_LifePoint <= m_max_life_point * 0.5f)
	{
		// ���[�U�[�̑��x�𑬂�����
		m_LaserSpeed = m_laser_speed_50;

		// �z�[�~���O���[�U�[�̊Ԋu��Z������
		m_HomingTimer.Setup(m_laser_time_50);
	}

	// �̗͂��Q�O���ȉ��ɂȂ����ꍇ
	if (m_LifePoint <= m_max_life_point * 0.2f)
	{
		// ���[�U�[�̑��x������ɑ�������
		m_LaserSpeed = m_laser_speed_20;

		// �z�[�~���O���[�U�[�̊Ԋu������ɒZ������
		m_HomingTimer.Setup(m_laser_time_20);
	}

	// ���Ԑ؂�Ń{�X��������
	if (m_EscapeTimer.Finished())
	{
		m_MoveSpeed += m_move_acceleration;
	}

	// ���x���ړ����s��
	m_Position.x -= m_MoveSpeed;

	// �摜�̈ړ�
	m_UnitSprite.position = m_Position;
}

void CMiniBoss::Fire(void)
{
	// ���˃^�C�}�[���O�ɂȂ�����
	if (m_FireTimer.Finished())
	{
		// �m�[�}���e�𔭎�
		m_BulletManager_P->CreateBullet(CATEGORY_ID::ENEMY, BULLET_ID::NORMAL, GetCenterPosition(), m_ShotSpeed, 180 + aqua::Rand(m_random_angle) - m_random_angle / 2);

		// ���˃^�C�}�[���Z�b�g
		m_FireTimer.Reset();
	}

	// �G�o���^�C�}�[���O�ɂȂ�����
	if (m_EnemySpawnTimer.Finished())
	{
		// �ԉΓG�𐶐�
		//m_UnitManager_P->CreateUnit(UNIT_ID::FIRE_WORK, GetCenterPosition());

		// �X�|�[���^�C�}�[���Z�b�g
		m_EnemySpawnTimer.Reset();
	}

	// �z�[�~���O���[�U�[�^�C�}�[
	if (m_HomingTimer.Finished())
	{
		// �z�[�~���O���[�U�[����
		m_BulletManager_P->CreateBullet(CATEGORY_ID::ENEMY, BULLET_ID::HOMING, GetCenterPosition(), m_LaserSpeed, 0);

		// �^�C�}�[���Z�b�g
		m_HomingTimer.Reset();
	}
}

float CMiniBoss::GetRadius(void)
{
	return m_hit_radius;
}
