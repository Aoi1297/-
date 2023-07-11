#include "ui_manager.h"

#include "UI/Frame/frame.h"
#include "UI/Score/score.h"
#include "UI/GameOver/game_over.h"
#include "UI/GameClear/game_clear.h"
#include "UI/ShowMessage/show_message.h"

CUiManager::CUiManager(IGameObject* parent)
	// parent(CGameMain)
	: IGameObject(parent,"UIManager")
{
}

void CUiManager::Update(void)
{
	// ��������UI�̍X�V�������s��
	IGameObject::Update();
}

void CUiManager::Draw(void)
{
	// ��������UI�̕`����s��
	IGameObject::Draw();
}

void CUiManager::Finalize(void)
{
	// ��������UI�̉�����s��
	IGameObject::Finalize();
}

void CUiManager::CreateUI(UI_ID id)
{
	IUserInterface* ui = nullptr;

	switch (id)
	{
	case UI_ID::FRAME:ui = aqua::CreateGameObject<CUIFrame>(this);			break;
	case UI_ID::SCORE:ui = aqua::CreateGameObject<CUIScore>(this);			break;
	case UI_ID::GAMEOVER:ui = aqua::CreateGameObject<CUiGameOver>(this);	break;
	case UI_ID::GAMECLEAR:ui = aqua::CreateGameObject<CUiGameClear>(this);	break;
	}

	if (ui) ui->Initialize();
}

void CUiManager::ShowMessage(const ITEM_ID& power_id)
{
	CShowMessage* message = nullptr;

	message = aqua::CreateGameObject<CShowMessage>(this);

	if (message) message->ShowMessage(power_id);
}