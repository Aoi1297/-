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
	// ユニットマネージャークラスオブジェクトのポインタを取得
	m_UnitManager_P = ((CUnitManager*)aqua::FindGameObject("UnitManager"));
}

void CBulletManager::Update(void)
{
	// 生成した弾リストを生成した順番に調べていく
	for (auto& it = GetChildList()->begin(); it != GetChildList()->end(); ++it)
	{
		IBullet* bullet = (IBullet*)*it;

		// 画面外へ弾が移動したら弾のクラスオブジェクトを削除する
		if (bullet->GetCenterPosition().x > aqua::GetWindowWidth())		bullet->DeleteObject();
		if (bullet->GetCenterPosition().x < 0)							bullet->DeleteObject();
		if (bullet->GetCenterPosition().y > aqua::GetWindowHeight())	bullet->DeleteObject();
		if (bullet->GetCenterPosition().y < 0)							bullet->DeleteObject();
	
		// 弾の状態が消滅状態ならユニットとの当たり判定を行わない（理由：DeleteObject()はOBJECT_STATEをDEADにするだけでクラスオブジェクトは次のフレームで削除されるため）
		if (bullet->GetGameObjectState() == aqua::GAME_OBJECT_STATE::DEAD) continue;

		// 生きている弾とプレイヤーの当たり判定を行う
		m_UnitManager_P->CheckUnit(bullet);
	}

	// 生成した弾の更新処理を行う
	IGameObject::Update();
}

void CBulletManager::Draw(void)
{
	// 生成した弾クラスの描画を行う
	IGameObject::Draw();
}

void CBulletManager::Finalize(void)
{
	// 生成した弾クラスのメモリ解放処理を行う
	IGameObject::Finalize();
}

void CBulletManager::CreateBullet(const CATEGORY_ID& category_id, const BULLET_ID& bullet_id, const aqua::CVector2& center_position, const float& bullet_speed, const float& direction)
{
	IBullet* bullet = nullptr;

	// IDに対応する弾クラスオブジェクトを生成する
	switch (bullet_id)
	{
	case BULLET_ID::NORMAL: bullet = aqua::CreateGameObject<CNormalBullet>(this); break;
	case BULLET_ID::HOMING: bullet = aqua::CreateGameObject<CHomingBullet>(this); break;
	case BULLET_ID::FIREWORK: bullet = aqua::CreateGameObject<CFireWorkBullet>(this); break;
	case BULLET_ID::DIRECTION: bullet = aqua::CreateGameObject<CDirectionBullet>(this); break;
	}

	// 生成した弾の初期設定を行う
	if (bullet) bullet->SetStatus(category_id, center_position, bullet_speed, direction);
}
