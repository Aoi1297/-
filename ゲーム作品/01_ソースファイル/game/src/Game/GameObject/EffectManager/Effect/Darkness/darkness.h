#pragma once

#include "../effect.h"

// �O���錾
class CPlayer;
class CBulletManager;

class CDarkness : public IEffect
{
public: // ���J�����o�֐�

	// �R���X�g���N�^
	CDarkness		(IGameObject* parent);

	// �f�X�g���N�^
	~CDarkness		(void) = default;

	// �������֐�
	void Initialize	(void)	override;

	// �X�V�֐�
	void Update		(void)	override;

	// �`��֐�
	void Draw		(void)	override;

	// ����֐�
	void Finalize	(void)	override;

private: // ����J�����o�ϐ�

	// �ÈŃG���A�p�T�[�t�F�C�X
	aqua::CSurface m_DarknessArea;

	// �T�[�t�F�C�X�p�X�v���C�g
	aqua::CSprite m_SurfaceSprite;

	// �����X�v���C�g
	aqua::CSprite m_LightSprite;

	// �ÈŃX�v���C�g
	aqua::CSprite m_DarknessSprite;

	// �t���b�V���X�v���C�g
	aqua::CSprite m_FlashSprite;

	// �t���b�V���t���O
	bool m_FlashFlag;
	
	// �ÈŃt���O
	bool m_DarknessFlag;

	// �t���b�V���^�C�}�[
	aqua::CTimer m_FlashTimer;

	// �ÈŃ^�C�}�[
	aqua::CTimer m_DarknessTimer;

	// �v���C���[�N���X�I�u�W�F�N�g�̃|�C���^�ϐ�
	CPlayer* m_Player_P;

private: // ����J�����o�萔
	
	static const aqua::CVector2 m_light_brightness;				// !< ���C�g�̖��邳
	static const aqua::CVector2 m_light_brightness_for_enemy;	// !< ���C�g�̖��邳
	static const float m_darkness_time;							// !< �ÈŎ���
	static const float m_darkness_time_for_enemy;				// !< �ÈŎ���
	static const float m_flash_time;							// !< �t���b�V������
};