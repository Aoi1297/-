#include "laserspeed.h"

CLaserSpeed::CLaserSpeed(IGameObject* parent)
	// parent(CItemManager)
	: IItem(parent, "ShotSpeedUp")
{
}

void CLaserSpeed::Initialize(void)
{
	IItem::CreateSprite("data/texture/item/laser_speed.png");
}
