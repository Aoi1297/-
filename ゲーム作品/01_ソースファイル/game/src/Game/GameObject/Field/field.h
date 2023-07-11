#pragma once

#include "aqua.h"

// 前方宣言
class CPlayer;

class CField : public aqua::IGameObject
{
public: // 公開メンバ関数

	// コンストラクタ
	CField			(IGameObject* parent);

	// デストラクタ
	~CField			(void) = default;

	// 初期化関数
	void Initialize	(void)	override;

	// 更新関数
	void Update		(void)	override;

	// 描画関数
	void Draw		(void)	override;

	// 解放関数
	void Finalize	(void)	override;

private: // 非公開メンバ関数

	// タイマー更新
	void TimerUpdate	(void);

	// 背景移動量計算
	void MoveCalculation(void);

	// 背景移動処理
	void MoveBackGround	(void);

private: // 非公開メンバ変数

	// スプライト画像
	aqua::CSprite	m_BackGroundSprite;			// !< 動かない背景
	aqua::CSprite	m_BackGroundMoveSprite;		// !< 動く背景１枚目
	aqua::CSprite	m_BackGroundMoveNextSprite;	// !< 動く背景２枚目

	// タイマー変数
	aqua::CTimer	m_MiniBossSpawnTimer;		// !< 中ボスが出現する時間

	// ポインタ変数
	CPlayer* m_Player_P;

	float m_BackGroundSpeed;

	float m_BackGroundSpeedPlus;

	bool m_MiniBossFlag;
	
private: // 非公開メンバ定数

	static const int m_pixel_width;	// !< ぼかし幅（１００で１ピクセル）
	static const int m_param;		// !< ぼかしの強さ
	static const float m_mini_boss_spawn_time;
	static const float m_back_ground_speed_normal;
	static const float m_back_ground_speed_laser;
	static const float m_back_ground_speed_headmode;
};