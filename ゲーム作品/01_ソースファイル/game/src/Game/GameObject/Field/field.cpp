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
	// ƒvƒŒƒCƒ„[ƒNƒ‰ƒXƒ|ƒCƒ“ƒ^‚ğæ“¾
	m_Player_P = (CPlayer*)aqua::FindGameObject("Player");

	// “®‚©‚È‚¢”wŒi‰æ‘œ
	m_BackGroundSprite.Create("data/texture/others/back_ground.png");

	// “®‚­”wŒi‰æ‘œ‚P–‡–Ú
	m_BackGroundMoveSprite.Create("data/texture/others/back_ground.png");
	m_BackGroundMoveSprite.ApplyGaussFilter(m_param, m_pixel_width);

	// “®‚­”wŒi‰æ‘œ‚Q–‡–Ú
	m_BackGroundMoveNextSprite.Create("data/texture/others/back_ground.png");
	m_BackGroundMoveNextSprite.ApplyGaussFilter(m_param, m_pixel_width);

	// ‚Q–‡–Ú‚Ì”wŒi‰æ‘œ‚ğ‰E’[‚ÉƒZƒbƒg
	m_BackGroundMoveNextSprite.position.x = (float)aqua::GetWindowWidth();

	// ’†ƒ{ƒXoŒ»ŠÔİ’è
	m_MiniBossSpawnTimer.Setup(m_mini_boss_spawn_time);
}

void CField::Update(void)
{
	// ƒ^ƒCƒ}[XVˆ—
	TimerUpdate();

	// ”wŒiˆÚ“®ŒvZˆ—
	MoveCalculation();

	// ”wŒiˆÚ“®ˆ—
	MoveBackGround();
}

void CField::Draw(void)
{
	m_BackGroundSprite.Draw();				// !< ”wŒi‚Ì•`‰æ
	m_BackGroundMoveSprite.Draw();			// !< ”wŒi‚Ì‚P–‡–Ú‚Ì•`‰æ
	m_BackGroundMoveNextSprite.Draw();		// !< ”wŒi‚Ì‚Q–‡–Ú‚Ì•`‰æ
}

void CField::Finalize(void)
{
	// ‰æ‘œƒf[ƒ^‚ğƒƒ‚ƒŠ‚Ì‰ğ•ú
	m_BackGroundMoveNextSprite.Delete();	// !< ”wŒi‚Q–‡–Ú‚Ì‰ğ•ú
	m_BackGroundMoveSprite.Delete();		// !< ”wŒi‚P–‡–Ú‚Ì‰ğ•ú
	m_BackGroundSprite.Delete();			// !< ”wŒi‚Ì‰ğ•ú
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
	// ‰æ‘œ‚ğˆÚ“®‚³‚¹‚é
	m_BackGroundMoveSprite.position.x -= m_BackGroundSpeed;
	m_BackGroundMoveNextSprite.position.x -= m_BackGroundSpeed;

	// ‚P–‡–Ú‚Ì‰æ‘œˆÚ“®ˆ—
	{
		// ‚P–‡–Ú‚Ì‰æ‘œ‚ª‰æ–Ê‚©‚çŒ©‚¦‚È‚­‚È‚Á‚½‚ç
		if (m_BackGroundMoveSprite.position.x < -(float)aqua::GetWindowWidth())
			// ‰æ‘œ‰E’[‚ÖˆÚ“®‚³‚¹‚é
			m_BackGroundMoveSprite.position.x = (float)aqua::GetWindowWidth();
	}

	// ‚Q–‡–Ú‚Ì‰æ‘œˆÚ“®ˆ—
	{
		// ‚Q–‡–Ú‚Ì‰æ‘œ‚ª‰æ–Ê‚©‚çŒ©‚¦‚È‚­‚È‚Á‚½‚ç
		if (m_BackGroundMoveNextSprite.position.x < -(float)aqua::GetWindowWidth())
			// ‰æ–Ê‰E’[‚ÖˆÚ“®‚³‚¹‚é
			m_BackGroundMoveNextSprite.position.x = (float)aqua::GetWindowWidth();
	}
}