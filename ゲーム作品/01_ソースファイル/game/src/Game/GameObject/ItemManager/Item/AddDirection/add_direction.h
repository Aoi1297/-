#pragma once

#include "../item.h"

class CAddDirection : public IItem
{
public: // 公開メンバ関数

	// コンストラクタ
	CAddDirection	(IGameObject* parent);

	// デストラクタ
	~CAddDirection	(void)	override = default;

	// 初期化関数
	void Initialize	(void)	override;
};