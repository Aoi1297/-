#include "frame.h"

#include "../../../UnitManager/Unit/Player/player.h"
#include "../../../CameraManager/camera_manager.h"

const float CUIFrame::m_max_laser_point				= 2;
const unsigned int CUIFrame::m_up_frame_color		= 0xff0000ff;
const unsigned int CUIFrame::m_down_frame_color		= 0xff000000;
const unsigned int CUIFrame::m_laser_line_color		= 0xfff5ff00;
const unsigned int CUIFrame::m_hp_line_color		= 0xff20eb00;
const unsigned int CUIFrame::m_line_color			= 0xff808080;
const int CUIFrame::m_line_thickness				= 50;
const float CUIFrame::m_frame_height				= 150.0f;
const float CUIFrame::m_line_height					= 130.0f;

CUIFrame::CUIFrame(IGameObject* parent)
	// parent(CUiManager)
	: IUserInterface(parent, "UIFrame")
	, m_LineLength(0.0f)
	, m_LaserPoint(0)
	, m_LaserPointRatio(0.0f)
	, m_HitPoint(0.0f)
	, m_HitPointRatio(0.0f)
	, m_Player_P(nullptr)
{
}

void CUIFrame::Initialize(void)
{
	m_LineLength = aqua::GetWindowWidth();

	m_Player_P = (CPlayer*)aqua::FindGameObject("Player");

	m_CameraManager_P = (CCameraManager*)aqua::FindGameObject("CameraManager");
}

void CUIFrame::Update(void)
{
	// �v���C���[�����[�U�[���o���Ȃ烌�[�U�[���[�^������������
	if (m_Player_P->GetLaserFlag())
	{
		// ���[�U�[���ԂɏI������Ɠ����Ƀ��[�^�[���O�ɂȂ�
		m_LineLength -= (aqua::GetWindowWidth() / m_Player_P->GetLaserTime()) / aqua::core::CFramework::GetInstance().GetFPS();
	}
	else m_LineLength = aqua::GetWindowWidth();

	// ���[�U�[�|�C���g�擾
	m_LaserPoint = m_Player_P->GetLaserPoint();

	// �v���C���[��HP�擾
	m_HitPoint = m_Player_P->GetHitPoint();

	// ���[�U�[�|�C���g�̊��������߂�i�����擾���Ă��邩�����[�^�[�ŕ\�����߁j
	m_LaserPointRatio = m_LaserPoint / m_max_laser_point;

	// �̗͂̊��������߂�i�����̗͂��c���Ă��邩���[�^�[�ŕ\�����߁j
	m_HitPointRatio = m_HitPoint / (float)m_Player_P->GetMaxHitPoint();

	// ���[�U�[�|�C���g�̊������P�O�O���ɂȂ����烌�[�U�[�t���O��TRUE�i���[�U�[���ˏ�ԁj�ɂ���
	if (m_LaserPointRatio >= 1) m_Player_P->SetLaserFlag();
}

void CUIFrame::Draw(void)
{
	// �J�����̐U���̒l���擾
	aqua::CVector2 camera_pos = m_CameraManager_P->GetPosition();

	// ��̐F�̎l�p�`�𐶐��i�t���[����̒����`�j
	DrawBox(0 + camera_pos.x, 0 + camera_pos.y, aqua::GetWindowWidth() + camera_pos.x, m_frame_height + camera_pos.y, m_up_frame_color, true);

	// ���[�U�[���[�^�[��݂��Ă���D�F�̃��[�^�[
	DrawLine(0 + camera_pos.x, m_line_height + camera_pos.y, aqua::GetWindowWidth() + camera_pos.x, m_line_height + camera_pos.y, m_line_color, m_line_thickness);

	// ���[�U�[���[�^�[�����ɉ����Ē�����ς���i���F�̃��[�^�[�j
	DrawLine(0 + camera_pos.x, m_line_height + camera_pos.y, m_LineLength * m_LaserPointRatio + camera_pos.x, m_line_height + camera_pos.y, m_laser_line_color, m_line_thickness);

	// ���̍����l�p�`�𐶐��i�t���[����̒����`�j
	DrawBox(0 + camera_pos.x, aqua::GetWindowHeight() - m_frame_height + camera_pos.y, aqua::GetWindowWidth() + camera_pos.x, aqua::GetWindowHeight() + camera_pos.y, m_down_frame_color, true);

	// HP���[�^�[��݂��Ă���D�F�̃��[�^�[
	DrawLine(0 + camera_pos.x, aqua::GetWindowHeight() - m_line_height + camera_pos.y, aqua::GetWindowWidth() + camera_pos.x, aqua::GetWindowHeight() - m_line_height + camera_pos.y, m_line_color, m_line_thickness);

	// HP���[�^�[�����ɉ����Ē�����ς���i�΂̃��[�^�[�j
	DrawLine(0 + camera_pos.x, aqua::GetWindowHeight() - m_line_height + camera_pos.y, aqua::GetWindowWidth() * m_HitPointRatio + camera_pos.x, aqua::GetWindowHeight() - m_line_height + camera_pos.y, m_hp_line_color, m_line_thickness);
}