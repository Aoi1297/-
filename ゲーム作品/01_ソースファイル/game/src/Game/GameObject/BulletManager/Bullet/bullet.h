#pragma once

#include "aqua.h"

#include "../../UnitManager/Unit/unit.h"

// 前方宣言
class CEffectManager;
enum class CATEGORY_ID;

class IBullet : public aqua::IGameObject
{
public: // 公開メンバ関数

	// コンストラクタ
	IBullet								(IGameObject* parent, const std::string& object_name);

	// デストラクタ
	~IBullet							(void)	override = default;

	// 初期化関数
	void			CreateSprite		(const std::string& sprite_file_name);

	// 初期化関数
	void			SetStatus			(const CATEGORY_ID& id, const aqua::CVector2& center_position, const float& bullet_speed, const float& direction);

	// 更新関数
	void			Update				(void);

	// 描画関数
	virtual void	Draw				(void);

	// 解放関数
	virtual void	Finalize			(void);

	// 弾それぞれの特徴的な動きを行う
	virtual void	OriginalMovement	(void) = 0;

	// 方向に対して飛んでいく弾
	void			DirectionMove		(void);

	// 弾の中心位置取得
	aqua::CVector2	GetCenterPosition	(void);

	// 弾のカテゴリー取得
	CATEGORY_ID GetCategory();

protected: // 非公開メンバ変数

	// 弾のスプライト
	aqua::CSprite	m_BulletSprite;

	// 弾の位置
	aqua::CVector2	m_Position;

	// 弾発光用のスプライト
	aqua::CSprite m_FlashSprite;

	//　速度量
	aqua::CVector2 m_Velocity;

	// 弾の速度
	float m_BulletSpeed;

	// 弾の角度
	float m_Direction;

	// 弾の角度
	CATEGORY_ID m_Category;

	// エフェクトマネージャークラスオブジェクトのポインタ変数
	CEffectManager* m_EffectManager;
};