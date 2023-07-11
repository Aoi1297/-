#pragma once

#include "aqua.h"

#include "../../UnitManager/Unit/unit.h"

// �O���錾
class CEffectManager;
enum class CATEGORY_ID;

class IBullet : public aqua::IGameObject
{
public: // ���J�����o�֐�

	// �R���X�g���N�^
	IBullet								(IGameObject* parent, const std::string& object_name);

	// �f�X�g���N�^
	~IBullet							(void)	override = default;

	// �������֐�
	void			CreateSprite		(const std::string& sprite_file_name);

	// �������֐�
	void			SetStatus			(const CATEGORY_ID& id, const aqua::CVector2& center_position, const float& bullet_speed, const float& direction);

	// �X�V�֐�
	void			Update				(void);

	// �`��֐�
	virtual void	Draw				(void);

	// ����֐�
	virtual void	Finalize			(void);

	// �e���ꂼ��̓����I�ȓ������s��
	virtual void	OriginalMovement	(void) = 0;

	// �����ɑ΂��Ĕ��ł����e
	void			DirectionMove		(void);

	// �e�̒��S�ʒu�擾
	aqua::CVector2	GetCenterPosition	(void);

	// �e�̃J�e�S���[�擾
	CATEGORY_ID GetCategory();

protected: // ����J�����o�ϐ�

	// �e�̃X�v���C�g
	aqua::CSprite	m_BulletSprite;

	// �e�̈ʒu
	aqua::CVector2	m_Position;

	// �e�����p�̃X�v���C�g
	aqua::CSprite m_FlashSprite;

	//�@���x��
	aqua::CVector2 m_Velocity;

	// �e�̑��x
	float m_BulletSpeed;

	// �e�̊p�x
	float m_Direction;

	// �e�̊p�x
	CATEGORY_ID m_Category;

	// �G�t�F�N�g�}�l�[�W���[�N���X�I�u�W�F�N�g�̃|�C���^�ϐ�
	CEffectManager* m_EffectManager;
};