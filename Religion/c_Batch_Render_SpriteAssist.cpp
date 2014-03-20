/* ///////////////////////////////////////////////////////// */
// ここでは、バッチレンダーのアシスト関数に関すること
// を記述するクラスコードファイルです。
/* /////////////////////////////////////////////////////////  */
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include <string.h>
#include "c_batch_preparat.h"//描画に必要なクラスの宣言ヘッダファイル
#include <string>




int Batch_Render::Set_SpriteMagY( const char *ObjName, const float Value){

	/* 変数の初期化&宣言 */
	int ech = 0;
	map<string, Sprite>::iterator it;
	
	if( Spt.count(ObjName))
	{
		it = Spt.find(ObjName);
	}
	else// 検索した文字が見つからなければ
	{
			_ASSERT( 1 );//エラー
			return -1;
	}

	/* MagXの設定 */
	(*it).second.MagY = Value;
	
	return 0;
}

int Batch_Render::Set_SpriteX( const char *ObjName, const float Value){

	/* 変数の初期化&宣言 */
	int ech = 0;
	map<string, Sprite>::iterator it;
	
	if( Spt.count(ObjName))
	{
		it = Spt.find(ObjName);
	}
	else// 検索した文字が見つからなければ
	{
			_ASSERT( 1 );//エラー
			return -1;
	}

	/* MagXの設定 */
	(*it).second.X = Value;
	
	return 0;
}

int Batch_Render::Set_SpriteY( const char *ObjName, const float Value){

	/* 変数の初期化&宣言 */
	int ech = 0;
	map<string, Sprite>::iterator it;
	
	if( Spt.count(ObjName))
	{
		it = Spt.find(ObjName);
	}
	else// 検索した文字が見つからなければ
	{
			_ASSERT( 1 );//エラー
			return -1;
	}

	/* MagXの設定 */
	(*it).second.Y = Value;
	
	return 0;
}

int Batch_Render::Set_ViewFlag( const char *ObjName, const bool Value){

	/* 変数の初期化&宣言 */
	int ech = 0;
	map<string, Sprite>::iterator it;
	
	if( Spt.count(ObjName))
	{
		it = Spt.find(ObjName);
	}
	else// 検索した文字が見つからなければ
	{
			_ASSERT( 1 );//エラー
			return -1;
	}

	/* MagXの設定 */
	(*it).second.ViewFlag = Value;
	
	return 0;
}

int Batch_Render::test()
{
	
	Spt.count("MainWp");
	PutLog("hello");

	return 0;
}