/* ////////////////////////////////////////////////////////////////////////// */
   //ここでは、初期化・終了・プロージャーに渡すという行為を行うクラスコードファイルです。
/* ////////////////////////////////////////////////////////////////////////// */
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ


/* ステージプロファイルからステージの読み込みを行います */
int Weapon::LoadEwaponFromCSV( const char *WeaponName){

	/* 初期化 */
	int Version;
	int ech = 0;
	const int wfindhash = ( WeaponName[0] * 13 + WeaponName[1] * 5) % 17;;// 文字列のハッシュ値
	FILE *fp; // ファイルポインタ
	char LoadPath[256];
	char Loadstr[256];
	char *pstr;

	wsprintf( LoadPath, "%s\\data\\prof\\weapon\\data.csv", System::path);
	fopen_s( &fp, LoadPath, "r");//指定されたファイルをオープンします。 
	if( fp == NULL){
		_ASSERT( 0 );
		return -1;
	}
	
	
	/* 改行後最初の文字列を取得 */
	while( ret = fscanf_s( fp, "\n%[^,],", Loadstr, 64) ){
		
		int hash = ( LoadStr[0] * 13 + LoadStr[1] * 5) % 17;
		if( hash == wfindhash){// hashが同じなら
			if( strcmp( Loadstr, WeaponName) != 0){// 同じなら、データ読み込みをする。
			
				fscanf_s( fp, ",%d,%f,%d,%f,%[^,],%d,%f"
							, );
			}
		}
	}
	Set_Kind( Wpkind);
	Set_Number( Wpno);

	Set_Attack( GunData[Wpno][0]);
	Set_Range( GunData[Wpno][1]);
	Set_Ammo( GunData[Wpno][2]);


	if( fclose(fp) == EOF){
		return -1;
	}
		


	return 0;
}
