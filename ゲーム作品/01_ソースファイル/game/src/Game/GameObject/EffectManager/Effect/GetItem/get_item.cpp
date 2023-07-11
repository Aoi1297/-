#include "get_item.h"

#include "../../../SoundManager/sound_creater.h"

const float CGetItem::m_easing_time = 2.0f;
const float CGetItem::m_max_size	= 10.0f;
const float CGetItem::m_start_size	= 6.0f;
const float CGetItem::m_final_size	= 0.0f;
const float CGetItem::m_max_angle	= 720.0f;
const int CGetItem::m_add_alpha		= 10;

CGetItem::CGetItem(IGameObject* parent)
	// parent(CEffectManager)
	: IEffect(parent, "GetItemEffect")
	, GetItemFlag(false)
{
}

void CGetItem::Initialize(void)
{
	// �G�t�F�N�g�X�v���C�g�𐶐�
	m_EffectSprite.Create("data/texture/effect/item.png");

	// �G�t�F�N�g�X�v���C�g�͕s�����ɂ��Ă���
	m_EffectSprite.color.alpha = 0;

	// �G�t�F�N�g�X�v���C�g�̊�_�𒆐S�ɂ���
	m_EffectSprite.anchor = { (float)m_EffectSprite.GetTextureWidth() / 2, (float)m_EffectSprite.GetTextureHeight() / 2 };

	// �����p�G�t�F�N�g�X�v���C�g�̐���
	m_EffectFlash.Create("data/texture/effect/item_grow.png");

	// �����p�G�t�F�N�g�X�v���C�g�̊�_�𒆐S�ɂ���
	m_EffectFlash.anchor = m_EffectSprite.anchor;

	// �����p�G�t�F�N�g�X�v���C�g�ɂڂ��������������Ȃ�
	m_EffectFlash.ApplyGaussFilter(32, 1000);

	// �����p�G�t�F�N�g�X�v���C�g�̃u�����h���[�h�����Z�����ɂ���
	m_EffectFlash.blend_mode = aqua::ALPHABLEND::ADD;

	m_EasingTimer.Setup(m_easing_time);

	// ���ʉ���炷
	((CSoundCreater*)aqua::FindGameObject("SoundManager"))->Play(SOUND_ID::EFFECT_ITEM);
}

void CGetItem::Update(void)
{
	// // �C�[�W���O�^�C�}�[�̍X�V
	m_EasingTimer.Update();

	// // �G�t�F�N�g�X�v���C�g�����X�ɕs�����ɂ��Ă���
	m_EffectSprite.color.alpha += m_add_alpha;

	// // ���X�ɏ������Ȃ�悤�ɃC�[�W���O��������
	m_EffectFlash.scale.x = m_EffectSprite.scale.x = aqua::easing::InOutBack(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), m_start_size, m_final_size, m_max_size);
	m_EffectFlash.scale.y = m_EffectSprite.scale.y = aqua::easing::InOutBack(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), m_start_size, m_final_size, m_max_size);

	// // �G�t�F�N�g�̉�]���C�[�W���O���g�p���čs��
	m_EffectFlash.rotation = m_EffectSprite.rotation = aqua::DegToRad(aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), 0, m_max_angle));

	// �G�t�F�N�g�T�C�Y��0.1�ȉ��ɂȂ�����N���X�I�u�W�F�N�g�̍폜���s��
	if (m_EffectFlash.scale.x <= 0.1) IGameObject::DeleteObject();

	// �G�t�F�N�g�X�v���C�g�̈ʒu�X�V
	m_EffectSprite.position = m_EffectFlash.position = m_Position;
}

void CGetItem::Draw(void)
{
	m_EffectSprite.Draw();

	m_EffectFlash.Draw();
}

void CGetItem::Finalize(void)
{
	m_EffectFlash.Delete();

	m_EffectSprite.Delete();
}
