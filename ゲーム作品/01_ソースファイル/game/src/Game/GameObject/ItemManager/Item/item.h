#pragma once

#include "aqua.h"

#include "../../ItemManager/item_manager.h"

// �O���錾
class CPlayer;

class IItem : public aqua::IGameObject
{
public: // ���J�����o�֐�

	// �R���X�g���N�^
	IItem(IGameObject* parent, const std::string& object_name);

	// �f�X�g���N�^
	~IItem								(void)	override = default;

	// �A�C�e���X�v���C�g�ݒ�
	void			CreateSprite		(const std::string& sprite_file_name);

	// �X�e�[�^�X�ݒ�
	void			SetStatus			(const ITEM_ID& id, const aqua::CVector2& create_pos);

	// �X�V�֐�
	void			Update				(void)	override;

	// �`��֐�
	void			Draw				(void)	override;

	// ����֐�
	void			Finalize			(void)	override;

	// �A�C�e�����擾
	void			HitItem				(void);

	// �A�C�e���̒��S�ʒu�擾
	aqua::CVector2	GetCenterPosition	(void);

private: // ����J�����o�֐�

	void			TimerUpdate			(void);

	void			SpawanEffect		(void);

	void			Movement			(void);

private: // ����J�����o�ϐ�

	// �v���C���[�N���X�|�C���^�̎擾
	CPlayer* m_Player_P;

	// �A�C�e���X�v���C�g
	aqua::CSprite m_ItemSprite;

	// �o�����̃C�[�W���O�^�C�}�[
	aqua::CTimer m_EasingTimer;

	// ���g�̃A�C�e��ID
	ITEM_ID	m_ItemId;

	// ���g�i�A�C�e���j�̈ʒu
	aqua::CVector2 m_Position;

	// ���g�i�A�C�e���j�̈ړ����x
	float m_MoveSpeed;

private: // ����J�����o�萔

	static const float m_item_move_speed;	// !< �A�C�e���̏����ړ����x
	static const float m_item_acceleration;	// !< �A�C�e���̉����x
	static const float m_easing_timer;		// !< �C�[�W���O����
	static const float m_item_max_scale;	// !< �A�C�e���摜�̍ő�X�P�[��
	static const float m_item_scale;		// !< �A�C�e���摜�̃X�P�[��
};