#pragma once

#include "../effect.h"

// 前方宣言
class CPlayer;
class CBulletManager;

class CDarkness : public IEffect
{
public: // 公開メンバ関数

	// コンストラクタ
	CDarkness		(IGameObject* parent);

	// デストラクタ
	~CDarkness		(void) = default;

	// 初期化関数
	void Initialize	(void)	override;

	// 更新関数
	void Update		(void)	override;

	// 描画関数
	void Draw		(void)	override;

	// 解放関数
	void Finalize	(void)	override;

private: // 非公開メンバ変数

	// 暗闇エリア用サーフェイス
	aqua::CSurface m_DarknessArea;

	// サーフェイス用スプライト
	aqua::CSprite m_SurfaceSprite;

	// 光源スプライト
	aqua::CSprite m_LightSprite;

	// 暗闇スプライト
	aqua::CSprite m_DarknessSprite;

	// フラッシュスプライト
	aqua::CSprite m_FlashSprite;

	// フラッシュフラグ
	bool m_FlashFlag;
	
	// 暗闇フラグ
	bool m_DarknessFlag;

	// フラッシュタイマー
	aqua::CTimer m_FlashTimer;

	// 暗闇タイマー
	aqua::CTimer m_DarknessTimer;

	// プレイヤークラスオブジェクトのポインタ変数
	CPlayer* m_Player_P;

private: // 非公開メンバ定数
	
	static const aqua::CVector2 m_light_brightness;				// !< ライトの明るさ
	static const aqua::CVector2 m_light_brightness_for_enemy;	// !< ライトの明るさ
	static const float m_darkness_time;							// !< 暗闇時間
	static const float m_darkness_time_for_enemy;				// !< 暗闇時間
	static const float m_flash_time;							// !< フラッシュ時間
};