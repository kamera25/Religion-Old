/* このソースはオペレーションの仕訳処理をする、OpsMissionBranchStart関数など
// オペレーション関係について記述されている"cOperation.cpp"ソースです
/* ////////////////////////////////////////////////////////////////////// */

#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ
#include "coperation.h"//オペレーション開始関係のクラスヘッダファイル
#include "cMission.h"

#include "clive.h"//敵やキャラの宣言ヘッダファイル


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
				OpsMissionFromFile( "shinryoku.mis");
				//OpsMission1_Shinryoku();
				break;
		}
	}









	return 0;
}

/* ファイルからミッション情報を読み取り、ミッションを開始します。 */
int Operation::OpsMissionFromFile( char *File)
{


	/* 以下、ファイルを読み込んだ後の処理 */

	
	Mission Mis;
	Mis.Intialize();
	Mis.Loading( File);

	// ゲーム開始
	Mis.MainProc();



	return 0;
}










// 基本的な BatchPreprate の処理を全て行います
int Operation::NormalBatchProces(){

	pBatP->BatchSpriteSet( pPly);
	pBatP->BatchRender( 0);
	pBatP->Batch_BillBoard( 0);
	pBatP->BatchSpriteRender( 0);
	pBatP->BatchFont( 1, pPly);
	pBatP->Batch_Present();

	return 0;
}