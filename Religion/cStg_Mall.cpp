/* ステージクラス関数系の一部である、この"cStg_Tronp.cpp"コードは
// 「レリギオンモール」ステージのロード・初期化関係のことが書かれています。
/* /////////////////////////////////////////////////////////////////////////// */
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "cstage.h"//ステージ関係のクラスヘッダファイル


/* レリギオンモールの読み込みを行ないます*/
int Stage::LoadStage_Mall( const int StageKind){

	/* 変数の宣言 */
	int ech = 0;// エラーチェック変数の初期化
	char loadname[256] = "";// 読み込みデータ用の文字列配列
	E3DCOLOR4UC FogColor = {255,255,255,255};// 霧の色を指定します


	/* //////////////////////////// */
	// ステージのロードを行ないます
	/* /////////////////////////// */

	if(StageKind == 0){
					wsprintf( loadname, "%s\\data\\3d\\map\\st_rm\\rm.sig", System::path);
					ech = E3DLoadSigFileAsGround(loadname, 55.0, 0, &Stage_hsid[0]);
					if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
							return 1;//問題ありで終了
					};
	};


	/* //////////////////// */
	// 霧の指定を行ないます
	/* /////////////////// */

	E3DSetLinearFogParams(1, FogColor, 15000, 100000, -1);//ファグをかけます。
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
				return 1;//問題ありで終了
	}

	Stage_GunTarget = 0;//ステージの銃操作を"通常"にする
	Stage_GndMode = 0;//キャラ地面操作を"通常にする"



	return 0;
}