#pragma once

#include "aqua.h"

class CCameraManager :public aqua::IGameObject
{
public: // ���J�����o�֐�

	// �R���X�g���N�^
	CCameraManager(aqua::IGameObject* parent);

	// �f�X�g���N�^
	~CCameraManager(void) = default;

	// �������֐�
	void Initialize(void) override;

	// �f�X�g���N�^
	void Update(void) override;

	// ��ʐU��
	void Shake(void);

	// �U���l�擾
	aqua::CVector2 GetPosition(void) const { return m_Position; }

private: // ����J�����o�֐�

	// �U���l�ۑ��ϐ�
	aqua::CVector2	m_Position;

	// ��ʐU���^�C�}�[
	aqua::CTimer	m_ShakeTimer;

	// �U���t���O�iON�̊ԐU���l�ɕω����N��������j
	bool			m_ShakeFlag;

private: // ����J�����o�萔
	static const float m_shake_time; // !< ��ʐU������
};