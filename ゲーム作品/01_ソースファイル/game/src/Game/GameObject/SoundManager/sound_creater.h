#pragma once

#include "aqua.h"

enum class SOUND_ID
{
	BGM_TITLE,
	BGM_GAME,
	BGM_BOSS,
	EFFECT_FUTURE,
	EFFECT_CHARGE,
	EFFECT_SPAWN,
	EFFECT_FIRE,
	EFFECT_DEAD,
	EFFECT_ITEM,
	EFFECT_LASER,
	EFFECT_ENHANCEMENT,
	EFFECT_ALERT,
	EFFECT_FLASH,

	MAX,
};

class CSoundCreater : public aqua::IGameObject
{
public: // 公開メンバ関数

	// コンストラクタ
	CSoundCreater(IGameObject* parent);

	// デストラクタ
	~CSoundCreater()		override = default;

	// 初期化関数
	void Initialize(void)	override;

public: // 公開メンバ関数

	// IDに対応したサウンドを再生
	void Play(SOUND_ID sound_id);

	// IDに対応したサウンドを停止
	void Stop(SOUND_ID sound_id);

	// IDに対応したサウンドの音量を設定
	void SetVolume(SOUND_ID sound_id, const int set_volume);

private: // 非公開メンバ関数

	// CSVファイルのサウンドファイルを読み込みサウンドハンドルを作成する
	void LoadSoundFile(const std::string& sound_file_name);

private: // 非公開メンバ変数

	// サウンドリスト（ vector )
	std::vector<aqua::CSoundPlayer>	m_SoundList;
};