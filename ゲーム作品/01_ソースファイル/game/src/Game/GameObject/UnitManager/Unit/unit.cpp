#include "unit.h"

#include "../../UnitManager/unit_manager.h"
#include "../../BulletManager/Bullet/bullet.h"
#include "../../ItemManager/Item/item.h"
#include "../../SceneManager/Scene/2_GameMain/game_main.h"
#include "../../InterfaceManager/ui_manager.h"
#include "../../UnitManager/Unit/Player/player.h"
#include "../../EffectManager/effect_manager.h"
#include "../../CameraManager/camera_manager.h"
#include "../../InterfaceManager/UI/Score/score.h"
#include "../../ItemManager/item_manager.h"
#include "../../BulletManager/bullet_manager.h"
#include "../../SoundManager/sound_creater.h"

const int IUnit::m_get_item_score		= 3000;
const int IUnit::m_defeat_score			= 1000;
const float IUnit::m_item_hit_radius	= 30.0f;

IUnit::IUnit(IGameObject* parent, const std::string& object_name)
	// parent(CGameMain)
	: IGameObject		(parent, object_name)
	, m_LifePoint		(0)
	, m_MoveSpeed		(0.0f)
	, m_GameMain_P		(nullptr)
	, m_UiManager_P		(nullptr)
	, m_Player_P		(nullptr)
	, m_EffectManager_P	(nullptr)
	, m_CameraManager_P	(nullptr)
	, m_Score_P			(nullptr)
	, m_ItemManager_P	(nullptr)
	, m_SoundManager_P	(nullptr)
{
	// ゲームメインシーンクラスポインタの取得
	m_GameMain_P = ((CGameMain*)aqua::FindGameObject("GameMain"));

	// UIマネージャークラスポインタの取得
	m_UiManager_P = ((CUiManager*)aqua::FindGameObject("UIManager"));

	// エフェクトマネージャークラスポインタの取得
	m_EffectManager_P = ((CEffectManager*)aqua::FindGameObject("EffectManager"));

	// カメラマネージャークラスポインタの取得
	m_CameraManager_P = ((CCameraManager*)aqua::FindGameObject("CameraManager"));

	// スコアクラスポインタの取得
	m_Score_P = ((CUIScore*)aqua::FindGameObject("UIScore"));

	// アイテムマネージャークラスポインタの取得
	m_ItemManager_P = ((CItemManager*)aqua::FindGameObject("ItemManager"));

	// バレットマネージャークラスポインタの取得
	m_BulletManager_P = ((CBulletManager*)aqua::FindGameObject("BulletManager"));

	// サウンドマネージャクラスポインタの取得
	m_SoundManager_P = ((CSoundCreater*)aqua::FindGameObject("SoundManager"));
}

void IUnit::CreateSprite(const std::string& sprite_file_name)
{
	// 画像の読み込み
	m_UnitSprite.Create(sprite_file_name);

	// 回転の基準点を画像の中心に設定
	m_UnitSprite.anchor = { (float)m_UnitSprite.GetTextureWidth() / 2,(float)m_UnitSprite.GetTextureHeight() / 2 };
}

void IUnit::SetStatus(const UNIT_ID& unit_id, const CATEGORY_ID& unit_category_id, const aqua::CVector2& create_pos)
{
	// ユニットID設定
	m_UnitId = unit_id;

	// カテゴリー設定
	m_UnitCategory = unit_category_id;

	// 配備位置設定
	m_UnitSprite.position = m_Position = create_pos;

	// 初期化関数を呼び出す
	Initialize();
}

void IUnit::Draw(void)
{
	// ユニットスプライトの描画
	m_UnitSprite.Draw();
}

void IUnit::Finalize()
{
	// ユニットスプライトのメモリ解放
	m_UnitSprite.Delete();
}

void IUnit::CheckHitBullet(IBullet* bullet)
{
	aqua::CVector2 vector = GetCenterPosition() - bullet->GetCenterPosition();

	// プレイヤーと敵の弾との当たり判定
	if (
		// カテゴリーがプレイヤー　かつ
		m_UnitCategory == CATEGORY_ID::PLAYER &&

		// 弾のカテゴリーが敵　または　ボス　かつ
		(bullet->GetCategory() == CATEGORY_ID::ENEMY ||
			bullet->GetCategory() == CATEGORY_ID::BOSS) &&

		// それらの距離がプレイヤーの当たり半径以下の距離になったとき
		vector.Length() <= GetRadius())
	{
		// プレイヤーのライフを１減らし、０以下であった場合ゲームオーバー
		if (--m_LifePoint <= 0)
		{
			// ゲームオーバー
			m_GameMain_P->SetGameOverFlag();

			// ゲームオーバーメッセージを表示する
			m_UiManager_P->CreateUI(UI_ID::GAMEOVER);

			// プレイヤークラスオブジェクトを削除
			IGameObject::DeleteObject();
		}

		// プレイヤーのライフが０以下ではない（死んでいない場合）かつ　視界不良状態ではない場合
		else if (!(m_LifePoint <= 0) && m_Player_P->GetDarknessFlag() == false)
		{
			// 効果音を鳴らす
			((CSoundCreater*)aqua::FindGameObject("SoundManager"))->Play(SOUND_ID::EFFECT_ALERT);

			// 視界不良状態にセットする
			m_Player_P->SetDarknessFlag();

			// 視界不良エフェクトを生成
			m_EffectManager_P->CreateEffect(EFFECT_ID::DARKNESS, GetCenterPosition(), m_UnitCategory);

			// ダメージエフェクトを生成
			m_EffectManager_P->CreateEffect(EFFECT_ID::DAMAGE, aqua::CVector2::ZERO, m_UnitCategory);
		}

		// 弾に当たった場合はライフに関係なく画面を揺らす処理を行う
		m_CameraManager_P->Shake();

		// 弾がプレイヤーに衝突したら弾を削除する
		bullet->DeleteObject();
	}

	// 敵またはボスとプレイヤーの弾との当たり判定
	if (
		// カテゴリーが敵　または　カテゴリーがボス　かつ
		(m_UnitCategory == CATEGORY_ID::ENEMY ||
			m_UnitCategory == CATEGORY_ID::BOSS) &&

		// 弾のカテゴリーがプレイヤーの場合　かつ
		bullet->GetCategory() == CATEGORY_ID::PLAYER &&

		// それらの距離がプレイヤーの当たり半径以下の距離になったとき
		vector.Length() <= GetRadius())
	{
		// 敵のライフを１減らし、０以下であった場合
		if (--m_LifePoint == 0)
		{
			// 敵撃破時の獲得スコア
			m_Score_P->AddScore(m_defeat_score * (int)m_UnitId);

			// 敵撃破エフェクトを生成
			m_EffectManager_P->CreateEffect(EFFECT_ID::DEAD_ENEMY, GetCenterPosition(), m_UnitCategory);

			// 画面を振動させる
			m_CameraManager_P->Shake();

			// 敵オブジェクトクラス削除
			IGameObject::DeleteObject();

			if (m_UnitCategory == CATEGORY_ID::BOSS)
			{
				m_EffectManager_P->CreateEffect(EFFECT_ID::DAMAGE, aqua::CVector2::ZERO, CATEGORY_ID::ENEMY);
				m_UiManager_P->CreateUI(UI_ID::GAMECLEAR);
			}
	
			// 撃破時アイテムランダム生成
			m_ItemManager_P->CreateItem((ITEM_ID)aqua::Rand((int)ITEM_ID::MAX - 1), GetCenterPosition());
		}

		// 衝突時弾消滅
		bullet->DeleteObject();

		// 衝突時衝突エフェクト生成
		m_EffectManager_P->CreateEffect(EFFECT_ID::RIPPLES, bullet->GetCenterPosition(), m_UnitCategory);
	}
}

void IUnit::CheckHitItem(IItem* item)
{
	// ユニットとアイテムの距離
	aqua::CVector2 vector = GetCenterPosition() - item->GetCenterPosition();

	// ユニットの当たり半径以下の距離になったら
	if (vector.Length() <= m_item_hit_radius)
	{
		// アイテム獲得スコア
		m_Score_P->AddScore(m_get_item_score);

		// アイテム取得エフェクトを生成
		m_EffectManager_P->CreateEffect(EFFECT_ID::GETITEM, m_Position, m_UnitCategory);

		// アイテム取得
		item->HitItem();

		// 画面を振動させる
		m_CameraManager_P->Shake();
	}
}

aqua::CVector2 IUnit::GetCenterPosition()
{
	return { m_Position.x + (float)m_UnitSprite.GetTextureWidth() / 2,m_Position.y + (float)m_UnitSprite.GetTextureHeight() / 2 };
}

CATEGORY_ID IUnit::GetCategory()
{
	return m_UnitCategory;
}

float IUnit::GetSpriteWidth()
{
	return m_UnitSprite.GetTextureWidth();
}

void IUnit::SetPlayerPointer(void)
{
	// プレイヤークラスポインタの取得
	m_Player_P = ((CPlayer*)aqua::FindGameObject("Player"));
}
