/*ここでは、生物クラスのキャラ・敵の関数を定義するクラスコードファイルです。
//特にゲームを開始する時に必要な関数が多く書かれています。
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include "cstage.h"//ステージ関係のクラスヘッダファイル
#include "clive.h"//敵やキャラの宣言ヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ


//ここにグローバル変数を宣言
extern System *sys;//システムクラスを指す、クラスのポインタ


/*プレイヤーキャラクターのコンストラクタ*/
PlayerChara::PlayerChara( int selchara, int Wpselect_equipment){

	//変数の初期化
	int ech = 0;
	char loadname[256] = "";


	//クラス内変数の初期化
	/*ウェポン変数の初期化*/
	for(int i = 0; i<3; i++){
		for(int j = 0; j<4; j++){
			for(int k = 0; k<6;k++){
					wp_data[i][j][k] = 0;//すべてのウェポン変数を空にする
			}
		}
	}

	/*その他変数の初期化*/

	BringWp = 0;//拾った武器を初期化します
	PC_Deg_XZ = 0.0f;//自分の向き（XZ座標初期化）
	PC_Deg_Y = 0.0f;//自分の向き（Y座標初期化）
	UpMotion = 0;//上半身のモーションの初期化
	UnderMotion = 0;//下半身のモーションの初期化
	Attitude = 0;//自分の姿勢を「立ち」に指定
	MyState = 0;//自分の動作状態を初期化
	AirOnPC = 0;//自分の空中状態を通常にする
	Acceleration = 0.0;//重力加速度を0にする
	MoveSpeed = 0.0;//平面加速度を0にする


	//キャラクターモデルのロード

	if(selchara == 0){//アーティーモデル

				//アーティーモデルの取得
				wsprintf( loadname, "%s\\data\\3d\\model\\demo\\hito.sig", sys->path);//アーティーモデルのsig名登録
				ech = E3DSigLoad( loadname, 0, 0, &cha_hsid[0]);//モデルの読み込み、cha_hsidへモデルを入れる。
				if(ech != 0 ){//エラーチェック
							_ASSERT(0);//エラーダイアログ
				};

				//ハンドモデルの取得
				wsprintf( loadname, "%s\\data\\3d\\model\\hand\\hand.sig", sys->path);//ハンドモデルのsig名登録
				ech = E3DSigLoad( loadname, 0, 1, &cha_hsid[1]);//モデルの読み込み、cha_hsidへモデルを入れる。
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};

				//ダミーモデルの取得
				wsprintf( loadname, "%s\\data\\3d\\model\\other\\demo.sig", sys->path);//仮モデルのsig名登録
				ech = E3DSigLoad( loadname, 0, 1, &DummyModel);//モデルの読み込み、submodidへモデルを入れる。
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};

	}

		if(selchara == 1){//WF兵1モデル

				//WF兵1モデルの取得
				wsprintf( loadname, "%s\\data\\3d\\chara\\wf1\\model.sig", sys->path);//アーティーモデルのsig名登録
				ech = E3DSigLoad( loadname, 0, 0.15f, &cha_hsid[0]);//モデルの読み込み、cha_hsidへモデルを入れる。
				if(ech != 0 ){//エラーチェック
							_ASSERT(0);//エラーダイアログ
				};

				//ダミーモデルの取得
				wsprintf( loadname, "%s\\data\\3d\\model\\other\\demo.sig", sys->path);//仮モデルのsig名登録
				ech = E3DSigLoad( loadname, 0, 0.01f, &DummyModel);//モデルの読み込み、submodidへモデルを入れる。
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};

				//モーションデータ構え
				wsprintf( loadname, "%s\\data\\3d\\chara\\motion\\pc_motion.moa", sys->path);//仮モデルのsig名登録
				ech = E3DLoadMOAFile( cha_hsid[0], loadname, 3, 1.0f); 
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};

				//ボーンネームからボーンIDの取得「銃もち手_X+」
				ech = E3DGetBoneNoByName( cha_hsid[0], "銃もち手_X+", &bone[0]);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};
				//ボーンネームからボーンIDの取得「銃もち手先_X+」
				ech = E3DGetBoneNoByName( cha_hsid[0], "銃もち手先_X+", &bone[1]);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};
				//ボーンネームからボーンIDの取得「首付け根」
				ech = E3DGetBoneNoByName( cha_hsid[0], "首付け根", &bone[2]);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};
				//ボーンネームからボーンIDの取得「足付け根_X+」
				ech = E3DGetBoneNoByName( cha_hsid[0], "足付け根_X+", &bone[3]);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};
				//ボーンネームからボーンIDの取得「足付け根_X-」
				ech = E3DGetBoneNoByName( cha_hsid[0], "足付け根_X-", &bone[4]);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};
				//ボーンネームからボーンIDの取得「おなか」
				ech = E3DGetBoneNoByName( cha_hsid[0], "おなか", &bone[5]);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};
				//ボーンネームからボーンIDの取得「移動先」
				ech = E3DGetBoneNoByName( cha_hsid[0], "移動先", &bone[6]);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};

				/*変数の代入*/
				MaxHP = 150;//最大HPの代入、!あとで移動させるかも!
				HP = MaxHP;//最大HPまで代入、!同上、移動させるかも!
				Stamina = 150;//固定スタミナ、あとで仕様変更するかも
	}

	/**/
	//クォータニオンを作成します
	/**/	
	for(int i = 0; i<10; i++){
				ech = E3DCreateQ( &Qid[i]);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};
				ech = E3DInitQ( Qid[i]);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};
	}



	/*所持した武器の中で最初に何を持っているか設定します*/
	Wp_equipment = Wpselect_equipment;




}


/*銃のロードを行うクラス内関数です。*/
int PlayerChara::GunLoad( int selwp_kind, int gunkind, int gunno){

	//変数の初期化
	int ech = 0;
	char loadname[256] = "";

	//一時的な変数（モデル格納等など）
	int hsid;//銃モデルのID
	int hit_hsid;//銃の当たり判定モデルID
	int g_spid;//銃スプライトのスプライトID
	int ammo;//弾薬の最大値
	int mag;//マガジンの最大値
	int distance;//射程距離の最大値
	int attack;//武器の攻撃値
	int bone[4];//銃のボーン
	int Garbage = 0;//いらない変数を格納します

	//すでに銃を取得しており、その銃データに上書きするなら

	if( wp_data[selwp_kind][0][0] != 0){//選択中のカテゴリにデータがあるのなら
				ech = E3DDestroyHandlerSet( wp_data[selwp_kind][0][0]);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};

				ech = E3DDestroySprite( wp_data[selwp_kind][0][0]);//スプライトを削除します
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};
		
	}




	//銃のモデルのロード

	if(gunkind == 1){//ハンドガン系

		if(gunno == 0){//M1911

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


				//M1911のデータを格納します。
				ammo = 7;
				mag = 7;
				distance = 100;
				attack = 100;
		}
		if(gunno == 2){//Glock95

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


				//Glockのデータを格納します。
				ammo = 50;
				mag = 3;
				distance = 60;
				attack = 30;
		}

		if(gunno == 3){//M92F

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

				//M92Fのデータを格納します。
				ammo = 15;
				mag = 2;
				distance = 120;
				attack = 80;
		}

	}
	if(gunkind == 4){//アサルトライフル系
	
		if(gunno == 0){//M4

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


				//M4のデータを格納します。
				ammo = 30;
				mag = 5;
				distance = 160;
				attack = 140;
		}
	}



	//変数をメンバー変数に格納します

	
		wp_data[selwp_kind][0][0] = hsid;//武器のモデルを格納
		wp_data[selwp_kind][0][1] = g_spid;//武器スプライトを格納
		wp_data[selwp_kind][0][2] = hit_hsid;//武器の当たりモデルを格納
		wp_data[selwp_kind][0][3] = 0;//武器の使用済み弾薬モデルを格納
		wp_data[selwp_kind][1][0] = gunkind;//武器の種類を格納
		wp_data[selwp_kind][1][1] = gunno;//武器のナンバーを格納
		wp_data[selwp_kind][1][2] = ammo;//最大弾薬数を格納
		wp_data[selwp_kind][1][3] = mag;//最大マガジン数を格納
		wp_data[selwp_kind][1][4] = distance;//射程距離を格納
		wp_data[selwp_kind][1][5] = attack;//射程距離を格納
		wp_data[selwp_kind][2][0] = bone[0];//銃口手前のボーンを格納
		wp_data[selwp_kind][2][1] = bone[1];//銃口手先のボーンを格納
		wp_data[selwp_kind][2][4] = bone[2];//銃口手先のボーンを格納
		wp_data[selwp_kind][2][5] = bone[3];//銃口手先のボーンを格納
		wp_data[selwp_kind][3][0] = ammo;//!!後で変えるかも!!弾薬数をいっぱいにする
		wp_data[selwp_kind][3][1] = mag;//!!後で変えるかも!!マガジン数をいっぱいにする

	return 0;
}


/*プレイヤーキャラクターのデコンストラクタ*/
PlayerChara::~PlayerChara(){

	int ech = 0;//エラー確認変数の初期化

	//キャラクターモデルを削除します
	E3DDestroyHandlerSet( cha_hsid[0]);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	//1つ目のキャラクターダミーモデルを削除します
	E3DDestroyHandlerSet( DummyModel);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	//銃のデータの削除します（最初から順番にメイン・サブ・グレネードの順番です）
	for(int i = 0;i < 3; i++){
		if( wp_data[i][0][0] != 0){//選択中のカテゴリにデータがあるのなら
					ech = E3DDestroyHandlerSet( wp_data[i][0][0]);//モデルを削除します
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
					};

					ech = E3DDestroySprite( wp_data[i][0][0]);//スプライトを削除します
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
					};
		}
	}

	/**/
	//クォータニオンを削除します
	/**/	
	for(int i = 0; i<4; i++){
				ech = E3DDestroyQ( Qid[i]);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};
	}


}