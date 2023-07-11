#pragma once

#include "aqua.h"

class CCameraManager :public aqua::IGameObject
{
public: // 公開メンバ関数

	// コンストラクタ
	CCameraManager(aqua::IGameObject* parent);

	// デストラクタ
	~CCameraManager(void) = default;

	// 初期化関数
	void Initialize(void) override;

	// デストラクタ
	void Update(void) override;

	// 画面振動
	void Shake(void);

	// 振動値取得
	aqua::CVector2 GetPosition(void) const { return m_Position; }

private: // 非公開メンバ関数

	// 振動値保存変数
	aqua::CVector2	m_Position;

	// 画面振動タイマー
	aqua::CTimer	m_ShakeTimer;

	// 振動フラグ（ONの間振動値に変化が起き続ける）
	bool			m_ShakeFlag;

private: // 非公開メンバ定数
	static const float m_shake_time; // !< 画面振動時間
};