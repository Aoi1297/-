#include "bullet_spawn.h"

#include "../../../UnitManager/unit_manager.h"

const float CSpawn::m_easing_time	= 0.75f;
const float CSpawn::m_sprite_size	= 0.5f;
const int CSpawn::m_alpha_decrease	= 7;
const int CSpawn::m_delete_num		= 4;

CSpawn::CSpawn(IGameObject* parent)
	// parent(CEffectManager)
	: IEffect(parent, "BulletSpawnEffect")
{
}

void CSpawn::Initialize(void)
{
	// �v���C���[�����������G�t�F�N�g�̏ꍇ
	if (m_Category == CATEGORY_ID::PLAYER)
	{
		// �����_���ŐF�ύX
		if (aqua::Rand(1))
		{
			// �F�̃X�v���C�g�𐶐�
			m_EffectSprite.Create("data/texture/effect/Trajectory_blue.png");
		}
		else
		{
			// �ΐF�̃X�v���C�g�𐶐�
			m_EffectSprite.Create("data/texture/effect/Trajectory_green.png");
		}
	}

	// �G�����������G�t�F�N�g�̏ꍇ
	if (m_Category == CATEGORY_ID::ENEMY)
	{
		// �����_���ŐF�ύX
		if (aqua::Rand(1))
		{
			// �ԐF�̃X�v���C�g�𐶐�
			m_EffectSprite.Create("data/texture/effect/Trajectory_red.png");
		}
		else
		{
			// ���F�̃X�v���C�g�𐶐�
			m_EffectSprite.Create("data/texture/effect/Trajectory_pink.png");
		}
	}

	// �G�t�F�N�g�X�v���C�g�̃u�����h���[�h���i���Z�����j�ɂ���
	m_EffectSprite.blend_mode = aqua::ALPHABLEND::ADD;

	// �C�[�W���O�^�C�}�[�̐ݒ�
	m_EasingTimer.Setup(m_easing_time);

	// �G�t�F�N�g�̃T�C�Y
	m_EffectSprite.scale = { m_sprite_size,m_sprite_size };

	// ��]�l���O�ɐݒ�
	m_Rotation = 0.0f;
}

void CSpawn::Update(void)
{
	// �^�C�}�[���I�����Ă��Ȃ��Ȃ�X�V����
	if (!m_EasingTimer.Finished()) m_EasingTimer.Update();

	// ���X�ɏ������Ȃ�悤�Ȍ��ʂ�^����
	m_EffectSprite.scale.x = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), aqua::CVector2::ONE.x, m_sprite_size);
	m_EffectSprite.scale.y = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), aqua::CVector2::ONE.y, m_sprite_size);

	// ��]�l���{�P����
	m_Rotation++;

	// ��]�l�ɉ����ĉ摜���p�x���X�V����
	m_EffectSprite.rotation += aqua::DegToRad(m_Rotation);

	// �摜�����X�ɓ����ɂ���
	m_EffectSprite.color.alpha -= m_alpha_decrease;

	// ���̒l�����ɂȂ����炱�̃N���X�I�u�W�F�N�g���폜����
	if (m_EffectSprite.color.alpha < m_delete_num) IGameObject::DeleteObject();

	// �G�t�F�N�g�̈ʒu�X�V
	m_EffectSprite.position = m_Position;
}