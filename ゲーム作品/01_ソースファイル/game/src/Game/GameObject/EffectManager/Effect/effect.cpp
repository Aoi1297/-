#include "effect.h"

IEffect::IEffect(aqua::IGameObject* parent, const std::string& object_name)
	// parent(CEffectManager)
	: IGameObject(parent, object_name)
{
}

void IEffect::SetStatus(const aqua::CVector2& create_pos, const CATEGORY_ID& category)
{
	// �G�t�F�N�g�̐����ʒu�ݒ�
	m_Position = create_pos;

	// �����҂̃J�e�S���[�ݒ�
	m_Category = category;

	// ���������s���i�摜�������܂܂��j
	Initialize();

	// �G�t�F�N�g�摜�����S�ƂȂ�悤�ɍ��킹��
	m_Position.x -= m_EffectSprite.GetTextureWidth() / 2;
	m_Position.y -= m_EffectSprite.GetTextureHeight() / 2;

	// �G�t�F�N�g�̊�_�𒆐S�ɂ���
	m_EffectSprite.anchor = { (float)m_EffectSprite.GetTextureWidth() / 2,(float)m_EffectSprite.GetTextureHeight() / 2 };
}

void IEffect::Draw(void)
{
	m_EffectSprite.Draw();
}

void IEffect::Finalize(void)
{
	m_EffectSprite.Delete();
}
