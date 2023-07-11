#pragma once

#include "aqua.h"

class IUserInterface : public aqua::IGameObject
{
public: // 公開メンバ関数

	// コンストラクタ
	IUserInterface(IGameObject* parent, const std::string& object_name);

	// デストラクタ
	~IUserInterface() override = default;

protected: // 限定公開メンバ変数

	// UIスプライト
	aqua::CSprite m_UiSprite;
};