/*ここでは、武器に関することを記述するクラスコードファイルです
//主に、グレネードをロードすることが書かれています
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "cweapon.h"//武器に関することのクラスヘッダファイル


/* ライフルの情報をロードする関数 */
int Weapon::GunLoad_Grenade( const int Selectkind, const int Wpno){



	//変数の初期化
	int ech = 0;
	char loadname[256] = "";

	//一時的な変数（モデル格納等など）
	int hsid;//銃モデルのID
	int g_spid;//銃スプライトのスプライトID
	int Garbage = 0;//いらない変数を格納します



	if(Wpno == 0){//グレネード

			//モデルデータのロード
			wsprintf( loadname, "%s\\data\\3d\\weapon\\grenade\\grenade\\grenade.sig", System::path);
			ech = E3DSigLoad( loadname, 0, 0.01f, &hsid);
			if(ech != 0 ){//エラーチェック
						_ASSERT( 0 );//エラーダイアログ
			};

			//武器スプライトのロード
			wsprintf( loadname, "%s\\data\\3d\\weapon\\rifle\\sr-25\\pict.png", System::path);
			ech = E3DCreateSprite( loadname, 1, 0, &g_spid);
			if(ech != 0 ){//エラーチェック
						_ASSERT( 0 );//エラーダイアログ
			};


	}









	//変数をメンバー変数に格納します
	WeaponModel[Selectkind] = hsid;//武器のモデルを格納
	WeaponSprite[Selectkind] = g_spid;//武器スプライトを格納
	WeaponOtherModel[Selectkind][0] = 0;//武器の使用済み弾薬モデルを格納



	return 0;
}