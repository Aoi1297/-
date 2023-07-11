#pragma once

#include "../ui.h"

class CUiGameOver : public IUserInterface
{
public: // ���J�����o�֐�

	// �R���X�g���N�^
	CUiGameOver		(IGameObject* parent);

	// �f�X�g���N�^
	~CUiGameOver	(void)	override = default;

	// �������֐�
	void Initialize	(void)	override;

	// �X�V�֐�
	void Update		(void)	override;

	// �`��֐�
	void Draw		(void)	override;

	// ����֐�
	void Finalize	(void)	override;
};