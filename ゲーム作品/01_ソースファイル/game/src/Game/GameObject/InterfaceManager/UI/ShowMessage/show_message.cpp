#include "show_message.h"

#include "../../../ItemManager/item_manager.h"

const float CShowMessage::m_easing_time			= 1.0f;
const float CShowMessage::m_finish_message_time = 0.7f;
const float CShowMessage::m_message_max_scale	= 5.0f;
const float CShowMessage::m_message_scale		= 2.0f;
const int CShowMessage::m_alpha_count			= 3;

CShowMessage::CShowMessage(IGameObject* parent)
	// parent(CUiManager)
	: IUserInterface(parent, "UIPowerUp")
	, m_AlphaCount(0)
{
}

void CShowMessage::ShowMessage(const ITEM_ID& item_id)
{
	// 表示するアイテムメッセージの識別
	m_ItemId = item_id;

	// 初期化を行う
	Initialize();
}

void CShowMessage::Initialize(void)
{
	// 表示するメッセージの判別を行う

	// レーザーメーター
	if (m_ItemId == ITEM_ID::LASER)
	{
		m_UiSprite.Create("data/texture/ui/laser_meter.png");
	}

	// レーザースピード
	else if (m_ItemId == ITEM_ID::SPEED)
	{
		m_UiSprite.Create("data/texture/ui/laser_speed.png");
	}

	// 発射方向追加
	else if (m_ItemId == ITEM_ID::DIRECTION)
	{
		m_UiSprite.Create("data/texture/ui/direction.png");
	}

	// 発射間隔短縮
	else if (m_ItemId == ITEM_ID::INTERVAL)
	{
		m_UiSprite.Create("data/texture/ui/interval.png");
	}

	// 表示するメッセージの基準点を中心にする
	m_UiSprite.anchor = { (float)m_UiSprite.GetTextureWidth() / 2, (float)m_UiSprite.GetTextureHeight() / 2 };

	// メッセージの表示位置
	m_UiSprite.position = { (float)aqua::GetWindowWidth() / 2 - m_UiSprite.GetTextureWidth() / 2,(float)aqua::GetWindowHeight() - m_UiSprite.GetTextureHeight() };

	// メッセージ画像の初期透明度の設定
	m_UiSprite.color.alpha = 0;

	// イージング時間設定
	m_EasingTimer.Setup(m_easing_time);

	// 終了時間設定
	m_FinishMessageTimer.Setup(m_finish_message_time);
}

void CShowMessage::Update(void)
{
	// イージングタイマーの更新
	if (!m_EasingTimer.Finished())
	{
		m_EasingTimer.Update();
	}

	// 表示するメッセージが徐々に下へ移動するような動きを与える
	m_UiSprite.position.y = aqua::easing::OutQuintic
	(
		m_EasingTimer.GetTime(),
		m_EasingTimer.GetLimit(),
		(float)aqua::GetWindowHeight() - m_UiSprite.GetTextureHeight() / 2,
		(float)aqua::GetWindowHeight() - m_UiSprite.GetTextureHeight()
	);

	// 表示するメッセージが徐々に小さくなっていくような動きを与える
	m_UiSprite.scale.x = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), m_message_max_scale, 1.0f);
	m_UiSprite.scale.y = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), m_message_max_scale, 1.0f);

	// 点滅した回数が３回以下なら処理を行う
	if (m_AlphaCount <= m_alpha_count)
	{
		// 不透明でなければ不透明に近づける
		if (m_UiSprite.color.alpha <= 250) m_UiSprite.color.alpha += 5;

		// 透明にする
		else m_UiSprite.color.alpha = 0;
	}

	// 透明になったら透明カウントを＋１する
	if (m_UiSprite.color.alpha == 0) m_AlphaCount++;

	// ４回以上透明になったら徐々にメッセージを大きくし、透明にさせることで消えていくようにする
	if (m_AlphaCount >= m_alpha_count + 1)
	{
		// メッセージ消滅タイマー更新
		m_FinishMessageTimer.Update();

		// 徐々に大きくなる（Ｘ軸）
		m_UiSprite.scale.x = aqua::easing::OutQuintic(m_FinishMessageTimer.GetTime(), m_FinishMessageTimer.GetLimit(), 1.0f, m_message_scale);

		// 徐々に小さくなる（Ｙ軸）
		m_UiSprite.scale.y = aqua::easing::OutQuintic(m_FinishMessageTimer.GetTime(), m_FinishMessageTimer.GetLimit(), m_message_scale, 0.0f);

		// 透明になっていく
		m_UiSprite.color.alpha -= 6;
	}

	// 消滅タイマー終了時にクラスオブジェクトを削除する
	if (m_FinishMessageTimer.Finished())
	{
		IGameObject::DeleteObject();
	}
}

void CShowMessage::Draw(void)
{
	// 既に表示されているメッセージの上に上書きするために長方形の黒を上書きさせ、その上に新しいメッセージを描画する
	DrawBox(0, aqua::GetWindowHeight() - m_UiSprite.GetTextureHeight(), aqua::GetWindowWidth(), aqua::GetWindowHeight(), 0x00000000, true);

	// メッセージの描画
	m_UiSprite.Draw();
}

void CShowMessage::Finalize(void)
{
	// メッセージ画像の解放
	m_UiSprite.Delete();
}