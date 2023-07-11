#pragma once

#include "aqua.h"

#include "../../scene_manager.h"

// �p�[�e�B�N���f�[�^�\����
struct PARTICLE_DATA
{
	aqua::CVector2	position;	// �p�[�e�B�N���ʒu
	aqua::CVector2	scale;		// �T�C�Y
	float			angle;		// �p�x
};

class CTitle : public IScene
{
public:	// ���J�����o�֐�

	// �R���X�g���N�^
	CTitle			(IGameObject* parent);

	// �f�X�g���N�^
	~CTitle			(void) = default;

	// �������֐�
	void Initialize	(void)	override;

	// �X�V�֐�
	void Update		(void)	override;

	// �`��֐�
	void Draw		(void)	override;

	// ����֐�
	void Finalize	(void)	override;

private: // ����J�����o�֐�

	// �L�[�`�F�b�N�֐�
	void CheckKeyZ		(void);

	// �^�C�}�[�X�V
	void TimerUpdate	(void);

	// �p�[�e�B�N���ړ�
	void ParticleMove	(void);

private: // ����J�����o�ϐ�

	// �X�v���C�g�ϐ�
	aqua::CSprite				m_ParticleSprite;			// !< �p�[�e�B�N���摜
	aqua::CSprite				m_ParticleEffectSprite;		// !< �p�[�e�B�N���G�t�F�N�g�摜
	aqua::CSprite				m_TitleSprite;				// !< �^�C�g���摜
	aqua::CSprite				m_TitleEffectSprite;		// !< �^�C�g���G�t�F�N�g�摜
	aqua::CSprite				m_TitleMassageSprite;		// !< �^�C�g�����b�Z�[�W�摜
	aqua::CSprite				m_TitleMassageEffectSprite;	// !< �^�C�g�����b�Z�[�W�G�t�F�N�g�摜
	aqua::CSprite				m_FlashScreenSprite;		// !< ��ʃt���b�V���摜

	// �^�C�}�[�ϐ�
	aqua::CTimer				m_FlashScreenTimer;			// !< ��ʃt���b�V���^�C�}�[
	aqua::CTimer				m_FlashObjectTimer;			// !< �I�u�W�F�N�g�t���b�V���^�C�}�[

	// �|�C���^�ϐ�
	CSceneManager*				m_SceneManager_P;			// !< �V�[���}�l�[�W���[�N���X�|�C���^

	std::vector<PARTICLE_DATA>	m_ParticleDataList;			// !< �p�[�e�B�N���f�[�^�\���̃��X�g

private: // �ÓI�����o�萔

	static const unsigned char	m_max_random_color;			// !< �J���[�ő僉���_���l
	static const int			m_pixel_width;				// !< �ڂ������i�P�O�O�łP�s�N�Z���j
	static const int			m_param;					// !< �ڂ����̋���
	static const aqua::CVector2 m_title_scale;				// !< �^�C�g���T�C�Y
	static const float			m_title_position_y;			// !< �^�C�g���ʒu�iY���W�j
	static const float			m_title_massage_position_y;	// !< �^�C�g�����b�Z�[�W�iY���W�j
	static const float			m_title_massage_scale_up;	// !< �^�C�g�����b�Z�[�W�g���
	static const int			m_particle_quantity;		// !< �p�[�e�B�N����
	static const int			m_particle_random_scale_max;// !< �p�[�e�B�N���ő�T�C�Y
	static const int			m_particle_random_angle_max;// !< �p�[�e�B�N���ő�p�x
	static const float			m_flash_screen_time;		// !< ��ʃt���b�V������
	static const float			m_flash_object_time;		// !< �I�u�W�F�N�g�t���b�V���Ԋu
};