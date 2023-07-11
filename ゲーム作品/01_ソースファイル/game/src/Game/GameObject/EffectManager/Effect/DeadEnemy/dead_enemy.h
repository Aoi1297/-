#pragma once

#include "../effect.h"

class CDeadEnemy : public IEffect
{
public: // ���J�����o�֐�

	// �R���X�g���N�^
	CDeadEnemy		(IGameObject* parent);

	// �f�X�g���N�^
	~CDeadEnemy		(void) = default;

	// �������֐�
	void Initialize	(void)	override;

	// �X�V�֐�
	void Update		(void)	override;

	// �`��֐�
	void Draw		(void)	override;

	// ����֐�
	void Finalize	(void)	override;

private: // ����J�����o�ϐ�

	// �G�t�F�N�g�𔭌�������X�v���C�g
	aqua::CSprite m_EffectFlash;

private: // ����J�����o�萔

	static const float	m_easing_time;
	static const float	m_max_size;
	static const float	m_start_size;
	static const float	m_final_size;
	static const float	m_max_angle;
	static const int	m_add_alpha;
};