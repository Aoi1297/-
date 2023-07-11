#include "camera_manager.h"

const float CCameraManager::m_shake_time = 0.2f;

CCameraManager::CCameraManager(aqua::IGameObject* parent)
	// parent(CGameMain)
	: aqua::IGameObject(parent, "CameraManager")
	, m_ShakeFlag(false)
{
}

void CCameraManager::Initialize(void)
{
	// �U���l�̏�����
	m_Position = aqua::CVector2::ZERO;

	// �U�����Ԃ�ݒ�
	m_ShakeTimer.Setup(m_shake_time);

	// �U�������t���O��OFF�ɐݒ�
	m_ShakeFlag = false;
}

void CCameraManager::Update(void)
{
	// Shake���Ă΂ꂽ��ȉ��̏���������
	if (!m_ShakeFlag) return;

	// X���̗h�炷�l�������_���ŋ��߂�
	m_Position.x = (float)aqua::Rand(10, 1) * (aqua::Rand(1) ? 5.0f : -5.0f);
	// Y���̗h�炷�l�������_���ŋ��߂�
	m_Position.y = (float)aqua::Rand(10, 1) * (aqua::Rand(1) ? 5.0f : -5.0f);

	// ��ʐU���^�C�}�[���J�n
	m_ShakeTimer.Update();

	// �^�C�}�[�I����
	if (m_ShakeTimer.Finished())
	{
		// �^�C�}�[�̃��Z�b�g�i�o�ߎ��Ԃ��O�ɂ���j
		m_ShakeTimer.Reset();

		// �U���l���O�ɂ���
		m_Position = aqua::CVector2::ZERO;

		// ��ʐU����~
		m_ShakeFlag = false;
	}
}

void CCameraManager::Shake(void)
{
	// ��ʐU���J�n
	m_ShakeFlag = true;
}