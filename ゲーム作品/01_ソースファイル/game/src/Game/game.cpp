
/*!
 *  @file       game.cpp
 *  @brief      �Q�[���Ǘ�
 *  @author     Kazuya Maruyama
 *  @date       2021/02/06
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "game.h"

#include "GameObject/SceneManager/scene_manager.h"
#include "GameObject/CameraManager/camera_manager.h"
#include "GameObject/SoundManager/sound_creater.h"

const unsigned char CGame::m_max_random_color = 200;

/*
 *  �R���X�g���N�^
 */
CGame::
CGame( aqua::IGameObject* parent )
    // parent(nullptr)
    : IGameObject( parent, "Game" )
{
}

/*
 *  ������
 */
void
CGame::
Initialize(void)
{
    // �Q�[���N�����A�w�i�̐F�������_���Őݒ肷��iRGB�P�ʁj
    {
        // R�i�ԁj�̒l��ݒ�i0~200)
        m_ClearColor.red   = aqua::Rand(m_max_random_color);

        // G�i�΁j�̒l��ݒ�i0~200)
        m_ClearColor.green = aqua::Rand(m_max_random_color);

        // B�i�j�̒l��ݒ�i0~200)
        m_ClearColor.blue  = aqua::Rand(m_max_random_color);
    }

    // �V�[���}�l�[�W���[�N���X�I�u�W�F�N�g�𐶐�
    aqua::CreateGameObject<CSceneManager>(this);

    // �T�E���h�v���C���[�N���X�I�u�W�F�N�g�𐶐�
    aqua::CreateGameObject<CSoundCreater>(this);

    // ���������N���X�I�u�W�F�N�g�̏��������s��
    IGameObject::Initialize();
}

/*
 *  �`��
 */
void
CGame::
Draw(void)
{
    // ��ʂ̃N���A
    aqua::Clear(m_ClearColor.GetColor());

    // �`�悵�����I�u�W�F�N�g�Q
    IGameObject::Draw();
}