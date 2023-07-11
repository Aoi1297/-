#include "lasermeter.h"

CLaserMeter::CLaserMeter(IGameObject* parent)
	// parent(CItemManager)
	: IItem(parent,"LaserMeter")
{
}

void CLaserMeter::Initialize(void)
{
	IItem::CreateSprite("data/texture/item/laser_meter.png");
}