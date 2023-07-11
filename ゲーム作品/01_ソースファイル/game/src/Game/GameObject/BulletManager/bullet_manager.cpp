#include "bullet_manager.h"

#include "Bullet/NormalBullet/normal_bullet.h"
#include "Bullet/HomingBullet/homing_bullet.h"
#include "Bullet/FireworkBullet/firework_bullet.h"
#include "Bullet/DirectionBullet/direction_bullet.h"

#include "../UnitManager/unit_manager.h"

CBulletManager::CBulletManager(IGameObject* parent)
	// parent(CGameMain)
	: IGameObject(parent,"BulletManager")
	, m_UnitManager_P(nullptr)
{
}

void CBulletManager::Initialize(void)
{
	// ���j�b�g�}�l�[�W���[�N���X�I�u�W�F�N�g�̃|�C���^���擾
	m_UnitManager_P = ((CUnitManager*)aqua::FindGameObject("UnitManager"));
}

void CBulletManager::Update(void)
{
	// ���������e���X�g�𐶐��������Ԃɒ��ׂĂ���
	for (auto& it = GetChildList()->begin(); it != GetChildList()->end(); ++it)
	{
		IBullet* bullet = (IBullet*)*it;

		// ��ʊO�֒e���ړ�������e�̃N���X�I�u�W�F�N�g���폜����
		if (bullet->GetCenterPosition().x > aqua::GetWindowWidth())		bullet->DeleteObject();
		if (bullet->GetCenterPosition().x < 0)							bullet->DeleteObject();
		if (bullet->GetCenterPosition().y > aqua::GetWindowHeight())	bullet->DeleteObject();
		if (bullet->GetCenterPosition().y < 0)							bullet->DeleteObject();
	
		// �e�̏�Ԃ����ŏ�ԂȂ烆�j�b�g�Ƃ̓����蔻����s��Ȃ��i���R�FDeleteObject()��OBJECT_STATE��DEAD�ɂ��邾���ŃN���X�I�u�W�F�N�g�͎��̃t���[���ō폜����邽�߁j
		if (bullet->GetGameObjectState() == aqua::GAME_OBJECT_STATE::DEAD) continue;

		// �����Ă���e�ƃv���C���[�̓����蔻����s��
		m_UnitManager_P->CheckUnit(bullet);
	}

	// ���������e�̍X�V�������s��
	IGameObject::Update();
}

void CBulletManager::Draw(void)
{
	// ���������e�N���X�̕`����s��
	IGameObject::Draw();
}

void CBulletManager::Finalize(void)
{
	// ���������e�N���X�̃���������������s��
	IGameObject::Finalize();
}

void CBulletManager::CreateBullet(const CATEGORY_ID& category_id, const BULLET_ID& bullet_id, const aqua::CVector2& center_position, const float& bullet_speed, const float& direction)
{
	IBullet* bullet = nullptr;

	// ID�ɑΉ�����e�N���X�I�u�W�F�N�g�𐶐�����
	switch (bullet_id)
	{
	case BULLET_ID::NORMAL: bullet = aqua::CreateGameObject<CNormalBullet>(this); break;
	case BULLET_ID::HOMING: bullet = aqua::CreateGameObject<CHomingBullet>(this); break;
	case BULLET_ID::FIREWORK: bullet = aqua::CreateGameObject<CFireWorkBullet>(this); break;
	case BULLET_ID::DIRECTION: bullet = aqua::CreateGameObject<CDirectionBullet>(this); break;
	}

	// ���������e�̏����ݒ���s��
	if (bullet) bullet->SetStatus(category_id, center_position, bullet_speed, direction);
}
