#include "laser.h"

#include "../../../UnitManager/unit_manager.h"

const aqua::CVector2 CLaser::m_effect_size = { 1.5f,1.5f };
const float CLaser::m_effect_decrease_size = 0.01f;
const int CLaser::m_effect_decrease_alpha = 7;
const int CLaser::m_effect_delete_alpha = 4;

CLaser::CLaser(IGameObject* parent)
	// parent(CEffectManager)
	: IEffect(parent, "LaserEffect")
{
}

void CLaser::Initialize(void)
{
	// �����_���Ő�������F��ύX����

	// �v���C���[���z�[�~���O�e��������ꍇ
	if (m_Category == CATEGORY_ID::PLAYER)
	{
		if (aqua::Rand(1))
		{
			// �F�̃G�t�F�N�g�𐶐�����
			m_EffectSprite.Create("data/texture/effect/laser_blue.png");
		}
		else
		{
			// �ΐF�̃G�t�F�N�g�𐶐�����
			m_EffectSprite.Create("data/texture/effect/laser_blue.png");
		}
	}

	// �G���z�[�~���O��������ꍇ
	if (m_Category == CATEGORY_ID::ENEMY)
	{
		if (aqua::Rand(1))
		{
			// ���F�̃G�t�F�N�g�𐶐�����
			m_EffectSprite.Create("data/texture/effect/laser_pink.png");
		}
		else
		{
			// �I�����W�F�̃G�t�F�N�g�𐶐�����
			m_EffectSprite.Create("data/texture/effect/laser_orange.png");
		}
	}

	// �G�t�F�N�g�X�v���C�g�̃u�����h���[�h�����Z�����ɂ���
	m_EffectSprite.blend_mode = aqua::ALPHABLEND::ADD;

	// �G�t�F�N�g�X�v���C�g�̊�_�𒆐S�ɐݒ�
	m_EffectSprite.anchor = { (float)m_EffectSprite.GetTextureWidth() / 2,(float)m_EffectSprite.GetTextureHeight() / 2 };

	// �G�t�F�N�g�̃T�C�Y��ݒ�
	m_EffectSprite.scale = m_effect_size;
}

void CLaser::Update(void)
{
	// ���X�ɓ����ɂ���
	m_EffectSprite.color.alpha -= m_effect_decrease_alpha;

	// �����x����薢���ɂȂ����炱�̃N���X�I�u�W�F�N�g���폜����
	if (m_EffectSprite.color.alpha < m_effect_delete_alpha) IGameObject::DeleteObject();

	// �G�t�F�N�g�̃T�C�Y�iY�����̂݁j���X�ɏ���������
	m_EffectSprite.scale.y -= m_effect_decrease_size;

	// �G�t�F�N�g�̈ʒu�X�V
	m_EffectSprite.position = m_Position;
}

void CLaser::Draw(void)
{
	m_EffectSprite.Draw();
}

void CLaser::Finalize(void)
{
	m_EffectSprite.Delete();
}
