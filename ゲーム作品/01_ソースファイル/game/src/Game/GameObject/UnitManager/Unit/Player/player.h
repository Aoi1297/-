#pragma once

#include "aqua.h"

#include "../unit.h"

// �O���錾
enum class BULLET_ID;
enum class ITEM_ID;

enum class DIRECTION_ID
{
	FRONT,
	DOUBLE,
	TRIPLE,
	QUAD,
	DOUBLE_DOUBLE,
	TRIPLE_TRIPLE,
	QUAD_QUAD,
	FINAL,
};

enum class POWER_UP_ID
{
	DIRECTION,
	SPEED,
	INTERVAL,
	LASER,
};

class CPlayer : public IUnit
{
public:	// ���J�I�[�o�[���C�h�֐�

	// �R���X�g���N�^
	CPlayer			(IGameObject* parent);

	// �f�X�g���N�^
	~CPlayer		(void)	override = default;

	// �������֐�
	void Initialize	(void)	override;

	// �X�V�֐�
	void Update		(void)	override;

public:	// ���J�����o�֐�

	// �A�C�e���擾���ʏ���
	void		 PowerUp		(ITEM_ID item_id);

	// ���[�U�[�������t���O
	inline void  SetLaserFlag	(void) { m_LaserShotFlag = true; };

	// ���[�U�[�|�C���g�擾
	inline int   GetLaserPoint	(void) { return m_LaserPoint; };

	// ���[�U�[�������t���O�擾
	inline bool  GetLaserFlag	(void) { return m_LaserShotFlag; };

	// �v���C���[�̗͎擾
	inline int   GetHitPoint	(void) { return m_LifePoint; };

	// �v���C���[�ő�̗�
	inline int   GetMaxHitPoint(void) { return m_max_life_point; };

	// ���E�s�Ǐ�Ԃɐݒ�i�t���O�j
	inline void  SetDarknessFlag(void) { m_DarknessFlag = true; };

	// ���E�s�Ǐ�ԃt���O�擾
	inline bool	 GetDarknessFlag(void) { return m_DarknessFlag; };

	// ���[�U�[���Ԏ擾
	inline float GetLaserTime	(void) { return m_laser_time; };

	// �O���G�t�F�N�g�t���O�擾
	inline bool  GetEffectFlag	(void) { return m_EffectFlag; };

	// �����蔻��擾
	float		 GetRadius(void)override;

private: // ����J�����o�֐�

	// �v���C���[����
	void Controller	(void);

	// �e���ˏ���
	void Fire		(void);

private: // ����J�����o�ϐ�

	// �^�C�}�[�ϐ�
	aqua::CTimer	m_FireInterval;	// !< �e���ˊԊu
	aqua::CTimer	m_DarknessTimer;// !< ���E�s�ǎ���
	aqua::CTimer	m_LaserTimer;	// !< ���[�U�[���ˎ���

	DIRECTION_ID	m_DirectionId;	// !< �e����ID
	float			m_ShotInterval;	// !< ���ˊԊu
	int				m_LaserPoint;	// !< ���[�U�[�|�C���g
	float			m_LaserSpeed;	// !< ���[�U�[�X�s�[�h
	int				m_ShotSpeed;	// !< �e�̑��x
	bool			m_LaserShotFlag;// !< ���[�U�[���˒��t���O
	bool			m_DarknessFlag;	// !< ���E�s�Ǐ�ԃt���O
	bool			m_EffectFlag;	// !< �O���G�t�F�N�g�t���O

private: // ����J�����o�萔

	static const int			m_max_life_point;		// !< �v���C���[�̍ő�̗�
	static const float			m_move_speed;			// !< �v���C���[�̈ړ����x
	static const float			m_max_laser_speed;		// !< �ő僌�[�U�[���x
	static const float			m_max_shot_interval;	// !< �ő唭�ˊԊu
	static const float			m_start_shot_interval;	// !< �����i�K���ˊԊu
	static const DIRECTION_ID	m_start_direction_id;	// !< �����i�K����ID
	static const BULLET_ID		m_start_bullet_id;		// !< �����i�K���˒eID
	static const float			m_start_laser_speed;	// !< �����i�K���[�U�[�X�s�[�h
	static const float			m_normal_bullet_speed;	// !< �e���ˑ��x
	static const float			m_iecrease_interval;	// !< ���ˊԊu�̌�����
	static const float			m_laser_time;			// !< ���[�U�[����
	static const float			m_darkness_time;		// !< ���E�s�ǎ���
	static const float			m_add_speed;			// !< ���[�U�[�X�s�[�h�������x
	static const int			m_bonus_score;			// !< �{�[�i�X�X�R�A
	static const float			m_limit_position_x;		// !< ���E�ړ��\�ʒu�iX�j
	static const float			m_limit_position_y;		// !< ���E�ړ��\�ʒu�iY�j
	static const float			m_random_angle;			// !< �e���Ԃ��p�x
	static const float			m_first_angle;			// !< �P�ڂ̒ǉ�����
	static const float			m_second_angle;			// !< �Q�ڂ̒ǉ�����
	static const float			m_third_angle;			// !< �R�ڂ̒ǉ�����
	static const float			m_fourth_angle;			// !< �S�ڂ̒ǉ�����
	static const float			m_fifth_angle;			// !< �T�ڂ̒ǉ�����
	static const float			m_fifth_angle;			// !< �T�ڂ̒ǉ�����
	static const float			m_sixth_angle;			// !< �U�ڂ̒ǉ�����
};