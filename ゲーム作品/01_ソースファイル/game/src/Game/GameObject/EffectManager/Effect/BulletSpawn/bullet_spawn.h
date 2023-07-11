#pragma once

#include "../effect.h"

class CSpawn : public IEffect
{
public: // 公開メンバ関数

	// コンストラクタ
	CSpawn(IGameObject* parent);

	// デストラクタ
	~CSpawn() = default;

	// 初期化関数
	void Initialize(void)override;

	// 更新関数
	void Update(void)override;

private: // 非公開メンバ変数

	// 回転値
	float m_Rotation;

private: // 非公開メンバ定数

	static const float	m_easing_time;		// !< 効果時間
	static const float	m_sprite_size;		// !< スプライトサイズ
	static const int	m_alpha_decrease;	// !< スプライトサイズ
	static const int	m_delete_num;		// !< スプライトサイズ
};