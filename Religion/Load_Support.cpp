/*ここでは、武器に関することを記述するクラスコードファイルです
//主に、サポート系をロードすることが書かれています
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "cWeapon_Support.h"//サポート武器関係のヘッダファイル



/* サポート系の情報をロードする関数 */
int Weapon_Support::WpLoad_Support( const int Wpno){

	/* 変数の初期化&宣言 */
	int ech = 0;
	char loadname[256] = "";

	//一時的な変数（モデル格納等など）
	int hsid = 0;//銃モデルのID
	int s_spid = 0;//銃スプライトのスプライトID
	int Garbage = 0;//いらない変数を格納します



	if(Wpno == 0){//M26

			//モデルデータのロード
			wsprintf( loadname, "%s\\data\\3d\\weapon\\support\\m26\\m26.sig", System::path);
			ech = E3DSigLoad( loadname, 0, 0.02f, &hsid);
			_ASSERT( ech != 1 );//エラーチェック

			//武器スプライトのロード
			wsprintf( loadname, "%s\\data\\3d\\weapon\\support\\m26\\pict.png", System::path);
			ech = E3DCreateSprite( loadname, 0, 0, &s_spid);
			_ASSERT( ech != 1 );//エラーチェック
	}
	if(Wpno == 1){//M67

			//モデルデータのロード
			wsprintf( loadname, "%s\\data\\3d\\weapon\\support\\m67\\m67.sig", System::path);
			ech = E3DSigLoad( loadname, 0, 0.01f, &hsid);
			_ASSERT( ech != 1 );//エラーチェック

			//武器スプライトのロード
			wsprintf( loadname, "%s\\data\\3d\\weapon\\support\\m67\\pict.png", System::path);
			ech = E3DCreateSprite( loadname, 0, 0, &s_spid);
			_ASSERT( ech != 1 );//エラーチェック
	}
	if(Wpno == 2){//M18 クレイモア

			//モデルデータのロード
			wsprintf( loadname, "%s\\data\\3d\\weapon\\support\\m18\\m18.sig", System::path);
			ech = E3DSigLoad( loadname, 0, 0.01f, &hsid);
			_ASSERT( ech != 1 );//エラーチェック

			//武器スプライトのロード
			wsprintf( loadname, "%s\\data\\3d\\weapon\\support\\m18\\pict.png", System::path);
			ech = E3DCreateSprite( loadname, 0, 0, &s_spid);
			_ASSERT( ech != 1 );//エラーチェック
	}
	if(Wpno == 3){//C4

			//モデルデータのロード
			wsprintf( loadname, "%s\\data\\3d\\weapon\\support\\c4\\c4.sig", System::path);
			ech = E3DSigLoad( loadname, 0, 0.01f, &hsid);
			_ASSERT( ech != 1 );//エラーチェック

			//武器スプライトのロード
			wsprintf( loadname, "%s\\data\\3d\\weapon\\support\\c4\\pict.png", System::path);
			ech = E3DCreateSprite( loadname, 0, 0, &s_spid);
			_ASSERT( ech != 1 );//エラーチェック
	}







	//変数をメンバー変数に格納します
	Set_Model( hsid);//武器のモデルを格納
	Set_Sprite( s_spid);//武器スプライトを格納
	Set_Sounds( -1, 0);
	Set_Sounds( -1, 1);

	return 1;
}