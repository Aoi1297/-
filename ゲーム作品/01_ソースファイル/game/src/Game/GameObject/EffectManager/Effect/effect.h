#pragma once

#include "aqua.h"

// �O���錾
enum class CATEGORY_ID;

class IEffect : public aqua::IGameObject
{
public: // ���J�����o�֐�

	// �R���X�g���N�^
	IEffect(IGameObject* parent, const std::string& object_name);

	// �f�X�g���N�^
	~IEffect				(void)	override = default;

	// �����ݒ�
	void SetStatus			(const aqua::CVector2& create_pos, const CATEGORY_ID& category);

	// �`��֐�
	virtual void Draw		(void)	override;

	// ����֐�
	virtual void Finalize	(void)	override;

protected: // ������J�����o�ϐ�

	// �G�t�F�N�g�X�v���C�g
	aqua::CSprite	m_EffectSprite;

	// �G�t�F�N�g�̈ʒu
	aqua::CVector2	m_Position;

	// ���ʎ���
	aqua::CTimer	m_EasingTimer;

	// �G���v���C���[���̃J�e�S���[
	CATEGORY_ID		m_Category;

};