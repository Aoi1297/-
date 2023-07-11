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
	// 画像の生成＆設定
	CreateSprite("data/texture/unit/boss_1st_form.png");

	// ボスユニットサイズの設定
	m_UnitSprite.scale = m_unit_scale;

	// 第二形態画像の生成
	m_SecondFormSprite.Create("data/texture/unit/boss_2nd_form.png");

	// 第二形態画像のブレンドモードを加算合成に設定する
	m_SecondFormSprite.blend_mode = aqua::ALPHABLEND::ADD;

	// 第二形態画像を透明にしておく
	m_SecondFormSprite.color.alpha = 0;

	// 第二形態画像の位置を設定
	m_SecondFormSprite.position = m_UnitSprite.position;

	// 第二形態画像の基準点を中心にする
	m_SecondFormSprite.anchor = m_UnitSprite.anchor;

	// 第二形態画像のサイズを設定
	m_SecondFormSprite.scale = m_UnitSprite.scale;

	// ユニット体力設定
	m_LifePoint = m_max_life_point;

	// 弾の速度
	m_ShotSpeed = m_shot_speed;

	// イージングタイマー設定
	m_EasingTimer.Setup(m_easing_time);

	// 第一砲撃発射間隔設定
	m_1stFireTimer.Setup(m_fire_interval);

	// 第二砲撃発射間隔設定
	m_2ndFireTimer.Setup(m_fire_interval);

	// 敵出現タイマー設定
	m_EnemySpawanTimer.Setup(m_enemy_spawan_interval);

	// ユニットマネージャークラスオブジェクトのポインタを取得
	m_UnitManager_P = (CUnitManager*)(aqua::FindGameObject("UnitManager"));

	// ボス出現時に出現時の暗黒エフェクトを生成
	m_EffectManager_P->CreateEffect(EFFECT_ID::DARKNESS, GetCenterPosition(), CATEGORY_ID::ENEMY);

	// BGMを停止
	((CSoundCreater*)aqua::FindGameObject("SoundManager"))->Stop(SOUND_ID::BGM_GAME);

	// ボス用BGMを生成
	((CSoundCreater*)aqua::FindGameObject("SoundManager"))->Play(SOUND_ID::BGM_BOSS);
}

void CFinalBoss::Update(void)
{
	// 第二形態ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
	if (m_LifePoint <= m_1st_change_hp && m_LifePoint >= m_2nd_change_hp)
	{
		// 射撃タイマー更新
		m_1stFireTimer.Update();

		// ボスユニットを回転させる
		m_UnitSprite.rotation += aqua::DegToRad(m_1st_angle);

		// 射撃タイマーが終了時
		if (m_1stFireTimer.Finished())
		{
			// 自身の回転角度に向かって通常弾を発射
			m_BulletManager_P->CreateBullet(CATEGORY_ID::ENEMY, BULLET_ID::NORMAL, GetCenterPosition(), m_ShotSpeed, aqua::RadToDeg(m_UnitSprite.rotation));

			// 射撃タイマーリセット
			m_1stFireTimer.Reset();
		}
	}

	// 第三形態（初期化）ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
	else if (m_LifePoint <= m_2nd_change_hp && m_LifePoint >= m_3rd_change_hp && !m_FormChangeInitializeFlag)
	{
		// 発射間隔を半分にする
		m_1stFireTimer.Setup(m_fire_interval / 2);

		// フラグセット
		m_FormChangeInitializeFlag = true;
	}

	// 第三形態ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
	else if (m_LifePoint <= m_2nd_change_hp && m_LifePoint >= m_3rd_change_hp)
	{
		// 射撃タイマー更新
		m_1stFireTimer.Update();

		// ボスユニットを回転させる
		m_UnitSprite.rotation -= aqua::DegToRad(m_1st_angle);

		// 射撃タイマーが終了時
		if (m_1stFireTimer.Finished())
		{
			// 自身の回転角度に向かって通常弾を発射
			m_BulletManager_P->CreateBullet(CATEGORY_ID::ENEMY, BULLET_ID::NORMAL, GetCenterPosition(), m_ShotSpeed, aqua::RadToDeg(m_UnitSprite.rotation));

			// 射撃タイマーリセット
			m_1stFireTimer.Reset();
		}
	}

	// 第四形態（初期化）ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
	else if (m_LifePoint <= m_3rd_change_hp && m_LifePoint >= m_4th_change_hp && m_FormChangeInitializeFlag)
	{
		// 発射速度を1.5倍にする
		m_ShotSpeed += m_shot_speed / 2;

		// フラグセット
		m_FormChangeInitializeFlag = false;

		m_EffectManager_P->CreateEffect(EFFECT_ID::DAMAGE, aqua::CVector2::ZERO, CATEGORY_ID::ENEMY);
	}

	// 第四形態ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
	else if (m_LifePoint <= m_3rd_change_hp && m_LifePoint >= m_4th_change_hp)
	{
		// 射撃タイマー更新
		m_1stFireTimer.Update();
		m_2ndFireTimer.Update();

		// ボスユニットを回転させる
		m_UnitSprite.rotation += aqua::DegToRad(m_1st_angle);

		// 射撃タイマーが終了時
		if (m_1stFireTimer.Finished())
		{
			// ランダム弾を発射
			m_BulletManager_P->CreateBullet(CATEGORY_ID::ENEMY, BULLET_ID::NORMAL, GetCenterPosition(), m_ShotSpeed, aqua::Rand(360));

			// 射撃タイマーリセット
			m_1stFireTimer.Reset();
		}
		// 射撃タイマーが終了時
		if (m_2ndFireTimer.Finished())
		{
			// ランダム弾を発射
			m_BulletManager_P->CreateBullet(CATEGORY_ID::ENEMY, BULLET_ID::NORMAL, GetCenterPosition(), m_ShotSpeed, aqua::Rand(360));

			// 射撃タイマーリセット
			m_2ndFireTimer.Reset();
		}
	}

	// 第五形態ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
	else if (m_LifePoint <= m_4th_change_hp && m_LifePoint >= m_5th_change_hp)
	{
		// 何もしない
	}

	// 第六形態ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
	else if (m_LifePoint <= m_5th_change_hp && m_LifePoint >= m_6th_change_hp)
	{
		// 敵出現タイマー更新
		m_EnemySpawanTimer.Update();

		// ボスユニットを回転させる
		m_UnitSprite.rotation -= aqua::DegToRad(m_1st_angle);

		// 雑魚敵召喚
		if (m_EnemySpawanTimer.Finished())
		{
			m_UnitManager_P->CreateUnit(UNIT_ID::NORMAL_TOUGH, { aqua::GetWindowWidth() - m_spawan_position_y ,m_spawan_position_y + (float)aqua::Rand(m_spawan_random_num) });
			m_UnitManager_P->CreateUnit(UNIT_ID::NORMAL, { aqua::GetWindowWidth() - m_spawan_position_y ,m_spawan_position_y + (float)aqua::Rand(m_spawan_random_num) });
			m_UnitManager_P->CreateUnit(UNIT_ID::NORMAL, { aqua::GetWindowWidth() - m_spawan_position_y ,m_spawan_position_y + (float)aqua::Rand(m_spawan_random_num) });
			m_UnitManager_P->CreateUnit(UNIT_ID::NORMAL, { aqua::GetWindowWidth() - m_spawan_position_y ,m_spawan_position_y + (float)aqua::Rand(m_spawan_random_num) });
			m_UnitManager_P->CreateUnit(UNIT_ID::NORMAL, { aqua::GetWindowWidth() - m_spawan_position_y ,m_spawan_position_y + (float)aqua::Rand(m_spawan_random_num) });
			m_UnitManager_P->CreateUnit(UNIT_ID::NORMAL, { aqua::GetWindowWidth() - m_spawan_position_y ,m_spawan_position_y + (float)aqua::Rand(m_spawan_random_num) });
			m_UnitManager_P->CreateUnit(UNIT_ID::NORMAL, { aqua::GetWindowWidth() - m_spawan_position_y ,m_spawan_position_y + (float)aqua::Rand(m_spawan_random_num) });

			// 敵出現タイマーリセット
			m_EnemySpawanTimer.Reset();
		}
	}

	// 第七形態ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
	else if (m_LifePoint <= m_6th_change_hp && m_LifePoint >= m_7th_change_hp)
	{
		// 形態変化画像の透明度を徐々に上げる
		if (m_SecondFormSprite.color.alpha != 255) m_SecondFormSprite.color.alpha++;
	}

	// 第八形態（初期化）ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
	else if (m_LifePoint <= m_7th_change_hp && m_LifePoint >= m_8th_change_hp && !m_FormChangeInitializeFlag)
	{
		m_ShotSpeed = m_shot_speed;

		m_2ndFireTimer.Setup(m_one);

		m_FormChangeInitializeFlag = true;

		m_EffectManager_P->CreateEffect(EFFECT_ID::DAMAGE, aqua::CVector2::ZERO, CATEGORY_ID::ENEMY);
	}

	// 第八形態ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
	else if (m_LifePoint <= m_7th_change_hp && m_LifePoint >= m_8th_change_hp)
	{
		// 射撃タイマー更新
		m_1stFireTimer.Update();
		m_2ndFireTimer.Update();

		// ボスユニットを回転させる
		m_UnitSprite.rotation += aqua::DegToRad(m_1st_angle);

		// ボスユニットを回転させる
		m_SecondFormSprite.rotation -= aqua::DegToRad(m_1st_angle);

		// 下から弾が出て壁のように射撃される
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

		// ホーミングレーザーが放たれる
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
