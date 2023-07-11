#pragma once

#include "../effect.h"

class CSpawn : public IEffect
{
public: // ���J�����o�֐�

	// �R���X�g���N�^
	CSpawn(IGameObject* parent);

	// �f�X�g���N�^
	~CSpawn() = default;

	// �������֐�
	void Initialize(void)override;

	// �X�V�֐�
	void Update(void)override;

private: // ����J�����o�ϐ�

	// ��]�l
	float m_Rotation;

private: // ����J�����o�萔

	static const float	m_easing_time;		// !< ���ʎ���
	static const float	m_sprite_size;		// !< �X�v���C�g�T�C�Y
	static const int	m_alpha_decrease;	// !< �X�v���C�g�T�C�Y
	static const int	m_delete_num;		// !< �X�v���C�g�T�C�Y
};