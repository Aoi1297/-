#pragma once

#include "../ui.h"

// 前方宣言
class CCameraManager;

class CUIScore : public IUserInterface
{
public: // 公開メンバ関数

	// コンストラクタ
	CUIScore(IGameObject* parent);

	// デストラクタ
	~CUIScore		(void)	override = default;

	// 初期化関数
	void Initialize	(void)	override;

	// 更新関数
	void Update		(void)	override;

	// 描画関数
	void Draw		(void)	override;

	// 解放関数
	void Finalize	(void)	override;

	// スコア加算関数
	void AddScore	(int score);

private: // 非公開メンバ変数

	// 現在のスコア
	int m_Score;

	// 一桁幅
	int m_DigitWidth;

	// 「SCORE」スプライト
	aqua::CSprite m_ScoreSprite;

	// 「0123456789」スプライト
	aqua::CSprite m_ScoreNumSprite;

	// カメラマネージャークラスオブジェクトのポインタ変数
	CCameraManager* m_CameraManager_P;

private: // 非公開メンバ定数

	static const aqua::CVector2 m_score_num_position;	// !< スコア（数字）の描画位置
};
