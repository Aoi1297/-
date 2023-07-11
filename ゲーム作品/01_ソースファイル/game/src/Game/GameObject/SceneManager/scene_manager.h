#pragma once

#include "aqua.h"

#include "../SceneManager/Scene/scene.h"

enum class SCENE_ID
{
	TITLE,		// �^�C�g��
	GAMEMAIN,	// �Q�[�����C��
	RESULT,		// ���U���g

	DUMMY,		// ����p�_�~�[
};

class CSceneManager : public aqua::IGameObject
{
public: // ���J�����o�֐�

	// �R���X�g���N�^
	CSceneManager	(IGameObject* parent);

	// �f�X�g���N�^
	~CSceneManager	(void)	override = default;

	// �������֐�
	void Initialize	(void)	override;

	// �X�V�֐�
	void Update		(void)	override;

	// �`��֐�
	void Draw		(void)	override;

	// ����֐�
	void Finalize	(void)	override;

public: // ���J�����o�֐�

	// ID�ɑΉ�����V�[���ֈړ�����
	void ChangeScene(SCENE_ID id);

private: // ����J�����o�ϐ�

	IScene*		m_CurrentScene_P;	// !< ���݂̃V�[��
	SCENE_ID	m_NextScene;		// !< ���̃V�[��
};