#include "game_clear.h"

#include "../../../SceneManager/scene_manager.h"
#include "../../../EffectManager/effect_manager.h"
#include "../../../UnitManager/unit_manager.h"

CUiGameClear::CUiGameClear(IGameObject* parent)
	// parent(CUiManager)
	: IUserInterface(parent, "UIGameClear")
	, DrawFlag(false)
{
}

void CUiGameClear::Initialize(void)
{
	// ゲームクリアスプライトの生成
	m_UiSprite.Create("data/texture/ui/game_clear.png");

	// 画面の中心位置
	m_UiSprite.position = { (float)aqua::GetWindowWidth() / 2 - m_UiSprite.GetTextureWidth() / 2,(float)aqua::GetWindowHeight() / 2 - m_UiSprite.GetTextureHeight() / 2 };

	// エフェクトマネージャーのクラスポインタ
	m_EffectManager_P = (CEffectManager*)aqua::FindGameObject("EffectManager");

	// ゲームクリアを表示するまでの時間の設定
	m_GameClearTime.Setup(5.0f);

	// エフェクト生成間隔タイム設定
	m_EffectTime.Setup(0.3f);
}

void CUiGameClear::Update(void)
{
	// タイマーの更新
	m_GameClearTime.Update();
	m_EffectTime.Update();

	// タイマーが終了していたら
	if (m_GameClearTime.Finished())
	{
		DrawFlag = true;
	}

	// エフェクト生成時間がきたら生成
	if (m_EffectTime.Finished() && !DrawFlag)
	{
		// エフェクトを画面のランダムな位置に生成
		m_EffectManager_P->CreateEffect(EFFECT_ID::DEAD_ENEMY, aqua::CVector2(aqua::Rand(aqua::GetWindowWidth()), aqua::Rand(aqua::GetWindowHeight())), CATEGORY_ID::PLAYER);

		m_EffectTime.Reset();
	}

	// Zキーでタイトルに戻る
	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::Z))
	{
		Finalize();
		((CSceneManager*)aqua::FindGameObject("SceneManager"))->ChangeScene(SCENE_ID::TITLE);
	}
}

void CUiGameClear::Draw(void)
{
	if(DrawFlag)
	m_UiSprite.Draw();
}

void CUiGameClear::Finalize(void)
{
	m_UiSprite.Delete();
}
