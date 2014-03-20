/*ここでは、モデルやスプライトの描画に必要な情報を収集、また描画で必要な
//関数を自動的に実行することができるようにするためのクラスコードファイル
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "c_batch_preparat.h"//描画に必要なクラスの宣言ヘッダファイル
#include "clive.h"//敵やキャラの宣言ヘッダファイル
#include "cweapon.h"//武器に関することのクラスヘッダファイル


/*最初にロードしたスプライトの倍率や描画指定*/
int Batch_Render::BatchSpriteSet( const PlayerChara *PcC){

	/* 変数の初期化&宣言 */
	int NowEqip = PcC->Get_Wp_equipment();

	/* ///////////////////////////// */
	// スプライトの倍率を変更します 
	/* ///////////////////////////// */

	//HPバーについての倍率代入
	Set_SpriteMagX( "HPber", float( PcC->Get_HP()) / float( PcC->Get_MaxHP()) * 100.0f);

	//スタミナバーについての倍率代入
	Set_SpriteMagX( "Staminaber", float( PcC->Get_Stamina()) / (PcC->Get_MaxStamina()) * 100.0f);



	// 武器がなければこの先はエラー
	if( PcC->Get_Wp_equipment() == -1) return -1;

	//銃の弾薬についての倍率変換
	Set_SpriteMagX( "Ammober", float( PcC->Wpn.Get_WeaponPointer( NowEqip)->Get_NowAmmo()) / float(PcC->Wpn.Get_WeaponPointer( NowEqip)->Get_Ammo()) * 100.0f);

	//銃のマガジンについての倍率変換
	Set_SpriteMagX( "Magber", float( PcC->Wpn.Get_WeaponPointer( NowEqip)->Get_NowMagazine()) / float(PcC->Wpn.Get_WeaponPointer( NowEqip)->Get_Magazine() ) * 100.0f);


	
	

	return 0;
}

int Batch_Render::LoadSprite( const char *ObjPath, const float MagX, const float MagY, const float X, const float Y, const float Z, const int DeleteFromBRFlag){

	LoadSprite_AddName( ObjPath, "", MagX, MagY, X, Y, Z, DeleteFromBRFlag);

	return 0;
}

int Batch_Render::LoadSprite_AddName( const char *ObjPath, const char *Name, const float MagX, const float MagY, const float X, const float Y, const float Z, const int DeleteFromBRFlag){

	/* 変数の宣言&初期化 */
	int ech = 0;
	char loadname[256] = "";//読み込む先のパスの文字列変数
	int SpID;// スプライトのIDを格納する変数


	/* スプライトのロード */
	wsprintf( loadname, "%s\\%s", System::path, ObjPath);
	ech = E3DCreateSprite( loadname, 0, 0, &SpID);
	_ASSERT( ech != 1 );//エラーチェック

	LoadSpriteFromID( SpID, Name, MagX, MagY, X, Y, Z, DeleteFromBRFlag);



	return 0;
}

int Batch_Render::LoadSpriteFromID( const int ID, const char *Name, const float MagX, const float MagY, const float X, const float Y, const float Z, const int DeleteFromBRFlag){

	/* 変数の宣言&初期化 */
	Sprite SptC;

	SptC.ID = ID;
	SptC.MagX = MagX;
	SptC.MagY = MagY;
	SptC.X = X;
	SptC.Y = Y;
	SptC.Z = Z;
	SptC.ViewFlag = 1;
	wsprintf( SptC.Name, "%s", Name);

	Spt.push_back( SptC);


	return 0;
}



int Batch_Render::Set_SpriteMagX( const char *ObjName, const float Value){

	/* 変数の初期化&宣言 */
	int ech = 0;
	vector<Sprite>::iterator it;
	
	ech = SearchSpriteFromName( ObjName, &it);// イテレータ

	if( ech != 0){
			_ASSERT( 1);
			return -1;
	}
	
	/* MagXの設定 */
	(*it).MagX = Value;
	
	return 0;
}

int Batch_Render::SearchSpriteFromName( const char *ObjName, vector<Sprite>::iterator *it){

	/* 変数の初期化&宣言 */
	vector<Sprite>::iterator iit;// イテレータ

	for( iit = Spt.begin(); iit != Spt.end(); iit++){
			if( strcmp( ObjName, (*iit).Name) == 0){
					*it = iit;
					return 0;// ループを抜け出す
			}
	}

	// 検索した文字が見つからなければ
	_ASSERT( 1 );//エラーチェック


	return -1;
}

int Batch_Render::SetSpriteAlpha( const char *Name, E3DCOLOR4UC AlfaColor){

	/* 変数の初期化&宣言 */
	int ech = 0;
	vector<Sprite>::iterator it;
	
	ech = SearchSpriteFromName( Name, &it);// イテレータ

	if( ech != 0){
			_ASSERT( 1 );
			return -1;
	}

	/*半透明化します*/
	ech = E3DSetSpriteARGB( (*it).ID, AlfaColor);
	_ASSERT( ech != 1 );//エラーチェック


	return 0;
}