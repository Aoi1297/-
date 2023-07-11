#include "game_clear.h"

#include "../../../SceneManager/scene_manager.h"
#include "../../../EffectManager/effect_manager.h"
#include "../../../UnitManager/unit_manager.h"

CUiGameClear::CUiGameClear(IGameObject* parent)
	// parent(CUiManager)
	: IUserInterface(parent, "UIGameClear")
	, DrawFlag(false)
{
}

void CUiGameClear::Initialize(void)
{
	// �Q�[���N���A�X�v���C�g�̐���
	m_UiSprite.Create("data/texture/ui/game_clear.png");

	// ��ʂ̒��S�ʒu
	m_UiSprite.position = { (float)aqua::GetWindowWidth() / 2 - m_UiSprite.GetTextureWidth() / 2,(float)aqua::GetWindowHeight() / 2 - m_UiSprite.GetTextureHeight() / 2 };

	// �G�t�F�N�g�}�l�[�W���[�̃N���X�|�C���^
	m_EffectManager_P = (CEffectManager*)aqua::FindGameObject("EffectManager");

	// �Q�[���N���A��\������܂ł̎��Ԃ̐ݒ�
	m_GameClearTime.Setup(5.0f);

	// �G�t�F�N�g�����Ԋu�^�C���ݒ�
	m_EffectTime.Setup(0.3f);
}

void CUiGameClear::Update(void)
{
	// �^�C�}�[�̍X�V
	m_GameClearTime.Update();
	m_EffectTime.Update();

	// �^�C�}�[���I�����Ă�����
	if (m_GameClearTime.Finished())
	{
		DrawFlag = true;
	}

	// �G�t�F�N�g�������Ԃ������琶��
	if (m_EffectTime.Finished() && !DrawFlag)
	{
		// �G�t�F�N�g����ʂ̃����_���Ȉʒu�ɐ���
		m_EffectManager_P->CreateEffect(EFFECT_ID::DEAD_ENEMY, aqua::CVector2(aqua::Rand(aqua::GetWindowWidth()), aqua::Rand(aqua::GetWindowHeight())), CATEGORY_ID::PLAYER);

		m_EffectTime.Reset();
	}

	// Z�L�[�Ń^�C�g���ɖ߂�
	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::Z))
	{
		Finalize();
		((CSceneManager*)aqua::FindGameObject("SceneManager"))->ChangeScene(SCENE_ID::TITLE);
	}
}

void CUiGameClear::Draw(void)
{
	if(DrawFlag)
	m_UiSprite.Draw();
}

void CUiGameClear::Finalize(void)
{
	m_UiSprite.Delete();
}
