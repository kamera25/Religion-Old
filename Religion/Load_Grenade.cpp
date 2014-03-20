/*ここでは、武器に関することを記述するクラスコードファイルです
//主に、グレネードをロードすることが書かれています
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "cWeapon_Gun.h"//武器に関することのクラスヘッダファイル


/* グレネードの情報をロードする関数 */
int Weapon_Gun::GunLoad_Grenade( const int Wpno){

	/* 変数の初期化 */
	int ech = 0;
	char loadname[256] = "";

	// 存在がエラーなので強制終了
	return -1;

	//一時的な変数（モデル格納等など）
	int hsid = 0;//銃モデルのID
	int g_spid = 0;//銃スプライトのスプライトID
	int Garbage = 0;//いらない変数を格納します






	//変数をメンバー変数に格納します
	Set_Model( hsid);//武器のモデルを格納
	Set_Sprite( g_spid);//武器スプライトを格納
	OtherModel = 0;//武器の使用済み弾薬モデルを格納



	return 0;
}