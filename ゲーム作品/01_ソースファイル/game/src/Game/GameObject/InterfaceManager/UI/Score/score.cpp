#include "score.h"

#include "../../../CameraManager/camera_manager.h"

const aqua::CVector2 CUIScore::m_score_num_position{ 900,40 };

CUIScore::CUIScore(IGameObject* parent)
	// parent(CUiManager)
	: IUserInterface(parent,"UIScore")
	, m_Score(0)
	, m_DigitWidth(0)
	, m_CameraManager_P(nullptr)
{
}

void CUIScore::Initialize(void)
{
	// �uSCORE�v�摜�̐���
	m_ScoreSprite.Create("data/texture/ui/score.png");

	// �u0123456789�v�摜�̐���
	m_ScoreNumSprite.Create("data/texture/ui/score_num.png");
	// �uSCORE�v�̉E�ɕ`�悳���悤�ɒ���
	m_ScoreNumSprite.position = m_score_num_position;

	// �ꌅ���̕����擾
	m_DigitWidth = m_ScoreNumSprite.GetTextureWidth() / 10;

	// �J�����}�l�[�W���[�N���X�I�u�W�F�N�g�̃|�C���^�擾
	m_CameraManager_P = (CCameraManager*)aqua::FindGameObject("CameraManager");
}

void CUIScore::Update(void)
{
	// ���t���[���X�R�A�����Z�����
	m_Score++;
}

void CUIScore::Draw(void)
{
	// ��ʐU���̒l���擾
	aqua::CVector2 camera_pos = m_CameraManager_P->GetPosition();

	// �Z�o�p�̃X�R�A���擾
	int score = m_Score;

	// �X�R�A�i�����j�̕`����s��
	for (int i = 0; i < 10; ++i)
	{
		// �X�R�A�̈ꌅ�ڂ̐������擾
		int digit = score % 10;

		// �����摜�̕`��͈͂��擾�����ꌅ�ڂɉ���������������͈͂ɐݒ肷��
		m_ScoreNumSprite.rect.left = digit * m_DigitWidth;
		m_ScoreNumSprite.rect.right = digit * m_DigitWidth + m_DigitWidth;

		// �����ɉ����Đ����̕������ɂ��炵�Đ�������ׂ�
		m_ScoreNumSprite.position.x = -m_DigitWidth * i + m_score_num_position.x + camera_pos.x;
		m_ScoreNumSprite.position.y = m_score_num_position.y + camera_pos.y;

		// ���ׂ�������`�悵�Ă���
		m_ScoreNumSprite.Draw();

		// �`��������Ȃ�������r������
		score /= 10;
	}

	// ��ʐU��
	m_ScoreSprite.position = camera_pos;

	// �uSCORE�v�摜�̕`��
	m_ScoreSprite.Draw();
}

void CUIScore::Finalize(void)
{
	// �X�v���C�g�̃��������
	m_ScoreNumSprite.Delete();
	m_ScoreSprite.Delete();
}

void CUIScore::AddScore(int score)
{
	m_Score += score;
}
