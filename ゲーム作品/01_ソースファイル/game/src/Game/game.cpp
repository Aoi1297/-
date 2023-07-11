
/*!
 *  @file       game.cpp
 *  @brief      ゲーム管理
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
 *  コンストラクタ
 */
CGame::
CGame( aqua::IGameObject* parent )
    // parent(nullptr)
    : IGameObject( parent, "Game" )
{
}

/*
 *  初期化
 */
void
CGame::
Initialize(void)
{
    // ゲーム起動時、背景の色をランダムで設定する（RGB単位）
    {
        // R（赤）の値を設定（0~200)
        m_ClearColor.red   = aqua::Rand(m_max_random_color);

        // G（緑）の値を設定（0~200)
        m_ClearColor.green = aqua::Rand(m_max_random_color);

        // B（青）の値を設定（0~200)
        m_ClearColor.blue  = aqua::Rand(m_max_random_color);
    }

    // シーンマネージャークラスオブジェクトを生成
    aqua::CreateGameObject<CSceneManager>(this);

    // サウンドプレイヤークラスオブジェクトを生成
    aqua::CreateGameObject<CSoundCreater>(this);

    // 生成したクラスオブジェクトの初期化を行う
    IGameObject::Initialize();
}

/*
 *  描画
 */
void
CGame::
Draw(void)
{
    // 画面のクリア
    aqua::Clear(m_ClearColor.GetColor());

    // 描画したいオブジェクト群
    IGameObject::Draw();
}