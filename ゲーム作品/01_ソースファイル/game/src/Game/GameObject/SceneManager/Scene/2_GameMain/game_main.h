#pragma once

#include "../scene.h"

class CGameMain : public IScene
{
public: // 公開仮想関数

	// コンストラクタ
	CGameMain		(IGameObject* parent);

	// デストラクタ
	~CGameMain		(void) = default;

	// 初期化関数
	void Initialize	(void)	override;

	// 更新関数
	void Update		(void)	override;

	// 描画関数
	void Draw		(void)	override;

	// 解放関数
	void Finalize	(void)	override;

public: // 公開関数

	// ゲーム経過時間取得
	inline float	GetGameTime		(void)	{ return m_GameTimer.GetTime(); }

	// ゲームオーバーセット
	inline void		SetGameOverFlag	(void)	{ m_GameOverFlag = true; }

	// ゲームオーバーフラグ取得
	inline bool		GetGameOverFlag	(void)	{ return m_GameOverFlag; }

private: // 非公開メンバ変数

	// タイマー変数
	aqua::CTimer	m_GameTimer;	// !< ゲーム経過時間

	// ゲームオーバーフラグ
	bool			m_GameOverFlag;	// !< ゲームオーバーフラグ

private: // 非公開メンバ定数

	static const aqua::CVector2 m_player_position;	// !< プレイヤーの初期位置
	static const float			m_game_time_set;	// !< ゲーム経過時間上限設定
};