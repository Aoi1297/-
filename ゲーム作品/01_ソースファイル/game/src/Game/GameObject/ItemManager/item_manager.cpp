#include "item_manager.h"

#include "../UnitManager/unit_manager.h"

#include "Item/AddDirection/add_direction.h"
#include "Item/IntervalShortening/interval_shortening.h"
#include "Item/LaserMeter/lasermeter.h"
#include "Item/LaserSpeed/laserspeed.h"

CItemManager::CItemManager(IGameObject* parent)
	// parent(CGameMain)
	: IGameObject(parent, "ItemManager")
	, m_UnitManager_P(nullptr)
{
}

void CItemManager::Initialize(void)
{
	// ユニットマネージャーのクラスポインタの取得
	m_UnitManager_P = (CUnitManager*)aqua::FindGameObject("UnitManager");
}

void CItemManager::Update(void)
{
	// 生成したアイテムとユニットの当たり判定を行う
	for (auto it = GetChildList()->begin(); it != GetChildList()->end(); ++it)
	{
		// アイテムリストを順に捜査する
		IItem* item = (IItem*)(*it);

		// アイテムが画面外へいったら消滅させる
		if (item->GetCenterPosition().x > aqua::GetWindowWidth()) item->DeleteObject();

		// ユニットとアイテムの当たり判定を行う（プレイヤーだけではなく、全てのユニットが対応する）
		m_UnitManager_P->CheckUnit(item);
	}

	// 生成したクラス子オブジェクトの更新を行う
	IGameObject::Update();
}

void CItemManager::Draw(void)
{
	// 生成したクラス子オブジェクトの描画を行う
	IGameObject::Draw();
}

void CItemManager::Finalize(void)
{
	// 生成したクラス子オブジェクトの解放を行う
	IGameObject::Finalize();
}

void CItemManager::CreateItem(const ITEM_ID& item_id, const aqua::CVector2& create_pos)
{
	IItem* item = nullptr;

	// 生成するアイテムIDに対するクラスオブジェクトを生成する
	switch (item_id)
	{
	case ITEM_ID::LASER:item = aqua::CreateGameObject<CLaserMeter>(this);				break;
	case ITEM_ID::SPEED:item = aqua::CreateGameObject<CLaserSpeed>(this);				break;
	case ITEM_ID::DIRECTION:item = aqua::CreateGameObject<CAddDirection>(this);			break;
	case ITEM_ID::INTERVAL:item = aqua::CreateGameObject<CIntervalShortening>(this);	break;
	}

	if (item)item->SetStatus(item_id, create_pos);
}