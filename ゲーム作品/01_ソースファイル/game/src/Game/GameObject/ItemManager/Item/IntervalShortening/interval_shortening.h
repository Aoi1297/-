#pragma once

#include "../item.h"

class CIntervalShortening : public IItem
{
public: // ���J�����o�֐�

	// �R���X�g���N�^
	CIntervalShortening	(IGameObject* parent);

	// �f�X�g���N�^
	~CIntervalShortening(void)	override = default;

	// �������֐�
	void Initialize		(void)	override;
};