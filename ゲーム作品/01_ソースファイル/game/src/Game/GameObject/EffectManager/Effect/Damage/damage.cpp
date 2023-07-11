#include "damage.h"

#include "../../../UnitManager/unit_manager.h"

CDamage::CDamage(IGameObject* parent)
	// paretn(CEffectManager)
	: IEffect(parent,"DamageEffect")
{
}

void CDamage::Initialize(void)
{
	// �v���C���[�����̃N���X�I�u�W�F�N�g���Ăяo�����ꍇ�͐Ԃ��_���[�W���o���s��
	if (m_Category == CATEGORY_ID::PLAYER)
		m_EffectSprite.Create("data/texture/others/damage.png");

	// �G�l�~�[�����̃N���X�I�u�W�F�N�g���Ăяo�����ꍇ�͔����_���[�W���o���s��
	if (m_Category == CATEGORY_ID::ENEMY)
		m_EffectSprite.Create("data/texture/others/white_out.png");

	// �X�v���C�g�̃u�����h���[�h���i���Z�����j�ɂ���
	m_EffectSprite.blend_mode = aqua::ALPHABLEND::ADD;
}

void CDamage::Update(void)
{
	// ���X�ɓ����ɂ���
	m_EffectSprite.color.alpha--;

	// �摜�����S�ɓ����ɂȂ����Ƃ��A���̃N���X�I�u�W�F�N�g���폜����
	if (m_EffectSprite.color.alpha <= 0) IGameObject::DeleteObject();
}