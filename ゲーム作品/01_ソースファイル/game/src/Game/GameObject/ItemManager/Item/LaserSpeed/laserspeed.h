#pragma once

#include "../item.h"

class CLaserSpeed : public IItem
{
public: // ���J�����o�֐�

	// �R���X�g���N�^
	CLaserSpeed		(IGameObject* parent);

	// �f�X�g���N�^
	~CLaserSpeed	(void)	override = default;

	// �������֐�
	void Initialize	(void)	override;
};