#include "show_message.h"

#include "../../../ItemManager/item_manager.h"

const float CShowMessage::m_easing_time			= 1.0f;
const float CShowMessage::m_finish_message_time = 0.7f;
const float CShowMessage::m_message_max_scale	= 5.0f;
const float CShowMessage::m_message_scale		= 2.0f;
const int CShowMessage::m_alpha_count			= 3;

CShowMessage::CShowMessage(IGameObject* parent)
	// parent(CUiManager)
	: IUserInterface(parent, "UIPowerUp")
	, m_AlphaCount(0)
{
}

void CShowMessage::ShowMessage(const ITEM_ID& item_id)
{
	// �\������A�C�e�����b�Z�[�W�̎���
	m_ItemId = item_id;

	// ���������s��
	Initialize();
}

void CShowMessage::Initialize(void)
{
	// �\�����郁�b�Z�[�W�̔��ʂ��s��

	// ���[�U�[���[�^�[
	if (m_ItemId == ITEM_ID::LASER)
	{
		m_UiSprite.Create("data/texture/ui/laser_meter.png");
	}

	// ���[�U�[�X�s�[�h
	else if (m_ItemId == ITEM_ID::SPEED)
	{
		m_UiSprite.Create("data/texture/ui/laser_speed.png");
	}

	// ���˕����ǉ�
	else if (m_ItemId == ITEM_ID::DIRECTION)
	{
		m_UiSprite.Create("data/texture/ui/direction.png");
	}

	// ���ˊԊu�Z�k
	else if (m_ItemId == ITEM_ID::INTERVAL)
	{
		m_UiSprite.Create("data/texture/ui/interval.png");
	}

	// �\�����郁�b�Z�[�W�̊�_�𒆐S�ɂ���
	m_UiSprite.anchor = { (float)m_UiSprite.GetTextureWidth() / 2, (float)m_UiSprite.GetTextureHeight() / 2 };

	// ���b�Z�[�W�̕\���ʒu
	m_UiSprite.position = { (float)aqua::GetWindowWidth() / 2 - m_UiSprite.GetTextureWidth() / 2,(float)aqua::GetWindowHeight() - m_UiSprite.GetTextureHeight() };

	// ���b�Z�[�W�摜�̏��������x�̐ݒ�
	m_UiSprite.color.alpha = 0;

	// �C�[�W���O���Ԑݒ�
	m_EasingTimer.Setup(m_easing_time);

	// �I�����Ԑݒ�
	m_FinishMessageTimer.Setup(m_finish_message_time);
}

void CShowMessage::Update(void)
{
	// �C�[�W���O�^�C�}�[�̍X�V
	if (!m_EasingTimer.Finished())
	{
		m_EasingTimer.Update();
	}

	// �\�����郁�b�Z�[�W�����X�ɉ��ֈړ�����悤�ȓ�����^����
	m_UiSprite.position.y = aqua::easing::OutQuintic
	(
		m_EasingTimer.GetTime(),
		m_EasingTimer.GetLimit(),
		(float)aqua::GetWindowHeight() - m_UiSprite.GetTextureHeight() / 2,
		(float)aqua::GetWindowHeight() - m_UiSprite.GetTextureHeight()
	);

	// �\�����郁�b�Z�[�W�����X�ɏ������Ȃ��Ă����悤�ȓ�����^����
	m_UiSprite.scale.x = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), m_message_max_scale, 1.0f);
	m_UiSprite.scale.y = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), m_message_max_scale, 1.0f);

	// �_�ł����񐔂��R��ȉ��Ȃ珈�����s��
	if (m_AlphaCount <= m_alpha_count)
	{
		// �s�����łȂ���Εs�����ɋ߂Â���
		if (m_UiSprite.color.alpha <= 250) m_UiSprite.color.alpha += 5;

		// �����ɂ���
		else m_UiSprite.color.alpha = 0;
	}

	// �����ɂȂ����瓧���J�E���g���{�P����
	if (m_UiSprite.color.alpha == 0) m_AlphaCount++;

	// �S��ȏ㓧���ɂȂ����珙�X�Ƀ��b�Z�[�W��傫�����A�����ɂ����邱�Ƃŏ����Ă����悤�ɂ���
	if (m_AlphaCount >= m_alpha_count + 1)
	{
		// ���b�Z�[�W���Ń^�C�}�[�X�V
		m_FinishMessageTimer.Update();

		// ���X�ɑ傫���Ȃ�i�w���j
		m_UiSprite.scale.x = aqua::easing::OutQuintic(m_FinishMessageTimer.GetTime(), m_FinishMessageTimer.GetLimit(), 1.0f, m_message_scale);

		// ���X�ɏ������Ȃ�i�x���j
		m_UiSprite.scale.y = aqua::easing::OutQuintic(m_FinishMessageTimer.GetTime(), m_FinishMessageTimer.GetLimit(), m_message_scale, 0.0f);

		// �����ɂȂ��Ă���
		m_UiSprite.color.alpha -= 6;
	}

	// ���Ń^�C�}�[�I�����ɃN���X�I�u�W�F�N�g���폜����
	if (m_FinishMessageTimer.Finished())
	{
		IGameObject::DeleteObject();
	}
}

void CShowMessage::Draw(void)
{
	// ���ɕ\������Ă��郁�b�Z�[�W�̏�ɏ㏑�����邽�߂ɒ����`�̍����㏑�������A���̏�ɐV�������b�Z�[�W��`�悷��
	DrawBox(0, aqua::GetWindowHeight() - m_UiSprite.GetTextureHeight(), aqua::GetWindowWidth(), aqua::GetWindowHeight(), 0x00000000, true);

	// ���b�Z�[�W�̕`��
	m_UiSprite.Draw();
}

void CShowMessage::Finalize(void)
{
	// ���b�Z�[�W�摜�̉��
	m_UiSprite.Delete();
}