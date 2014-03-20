/* ///////////////////////////////////////////////////////// */
// ここでは、バッチレンダーのアシスト関数に関すること
// を記述するクラスコードファイルです。
/* /////////////////////////////////////////////////////////  */
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include <string.h>
#include "c_batch_preparat.h"//描画に必要なクラスの宣言ヘッダファイル





int Batch_Render::Set_SpriteMagY( const char *ObjName, const float Value){

	/* 変数の初期化&宣言 */
	int ech = 0;
	vector<Sprite>::iterator it;
	
	ech = SearchSpriteFromName( ObjName, &it);// イテレータ
	
	if( ech != 0){
			_ASSERT( 1);
			return -1;
	}

	/* MagXの設定 */
	(*it).MagY = Value;
	
	return 0;
}

int Batch_Render::Set_SpriteX( const char *ObjName, const float Value){

	/* 変数の初期化&宣言 */
	int ech = 0;
	vector<Sprite>::iterator it;
	
	ech = SearchSpriteFromName( ObjName, &it);// イテレータ
	
	if( ech != 0){
			_ASSERT( 1);
			return -1;
	}

	/* MagXの設定 */
	(*it).X = Value;
	
	return 0;
}

int Batch_Render::Set_SpriteY( const char *ObjName, const float Value){

	/* 変数の初期化&宣言 */
	int ech = 0;
	vector<Sprite>::iterator it;
	
	ech = SearchSpriteFromName( ObjName, &it);// イテレータ
	
	if( ech != 0){
			_ASSERT( 1);
			return -1;
	}

	/* MagXの設定 */
	(*it).Y = Value;
	
	return 0;
}

int Batch_Render::Set_ViewFlag( const char *ObjName, const bool Value){

	/* 変数の初期化&宣言 */
	int ech = 0;
	vector<Sprite>::iterator it;
	
	ech = SearchSpriteFromName( ObjName, &it);// イテレータ
	
	if( ech != 0){
			_ASSERT( 1);
			return -1;
	}

	/* MagXの設定 */
	(*it).ViewFlag = Value;
	
	return 0;
}