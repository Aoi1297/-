#pragma once

#include "aqua.h"

class IScene : public aqua::IGameObject
{
public: // 公開メンバ関数

	// コンストラクタ
	IScene	(IGameObject* parent, const std::string& object_name);

	// デストラクタ
	~IScene	(void) override = default;
};