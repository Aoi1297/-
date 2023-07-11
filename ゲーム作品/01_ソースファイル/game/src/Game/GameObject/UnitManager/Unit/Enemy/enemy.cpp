#include "enemy.h"

#include "../Player/player.h"

IEnemy::IEnemy(IGameObject* parent, const std::string& object_name)
	: IUnit(parent, object_name)
{
}

void IEnemy::TimerUpdate(void)
{
	// �e���˃^�C�}�[�N��
	m_FireTimer.Update();

	// �I�����Ă��Ȃ��Ȃ�C�[�W���O�^�C�}�[�N��
	if (!m_EasingTimer.Finished()) m_EasingTimer.Update();
}
