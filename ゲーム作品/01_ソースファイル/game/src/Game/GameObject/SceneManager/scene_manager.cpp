#include "scene_manager.h"

#include "Scene/scene.h"
#include "scene/1_Title/title.h"
#include "scene/2_GameMain/game_main.h"
#include "Scene/3_Result/result.h"

CSceneManager::CSceneManager(aqua::IGameObject* parent)
	// parent(CGame)
	: IGameObject(parent, "SceneManager")
	, m_CurrentScene_P(nullptr)
	, m_NextScene(SCENE_ID::TITLE)
{
}

void CSceneManager::Initialize(void)
{
	// �ŏ��Ɏn�܂�V�[����ݒ�
	m_NextScene = SCENE_ID::TITLE;
}

void CSceneManager::Update(void)
{
	// �V�[����؂�ւ���K�v���Ȃ���Έȍ~�̏������s��Ȃ�
	if (m_NextScene == SCENE_ID::DUMMY)
	{
		// ���݂̃V�[���̍X�V�������s��
		IGameObject::Update();
		return;
	}

	// �V�[�������݂��Ă���ꍇ�͈ȉ��̏������s��
	if (m_CurrentScene_P)
	{	
		// ���݂̃V�[���̉���������s��
		m_CurrentScene_P->Finalize();

		// ���݂̃V�[�����폜����i�q���X�g����O���j
		m_ChildObjectList.erase(std::find(m_ChildObjectList.begin(), m_ChildObjectList.end(), m_CurrentScene_P));

		// �|�C���^�̔j����NULL��
		AQUA_SAFE_DELETE(m_CurrentScene_P)
	}

	// �V�[���̐����ƃV�[���̏��������s��
	switch (m_NextScene)
	{
	case SCENE_ID::TITLE:	 m_CurrentScene_P = aqua::CreateGameObject<CTitle>(this);	break;
	case SCENE_ID::GAMEMAIN: m_CurrentScene_P = aqua::CreateGameObject<CGameMain>(this);break;
	case SCENE_ID::RESULT:	 m_CurrentScene_P = aqua::CreateGameObject<CResult>(this);	break;
	}

	// �V�[���𐶐�������DUMMY�ɖ߂�
	m_NextScene = SCENE_ID::DUMMY;

	// ���������N���X�I�u�W�F�N�g�i�V�[���j�̏�����
	IGameObject::Initialize();

	// ���������V�[���̍X�V�������s��
	IGameObject::Update();
}

void CSceneManager::Draw(void)
{
	// ���������N���X�I�u�W�F�N�g�̕`����s��
	IGameObject::Draw();
}

void CSceneManager::Finalize(void)
{
	// ���������N���X�I�u�W�F�N�g�̉�����s��
	IGameObject::Finalize();
}

void CSceneManager::ChangeScene(SCENE_ID scene_id)
{
	// �ύX����V�[����ݒ肷��
	m_NextScene = scene_id;
}