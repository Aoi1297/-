#pragma once

#include "../effect.h"

class CDeadEnemy : public IEffect
{
public: // 公開メンバ関数

	// コンストラクタ
	CDeadEnemy		(IGameObject* parent);

	// デストラクタ
	~CDeadEnemy		(void) = default;

	// 初期化関数
	void Initialize	(void)	override;

	// 更新関数
	void Update		(void)	override;

	// 描画関数
	void Draw		(void)	override;

	// 解放関数
	void Finalize	(void)	override;

private: // 非公開メンバ変数

	// エフェクトを発光させるスプライト
	aqua::CSprite m_EffectFlash;

private: // 非公開メンバ定数

	static const float	m_easing_time;
	static const float	m_max_size;
	static const float	m_start_size;
	static const float	m_final_size;
	static const float	m_max_angle;
	static const int	m_add_alpha;
};