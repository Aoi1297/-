#include "result.h"

CResult::CResult(IGameObject* parent)
	: IScene(parent,"Result")
{
}

void CResult::Initialize(void)
{
	m_TitleText.Create(50);
	m_TitleText.text = "リザルト[SPACE]";
}

void CResult::Update(void)
{
	// スペースキーを押したらゲームメインシーンを生成する
	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::SPACE))
	{
		((CSceneManager*)aqua::FindGameObject("SceneManager"))->ChangeScene(SCENE_ID::TITLE);
	}
}

void CResult::Draw(void)
{
	m_TitleText.Draw();
}

void CResult::Finalize(void)
{
	m_TitleText.Delete();

	// titleの子オブジェクトの解放処理を行う
	IGameObject::Finalize();
}
