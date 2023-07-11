#include "darkness.h"

#include "../../../UnitManager/Unit/Player/player.h"
#include "../../../UnitManager/unit_manager.h"
#include "../../../SoundManager/sound_creater.h"

const aqua::CVector2 CDarkness::m_light_brightness				= { 15.0f,15.0f };
const aqua::CVector2 CDarkness::m_light_brightness_for_enemy	= { 3.0f,3.0f };
const float CDarkness::m_darkness_time							= 5.0f;
const float CDarkness::m_darkness_time_for_enemy				= 7.0f;
const float CDarkness::m_flash_time								= 1.0f;

CDarkness::CDarkness(IGameObject* parent)
	// parent(CEffectManager)
	: IEffect(parent,"Darkness")
	, m_FlashFlag(false)
	, m_DarknessFlag(true)
	, m_Player_P(nullptr)
{
}

void CDarkness::Initialize(void)
{
	// サーフェイスを生成（Xサイズ、Yサイズ、アルファチャンネルの使用）
	m_DarknessArea.Create(aqua::GetWindowWidth(), aqua::GetWindowHeight(), true);

	// サーフェイス描画用スプライトを生成
	m_SurfaceSprite.Create(m_DarknessArea);

	// 光源スプライトを生成
	m_LightSprite.Create("data/texture/others/light.png");

	// 光源スプライトの基準点を中心にする
	m_LightSprite.anchor = { (float)m_LightSprite.GetTextureWidth() / 2,(float)m_LightSprite.GetTextureHeight() / 2 };

	// 光源スプライトのブレンドモードを（減算合成）にする
	m_LightSprite.blend_mode = aqua::ALPHABLEND::SUB;

	// 暗闇スプライトを生成
	m_DarknessSprite.Create("data/texture/others/darkness.png");

	// ライトの明るさ（サイズ設定）（大きめ）
	m_LightSprite.scale = m_light_brightness;

	// 敵がこのクラスオブジェクトを生成したときの明るさ（サイズ）
	if (m_Category == CATEGORY_ID::ENEMY)
	{
		// ライトの明るさ（サイズ設定）（小さめ）
		m_LightSprite.scale = m_light_brightness_for_enemy;
	}

	// プレイヤークラスオブジェクトのポインタの取得
	m_Player_P = ((CPlayer*)aqua::FindGameObject("Player"));

	// フラッシュ用のスプライトの生成
	m_FlashSprite.Create("data/texture/others/white.png");

	// フラッシュ用スプライトは透明で初期化しておく
	m_FlashSprite.color.alpha = 0;

	// カテゴリーがプレイヤーなら暗闇時間を５秒にする
	if (m_Category == CATEGORY_ID::PLAYER) m_DarknessTimer.Setup(m_darkness_time);

	// プレイヤー以外のカテゴリーなら７秒にする
	else m_DarknessTimer.Setup(m_darkness_time_for_enemy);

	// フラッシュ時間
	m_FlashTimer.Setup(m_flash_time);
}

void CDarkness::Update(void)
{
	// 暗闇タイマー更新
	m_DarknessTimer.Update();

	// 暗闇時間計測終了時
	if (m_DarknessTimer.Finished())
	{
		// フラッシュフラグがFALSEなら
		if (!m_FlashFlag)
		{
			// フラッシュスプライトを不透明にする（画面真っ白状態にする）
			m_FlashSprite.color.alpha = 255;

			((CSoundCreater*)aqua::FindGameObject("SoundManager"))->Play(SOUND_ID::EFFECT_FLASH);
		}

		// フラッシュタイマーが終了していなければ
		if (!m_FlashTimer.Finished())
		{
			// フラッシュタイマー更新
			m_FlashTimer.Update();

			// フラッシュ用スプライトを徐々に透明にしていく
			m_FlashSprite.color.alpha -= 5;
		}
		// タイマーが終了していればクラスオブジェクトの削除を行う
		else if (m_FlashTimer.Finished())
		{
			IGameObject::DeleteObject();
		}

		//　フラッシュフラグをTRUEにする
		m_FlashFlag = true;
	}

	// ライトの位置をプレイヤーの位置と同じようにする
	m_LightSprite.position = m_Player_P->GetCenterPosition() - aqua::CVector2::ONE * m_LightSprite.GetTextureWidth()/2;
}

void CDarkness::Draw(void)
{
	// サーフェイスエリアの描画
	m_DarknessArea.Begin();
	{
		// 背景黒に設定
		aqua::Clear(0x00000000);

		// 暗闇スプライトを描画
		m_DarknessSprite.Draw();

		// 減算合成した光源スプライトを上から描画することで、暗闇スプライトの透明度を抜き照らされているようにみせる
		m_LightSprite.Draw();
	}
	// サーフェイスエリアの描画を終了
	m_DarknessArea.End();

	// サーフェイスの描画
	m_SurfaceSprite.Draw();

	// フラッシュスプライトの描画
	m_FlashSprite.Draw();
}

void CDarkness::Finalize(void)
{
	// スプライト等のメモリ解放
	m_FlashSprite.Delete();
	m_SurfaceSprite.Delete();
	m_LightSprite.Delete();
	m_DarknessSprite.Delete();
	m_DarknessArea.Delete();
}