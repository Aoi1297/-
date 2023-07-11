#include "score.h"

#include "../../../CameraManager/camera_manager.h"

const aqua::CVector2 CUIScore::m_score_num_position{ 900,40 };

CUIScore::CUIScore(IGameObject* parent)
	// parent(CUiManager)
	: IUserInterface(parent,"UIScore")
	, m_Score(0)
	, m_DigitWidth(0)
	, m_CameraManager_P(nullptr)
{
}

void CUIScore::Initialize(void)
{
	// 「SCORE」画像の生成
	m_ScoreSprite.Create("data/texture/ui/score.png");

	// 「0123456789」画像の生成
	m_ScoreNumSprite.Create("data/texture/ui/score_num.png");
	// 「SCORE」の右に描画されるように調整
	m_ScoreNumSprite.position = m_score_num_position;

	// 一桁分の幅を取得
	m_DigitWidth = m_ScoreNumSprite.GetTextureWidth() / 10;

	// カメラマネージャークラスオブジェクトのポインタ取得
	m_CameraManager_P = (CCameraManager*)aqua::FindGameObject("CameraManager");
}

void CUIScore::Update(void)
{
	// 毎フレームスコアが加算される
	m_Score++;
}

void CUIScore::Draw(void)
{
	// 画面振動の値を取得
	aqua::CVector2 camera_pos = m_CameraManager_P->GetPosition();

	// 算出用のスコアを取得
	int score = m_Score;

	// スコア（数字）の描画を行う
	for (int i = 0; i < 10; ++i)
	{
		// スコアの一桁目の数字を取得
		int digit = score % 10;

		// 数字画像の描画範囲を取得した一桁目に応じた数字がある範囲に設定する
		m_ScoreNumSprite.rect.left = digit * m_DigitWidth;
		m_ScoreNumSprite.rect.right = digit * m_DigitWidth + m_DigitWidth;

		// 桁数に応じて数字の幅分左にずらして数字を並べる
		m_ScoreNumSprite.position.x = -m_DigitWidth * i + m_score_num_position.x + camera_pos.x;
		m_ScoreNumSprite.position.y = m_score_num_position.y + camera_pos.y;

		// 並べた数字を描画していく
		m_ScoreNumSprite.Draw();

		// 描画をおこなった桁を排除する
		score /= 10;
	}

	// 画面振動
	m_ScoreSprite.position = camera_pos;

	// 「SCORE」画像の描画
	m_ScoreSprite.Draw();
}

void CUIScore::Finalize(void)
{
	// スプライトのメモリ解放
	m_ScoreNumSprite.Delete();
	m_ScoreSprite.Delete();
}

void CUIScore::AddScore(int score)
{
	m_Score += score;
}
