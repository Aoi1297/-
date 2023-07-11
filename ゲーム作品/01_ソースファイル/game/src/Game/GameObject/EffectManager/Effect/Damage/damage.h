#pragma once

#include "../effect.h"

class CDamage : public IEffect
{
public: // 公開メンバ関数

	// コンストラクタ
	CDamage(IGameObject* parent);

	// デストラクタ
	~CDamage() = default;

	// 初期化関数
	void Initialize(void)override;

	// 更新関数
	void Update(void)override;
};