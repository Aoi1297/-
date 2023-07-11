#include "title.h"

#include "../../../SoundManager/sound_creater.h"

const unsigned char		CTitle::m_max_random_color			= 200;
const int				CTitle::m_pixel_width				= 8;
const int				CTitle::m_param						= 100;
const aqua::CVector2	CTitle::m_title_scale				= { 1.5,1.5 };
const float				CTitle::m_title_position_y			= 100;
const float				CTitle::m_title_massage_position_y	= 300;
const float				CTitle::m_title_massage_scale_up	= 0.05f;
const int				CTitle::m_particle_quantity			= 100;
const int				CTitle::m_particle_random_scale_max	= 5;
const int				CTitle::m_particle_random_angle_max	= 360;
const float				CTitle::m_flash_screen_time			= 5.0f;
const float				CTitle::m_flash_object_time			= 0.5f;

CTitle::CTitle(aqua::IGameObject* parent)
	// parent(CSceneManager)
	: IScene(parent, "Title")
	, m_SceneManager_P(nullptr)
{
}

void CTitle::Initialize(void)
{
	// �V�[���}�l�[�W���[�N���X�|�C���^���擾
	m_SceneManager_P = (CSceneManager*)aqua::FindGameObject("SceneManager");

	// �T�E���h�}�l�[�W���[�N���X�|�C���^���擾
	CSoundCreater* sound_manager = (CSoundCreater*)aqua::FindGameObject("SoundManager");

	// �Q�[��BGM�̍Đ����~
	sound_manager->Stop(SOUND_ID::BGM_GAME);

	// �{�XBGM�̍Đ����~
	sound_manager->Stop(SOUND_ID::BGM_BOSS);

	// �^�C�g��BGM���Đ�
	sound_manager->Play(SOUND_ID::BGM_TITLE);

	//////////////////////////////////////////////// �X�v���C�g�n�̏����� ////////////////////////////////////////////////
	{
		// �p�[�e�B�N���摜�̓ǂݍ��݁������ݒ�
		{
			m_ParticleSprite.Create("data/texture/others/particle.png");
			m_ParticleSprite.anchor			= { (float)m_ParticleSprite.GetTextureWidth() / 2, (float)m_ParticleSprite.GetTextureHeight() / 2 };
			m_ParticleSprite.color.alpha	= 0;
		}

		// �G�t�F�N�g�p�p�[�e�B�N���摜�̓ǂݍ��݁������ݒ�
		{
			m_ParticleEffectSprite.Create("data/texture/others/particle.png");
			m_ParticleEffectSprite.anchor		= { (float)m_ParticleEffectSprite.GetTextureWidth() / 2, (float)m_ParticleEffectSprite.GetTextureHeight() / 2 };
			m_ParticleEffectSprite.blend_mode	= aqua::ALPHABLEND::ADD;
			m_ParticleEffectSprite.color		= GetColor(aqua::Rand(m_max_random_color), aqua::Rand(m_max_random_color), aqua::Rand(m_max_random_color));
			m_ParticleEffectSprite.color.alpha	= 0;
		}

		// �G�t�F�N�g�p�^�C�g���摜�̓ǂݍ��݁������ݒ�
		{
			m_TitleEffectSprite.Create("data/texture/others/title_blur.png");
			m_TitleEffectSprite.anchor		= { (float)m_TitleEffectSprite.GetTextureWidth() / 2, (float)m_TitleEffectSprite.GetTextureHeight() };
			m_TitleEffectSprite.scale		= m_title_scale;
			m_TitleEffectSprite.blend_mode	= aqua::ALPHABLEND::ADD;
			m_TitleEffectSprite.color.alpha = 0;
			m_TitleEffectSprite.position	= { (float)(aqua::GetWindowWidth() / 2 - m_TitleEffectSprite.GetTextureWidth() / 2),(float)((aqua::GetWindowHeight() / 2 - m_TitleEffectSprite.GetTextureHeight() / 2) - m_title_position_y) };
			m_TitleEffectSprite.ApplyGaussFilter(m_pixel_width, m_param);
		}

		// �^�C�g���摜�̓ǂݍ��݁������ݒ�
		{
			m_TitleSprite.Create("data/texture/others/title.png");
			m_TitleSprite.anchor		= m_TitleEffectSprite.anchor;
			m_TitleSprite.scale			= m_TitleEffectSprite.scale;
			m_TitleSprite.blend_mode	= aqua::ALPHABLEND::ADD;
			m_TitleSprite.color.alpha	= m_TitleEffectSprite.color.alpha;
			m_TitleSprite.position		= m_TitleEffectSprite.position;
		}

		// �G�t�F�N�g�p�^�C�g�����b�Z�[�W�摜�̓ǂݍ��݁������ݒ�
		{
			m_TitleMassageEffectSprite.Create("data/texture/others/tittle_massage_blur.png");
			m_TitleMassageEffectSprite.anchor		= { (float)m_TitleMassageEffectSprite.GetTextureWidth() / 2,(float)m_TitleMassageEffectSprite.GetTextureHeight() / 2 };
			m_TitleMassageEffectSprite.scale.y		= 0;
			m_TitleMassageEffectSprite.blend_mode	= aqua::ALPHABLEND::ADD;
			m_TitleMassageEffectSprite.color.alpha	= 0;
			m_TitleMassageEffectSprite.position		= { (float)(aqua::GetWindowWidth() / 2 - m_TitleMassageEffectSprite.GetTextureWidth() / 2),(float)((aqua::GetWindowHeight() / 2 - m_TitleMassageEffectSprite.GetTextureHeight() / 2) + m_title_massage_position_y) };
			m_TitleMassageEffectSprite.ApplyGaussFilter(m_pixel_width, m_param);
		}

		// �^�C�g�����b�Z�[�W�摜�̓ǂݍ��݁������ݒ�
		{
			m_TitleMassageSprite.Create("data/texture/others/title_massage.png");
			m_TitleMassageSprite.anchor			= m_TitleMassageEffectSprite.anchor;
			m_TitleMassageSprite.scale.y		= m_TitleMassageEffectSprite.scale.y;
			m_TitleMassageSprite.position		= m_TitleMassageEffectSprite.position;
			m_TitleMassageSprite.color.alpha	= m_TitleMassageEffectSprite.color.alpha;
		}

		// ��ʃt���b�V���摜�̓ǂݍ��݁������ݒ�
		{
			m_FlashScreenSprite.Create("data/texture/others/white.png");
			m_FlashScreenSprite.color.alpha = 0;
		}
	}

	//////////////////////////////////////////////// ���q�摜�̃f�[�^�̏������i���q�̐������J��Ԃ��j////////////////////////////////////////////////
	for (int i = 0; i < m_particle_quantity; ++i)
	{
		/////// �ʒu�̃����_������ ///////
		PARTICLE_DATA random;
		{
			// ��ʂ���͂ݏo���ʒu�ɐ�������Ȃ��悤�ɗ��q�̍ő�T�C�Y������
			random.position.x = (float)aqua::Rand(aqua::GetWindowWidth() - m_ParticleEffectSprite.GetTextureWidth() / 2 * m_particle_random_scale_max);
			random.position.y = (float)aqua::Rand(aqua::GetWindowHeight() - m_ParticleEffectSprite.GetTextureHeight() / 2 * m_particle_random_scale_max);
		}

		/////// �傫���̃����_������ ///////
		{
			// X��Y�͓����傫�����ɂ���
			random.scale.x = random.scale.y = (float)aqua::Rand(m_particle_random_scale_max);
		}

		/////// �p�x�̃����_������ ///////
		{
			// �����łO����R�U�O�̊p�x���擾����
			random.angle = (float)aqua::Rand(m_particle_random_angle_max);
		}

		// �p�[�e�B�N�����X�g�Ƀf�[�^�ǉ�
		m_ParticleDataList.push_back(random);
	}

	//////////////////////////////////////////////// �^�C�}�[�n������ ////////////////////////////////////////////////
	{
		// ��ʃt���b�V���J�n���Ԑݒ�
		m_FlashScreenTimer.Setup(m_flash_screen_time);

		// �����I�u�W�F�N�g�̓_�Ŏ��Ԑݒ�
		m_FlashObjectTimer.Setup(m_flash_object_time);
	}
}

void CTitle::Update(void)
{
	// Z�L�[��������Ă��邩�̔���
	CheckKeyZ();

	// �^�C�}�[�̍X�V����
	TimerUpdate();

	// �p�[�e�B�N���̈ړ�����
	ParticleMove();
}

void CTitle::Draw(void)
{
	// �p�[�e�B�N�����X�g
	for (auto& element : m_ParticleDataList)
	{
		// �ʒu�Ƒ傫���𖈃t���[���ݒ�
		m_ParticleEffectSprite.position = m_ParticleSprite.position = element.position;
		m_ParticleEffectSprite.scale	= m_ParticleSprite.scale	= element.scale;

		// �p�[�e�B�N���G�t�F�N�g�X�v���C�g�̕`��
		m_ParticleEffectSprite.	Draw();

		// �p�[�e�B�N���X�v���C�g�̕`��
		m_ParticleSprite.		Draw();
	}

	// �^�C�g���G�t�F�N�g�X�v���C�g�̕`��
	m_TitleEffectSprite.		Draw();

	// �^�C�g���X�v���C�g�̕`��
	m_TitleSprite.				Draw();

	// �^�C�g�����b�Z�[�W�G�t�F�N�g�X�v���C�g�̕`��
	m_TitleMassageEffectSprite.	Draw();

	// �^�C�g�����b�Z�[�W�X�v���C�g�̕`��
	m_TitleMassageSprite.		Draw();

	// ��ʃt���b�V���X�v���C�g�̕`��
	m_FlashScreenSprite.		Draw();
}


void CTitle::Finalize(void)
{
	// �X�v���C�g�̃��������
	m_FlashScreenSprite.		Delete();	// !< ��ʃt���b�V���摜
	m_TitleMassageEffectSprite.	Delete();	// !< �^�C�g�����b�Z�[�W�G�t�F�N�g�摜
	m_TitleMassageSprite.		Delete();	// !< �^�C�g�����b�Z�[�W�摜
	m_TitleEffectSprite.		Delete();	// !< �^�C�g���G�t�F�N�g�摜
	m_TitleSprite.				Delete();	// !< �^�C�g���摜
	m_ParticleEffectSprite.		Delete();	// !< �p�[�e�B�N���G�t�F�N�g�摜
	m_ParticleSprite.			Delete();	// !< �p�[�e�B�N���摜
}

void CTitle::CheckKeyZ(void)
{
	// �uZ�v�L�[�������ꂽ��u�Q�[�����C���V�[���v�ֈړ�����
	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::Z))
	{
		m_SceneManager_P->ChangeScene(SCENE_ID::GAMEMAIN);
	}
}

void CTitle::TimerUpdate(void)
{
	// ��ʃt���b�V���^�C�}�[�N��
	if (!m_FlashScreenTimer.Finished()) m_FlashScreenTimer.Update();

	// �t���b�V���^�C�}�[���I�������烁�b�Z�[�W�̕\��������
	if (m_FlashScreenTimer.Finished() && m_TitleMassageSprite.scale.y <= aqua::CVector2::ONE.y)
	{
		m_TitleMassageSprite.scale.y += m_title_massage_scale_up;
		m_TitleMassageEffectSprite.scale = m_TitleEffectSprite.scale;
	}

	// ��ʃt���b�V���^�C�}�[���� //
	{
		// �����x��ύX����I�u�W�F�N�g�Q
		m_ParticleSprite.color.alpha		=
		m_TitleSprite.color.alpha			=
		m_TitleMassageSprite.color.alpha	=

		// �o�ߎ��Ԃ̊����ɂ���ĉ摜�̓����x��ω�������
		(unsigned char)(aqua::CColor::MAX_COLOR * m_FlashScreenTimer.GetTime() / m_FlashScreenTimer.GetLimit());
	}

	// ��ʃt���b�V���^�C�}�[���v��I��������A�I�u�W�F�N�g�t���b�V���^�C�}�[���N��
	if (m_FlashScreenTimer.Finished()) m_FlashObjectTimer.Update();

	// �I�u�W�F�N�g�t���b�V���^�C�}�[���� //
	{
		// �����x��ύX����I�u�W�F�N�g�Q
		m_ParticleEffectSprite.color.alpha	=
		m_TitleEffectSprite.color.alpha		=
		m_TitleEffectSprite.color.alpha		=

		// �o�ߎ��Ԃ̊����ɂ���ĉ摜�̓����x��ω�������
		(unsigned char)(aqua::CColor::MAX_COLOR * m_FlashObjectTimer.GetTime() / m_FlashObjectTimer.GetLimit());
	}

	// �I�u�W�F�N�g�^�C�}�[���v��I�������A�Čv������
	if (m_FlashObjectTimer.Finished()) m_FlashObjectTimer.Reset();
}

void CTitle::ParticleMove(void)
{
	// �p�[�e�B�N�����X�g����ʒu��ύX����
	for (auto& element : m_ParticleDataList)
	{
		// �p�[�e�B�N�����p�x�ɑΉ����������֐i�߂�
		element.position.x += cos(aqua::DegToRad(element.angle));
		element.position.y += sin(aqua::DegToRad(element.angle));

		// ���ǂɃp�[�e�B�N�����Ԃ�������
		if (element.position.x < 0 - m_ParticleEffectSprite.GetTextureWidth())
		{
			// �p�x���]
			element.angle += 180;
		}
		// �E�ǂɃp�[�e�B�N�����Ԃ�������
		else if (element.position.x > aqua::GetWindowWidth() - m_ParticleEffectSprite.GetTextureWidth())
		{
			// �p�x���]
			element.angle -= 180;
		}

		// ��ǂɃp�[�e�B�N�����Ԃ�������
		if (element.position.y < 0 - m_ParticleEffectSprite.GetTextureHeight())
		{
			// �p�x���]
			element.angle = -element.angle;
		}
		// ���ǂɃp�[�e�B�N�����Ԃ�������
		else if (element.position.y > aqua::GetWindowHeight() - m_ParticleEffectSprite.GetTextureHeight())
		{
			// �p�x���]
			element.angle = -element.angle;
		}
	}
}
