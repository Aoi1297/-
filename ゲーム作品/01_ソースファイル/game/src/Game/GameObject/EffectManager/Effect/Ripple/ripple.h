#pragma once

#include "../effect.h"

class CRipple : public IEffect
{
public: // 公開メンバ関数

	// コンストラクタ
	CRipple			(IGameObject* parent);

	// デストラクタ
	~CRipple		()		override = default;

	// 初期化
	void Initialize	(void)	override;

	// 更新
	void Update		(void)	override;

	// 描画
	void Draw		(void)	override;

private: // 非公開メンバ変数

	// 波紋（円）描画クラス
	aqua::CCirclePrimitive	m_RippleEffect;

	// 波紋の色
	aqua::CColor			m_RippleColor;

	// 波紋（円）の半径
	float m_RippleRadius;

private: // 非公開メンバ定数

	static const int m_vertex_count;
	static const float m_thickness;
	static const int m_ripple_alpha;
	static const float m_move_speed;
	static const float m_max_ripple_radius;
};