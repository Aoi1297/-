#pragma once

#include "aqua.h"

// 前方宣言
enum class CATEGORY_ID;

enum class EFFECT_ID
{
	RIPPLES,
	DARKNESS,
	DAMAGE,
	BULLET_SPAWN,
	LASER,
	GETITEM,
	DEAD_ENEMY,
};

class CEffectManager : public aqua::IGameObject
{
public: // 公開メンバ関数

	// コンストラクタ
	CEffectManager	(IGameObject* parent);

	// デストラクタ
	~CEffectManager	()		override = default;

	// 更新関数
	void Update		(void)	override;

	// 描画関数
	void Draw		(void)	override;

	// 解放関数
	void Finalize	(void)	override;

public: // 非公開メンバ関数

	// エフェクト生成
	void CreateEffect(const EFFECT_ID& effect_id, const aqua::CVector2& create_pos,const CATEGORY_ID& category);
};