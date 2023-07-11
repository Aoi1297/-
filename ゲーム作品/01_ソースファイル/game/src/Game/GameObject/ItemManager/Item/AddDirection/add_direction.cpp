#include "add_direction.h"

CAddDirection::CAddDirection(IGameObject* parent)
	// parent(CItemManager)
	: IItem(parent, "AddDirection")
{
}

void CAddDirection::Initialize(void)
{
	IItem::CreateSprite("data/texture/item/direction.png");
}
