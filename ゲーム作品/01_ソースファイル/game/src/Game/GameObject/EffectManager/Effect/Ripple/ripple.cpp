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
	// �g�䐶���i�ʒu�A���a�A�搔�i�R�U�p�`�̉~�j�A�F�A�h��Ԃ��t���O�A�����j
	m_RippleEffect.Setup(m_Position, m_RippleRadius, m_vertex_count, m_RippleColor, false, m_thickness);

	// �g��̓����x�ݒ�
	m_RippleColor.alpha = m_ripple_alpha;

	// �g��̃u�����h���[�h�����Z�����ɂ���
	m_RippleEffect.blend_mode = aqua::ALPHABLEND::ADD;
}

void CRipple::Update(void)
{
	// �g��̔��a�����X�ɍL���Ă���
	m_RippleRadius++;

	// ���X�ɔg��𓧖��ɂ��Ă���
	m_RippleColor.alpha--;

	// �g����ړ�������
	m_Position.x -= m_move_speed;

	// �g��̍X�V���s��
	m_RippleEffect.Setup(m_Position, m_RippleRadius, m_vertex_count, m_RippleColor, false, m_thickness);

	// �g�䂪���̑傫���ɂȂ�����폜����
	if (m_max_ripple_radius < m_RippleRadius) IGameObject::DeleteObject();
}

void CRipple::Draw(void)
{
	m_RippleEffect.Draw();
}