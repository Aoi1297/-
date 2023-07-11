#include "ui.h"

IUserInterface::IUserInterface(IGameObject* parent, const std::string& object_name)
	// parent(CUiManager)
	: IGameObject(parent, object_name)
{
}