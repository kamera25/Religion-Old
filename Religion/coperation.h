#pragma once
/* この"coperation.h"ヘッダはオペレーションクラスについて書かれています。
// オペレーションクラスは主にゲーム本編のシステムの統括、任務分岐を行ないます
/* /////////////////////////////////////////////////////////////////// */

class Operation{

private:

	/* ミッション関数宣言 */
	int OpsMission1_Shinryoku();// ミッション1 新緑の少女



public:

	/* 関数の宣言 */
	int OpsMissionBranchStart( int MissionNumber);


};