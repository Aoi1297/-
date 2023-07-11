#include "interval_shortening.h"

CIntervalShortening::CIntervalShortening(IGameObject* parent)
	// parent(CItemManager)
	: IItem(parent, "IntervalShortening")
{
}

void CIntervalShortening::Initialize(void)
{
	IItem::CreateSprite("data/texture/item/interval.png");
}
