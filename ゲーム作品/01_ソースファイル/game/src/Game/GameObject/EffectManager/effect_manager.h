#pragma once

#include "aqua.h"

// �O���錾
enum class CATEGORY_ID;

enum class EFFECT_ID
{
	RIPPLES,
	DARKNESS,
	DAMAGE,
	BULLET_SPAWN,
	LASER,
	GETITEM,
	DEAD_ENEMY,
};

class CEffectManager : public aqua::IGameObject
{
public: // ���J�����o�֐�

	// �R���X�g���N�^
	CEffectManager	(IGameObject* parent);

	// �f�X�g���N�^
	~CEffectManager	()		override = default;

	// �X�V�֐�
	void Update		(void)	override;

	// �`��֐�
	void Draw		(void)	override;

	// ����֐�
	void Finalize	(void)	override;

public: // ����J�����o�֐�

	// �G�t�F�N�g����
	void CreateEffect(const EFFECT_ID& effect_id, const aqua::CVector2& create_pos,const CATEGORY_ID& category);
};