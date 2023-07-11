#include "scene.h"

IScene::IScene(aqua::IGameObject* parent, const std::string& object_name)
	// parent(CSceneManager)
	: IGameObject(parent, object_name)
{
}