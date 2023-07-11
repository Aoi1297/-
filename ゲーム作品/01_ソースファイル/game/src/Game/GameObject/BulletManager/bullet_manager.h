#pragma once

#include "aqua.h"

enum class BULLET_ID
{
	NORMAL,
	HOMING,
	FIREWORK,
	DIRECTION,
};

// �O���錾
class CUnitManager;
enum class CATEGORY_ID;

class CBulletManager : public aqua::IGameObject
{
public: // ���J�����o�֐�

	// �R���X�g���N�^
	CBulletManager	(IGameObject* parent);

	// �f�X�g���N�^
	~CBulletManager	(void)	override = default;

	// �������֐�
	void Initialize	(void)	override;

	// �X�V�֐�
	void Update		(void)	override;

	// �`��֐�
	void Draw		(void)	override;

	// ����֐�
	void Finalize	(void)	override;

public: // ���J�����o�֐�

	// �e�����֐�
	void CreateBullet(const CATEGORY_ID& category_id, const BULLET_ID& bullet_id, const aqua::CVector2& center_position, const float& bullet_speed, const float& direction);

private: // ����J�����o�ϐ�

	// ���j�b�g�}�l�[�W���[�N���X�I�u�W�F�N�g�̃|�C���^�ϐ�
	CUnitManager* m_UnitManager_P;
};