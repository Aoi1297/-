#pragma once

#include "../ui.h"

class CEffectManager;

class CUiGameClear : public IUserInterface
{
public: // ���J�����o�֐�

	// �R���X�g���N�^
	CUiGameClear	(IGameObject* parent);

	// �f�X�g���N�^
	~CUiGameClear	(void)	override = default;

	// �������֐�
	void Initialize	(void)	override;

	// �X�V�֐�
	void Update		(void)	override;

	// �`��֐�
	void Draw		(void)	override;

	// ����֐�
	void Finalize	(void)	override;

private: // ����J�����o�ϐ�

	// �G�t�F�N�g�}�l�[�W���[�̃N���X�|�C���^
	CEffectManager* m_EffectManager_P;

	// �Q�[���N���A��\������܂ł̎���
	aqua::CTimer m_GameClearTime;

	// �G�t�F�N�g�𐶐�����Ԋu
	aqua::CTimer m_EffectTime;

	// �`��t���O
	bool DrawFlag;
};