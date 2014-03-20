/* ステージクラス関数系の一部である、この"cStg_Tronp.cpp"コードは
// 「レトリス」ステージのロード・初期化関係のことが書かれています。
/* /////////////////////////////////////////////////////////////////////////// */
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "cstage.h"//ステージ関係のクラスヘッダファイル


/* トロンプールの読み込みを行ないます*/
int Stage::LoadStage_Retolis( const int StageKind, float *FogDist){


	LoadStageFromProfile( "st_retolis.mpd");

	*FogDist = 8000.0f;//背景のもやで見えにくくする。
	/* //////////////// */
	// ナビラインの作成 
	/* //////////////// */
	int ANaviPoint = 0;
	int BNaviPoint = 0;


	Navi.NaviRailOnOffSwitch( true);// ナビレールを使用する
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