#pragma once

#include "aqua.h"

#include "../enemy.h"

// �O���錾
class CUnitManager;

class CMiniBoss : public IEnemy
{
public:	// ���J�I�[�o�[���C�h�֐�

	// �R���X�g���N�^
	CMiniBoss(IGameObject* parent);

	// �f�X�g���N�^
	~CMiniBoss(void)	override = default;

	// �������֐�
	void Initialize(void)  override;

	// �X�V�֐�
	void Update(void)	override;

	// �����蔻��擾
	float GetRadius(void)override;

private: // ����J�����o�֐�

	// �o�����̃G�t�F�N�g
	void SpawanEffect(void)override;

	// ��������
	void Movement(void)override;

	// �ˌ�����
	void Fire(void)override;

private: // ����J�����o�ϐ�

	aqua::CTimer	m_EnemySpawnTimer;	// !< �G�l�~�[�o���Ԋu

	aqua::CTimer	m_HomingTimer;		// !< �z�[�~���O�Ԋu

	aqua::CTimer	m_EscapeTimer;		// !< �{�X�����^�C�}�[

	float			m_Angle;			// !< �T�C���g�̂��߂̊p�x

	float			m_LaserSpeed;		// !< ���[�U�[���x

	CUnitManager*	m_UnitManager_P;	// !< ���j�b�g�}�l�[�W���[�N���X�|�C���^�̎擾

private: // ����J�����o�萔

	static const int			m_max_life_point;		// !< ���j�b�g�ő�̗�
	static const float			m_fire_interval;		// !< �ˌ��Ԋu
	static const float			m_easing_time;			// !< �o�����̃C�[�W���O����
	static const aqua::CVector2 m_unit_scale;			// !< ���j�b�g�T�C�Y
	static const aqua::CVector2	m_max_scale;			// !< ���j�b�g�ő�T�C�Y
	static const float			m_random_angle;			// !< �e�̃u���̍ő�p�x
	static const float			m_rotation_angle;		// !< ���j�b�g�̉�]�p�x
	static const float			m_shot_speed;			// !< �e�̑��x
	static const float			m_move_acceleration;	// !< ���j�b�g�̉����x
	static const float			m_move_deceleration;	// !< ���j�b�g�̌����x
	static const float			m_move_upand_down;		// !< �㉺�ړ���
	static const float			m_spwan_time;			// !< ���j�b�g�������x
	static const float			m_homing_time;			// !< �z�[�~���O�Ԋu
	static const float			m_escape_time;			// !< �{�X��������
	static const float			m_move_speed;			// !< �{�X��������
	static const int			m_laser_speed_50;		// !< �̗͂T�O���ȉ����̃z�[�~���O���[�U�[���x
	static const float			m_laser_time_50;		// !< �̗͂T�O���ȉ����̃z�[�~���O���[�U�[���ˊԊu
	static const int			m_laser_speed_20;		// !< �̗͂Q�O���ȉ����̃z�[�~���O���[�U�[���x
	static const float			m_laser_time_20;		// !< �̗͂Q�O���ȉ����̃z�[�~���O���[�U�[���ˊԊu
	static const float			m_hit_radius;			// !< ���j�b�g�̓����蔻��
};