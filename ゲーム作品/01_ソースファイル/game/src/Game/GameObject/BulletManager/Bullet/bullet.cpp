#include "bullet.h"

IBullet::IBullet(IGameObject* parent, const std::string& object_name)
	// parent(CBulletManager)
	: IGameObject(parent, object_name)
	, m_BulletSpeed(0)
	, m_Direction(0)
	, m_EffectManager(nullptr)
{
}

void IBullet::CreateSprite(const std::string& sprite_file_name)
{
	// 画像の読み込み
	m_BulletSprite.Create(sprite_file_name);

	// 弾の画像のブレントモードを加算合成にする
	m_BulletSprite.blend_mode = aqua::ALPHABLEND::ADD;

	// 回転の基準点を画像の中心に設定
	m_BulletSprite.anchor = { (float)m_BulletSprite.GetTextureWidth() / 2,(float)m_BulletSprite.GetTextureHeight() / 2 };

	// 弾の方向（画像の角度）の設定
	m_BulletSprite.rotation = aqua::DegToRad(m_Direction);

	// 弾の生成位置を発射したユニットの中心位置にする
	m_Position.x -= m_BulletSprite.GetTextureWidth() / 2;
	m_Position.y -= m_BulletSprite.GetTextureHeight() / 2;
}

void IBullet::SetStatus(const CATEGORY_ID& category_id, const aqua::CVector2& center_position, const float& bullet_speed, const float& direction)
{
	// 敵か味方を識別するIDの初期化
	m_Category = category_id;

	// 弾自体の速度
	m_BulletSpeed = bullet_speed;

	// 生成時の角度設定
	m_Direction = direction;

	// 弾の移動速度（X座標）
	m_Velocity.x = cos(aqua::DegToRad(m_Direction));

	// 弾の移動速度（Y座標）
	m_Velocity.y = sin(aqua::DegToRad(m_Direction));

	// 弾の位置の初期化
	m_Position = center_position;

	// エフェクトマネージャークラスオブジェクトポインタの取得
	m_EffectManager = ((CEffectManager*)aqua::FindGameObject("EffectManager"));

	// 自身の初期化関数を呼び出す
	Initialize();
}

void IBullet::Update()
{
	// 弾自身の動きの計算を行う
	OriginalMovement();

	// 方向に対して進んでいく弾の計算
	DirectionMove();
}

void IBullet::Draw(void)
{
	// 弾スプライトの描画を行う
	m_BulletSprite.Draw();

	m_FlashSprite.Draw();
}

void IBullet::Finalize()
{
	// 弾スプライトの解放処理を行う
	m_BulletSprite.Delete();

	m_FlashSprite.Delete();
}

void IBullet::DirectionMove()
{
	// 弾の移動処理
	m_Position += m_BulletSpeed * m_Velocity;

	// 位置の更新
	m_BulletSprite.position = m_Position;
}

aqua::CVector2 IBullet::GetCenterPosition()
{
	return { m_Position.x + (float)m_BulletSprite.GetTextureWidth() / 2,m_Position.y + (float)m_BulletSprite.GetTextureHeight() / 2 };
}

CATEGORY_ID IBullet::GetCategory()
{
	return m_Category;
}
