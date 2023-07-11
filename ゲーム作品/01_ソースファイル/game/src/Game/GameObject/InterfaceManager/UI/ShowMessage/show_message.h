#pragma once

#include "../ui.h"

// 前方宣言
enum class ITEM_ID;

class CShowMessage : public IUserInterface
{
public:	// 公開メンバ関数

	// コンストラクタ
	CShowMessage(IGameObject* parent);

	// デストラクタ
	~CShowMessage()override = default;

	// 表示するメッセージ識別関数
	void ShowMessage(const ITEM_ID& item_id);

	// 初期化関数
	void Initialize(void)override;

	// 更新関数
	void Update(void)override;

	// 描画関数
	void Draw(void)override;

	// 解放関数
	void Finalize(void)override;

private: // 非公開メンバ変数

	// 表示するアイテム効果を識別するためのID
	ITEM_ID m_ItemId;

	// 表示する瞬間の効果を与えるための時間
	aqua::CTimer m_EasingTimer;

	// 表示をやめる効果を与えるための時間
	aqua::CTimer m_FinishMessageTimer;

	// 透明になった回数
	int m_AlphaCount;

private: // 非公開メンバ定数

	static const float	m_easing_time;			// !< イージング時間
	static const float	m_finish_message_time;	// !< 消滅時間
	static const float	m_message_max_scale;	// !< 最大スケール
	static const float	m_message_scale;		// !< 標準スケール
	static const int	m_alpha_count;			// !< 透明度カウント
};
