#pragma once

#include "aqua.h"

// 前方宣言
enum class CATEGORY_ID;

class IEffect : public aqua::IGameObject
{
public: // 公開メンバ関数

	// コンストラクタ
	IEffect(IGameObject* parent, const std::string& object_name);

	// デストラクタ
	~IEffect				(void)	override = default;

	// 初期設定
	void SetStatus			(const aqua::CVector2& create_pos, const CATEGORY_ID& category);

	// 描画関数
	virtual void Draw		(void)	override;

	// 解放関数
	virtual void Finalize	(void)	override;

protected: // 限定公開メンバ変数

	// エフェクトスプライト
	aqua::CSprite	m_EffectSprite;

	// エフェクトの位置
	aqua::CVector2	m_Position;

	// 効果時間
	aqua::CTimer	m_EasingTimer;

	// 敵かプレイヤーかのカテゴリー
	CATEGORY_ID		m_Category;

};