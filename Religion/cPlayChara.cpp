/*ここでは、生物クラスのキャラ・敵の関数を定義するクラスコードファイルです。
//特にゲームを開始する時に必要な関数が多く書かれています。
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "clive.h"//敵やキャラの宣言ヘッダファイル

/* プレイヤーキャラクターのコンストラクタ */
PlayerChara::PlayerChara( int selchara, int Wpselect_equipment) : Soldier( selchara, Wpselect_equipment){

	StatusReset();

	return;
}

/*プレイヤーキャラクターのデストラクタ*/
PlayerChara::~PlayerChara(){

	int ech = 0;//エラー確認変数の初期化








}


/* ソルジャークラスの状態を初期に戻します(リスタート等で利用) */
int PlayerChara::StatusReset()
{

	Soldier::StatusReset();

	ChangePerspectiveMode = 0;

	return 0;
}