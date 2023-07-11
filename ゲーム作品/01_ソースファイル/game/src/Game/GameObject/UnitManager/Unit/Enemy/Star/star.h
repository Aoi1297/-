#pragma once

#include "aqua.h"

#include "../enemy.h"

class CStar : public IEnemy
{
public:	// ���J�I�[�o�[���C�h�֐�

	// �R���X�g���N�^
	CStar(IGameObject* parent);

	// �f�X�g���N�^
	~CStar(void)	override = default;

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
	static const float			m_hit_radius;			// !< ���j�b�g�̓����蔻��
};