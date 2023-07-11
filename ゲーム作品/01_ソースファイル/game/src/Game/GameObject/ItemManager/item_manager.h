#pragma once

#include "aqua.h"

// �A�C�e��ID
enum class ITEM_ID
{
	LASER,
	SPEED,
	DIRECTION,
	INTERVAL,

	MAX,
};

// �O���錾
class CUnitManager;

class CItemManager : public aqua::IGameObject
{
public: // ���J�����o���z�֐�

	// �R���X�g���N�^
	CItemManager	(IGameObject* parent);

	// �f�X�g���N�^
	~CItemManager	(void)	override = default;

	// �������֐�
	void Initialize	(void)	override;

	// �X�V�֐�
	void Update		(void)	override;

	// �`��֐�
	void Draw		(void)	override;

	// ����֐�
	void Finalize	(void)	override;

public: // ���J�����o�֐�

	// �A�C�e������
	void CreateItem(const ITEM_ID& item_id,const aqua::CVector2& create_pos);

private: // ����J�����o�ϐ�

	// ���j�b�g�}�l�[�W���[�N���X�|�C���^
	CUnitManager* m_UnitManager_P;
};