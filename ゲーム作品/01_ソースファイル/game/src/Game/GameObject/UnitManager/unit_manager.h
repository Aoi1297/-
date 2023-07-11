#pragma once

#include "aqua.h"

// �O���錾
class IBullet;
class IItem;
class IUnit;
class CGameMain;
class CSoundCreater;

// ���j�b�g��ID
enum class UNIT_ID
{
	PLAYER,				// �v���C���[�i���삷��@�́j
	NORMAL,				// �p�ɂɓo�ꂷ��G
	FIRE_WORK,			// �ԉ΂̂悤�Ȓe����G
	STAR,				// ���`�̎��@�_���e����G
	MINI_BOSS,			// ���{�X
	NORMAL_TOUGH,		// NORML�̋�����
	FIRE_WORK_TOUGH,	// FIRE_WORK�̋�����
	FINAL_BOSS,			// ���X�{�X

	MAX,				// ���j�b�g��
};

// ���j�b�g�̃J�e�S���[ID
enum class CATEGORY_ID
{
	PLAYER,	// �v���C���[
	ENEMY,	// �G���j�b�g
	BOSS,	// �{�X���j�b�g

	MAX,	// �J�e�S���[��
};

// CSV�t�@�C������擾����G�f�[�^
struct ENEMY_DATA
{
	UNIT_ID			unit_id;	 // ���j�b�gID
	aqua::CVector2	position;	 // �����ʒu
	float			create_time; // ��������
};

class CUnitManager : public aqua::IGameObject
{
public:	// ���J�����o�֐�

	// �R���X�g���N�^
	CUnitManager	(IGameObject* parent);

	// �f�X�g���N�^
	~CUnitManager	(void) = default;

	// �������֐�
	void Initialize	(void)	override;

	// �X�V�֐�
	void Update		(void)	override;

	// �`��֐�
	void Draw		(void)	override;

	// ����֐�
	void Finalize	(void)	override;

public: // ����J�����o�֐�

	// �G���j�b�g�����֐�
	void CreateUnit		(const UNIT_ID& unit_id, const aqua::CVector2& create_position);

	// ���j�b�g�̔���m�F
	void CheckUnit		(IBullet* bullet);

	// �v���C���[�ƃA�C�e���̔���m�F
	void CheckUnit		(IItem* item);

	// �����ɗ^����ꂽ�e�����ԋ߂��G���j�b�g��T��
	IUnit* FindNearUnit	(IBullet* bullet);

private: // ����J�����o�֐�

	// CSV�t�@�C�����
	void Parse			(const std::string& csv_file_name);

	// �G�z��
	void DeployEnemy	(void);

private: // ����J�����o�ϐ�

	// CSV�G�f�[�^�\����
	std::vector<ENEMY_DATA> m_EnemyTable;

	// �Q�[�����C���N���X�|�C���^
	CGameMain*				m_GameMain_P;

	// �T�E���h�N���X�|�C���^
	CSoundCreater*			m_SoundManager_P;
};