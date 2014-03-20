/* ステージクラス関数系の一部である、この"cStg_Tronp.cpp"コードは
// 「フォレスト」ステージのロード・初期化関係のことが書かれています。
/* /////////////////////////////////////////////////////////////////////////// */
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "cstage.h"//ステージ関係のクラスヘッダファイル


/* フォレストの読み込みを行ないます*/
int Stage::LoadStage_Forest( const int StageKind, float *FogDist){

	/* 変数の宣言 */
	int ech = 0;// エラーチェック変数の初期化
	int NaviPoint = 0;//新しく追加したナビポイントのIDを代入
	char loadname[256] = "";// 読み込みデータ用の文字列配列
	E3DCOLOR4UC FogColor = {50,50,50,50};// 霧の色を指定します
	D3DXVECTOR3 NaviPointPos( 0.0, 0.0, 0.0);//ナビポイント座標を代入する構造体


	/* //////////////////////////// */
	// ステージのロードを行ないます
	/* /////////////////////////// */

	if(StageKind == 0){
			wsprintf( loadname, "%s\\data\\3d\\map\\st_forest\\st_forest.sig", System::path);
			ech = E3DLoadSigFileAsGround(loadname, 40.0, 0, &Stage_hsid[0]);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			};
		
			wsprintf( loadname, "%s\\data\\3d\\map\\st_forest\\gwl_forest.mqo", System::path);
			ech = E3DLoadMQOFileAsMovableArea( loadname, 40.0, &Wall_hsid[1]);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			};

	};




	return 0;
}