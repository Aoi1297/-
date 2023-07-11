#include "effect_manager.h"

#include "Effect/effect.h"

#include "Effect/BulletSpawn/bullet_spawn.h"
#include "Effect/Damage/damage.h"
#include "Effect/Darkness/darkness.h"
#include "Effect/DeadEnemy/dead_enemy.h"
#include "Effect/GetItem/get_item.h"
#include "Effect/Laser/laser.h"
#include "Effect/Ripple/ripple.h"

CEffectManager::CEffectManager(IGameObject* parent)
	// parent(CGameMain)
	: IGameObject(parent, "EffectManager")
{
}

void CEffectManager::Update(void)
{
	IGameObject::Update();
}

void CEffectManager::Draw(void)
{
	IGameObject::Draw();
}

void CEffectManager::Finalize(void)
{
	IGameObject::Finalize();
}

void CEffectManager::CreateEffect(const EFFECT_ID& effect_id, const aqua::CVector2& create_pos, const CATEGORY_ID& category)
{
	IEffect* effect = nullptr;

	// エフェクトIDに対するクラスオブジェクトを生成する
	switch (effect_id)
	{
	case EFFECT_ID::RIPPLES:effect = aqua::CreateGameObject<CRipple>(this);			break;
	case EFFECT_ID::DARKNESS:effect = aqua::CreateGameObject<CDarkness>(this);		break;
	case EFFECT_ID::DAMAGE:effect = aqua::CreateGameObject<CDamage>(this);			break;
	case EFFECT_ID::BULLET_SPAWN:effect = aqua::CreateGameObject<CSpawn>(this);		break;
	case EFFECT_ID::LASER:effect = aqua::CreateGameObject<CLaser>(this);			break;
	case EFFECT_ID::GETITEM:effect = aqua::CreateGameObject<CGetItem>(this);		break;
	case EFFECT_ID::DEAD_ENEMY:effect = aqua::CreateGameObject<CDeadEnemy>(this);	break;
	}

	// NULLチェックを行い、マネージャーが受け取った情報を元に初期化を行う
	if (effect) effect->SetStatus(create_pos, category);
}