#include "result.h"

CResult::CResult(IGameObject* parent)
	: IScene(parent,"Result")
{
}

void CResult::Initialize(void)
{
	m_TitleText.Create(50);
	m_TitleText.text = "���U���g[SPACE]";
}

void CResult::Update(void)
{
	// �X�y�[�X�L�[����������Q�[�����C���V�[���𐶐�����
	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::SPACE))
	{
		((CSceneManager*)aqua::FindGameObject("SceneManager"))->ChangeScene(SCENE_ID::TITLE);
	}
}

void CResult::Draw(void)
{
	m_TitleText.Draw();
}

void CResult::Finalize(void)
{
	m_TitleText.Delete();

	// title�̎q�I�u�W�F�N�g�̉���������s��
	IGameObject::Finalize();
}
