#pragma once

#include "aqua.h"

// �O���錾
enum class ITEM_ID;

// UIID
enum class UI_ID
{
	FRAME,
	SCORE,
	GAMEOVER,
	GAMECLEAR,

	MAX,
};

class CUiManager : public aqua::IGameObject
{
public: // ���J�����o�֐�

	// �R���X�g���N�^
	CUiManager(IGameObject* parent);

	// �f�X�g���N�^
	~CUiManager() override = default;

	// ���z�X�V�֐�
	virtual void Update(void)override;

	// ���z�`��֐�
	virtual void Draw(void)override;

	// ���z����֐�
	virtual void Finalize(void)override;

	// UI����
	void CreateUI(UI_ID id);

	// ���b�Z�[�W�\��
	void ShowMessage(const ITEM_ID& power_id);
};