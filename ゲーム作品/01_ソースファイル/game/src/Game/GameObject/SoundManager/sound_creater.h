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
public: // ���J�����o�֐�

	// �R���X�g���N�^
	CSoundCreater(IGameObject* parent);

	// �f�X�g���N�^
	~CSoundCreater()		override = default;

	// �������֐�
	void Initialize(void)	override;

public: // ���J�����o�֐�

	// ID�ɑΉ������T�E���h���Đ�
	void Play(SOUND_ID sound_id);

	// ID�ɑΉ������T�E���h���~
	void Stop(SOUND_ID sound_id);

	// ID�ɑΉ������T�E���h�̉��ʂ�ݒ�
	void SetVolume(SOUND_ID sound_id, const int set_volume);

private: // ����J�����o�֐�

	// CSV�t�@�C���̃T�E���h�t�@�C����ǂݍ��݃T�E���h�n���h�����쐬����
	void LoadSoundFile(const std::string& sound_file_name);

private: // ����J�����o�ϐ�

	// �T�E���h���X�g�i vector )
	std::vector<aqua::CSoundPlayer>	m_SoundList;
};