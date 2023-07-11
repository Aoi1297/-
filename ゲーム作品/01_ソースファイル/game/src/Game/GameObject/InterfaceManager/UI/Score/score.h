#pragma once

#include "../ui.h"

// �O���錾
class CCameraManager;

class CUIScore : public IUserInterface
{
public: // ���J�����o�֐�

	// �R���X�g���N�^
	CUIScore(IGameObject* parent);

	// �f�X�g���N�^
	~CUIScore		(void)	override = default;

	// �������֐�
	void Initialize	(void)	override;

	// �X�V�֐�
	void Update		(void)	override;

	// �`��֐�
	void Draw		(void)	override;

	// ����֐�
	void Finalize	(void)	override;

	// �X�R�A���Z�֐�
	void AddScore	(int score);

private: // ����J�����o�ϐ�

	// ���݂̃X�R�A
	int m_Score;

	// �ꌅ��
	int m_DigitWidth;

	// �uSCORE�v�X�v���C�g
	aqua::CSprite m_ScoreSprite;

	// �u0123456789�v�X�v���C�g
	aqua::CSprite m_ScoreNumSprite;

	// �J�����}�l�[�W���[�N���X�I�u�W�F�N�g�̃|�C���^�ϐ�
	CCameraManager* m_CameraManager_P;

private: // ����J�����o�萔

	static const aqua::CVector2 m_score_num_position;	// !< �X�R�A�i�����j�̕`��ʒu
};
