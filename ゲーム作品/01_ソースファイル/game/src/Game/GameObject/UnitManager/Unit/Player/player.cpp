#include "player.h"

#include "../../../BulletManager/bullet_manager.h"
#include "../../../ItemManager/item_manager.h"
#include "../../../InterfaceManager/ui_manager.h"
#include "../../../InterfaceManager/UI/Score/score.h"
#include "../../../UnitManager/unit_manager.h"

const int CPlayer::			m_max_life_point		= 20;
const float CPlayer::		m_move_speed			= 5.0f;
const float CPlayer::		m_start_shot_interval	= 1.0f;
const float CPlayer::		m_start_laser_speed		= 10.0f;
const DIRECTION_ID CPlayer::m_start_direction_id	= DIRECTION_ID::FRONT;
const BULLET_ID CPlayer::	m_start_bullet_id		= BULLET_ID::NORMAL;
const float CPlayer::		m_laser_time			= 3.0f;
const float CPlayer::		m_darkness_time			= 6.0f;
const float CPlayer::		m_max_laser_speed		= 30.0f;
const float CPlayer::		m_add_speed				= 2.0f;
const int CPlayer::			m_bonus_score			= 10000;
const float CPlayer::		m_max_shot_interval		= 0.135f;
const float CPlayer::		m_iecrease_interval		= 0.08f;
const float CPlayer::		m_normal_bullet_speed	= 25.0f;
const float CPlayer::		m_limit_position_x		= 1420;
const float CPlayer::		m_limit_position_y		= 150;
const float CPlayer::		m_random_angle			= 6.0f;
const float CPlayer::		m_first_angle			= -15.0f;
const float CPlayer::		m_second_angle			= 15.0f;
const float CPlayer::		m_third_angle			= -45.0f;
const float CPlayer::		m_fourth_angle			= 45.0f;
const float CPlayer::		m_fifth_angle			= -135.0f;
const float CPlayer::		m_sixth_angle			= 135.0f;

CPlayer::CPlayer(aqua::IGameObject* parent)
	// parent(CGameMain)
	: IUnit				(parent, "Player")
	, m_LaserSpeed		(0.0f)
	, m_ShotInterval	(0.0f)
	, m_LaserPoint		(0)
	, m_LaserShotFlag	(false)
	, m_DarknessFlag	(false)
	, m_EffectFlag		(true)
{
}

void CPlayer::Initialize(void)
{
	// 画像の生成＆初期設定
	CreateSprite("data/texture/unit/player.png");

	// 自身のポインタをセット
	SetPlayerPointer();

	// 体力を設定
	m_LifePoint = m_max_life_point;

	// 初期段階の発射速度
	{
		m_ShotInterval = m_start_shot_interval;
		m_FireInterval.Setup(m_start_shot_interval);
	}

	// レーザースピード設定
	m_ShotSpeed = m_normal_bullet_speed;

	// 弾発射速度設定
	m_LaserSpeed = m_start_laser_speed;

	// 初期段階の発射方向設定
	m_DirectionId = m_start_direction_id;

	// 弾の種類設定
	m_ShotKind = m_start_bullet_id;

	// レーザー時間設定
	m_LaserTimer.Setup(m_laser_time);

	// 暗闇時間設定
	m_DarknessTimer.Setup(m_darkness_time);
}

void CPlayer::Update(void)
{
	// プレイヤー操作
	Controller();

	// 射撃
	Fire();
}

void CPlayer::PowerUp(ITEM_ID item_id)
{
	switch (item_id)
	{
		// 「P」アイテムを取った場合
	case ITEM_ID::LASER:
	{
		// UIを表示
		m_UiManager_P->ShowMessage(ITEM_ID::LASER);

		// レーザーポイントアップ
		m_LaserPoint++;
	}break;

	// 「S」アイテムを取った場合
	case ITEM_ID::SPEED:
	{
		// UIを表示
		m_UiManager_P->ShowMessage(ITEM_ID::SPEED);

		// 最大速度を超えていなければ速度を追加する
		if (m_LaserSpeed <= m_max_laser_speed) m_LaserSpeed += m_add_speed;
		else
		{
			// 最大速度を超えたら最大速度にする
			m_LaserSpeed = m_max_laser_speed;

			// ボーナススコアを追加
			m_Score_P->AddScore(m_bonus_score);
		}
	}break;

	// 「→」アイテムを取った場合
	case ITEM_ID::DIRECTION:
	{
		// UIを表示
		m_UiManager_P->ShowMessage(ITEM_ID::DIRECTION);

		// 発射方向を現段階より１つ増やす
		switch (m_DirectionId)
		{
		case DIRECTION_ID::FRONT:			m_DirectionId = DIRECTION_ID::DOUBLE;		break;
		case DIRECTION_ID::DOUBLE:			m_DirectionId = DIRECTION_ID::TRIPLE;		break;
		case DIRECTION_ID::TRIPLE:			m_DirectionId = DIRECTION_ID::QUAD;			break;
		case DIRECTION_ID::QUAD:			m_DirectionId = DIRECTION_ID::DOUBLE_DOUBLE; break;
		case DIRECTION_ID::DOUBLE_DOUBLE:	m_DirectionId = DIRECTION_ID::TRIPLE_TRIPLE; break;
		case DIRECTION_ID::TRIPLE_TRIPLE:	m_DirectionId = DIRECTION_ID::QUAD_QUAD;	break;
		case DIRECTION_ID::QUAD_QUAD:		m_DirectionId = DIRECTION_ID::FINAL;		break;

			// 最終段階時ではボーナススコアが追加される
		default:m_Score_P->AddScore(m_bonus_score); break;
		}
	}break;

	// 「I」アイテムを取った場合
	case ITEM_ID::INTERVAL:
	{
		// UIを表示
		m_UiManager_P->ShowMessage(ITEM_ID::INTERVAL);

		// 発射間隔減少処理
		if (m_ShotInterval > m_max_shot_interval)
		{
			// 発射間隔減少
			m_ShotInterval -= m_iecrease_interval;

			// 発射間隔タイマーセット
			m_FireInterval.Setup(m_ShotInterval);
		}
		else
		{
			// 見にくい軌道エフェクトを無効化
			m_EffectFlag = false;

			// 発射間隔が最大値を超えたら超えないように設定
			m_ShotInterval = m_max_shot_interval;

			// ボーナススコアを追加する
			m_Score_P->AddScore(m_bonus_score);
		}
	}break;
	}
}

float CPlayer::GetRadius(void)
{
	return m_UnitSprite.GetTextureHeight() / 2;
}

void CPlayer::Controller(void)
{
	// 視界不良状態なら
	if (m_DarknessFlag)
	{
		// 視界不良時間計測
		m_DarknessTimer.Update();
	}
	if (m_DarknessTimer.Finished())
	{
		// 視界不良時間リセット
		m_DarknessFlag = false;
		m_DarknessTimer.Reset();
	}

	// 上に移動する
	if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::W) || aqua::keyboard::Button(aqua::keyboard::KEY_ID::UP))
		m_Position.y -= m_move_speed;
	
	// 左に移動する
	if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::A) || aqua::keyboard::Button(aqua::keyboard::KEY_ID::LEFT))
		m_Position.x -= m_move_speed;

	// 下に移動する
	if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::S) || aqua::keyboard::Button(aqua::keyboard::KEY_ID::DOWN))
		m_Position.y += m_move_speed;

	// 右に移動する
	if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::D) || aqua::keyboard::Button(aqua::keyboard::KEY_ID::RIGHT))
		m_Position.x += m_move_speed;

	// 画面左端より移動しない
	if (m_Position.x <= 0)
	{
		m_Position.x = 0;
	}

	// 一定の位置まででしか移動できないようにする（右方向）
	if (m_Position.x >= m_limit_position_x - m_UnitSprite.GetTextureWidth())
	{
		m_Position.x = m_limit_position_x - m_UnitSprite.GetTextureWidth();
	}

	// 上のUIまでの位置以上進めないようにする
	if (m_Position.y <= m_limit_position_y)
	{
		m_Position.y = m_limit_position_y;
	}

	// 下のUIまでの位置以上進めないようにする
	if (m_Position.y >= aqua::GetWindowHeight() - m_limit_position_y - m_UnitSprite.GetTextureHeight())
	{
		m_Position.y = aqua::GetWindowHeight() - m_limit_position_y - m_UnitSprite.GetTextureHeight();
	}

	// プレイヤー画像の移動処理
	m_UnitSprite.position = m_Position;
}

void CPlayer::Fire(void)
{
	// レーザー中ならレーザータイマーを起動
	if (m_LaserShotFlag) m_LaserTimer.Update();

	// 右矢印を押している間
	if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::SPACE))
	{
		// 矢印を押している間はタイマーを起動
		m_FireInterval.Update();

		// 計り終わったら弾を発射する
		if (m_FireInterval.Finished())
		{
			// プレイヤーの中心位置
			aqua::CVector2 center_position = GetCenterPosition();

			// 現在の発射方向IDに応じて放つ量や方向を変える
			switch (m_DirectionId)
			{
			case DIRECTION_ID::FRONT:
			{
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, aqua::Rand(m_random_angle) - m_random_angle / 2);
			}break;
			case DIRECTION_ID::DOUBLE:
			{
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, aqua::Rand(m_random_angle) - m_random_angle / 2);
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, aqua::Rand(m_random_angle));
			}break;
			case DIRECTION_ID::TRIPLE:
			{
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, aqua::Rand(m_random_angle) - m_random_angle / 2);
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_first_angle - aqua::Rand(m_random_angle));
			}break;
			case DIRECTION_ID::QUAD:
			{
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, aqua::Rand(m_random_angle) - m_random_angle / 2);
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_first_angle - aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_second_angle - aqua::Rand(m_random_angle));
			}break;
			case DIRECTION_ID::DOUBLE_DOUBLE:
			{
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, aqua::Rand(m_random_angle) - m_random_angle / 2);
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_first_angle - aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_second_angle - aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_third_angle - aqua::Rand(m_random_angle));
			}break;
			case DIRECTION_ID::TRIPLE_TRIPLE:
			{
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, aqua::Rand(m_random_angle) - m_random_angle / 2);
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_first_angle - aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_second_angle - aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_third_angle - aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_fourth_angle - aqua::Rand(m_random_angle));
			}break;
			case DIRECTION_ID::QUAD_QUAD:
			{
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, aqua::Rand(m_random_angle) - m_random_angle / 2);
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_first_angle - aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_second_angle - aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_third_angle - aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_fourth_angle - aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_fifth_angle - aqua::Rand(m_random_angle));
			}break;
			case DIRECTION_ID::FINAL:
			{
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, aqua::Rand(m_random_angle) - m_random_angle / 2);
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_first_angle - aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_second_angle - aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_third_angle - aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_fourth_angle - aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_fifth_angle - aqua::Rand(m_random_angle));
				m_BulletManager_P->CreateBullet(CATEGORY_ID::PLAYER, m_ShotKind, center_position, m_ShotSpeed, m_sixth_angle - aqua::Rand(m_random_angle));
			}break;
			}

			// レーザー時間が終了していなかったら　かつ　レーザー中かどうか
			if (!m_LaserTimer.Finished() && m_LaserShotFlag)
			{
				// ホーミングレーザーを放つ
				m_BulletManager_P->CreateBullet(m_UnitCategory, BULLET_ID::HOMING, center_position, m_LaserSpeed, 0);
			}

			// レーザー時間が終了していたら
			else if (m_LaserTimer.Finished())
			{
				// レーザー停止
				m_LaserShotFlag = false;

				// レーザータイマーリセット
				m_LaserTimer.Reset();

				// レーザーポイントリセット
				m_LaserPoint = 0;
			}

			// 弾が打ち終わったら発射間隔タイマーをリセットする
			m_FireInterval.Reset();
		}
	}
}