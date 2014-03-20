/*ここでは、ゲームメインループを作り、および各システムを呼び出します。
//
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "cfirstmenu.h"//メインメニューに関するメニュクラスヘッダファイル
#include "copsmenu.h"//オペレーションモードに関するクラスヘッダ
#include "coperation.h"//オペレーション開始関係のクラスヘッダファイル


//ゲームをスタートします。
int GMStart(){

	/*変数の初期化&宣言*/
	int MenuSelectNo = 0;//どのメニューが選択されたか格納します

	while( WM_QUIT != System::msg.message){

			/*メインメニューをに入ります*/
			{
				MainMenu MainMenu;
				MenuSelectNo = MainMenu.InMainMenu();
			}

			/*セレクト変数によって分岐します*/
			switch( MenuSelectNo){
				case 1:{//オペレーションモードが選択されたら
					OperationMenu OpsMenu;//オプスメニュークラスを作成
					OpsMenu.InOpsMenu();
					break;
				}
				case 0:{
						Operation OPS;//オペレーションを作る
						OPS.OpsMissionBranchStart( 0);// 新緑の少女を呼ぶ
						break;
				}
			}
	}


	return 0;
}