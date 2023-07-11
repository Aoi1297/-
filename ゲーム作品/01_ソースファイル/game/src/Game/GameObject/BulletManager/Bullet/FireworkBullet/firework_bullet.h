#pragma once

#include "../bullet.h"

class CFireWorkBullet : public IBullet
{
public: // ���J�����o�֐�

	// �R���X�g���N�^
	CFireWorkBullet			(IGameObject* parent);

	// �f�X�g���N�^
	~CFireWorkBullet		(void) = default;

	// ������
	void Initialize			(void)	override;

	// �e�̓����I�ȓ�������
	void OriginalMovement	(void)	override;

	// �`��
	void Draw				(void)	override;

	// ���
	void Finalize			(void)	override;

private: // ����J�����o�ϐ�

	// �C�[�W���O�^�C�}�[
	aqua::CTimer m_EasingTimer;

private: // ����J�����o�萔

	static const float m_easing_time;
	static const float m_max_bullet_speed;
	static const float m_bullet_deceleration;
	static const int m_add_alpha;
	static const int m_reset_alpha;
};