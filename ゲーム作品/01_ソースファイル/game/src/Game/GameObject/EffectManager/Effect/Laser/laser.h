#pragma once

#include "../effect.h"

class CLaser : public IEffect
{
public: // 公開メンバ関数

	// コンストラクタ
	CLaser(IGameObject* parent);

	// デストラクタ
	~CLaser() = default;

	// 初期化
	void Initialize(void)override;

	// 更新
	void Update(void)override;

	// 描画
	void Draw(void)override;
	
	// 解放
	void Finalize(void)override;

private: // 非公開メンバ変数

	static const aqua::CVector2 m_effect_size;
	static const float m_effect_decrease_size;
	static const int m_effect_decrease_alpha;
	static const int m_effect_delete_alpha;
};