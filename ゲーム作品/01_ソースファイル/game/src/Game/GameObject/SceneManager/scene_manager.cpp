#include "scene_manager.h"

#include "Scene/scene.h"
#include "scene/1_Title/title.h"
#include "scene/2_GameMain/game_main.h"
#include "Scene/3_Result/result.h"

CSceneManager::CSceneManager(aqua::IGameObject* parent)
	// parent(CGame)
	: IGameObject(parent, "SceneManager")
	, m_CurrentScene_P(nullptr)
	, m_NextScene(SCENE_ID::TITLE)
{
}

void CSceneManager::Initialize(void)
{
	// 最初に始まるシーンを設定
	m_NextScene = SCENE_ID::TITLE;
}

void CSceneManager::Update(void)
{
	// シーンを切り替える必要がなければ以降の処理を行わない
	if (m_NextScene == SCENE_ID::DUMMY)
	{
		// 現在のシーンの更新処理を行う
		IGameObject::Update();
		return;
	}

	// シーンが存在している場合は以下の処理を行う
	if (m_CurrentScene_P)
	{	
		// 現在のシーンの解放処理を行う
		m_CurrentScene_P->Finalize();

		// 現在のシーンを削除する（子リストから外す）
		m_ChildObjectList.erase(std::find(m_ChildObjectList.begin(), m_ChildObjectList.end(), m_CurrentScene_P));

		// ポインタの破棄＆NULL化
		AQUA_SAFE_DELETE(m_CurrentScene_P)
	}

	// シーンの生成とシーンの初期化を行う
	switch (m_NextScene)
	{
	case SCENE_ID::TITLE:	 m_CurrentScene_P = aqua::CreateGameObject<CTitle>(this);	break;
	case SCENE_ID::GAMEMAIN: m_CurrentScene_P = aqua::CreateGameObject<CGameMain>(this);break;
	case SCENE_ID::RESULT:	 m_CurrentScene_P = aqua::CreateGameObject<CResult>(this);	break;
	}

	// シーンを生成したらDUMMYに戻す
	m_NextScene = SCENE_ID::DUMMY;

	// 生成したクラスオブジェクト（シーン）の初期化
	IGameObject::Initialize();

	// 生成したシーンの更新処理を行う
	IGameObject::Update();
}

void CSceneManager::Draw(void)
{
	// 生成したクラスオブジェクトの描画を行う
	IGameObject::Draw();
}

void CSceneManager::Finalize(void)
{
	// 生成したクラスオブジェクトの解放を行う
	IGameObject::Finalize();
}

void CSceneManager::ChangeScene(SCENE_ID scene_id)
{
	// 変更するシーンを設定する
	m_NextScene = scene_id;
}