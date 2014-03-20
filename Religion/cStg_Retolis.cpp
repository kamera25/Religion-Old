/* ステージクラス関数系の一部である、この"cStg_Tronp.cpp"コードは
// 「レトリス」ステージのロード・初期化関係のことが書かれています。
/* /////////////////////////////////////////////////////////////////////////// */
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "cstage.h"//ステージ関係のクラスヘッダファイル


/* トロンプールの読み込みを行ないます*/
int Stage::LoadStage_Retolis( const int StageKind, float *FogDist){

	/* 変数の宣言 */
	int ech = 0;// エラーチェック変数の初期化
	int NaviPoint = 0;//新しく追加したナビポイントのIDを代入
	char loadname[256] = "";// 読み込みデータ用の文字列配列
	E3DCOLOR4UC FogColor = {255,0,0,0};// 霧の色を指定します
	D3DXVECTOR3 NaviPointPos( 0.0, 0.0, 0.0);//ナビポイント座標を代入する構造体


	/* //////////////////////////// */
	// ステージのロードを行ないます
	/* /////////////////////////// */

	if(StageKind == 0){
					wsprintf( loadname, "%s\\data\\3d\\map\\st_retolis\\st_retolis.sig", System::path);
					ech = E3DLoadSigFileAsGround(loadname, 55.0, 0, &Stage_hsid[0]);
					if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
							return 1;//問題ありで終了
					};
	};


	/* //////////////////// */
	// 霧の指定を行ないます
	/* /////////////////// */

	ech = E3DSetLinearFogParams(1, FogColor, 0, 20000, -1);//ファグをかけます。
	_ASSERT( ech != 1 );//エラーダイアログ


	*FogDist = 8000.0f;//背景のもやで見えにくくする。
	Stage_GunTarget = 0;//ステージの銃操作を"通常"にする
	Stage_GndMode = 0;//キャラ地面操作を"通常にする"



	/* //////////////// */
	// ナビラインの作成 
	/* //////////////// */
	int ANaviPoint = 0;
	int BNaviPoint = 0;


	Navi.NaviRailOnOffSwitch( 1);// ナビレールを使用する
	Navi.AddNaviPointToStage( -1, 0, -106.49518f, 2105.9500f, 4596.2803f);// ナビレール0
	Navi.AddNaviPointToStage( -1, 0, -727.48090f, 2105.9500f, -1364.0236f);
	Navi.AddNaviPointToStage( -1, 0, -4238.1382f, 2105.9500f, -4166.2183f);
	ANaviPoint = Navi.AddNaviPointToStage( -1, 0, -9303.3115f, 2105.9500f, -6399.7251f);
	Navi.AddNaviPointToStage( -1, 0, -6660.0215f, 2105.9500f, 2587.4690f);


	BNaviPoint = Navi.AddNaviPointToStage( -1, 1, -9587.6592f, 2105.9500f, -12795.226f);// ナビレール1
	Navi.AddNaviPointToStage( -1, 1, -15797.104f, 2105.9500f, -12412.747f);
	Navi.AddNaviPointToStage( -1, 1, -16401.408f, 2105.9500f, -15693.905f);
	Navi.AddNaviPointToStage( -1, 1, -14735.134f, 2105.9500f, -19126.313f);
	Navi.AddNaviPointToStage( -1, 1, -11618.377f, 2105.9500f, -20582.639f);
	Navi.AddNaviPointToStage( -1, 1, 3346.5337f, 2105.9500f, -21234.010f);
	Navi.AddNaviPointToStage( -1, 1, 6677.0371f, 2105.9500f, -18553.188f);
	Navi.AddNaviPointToStage( -1, 1, 2218.3247f, 2105.9500f, -14321.980f);
	Navi.AddNaviPointToStage( -1, 1, 266.76770f, 2105.9500f, -13969.053f);
	Navi.AddNaviPointToStage( -1, 1, -141.62057f, 2105.9500f, -16286.854f);
	Navi.AddNaviPointToStage( -1, 1, -8746.4385f, 2105.9500f, -16191.914f);


	Navi.AddNaviPointToStage( -1, 2, -9394.7578f, 2105.9500f, -8282.7041f);// ナビレール2(接続線)
	Navi.AddNaviPointToStage( -1, 2, -9451.8779f, 2105.9500f, -10827.891f);
	Navi.NRGivenTransfarFromAToB( 2, 0, ANaviPoint, 1, BNaviPoint);

	return 0;
}