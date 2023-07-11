#include "enemy.h"

#include "../Player/player.h"

IEnemy::IEnemy(IGameObject* parent, const std::string& object_name)
	: IUnit(parent, object_name)
{
}

void IEnemy::TimerUpdate(void)
{
	// 弾発射タイマー起動
	m_FireTimer.Update();

	// 終了していないならイージングタイマー起動
	if (!m_EasingTimer.Finished()) m_EasingTimer.Update();
}
