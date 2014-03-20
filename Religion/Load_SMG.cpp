/*ここでは、武器に関することを記述するクラスコードファイルです
//主に、をロードすることが書かれています
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "cWeapon_Gun.h"//武器に関することのクラスヘッダファイル


/* ショットガンの情報をロードする関数 */
int Weapon_Gun::GunLoad_SMG( const int Wpno){

	//変数の初期化
	int ech = 0;
	char loadname[256] = "";

	//一時的な変数（モデル格納等など）
/*	int hsid;//銃モデルのID
	int g_spid;//銃スプライトのスプライトID
	int bone[4];//銃のボーン
	int Garbage = 0;//いらない変数を格納します
	int sound[5];//効果音のID
*/

	if(Wpno == 0){//  TMP


	}




	//変数をメンバー変数に格納します
/*	Set_Model( hsid);//武器のモデルを格納
	Set_Sprite( g_spid);//武器スプライトを格納
	OtherModel =  0;//武器の使用済み弾薬モデルを格納
	Set_Bones( bone[0], 0);//銃口手前のボーンを格納
	Set_Bones( bone[1], 1);//銃口手先のボーンを格納
	Set_Sounds( sound[0], 0);
	Set_Sounds( sound[1], 1);
	*/





	return 0;
}