#pragma once

#include "aqua.h"

#include "../enemy.h"

// �O���錾
class CUnitManager;

class CFinalBoss : public IEnemy
{
public:	// ���J�I�[�o�[���C�h�֐�

	// �R���X�g���N�^
	CFinalBoss(IGameObject* parent);

	// �f�X�g���N�^
	~CFinalBoss		(void)	override = default;

	// �������֐�
	void Initialize	(void)  override;

	// �X�V�֐�
	void Update		(void)	override;

	// �`��֐�
	void Draw		(void)	override;

	// ����֐�
	void Finalize	(void)	override;

	// �����蔻��擾
	float GetRadius(void)override;

private: // ����J�����o�֐�

	// �o�����̃G�t�F�N�g
	void SpawanEffect(void)override;

	// ��������
	void Movement(void)override;

	// �ˌ�����
	void Fire(void)override;

private: // ����J�����o�ϐ�

	// ���`�ԗp�X�v���C�g
	aqua::CSprite	m_SecondFormSprite;

	// ���C�����ˊԊu
	aqua::CTimer	m_1stFireTimer;

	// ���C�����ˊԊu
	aqua::CTimer	m_2ndFireTimer;

	// �G�o���^�C�}�[
	aqua::CTimer	m_EnemySpawanTimer;

	// �`�ԕω��ɂ�鏉�������s�����߂̃t���O
	bool			m_FormChangeInitializeFlag;

	// ���j�b�g�}�l�[�W���[�N���X�I�u�W�F�N�g�̃|�C���^�ϐ�
	CUnitManager*	m_UnitManager_P;

private: // ����J�����o�萔

	static const int			m_max_life_point;		// !< ���j�b�g�ő�̗�
	static const float			m_fire_interval;		// !< �ˌ��Ԋu
	static const float			m_enemy_spawan_interval;// !< �G���G�o���Ԋu
	static const float			m_easing_time;			// !< �o�����̃C�[�W���O����
	static const aqua::CVector2 m_unit_scale;			// !< ���j�b�g�T�C�Y
	static const aqua::CVector2	m_max_scale;			// !< ���j�b�g�ő�T�C�Y
	static const float			m_random_angle;			// !< �e�̃u���̍ő�p�x
	static const float			m_rotation_angle;		// !< ���j�b�g�̉�]�p�x
	static const float			m_shot_speed;			// !< �e�̑��x
	static const float			m_move_acceleration;	// !< ���j�b�g�̉����x
	static const float			m_hit_radius;			// !< ���j�b�g�̓����蔻��
	static const float			m_1st_angle;			// !< ���`�ԉ�]�p�x
	static const float			m_one;					// !< 1.0f�̑����p�̒l
	static const float			m_spawan_position_y;	// !< �G�o���Œ�ʒu
	static const float			m_spawan_random_num;	// !< �o�����̍ő僉���_���l
	static const int			m_1st_change_hp;		// !< ���ڂ̌`�ԕω��Ɏ���܂ł�HP
	static const int			m_2nd_change_hp;		// !< ���ڂ̌`�ԕω��Ɏ���܂ł�HP
	static const int			m_3rd_change_hp;		// !< �O��ڂ̌`�ԕω��Ɏ���܂ł�HP
	static const int			m_4th_change_hp;		// !< �l��ڂ̌`�ԕω��Ɏ���܂ł�HP
	static const int			m_5th_change_hp;		// !< �܉�ڂ̌`�ԕω��Ɏ���܂ł�HP
	static const int			m_6th_change_hp;		// !< �Z��ڂ̌`�ԕω��Ɏ���܂ł�HP
	static const int			m_7th_change_hp;		// !< ����ڂ̌`�ԕω��Ɏ���܂ł�HP
	static const int			m_8th_change_hp;		// !< ����ڂ̌`�ԕω��Ɏ���܂ł�HP
};
