#include "Ripple.h"

const int CRipple::m_vertex_count			= 36;
const float CRipple::m_thickness			= 5.0f;
const int CRipple::m_ripple_alpha			= 100;
const float CRipple::m_move_speed			= 5.0f;
const float CRipple::m_max_ripple_radius	= 99.0f;

CRipple::CRipple(aqua::IGameObject* parent)
	// parent(CEffectManager)
	: IEffect(parent, "Ripple")
	, m_RippleRadius(0.0f)
{
}

void CRipple::Initialize(void)
{
	// 波紋生成（位置、半径、画数（３６角形の円）、色、塗りつぶしフラグ、太さ）
	m_RippleEffect.Setup(m_Position, m_RippleRadius, m_vertex_count, m_RippleColor, false, m_thickness);

	// 波紋の透明度設定
	m_RippleColor.alpha = m_ripple_alpha;

	// 波紋のブレンドモードを加算合成にする
	m_RippleEffect.blend_mode = aqua::ALPHABLEND::ADD;
}

void CRipple::Update(void)
{
	// 波紋の半径を徐々に広げていく
	m_RippleRadius++;

	// 徐々に波紋を透明にしていく
	m_RippleColor.alpha--;

	// 波紋を移動させる
	m_Position.x -= m_move_speed;

	// 波紋の更新を行う
	m_RippleEffect.Setup(m_Position, m_RippleRadius, m_vertex_count, m_RippleColor, false, m_thickness);

	// 波紋が一定の大きさになったら削除する
	if (m_max_ripple_radius < m_RippleRadius) IGameObject::DeleteObject();
}

void CRipple::Draw(void)
{
	m_RippleEffect.Draw();
}