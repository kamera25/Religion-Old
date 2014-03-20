/* このソースはオペレーションの仕訳処理をする、OpsMissionBranchStart関数など
// オペレーション関係について記述されている"cOperation.cpp"ソースです
/* ////////////////////////////////////////////////////////////////////// */

#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ
#include "coperation.h"//オペレーション開始関係のクラスヘッダファイル




int Operation::OpsMissionBranchStart( const int MissionNumber){

	/* 変数の初期化 & 宣言 */
	/* N/a */

	/* ロード画面を表示します */
	System::WaitRender();//読み込み画面を表示させます


	/* ///////////////////////////////////////////////////////////// */
	// !! 任務分岐 !! 
	// 
	//  これから下はそれぞれのミッションを開始するための分岐です。
	// 変数:MissionNumberでそれぞれ分岐、関数は基本的にOperationクラス
	// 内に記述されます。例:OpsMission1_Shinryoku();...
	// あとのシステムはすべてそれぞれの関数に丸投げします。
	/* //////////////////////////////////////////////////////////// */
	switch( MissionNumber){
			
		case(0):{ // 新緑のブレスレッド
				OpsMission1_Shinryoku();
				break;
		}
	}









	return 0;
}