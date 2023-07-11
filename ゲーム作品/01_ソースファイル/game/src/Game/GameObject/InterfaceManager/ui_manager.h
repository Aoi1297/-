#pragma once

#include "aqua.h"

// 前方宣言
enum class ITEM_ID;

// UIID
enum class UI_ID
{
	FRAME,
	SCORE,
	GAMEOVER,
	GAMECLEAR,

	MAX,
};

class CUiManager : public aqua::IGameObject
{
public: // 公開メンバ関数

	// コンストラクタ
	CUiManager(IGameObject* parent);

	// デストラクタ
	~CUiManager() override = default;

	// 仮想更新関数
	virtual void Update(void)override;

	// 仮想描画関数
	virtual void Draw(void)override;

	// 仮想解放関数
	virtual void Finalize(void)override;

	// UI生成
	void CreateUI(UI_ID id);

	// メッセージ表示
	void ShowMessage(const ITEM_ID& power_id);
};