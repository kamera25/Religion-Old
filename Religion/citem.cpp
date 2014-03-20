/*ここは、アイテムに関することのクラスのヘッダです。
//ゲーム中でのアイテム全般について書かれています。
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "citem.h"//アイテムの宣言ヘッダファイル


/* コンストラクタ、初期動作を行ないます */
Item::Item(){

	/* ********
	// 初期化
	// ********
	*/

	BringWp = 0;//拾った武器を初期化します

	// Ammo内のデータを初期化します
	for( int i=0; i<4; i++){
			Ammo[i] = -1;		
	}

	/* !!以下、テスト動作!! */
	Ammo[0] = 0;


	return;
}
/* 格納されているアイテムナンバーを取得します */
int Item::GetItemNumber( const int ItemKind, const int ItemEle1, const int ItemEle2){

	/* 変数の初期化 */
	int Value = 0;// 返り値、

	switch( ItemKind ){
		case 0:{
			Value = BringWp;
			break;
		}
		case 1:{
			Value = Ammo[ItemEle1];
			break;
		}
		case 2:{
			Value = Recovery[ItemEle1][ItemEle2];
			break;
		}
		case 3:{
			Value = Key[ItemEle1];
			break;
	    }
		case 4:{
			Value = Equipment[ItemEle1];
			break;
		}
		default:{
			Value = 0;
			_ASSERT(0);//エラーダイアログを表示
		}
	}


	return Value;
}

