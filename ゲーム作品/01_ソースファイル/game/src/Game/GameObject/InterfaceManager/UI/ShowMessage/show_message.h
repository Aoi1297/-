#pragma once

#include "../ui.h"

// �O���錾
enum class ITEM_ID;

class CShowMessage : public IUserInterface
{
public:	// ���J�����o�֐�

	// �R���X�g���N�^
	CShowMessage(IGameObject* parent);

	// �f�X�g���N�^
	~CShowMessage()override = default;

	// �\�����郁�b�Z�[�W���ʊ֐�
	void ShowMessage(const ITEM_ID& item_id);

	// �������֐�
	void Initialize(void)override;

	// �X�V�֐�
	void Update(void)override;

	// �`��֐�
	void Draw(void)override;

	// ����֐�
	void Finalize(void)override;

private: // ����J�����o�ϐ�

	// �\������A�C�e�����ʂ����ʂ��邽�߂�ID
	ITEM_ID m_ItemId;

	// �\������u�Ԃ̌��ʂ�^���邽�߂̎���
	aqua::CTimer m_EasingTimer;

	// �\������߂���ʂ�^���邽�߂̎���
	aqua::CTimer m_FinishMessageTimer;

	// �����ɂȂ�����
	int m_AlphaCount;

private: // ����J�����o�萔

	static const float	m_easing_time;			// !< �C�[�W���O����
	static const float	m_finish_message_time;	// !< ���Ŏ���
	static const float	m_message_max_scale;	// !< �ő�X�P�[��
	static const float	m_message_scale;		// !< �W���X�P�[��
	static const int	m_alpha_count;			// !< �����x�J�E���g
};
