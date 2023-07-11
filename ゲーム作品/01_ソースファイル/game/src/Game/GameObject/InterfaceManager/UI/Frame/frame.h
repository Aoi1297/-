#pragma once

#include "../ui.h"

// 前方宣言
class CPlayer;
class CCameraManager;

class CUIFrame : public IUserInterface
{
public: // 公開メンバ関数

	// コンストラクタ
	CUIFrame		(IGameObject* parent);

	// デストラクタ
	~CUIFrame		(void)	override = default;

	// 初期化関数
	void Initialize	(void)	override;

	// 更新関数
	void Update		(void)	override;

	// 描画関数
	void Draw		(void)	override;

private: // 非公開メンバ変数


	float m_LineLength;

	// 現在のレーザーポイント
	float m_LaserPoint;

	// レーザーポイントの割合
	float m_LaserPointRatio;

	// 現在の体力
	float m_HitPoint;

	// 体力の割合
	float m_HitPointRatio;

	// プレイヤークラスオブジェクトのポインタ変数
	CPlayer* m_Player_P;

	// カメラマネージャークラスオブジェクトのポインタ変数
	CCameraManager* m_CameraManager_P;

private: // 非公開メンバ定数

	static const float m_max_laser_point;			// !< レーザー発射までに必要なポイント
	static const unsigned int m_up_frame_color;	// !< 上のフレーム（長方形）の色
	static const unsigned int m_down_frame_color;	// !< 下のフレーム（長方形）の色
	static const unsigned int m_laser_line_color;	// !< レーザーメーターの色
	static const unsigned int m_hp_line_color;		// !< ＨＰメーターの色
	static const unsigned int m_line_color;		// !< メーターの色（灰色）
	static const int m_line_thickness;				// !< メーターの太さ
	static const float m_frame_height;				// !< フレームの縦幅
	static const float m_line_height;				// !< メーターの縦幅
};