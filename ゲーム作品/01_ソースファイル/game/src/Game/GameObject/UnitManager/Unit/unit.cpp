#include "unit.h"

#include "../../UnitManager/unit_manager.h"
#include "../../BulletManager/Bullet/bullet.h"
#include "../../ItemManager/Item/item.h"
#include "../../SceneManager/Scene/2_GameMain/game_main.h"
#include "../../InterfaceManager/ui_manager.h"
#include "../../UnitManager/Unit/Player/player.h"
#include "../../EffectManager/effect_manager.h"
#include "../../CameraManager/camera_manager.h"
#include "../../InterfaceManager/UI/Score/score.h"
#include "../../ItemManager/item_manager.h"
#include "../../BulletManager/bullet_manager.h"
#include "../../SoundManager/sound_creater.h"

const int IUnit::m_get_item_score		= 3000;
const int IUnit::m_defeat_score			= 1000;
const float IUnit::m_item_hit_radius	= 30.0f;

IUnit::IUnit(IGameObject* parent, const std::string& object_name)
	// parent(CGameMain)
	: IGameObject		(parent, object_name)
	, m_LifePoint		(0)
	, m_MoveSpeed		(0.0f)
	, m_GameMain_P		(nullptr)
	, m_UiManager_P		(nullptr)
	, m_Player_P		(nullptr)
	, m_EffectManager_P	(nullptr)
	, m_CameraManager_P	(nullptr)
	, m_Score_P			(nullptr)
	, m_ItemManager_P	(nullptr)
	, m_SoundManager_P	(nullptr)
{
	// �Q�[�����C���V�[���N���X�|�C���^�̎擾
	m_GameMain_P = ((CGameMain*)aqua::FindGameObject("GameMain"));

	// UI�}�l�[�W���[�N���X�|�C���^�̎擾
	m_UiManager_P = ((CUiManager*)aqua::FindGameObject("UIManager"));

	// �G�t�F�N�g�}�l�[�W���[�N���X�|�C���^�̎擾
	m_EffectManager_P = ((CEffectManager*)aqua::FindGameObject("EffectManager"));

	// �J�����}�l�[�W���[�N���X�|�C���^�̎擾
	m_CameraManager_P = ((CCameraManager*)aqua::FindGameObject("CameraManager"));

	// �X�R�A�N���X�|�C���^�̎擾
	m_Score_P = ((CUIScore*)aqua::FindGameObject("UIScore"));

	// �A�C�e���}�l�[�W���[�N���X�|�C���^�̎擾
	m_ItemManager_P = ((CItemManager*)aqua::FindGameObject("ItemManager"));

	// �o���b�g�}�l�[�W���[�N���X�|�C���^�̎擾
	m_BulletManager_P = ((CBulletManager*)aqua::FindGameObject("BulletManager"));

	// �T�E���h�}�l�[�W���N���X�|�C���^�̎擾
	m_SoundManager_P = ((CSoundCreater*)aqua::FindGameObject("SoundManager"));
}

void IUnit::CreateSprite(const std::string& sprite_file_name)
{
	// �摜�̓ǂݍ���
	m_UnitSprite.Create(sprite_file_name);

	// ��]�̊�_���摜�̒��S�ɐݒ�
	m_UnitSprite.anchor = { (float)m_UnitSprite.GetTextureWidth() / 2,(float)m_UnitSprite.GetTextureHeight() / 2 };
}

void IUnit::SetStatus(const UNIT_ID& unit_id, const CATEGORY_ID& unit_category_id, const aqua::CVector2& create_pos)
{
	// ���j�b�gID�ݒ�
	m_UnitId = unit_id;

	// �J�e�S���[�ݒ�
	m_UnitCategory = unit_category_id;

	// �z���ʒu�ݒ�
	m_UnitSprite.position = m_Position = create_pos;

	// �������֐����Ăяo��
	Initialize();
}

void IUnit::Draw(void)
{
	// ���j�b�g�X�v���C�g�̕`��
	m_UnitSprite.Draw();
}

void IUnit::Finalize()
{
	// ���j�b�g�X�v���C�g�̃��������
	m_UnitSprite.Delete();
}

void IUnit::CheckHitBullet(IBullet* bullet)
{
	aqua::CVector2 vector = GetCenterPosition() - bullet->GetCenterPosition();

	// �v���C���[�ƓG�̒e�Ƃ̓����蔻��
	if (
		// �J�e�S���[���v���C���[�@����
		m_UnitCategory == CATEGORY_ID::PLAYER &&

		// �e�̃J�e�S���[���G�@�܂��́@�{�X�@����
		(bullet->GetCategory() == CATEGORY_ID::ENEMY ||
			bullet->GetCategory() == CATEGORY_ID::BOSS) &&

		// �����̋������v���C���[�̓����蔼�a�ȉ��̋����ɂȂ����Ƃ�
		vector.Length() <= GetRadius())
	{
		// �v���C���[�̃��C�t���P���炵�A�O�ȉ��ł������ꍇ�Q�[���I�[�o�[
		if (--m_LifePoint <= 0)
		{
			// �Q�[���I�[�o�[
			m_GameMain_P->SetGameOverFlag();

			// �Q�[���I�[�o�[���b�Z�[�W��\������
			m_UiManager_P->CreateUI(UI_ID::GAMEOVER);

			// �v���C���[�N���X�I�u�W�F�N�g���폜
			IGameObject::DeleteObject();
		}

		// �v���C���[�̃��C�t���O�ȉ��ł͂Ȃ��i����ł��Ȃ��ꍇ�j���@���E�s�Ǐ�Ԃł͂Ȃ��ꍇ
		else if (!(m_LifePoint <= 0) && m_Player_P->GetDarknessFlag() == false)
		{
			// ���ʉ���炷
			((CSoundCreater*)aqua::FindGameObject("SoundManager"))->Play(SOUND_ID::EFFECT_ALERT);

			// ���E�s�Ǐ�ԂɃZ�b�g����
			m_Player_P->SetDarknessFlag();

			// ���E�s�ǃG�t�F�N�g�𐶐�
			m_EffectManager_P->CreateEffect(EFFECT_ID::DARKNESS, GetCenterPosition(), m_UnitCategory);

			// �_���[�W�G�t�F�N�g�𐶐�
			m_EffectManager_P->CreateEffect(EFFECT_ID::DAMAGE, aqua::CVector2::ZERO, m_UnitCategory);
		}

		// �e�ɓ��������ꍇ�̓��C�t�Ɋ֌W�Ȃ���ʂ�h�炷�������s��
		m_CameraManager_P->Shake();

		// �e���v���C���[�ɏՓ˂�����e���폜����
		bullet->DeleteObject();
	}

	// �G�܂��̓{�X�ƃv���C���[�̒e�Ƃ̓����蔻��
	if (
		// �J�e�S���[���G�@�܂��́@�J�e�S���[���{�X�@����
		(m_UnitCategory == CATEGORY_ID::ENEMY ||
			m_UnitCategory == CATEGORY_ID::BOSS) &&

		// �e�̃J�e�S���[���v���C���[�̏ꍇ�@����
		bullet->GetCategory() == CATEGORY_ID::PLAYER &&

		// �����̋������v���C���[�̓����蔼�a�ȉ��̋����ɂȂ����Ƃ�
		vector.Length() <= GetRadius())
	{
		// �G�̃��C�t���P���炵�A�O�ȉ��ł������ꍇ
		if (--m_LifePoint == 0)
		{
			// �G���j���̊l���X�R�A
			m_Score_P->AddScore(m_defeat_score * (int)m_UnitId);

			// �G���j�G�t�F�N�g�𐶐�
			m_EffectManager_P->CreateEffect(EFFECT_ID::DEAD_ENEMY, GetCenterPosition(), m_UnitCategory);

			// ��ʂ�U��������
			m_CameraManager_P->Shake();

			// �G�I�u�W�F�N�g�N���X�폜
			IGameObject::DeleteObject();

			if (m_UnitCategory == CATEGORY_ID::BOSS)
			{
				m_EffectManager_P->CreateEffect(EFFECT_ID::DAMAGE, aqua::CVector2::ZERO, CATEGORY_ID::ENEMY);
				m_UiManager_P->CreateUI(UI_ID::GAMECLEAR);
			}
	
			// ���j���A�C�e�������_������
			m_ItemManager_P->CreateItem((ITEM_ID)aqua::Rand((int)ITEM_ID::MAX - 1), GetCenterPosition());
		}

		// �Փˎ��e����
		bullet->DeleteObject();

		// �Փˎ��Փ˃G�t�F�N�g����
		m_EffectManager_P->CreateEffect(EFFECT_ID::RIPPLES, bullet->GetCenterPosition(), m_UnitCategory);
	}
}

void IUnit::CheckHitItem(IItem* item)
{
	// ���j�b�g�ƃA�C�e���̋���
	aqua::CVector2 vector = GetCenterPosition() - item->GetCenterPosition();

	// ���j�b�g�̓����蔼�a�ȉ��̋����ɂȂ�����
	if (vector.Length() <= m_item_hit_radius)
	{
		// �A�C�e���l���X�R�A
		m_Score_P->AddScore(m_get_item_score);

		// �A�C�e���擾�G�t�F�N�g�𐶐�
		m_EffectManager_P->CreateEffect(EFFECT_ID::GETITEM, m_Position, m_UnitCategory);

		// �A�C�e���擾
		item->HitItem();

		// ��ʂ�U��������
		m_CameraManager_P->Shake();
	}
}

aqua::CVector2 IUnit::GetCenterPosition()
{
	return { m_Position.x + (float)m_UnitSprite.GetTextureWidth() / 2,m_Position.y + (float)m_UnitSprite.GetTextureHeight() / 2 };
}

CATEGORY_ID IUnit::GetCategory()
{
	return m_UnitCategory;
}

float IUnit::GetSpriteWidth()
{
	return m_UnitSprite.GetTextureWidth();
}

void IUnit::SetPlayerPointer(void)
{
	// �v���C���[�N���X�|�C���^�̎擾
	m_Player_P = ((CPlayer*)aqua::FindGameObject("Player"));
}
