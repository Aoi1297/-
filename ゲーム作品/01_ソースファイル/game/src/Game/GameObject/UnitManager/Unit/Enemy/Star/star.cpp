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
	// �摜�̐������ݒ�
	CreateSprite("data/texture/unit/star.png");

	// ���j�b�g�̗͐ݒ�
	m_LifePoint = m_max_life_point;

	// �e�̑��x
	m_ShotSpeed = m_shot_speed;

	// ���ˊԊu�ݒ�
	m_FireTimer.Setup(m_fire_interval);

	// �C�[�W���O�^�C�}�[�ݒ�
	m_EasingTimer.Setup(m_easing_time);

	// ���j�b�g�X�v���C�g�T�C�Y�ύX
	m_UnitSprite.scale = m_unit_scale;
}

void CStar::Update(void)
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

float CStar::GetRadius(void)
{
	return m_UnitSprite.GetTextureHeight() / 2 * m_unit_scale.y;
}

void CStar::SpawanEffect(void)
{
	// �o�����ɏ��X�ɉ摜�T�C�Y�������Ȃ��Ă����悤�ɏo��������
	m_UnitSprite.scale.x = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), m_max_scale.x, m_unit_scale.x);
	m_UnitSprite.scale.y = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), m_max_scale.y, m_unit_scale.y);
}

void CStar::Movement(void)
{
	// ���j�b�g�摜����]������
	m_UnitSprite.rotation += aqua::DegToRad(m_rotation_angle);

	// ���X�Ɉړ����x���������Ă���
	m_MoveSpeed += m_move_acceleration;

	// ���x���ړ����s��
	m_Position.x -= m_MoveSpeed;

	// �摜�̈ړ�
	m_UnitSprite.position = m_Position;
}

void CStar::Fire(void)
{
	// ���˃^�C�}�[���O�ɂȂ�����
	if (m_FireTimer.Finished())
	{
		// �m�[�}���e�𔭎�
		m_BulletManager_P->CreateBullet(CATEGORY_ID::ENEMY, BULLET_ID::DIRECTION, GetCenterPosition(), m_ShotSpeed, 180 + aqua::Rand(m_random_angle) - m_random_angle / 2);

		// ���˃^�C�}�[���Z�b�g
		m_FireTimer.Reset();
	}
}
