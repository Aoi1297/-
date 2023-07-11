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
	// �A�C�e���摜��ǂݍ���
	m_ItemSprite.Create(sprite_file_name);

	// �X�v���C�g�̊�_�𒆐S�ɐݒ�
	m_ItemSprite.anchor = { (float)m_ItemSprite.GetTextureWidth() / 2,(float)m_ItemSprite.GetTextureHeight() / 2 };
}

void IItem::SetStatus(const ITEM_ID& id, const aqua::CVector2& create_pos)
{
	// �A�C�e��ID��ݒ�
	m_ItemId = id;

	// �����ʒu�ݒ�
	m_ItemSprite.position = m_Position = create_pos;

	// �v���C���[�N���X�|�C���^���擾
	m_Player_P = (CPlayer*)aqua::FindGameObject("Player");

	// �o�����̉��o�Ɏg�p����C�[�W���O�^�C�}�[�̐ݒ�
	m_EasingTimer.Setup(m_easing_timer);

	// �������֐����Ăяo��
	Initialize();
}

void IItem::Update()
{
	// �^�C�}�[�X�V
	TimerUpdate();

	// �o�����̌���
	SpawanEffect();

	// �����̏���
	Movement();
}

void IItem::Draw()
{
	// ���t���[��RGB�S�Ă̗v�f�������_���Ŏ擾���A�F��ω�������
	m_ItemSprite.color = GetColor(aqua::Rand(aqua::CColor::MAX_COLOR), aqua::Rand(aqua::CColor::MAX_COLOR), aqua::Rand(aqua::CColor::MAX_COLOR));

	// �A�C�e���̕`��
	m_ItemSprite.Draw();
}

void IItem::Finalize()
{
	// �A�C�e���̃X�v���C�g�̃��������
	m_ItemSprite.Delete();
}

void IItem::HitItem()
{
	// �v���C���[�̃p���[�A�b�v���s��
	m_Player_P->PowerUp(m_ItemId);

	// �A�C�e�����擾��������ł�����
	IGameObject::DeleteObject();
}

aqua::CVector2 IItem::GetCenterPosition(void)
{
	return { m_Position.x + (float)m_ItemSprite.GetTextureWidth() / 2,m_Position.y + (float)m_ItemSprite.GetTextureHeight() / 2 };
}

void IItem::TimerUpdate(void)
{
	// �^�C�}�[�X�V
	if (!m_EasingTimer.Finished()) m_EasingTimer.Update();
}

void IItem::SpawanEffect(void)
{
	// �o�����ɏ��X�ɉ摜�T�C�Y�������Ȃ��Ă����悤�ɏo��������
	m_ItemSprite.scale.x = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), m_item_max_scale, m_item_scale);
	m_ItemSprite.scale.y = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), m_item_max_scale, m_item_scale);
}

void IItem::Movement(void)
{
	// ���X�Ɉړ����x����������
	m_MoveSpeed += m_item_acceleration;

	// �ړ�����
	m_Position.x -= m_MoveSpeed;

	// �摜�̈ړ�����
	m_ItemSprite.position = m_Position;
}
