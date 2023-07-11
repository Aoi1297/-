#include "field.h"

#include "../UnitManager/Unit/Player/player.h"

const int CField::m_pixel_width						= 100;
const int CField::m_param							= 8;
const float CField::m_mini_boss_spawn_time			= 70;
const float CField::m_back_ground_speed_normal		= 5;
const float CField::m_back_ground_speed_laser		= 10;
const float CField::m_back_ground_speed_headmode	= 10;

CField::CField(IGameObject* parent)
	// parent(CGameMain)
	: IGameObject(parent, "Field")
	, m_BackGroundSpeed(0)
{
}

void CField::Initialize(void)
{
	// �v���C���[�N���X�|�C���^���擾
	m_Player_P = (CPlayer*)aqua::FindGameObject("Player");

	// �����Ȃ��w�i�摜
	m_BackGroundSprite.Create("data/texture/others/back_ground.png");

	// �����w�i�摜�P����
	m_BackGroundMoveSprite.Create("data/texture/others/back_ground.png");
	m_BackGroundMoveSprite.ApplyGaussFilter(m_param, m_pixel_width);

	// �����w�i�摜�Q����
	m_BackGroundMoveNextSprite.Create("data/texture/others/back_ground.png");
	m_BackGroundMoveNextSprite.ApplyGaussFilter(m_param, m_pixel_width);

	// �Q���ڂ̔w�i�摜���E�[�ɃZ�b�g
	m_BackGroundMoveNextSprite.position.x = (float)aqua::GetWindowWidth();

	// ���{�X�o�����Ԑݒ�
	m_MiniBossSpawnTimer.Setup(m_mini_boss_spawn_time);
}

void CField::Update(void)
{
	// �^�C�}�[�X�V����
	TimerUpdate();

	// �w�i�ړ��v�Z����
	MoveCalculation();

	// �w�i�ړ�����
	MoveBackGround();
}

void CField::Draw(void)
{
	m_BackGroundSprite.Draw();				// !< �w�i�̕`��
	m_BackGroundMoveSprite.Draw();			// !< �w�i�̂P���ڂ̕`��
	m_BackGroundMoveNextSprite.Draw();		// !< �w�i�̂Q���ڂ̕`��
}

void CField::Finalize(void)
{
	// �摜�f�[�^���������̉��
	m_BackGroundMoveNextSprite.Delete();	// !< �w�i�Q���ڂ̉��
	m_BackGroundMoveSprite.Delete();		// !< �w�i�P���ڂ̉��
	m_BackGroundSprite.Delete();			// !< �w�i�̉��
}

void CField::TimerUpdate(void)
{
	m_MiniBossSpawnTimer.Update();
}

void CField::MoveCalculation(void)
{
	m_BackGroundSpeed = m_back_ground_speed_normal;

	if (m_MiniBossSpawnTimer.Finished())
	{
		m_BackGroundSpeed += m_back_ground_speed_headmode;

		m_MiniBossSpawnTimer.SetTime(m_MiniBossSpawnTimer.GetLimit());
	}

	if (m_Player_P->GetLaserFlag())
	{
		m_BackGroundSpeed += m_back_ground_speed_laser;
	}
}

void CField::MoveBackGround(void)
{
	// �摜���ړ�������
	m_BackGroundMoveSprite.position.x -= m_BackGroundSpeed;
	m_BackGroundMoveNextSprite.position.x -= m_BackGroundSpeed;

	// �P���ڂ̉摜�ړ�����
	{
		// �P���ڂ̉摜����ʂ��猩���Ȃ��Ȃ�����
		if (m_BackGroundMoveSprite.position.x < -(float)aqua::GetWindowWidth())
			// �摜�E�[�ֈړ�������
			m_BackGroundMoveSprite.position.x = (float)aqua::GetWindowWidth();
	}

	// �Q���ڂ̉摜�ړ�����
	{
		// �Q���ڂ̉摜����ʂ��猩���Ȃ��Ȃ�����
		if (m_BackGroundMoveNextSprite.position.x < -(float)aqua::GetWindowWidth())
			// ��ʉE�[�ֈړ�������
			m_BackGroundMoveNextSprite.position.x = (float)aqua::GetWindowWidth();
	}
}