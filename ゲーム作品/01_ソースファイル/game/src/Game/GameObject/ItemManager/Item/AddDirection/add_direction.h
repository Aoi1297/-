#pragma once

#include "../item.h"

class CAddDirection : public IItem
{
public: // ���J�����o�֐�

	// �R���X�g���N�^
	CAddDirection	(IGameObject* parent);

	// �f�X�g���N�^
	~CAddDirection	(void)	override = default;

	// �������֐�
	void Initialize	(void)	override;
};