#pragma once

#include "../ui.h"

// �O���錾
class CPlayer;
class CCameraManager;

class CUIFrame : public IUserInterface
{
public: // ���J�����o�֐�

	// �R���X�g���N�^
	CUIFrame		(IGameObject* parent);

	// �f�X�g���N�^
	~CUIFrame		(void)	override = default;

	// �������֐�
	void Initialize	(void)	override;

	// �X�V�֐�
	void Update		(void)	override;

	// �`��֐�
	void Draw		(void)	override;

private: // ����J�����o�ϐ�


	float m_LineLength;

	// ���݂̃��[�U�[�|�C���g
	float m_LaserPoint;

	// ���[�U�[�|�C���g�̊���
	float m_LaserPointRatio;

	// ���݂̗̑�
	float m_HitPoint;

	// �̗͂̊���
	float m_HitPointRatio;

	// �v���C���[�N���X�I�u�W�F�N�g�̃|�C���^�ϐ�
	CPlayer* m_Player_P;

	// �J�����}�l�[�W���[�N���X�I�u�W�F�N�g�̃|�C���^�ϐ�
	CCameraManager* m_CameraManager_P;

private: // ����J�����o�萔

	static const float m_max_laser_point;			// !< ���[�U�[���˂܂łɕK�v�ȃ|�C���g
	static const unsigned int m_up_frame_color;	// !< ��̃t���[���i�����`�j�̐F
	static const unsigned int m_down_frame_color;	// !< ���̃t���[���i�����`�j�̐F
	static const unsigned int m_laser_line_color;	// !< ���[�U�[���[�^�[�̐F
	static const unsigned int m_hp_line_color;		// !< �g�o���[�^�[�̐F
	static const unsigned int m_line_color;		// !< ���[�^�[�̐F�i�D�F�j
	static const int m_line_thickness;				// !< ���[�^�[�̑���
	static const float m_frame_height;				// !< �t���[���̏c��
	static const float m_line_height;				// !< ���[�^�[�̏c��
};