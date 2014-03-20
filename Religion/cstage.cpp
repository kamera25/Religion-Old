/*ここでは、ステージの読み込み、制御を行う関数を定義するクラスコードファイルです。
//
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "cstage.h"//ステージ関係のクラスヘッダファイル



/*ステージをロード・設定する関数です*/
int Stage::LoadStage(int StageID, int StageKind, int LightKind){

	/* 変数の宣言 */
	int ech = 0;//エラーチェック変数の初期化
	int NaviPoint = 0;//新しく追加したナビポイントのIDを代入
	float FogDist = 1000.0;//背景の距離を指定する変数、通常は1000(近い)
	char loadname[256] = "";//読み込みデータ用の文字列配列
	D3DXVECTOR3 NaviPointPos( 0.0, 0.0, 0.0);//ナビポイント座標を代入する構造体


	//ステージ上のデータを初期化します。
	for(int i = 0; i < 3; i++){
		Stage_hsid[i]= 0;//ステージ配列を初期化します
		Wall_hsid[i] = 0;//壁配列を初期化します
	};



	/* ///////////////////////////// */
	// 以下より、マップを準備します
	/* ///////////////////////////// */

	switch(StageID){
			case 0:{// トロンプールなら
					LoadStage_Tronp( StageKind);
					break;
			}
			case 1:{// インターネットロビーなら
					LoadStage_IRoby( StageKind);
					break;
			}
			case 2:{// 森林なら
					LoadStage_Forest( StageKind, &FogDist);
					break;
			}
			case 3:{// 神ヶ一町なら
					LoadStage_Kamigaichi( StageKind);
					break;
			}
			case 4:{// レリギオンモールなら
					LoadStage_Mall( StageKind);
					break;
			}
			case 5:{// 基地前なら
					LoadStage_BaseFront( StageKind);
					break;
			}
			case 6:{// レトリスなら
					LoadStage_Retolis( StageKind, &FogDist);
					break;
			}
	}

	/* /////////////////////////// */
	//  以下より、光源を用意します。
	/* /////////////////////////// */

	//光源の属性を決定します。
	SetStageLight( LightKind, FogDist);



	/* ////////////////////////// */
	//  最後に変数操作を行います。
	/* ////////////////////////// */

	Stage_ID = StageID;//ステージIDを代入
	Stage_Kind = StageKind;//ステージの種類を代入



	return 0;
}
/* ステージにセットするライトの設定を行ないます */
int Stage::SetStageLight( const int LightKind, const float FogDist){

	/* 変数の宣言 */
	int ech = 0;//エラーチェック変数の初期化
	char loadname[256] = "";// 読み込みデータ用の文字列配列
	const char LoadBGName[3][12] = { "hare.jpg", "sunset.jpg", "night.jpg"};// ロードする背景パス変数
	const D3DXVECTOR3 ldir1( -1.0, -1.0, -1.0);
	const D3DXVECTOR3 ldir2( 1.0, 1.0, 1.0);
	E3DCOLOR4UC LightColor = { 0, 0, 0, 0};



	/* //////////////// */
	// 光源を作成します
	/* //////////////// */
	ech = E3DCreateLight( &Light1_ID);//光源1を作成します。
	if( ech != 0){
			_ASSERT( 0 );
	};
	ech = E3DCreateLight( &Light2_ID);//光源2を作成します。
	if( ech != 0){
			_ASSERT( 0 );
	};


	/* ///////////////// */
	// 光源の色を代入します
	/* ///////////////// */
	switch(LightKind){
			case 0:{// 晴れなら
					LightColor.b = 255;
					LightColor.g = 255;
					LightColor.r = 255;
					break;
			}
			case 1:{// 夕方なら
					LightColor.b = 50;
					LightColor.g = 50;
					LightColor.r = 255;
					break;
			}
			case 2:{// 夜なら
					LightColor.b = 50;
					LightColor.g = 50;
					LightColor.r = 50;
					break;
			}
	}


	/* /////////////////// */
	// 光源に色を割り当てます
	/* /////////////////// */

	//一つ目のライトを設定する。
	ech = E3DSetDirectionalLight( Light1_ID, ldir1, LightColor);
	if( ech != 0){
			_ASSERT( 0 );
	};

	//二つ目のライトを設定する。
	ech = E3DSetDirectionalLight( Light2_ID, ldir2, LightColor);
	if( ech != 0){
			_ASSERT( 0 );
	};


	/* /////////////// */
	// 背景をロードします
	/* /////////////// */
	wsprintf( loadname, "%s\\data\\3d\\map\\360\\%s", System::path, LoadBGName[LightKind]);
	ech = E3DCreateBG( System::scid1, loadname, "", 0, 0, 1, FogDist);
	if( ech != 0){
			_ASSERT( 0 );
	};



	//一つ目のバンプマップの光源を指定します
	ech = E3DSetLightIdOfBumpMap( Light1_ID); 
	if( ech != 0){
				_ASSERT( 0 );
	};


	return 0;
}

/*Stageクラスのデコンストラクタ、ロードした情報などを削除します。*/
Stage::~Stage(){

	//変数の初期化を行います
	int ech = 0;//エラーチェック変数の初期化
	

	//ステージと壁を削除します
	for(int i = 0; i < 3; i++){
		if(Stage_hsid[i] != 0){//ステージを削除します
				ech = E3DDestroyHandlerSet( Stage_hsid[i]);
				if( ech != 0){
							_ASSERT( 0 );
				};
		}
		if(Wall_hsid[i] != 0){//壁を削除します
				ech = E3DDestroyHandlerSet( Wall_hsid[i]);
				if( ech != 0){
							_ASSERT( 0 );
				};
		}
	};




	/*光源を削除するよ*/

	//一つ目の光源の削除
	ech = E3DDestroyLight( Light1_ID);
	if( ech != 0){
				_ASSERT( 0 );
	};
	//一つ目の光源の削除
	ech = E3DDestroyLight( Light2_ID);
	if( ech != 0){
				_ASSERT( 0 );
	};


	//背景を削除します
	ech = E3DDestroyBG( System::scid1);
	if( ech != 0){
				_ASSERT( 0 );
	};


}