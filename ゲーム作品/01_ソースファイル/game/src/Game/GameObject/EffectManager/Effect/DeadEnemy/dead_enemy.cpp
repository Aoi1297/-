#include "dead_enemy.h"

#include "../../../SoundManager/sound_creater.h"

const float CDeadEnemy::m_easing_time	= 2.0f;
const float CDeadEnemy::m_max_size		= 10.0f;
const float CDeadEnemy::m_start_size	= 6.0f;
const float CDeadEnemy::m_final_size	= 0.0f;
const float CDeadEnemy::m_max_angle		= 720.0f;
const int CDeadEnemy::	m_add_alpha		= 10;

CDeadEnemy::CDeadEnemy(IGameObject* parent)
	// paretn(CEffectManager)
	: IEffect(parent, "DeadEnemyEffect")
{
}

void CDeadEnemy::Initialize(void)
{
	// ���ʉ���炷
	((CSoundCreater*)aqua::FindGameObject("SoundManager"))->Play(SOUND_ID::EFFECT_DEAD);

	// �j�󎞂ɕ\������G�t�F�N�g�X�v���C�g�̐���
	m_EffectSprite.Create("data/texture/effect/destroy.png");
	m_EffectSprite.color.alpha = 0;

	// �G�t�F�N�g�̊�_�𒆐S�ɂ���
	m_EffectSprite.anchor = { (float)m_EffectSprite.GetTextureWidth() / 2, (float)m_EffectSprite.GetTextureHeight() / 2 };

	// �G�t�F�N�g�𔭌������邽�߂̃X�v���C�g�𐶐�
	m_EffectFlash.Create("data/texture/effect/destroy_grow.png");

	// �����p�G�t�F�N�g�̊�_��ݒ�
	m_EffectFlash.anchor = m_EffectSprite.anchor;

	// �����p�G�t�F�N�g�ɂڂ����������s��
	m_EffectFlash.ApplyGaussFilter(32, 1000);

	// �G�t�F�N�g�̃u�����h���[�h�����Z�����ɂ���
	m_EffectFlash.blend_mode = aqua::ALPHABLEND::ADD;

	// �C�[�W���O�^�C�}�[�̐ݒ�
	m_EasingTimer.Setup(m_easing_time);
}

void CDeadEnemy::Update(void)
{
	// �C�[�W���O�^�C�}�[�̍X�V
	m_EasingTimer.Update();

	// �G�t�F�N�g�X�v���C�g�����X�ɕs�����ɂ��Ă���
	m_EffectSprite.color.alpha += m_add_alpha;

	// ���X�ɏ������Ȃ�悤�ɃC�[�W���O��������
	m_EffectFlash.scale.x = m_EffectSprite.scale.x = aqua::easing::InOutBack(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), m_start_size, m_final_size, m_max_size);
	m_EffectFlash.scale.y = m_EffectSprite.scale.y = aqua::easing::InOutBack(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), m_start_size, m_final_size, m_max_size);

	// �G�t�F�N�g�̉�]���C�[�W���O���g�p���čs��
	m_EffectFlash.rotation = m_EffectSprite.rotation = aqua::DegToRad(aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), 0, m_max_angle));

	// �G�t�F�N�g�T�C�Y��0.1�ȉ��ɂȂ�����N���X�I�u�W�F�N�g�̍폜���s��
	if (m_EffectFlash.scale.x <= 0.1) IGameObject::DeleteObject();

	// �G�t�F�N�g�X�v���C�g�̈ʒu�X�V
	m_EffectSprite.position = m_EffectFlash.position = m_Position;
}

void CDeadEnemy::Draw(void)
{
	m_EffectSprite.Draw();

	m_EffectFlash.Draw();
}

void CDeadEnemy::Finalize(void)
{
	m_EffectFlash.Delete();

	m_EffectSprite.Delete();
}
