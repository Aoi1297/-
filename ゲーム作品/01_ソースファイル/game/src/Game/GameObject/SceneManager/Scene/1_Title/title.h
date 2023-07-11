#pragma once

#include "aqua.h"

#include "../../scene_manager.h"

// パーティクルデータ構造体
struct PARTICLE_DATA
{
	aqua::CVector2	position;	// パーティクル位置
	aqua::CVector2	scale;		// サイズ
	float			angle;		// 角度
};

class CTitle : public IScene
{
public:	// 公開メンバ関数

	// コンストラクタ
	CTitle			(IGameObject* parent);

	// デストラクタ
	~CTitle			(void) = default;

	// 初期化関数
	void Initialize	(void)	override;

	// 更新関数
	void Update		(void)	override;

	// 描画関数
	void Draw		(void)	override;

	// 解放関数
	void Finalize	(void)	override;

private: // 非公開メンバ関数

	// キーチェック関数
	void CheckKeyZ		(void);

	// タイマー更新
	void TimerUpdate	(void);

	// パーティクル移動
	void ParticleMove	(void);

private: // 非公開メンバ変数

	// スプライト変数
	aqua::CSprite				m_ParticleSprite;			// !< パーティクル画像
	aqua::CSprite				m_ParticleEffectSprite;		// !< パーティクルエフェクト画像
	aqua::CSprite				m_TitleSprite;				// !< タイトル画像
	aqua::CSprite				m_TitleEffectSprite;		// !< タイトルエフェクト画像
	aqua::CSprite				m_TitleMassageSprite;		// !< タイトルメッセージ画像
	aqua::CSprite				m_TitleMassageEffectSprite;	// !< タイトルメッセージエフェクト画像
	aqua::CSprite				m_FlashScreenSprite;		// !< 画面フラッシュ画像

	// タイマー変数
	aqua::CTimer				m_FlashScreenTimer;			// !< 画面フラッシュタイマー
	aqua::CTimer				m_FlashObjectTimer;			// !< オブジェクトフラッシュタイマー

	// ポインタ変数
	CSceneManager*				m_SceneManager_P;			// !< シーンマネージャークラスポインタ

	std::vector<PARTICLE_DATA>	m_ParticleDataList;			// !< パーティクルデータ構造体リスト

private: // 静的メンバ定数

	static const unsigned char	m_max_random_color;			// !< カラー最大ランダム値
	static const int			m_pixel_width;				// !< ぼかし幅（１００で１ピクセル）
	static const int			m_param;					// !< ぼかしの強さ
	static const aqua::CVector2 m_title_scale;				// !< タイトルサイズ
	static const float			m_title_position_y;			// !< タイトル位置（Y座標）
	static const float			m_title_massage_position_y;	// !< タイトルメッセージ（Y座標）
	static const float			m_title_massage_scale_up;	// !< タイトルメッセージ拡大量
	static const int			m_particle_quantity;		// !< パーティクル量
	static const int			m_particle_random_scale_max;// !< パーティクル最大サイズ
	static const int			m_particle_random_angle_max;// !< パーティクル最大角度
	static const float			m_flash_screen_time;		// !< 画面フラッシュ時間
	static const float			m_flash_object_time;		// !< オブジェクトフラッシュ間隔
};