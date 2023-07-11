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
	// ���j�b�g�}�l�[�W���[�̃N���X�|�C���^�̎擾
	m_UnitManager_P = (CUnitManager*)aqua::FindGameObject("UnitManager");
}

void CItemManager::Update(void)
{
	// ���������A�C�e���ƃ��j�b�g�̓����蔻����s��
	for (auto it = GetChildList()->begin(); it != GetChildList()->end(); ++it)
	{
		// �A�C�e�����X�g�����ɑ{������
		IItem* item = (IItem*)(*it);

		// �A�C�e������ʊO�ւ���������ł�����
		if (item->GetCenterPosition().x > aqua::GetWindowWidth()) item->DeleteObject();

		// ���j�b�g�ƃA�C�e���̓����蔻����s���i�v���C���[�����ł͂Ȃ��A�S�Ẵ��j�b�g���Ή�����j
		m_UnitManager_P->CheckUnit(item);
	}

	// ���������N���X�q�I�u�W�F�N�g�̍X�V���s��
	IGameObject::Update();
}

void CItemManager::Draw(void)
{
	// ���������N���X�q�I�u�W�F�N�g�̕`����s��
	IGameObject::Draw();
}

void CItemManager::Finalize(void)
{
	// ���������N���X�q�I�u�W�F�N�g�̉�����s��
	IGameObject::Finalize();
}

void CItemManager::CreateItem(const ITEM_ID& item_id, const aqua::CVector2& create_pos)
{
	IItem* item = nullptr;

	// ��������A�C�e��ID�ɑ΂���N���X�I�u�W�F�N�g�𐶐�����
	switch (item_id)
	{
	case ITEM_ID::LASER:item = aqua::CreateGameObject<CLaserMeter>(this);				break;
	case ITEM_ID::SPEED:item = aqua::CreateGameObject<CLaserSpeed>(this);				break;
	case ITEM_ID::DIRECTION:item = aqua::CreateGameObject<CAddDirection>(this);			break;
	case ITEM_ID::INTERVAL:item = aqua::CreateGameObject<CIntervalShortening>(this);	break;
	}

	if (item)item->SetStatus(item_id, create_pos);
}