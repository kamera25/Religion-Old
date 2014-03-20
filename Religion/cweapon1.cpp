/*ここでは、武器に関することを記述するクラスコードファイルです
//
*/
#include "cweapon.h"//武器に関することのクラスヘッダファイル
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include "cstage.h"//ステージ関係のクラスヘッダファイル
#include "clive.h"//敵やキャラの宣言ヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

//ここにグローバル変数を宣言
extern System *sys;//システムクラスを指す、クラスのポインタ

/*武器をロードするための関数*/
int Weapon::GunLoad( int Selectkind, int Wpkind, int Wpno){

	//変数の初期化
	int ech = 0;

	/*すでに銃を取得しており、その銃データに上書きするなら*/
	if( WeaponModel[Selectkind] != 0){//選択中のカテゴリにデータがあるのなら
				ech = E3DDestroyHandlerSet( WeaponModel[Selectkind]);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};

				ech = E3DDestroySprite( WeaponSprite[Selectkind]);//スプライトを削除します
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};
	}


	/*銃のモデルのロード*/
	if(Wpkind == 1) GunLoad_Hand( Selectkind, Wpno);//ハンドガン系
	if(Wpkind == 4) GunLoad_Assault( Selectkind, Wpno);//アサルトライフル系


	/**/
	WeaponOtherModel[Selectkind][0] = WeaponData[Selectkind][2];//弾薬数をいっぱいにする
	WeaponOtherModel[Selectkind][1] = WeaponData[Selectkind][3];//マガジン数をいっぱいにする


	return 0;
}
/*アサルトライフルの情報をロードする関数*/
int Weapon::GunLoad_Assault( int Selectkind, int Wpno){

	//変数の初期化
	int ech = 0;
	char loadname[256] = "";

	//一時的な変数（モデル格納等など）
	int hsid;//銃モデルのID
	int hit_hsid;//銃の当たり判定モデルID
	int g_spid;//銃スプライトのスプライトID
	int bone[4];//銃のボーン
	int Garbage = 0;//いらない変数を格納します


	if(Wpno == 0){//M4

				//モデルデータのロード
				wsprintf( loadname, "%s\\data\\3d\\weapon\\assault\\m4\\m4a5.sig", sys->path);
				ech = E3DSigLoad( loadname, 0, 0.042f, &hsid);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};

				//当たり判定モデルのロード
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\hitchk\\hitber.sig", sys->path);
				ech = E3DSigLoad( loadname, 0, 5.0f, &hit_hsid);//モデルの読み込み
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};

				//武器スプライトのロード
				wsprintf( loadname, "%s\\data\\3d\\weapon\\assault\\m4\\pict.png", sys->path);
				ech = E3DCreateSprite( loadname, 1, 0, &g_spid);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};

				//武器のモーションを読み込み
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\m1911\\wait.qua", sys->path);
				ech = E3DAddMotion( hsid, loadname, 1, &Garbage, &Garbage);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};


				/**/
				//ボーンデータのロードを行います
				/**/

				/*//ボーンネームからボーンIDの取得「銃もち手_X+」
				E3DGetBoneNoByName( hsid, "銃根", &bone[0]);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};
				//ボーンネームからボーンIDの取得「銃もち手先_X+」
				E3DGetBoneNoByName( hsid, "銃先", &bone[1]);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};*/

				bone[0] = 0;//銃口手前のボーンを格納
				bone[1] = 0;//銃口手先のボーンを格納

				//ボーンネームから当たり判定ボーンIDの取得「当たり判定先」
				E3DGetBoneNoByName( hit_hsid, "当たり判定先", &bone[2]);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};
				//ボーンネームからボーンIDの取得「当たり判定根」
				E3DGetBoneNoByName( hit_hsid, "当たり判定根", &bone[3]);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};



		}

		//変数をメンバー変数に格納します
		WeaponModel[Selectkind] = hsid;//武器のモデルを格納
		WeaponSprite[Selectkind] = g_spid;//武器スプライトを格納
		WeaponOtherModel[Selectkind][0] = 0;//武器の使用済み弾薬モデルを格納
		WeaponBone[Selectkind][0] = bone[0];//銃口手前のボーンを格納
		WeaponBone[Selectkind][1] = bone[1];//銃口手先のボーンを格納
		WeaponBone[Selectkind][2] = bone[2];//銃口手先のボーンを格納
		WeaponBone[Selectkind][3] = bone[3];//銃口手先のボーンを格納




	return 0;
}
/*ハンドガンの情報をロードする関数*/
int Weapon::GunLoad_Hand( int Selectkind, int Wpno){

	//変数の初期化
	int ech = 0;
	char loadname[256] = "";

	//一時的な変数（モデル格納等など）
	int hsid;//銃モデルのID
	int hit_hsid;//銃の当たり判定モデルID
	int g_spid;//銃スプライトのスプライトID
	int bone[4];//銃のボーン
	int Garbage = 0;//いらない変数を格納します


	if(Wpno == 0){//M1911

				//モデルデータのロード
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\m1911\\m1911.sig", sys->path);
				ech = E3DSigLoad( loadname, 0, 0.055f, &hsid);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};

				//当たり判定モデルのロード
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\hitchk\\hitber.sig", sys->path);
				ech = E3DSigLoad( loadname, 0, 5.0f, &hit_hsid);//モデルの読み込み
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};

				//武器スプライトのロード
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\m1911\\pict.png", sys->path);
				ech = E3DCreateSprite( loadname, 1, 0, &g_spid);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};

				//武器のモーションを読み込み
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\m1911\\wait.qua", sys->path);
				ech = E3DAddMotion( hsid, loadname, 1, &Garbage, &Garbage);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};


				/**/
				//ボーンデータのロードを行います
				/**/

				//ボーンネームからボーンIDの取得「銃もち手_X+」
				E3DGetBoneNoByName( hsid, "銃根", &bone[0]);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};
				//ボーンネームからボーンIDの取得「銃もち手先_X+」
				E3DGetBoneNoByName( hsid, "銃先", &bone[1]);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};
				//ボーンネームから当たり判定ボーンIDの取得「当たり判定先」
				E3DGetBoneNoByName( hit_hsid, "当たり判定先", &bone[2]);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};
				//ボーンネームからボーンIDの取得「当たり判定根」
				E3DGetBoneNoByName( hit_hsid, "当たり判定根", &bone[3]);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};


		}
		if(Wpno == 2){//Glock95

				//モデルデータのロード
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\glock95\\glock.sig", sys->path);
				ech = E3DSigLoad( loadname, 0, 0.037f, &hsid);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};

				//当たり判定モデルのロード
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\hitchk\\hitber.sig", sys->path);
				ech = E3DSigLoad( loadname, 0, 5.0f, &hit_hsid);//モデルの読み込み
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};

				//武器スプライトのロード
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\glock95\\pict.png", sys->path);
				ech = E3DCreateSprite( loadname, 1, 0, &g_spid);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};

				//武器のモーションを読み込み
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\m1911\\wait.qua", sys->path);
				ech = E3DAddMotion( hsid, loadname, 1, &Garbage, &Garbage);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};


				/**/
				//ボーンデータのロードを行います
				/**/

				/*//ボーンネームからボーンIDの取得「銃もち手_X+」
				E3DGetBoneNoByName( hsid, "銃根", &bone[0]);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};
				//ボーンネームからボーンIDの取得「銃もち手先_X+」
				E3DGetBoneNoByName( hsid, "銃先", &bone[1]);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};*/

				bone[0] = 0;//銃口手前のボーンを格納
				bone[1] = 0;//銃口手先のボーンを格納
				//ボーンネームから当たり判定ボーンIDの取得「当たり判定先」
				E3DGetBoneNoByName( hit_hsid, "当たり判定先", &bone[2]);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};
				//ボーンネームからボーンIDの取得「当たり判定根」
				E3DGetBoneNoByName( hit_hsid, "当たり判定根", &bone[3]);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};



		}

		if(Wpno == 3){//M92F

				//モデルデータのロード
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\m92f\\m92f.sig", sys->path);
				ech = E3DSigLoad( loadname, 0, 0.039f, &hsid);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};

				//当たり判定モデルのロード
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\hitchk\\hitber.sig", sys->path);
				ech = E3DSigLoad( loadname, 0, 5.0f, &hit_hsid);//モデルの読み込み
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};

				//武器スプライトのロード
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\m92f\\pict.png", sys->path);
				ech = E3DCreateSprite( loadname, 1, 0, &g_spid);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};

				//武器のモーションを読み込み
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\m92f\\wait.qua", sys->path);
				ech = E3DAddMotion( hsid, loadname, 1, &Garbage, &Garbage);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};


				/**/
				//ボーンデータのロードを行います
				/**/

				//ボーンネームからボーンIDの取得「銃もち手_X+」
				E3DGetBoneNoByName( hsid, "銃根", &bone[0]);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};
				//ボーンネームからボーンIDの取得「銃もち手先_X+」
				E3DGetBoneNoByName( hsid, "銃先", &bone[1]);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};
				//ボーンネームからボーンIDの取得「当たり判定先」
				E3DGetBoneNoByName( hit_hsid, "当たり判定先", &bone[2]);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};
				//ボーンネームからボーンIDの取得「当たり判定根」
				E3DGetBoneNoByName( hit_hsid, "当たり判定根", &bone[3]);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};


		}

		//変数をメンバー変数に格納します
		WeaponModel[Selectkind] = hsid;//武器のモデルを格納
		WeaponSprite[Selectkind] = g_spid;//武器スプライトを格納
		WeaponOtherModel[Selectkind][0] = 0;//武器の使用済み弾薬モデルを格納
		WeaponBone[Selectkind][0] = bone[0];//銃口手前のボーンを格納
		WeaponBone[Selectkind][1] = bone[1];//銃口手先のボーンを格納
		WeaponBone[Selectkind][2] = bone[2];//銃口手先のボーンを格納
		WeaponBone[Selectkind][3] = bone[3];//銃口手先のボーンを格納


	return 0;
}
/*武器に関するデータを格納する関数*/
int Weapon::GunLoad_Data( int Selectkind, int Wpkind, int Wpno){

	//一時的な変数（モデル格納等など）
	int ammo;//弾薬の最大値
	int mag;//マガジンの最大値
	int distance;//射程距離の最大値
	int attack;//武器の攻撃値


	/*ハンドガン関係*/
	if( Wpkind == 1){
			if(Wpno == 0){//M1911

						//M1911のデータを格納します。
						ammo = 7;
						mag = 7;
						distance = 100;
						attack = 100;
			}
			if(Wpno == 2){//Glock95
						
						//Glockのデータを格納します。
						ammo = 50;
						mag = 3;
						distance = 60;
						attack = 30;
			}
			if(Wpno == 3){//M92FS
								
						//M92Fのデータを格納します。
						ammo = 15;
						mag = 2;
						distance = 120;
						attack = 80;
			}
	}
	/*アサルトライフル関係*/
	if( Wpkind == 4){

			if( Wpno == 3){
						//M4のデータを格納します。
						ammo = 30;
						mag = 5;
						distance = 160;
						attack = 140;
			}
	}


	WeaponData[Selectkind][0] = Wpkind;
	WeaponData[Selectkind][1] = Wpno;
	WeaponData[Selectkind][2] = ammo;
	WeaponData[Selectkind][3] = mag;
	WeaponData[Selectkind][4] = distance;
	WeaponData[Selectkind][5] = attack;


	return 0;
}

/*コンストラクタ、変数の初期化を行います*/
Weapon::Weapon(){





	return;
}
/*デストラクタ、モデルの破棄等を行います*/
Weapon::~Weapon(){

	//変数の初期化
	int ech = 0;

	//銃のデータの削除します（最初から順番にメイン・サブ・グレネードの順番です）
	for(int i = 0;i < 3; i++){
		if( WeaponModel[i] != 0){//選択中のカテゴリにデータがあるのなら
					ech = E3DDestroyHandlerSet( WeaponModel[i]);//モデルを削除します
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
					};

					ech = E3DDestroySprite( WeaponSprite[i]);//スプライトを削除します
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
					};
		}
	}

	return;
}