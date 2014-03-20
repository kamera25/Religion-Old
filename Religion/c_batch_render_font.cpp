/*ここでは、モデルやスプライトの描画に必要な情報を収集、また描画で必要な
//関数を自動的に実行することができるようにするためのクラスコードファイル
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "c_batch_preparat.h"//描画に必要なクラスの宣言ヘッダファイル
#include "clive.h"//敵やキャラの宣言ヘッダファイル
#include "cweapon.h"//武器に関することのクラスヘッダファイル

/*文字を描画することや設定をしたりします*/
int Batch_Render::BatchFont( const int SceneEndFlg, const PlayerChara *PcC){

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
	int Eqip = 0;
	int NowAmmo = 0;
	int Ammo = 0;
	int Magazine = 0;
	int NowMagazine = 0;

	/*文字の描画*/
	//HP部分の描画
	Pos.x = 28.0f;/**/Pos.y = 394.0f;
	ech = E3DDrawText( Pos, Scale, Gray, "F19");
	_ASSERT( ech != 1 );//エラーチェック


	if( PcC->Get_Wp_equipment() != -1){ //武器がなし以外なら

			Eqip = PcC->Get_Wp_equipment();
			NowAmmo = PcC->Wpn.Get_WeaponPointer(Eqip)->Get_NowAmmo();
			Ammo = PcC->Wpn.Get_WeaponPointer(Eqip)->Get_Ammo();
			Magazine = PcC->Wpn.Get_WeaponPointer(Eqip)->Get_Magazine();
			NowMagazine = PcC->Wpn.Get_WeaponPointer(Eqip)->Get_NowMagazine();


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
			Pos.x = 558.0f;/**/Pos.y = 394.0f;
			ech = E3DDrawText( Pos, 1.4f, Color, ParometaString);
			_ASSERT( ech != 1 );//エラーチェック

			/*Ammoの数を表示します*/
			wsprintf( ParometaString, "%d", Ammo);
			Pos.x = 588.0f;/**/Pos.y = 394.0f;
			ech = E3DDrawText( Pos, 1.4f, White, ParometaString);
			_ASSERT( ech != 1 );//エラーチェック

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
			wsprintf( ParometaString, "%d", NowMagazine, 1);
			Pos.x = 558.0f;/**/Pos.y = 424.0f;
			ech = E3DDrawText( Pos, 1.4f, Color, ParometaString);
			_ASSERT( ech != 1 );//エラーチェック

			/*Magの数を表示します*/
			wsprintf( ParometaString, "%d", Magazine, 3);
			Pos.x = 588.0f;/**/Pos.y = 424.0f;
			ech = E3DDrawText( Pos, 1.4f, White, ParometaString);
			_ASSERT( ech != 1 );//エラーチェック

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

