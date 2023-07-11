#pragma once

#include "../item.h"

class CIntervalShortening : public IItem
{
public: // 公開メンバ関数

	// コンストラクタ
	CIntervalShortening	(IGameObject* parent);

	// デストラクタ
	~CIntervalShortening(void)	override = default;

	// 初期化関数
	void Initialize		(void)	override;
};