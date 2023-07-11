
/*!
 *  @file       game.h
 *  @brief      �Q�[���Ǘ�
 *  @author     Kazuya Maruyama
 *  @date       2021/02/06
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "aqua.h"

/*!
 *  @class      CGame
 *
 *  @brief      �Q�[���N���X
 *
 *  @author     Kazuya Maruyama
 *
 *  @date       2021/02/06
 *
 *  @version    1.0
 */
class CGame
    : public aqua::IGameObject
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  parent  �e�I�u�W�F�N�g
     */
    CGame( IGameObject* parent );

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CGame( void ) = default;

    /*!
     *  @brief      ������
     */
    void        Initialize( void ) override;

    /*!
     *  @brief      �`��
     */
    void        Draw( void ) override;

private:
    //! ��ʃN���A�J���[
    aqua::CColor m_ClearColor;

private:
    static const unsigned char m_max_random_color;
};
