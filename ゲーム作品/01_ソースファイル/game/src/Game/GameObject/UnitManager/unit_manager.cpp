#include "unit_manager.h"

#include "../BulletManager/Bullet/bullet.h"
#include "../ItemManager/Item/item.h"
#include "../UnitManager/Unit/unit.h"
#include "../SoundManager/sound_creater.h"
#include "../SceneManager/Scene/2_GameMain/game_main.h"

#include "../UnitManager/Unit/Player/player.h"
#include "../UnitManager/Unit/Enemy/Normal/normal.h"
#include "../UnitManager/Unit/Enemy/FireWork/fire_work.h"
#include "../UnitManager/Unit/Enemy/Star/star.h"
#include "../UnitManager/Unit/Enemy/MiniBoss/mini_boss.h"
#include "../UnitManager/Unit/Enemy/NormalTough/normal_tough.h"
#include "../UnitManager/Unit/Enemy/FireWorkTough/fire_work_tough.h"
#include "../UnitManager/Unit/Enemy/FinalBoss/final_boss.h"
#include "../UnitManager/Unit/unit.h"

CUnitManager::CUnitManager(IGameObject* parent)
	// parent(CGameMain)
	: IGameObject(parent, "UnitManager")
	, m_GameMain_P(nullptr)
{
}

void CUnitManager::Initialize(void)
{
	// ゲームメインシーンクラスのポインタを取得
	m_GameMain_P = ((CGameMain*)aqua::FindGameObject("GameMain"));

	// サウンドクラスポインタを取得
	m_SoundManager_P = ((CSoundCreater*)aqua::FindGameObject("SoundManager"));

	// エネミーテーブルの解析
	Parse("data/csv/enemy_table.csv");
}

void CUnitManager::Update(void)
{
	// NULLチェック
	if (!m_GameMain_P) return;

	// ゲームオーバーなら処理をしない
	if (m_GameMain_P->GetGameOverFlag()) return;

	// エネミーテーブルを元に敵を配備する
	DeployEnemy();

	// 生成したユニットの更新を行う
	IGameObject::Update();
}

void CUnitManager::Draw(void)
{
	// NULLチェック
	if (!m_GameMain_P) return;

	// ゲームオーバーなら処理をしない
	if (m_GameMain_P->GetGameOverFlag()) return;

	// 生成したユニットの描画を行う
	IGameObject::Draw();
}

void CUnitManager::Finalize(void)
{
	// 生成したユニットの解放を行う
	IGameObject::Finalize();
}

void CUnitManager::Parse(const std::string& csv_file_name)
{
	// CSVローダー生成
	aqua::CCSVLoader csv_loader;

	// SCVファイルの読み込み
	csv_loader.Load(csv_file_name);

	// 縦のセル数だけ繰り返す
	for (int i = 0; i < csv_loader.GetRows(); ++i)
	{
		// 敵 構造体を生成
		ENEMY_DATA enemy_data;

		// エネミーIDを取得
		enemy_data.unit_id = (UNIT_ID)csv_loader.GetInteger(i, 0);

		// 配備位置を取得
		{
			// X座標
			enemy_data.position.x = csv_loader.GetFloat(i, 1);

			// Y座標
			enemy_data.position.y = csv_loader.GetFloat(i, 2);
		}

		// 生成時間（ゲーム開始から何秒後なのか）を取得
		enemy_data.create_time = csv_loader.GetFloat(i, 3);

		// 敵１体の情報として配列に格納
		m_EnemyTable.push_back(enemy_data);
	}

	// SCVファイルの解放
	csv_loader.Unload();
}

void CUnitManager::DeployEnemy()
{
	// エネミーテーブルが空なら処理をしない
	if (!m_EnemyTable.empty())
	{
		// 指定出現時間がゲーム経過時間を超えていたら出現させる
		if (m_EnemyTable[0].create_time < m_GameMain_P->GetGameTime())
		{
			// ユニット（敵）を生成
			CreateUnit(m_EnemyTable[0].unit_id, m_EnemyTable[0].position);

			// 生成したらデータから除外する
			m_EnemyTable.erase(m_EnemyTable.begin());
		}
	}
}

void CUnitManager::CreateUnit(const UNIT_ID& unit_id, const aqua::CVector2& create_position)
{
	// ユニットを作成
	IUnit* unit = nullptr;

	// カテゴリーの作成
	CATEGORY_ID category = CATEGORY_ID::MAX;

	// 生成したいIDを確認してそのIDと一致するユニットを生成する
	switch (unit_id)
		{
		case UNIT_ID::PLAYER:
		{
			unit = aqua::CreateGameObject<CPlayer>(this);
			category = CATEGORY_ID::PLAYER;
		}break;

		case UNIT_ID::NORMAL:
		{
			unit = aqua::CreateGameObject<CNormal>(this);
			category = CATEGORY_ID::ENEMY;
		}break;

		case UNIT_ID::FIRE_WORK:
		{
			unit = aqua::CreateGameObject<CFireWork>(this);
			category = CATEGORY_ID::ENEMY;
		}break;

		case UNIT_ID::STAR:
		{
			unit = aqua::CreateGameObject<CStar>(this);
			category = CATEGORY_ID::ENEMY;
		}break;

		case UNIT_ID::MINI_BOSS:
		{
			unit = aqua::CreateGameObject<CMiniBoss>(this);
			category = CATEGORY_ID::ENEMY;
		}break;

		case UNIT_ID::FIRE_WORK_TOUGH:
		{
			unit = aqua::CreateGameObject<CFireWorkTough>(this);
			category = CATEGORY_ID::ENEMY;
		}break;

		case UNIT_ID::FINAL_BOSS:
		{
			unit = aqua::CreateGameObject<CFinalBoss>(this);
			category = CATEGORY_ID::BOSS;
		}break;

		case UNIT_ID::NORMAL_TOUGH:
		{
			unit = aqua::CreateGameObject<CNormalTough>(this);
			category = CATEGORY_ID::ENEMY;
		}break;
	}

	// NULLチェック
	if (!unit) return;
	
	// 効果音を鳴らす
	((CSoundCreater*)aqua::FindGameObject("SoundManager"))->Play(SOUND_ID::EFFECT_SPAWN);

	// 生成したユニットだけの初期化を行う
	unit->SetStatus(unit_id, category, create_position);
}

void CUnitManager::CheckUnit(IBullet* bullet)
{
	// ユニットリストが空なら当たり判定チェックを行わない
	if (GetChildList()->empty()) return;

	// 生成したユニット全てに以下の処理を順々に行う
	for (auto it = GetChildList()->begin(); it != GetChildList()->end(); ++it)
	{
		// リストデータをunitに格納する
		IUnit* unit = (IUnit*)*it;

		// ユニットが画面外へ行ったなら削除する(画像が見えなくなったら消すように調整もする）
		if (unit->GetCenterPosition().x < 0 - unit->GetSpriteWidth() / 2)
		{
			// 画面外へ行ったユニットの削除を行う
			unit->DeleteObject();
		}

		// 画面内にいるユニットの弾との当たり判定をチェックする
		unit->CheckHitBullet(bullet);
	}
}

void CUnitManager::CheckUnit(IItem* item)
{
	// ユニットリストが空なら当たり判定チェックを行わない
	if (GetChildList()->empty()) return;

	// 生成したユニット全てに以下の処理を順々に行う
	for (auto it = GetChildList()->begin(); it != GetChildList()->end(); ++it)
	{
		// リストデータをunitに格納する
		IUnit* unit = (IUnit*)*it;

		// アイテムとユニットとの衝突判定
		unit->CheckHitItem(item);
	}
}

IUnit* CUnitManager::FindNearUnit(IBullet* bullet)
{
	// ユニットリストが空の場合は処理をしない
	if (GetChildList()->empty()) return nullptr;

	// 初期最小値設定
	float min = 99999.0f;

	// 近くのユニットのポインタを格納する変数
	IUnit* near_unit = nullptr;

	// 生成したユニットリストから一番近いユニットを調べる
	for (auto it = GetChildList()->begin(); it != GetChildList()->end(); ++it)
	{
		IUnit* unit = (IUnit*)*it;

		// プレイヤー以外のカテゴリーに対してのみ処理を行う
		if (!(unit->GetCategory() == CATEGORY_ID::PLAYER))
		{
			// ユニットの位置と弾の位置を引いたベクトルを求める
			aqua::CVector2 direction = unit->GetCenterPosition() - bullet->GetCenterPosition();

			// そのベクトルの距離がリストの中から一番短ければ更新する
			if (direction.Length() <= min)
			{
				// 最短距離更新
				min = direction.Length();

				// 一番近いユニットのポインタを取得
				near_unit = unit;
			}
		}
	}

	// 求めた一番近いユニットのポインタを返す
	return near_unit;
}