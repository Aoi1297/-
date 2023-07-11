#include "game_over.h"
#include "../../../SceneManager/scene_manager.h"

CUiGameOver::CUiGameOver(IGameObject* parent)
	// parent(CUiManager)
	: IUserInterface(parent, "UIGameOver")
{
}

void CUiGameOver::Initialize(void)
{
	// �Q�[���I�[�o�[�摜�̐���
	m_UiSprite.Create("data/texture/ui/game_over.png");

	// ��ʂ̒��S�ʒu
	m_UiSprite.position = { (float)aqua::GetWindowWidth() / 2 - m_UiSprite.GetTextureWidth() / 2,(float)aqua::GetWindowHeight() / 2 - m_UiSprite.GetTextureHeight() / 2 };
}

void CUiGameOver::Update(void)
{
	// Z�L�[�Ń^�C�g���ɖ߂�
	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::Z))
	{
		Finalize();
		((CSceneManager*)aqua::FindGameObject("SceneManager"))->ChangeScene(SCENE_ID::TITLE);
	}
}

void CUiGameOver::Draw(void)
{
	m_UiSprite.Draw();
}

void CUiGameOver::Finalize(void)
{
	m_UiSprite.Delete();
}
