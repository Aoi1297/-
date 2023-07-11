#include "dead_enemy.h"

#include "../../../SoundManager/sound_creater.h"

const float CDeadEnemy::m_easing_time	= 2.0f;
const float CDeadEnemy::m_max_size		= 10.0f;
const float CDeadEnemy::m_start_size	= 6.0f;
const float CDeadEnemy::m_final_size	= 0.0f;
const float CDeadEnemy::m_max_angle		= 720.0f;
const int CDeadEnemy::	m_add_alpha		= 10;

CDeadEnemy::CDeadEnemy(IGameObject* parent)
	// paretn(CEffectManager)
	: IEffect(parent, "DeadEnemyEffect")
{
}

void CDeadEnemy::Initialize(void)
{
	// 効果音を鳴らす
	((CSoundCreater*)aqua::FindGameObject("SoundManager"))->Play(SOUND_ID::EFFECT_DEAD);

	// 破壊時に表示するエフェクトスプライトの生成
	m_EffectSprite.Create("data/texture/effect/destroy.png");
	m_EffectSprite.color.alpha = 0;

	// エフェクトの基準点を中心にする
	m_EffectSprite.anchor = { (float)m_EffectSprite.GetTextureWidth() / 2, (float)m_EffectSprite.GetTextureHeight() / 2 };

	// エフェクトを発光させるためのスプライトを生成
	m_EffectFlash.Create("data/texture/effect/destroy_grow.png");

	// 発光用エフェクトの基準点を設定
	m_EffectFlash.anchor = m_EffectSprite.anchor;

	// 発光用エフェクトにぼかし処理を行う
	m_EffectFlash.ApplyGaussFilter(32, 1000);

	// エフェクトのブレンドモードを加算合成にする
	m_EffectFlash.blend_mode = aqua::ALPHABLEND::ADD;

	// イージングタイマーの設定
	m_EasingTimer.Setup(m_easing_time);
}

void CDeadEnemy::Update(void)
{
	// イージングタイマーの更新
	m_EasingTimer.Update();

	// エフェクトスプライトを徐々に不透明にしていく
	m_EffectSprite.color.alpha += m_add_alpha;

	// 徐々に小さくなるようにイージングをかける
	m_EffectFlash.scale.x = m_EffectSprite.scale.x = aqua::easing::InOutBack(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), m_start_size, m_final_size, m_max_size);
	m_EffectFlash.scale.y = m_EffectSprite.scale.y = aqua::easing::InOutBack(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), m_start_size, m_final_size, m_max_size);

	// エフェクトの回転もイージングを使用して行う
	m_EffectFlash.rotation = m_EffectSprite.rotation = aqua::DegToRad(aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), 0, m_max_angle));

	// エフェクトサイズを0.1以下になったらクラスオブジェクトの削除を行う
	if (m_EffectFlash.scale.x <= 0.1) IGameObject::DeleteObject();

	// エフェクトスプライトの位置更新
	m_EffectSprite.position = m_EffectFlash.position = m_Position;
}

void CDeadEnemy::Draw(void)
{
	m_EffectSprite.Draw();

	m_EffectFlash.Draw();
}

void CDeadEnemy::Finalize(void)
{
	m_EffectFlash.Delete();

	m_EffectSprite.Delete();
}
