#pragma once

#include "aqua.h"

class IScene : public aqua::IGameObject
{
public: // ���J�����o�֐�

	// �R���X�g���N�^
	IScene	(IGameObject* parent, const std::string& object_name);

	// �f�X�g���N�^
	~IScene	(void) override = default;
};