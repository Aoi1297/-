#pragma once

#include "../ui.h"

class CEffectManager;

class CUiGameClear : public IUserInterface
{
public: // 公開メンバ関数

	// コンストラクタ
	CUiGameClear	(IGameObject* parent);

	// デストラクタ
	~CUiGameClear	(void)	override = default;

	// 初期化関数
	void Initialize	(void)	override;

	// 更新関数
	void Update		(void)	override;

	// 描画関数
	void Draw		(void)	override;

	// 解放関数
	void Finalize	(void)	override;

private: // 非公開メンバ変数

	// エフェクトマネージャーのクラスポインタ
	CEffectManager* m_EffectManager_P;

	// ゲームクリアを表示するまでの時間
	aqua::CTimer m_GameClearTime;

	// エフェクトを生成する間隔
	aqua::CTimer m_EffectTime;

	// 描画フラグ
	bool DrawFlag;
};