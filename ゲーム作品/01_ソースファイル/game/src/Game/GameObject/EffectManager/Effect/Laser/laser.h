#pragma once

#include "../effect.h"

class CLaser : public IEffect
{
public: // ���J�����o�֐�

	// �R���X�g���N�^
	CLaser(IGameObject* parent);

	// �f�X�g���N�^
	~CLaser() = default;

	// ������
	void Initialize(void)override;

	// �X�V
	void Update(void)override;

	// �`��
	void Draw(void)override;
	
	// ���
	void Finalize(void)override;

private: // ����J�����o�ϐ�

	static const aqua::CVector2 m_effect_size;
	static const float m_effect_decrease_size;
	static const int m_effect_decrease_alpha;
	static const int m_effect_delete_alpha;
};