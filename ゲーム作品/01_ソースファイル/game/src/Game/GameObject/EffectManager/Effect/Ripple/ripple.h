#pragma once

#include "../effect.h"

class CRipple : public IEffect
{
public: // ���J�����o�֐�

	// �R���X�g���N�^
	CRipple			(IGameObject* parent);

	// �f�X�g���N�^
	~CRipple		()		override = default;

	// ������
	void Initialize	(void)	override;

	// �X�V
	void Update		(void)	override;

	// �`��
	void Draw		(void)	override;

private: // ����J�����o�ϐ�

	// �g��i�~�j�`��N���X
	aqua::CCirclePrimitive	m_RippleEffect;

	// �g��̐F
	aqua::CColor			m_RippleColor;

	// �g��i�~�j�̔��a
	float m_RippleRadius;

private: // ����J�����o�萔

	static const int m_vertex_count;
	static const float m_thickness;
	static const int m_ripple_alpha;
	static const float m_move_speed;
	static const float m_max_ripple_radius;
};