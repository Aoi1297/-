#include "game_main.h"

#include "../../../Field/field.h"
#include "../../../UnitManager/unit_manager.h"
#include "../../../ItemManager/item_manager.h"
#include "../../../BulletManager/bullet_manager.h"
#include "../../../EffectManager/effect_manager.h"
#include "../../../InterfaceManager/ui_manager.h"
#include "../../../CameraManager/camera_manager.h"
#include "../../../SoundManager/sound_creater.h"

const aqua::CVector2 CGameMain::m_player_position	= { (float)aqua::GetWindowWidth() / 2,(float)aqua::GetWindowHeight() / 2 };
const float			 CGameMain::m_game_time_set		= 250.0f;

CGameMain::CGameMain(IGameObject* parent)
	// parent(CSceneManager)
	: IScene(parent, "GameMain")
	, m_GameOverFlag(false)
{
}

void CGameMain::Initialize(void)
{
	// タイトルBGMの再生を停止
	((CSoundCreater*)aqua::FindGameObject("SoundManager"))->Stop(SOUND_ID::BGM_TITLE);

	// ゲームBGMを再生
	((CSoundCreater*)aqua::FindGameObject("SoundManager"))->Play(SOUND_ID::BGM_GAME);

	// 背景クラスオブジェクトの生成
	aqua::CreateGameObject<CField>(this);

	// ユニットマネージャークラスオブジェクトの生成
	CUnitManager* unit_manager = aqua::CreateGameObject<CUnitManager>(this);

	// アイテムマネージャークラスオブジェクトの生成
	aqua::CreateGameObject<CItemManager>(this);

	// 弾マネージャークラスオブジェクトの生成
	aqua::CreateGameObject<CBulletManager>(this);

	// エフェクトマネージャークラスオブジェクトの生成
	aqua::CreateGameObject<CEffectManager>(this);

	// UIマネージャークラスオブジェクトの生成
	CUiManager* ui_manager = aqua::CreateGameObject<CUiManager>(this);

	// カメラマネージャークラスオブジェクトの生成
	aqua::CreateGameObject<CCameraManager>(this);

	// UI（フレーム）を作成
	ui_manager->CreateUI(UI_ID::FRAME);

	// UI（スコア）を作成
	ui_manager->CreateUI(UI_ID::SCORE);

	// 操作するプレイヤーを作成
	unit_manager->CreateUnit(UNIT_ID::PLAYER, { m_player_position });

	// ゲーム経過時間設定
	m_GameTimer.Setup(m_game_time_set);

	// 生成したクラスオブジェクトの初期化を行う
	IGameObject::Initialize();
}

void CGameMain::Update(void)
{
	// ゲームタイマーの計測を行う
	m_GameTimer.Update();

	// 生成したクラスオブジェクトの更新処理を行う
	IGameObject::Update();
}

void CGameMain::Draw(void)
{
	// 生成したクラスオブジェクトの描画処理を行う
	IGameObject::Draw();
}

void CGameMain::Finalize(void)
{
	// 生成したクラスオブジェクトの解放処理を行う
	IGameObject::Finalize();
}