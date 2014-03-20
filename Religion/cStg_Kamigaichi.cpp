/* ステージクラス関数系の一部である、この"cStg_Tronp.cpp"コードは
// 「神ヶ一町」ステージのロード・初期化関係のことが書かれています。
/* /////////////////////////////////////////////////////////////////////////// */
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "cstage.h"//ステージ関係のクラスヘッダファイル


/* 神ヶ一町の読み込みを行ないます*/
int Stage::LoadStage_Kamigaichi( const int StageKind){



	LoadStageFromProfile( "st_kamigaichi.mpd");


	/* //////////////// */
	// ナビラインの作成 
	/* //////////////// */





	return 0;
}