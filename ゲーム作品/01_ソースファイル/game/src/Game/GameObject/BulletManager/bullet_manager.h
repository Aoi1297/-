#pragma once

#include "aqua.h"

enum class BULLET_ID
{
	NORMAL,
	HOMING,
	FIREWORK,
	DIRECTION,
};

// 前方宣言
class CUnitManager;
enum class CATEGORY_ID;

class CBulletManager : public aqua::IGameObject
{
public: // 公開メンバ関数

	// コンストラクタ
	CBulletManager	(IGameObject* parent);

	// デストラクタ
	~CBulletManager	(void)	override = default;

	// 初期化関数
	void Initialize	(void)	override;

	// 更新関数
	void Update		(void)	override;

	// 描画関数
	void Draw		(void)	override;

	// 解放関数
	void Finalize	(void)	override;

public: // 公開メンバ関数

	// 弾生成関数
	void CreateBullet(const CATEGORY_ID& category_id, const BULLET_ID& bullet_id, const aqua::CVector2& center_position, const float& bullet_speed, const float& direction);

private: // 非公開メンバ変数

	// ユニットマネージャークラスオブジェクトのポインタ変数
	CUnitManager* m_UnitManager_P;
};