/*ここでは、生物クラスのキャラ・敵の関数を定義するクラスコードファイルです。
//特にゲームを開始する時に必要な関数が多く書かれています。
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "clive.h"//敵やキャラの宣言ヘッダファイル

/* プレイヤーキャラクターのコンストラクタ */
PlayerChara::PlayerChara( int selchara, int Wpselect_equipment) : Soldier( selchara, Wpselect_equipment){


	ChangePerspectiveMode = 0;

	return;
}

/*プレイヤーキャラクターのデストラクタ*/
PlayerChara::~PlayerChara(){

	int ech = 0;//エラー確認変数の初期化

	//キャラクターモデルを削除します
	E3DDestroyHandlerSet( Get_BodyModel());
	_ASSERT( ech != 1 );//エラーチェック

	//1つ目のキャラクターダミーモデルを削除します
	E3DDestroyHandlerSet( Get_DummyModel());
	_ASSERT( ech != 1 );//エラーチェック

	//スキル格納変数の削除
	Delete_Skill();


	/**/
	//クォータニオンを削除します
	/**/	
	for(int i = 0; i<4; i++){
				ech = E3DDestroyQ( Get_Quaternion(i));
				_ASSERT( ech != 1 );//エラーチェック
	}


}