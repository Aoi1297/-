#pragma once

#include "../unit.h"

class IEnemy : public IUnit
{
public: // ���J�����o�֐�

	// �R���X�g���N�^
	IEnemy			(IGameObject* parent, const std::string& object_name);

	// �f�X�g���N�^
	~IEnemy			(void)	override = default;

	// �^�C�}�[�X�V
	void TimerUpdate(void);

protected: // ������J�����o�֐�

	// �o�������o����
	virtual void SpawanEffect(void) = 0;

	// �s������
	virtual void Movement(void) = 0;

	// �G�ˌ�����
	virtual void Fire(void) = 0;

protected: // ������J�����o�ϐ�

	aqua::CTimer m_FireTimer;

	aqua::CTimer m_EasingTimer;
};