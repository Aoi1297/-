#pragma once

#include "aqua.h"

// アイテムID
enum class ITEM_ID
{
	LASER,
	SPEED,
	DIRECTION,
	INTERVAL,

	MAX,
};

// 前方宣言
class CUnitManager;

class CItemManager : public aqua::IGameObject
{
public: // 公開メンバ仮想関数

	// コンストラクタ
	CItemManager	(IGameObject* parent);

	// デストラクタ
	~CItemManager	(void)	override = default;

	// 初期化関数
	void Initialize	(void)	override;

	// 更新関数
	void Update		(void)	override;

	// 描画関数
	void Draw		(void)	override;

	// 解放関数
	void Finalize	(void)	override;

public: // 公開メンバ関数

	// アイテム生成
	void CreateItem(const ITEM_ID& item_id,const aqua::CVector2& create_pos);

private: // 非公開メンバ変数

	// ユニットマネージャークラスポインタ
	CUnitManager* m_UnitManager_P;
};