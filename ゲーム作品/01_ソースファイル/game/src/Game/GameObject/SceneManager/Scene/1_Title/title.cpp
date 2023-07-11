#include "title.h"

#include "../../../SoundManager/sound_creater.h"

const unsigned char		CTitle::m_max_random_color			= 200;
const int				CTitle::m_pixel_width				= 8;
const int				CTitle::m_param						= 100;
const aqua::CVector2	CTitle::m_title_scale				= { 1.5,1.5 };
const float				CTitle::m_title_position_y			= 100;
const float				CTitle::m_title_massage_position_y	= 300;
const float				CTitle::m_title_massage_scale_up	= 0.05f;
const int				CTitle::m_particle_quantity			= 100;
const int				CTitle::m_particle_random_scale_max	= 5;
const int				CTitle::m_particle_random_angle_max	= 360;
const float				CTitle::m_flash_screen_time			= 5.0f;
const float				CTitle::m_flash_object_time			= 0.5f;

CTitle::CTitle(aqua::IGameObject* parent)
	// parent(CSceneManager)
	: IScene(parent, "Title")
	, m_SceneManager_P(nullptr)
{
}

void CTitle::Initialize(void)
{
	// シーンマネージャークラスポインタを取得
	m_SceneManager_P = (CSceneManager*)aqua::FindGameObject("SceneManager");

	// サウンドマネージャークラスポインタを取得
	CSoundCreater* sound_manager = (CSoundCreater*)aqua::FindGameObject("SoundManager");

	// ゲームBGMの再生を停止
	sound_manager->Stop(SOUND_ID::BGM_GAME);

	// ボスBGMの再生を停止
	sound_manager->Stop(SOUND_ID::BGM_BOSS);

	// タイトルBGMを再生
	sound_manager->Play(SOUND_ID::BGM_TITLE);

	//////////////////////////////////////////////// スプライト系の初期化 ////////////////////////////////////////////////
	{
		// パーティクル画像の読み込み＆初期設定
		{
			m_ParticleSprite.Create("data/texture/others/particle.png");
			m_ParticleSprite.anchor			= { (float)m_ParticleSprite.GetTextureWidth() / 2, (float)m_ParticleSprite.GetTextureHeight() / 2 };
			m_ParticleSprite.color.alpha	= 0;
		}

		// エフェクト用パーティクル画像の読み込み＆初期設定
		{
			m_ParticleEffectSprite.Create("data/texture/others/particle.png");
			m_ParticleEffectSprite.anchor		= { (float)m_ParticleEffectSprite.GetTextureWidth() / 2, (float)m_ParticleEffectSprite.GetTextureHeight() / 2 };
			m_ParticleEffectSprite.blend_mode	= aqua::ALPHABLEND::ADD;
			m_ParticleEffectSprite.color		= GetColor(aqua::Rand(m_max_random_color), aqua::Rand(m_max_random_color), aqua::Rand(m_max_random_color));
			m_ParticleEffectSprite.color.alpha	= 0;
		}

		// エフェクト用タイトル画像の読み込み＆初期設定
		{
			m_TitleEffectSprite.Create("data/texture/others/title_blur.png");
			m_TitleEffectSprite.anchor		= { (float)m_TitleEffectSprite.GetTextureWidth() / 2, (float)m_TitleEffectSprite.GetTextureHeight() };
			m_TitleEffectSprite.scale		= m_title_scale;
			m_TitleEffectSprite.blend_mode	= aqua::ALPHABLEND::ADD;
			m_TitleEffectSprite.color.alpha = 0;
			m_TitleEffectSprite.position	= { (float)(aqua::GetWindowWidth() / 2 - m_TitleEffectSprite.GetTextureWidth() / 2),(float)((aqua::GetWindowHeight() / 2 - m_TitleEffectSprite.GetTextureHeight() / 2) - m_title_position_y) };
			m_TitleEffectSprite.ApplyGaussFilter(m_pixel_width, m_param);
		}

		// タイトル画像の読み込み＆初期設定
		{
			m_TitleSprite.Create("data/texture/others/title.png");
			m_TitleSprite.anchor		= m_TitleEffectSprite.anchor;
			m_TitleSprite.scale			= m_TitleEffectSprite.scale;
			m_TitleSprite.blend_mode	= aqua::ALPHABLEND::ADD;
			m_TitleSprite.color.alpha	= m_TitleEffectSprite.color.alpha;
			m_TitleSprite.position		= m_TitleEffectSprite.position;
		}

		// エフェクト用タイトルメッセージ画像の読み込み＆初期設定
		{
			m_TitleMassageEffectSprite.Create("data/texture/others/tittle_massage_blur.png");
			m_TitleMassageEffectSprite.anchor		= { (float)m_TitleMassageEffectSprite.GetTextureWidth() / 2,(float)m_TitleMassageEffectSprite.GetTextureHeight() / 2 };
			m_TitleMassageEffectSprite.scale.y		= 0;
			m_TitleMassageEffectSprite.blend_mode	= aqua::ALPHABLEND::ADD;
			m_TitleMassageEffectSprite.color.alpha	= 0;
			m_TitleMassageEffectSprite.position		= { (float)(aqua::GetWindowWidth() / 2 - m_TitleMassageEffectSprite.GetTextureWidth() / 2),(float)((aqua::GetWindowHeight() / 2 - m_TitleMassageEffectSprite.GetTextureHeight() / 2) + m_title_massage_position_y) };
			m_TitleMassageEffectSprite.ApplyGaussFilter(m_pixel_width, m_param);
		}

		// タイトルメッセージ画像の読み込み＆初期設定
		{
			m_TitleMassageSprite.Create("data/texture/others/title_massage.png");
			m_TitleMassageSprite.anchor			= m_TitleMassageEffectSprite.anchor;
			m_TitleMassageSprite.scale.y		= m_TitleMassageEffectSprite.scale.y;
			m_TitleMassageSprite.position		= m_TitleMassageEffectSprite.position;
			m_TitleMassageSprite.color.alpha	= m_TitleMassageEffectSprite.color.alpha;
		}

		// 画面フラッシュ画像の読み込み＆初期設定
		{
			m_FlashScreenSprite.Create("data/texture/others/white.png");
			m_FlashScreenSprite.color.alpha = 0;
		}
	}

	//////////////////////////////////////////////// 粒子画像のデータの初期化（粒子の数だけ繰り返す）////////////////////////////////////////////////
	for (int i = 0; i < m_particle_quantity; ++i)
	{
		/////// 位置のランダム決め ///////
		PARTICLE_DATA random;
		{
			// 画面からはみ出た位置に生成されないように粒子の最大サイズ分引く
			random.position.x = (float)aqua::Rand(aqua::GetWindowWidth() - m_ParticleEffectSprite.GetTextureWidth() / 2 * m_particle_random_scale_max);
			random.position.y = (float)aqua::Rand(aqua::GetWindowHeight() - m_ParticleEffectSprite.GetTextureHeight() / 2 * m_particle_random_scale_max);
		}

		/////// 大きさのランダム決め ///////
		{
			// XとYは同じ大きさ幅にする
			random.scale.x = random.scale.y = (float)aqua::Rand(m_particle_random_scale_max);
		}

		/////// 角度のランダム決め ///////
		{
			// 整数で０から３６０の角度を取得する
			random.angle = (float)aqua::Rand(m_particle_random_angle_max);
		}

		// パーティクルリストにデータ追加
		m_ParticleDataList.push_back(random);
	}

	//////////////////////////////////////////////// タイマー系初期化 ////////////////////////////////////////////////
	{
		// 画面フラッシュ開始時間設定
		m_FlashScreenTimer.Setup(m_flash_screen_time);

		// 発光オブジェクトの点滅時間設定
		m_FlashObjectTimer.Setup(m_flash_object_time);
	}
}

void CTitle::Update(void)
{
	// Zキーが押されているかの判定
	CheckKeyZ();

	// タイマーの更新処理
	TimerUpdate();

	// パーティクルの移動処理
	ParticleMove();
}

void CTitle::Draw(void)
{
	// パーティクルリスト
	for (auto& element : m_ParticleDataList)
	{
		// 位置と大きさを毎フレーム設定
		m_ParticleEffectSprite.position = m_ParticleSprite.position = element.position;
		m_ParticleEffectSprite.scale	= m_ParticleSprite.scale	= element.scale;

		// パーティクルエフェクトスプライトの描画
		m_ParticleEffectSprite.	Draw();

		// パーティクルスプライトの描画
		m_ParticleSprite.		Draw();
	}

	// タイトルエフェクトスプライトの描画
	m_TitleEffectSprite.		Draw();

	// タイトルスプライトの描画
	m_TitleSprite.				Draw();

	// タイトルメッセージエフェクトスプライトの描画
	m_TitleMassageEffectSprite.	Draw();

	// タイトルメッセージスプライトの描画
	m_TitleMassageSprite.		Draw();

	// 画面フラッシュスプライトの描画
	m_FlashScreenSprite.		Draw();
}


void CTitle::Finalize(void)
{
	// スプライトのメモリ解放
	m_FlashScreenSprite.		Delete();	// !< 画面フラッシュ画像
	m_TitleMassageEffectSprite.	Delete();	// !< タイトルメッセージエフェクト画像
	m_TitleMassageSprite.		Delete();	// !< タイトルメッセージ画像
	m_TitleEffectSprite.		Delete();	// !< タイトルエフェクト画像
	m_TitleSprite.				Delete();	// !< タイトル画像
	m_ParticleEffectSprite.		Delete();	// !< パーティクルエフェクト画像
	m_ParticleSprite.			Delete();	// !< パーティクル画像
}

void CTitle::CheckKeyZ(void)
{
	// 「Z」キーが押されたら「ゲームメインシーン」へ移動する
	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::Z))
	{
		m_SceneManager_P->ChangeScene(SCENE_ID::GAMEMAIN);
	}
}

void CTitle::TimerUpdate(void)
{
	// 画面フラッシュタイマー起動
	if (!m_FlashScreenTimer.Finished()) m_FlashScreenTimer.Update();

	// フラッシュタイマーが終了したらメッセージの表示をする
	if (m_FlashScreenTimer.Finished() && m_TitleMassageSprite.scale.y <= aqua::CVector2::ONE.y)
	{
		m_TitleMassageSprite.scale.y += m_title_massage_scale_up;
		m_TitleMassageEffectSprite.scale = m_TitleEffectSprite.scale;
	}

	// 画面フラッシュタイマー処理 //
	{
		// 透明度を変更するオブジェクト群
		m_ParticleSprite.color.alpha		=
		m_TitleSprite.color.alpha			=
		m_TitleMassageSprite.color.alpha	=

		// 経過時間の割合によって画像の透明度を変化させる
		(unsigned char)(aqua::CColor::MAX_COLOR * m_FlashScreenTimer.GetTime() / m_FlashScreenTimer.GetLimit());
	}

	// 画面フラッシュタイマーが計り終わった時、オブジェクトフラッシュタイマーを起動
	if (m_FlashScreenTimer.Finished()) m_FlashObjectTimer.Update();

	// オブジェクトフラッシュタイマー処理 //
	{
		// 透明度を変更するオブジェクト群
		m_ParticleEffectSprite.color.alpha	=
		m_TitleEffectSprite.color.alpha		=
		m_TitleEffectSprite.color.alpha		=

		// 経過時間の割合によって画像の透明度を変化させる
		(unsigned char)(aqua::CColor::MAX_COLOR * m_FlashObjectTimer.GetTime() / m_FlashObjectTimer.GetLimit());
	}

	// オブジェクトタイマーが計り終わったら、再計測する
	if (m_FlashObjectTimer.Finished()) m_FlashObjectTimer.Reset();
}

void CTitle::ParticleMove(void)
{
	// パーティクルリストから位置を変更する
	for (auto& element : m_ParticleDataList)
	{
		// パーティクルを角度に対応した向きへ進める
		element.position.x += cos(aqua::DegToRad(element.angle));
		element.position.y += sin(aqua::DegToRad(element.angle));

		// 左壁にパーティクルがぶつかったら
		if (element.position.x < 0 - m_ParticleEffectSprite.GetTextureWidth())
		{
			// 角度反転
			element.angle += 180;
		}
		// 右壁にパーティクルがぶつかったら
		else if (element.position.x > aqua::GetWindowWidth() - m_ParticleEffectSprite.GetTextureWidth())
		{
			// 角度反転
			element.angle -= 180;
		}

		// 上壁にパーティクルがぶつかったら
		if (element.position.y < 0 - m_ParticleEffectSprite.GetTextureHeight())
		{
			// 角度反転
			element.angle = -element.angle;
		}
		// 下壁にパーティクルがぶつかったら
		else if (element.position.y > aqua::GetWindowHeight() - m_ParticleEffectSprite.GetTextureHeight())
		{
			// 角度反転
			element.angle = -element.angle;
		}
	}
}
