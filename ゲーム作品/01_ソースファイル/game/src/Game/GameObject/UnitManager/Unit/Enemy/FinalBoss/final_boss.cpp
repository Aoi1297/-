#include "final_boss.h"

#include "../../../unit_manager.h"
#include "../../../../EffectManager/effect_manager.h"
#include "../../../../SoundManager/sound_creater.h"
#include "../../../../BulletManager/bullet_manager.h"
#include "../../../../InterfaceManager/ui_manager.h"

const int	CFinalBoss::m_max_life_point = 1000;
const float CFinalBoss::m_fire_interval = 0.1f;
const float CFinalBoss::m_enemy_spawan_interval = 2.0f;
const float CFinalBoss::m_easing_time = 0.7f;
const float CFinalBoss::m_random_angle = 6;
const aqua::CVector2 CFinalBoss::m_unit_scale = { 7.0f,7.0f };
const aqua::CVector2 CFinalBoss::m_max_scale = { 15.0f,15.0f };
const float CFinalBoss::m_rotation_angle = 45.0f;
const float CFinalBoss::m_shot_speed = 10.0f;
const float CFinalBoss::m_move_acceleration = 0.04f;
const float CFinalBoss::m_hit_radius = 150.0f;
const float CFinalBoss::m_one = 1.0f;
const float CFinalBoss::m_spawan_position_y = 200.0f;
const float CFinalBoss::m_spawan_random_num = 700.0f;
const float CFinalBoss::m_1st_angle = 1.0f;
const int	CFinalBoss::m_1st_change_hp = 900;
const int	CFinalBoss::m_2nd_change_hp = 800;
const int	CFinalBoss::m_3rd_change_hp = 700;
const int	CFinalBoss::m_4th_change_hp = 600;
const int	CFinalBoss::m_5th_change_hp = 500;
const int	CFinalBoss::m_6th_change_hp = 300;
const int	CFinalBoss::m_7th_change_hp = 200;
const int	CFinalBoss::m_8th_change_hp = 50;

CFinalBoss::CFinalBoss(IGameObject* parent)
	: IEnemy(parent, "FinalBoss")
	, m_FormChangeInitializeFlag(false)
{
}

void CFinalBoss::Initialize(void)
{
	// �摜�̐������ݒ�
	CreateSprite("data/texture/unit/boss_1st_form.png");

	// �{�X���j�b�g�T�C�Y�̐ݒ�
	m_UnitSprite.scale = m_unit_scale;

	// ���`�ԉ摜�̐���
	m_SecondFormSprite.Create("data/texture/unit/boss_2nd_form.png");

	// ���`�ԉ摜�̃u�����h���[�h�����Z�����ɐݒ肷��
	m_SecondFormSprite.blend_mode = aqua::ALPHABLEND::ADD;

	// ���`�ԉ摜�𓧖��ɂ��Ă���
	m_SecondFormSprite.color.alpha = 0;

	// ���`�ԉ摜�̈ʒu��ݒ�
	m_SecondFormSprite.position = m_UnitSprite.position;

	// ���`�ԉ摜�̊�_�𒆐S�ɂ���
	m_SecondFormSprite.anchor = m_UnitSprite.anchor;

	// ���`�ԉ摜�̃T�C�Y��ݒ�
	m_SecondFormSprite.scale = m_UnitSprite.scale;

	// ���j�b�g�̗͐ݒ�
	m_LifePoint = m_max_life_point;

	// �e�̑��x
	m_ShotSpeed = m_shot_speed;

	// �C�[�W���O�^�C�}�[�ݒ�
	m_EasingTimer.Setup(m_easing_time);

	// ���C�����ˊԊu�ݒ�
	m_1stFireTimer.Setup(m_fire_interval);

	// ���C�����ˊԊu�ݒ�
	m_2ndFireTimer.Setup(m_fire_interval);

	// �G�o���^�C�}�[�ݒ�
	m_EnemySpawanTimer.Setup(m_enemy_spawan_interval);

	// ���j�b�g�}�l�[�W���[�N���X�I�u�W�F�N�g�̃|�C���^���擾
	m_UnitManager_P = (CUnitManager*)(aqua::FindGameObject("UnitManager"));

	// �{�X�o�����ɏo�����̈Í��G�t�F�N�g�𐶐�
	m_EffectManager_P->CreateEffect(EFFECT_ID::DARKNESS, GetCenterPosition(), CATEGORY_ID::ENEMY);

	// BGM���~
	((CSoundCreater*)aqua::FindGameObject("SoundManager"))->Stop(SOUND_ID::BGM_GAME);

	// �{�X�pBGM�𐶐�
	((CSoundCreater*)aqua::FindGameObject("SoundManager"))->Play(SOUND_ID::BGM_BOSS);
}

void CFinalBoss::Update(void)
{
	// ���`�ԁ[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
	if (m_LifePoint <= m_1st_change_hp && m_LifePoint >= m_2nd_change_hp)
	{
		// �ˌ��^�C�}�[�X�V
		m_1stFireTimer.Update();

		// �{�X���j�b�g����]������
		m_UnitSprite.rotation += aqua::DegToRad(m_1st_angle);

		// �ˌ��^�C�}�[���I����
		if (m_1stFireTimer.Finished())
		{
			// ���g�̉�]�p�x�Ɍ������Ēʏ�e�𔭎�
			m_BulletManager_P->CreateBullet(CATEGORY_ID::ENEMY, BULLET_ID::NORMAL, GetCenterPosition(), m_ShotSpeed, aqua::RadToDeg(m_UnitSprite.rotation));

			// �ˌ��^�C�}�[���Z�b�g
			m_1stFireTimer.Reset();
		}
	}

	// ��O�`�ԁi�������j�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
	else if (m_LifePoint <= m_2nd_change_hp && m_LifePoint >= m_3rd_change_hp && !m_FormChangeInitializeFlag)
	{
		// ���ˊԊu�𔼕��ɂ���
		m_1stFireTimer.Setup(m_fire_interval / 2);

		// �t���O�Z�b�g
		m_FormChangeInitializeFlag = true;
	}

	// ��O�`�ԁ[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
	else if (m_LifePoint <= m_2nd_change_hp && m_LifePoint >= m_3rd_change_hp)
	{
		// �ˌ��^�C�}�[�X�V
		m_1stFireTimer.Update();

		// �{�X���j�b�g����]������
		m_UnitSprite.rotation -= aqua::DegToRad(m_1st_angle);

		// �ˌ��^�C�}�[���I����
		if (m_1stFireTimer.Finished())
		{
			// ���g�̉�]�p�x�Ɍ������Ēʏ�e�𔭎�
			m_BulletManager_P->CreateBullet(CATEGORY_ID::ENEMY, BULLET_ID::NORMAL, GetCenterPosition(), m_ShotSpeed, aqua::RadToDeg(m_UnitSprite.rotation));

			// �ˌ��^�C�}�[���Z�b�g
			m_1stFireTimer.Reset();
		}
	}

	// ��l�`�ԁi�������j�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
	else if (m_LifePoint <= m_3rd_change_hp && m_LifePoint >= m_4th_change_hp && m_FormChangeInitializeFlag)
	{
		// ���ˑ��x��1.5�{�ɂ���
		m_ShotSpeed += m_shot_speed / 2;

		// �t���O�Z�b�g
		m_FormChangeInitializeFlag = false;

		m_EffectManager_P->CreateEffect(EFFECT_ID::DAMAGE, aqua::CVector2::ZERO, CATEGORY_ID::ENEMY);
	}

	// ��l�`�ԁ[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
	else if (m_LifePoint <= m_3rd_change_hp && m_LifePoint >= m_4th_change_hp)
	{
		// �ˌ��^�C�}�[�X�V
		m_1stFireTimer.Update();
		m_2ndFireTimer.Update();

		// �{�X���j�b�g����]������
		m_UnitSprite.rotation += aqua::DegToRad(m_1st_angle);

		// �ˌ��^�C�}�[���I����
		if (m_1stFireTimer.Finished())
		{
			// �����_���e�𔭎�
			m_BulletManager_P->CreateBullet(CATEGORY_ID::ENEMY, BULLET_ID::NORMAL, GetCenterPosition(), m_ShotSpeed, aqua::Rand(360));

			// �ˌ��^�C�}�[���Z�b�g
			m_1stFireTimer.Reset();
		}
		// �ˌ��^�C�}�[���I����
		if (m_2ndFireTimer.Finished())
		{
			// �����_���e�𔭎�
			m_BulletManager_P->CreateBullet(CATEGORY_ID::ENEMY, BULLET_ID::NORMAL, GetCenterPosition(), m_ShotSpeed, aqua::Rand(360));

			// �ˌ��^�C�}�[���Z�b�g
			m_2ndFireTimer.Reset();
		}
	}

	// ��܌`�ԁ[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
	else if (m_LifePoint <= m_4th_change_hp && m_LifePoint >= m_5th_change_hp)
	{
		// �������Ȃ�
	}

	// ��Z�`�ԁ[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
	else if (m_LifePoint <= m_5th_change_hp && m_LifePoint >= m_6th_change_hp)
	{
		// �G�o���^�C�}�[�X�V
		m_EnemySpawanTimer.Update();

		// �{�X���j�b�g����]������
		m_UnitSprite.rotation -= aqua::DegToRad(m_1st_angle);

		// �G���G����
		if (m_EnemySpawanTimer.Finished())
		{
			m_UnitManager_P->CreateUnit(UNIT_ID::NORMAL_TOUGH, { aqua::GetWindowWidth() - m_spawan_position_y ,m_spawan_position_y + (float)aqua::Rand(m_spawan_random_num) });
			m_UnitManager_P->CreateUnit(UNIT_ID::NORMAL, { aqua::GetWindowWidth() - m_spawan_position_y ,m_spawan_position_y + (float)aqua::Rand(m_spawan_random_num) });
			m_UnitManager_P->CreateUnit(UNIT_ID::NORMAL, { aqua::GetWindowWidth() - m_spawan_position_y ,m_spawan_position_y + (float)aqua::Rand(m_spawan_random_num) });
			m_UnitManager_P->CreateUnit(UNIT_ID::NORMAL, { aqua::GetWindowWidth() - m_spawan_position_y ,m_spawan_position_y + (float)aqua::Rand(m_spawan_random_num) });
			m_UnitManager_P->CreateUnit(UNIT_ID::NORMAL, { aqua::GetWindowWidth() - m_spawan_position_y ,m_spawan_position_y + (float)aqua::Rand(m_spawan_random_num) });
			m_UnitManager_P->CreateUnit(UNIT_ID::NORMAL, { aqua::GetWindowWidth() - m_spawan_position_y ,m_spawan_position_y + (float)aqua::Rand(m_spawan_random_num) });
			m_UnitManager_P->CreateUnit(UNIT_ID::NORMAL, { aqua::GetWindowWidth() - m_spawan_position_y ,m_spawan_position_y + (float)aqua::Rand(m_spawan_random_num) });

			// �G�o���^�C�}�[���Z�b�g
			m_EnemySpawanTimer.Reset();
		}
	}

	// �掵�`�ԁ[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
	else if (m_LifePoint <= m_6th_change_hp && m_LifePoint >= m_7th_change_hp)
	{
		// �`�ԕω��摜�̓����x�����X�ɏグ��
		if (m_SecondFormSprite.color.alpha != 255) m_SecondFormSprite.color.alpha++;
	}

	// �攪�`�ԁi�������j�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
	else if (m_LifePoint <= m_7th_change_hp && m_LifePoint >= m_8th_change_hp && !m_FormChangeInitializeFlag)
	{
		m_ShotSpeed = m_shot_speed;

		m_2ndFireTimer.Setup(m_one);

		m_FormChangeInitializeFlag = true;

		m_EffectManager_P->CreateEffect(EFFECT_ID::DAMAGE, aqua::CVector2::ZERO, CATEGORY_ID::ENEMY);
	}

	// �攪�`�ԁ[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
	else if (m_LifePoint <= m_7th_change_hp && m_LifePoint >= m_8th_change_hp)
	{
		// �ˌ��^�C�}�[�X�V
		m_1stFireTimer.Update();
		m_2ndFireTimer.Update();

		// �{�X���j�b�g����]������
		m_UnitSprite.rotation += aqua::DegToRad(m_1st_angle);

		// �{�X���j�b�g����]������
		m_SecondFormSprite.rotation -= aqua::DegToRad(m_1st_angle);

		// ������e���o�ĕǂ̂悤�Ɏˌ������
		if (m_1stFireTimer.Finished())
		{
			m_BulletManager_P->CreateBullet(CATEGORY_ID::BOSS, BULLET_ID::NORMAL, { 0,(float)aqua::GetWindowHeight() }, m_ShotSpeed, -90);
			m_BulletManager_P->CreateBullet(CATEGORY_ID::BOSS, BULLET_ID::NORMAL, { 300,(float)aqua::GetWindowHeight() }, m_ShotSpeed, -90);
			m_BulletManager_P->CreateBullet(CATEGORY_ID::BOSS, BULLET_ID::NORMAL, { 600,(float)aqua::GetWindowHeight() }, m_ShotSpeed, -90);
			m_BulletManager_P->CreateBullet(CATEGORY_ID::BOSS, BULLET_ID::NORMAL, { 900,(float)aqua::GetWindowHeight() }, m_ShotSpeed, -90);
			m_BulletManager_P->CreateBullet(CATEGORY_ID::BOSS, BULLET_ID::NORMAL, { 1200,(float)aqua::GetWindowHeight() }, m_ShotSpeed, -90);
			m_BulletManager_P->CreateBullet(CATEGORY_ID::BOSS, BULLET_ID::NORMAL, { 1500,(float)aqua::GetWindowHeight() }, m_ShotSpeed, -90);
			m_BulletManager_P->CreateBullet(CATEGORY_ID::BOSS, BULLET_ID::NORMAL, { 1800,(float)aqua::GetWindowHeight() }, m_ShotSpeed, -90);

			m_1stFireTimer.Reset();
		}

		// �z�[�~���O���[�U�[���������
		if (m_2ndFireTimer.Finished())
		{
			m_BulletManager_P->CreateBullet(CATEGORY_ID::ENEMY, BULLET_ID::HOMING, GetCenterPosition(), m_ShotSpeed, 0);

			m_2ndFireTimer.Reset();
		}
	}
}

void CFinalBoss::Draw(void)
{
	m_UnitSprite.Draw();

	m_SecondFormSprite.Draw();
}

void CFinalBoss::Finalize(void)
{
	m_SecondFormSprite.Delete();

	m_UnitSprite.Delete();
}

float CFinalBoss::GetRadius(void)
{
	return m_hit_radius;
}

void CFinalBoss::SpawanEffect(void)
{
}

void CFinalBoss::Movement(void)
{
}

void CFinalBoss::Fire(void)
{
}
