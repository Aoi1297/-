#pragma once

#include "../item.h"

class CLaserMeter : public IItem
{
public: // 公開メンバ関数

	// コンストラクタ
	CLaserMeter		(IGameObject* parent);

	// デストラクタ
	~CLaserMeter	(void)	override = default;

	// 初期化関数
	void Initialize	(void)	override;
};