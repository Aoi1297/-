#include "camera_manager.h"

const float CCameraManager::m_shake_time = 0.2f;

CCameraManager::CCameraManager(aqua::IGameObject* parent)
	// parent(CGameMain)
	: aqua::IGameObject(parent, "CameraManager")
	, m_ShakeFlag(false)
{
}

void CCameraManager::Initialize(void)
{
	// 振動値の初期化
	m_Position = aqua::CVector2::ZERO;

	// 振動時間を設定
	m_ShakeTimer.Setup(m_shake_time);

	// 振動初期フラグをOFFに設定
	m_ShakeFlag = false;
}

void CCameraManager::Update(void)
{
	// Shakeが呼ばれたら以下の処理をする
	if (!m_ShakeFlag) return;

	// X軸の揺らす値をランダムで求める
	m_Position.x = (float)aqua::Rand(10, 1) * (aqua::Rand(1) ? 5.0f : -5.0f);
	// Y軸の揺らす値をランダムで求める
	m_Position.y = (float)aqua::Rand(10, 1) * (aqua::Rand(1) ? 5.0f : -5.0f);

	// 画面振動タイマーを開始
	m_ShakeTimer.Update();

	// タイマー終了時
	if (m_ShakeTimer.Finished())
	{
		// タイマーのリセット（経過時間を０にする）
		m_ShakeTimer.Reset();

		// 振動値を０にする
		m_Position = aqua::CVector2::ZERO;

		// 画面振動停止
		m_ShakeFlag = false;
	}
}

void CCameraManager::Shake(void)
{
	// 画面振動開始
	m_ShakeFlag = true;
}