#include "game_main.h"

#include "../../../Field/field.h"
#include "../../../UnitManager/unit_manager.h"
#include "../../../ItemManager/item_manager.h"
#include "../../../BulletManager/bullet_manager.h"
#include "../../../EffectManager/effect_manager.h"
#include "../../../InterfaceManager/ui_manager.h"
#include "../../../CameraManager/camera_manager.h"
#include "../../../SoundManager/sound_creater.h"

const aqua::CVector2 CGameMain::m_player_position	= { (float)aqua::GetWindowWidth() / 2,(float)aqua::GetWindowHeight() / 2 };
const float			 CGameMain::m_game_time_set		= 250.0f;

CGameMain::CGameMain(IGameObject* parent)
	// parent(CSceneManager)
	: IScene(parent, "GameMain")
	, m_GameOverFlag(false)
{
}

void CGameMain::Initialize(void)
{
	// �^�C�g��BGM�̍Đ����~
	((CSoundCreater*)aqua::FindGameObject("SoundManager"))->Stop(SOUND_ID::BGM_TITLE);

	// �Q�[��BGM���Đ�
	((CSoundCreater*)aqua::FindGameObject("SoundManager"))->Play(SOUND_ID::BGM_GAME);

	// �w�i�N���X�I�u�W�F�N�g�̐���
	aqua::CreateGameObject<CField>(this);

	// ���j�b�g�}�l�[�W���[�N���X�I�u�W�F�N�g�̐���
	CUnitManager* unit_manager = aqua::CreateGameObject<CUnitManager>(this);

	// �A�C�e���}�l�[�W���[�N���X�I�u�W�F�N�g�̐���
	aqua::CreateGameObject<CItemManager>(this);

	// �e�}�l�[�W���[�N���X�I�u�W�F�N�g�̐���
	aqua::CreateGameObject<CBulletManager>(this);

	// �G�t�F�N�g�}�l�[�W���[�N���X�I�u�W�F�N�g�̐���
	aqua::CreateGameObject<CEffectManager>(this);

	// UI�}�l�[�W���[�N���X�I�u�W�F�N�g�̐���
	CUiManager* ui_manager = aqua::CreateGameObject<CUiManager>(this);

	// �J�����}�l�[�W���[�N���X�I�u�W�F�N�g�̐���
	aqua::CreateGameObject<CCameraManager>(this);

	// UI�i�t���[���j���쐬
	ui_manager->CreateUI(UI_ID::FRAME);

	// UI�i�X�R�A�j���쐬
	ui_manager->CreateUI(UI_ID::SCORE);

	// ���삷��v���C���[���쐬
	unit_manager->CreateUnit(UNIT_ID::PLAYER, { m_player_position });

	// �Q�[���o�ߎ��Ԑݒ�
	m_GameTimer.Setup(m_game_time_set);

	// ���������N���X�I�u�W�F�N�g�̏��������s��
	IGameObject::Initialize();
}

void CGameMain::Update(void)
{
	// �Q�[���^�C�}�[�̌v�����s��
	m_GameTimer.Update();

	// ���������N���X�I�u�W�F�N�g�̍X�V�������s��
	IGameObject::Update();
}

void CGameMain::Draw(void)
{
	// ���������N���X�I�u�W�F�N�g�̕`�揈�����s��
	IGameObject::Draw();
}

void CGameMain::Finalize(void)
{
	// ���������N���X�I�u�W�F�N�g�̉���������s��
	IGameObject::Finalize();
}