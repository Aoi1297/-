#pragma once

#include "../ui.h"

class CUiGameOver : public IUserInterface
{
public: // 公開メンバ関数

	// コンストラクタ
	CUiGameOver		(IGameObject* parent);

	// デストラクタ
	~CUiGameOver	(void)	override = default;

	// 初期化関数
	void Initialize	(void)	override;

	// 更新関数
	void Update		(void)	override;

	// 描画関数
	void Draw		(void)	override;

	// 解放関数
	void Finalize	(void)	override;
};