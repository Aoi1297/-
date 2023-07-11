#pragma once

#include "../bullet.h"

class CNormalBullet : public IBullet
{
public: // ���J�����o�֐�

	// �R���X�g���N�^
	CNormalBullet			(IGameObject* parent);

	// �f�X�g���N�^
	~CNormalBullet			(void) = default;

	// ������
	void Initialize			(void)	override;

	// �e�̓����I�ȓ�������
	void OriginalMovement	(void)	override;

	// �`��֐�
	void Draw				(void)	override;

	// ����֐�
	void Finalize			(void)	override;

private: // ����J�����o�ϐ�

	// �C�[�W���O�^�C�}�[
	aqua::CTimer m_EasingTimer;
	aqua::CTimer m_EffectTimer;

private: // ����J�����o�萔

	static const float	m_effect_time;				// !< �G�t�F�N�g����
	static const float	m_easing_time;				// !< �C�[�W���O����
	static const float	m_effect_time_for_enemy;	// !< �G�̃G�t�F�N�g����
	static const int	m_bullet_size;				// !< �e�̃T�C�Y
	static const int	m_bullet_boss_max_size;		// !< �e�̍ő�T�C�Y�i�{�X�j
	static const int	m_bullet_enemy_max_size;	// !< �e�̍ő�T�C�Y�i�G�j
	static const int	m_bullet_player_max_size;	// !< �e�̍ő�T�C�Y�i�v���C���[�j
	static const int	m_bullet_max_speed;			// !< �e�̍ő呬�x
	static const float	m_bullet_deceleration;		// !< �e�̏����p�x
};