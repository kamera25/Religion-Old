/*ここでは、生物クラスのキャラの関数を定義するクラスコードファイルです。
//銃に関係する時に必要な関数が多く書かれています。
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ
#include "cstage.h"//ステージ関係のクラスヘッダファイル
#include "clive.h"//敵やキャラのクラスヘッダファイル
#include "c_batch_preparat.h"//描画に必要なクラスの宣言ヘッダファイル
#include <math.h>//数学計算を使うためのヘッダファイル
#include "ccamera.h"//カメラに関することのクラスヘッダファイル

//ここにグローバル変数を宣言
extern System *sys;//システムクラスを指す、クラスのポインタ

/*銃について作動させる関数、リロード、次打てるまでの時間計算、敵へのあたり判定、ダメージ計算など*/
int PlayerChara::GunSystem( Enemy *Ene){

	/*全体で使う変数の初期化*/
	int ech = 0;//エラー確認変数

	











	return 0;
}