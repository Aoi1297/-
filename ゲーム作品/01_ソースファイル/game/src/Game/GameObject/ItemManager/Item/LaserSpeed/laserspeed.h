#pragma once

#include "../item.h"

class CLaserSpeed : public IItem
{
public: // 公開メンバ関数

	// コンストラクタ
	CLaserSpeed		(IGameObject* parent);

	// デストラクタ
	~CLaserSpeed	(void)	override = default;

	// 初期化関数
	void Initialize	(void)	override;
};