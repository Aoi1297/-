#pragma once

#include "../bullet.h"

class CDirectionBullet : public IBullet
{
public: // ���J�����o�֐�

	// �R���X�g���N�^
	CDirectionBullet		(IGameObject* parent);

	// �f�X�g���N�^
	~CDirectionBullet		(void) = default;

	// ������
	void Initialize			(void)	override;

	// �e�̓����I�ȓ�������
	void OriginalMovement	(void)	override;

private: // ����J�����o�ϐ�

	// �C�[�W���O�^�C�}�[�X�V
	aqua::CTimer m_EasingTimer;

	// �v���C���[�p�x
	aqua::CVector2 m_PlayerNormalize;

private: // ����J�����o�萔

	static const float m_easing_time;
	static const float m_move_speed;
};