#pragma once

#include "../item.h"

class CLaserMeter : public IItem
{
public: // ���J�����o�֐�

	// �R���X�g���N�^
	CLaserMeter		(IGameObject* parent);

	// �f�X�g���N�^
	~CLaserMeter	(void)	override = default;

	// �������֐�
	void Initialize	(void)	override;
};