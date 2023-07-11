#include "damage.h"

#include "../../../UnitManager/unit_manager.h"

CDamage::CDamage(IGameObject* parent)
	// paretn(CEffectManager)
	: IEffect(parent,"DamageEffect")
{
}

void CDamage::Initialize(void)
{
	// プレイヤーがこのクラスオブジェクトを呼び出した場合は赤いダメージ演出を行う
	if (m_Category == CATEGORY_ID::PLAYER)
		m_EffectSprite.Create("data/texture/others/damage.png");

	// エネミーがこのクラスオブジェクトを呼び出した場合は白いダメージ演出を行う
	if (m_Category == CATEGORY_ID::ENEMY)
		m_EffectSprite.Create("data/texture/others/white_out.png");

	// スプライトのブレンドモードを（加算合成）にする
	m_EffectSprite.blend_mode = aqua::ALPHABLEND::ADD;
}

void CDamage::Update(void)
{
	// 徐々に透明にする
	m_EffectSprite.color.alpha--;

	// 画像が完全に透明になったとき、このクラスオブジェクトを削除する
	if (m_EffectSprite.color.alpha <= 0) IGameObject::DeleteObject();
}