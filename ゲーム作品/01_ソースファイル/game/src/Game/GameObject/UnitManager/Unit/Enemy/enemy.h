#pragma once

#include "../unit.h"

class IEnemy : public IUnit
{
public: // 公開メンバ関数

	// コンストラクタ
	IEnemy			(IGameObject* parent, const std::string& object_name);

	// デストラクタ
	~IEnemy			(void)	override = default;

	// タイマー更新
	void TimerUpdate(void);

protected: // 限定公開メンバ関数

	// 出現時演出処理
	virtual void SpawanEffect(void) = 0;

	// 行動処理
	virtual void Movement(void) = 0;

	// 敵射撃処理
	virtual void Fire(void) = 0;

protected: // 限定公開メンバ変数

	aqua::CTimer m_FireTimer;

	aqua::CTimer m_EasingTimer;
};