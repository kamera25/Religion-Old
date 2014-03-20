/*ここでは、武器に関することを記述するクラスコードファイルです
//主に、マシンガンをロードすることが書かれています
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "cWeapon_Gun.h"//武器に関することのクラスヘッダファイル

/* アサルトライフルの情報をロードする関数 */
int Weapon_Gun::GunLoad_Machine( const int Wpno){

	//変数の初期化
	int ech = 0;
	char loadname[256] = "";

	//一時的な変数（モデル格納等など）
	int hsid;//銃モデルのID
	int g_spid;//銃スプライトのスプライトID
	int bone[4];//銃のボーン
	int sound[6];//効果音データ
	int Garbage = 0;//いらない変数を格納します


	if( Wpno == 2){//M4マシンガン

			//モデルデータのロード
			wsprintf( loadname, "%s\\data\\3d\\weapon\\machinegun\\m4_machine\\M4MC.sig", System::path);
			ech = E3DSigLoad( loadname, 0, 0.042f, &hsid);
			_ASSERT( ech != 1 );//エラーチェック

			//武器スプライトのロード
			wsprintf( loadname, "%s\\data\\3d\\weapon\\machinegun\\m4_machine\\pict.png", System::path);
			ech = E3DCreateSprite( loadname, 1, 0, &g_spid);
			_ASSERT( ech != 1 );//エラーチェック

			//武器のモーションを読み込み
			wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\m1911\\wait.qua", System::path);
			//ech = E3DAddMotion( hsid, loadname, 1, &Garbage, &Garbage);
			_ASSERT( ech != 1 );//エラーチェック


			/* ////////////////////////////// */
			// ボーンデータのロードを行います
			/* ////////////////////////////// */

			// ボーンネームからボーンIDの取得「銃根」
			E3DGetBoneNoByName( hsid, "銃根", &bone[0]);
			_ASSERT( ech != 1 );//エラーチェック
			//ボーンネームからボーンIDの取得「銃先」
			E3DGetBoneNoByName( hsid, "銃先", &bone[1]);
			_ASSERT( ech != 1 );//エラーチェック

	}


	/*サウンドをロードします*/
	//発射音
	wsprintf( loadname, "%s\\data\\sound\\se\\shot\\rifle_fire.wav", System::path);
	ech = E3DLoadSound( loadname, 1, 1, 20, &sound[0]);
	_ASSERT( ech != 1 );//エラーチェック

	//空撃ち
	wsprintf( loadname, "%s\\data\\sound\\se\\shot\\sky_fire.wav", System::path);
	ech = E3DLoadSound( loadname, 1, 1, 20, &sound[1]);
	_ASSERT( ech != 1 );//エラーチェック

	/*音が届く範囲を指定*/
	ech = E3DSet3DSoundEmiDist( sound[0], 25000.0f);
	_ASSERT( ech != 1 );//エラーチェック

	ech = E3DSet3DSoundEmiDist( sound[1], 4000.0f);
	_ASSERT( ech != 1 );//エラーチェック



	//変数をメンバー変数に格納します
	Set_Model( hsid);//武器のモデルを格納
	Set_Sprite( g_spid);//武器スプライトを格納
	OtherModel = 0;//武器の使用済み弾薬モデルを格納
	Set_Bones( bone[0], 0);//銃口手前のボーンを格納
	Set_Bones( bone[1], 1);//銃口手先のボーンを格納
	Set_Sounds( sound[0], 0);
	Set_Sounds( sound[1], 0);



	return 0;
}