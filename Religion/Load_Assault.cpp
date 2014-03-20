/*ここでは、武器に関することを記述するクラスコードファイルです
//主に、アサルトライフルをロードすることが書かれています
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "cweapon.h"//武器に関することのクラスヘッダファイル


/* アサルトライフルの情報をロードする関数 */
int Weapon::GunLoad_Assault( const int Selectkind, const int Wpno){

	//変数の初期化
	int ech = 0;
	char loadname[256] = "";

	//一時的な変数（モデル格納等など）
	int hsid;//銃モデルのID
	int g_spid;//銃スプライトのスプライトID
	int bone[4];//銃のボーン
	int sound[6];//効果音データ
	int Garbage = 0;//いらない変数を格納します


	if( Wpno == 0){//M4

			//モデルデータのロード
			wsprintf( loadname, "%s\\data\\3d\\weapon\\assault\\m4\\m4a5.sig", System::path);
			ech = E3DSigLoad( loadname, 0, 0.042f, &hsid);
			if(ech != 0 ){//エラーチェック
						_ASSERT( 0 );//エラーダイアログ
			};

			//武器スプライトのロード
			wsprintf( loadname, "%s\\data\\3d\\weapon\\assault\\m4\\pict.png", System::path);
			ech = E3DCreateSprite( loadname, 1, 0, &g_spid);
			if(ech != 0 ){//エラーチェック
						_ASSERT( 0 );//エラーダイアログ
			};

			//武器のモーションを読み込み
			wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\m1911\\wait.qua", System::path);
			ech = E3DAddMotion( hsid, loadname, 1, &Garbage, &Garbage);
			if(ech != 0 ){//エラーチェック
						_ASSERT( 0 );//エラーダイアログ
			};


			/* ////////////////////////////// */
			// ボーンデータのロードを行います
			/* ////////////////////////////// */

			// ボーンネームからボーンIDの取得「銃根」
			E3DGetBoneNoByName( hsid, "銃根", &bone[0]);
			if(ech != 0 ){//エラーチェック
						_ASSERT( 0 );//エラーダイアログ
			};
			//ボーンネームからボーンIDの取得「銃先」
			E3DGetBoneNoByName( hsid, "銃先", &bone[1]);
			if(ech != 0 ){//エラーチェック
						_ASSERT( 0 );//エラーダイアログ
			};

	}
	if( Wpno == 1){//AK-74u

			//モデルデータのロード
			wsprintf( loadname, "%s\\data\\3d\\weapon\\assault\\ak-74u\\ak-74u.sig", System::path);
			ech = E3DSigLoad( loadname, 0, 0.096f, &hsid);
			if(ech != 0 ){//エラーチェック
						_ASSERT( 0 );//エラーダイアログ
			};

			//武器スプライトのロード
			wsprintf( loadname, "%s\\data\\3d\\weapon\\assault\\ak-74u\\pict.png", System::path);
			ech = E3DCreateSprite( loadname, 1, 0, &g_spid);
			if(ech != 0 ){//エラーチェック
						_ASSERT( 0 );//エラーダイアログ
			};

			//武器のモーションを読み込み
			wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\m1911\\wait.qua", System::path);
			ech = E3DAddMotion( hsid, loadname, 1, &Garbage, &Garbage);
			if(ech != 0 ){//エラーチェック
						_ASSERT( 0 );//エラーダイアログ
			};


			/* ////////////////////////////// */
			// ボーンデータのロードを行います
			/* ////////////////////////////// */

			// ボーンネームからボーンIDの取得「銃根」
			E3DGetBoneNoByName( hsid, "銃根", &bone[0]);
			if(ech != 0 ){//エラーチェック
						_ASSERT( 0 );//エラーダイアログ
			};
			//ボーンネームからボーンIDの取得「銃先」
			E3DGetBoneNoByName( hsid, "銃先", &bone[1]);
			if(ech != 0 ){//エラーチェック
						_ASSERT( 0 );//エラーダイアログ
			};

	}
	if( Wpno == 6){//HK 416

			//モデルデータのロード
			wsprintf( loadname, "%s\\data\\3d\\weapon\\assault\\hk_416\\hk_416.sig", System::path);
			ech = E3DSigLoad( loadname, 0, 0.042f, &hsid);
			if(ech != 0 ){//エラーチェック
						_ASSERT( 0 );//エラーダイアログ
			};

			//武器スプライトのロード
			wsprintf( loadname, "%s\\data\\3d\\weapon\\assault\\hk_416\\pict.png", System::path);
			ech = E3DCreateSprite( loadname, 1, 0, &g_spid);
			if(ech != 0 ){//エラーチェック
						_ASSERT( 0 );//エラーダイアログ
			};

			//武器のモーションを読み込み
			wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\m1911\\wait.qua", System::path);
			ech = E3DAddMotion( hsid, loadname, 1, &Garbage, &Garbage);
			if(ech != 0 ){//エラーチェック
						_ASSERT( 0 );//エラーダイアログ
			};


			/* ////////////////////////////// */
			// ボーンデータのロードを行います
			/* ////////////////////////////// */

			// ボーンネームからボーンIDの取得「銃根」
			E3DGetBoneNoByName( hsid, "銃根", &bone[0]);
			if(ech != 0 ){//エラーチェック
						_ASSERT( 0 );//エラーダイアログ
			};
			//ボーンネームからボーンIDの取得「銃先」
			E3DGetBoneNoByName( hsid, "銃先", &bone[1]);
			if(ech != 0 ){//エラーチェック
						_ASSERT( 0 );//エラーダイアログ
			};


	}


	/*サウンドをロードします*/
	//発射音
	wsprintf( loadname, "%s\\data\\sound\\se\\shot\\rifle_fire.wav", System::path);
	ech = E3DLoadSound( loadname, 1, 1, 20, &sound[0]);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	//空撃ち
	wsprintf( loadname, "%s\\data\\sound\\se\\shot\\sky_fire.wav", System::path);
	ech = E3DLoadSound( loadname, 1, 1, 20, &sound[1]);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/*音が届く範囲を指定*/
	ech = E3DSet3DSoundEmiDist( sound[0], 25000.0f);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	ech = E3DSet3DSoundEmiDist( sound[1], 4000.0f);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};



	//変数をメンバー変数に格納します
	WeaponModel[Selectkind] = hsid;//武器のモデルを格納
	WeaponSprite[Selectkind] = g_spid;//武器スプライトを格納
	WeaponOtherModel[Selectkind][0] = 0;//武器の使用済み弾薬モデルを格納
	WeaponBone[Selectkind][0] = bone[0];//銃口手前のボーンを格納
	WeaponBone[Selectkind][1] = bone[1];//銃口手先のボーンを格納
	WeaponSoundEfeect[Selectkind][0] = sound[0];
	WeaponSoundEfeect[Selectkind][1] = sound[1];



	return 0;
}