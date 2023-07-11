#pragma once

#include "aqua.h"

#include "../../ItemManager/item_manager.h"

// 前方宣言
class CPlayer;

class IItem : public aqua::IGameObject
{
public: // 公開メンバ関数

	// コンストラクタ
	IItem(IGameObject* parent, const std::string& object_name);

	// デストラクタ
	~IItem								(void)	override = default;

	// アイテムスプライト設定
	void			CreateSprite		(const std::string& sprite_file_name);

	// ステータス設定
	void			SetStatus			(const ITEM_ID& id, const aqua::CVector2& create_pos);

	// 更新関数
	void			Update				(void)	override;

	// 描画関数
	void			Draw				(void)	override;

	// 解放関数
	void			Finalize			(void)	override;

	// アイテムを取得
	void			HitItem				(void);

	// アイテムの中心位置取得
	aqua::CVector2	GetCenterPosition	(void);

private: // 非公開メンバ関数

	void			TimerUpdate			(void);

	void			SpawanEffect		(void);

	void			Movement			(void);

private: // 非公開メンバ変数

	// プレイヤークラスポインタの取得
	CPlayer* m_Player_P;

	// アイテムスプライト
	aqua::CSprite m_ItemSprite;

	// 出現時のイージングタイマー
	aqua::CTimer m_EasingTimer;

	// 自身のアイテムID
	ITEM_ID	m_ItemId;

	// 自身（アイテム）の位置
	aqua::CVector2 m_Position;

	// 自身（アイテム）の移動速度
	float m_MoveSpeed;

private: // 非公開メンバ定数

	static const float m_item_move_speed;	// !< アイテムの初期移動速度
	static const float m_item_acceleration;	// !< アイテムの加速度
	static const float m_easing_timer;		// !< イージング時間
	static const float m_item_max_scale;	// !< アイテム画像の最大スケール
	static const float m_item_scale;		// !< アイテム画像のスケール
};