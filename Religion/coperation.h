#pragma once
/* この"coperation.h"ヘッダはオペレーションクラスについて書かれています。
// オペレーションクラスは主にゲーム本編のシステムの統括、任務分岐を行ないます
/* /////////////////////////////////////////////////////////////////// */

#include "cPoseMenu.h"//メニュークラスに関するヘッダファイル
#include "ccamera.h"//カメラ関係のクラスヘッダファイル

class Operation{

private:

	/* ゲーム本編で使うクラス */
	Camera Cam; //カメラクラスの実体
	PoseMenu Menu; // メニュークラスの実体

	/* ミッション関数宣言 */
	int OpsMission1_Shinryoku();// ミッション1 新緑の少女



public:

	/* 関数の宣言 */
	int OpsMissionBranchStart( const int MissionNumber);


};