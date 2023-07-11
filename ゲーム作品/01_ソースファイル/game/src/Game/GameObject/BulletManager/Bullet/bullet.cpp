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
	// �摜�̓ǂݍ���
	m_BulletSprite.Create(sprite_file_name);

	// �e�̉摜�̃u�����g���[�h�����Z�����ɂ���
	m_BulletSprite.blend_mode = aqua::ALPHABLEND::ADD;

	// ��]�̊�_���摜�̒��S�ɐݒ�
	m_BulletSprite.anchor = { (float)m_BulletSprite.GetTextureWidth() / 2,(float)m_BulletSprite.GetTextureHeight() / 2 };

	// �e�̕����i�摜�̊p�x�j�̐ݒ�
	m_BulletSprite.rotation = aqua::DegToRad(m_Direction);

	// �e�̐����ʒu�𔭎˂������j�b�g�̒��S�ʒu�ɂ���
	m_Position.x -= m_BulletSprite.GetTextureWidth() / 2;
	m_Position.y -= m_BulletSprite.GetTextureHeight() / 2;
}

void IBullet::SetStatus(const CATEGORY_ID& category_id, const aqua::CVector2& center_position, const float& bullet_speed, const float& direction)
{
	// �G�����������ʂ���ID�̏�����
	m_Category = category_id;

	// �e���̂̑��x
	m_BulletSpeed = bullet_speed;

	// �������̊p�x�ݒ�
	m_Direction = direction;

	// �e�̈ړ����x�iX���W�j
	m_Velocity.x = cos(aqua::DegToRad(m_Direction));

	// �e�̈ړ����x�iY���W�j
	m_Velocity.y = sin(aqua::DegToRad(m_Direction));

	// �e�̈ʒu�̏�����
	m_Position = center_position;

	// �G�t�F�N�g�}�l�[�W���[�N���X�I�u�W�F�N�g�|�C���^�̎擾
	m_EffectManager = ((CEffectManager*)aqua::FindGameObject("EffectManager"));

	// ���g�̏������֐����Ăяo��
	Initialize();
}

void IBullet::Update()
{
	// �e���g�̓����̌v�Z���s��
	OriginalMovement();

	// �����ɑ΂��Đi��ł����e�̌v�Z
	DirectionMove();
}

void IBullet::Draw(void)
{
	// �e�X�v���C�g�̕`����s��
	m_BulletSprite.Draw();

	m_FlashSprite.Draw();
}

void IBullet::Finalize()
{
	// �e�X�v���C�g�̉���������s��
	m_BulletSprite.Delete();

	m_FlashSprite.Delete();
}

void IBullet::DirectionMove()
{
	// �e�̈ړ�����
	m_Position += m_BulletSpeed * m_Velocity;

	// �ʒu�̍X�V
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
