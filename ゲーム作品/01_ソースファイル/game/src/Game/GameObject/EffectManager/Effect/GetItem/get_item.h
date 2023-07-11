#pragma once

#include "../effect.h"

class CGetItem : public IEffect
{
public: // ���J�����o�֐�

	// �R���X�g���N�^
	CGetItem		(IGameObject* parent);

	// �f�X�g���N�^
	~CGetItem		(void) = default;

	// �������֐�
	void Initialize	(void)	override;

	// �X�V�֐�
	void Update		(void)	override;

	// �`��֐�
	void Draw		(void)	override;

	//�X�V�֐�
	void Finalize	(void)	override;

private: // ����J�����o�ϐ�

	// �����p�G�t�F�N�g�X�v���C�g
	aqua::CSprite m_EffectFlash;

	// �A�C�e���l���t���O
	bool GetItemFlag;

private: // ����J�����o�萔

	static const float	m_easing_time;
	static const float	m_max_size;
	static const float	m_start_size;
	static const float	m_final_size;
	static const float	m_max_angle;
	static const int	m_add_alpha;
};