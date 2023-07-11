#include "homing_bullet.h"

#include "../../../EffectManager/effect_manager.h"
#include "../../../UnitManager/unit_manager.h"
#include "../../../SoundManager/sound_creater.h"

const float CHomingBullet::m_homing_time	= 1.0f;
const float CHomingBullet::m_start_position = 100.0f;
const float CHomingBullet::m_homing_angle	= 5.0f;

CHomingBullet::CHomingBullet(IGameObject* parent)
	// parent(CBulletManager)
	: IBullet(parent, "HomingBullet")
{
}

void CHomingBullet::Initialize(void)
{
	// ホーミング弾の画像生成
	IBullet::CreateSprite("data/texture/bullet/normal_bullet_blue.png");

	// 効果音を鳴らす
	((CSoundCreater*)aqua::FindGameObject("SoundManager"))->Play(SOUND_ID::EFFECT_LASER);

	// ホーミングタイマーの設定
	m_HomingTimer.Setup(m_homing_time);

	// ホーミング位置をずらす
	m_Position.y -= m_start_position;
}

void CHomingBullet::OriginalMovement(void)
{
	// ホーミングタイマー更新
	m_HomingTimer.Update();

	// レーザーエフェクトを毎フレーム生成する
	m_EffectManager->CreateEffect(EFFECT_ID::LASER, GetCenterPosition(), m_Category);

	// ホーミングタイマーが終了していなければ　かつ　プレイヤーが放った場合
	if (!(m_HomingTimer.Finished()) && m_Category == CATEGORY_ID::PLAYER)
	{
		// プレイヤー以外の一番近くにいるユニットのクラスポインタを取得する
		IUnit* unit = ((CUnitManager*)aqua::FindGameObject("UnitManager"))->FindNearUnit(this);

		// 取得したユニットのクラスポインタのNULLチェックを行う
		if (unit == nullptr) return;

		// 一番近くにいたユニットとホーミング弾の距離を求める
		const aqua::CVector2 distance = unit->GetCenterPosition() - GetCenterPosition();

		// 自分の弾が進行方向に対して右か左にあるか調べる
		const float direction = aqua::CVector2::Cross(distance, m_Velocity);

		if (direction > 0.0f)
		{
			m_Direction -= m_homing_angle;
		}
		else
		{
			m_Direction += m_homing_angle;
		}

		// 弾の発射角度に向かって進むように計算する
		m_Velocity.x = cos(aqua::DegToRad(m_Direction));
		m_Velocity.y = sin(aqua::DegToRad(m_Direction));
	}

	// 敵が放った場合　かつ　ホーミングタイマーが終了していないとき
	if (m_Category == CATEGORY_ID::ENEMY && !(m_HomingTimer.Finished()))
	{
		// ユニットマネージャーリストの先頭はプレイヤーが格納されているため
		const auto& it = ((CUnitManager*)aqua::FindGameObject("UnitManager"))->GetChildList()->begin();

		// プレイヤークラスオブジェクトの取得
		IUnit* player = (IUnit*)*it;

		// プレイヤーNULLチェック
		if (player == nullptr)return;

		// プレイヤーと弾の距離を求める
		const aqua::CVector2 distance = player->GetCenterPosition() - GetCenterPosition();

		// プレイヤーに対して弾が右側か左側にあるのかを調べる
		const float direction = aqua::CVector2::Cross(distance, m_Velocity);

		if (direction > 0.0f)
		{
			m_Direction -= m_homing_angle;
		}
		else
		{
			m_Direction += m_homing_angle;
		}

		// 弾の発射角度に向かって進むように計算する
		m_Velocity.x = cos(aqua::DegToRad(m_Direction));
		m_Velocity.y = sin(aqua::DegToRad(m_Direction));
	}

	// 弾の更新処理を行う
	m_BulletSprite.position = m_Position;
}