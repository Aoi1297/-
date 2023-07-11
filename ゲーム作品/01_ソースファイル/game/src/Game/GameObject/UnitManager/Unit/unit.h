#pragma once

#include "aqua.h"

// 前方宣言
class		IBullet;
class		IItem;
class		CGameMain;
class		CUiManager;
class		CPlayer;
class		CEffectManager;
class		CCameraManager;
class		CBulletManager;
class		CUIScore;
class		CItemManager;
class       CSoundCreater;
enum class	UNIT_ID;
enum class	CATEGORY_ID;
enum class  BULLET_ID;

class IUnit : public aqua::IGameObject
{
public: // 公開メンバ関数

	// コンストラクタ
	IUnit								(IGameObject* parent, const std::string& object_name);

	// デストラクタ
	~IUnit								(void)	override = default;

	// 画像設定
	void			CreateSprite		(const std::string& sprite_file_name);

	// ステータス設定
	void			SetStatus			(const UNIT_ID& unit_id, const CATEGORY_ID& unit_category_id, const aqua::CVector2& create_pos);

	// 描画関数
	virtual void	Draw				(void);

	// 解放関数
	virtual void	Finalize			(void);

	// 弾とユニットの当たり判定
	void			CheckHitBullet		(IBullet* bullet);

	// ユニットとアイテムの当たり判定
	void			CheckHitItem		(IItem* item);

	// ユニットの中心位置の取得
	aqua::CVector2	GetCenterPosition	(void);

	// ユニットのカテゴリーの取得
	CATEGORY_ID		GetCategory			(void);

	// ユニット画像の横幅
	float			GetSpriteWidth		(void);

	//　ユニットの当たり半径取得 
	virtual float	GetRadius			(void) = 0;

	// プレイヤーのポインタを取得
	void			SetPlayerPointer	(void);

protected: // 限定公開メンバ変数

	// ユニットスプライト
	aqua::CSprite	m_UnitSprite;

	// ユニット位置
	aqua::CVector2	m_Position;

	// ユニットのライフ
	int m_LifePoint;

	// ユニットの移動速度
	float m_MoveSpeed;

	// ユニットの弾発射速度
	float m_ShotSpeed;

	// 撃つ弾の種類
	BULLET_ID m_ShotKind;

	// ユニットのID
	UNIT_ID m_UnitId;

	// ユニットの敵味方識別子
	CATEGORY_ID m_UnitCategory;

	// クラスポインタ変数
	CGameMain*		m_GameMain_P;		// !< ゲームメインクラス
	CUiManager*		m_UiManager_P;		// !< ユニットマネージャークラス
	CPlayer*		m_Player_P;			// !< プレイヤークラス
	CEffectManager* m_EffectManager_P;	// !< エフェクトマネージャークラス
	CCameraManager* m_CameraManager_P;	// !< カメラマネージャークラス
	CUIScore*		m_Score_P;			// !< スコアクラス
	CItemManager*	m_ItemManager_P;	// !< アイテムマネージャークラス
	CBulletManager* m_BulletManager_P;	// !< バレットマネージャークラスポインタの取得
	CSoundCreater*  m_SoundManager_P;	// !< サウンドマネージャークラスポインタの取得

private: // 非公開メンバ定数

	static const int m_get_item_score;	// !< アイテム取得時の獲得スコア
	static const int m_defeat_score;	// !< 敵撃破時の獲得スコア
	static const float m_item_hit_radius;	// !< アイテムとの当たり判定
};