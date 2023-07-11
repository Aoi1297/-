#include "item.h"
#include "../../UnitManager/Unit/Player/player.h"

const float IItem::m_item_move_speed	= 1.0f;
const float IItem::m_item_acceleration	= 0.01f;
const float IItem::m_easing_timer		= 0.5f;
const float IItem::m_item_max_scale		= 15.0f;
const float IItem::m_item_scale			= 1.3f;

IItem::IItem(IGameObject* parent, const std::string& object_name)
	// parent(CItemManager)
	: IGameObject(parent, object_name)
	, m_Player_P(nullptr)
	, m_MoveSpeed(m_item_move_speed)
{
}

void IItem::CreateSprite(const std::string& sprite_file_name)
{
	// アイテム画像を読み込む
	m_ItemSprite.Create(sprite_file_name);

	// スプライトの基準点を中心に設定
	m_ItemSprite.anchor = { (float)m_ItemSprite.GetTextureWidth() / 2,(float)m_ItemSprite.GetTextureHeight() / 2 };
}

void IItem::SetStatus(const ITEM_ID& id, const aqua::CVector2& create_pos)
{
	// アイテムIDを設定
	m_ItemId = id;

	// 生成位置設定
	m_ItemSprite.position = m_Position = create_pos;

	// プレイヤークラスポインタを取得
	m_Player_P = (CPlayer*)aqua::FindGameObject("Player");

	// 出現時の演出に使用するイージングタイマーの設定
	m_EasingTimer.Setup(m_easing_timer);

	// 初期化関数を呼び出す
	Initialize();
}

void IItem::Update()
{
	// タイマー更新
	TimerUpdate();

	// 出現時の効果
	SpawanEffect();

	// 動きの処理
	Movement();
}

void IItem::Draw()
{
	// 毎フレームRGB全ての要素をランダムで取得し、色を変化させる
	m_ItemSprite.color = GetColor(aqua::Rand(aqua::CColor::MAX_COLOR), aqua::Rand(aqua::CColor::MAX_COLOR), aqua::Rand(aqua::CColor::MAX_COLOR));

	// アイテムの描画
	m_ItemSprite.Draw();
}

void IItem::Finalize()
{
	// アイテムのスプライトのメモリ解放
	m_ItemSprite.Delete();
}

void IItem::HitItem()
{
	// プレイヤーのパワーアップを行う
	m_Player_P->PowerUp(m_ItemId);

	// アイテムを取得したら消滅させる
	IGameObject::DeleteObject();
}

aqua::CVector2 IItem::GetCenterPosition(void)
{
	return { m_Position.x + (float)m_ItemSprite.GetTextureWidth() / 2,m_Position.y + (float)m_ItemSprite.GetTextureHeight() / 2 };
}

void IItem::TimerUpdate(void)
{
	// タイマー更新
	if (!m_EasingTimer.Finished()) m_EasingTimer.Update();
}

void IItem::SpawanEffect(void)
{
	// 出現時に徐々に画像サイズ小さくなっていくように出現させる
	m_ItemSprite.scale.x = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), m_item_max_scale, m_item_scale);
	m_ItemSprite.scale.y = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), m_item_max_scale, m_item_scale);
}

void IItem::Movement(void)
{
	// 徐々に移動速度が加速する
	m_MoveSpeed += m_item_acceleration;

	// 移動処理
	m_Position.x -= m_MoveSpeed;

	// 画像の移動処理
	m_ItemSprite.position = m_Position;
}
