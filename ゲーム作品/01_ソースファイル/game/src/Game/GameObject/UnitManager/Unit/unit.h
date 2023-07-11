#pragma once

#include "aqua.h"

// �O���錾
class		IBullet;
class		IItem;
class		CGameMain;
class		CUiManager;
class		CPlayer;
class		CEffectManager;
class		CCameraManager;
class		CBulletManager;
class		CUIScore;
class		CItemManager;
class       CSoundCreater;
enum class	UNIT_ID;
enum class	CATEGORY_ID;
enum class  BULLET_ID;

class IUnit : public aqua::IGameObject
{
public: // ���J�����o�֐�

	// �R���X�g���N�^
	IUnit								(IGameObject* parent, const std::string& object_name);

	// �f�X�g���N�^
	~IUnit								(void)	override = default;

	// �摜�ݒ�
	void			CreateSprite		(const std::string& sprite_file_name);

	// �X�e�[�^�X�ݒ�
	void			SetStatus			(const UNIT_ID& unit_id, const CATEGORY_ID& unit_category_id, const aqua::CVector2& create_pos);

	// �`��֐�
	virtual void	Draw				(void);

	// ����֐�
	virtual void	Finalize			(void);

	// �e�ƃ��j�b�g�̓����蔻��
	void			CheckHitBullet		(IBullet* bullet);

	// ���j�b�g�ƃA�C�e���̓����蔻��
	void			CheckHitItem		(IItem* item);

	// ���j�b�g�̒��S�ʒu�̎擾
	aqua::CVector2	GetCenterPosition	(void);

	// ���j�b�g�̃J�e�S���[�̎擾
	CATEGORY_ID		GetCategory			(void);

	// ���j�b�g�摜�̉���
	float			GetSpriteWidth		(void);

	//�@���j�b�g�̓����蔼�a�擾 
	virtual float	GetRadius			(void) = 0;

	// �v���C���[�̃|�C���^���擾
	void			SetPlayerPointer	(void);

protected: // ������J�����o�ϐ�

	// ���j�b�g�X�v���C�g
	aqua::CSprite	m_UnitSprite;

	// ���j�b�g�ʒu
	aqua::CVector2	m_Position;

	// ���j�b�g�̃��C�t
	int m_LifePoint;

	// ���j�b�g�̈ړ����x
	float m_MoveSpeed;

	// ���j�b�g�̒e���ˑ��x
	float m_ShotSpeed;

	// ���e�̎��
	BULLET_ID m_ShotKind;

	// ���j�b�g��ID
	UNIT_ID m_UnitId;

	// ���j�b�g�̓G�������ʎq
	CATEGORY_ID m_UnitCategory;

	// �N���X�|�C���^�ϐ�
	CGameMain*		m_GameMain_P;		// !< �Q�[�����C���N���X
	CUiManager*		m_UiManager_P;		// !< ���j�b�g�}�l�[�W���[�N���X
	CPlayer*		m_Player_P;			// !< �v���C���[�N���X
	CEffectManager* m_EffectManager_P;	// !< �G�t�F�N�g�}�l�[�W���[�N���X
	CCameraManager* m_CameraManager_P;	// !< �J�����}�l�[�W���[�N���X
	CUIScore*		m_Score_P;			// !< �X�R�A�N���X
	CItemManager*	m_ItemManager_P;	// !< �A�C�e���}�l�[�W���[�N���X
	CBulletManager* m_BulletManager_P;	// !< �o���b�g�}�l�[�W���[�N���X�|�C���^�̎擾
	CSoundCreater*  m_SoundManager_P;	// !< �T�E���h�}�l�[�W���[�N���X�|�C���^�̎擾

private: // ����J�����o�萔

	static const int m_get_item_score;	// !< �A�C�e���擾���̊l���X�R�A
	static const int m_defeat_score;	// !< �G���j���̊l���X�R�A
	static const float m_item_hit_radius;	// !< �A�C�e���Ƃ̓����蔻��
};