#pragma once

#include "../bullet.h"

class CHomingBullet : public IBullet
{
public: // ���J�����o�֐�

	// �R���X�g���N�^
	CHomingBullet(IGameObject* parent);

	// �f�X�g���N�^
	~CHomingBullet(void) = default;

	// ������
	void Initialize(void)	override;

	// �e�̓����I�ȓ�������
	void OriginalMovement(void)	override;

private: // ����J�����o�ϐ�

	// �z�[�~���O����
	aqua::CTimer m_HomingTimer;

private: // ����J�����o�萔

	static const float m_homing_time;		// !< �z�[�~���O����
	static const float m_start_position;	// !< �z�[�~���O�ꏊ�����炷�i�l�j
	static const float m_homing_angle;		// !< �z�[�~���O�p�x
};