#include "effect.h"

IEffect::IEffect(aqua::IGameObject* parent, const std::string& object_name)
	// parent(CEffectManager)
	: IGameObject(parent, object_name)
{
}

void IEffect::SetStatus(const aqua::CVector2& create_pos, const CATEGORY_ID& category)
{
	// エフェクトの生成位置設定
	m_Position = create_pos;

	// 生成者のカテゴリー設定
	m_Category = category;

	// 初期化を行う（画像生成も含まれる）
	Initialize();

	// エフェクト画像が中心となるように合わせる
	m_Position.x -= m_EffectSprite.GetTextureWidth() / 2;
	m_Position.y -= m_EffectSprite.GetTextureHeight() / 2;

	// エフェクトの基準点を中心にする
	m_EffectSprite.anchor = { (float)m_EffectSprite.GetTextureWidth() / 2,(float)m_EffectSprite.GetTextureHeight() / 2 };
}

void IEffect::Draw(void)
{
	m_EffectSprite.Draw();
}

void IEffect::Finalize(void)
{
	m_EffectSprite.Delete();
}
