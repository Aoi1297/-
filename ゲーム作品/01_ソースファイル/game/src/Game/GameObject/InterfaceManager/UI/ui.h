#pragma once

#include "aqua.h"

class IUserInterface : public aqua::IGameObject
{
public: // ���J�����o�֐�

	// �R���X�g���N�^
	IUserInterface(IGameObject* parent, const std::string& object_name);

	// �f�X�g���N�^
	~IUserInterface() override = default;

protected: // ������J�����o�ϐ�

	// UI�X�v���C�g
	aqua::CSprite m_UiSprite;
};