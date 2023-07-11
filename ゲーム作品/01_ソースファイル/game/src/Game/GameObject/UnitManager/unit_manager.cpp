#include "unit_manager.h"

#include "../BulletManager/Bullet/bullet.h"
#include "../ItemManager/Item/item.h"
#include "../UnitManager/Unit/unit.h"
#include "../SoundManager/sound_creater.h"
#include "../SceneManager/Scene/2_GameMain/game_main.h"

#include "../UnitManager/Unit/Player/player.h"
#include "../UnitManager/Unit/Enemy/Normal/normal.h"
#include "../UnitManager/Unit/Enemy/FireWork/fire_work.h"
#include "../UnitManager/Unit/Enemy/Star/star.h"
#include "../UnitManager/Unit/Enemy/MiniBoss/mini_boss.h"
#include "../UnitManager/Unit/Enemy/NormalTough/normal_tough.h"
#include "../UnitManager/Unit/Enemy/FireWorkTough/fire_work_tough.h"
#include "../UnitManager/Unit/Enemy/FinalBoss/final_boss.h"
#include "../UnitManager/Unit/unit.h"

CUnitManager::CUnitManager(IGameObject* parent)
	// parent(CGameMain)
	: IGameObject(parent, "UnitManager")
	, m_GameMain_P(nullptr)
{
}

void CUnitManager::Initialize(void)
{
	// �Q�[�����C���V�[���N���X�̃|�C���^���擾
	m_GameMain_P = ((CGameMain*)aqua::FindGameObject("GameMain"));

	// �T�E���h�N���X�|�C���^���擾
	m_SoundManager_P = ((CSoundCreater*)aqua::FindGameObject("SoundManager"));

	// �G�l�~�[�e�[�u���̉��
	Parse("data/csv/enemy_table.csv");
}

void CUnitManager::Update(void)
{
	// NULL�`�F�b�N
	if (!m_GameMain_P) return;

	// �Q�[���I�[�o�[�Ȃ珈�������Ȃ�
	if (m_GameMain_P->GetGameOverFlag()) return;

	// �G�l�~�[�e�[�u�������ɓG��z������
	DeployEnemy();

	// �����������j�b�g�̍X�V���s��
	IGameObject::Update();
}

void CUnitManager::Draw(void)
{
	// NULL�`�F�b�N
	if (!m_GameMain_P) return;

	// �Q�[���I�[�o�[�Ȃ珈�������Ȃ�
	if (m_GameMain_P->GetGameOverFlag()) return;

	// �����������j�b�g�̕`����s��
	IGameObject::Draw();
}

void CUnitManager::Finalize(void)
{
	// �����������j�b�g�̉�����s��
	IGameObject::Finalize();
}

void CUnitManager::Parse(const std::string& csv_file_name)
{
	// CSV���[�_�[����
	aqua::CCSVLoader csv_loader;

	// SCV�t�@�C���̓ǂݍ���
	csv_loader.Load(csv_file_name);

	// �c�̃Z���������J��Ԃ�
	for (int i = 0; i < csv_loader.GetRows(); ++i)
	{
		// �G �\���̂𐶐�
		ENEMY_DATA enemy_data;

		// �G�l�~�[ID���擾
		enemy_data.unit_id = (UNIT_ID)csv_loader.GetInteger(i, 0);

		// �z���ʒu���擾
		{
			// X���W
			enemy_data.position.x = csv_loader.GetFloat(i, 1);

			// Y���W
			enemy_data.position.y = csv_loader.GetFloat(i, 2);
		}

		// �������ԁi�Q�[���J�n���牽�b��Ȃ̂��j���擾
		enemy_data.create_time = csv_loader.GetFloat(i, 3);

		// �G�P�̂̏��Ƃ��Ĕz��Ɋi�[
		m_EnemyTable.push_back(enemy_data);
	}

	// SCV�t�@�C���̉��
	csv_loader.Unload();
}

void CUnitManager::DeployEnemy()
{
	// �G�l�~�[�e�[�u������Ȃ珈�������Ȃ�
	if (!m_EnemyTable.empty())
	{
		// �w��o�����Ԃ��Q�[���o�ߎ��Ԃ𒴂��Ă�����o��������
		if (m_EnemyTable[0].create_time < m_GameMain_P->GetGameTime())
		{
			// ���j�b�g�i�G�j�𐶐�
			CreateUnit(m_EnemyTable[0].unit_id, m_EnemyTable[0].position);

			// ����������f�[�^���珜�O����
			m_EnemyTable.erase(m_EnemyTable.begin());
		}
	}
}

void CUnitManager::CreateUnit(const UNIT_ID& unit_id, const aqua::CVector2& create_position)
{
	// ���j�b�g���쐬
	IUnit* unit = nullptr;

	// �J�e�S���[�̍쐬
	CATEGORY_ID category = CATEGORY_ID::MAX;

	// ����������ID���m�F���Ă���ID�ƈ�v���郆�j�b�g�𐶐�����
	switch (unit_id)
		{
		case UNIT_ID::PLAYER:
		{
			unit = aqua::CreateGameObject<CPlayer>(this);
			category = CATEGORY_ID::PLAYER;
		}break;

		case UNIT_ID::NORMAL:
		{
			unit = aqua::CreateGameObject<CNormal>(this);
			category = CATEGORY_ID::ENEMY;
		}break;

		case UNIT_ID::FIRE_WORK:
		{
			unit = aqua::CreateGameObject<CFireWork>(this);
			category = CATEGORY_ID::ENEMY;
		}break;

		case UNIT_ID::STAR:
		{
			unit = aqua::CreateGameObject<CStar>(this);
			category = CATEGORY_ID::ENEMY;
		}break;

		case UNIT_ID::MINI_BOSS:
		{
			unit = aqua::CreateGameObject<CMiniBoss>(this);
			category = CATEGORY_ID::ENEMY;
		}break;

		case UNIT_ID::FIRE_WORK_TOUGH:
		{
			unit = aqua::CreateGameObject<CFireWorkTough>(this);
			category = CATEGORY_ID::ENEMY;
		}break;

		case UNIT_ID::FINAL_BOSS:
		{
			unit = aqua::CreateGameObject<CFinalBoss>(this);
			category = CATEGORY_ID::BOSS;
		}break;

		case UNIT_ID::NORMAL_TOUGH:
		{
			unit = aqua::CreateGameObject<CNormalTough>(this);
			category = CATEGORY_ID::ENEMY;
		}break;
	}

	// NULL�`�F�b�N
	if (!unit) return;
	
	// ���ʉ���炷
	((CSoundCreater*)aqua::FindGameObject("SoundManager"))->Play(SOUND_ID::EFFECT_SPAWN);

	// �����������j�b�g�����̏��������s��
	unit->SetStatus(unit_id, category, create_position);
}

void CUnitManager::CheckUnit(IBullet* bullet)
{
	// ���j�b�g���X�g����Ȃ瓖���蔻��`�F�b�N���s��Ȃ�
	if (GetChildList()->empty()) return;

	// �����������j�b�g�S�ĂɈȉ��̏��������X�ɍs��
	for (auto it = GetChildList()->begin(); it != GetChildList()->end(); ++it)
	{
		// ���X�g�f�[�^��unit�Ɋi�[����
		IUnit* unit = (IUnit*)*it;

		// ���j�b�g����ʊO�֍s�����Ȃ�폜����(�摜�������Ȃ��Ȃ���������悤�ɒ���������j
		if (unit->GetCenterPosition().x < 0 - unit->GetSpriteWidth() / 2)
		{
			// ��ʊO�֍s�������j�b�g�̍폜���s��
			unit->DeleteObject();
		}

		// ��ʓ��ɂ��郆�j�b�g�̒e�Ƃ̓����蔻����`�F�b�N����
		unit->CheckHitBullet(bullet);
	}
}

void CUnitManager::CheckUnit(IItem* item)
{
	// ���j�b�g���X�g����Ȃ瓖���蔻��`�F�b�N���s��Ȃ�
	if (GetChildList()->empty()) return;

	// �����������j�b�g�S�ĂɈȉ��̏��������X�ɍs��
	for (auto it = GetChildList()->begin(); it != GetChildList()->end(); ++it)
	{
		// ���X�g�f�[�^��unit�Ɋi�[����
		IUnit* unit = (IUnit*)*it;

		// �A�C�e���ƃ��j�b�g�Ƃ̏Փ˔���
		unit->CheckHitItem(item);
	}
}

IUnit* CUnitManager::FindNearUnit(IBullet* bullet)
{
	// ���j�b�g���X�g����̏ꍇ�͏��������Ȃ�
	if (GetChildList()->empty()) return nullptr;

	// �����ŏ��l�ݒ�
	float min = 99999.0f;

	// �߂��̃��j�b�g�̃|�C���^���i�[����ϐ�
	IUnit* near_unit = nullptr;

	// �����������j�b�g���X�g�����ԋ߂����j�b�g�𒲂ׂ�
	for (auto it = GetChildList()->begin(); it != GetChildList()->end(); ++it)
	{
		IUnit* unit = (IUnit*)*it;

		// �v���C���[�ȊO�̃J�e�S���[�ɑ΂��Ă̂ݏ������s��
		if (!(unit->GetCategory() == CATEGORY_ID::PLAYER))
		{
			// ���j�b�g�̈ʒu�ƒe�̈ʒu���������x�N�g�������߂�
			aqua::CVector2 direction = unit->GetCenterPosition() - bullet->GetCenterPosition();

			// ���̃x�N�g���̋��������X�g�̒������ԒZ����΍X�V����
			if (direction.Length() <= min)
			{
				// �ŒZ�����X�V
				min = direction.Length();

				// ��ԋ߂����j�b�g�̃|�C���^���擾
				near_unit = unit;
			}
		}
	}

	// ���߂���ԋ߂����j�b�g�̃|�C���^��Ԃ�
	return near_unit;
}