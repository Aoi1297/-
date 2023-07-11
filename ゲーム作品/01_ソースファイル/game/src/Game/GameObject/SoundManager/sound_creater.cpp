#include "sound_creater.h"

CSoundCreater::CSoundCreater(IGameObject* parent)
	// parent(CGame)
	: IGameObject(parent, "SoundManager")
{
}

void CSoundCreater::Initialize(void)
{
	// サウンドファイルを読み込み
	LoadSoundFile("data/csv/sound_file.csv");
}

void CSoundCreater::Play(SOUND_ID sound_id)
{
	m_SoundList[(int)sound_id].Play();
}

void CSoundCreater::Stop(SOUND_ID sound_id)
{
	m_SoundList[(int)sound_id].Stop();
}

void CSoundCreater::SetVolume(SOUND_ID sound_id, const int set_volume)
{
	m_SoundList[(int)sound_id].SetVolume(set_volume);
}

void CSoundCreater::LoadSoundFile(const std::string& sound_file_name)
{
	// CSVローダー生成
	aqua::CCSVLoader csv_loader;

	// SCVファイルの読み込み
	csv_loader.Load(sound_file_name);

	// 縦のセル数だけ繰り返す
	for (int i = 0; i < csv_loader.GetRows(); ++i)
	{
		// サウンドクラスを生成
		aqua::CSoundPlayer sound;

		// Create( sound_file_name , sound_loop_flag )
		sound.Create(csv_loader.GetString(i, 0), csv_loader.GetInteger(i, 1));

		// 読み込んだサウンドをリストに追加
		m_SoundList.push_back(sound);
	}

	// SCVファイルの解放
	csv_loader.Unload();
}
