#pragma once

#include "../effect.h"

class CDamage : public IEffect
{
public: // ���J�����o�֐�

	// �R���X�g���N�^
	CDamage(IGameObject* parent);

	// �f�X�g���N�^
	~CDamage() = default;

	// �������֐�
	void Initialize(void)override;

	// �X�V�֐�
	void Update(void)override;
};