#pragma once

#include "aqua.h"

// �O���錾
class CPlayer;

class CField : public aqua::IGameObject
{
public: // ���J�����o�֐�

	// �R���X�g���N�^
	CField			(IGameObject* parent);

	// �f�X�g���N�^
	~CField			(void) = default;

	// �������֐�
	void Initialize	(void)	override;

	// �X�V�֐�
	void Update		(void)	override;

	// �`��֐�
	void Draw		(void)	override;

	// ����֐�
	void Finalize	(void)	override;

private: // ����J�����o�֐�

	// �^�C�}�[�X�V
	void TimerUpdate	(void);

	// �w�i�ړ��ʌv�Z
	void MoveCalculation(void);

	// �w�i�ړ�����
	void MoveBackGround	(void);

private: // ����J�����o�ϐ�

	// �X�v���C�g�摜
	aqua::CSprite	m_BackGroundSprite;			// !< �����Ȃ��w�i
	aqua::CSprite	m_BackGroundMoveSprite;		// !< �����w�i�P����
	aqua::CSprite	m_BackGroundMoveNextSprite;	// !< �����w�i�Q����

	// �^�C�}�[�ϐ�
	aqua::CTimer	m_MiniBossSpawnTimer;		// !< ���{�X���o�����鎞��

	// �|�C���^�ϐ�
	CPlayer* m_Player_P;

	float m_BackGroundSpeed;

	float m_BackGroundSpeedPlus;

	bool m_MiniBossFlag;
	
private: // ����J�����o�萔

	static const int m_pixel_width;	// !< �ڂ������i�P�O�O�łP�s�N�Z���j
	static const int m_param;		// !< �ڂ����̋���
	static const float m_mini_boss_spawn_time;
	static const float m_back_ground_speed_normal;
	static const float m_back_ground_speed_laser;
	static const float m_back_ground_speed_headmode;
};