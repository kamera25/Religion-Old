/*ここでは、生物クラスのキャラ・敵の関数を定義するクラスコードファイルです。
//特にゲームを開始する時に必要な関数が多く書かれています。
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "clive.h"//敵やキャラの宣言ヘッダファイル





/*プレイヤーキャラクターのコンストラクタ*/
PlayerChara::PlayerChara( int selchara, int Wpselect_equipment){

	//変数の初期化
	int ech = 0;
	char loadname[256] = "";


	//クラスメンバ変数の初期化

	
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
				wsprintf( loadname, "%s\\data\\3d\\model\\demo\\hito.sig", System::path);//アーティーモデルのsig名登録
				ech = E3DSigLoad( loadname, 0, 0, &cha_hsid[0]);//モデルの読み込み、cha_hsidへモデルを入れる。
				if(ech != 0 ){//エラーチェック
							_ASSERT(0);//エラーダイアログ
				};

				//ハンドモデルの取得
				wsprintf( loadname, "%s\\data\\3d\\model\\hand\\hand.sig", System::path);//ハンドモデルのsig名登録
				ech = E3DSigLoad( loadname, 0, 1, &cha_hsid[1]);//モデルの読み込み、cha_hsidへモデルを入れる。
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};

				//ダミーモデルの取得
				wsprintf( loadname, "%s\\data\\3d\\model\\other\\demo.sig", System::path);//仮モデルのsig名登録
				ech = E3DSigLoad( loadname, 0, 1, &DummyModel);//モデルの読み込み、submodidへモデルを入れる。
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};

	}

		if(selchara == 1){//WF兵1モデル

				//WF兵1モデルの取得
				wsprintf( loadname, "%s\\data\\3d\\chara\\wf1\\model.sig", System::path);//アーティーモデルのsig名登録
				ech = E3DSigLoad( loadname, 0, 0.15f, &cha_hsid[0]);//モデルの読み込み、cha_hsidへモデルを入れる。
				if(ech != 0 ){//エラーチェック
							_ASSERT(0);//エラーダイアログ
				};

				//ダミーモデルの取得
				wsprintf( loadname, "%s\\data\\3d\\model\\other\\demo.sig", System::path);//仮モデルのsig名登録
				ech = E3DSigLoad( loadname, 0, 0.01f, &DummyModel);//モデルの読み込み、submodidへモデルを入れる。
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};

				//モーションデータ構え
				wsprintf( loadname, "%s\\data\\3d\\chara\\motion\\pc_motion.moa", System::path);//仮モデルのsig名登録
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