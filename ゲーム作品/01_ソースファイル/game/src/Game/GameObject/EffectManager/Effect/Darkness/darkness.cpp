#include "darkness.h"

#include "../../../UnitManager/Unit/Player/player.h"
#include "../../../UnitManager/unit_manager.h"
#include "../../../SoundManager/sound_creater.h"

const aqua::CVector2 CDarkness::m_light_brightness				= { 15.0f,15.0f };
const aqua::CVector2 CDarkness::m_light_brightness_for_enemy	= { 3.0f,3.0f };
const float CDarkness::m_darkness_time							= 5.0f;
const float CDarkness::m_darkness_time_for_enemy				= 7.0f;
const float CDarkness::m_flash_time								= 1.0f;

CDarkness::CDarkness(IGameObject* parent)
	// parent(CEffectManager)
	: IEffect(parent,"Darkness")
	, m_FlashFlag(false)
	, m_DarknessFlag(true)
	, m_Player_P(nullptr)
{
}

void CDarkness::Initialize(void)
{
	// �T�[�t�F�C�X�𐶐��iX�T�C�Y�AY�T�C�Y�A�A���t�@�`�����l���̎g�p�j
	m_DarknessArea.Create(aqua::GetWindowWidth(), aqua::GetWindowHeight(), true);

	// �T�[�t�F�C�X�`��p�X�v���C�g�𐶐�
	m_SurfaceSprite.Create(m_DarknessArea);

	// �����X�v���C�g�𐶐�
	m_LightSprite.Create("data/texture/others/light.png");

	// �����X�v���C�g�̊�_�𒆐S�ɂ���
	m_LightSprite.anchor = { (float)m_LightSprite.GetTextureWidth() / 2,(float)m_LightSprite.GetTextureHeight() / 2 };

	// �����X�v���C�g�̃u�����h���[�h���i���Z�����j�ɂ���
	m_LightSprite.blend_mode = aqua::ALPHABLEND::SUB;

	// �ÈŃX�v���C�g�𐶐�
	m_DarknessSprite.Create("data/texture/others/darkness.png");

	// ���C�g�̖��邳�i�T�C�Y�ݒ�j�i�傫�߁j
	m_LightSprite.scale = m_light_brightness;

	// �G�����̃N���X�I�u�W�F�N�g�𐶐������Ƃ��̖��邳�i�T�C�Y�j
	if (m_Category == CATEGORY_ID::ENEMY)
	{
		// ���C�g�̖��邳�i�T�C�Y�ݒ�j�i�����߁j
		m_LightSprite.scale = m_light_brightness_for_enemy;
	}

	// �v���C���[�N���X�I�u�W�F�N�g�̃|�C���^�̎擾
	m_Player_P = ((CPlayer*)aqua::FindGameObject("Player"));

	// �t���b�V���p�̃X�v���C�g�̐���
	m_FlashSprite.Create("data/texture/others/white.png");

	// �t���b�V���p�X�v���C�g�͓����ŏ��������Ă���
	m_FlashSprite.color.alpha = 0;

	// �J�e�S���[���v���C���[�Ȃ�ÈŎ��Ԃ��T�b�ɂ���
	if (m_Category == CATEGORY_ID::PLAYER) m_DarknessTimer.Setup(m_darkness_time);

	// �v���C���[�ȊO�̃J�e�S���[�Ȃ�V�b�ɂ���
	else m_DarknessTimer.Setup(m_darkness_time_for_enemy);

	// �t���b�V������
	m_FlashTimer.Setup(m_flash_time);
}

void CDarkness::Update(void)
{
	// �ÈŃ^�C�}�[�X�V
	m_DarknessTimer.Update();

	// �ÈŎ��Ԍv���I����
	if (m_DarknessTimer.Finished())
	{
		// �t���b�V���t���O��FALSE�Ȃ�
		if (!m_FlashFlag)
		{
			// �t���b�V���X�v���C�g��s�����ɂ���i��ʐ^������Ԃɂ���j
			m_FlashSprite.color.alpha = 255;

			((CSoundCreater*)aqua::FindGameObject("SoundManager"))->Play(SOUND_ID::EFFECT_FLASH);
		}

		// �t���b�V���^�C�}�[���I�����Ă��Ȃ����
		if (!m_FlashTimer.Finished())
		{
			// �t���b�V���^�C�}�[�X�V
			m_FlashTimer.Update();

			// �t���b�V���p�X�v���C�g�����X�ɓ����ɂ��Ă���
			m_FlashSprite.color.alpha -= 5;
		}
		// �^�C�}�[���I�����Ă���΃N���X�I�u�W�F�N�g�̍폜���s��
		else if (m_FlashTimer.Finished())
		{
			IGameObject::DeleteObject();
		}

		//�@�t���b�V���t���O��TRUE�ɂ���
		m_FlashFlag = true;
	}

	// ���C�g�̈ʒu���v���C���[�̈ʒu�Ɠ����悤�ɂ���
	m_LightSprite.position = m_Player_P->GetCenterPosition() - aqua::CVector2::ONE * m_LightSprite.GetTextureWidth()/2;
}

void CDarkness::Draw(void)
{
	// �T�[�t�F�C�X�G���A�̕`��
	m_DarknessArea.Begin();
	{
		// �w�i���ɐݒ�
		aqua::Clear(0x00000000);

		// �ÈŃX�v���C�g��`��
		m_DarknessSprite.Draw();

		// ���Z�������������X�v���C�g���ォ��`�悷�邱�ƂŁA�ÈŃX�v���C�g�̓����x�𔲂��Ƃ炳��Ă���悤�ɂ݂���
		m_LightSprite.Draw();
	}
	// �T�[�t�F�C�X�G���A�̕`����I��
	m_DarknessArea.End();

	// �T�[�t�F�C�X�̕`��
	m_SurfaceSprite.Draw();

	// �t���b�V���X�v���C�g�̕`��
	m_FlashSprite.Draw();
}

void CDarkness::Finalize(void)
{
	// �X�v���C�g���̃��������
	m_FlashSprite.Delete();
	m_SurfaceSprite.Delete();
	m_LightSprite.Delete();
	m_DarknessSprite.Delete();
	m_DarknessArea.Delete();
}