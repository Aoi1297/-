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
	// プレイヤーがレーザー放出中ならレーザーメータを減少させる
	if (m_Player_P->GetLaserFlag())
	{
		// レーザー時間に終了すると同時にメーターが０になる
		m_LineLength -= (aqua::GetWindowWidth() / m_Player_P->GetLaserTime()) / aqua::core::CFramework::GetInstance().GetFPS();
	}
	else m_LineLength = aqua::GetWindowWidth();

	// レーザーポイント取得
	m_LaserPoint = m_Player_P->GetLaserPoint();

	// プレイヤーのHP取得
	m_HitPoint = m_Player_P->GetHitPoint();

	// レーザーポイントの割合を求める（何％取得しているかをメーターで表すため）
	m_LaserPointRatio = m_LaserPoint / m_max_laser_point;

	// 体力の割合を求める（何％体力が残っているかメーターで表すため）
	m_HitPointRatio = m_HitPoint / (float)m_Player_P->GetMaxHitPoint();

	// レーザーポイントの割合が１００％になったらレーザーフラグをTRUE（レーザー発射状態）にする
	if (m_LaserPointRatio >= 1) m_Player_P->SetLaserFlag();
}

void CUIFrame::Draw(void)
{
	// カメラの振動の値を取得
	aqua::CVector2 camera_pos = m_CameraManager_P->GetPosition();

	// 上の青色の四角形を生成（フレーム状の長方形）
	DrawBox(0 + camera_pos.x, 0 + camera_pos.y, aqua::GetWindowWidth() + camera_pos.x, m_frame_height + camera_pos.y, m_up_frame_color, true);

	// レーザーメーター常設している灰色のメーター
	DrawLine(0 + camera_pos.x, m_line_height + camera_pos.y, aqua::GetWindowWidth() + camera_pos.x, m_line_height + camera_pos.y, m_line_color, m_line_thickness);

	// レーザーメーター割合に応じて長さを変える（黄色のメーター）
	DrawLine(0 + camera_pos.x, m_line_height + camera_pos.y, m_LineLength * m_LaserPointRatio + camera_pos.x, m_line_height + camera_pos.y, m_laser_line_color, m_line_thickness);

	// 下の黒い四角形を生成（フレーム状の長方形）
	DrawBox(0 + camera_pos.x, aqua::GetWindowHeight() - m_frame_height + camera_pos.y, aqua::GetWindowWidth() + camera_pos.x, aqua::GetWindowHeight() + camera_pos.y, m_down_frame_color, true);

	// HPメーター常設している灰色のメーター
	DrawLine(0 + camera_pos.x, aqua::GetWindowHeight() - m_line_height + camera_pos.y, aqua::GetWindowWidth() + camera_pos.x, aqua::GetWindowHeight() - m_line_height + camera_pos.y, m_line_color, m_line_thickness);

	// HPメーター割合に応じて長さを変える（緑のメーター）
	DrawLine(0 + camera_pos.x, aqua::GetWindowHeight() - m_line_height + camera_pos.y, aqua::GetWindowWidth() * m_HitPointRatio + camera_pos.x, aqua::GetWindowHeight() - m_line_height + camera_pos.y, m_hp_line_color, m_line_thickness);
}