#pragma once

#include "aqua.h"

#include "../SceneManager/Scene/scene.h"

enum class SCENE_ID
{
	TITLE,		// タイトル
	GAMEMAIN,	// ゲームメイン
	RESULT,		// リザルト

	DUMMY,		// 判定用ダミー
};

class CSceneManager : public aqua::IGameObject
{
public: // 公開メンバ関数

	// コンストラクタ
	CSceneManager	(IGameObject* parent);

	// デストラクタ
	~CSceneManager	(void)	override = default;

	// 初期化関数
	void Initialize	(void)	override;

	// 更新関数
	void Update		(void)	override;

	// 描画関数
	void Draw		(void)	override;

	// 解放関数
	void Finalize	(void)	override;

public: // 公開メンバ関数

	// IDに対応するシーンへ移動する
	void ChangeScene(SCENE_ID id);

private: // 非公開メンバ変数

	IScene*		m_CurrentScene_P;	// !< 現在のシーン
	SCENE_ID	m_NextScene;		// !< 次のシーン
};