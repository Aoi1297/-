#pragma once

#include "../scene.h"

class CGameMain : public IScene
{
public: // ���J���z�֐�

	// �R���X�g���N�^
	CGameMain		(IGameObject* parent);

	// �f�X�g���N�^
	~CGameMain		(void) = default;

	// �������֐�
	void Initialize	(void)	override;

	// �X�V�֐�
	void Update		(void)	override;

	// �`��֐�
	void Draw		(void)	override;

	// ����֐�
	void Finalize	(void)	override;

public: // ���J�֐�

	// �Q�[���o�ߎ��Ԏ擾
	inline float	GetGameTime		(void)	{ return m_GameTimer.GetTime(); }

	// �Q�[���I�[�o�[�Z�b�g
	inline void		SetGameOverFlag	(void)	{ m_GameOverFlag = true; }

	// �Q�[���I�[�o�[�t���O�擾
	inline bool		GetGameOverFlag	(void)	{ return m_GameOverFlag; }

private: // ����J�����o�ϐ�

	// �^�C�}�[�ϐ�
	aqua::CTimer	m_GameTimer;	// !< �Q�[���o�ߎ���

	// �Q�[���I�[�o�[�t���O
	bool			m_GameOverFlag;	// !< �Q�[���I�[�o�[�t���O

private: // ����J�����o�萔

	static const aqua::CVector2 m_player_position;	// !< �v���C���[�̏����ʒu
	static const float			m_game_time_set;	// !< �Q�[���o�ߎ��ԏ���ݒ�
};