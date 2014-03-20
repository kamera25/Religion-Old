/*ここでは、モデルやスプライトの描画に必要な情報を収集、また描画で必要な
//関数を自動的に実行することができるようにするためのクラスコードファイル
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include <time.h>
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "c_batch_preparat.h"//描画に必要なクラスの宣言ヘッダファイル
#include "clive.h"//敵やキャラの宣言ヘッダファイル
#include "cweapon.h"//武器に関することのクラスヘッダファイル
#include "cMission.h"

/*文字を描画することや設定をしたりします*/


int Batch_Render::BatchFont( const int SceneEndFlg, const PlayerChara *PcC, const struct GameTimer Timer){

	/*変数の初期化*/
	int ech = 0;//エラーチェック用の確認変数
	float Scale = 1.6f;//文字の大きさを格納する変数
	char ParometaString[64] = "";//表示させる文字を入れます
	D3DXVECTOR2 Pos( 0.0, 0.0);//座標を代入する構造体
	E3DCOLOR4UC Color = { 255, 50, 50, 50};//空の構造体
	const E3DCOLOR4UC Gray = { 255, 50, 50, 50};//色構造体、グレーを指定
	const E3DCOLOR4UC White = { 255, 230, 230, 230};//色構造体、白を指定
	const E3DCOLOR4UC Red = { 255, 255, 100, 100};//色構造体、赤を指定
	const E3DCOLOR4UC Bule = { 255, 100, 100, 250};//色構造体、青を指定
	const E3DCOLOR4UC Yellow = { 255, 255, 255, 100};//色構造体、黄を指定
	const E3DCOLOR4UC Black = { 255, 0, 0, 0};//色構造体、黒を指定
	int Eqip = 0;
	int NowAmmo = 0;
	int Ammo = 0;
	int Magazine = 0;
	int NowMagazine = 0;

	/*文字の描画*/
	// 名前部分の描画
	Pos.x = 28.0f;/**/Pos.y = 394.0f;

	ech = E3DDrawText( Pos, Scale, Gray, "F19");
	_ASSERT( ech != 1 );//エラーチェック


	if( PcC->Get_Wp_equipment() != -1){ //武器がなし以外なら

			Eqip = PcC->Get_Wp_equipment();
			NowAmmo = PcC->Wpn.Get_WeaponPointer(Eqip)->Get_NowAmmo();
			Ammo = PcC->Wpn.Get_WeaponPointer(Eqip)->Get_Ammo();
			Magazine = PcC->Wpn.Get_WeaponPointer(Eqip)->Get_Magazine();
			NowMagazine = PcC->Wpn.Get_WeaponPointer(Eqip)->Get_NowMagazine();

			/* サポート系に対する処理 */
			if( Magazine == -1){
					Magazine = 0;
					NowMagazine = 0;
			}


			/*現在のAmmoの数を表示します*/
			if( NowAmmo == 0){//弾薬がなくなったら
					Color = Red;// 赤色にします
			}
			else if( Ammo < NowAmmo){//弾が増えているならなら
					Color = Bule;// 青にします
			}
			else if( double(NowAmmo) / double(Ammo) < 0.3){//弾薬が3割以下なら
					Color = Yellow;// 黄にします
			}
			else{//通常モードなら
					Color = White;// 白にします
			}
			wsprintf( ParometaString, "%d", NowAmmo);
			RenderFont( ParometaString, 558.0f, 394.0f, 1.4f, Color);

			/*Ammoの数を表示します*/
			wsprintf( ParometaString, "%d", Ammo);
			RenderFont( ParometaString, 588.0f, 394.0f, 1.4f, White);

			/*現在のMagの数を表示します*/
			if( NowMagazine == 0){//マガジンがなくなったら
					Color = Red;// 赤色にします
			}
			else if( double(NowMagazine) / double(Magazine) < 0.35){//弾薬が3割以下なら
					Color = Yellow;// 黄にします
			}
			else{//通常モードなら
					Color = White;// 白にします
			}
			wsprintf( ParometaString, "%d", NowMagazine, 3);
			RenderFont( ParometaString, 558.0f, 424.0f, 1.4f, Color);

			/*Magの数を表示します*/
			wsprintf( ParometaString, "%d", Magazine, 3);
			RenderFont( ParometaString, 588.0f, 424.0f, 1.4f, White);
	}

	// もし、時間制限がありなら
	if( *(Timer.TimeUsing) == true)
	{
		int LimitTime = Timer.LimitTime;
		double PlayTime = ( clock() - (double)Timer.FirstTime) / (double)CLOCKS_PER_SEC;
		
		// 時間表示を増加するように見せる
		if( Timer.IndicateTimeNormal == true)
		{

			sprintf_s( ParometaString, "%02d . %02d . %02d", (int)PlayTime / 60 , (int)PlayTime % 60, (int)(PlayTime*100 - (int)PlayTime * 100));
			RenderFont( ParometaString, 10.0f, 10.0f, 0.6f, White);
		}
		// 時間表示を減少するように見せる
		else
		{
			// 時間が1分以下なら
			if( (LimitTime - (int)PlayTime) / 60 < 1)
			{
				Color = Red;
			}
			// それ以外なら
			else
			{
				Color = Bule;
			}
			sprintf_s( ParometaString, "%02d . %02d . %02d", (LimitTime - (int)PlayTime) / 60, (LimitTime - (int)PlayTime) % 60, 99 - (int)(PlayTime*100 - (int)PlayTime * 100));
			RenderFont( ParometaString, 10.0f, 10.0f, 0.6f, Color);
			
			/*char test[120];
			static int i = 0;
			wsprintf( test, "%d : Spending 10 minites.", i);
			if( (int)PlayTime%10 ) PutLog(test);
			i++;*/
		}
	}

	/* ログの表示 */
	vector<GameLog>::iterator it;  // イテレータのインスタンス化
	int i = 0;

	for( it = ( Log.begin() + (Log.size() - 2)); it != Log.end() && i <2; it++)
	{
		
		RenderFont( (*it).Messeage, 400.0f, 20.0f - i * 20.f, 1.2f, White);
		i++;
	}



	/*
	//描画の終了処理
	*/
	if( SceneEndFlg == 1){

		ech = E3DEndScene();
		_ASSERT( ech != 1 );//エラーチェック
	}

	return 0;
}

/* 英文字を描画します */
int Batch_Render::RenderFont( char *Str, float Posx, float Posy, float MagScl, E3DCOLOR4UC Color){

	/* 変数の初期化 */
	int ech;
	D3DXVECTOR2 Pos( 0.0, 0.0);//座標を代入する構造体

	Pos.x = Posx;/**/Pos.y = Posy;
	ech = E3DDrawText( Pos, MagScl, Color, Str);
	_ASSERT( ech != 1 );//エラーチェック


	return 0;
}



/* ログを表示させる関数 */
int Batch_Render::PutLog( const char *Messeage)
{
	/* 初期化 */
	struct GameLog GLog;

	strcpy_s( GLog.Messeage, Messeage);


	Log.push_back(GLog);

	return 0;
}

/* ログを表示させる関数 */
int Batch_Render::ResetLog()
{
	
	/* 初期化 */
	Log.clear();
	
	

	PutLog("");
	PutLog("");

	return 0;
}