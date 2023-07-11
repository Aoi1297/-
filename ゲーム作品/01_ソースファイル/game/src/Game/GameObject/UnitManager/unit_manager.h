#pragma once

#include "aqua.h"

// 前方宣言
class IBullet;
class IItem;
class IUnit;
class CGameMain;
class CSoundCreater;

// ユニットのID
enum class UNIT_ID
{
	PLAYER,				// プレイヤー（操作する機体）
	NORMAL,				// 頻繁に登場する敵
	FIRE_WORK,			// 花火のような弾を放つ敵
	STAR,				// 星形の自機狙い弾を放つ敵
	MINI_BOSS,			// 中ボス
	NORMAL_TOUGH,		// NORMLの強い版
	FIRE_WORK_TOUGH,	// FIRE_WORKの強い版
	FINAL_BOSS,			// ラスボス

	MAX,				// ユニット数
};

// ユニットのカテゴリーID
enum class CATEGORY_ID
{
	PLAYER,	// プレイヤー
	ENEMY,	// 敵ユニット
	BOSS,	// ボスユニット

	MAX,	// カテゴリー数
};

// CSVファイルから取得する敵データ
struct ENEMY_DATA
{
	UNIT_ID			unit_id;	 // ユニットID
	aqua::CVector2	position;	 // 生成位置
	float			create_time; // 生成時間
};

class CUnitManager : public aqua::IGameObject
{
public:	// 公開メンバ関数

	// コンストラクタ
	CUnitManager	(IGameObject* parent);

	// デストラクタ
	~CUnitManager	(void) = default;

	// 初期化関数
	void Initialize	(void)	override;

	// 更新関数
	void Update		(void)	override;

	// 描画関数
	void Draw		(void)	override;

	// 解放関数
	void Finalize	(void)	override;

public: // 非公開メンバ関数

	// 敵ユニット生成関数
	void CreateUnit		(const UNIT_ID& unit_id, const aqua::CVector2& create_position);

	// ユニットの判定確認
	void CheckUnit		(IBullet* bullet);

	// プレイヤーとアイテムの判定確認
	void CheckUnit		(IItem* item);

	// 引数に与えられた弾から一番近い敵ユニットを探す
	IUnit* FindNearUnit	(IBullet* bullet);

private: // 非公開メンバ関数

	// CSVファイル解析
	void Parse			(const std::string& csv_file_name);

	// 敵配備
	void DeployEnemy	(void);

private: // 非公開メンバ変数

	// CSV敵データ構造体
	std::vector<ENEMY_DATA> m_EnemyTable;

	// ゲームメインクラスポインタ
	CGameMain*				m_GameMain_P;

	// サウンドクラスポインタ
	CSoundCreater*			m_SoundManager_P;
};