/* ////////////////////////////////////////////////////////////////////////// */
// cMenu2クラスソースファイルです。
// cMenu2クラスを継承することで、メニュー部分の共通システムを簡潔に組み込めます。
/* ////////////////////////////////////////////////////////////////////////// */
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "cMenu.h"
#include "cGUI.h"// GUIのサブセットを使います

Menu::Menu() {

	/* 変数の初期化&宣言 */
	int ech = 0;// 初期化
	char loadname[256] = "";//ロードするファイル名の文字列配列

	///* メンバ変数の初期化 */
	//SpriteSum = 0;
	//for( int i=0; i<10; i++){
	//		SpriteID[i] = -1;
	//		Btn[i].X = -1;
	//		Bal[i].X = -1;
	//}



	/*スプライトをロードします*/
	wsprintf( loadname, "%s\\data\\img\\menu\\menubg.png", System::path);//メニュー画面での背景をロードします。
	ech = E3DCreateSprite( loadname, 0, 0, &Foundation_BG[0]);
	_ASSERT( ech != 1 );//エラーチェック

	wsprintf( loadname, "%s\\data\\img\\menu\\menuber.png", System::path);//メニュー画面での十字バーをロードします。
	ech = E3DCreateSprite( loadname, 0, 0, &Foundation_BG[1]);
	_ASSERT( ech != 1 );//エラーチェック

	wsprintf( loadname, "%s\\data\\img\\menu\\menu_up_ber.png", System::path);//メニュー画面での上部白いバーをロードします。
	ech = E3DCreateSprite( loadname, 0, 0, &Foundation_BG[2]);
	_ASSERT( ech != 1 );//エラーチェック


	///* メニューで使う文字IDを設定します。*/
	//ech = E3DCreateFont( 35, 0, 800, 0, 0, 0, "MS Pゴシック", &Font[0]);//大文字
	//_ASSERT( ech != 1 );//エラーチェック

	//ech = E3DCreateFont( 30, 0, 800, 0, 0, 0, "MS Pゴシック", &Font[1]);//中文字
	//_ASSERT( ech != 1 );//エラーチェック

	//ech = E3DCreateFont( 25, 0, 800, 0, 0, 0, "MS Pゴシック", &Font[2]);//小文字
	//_ASSERT( ech != 1 );//エラーチェック


	return;
}

//int Menu::LoadImg( const char *FilePath, int *SpriteID){
//
//	/* 変数の初期化&宣言 */
//	int ech = 0;// 
//	int IDNum = 0;//  
//	char loadname[256] = "";
//
//
//	if( SpriteSum == 10){		
//			return -1;
//	}
//
//	/* 空の配列を検索して、 */
//	for( int i=0; i<10; i++){
//			if( SpriteID[i] = 0){
//					IDNum = i;
//					break;
//			}
//	}
//
//	wsprintf( loadname, "%s\\%s", FilePath, System::path);//メニュー画面での上部白いバーをロードします。
//	ech = E3DCreateSprite( loadname, 0, 0, &SpriteID[IDNum]);
//	_ASSERT( ech != 1 );//エラーチェック
//
//	/* 代入されたIDをSpriteIDに返します */
//	*SpriteID = IDNum;
//
//	return 0;
//}
//
//int Menu::MakeFontButton( const char *Message, int *ButtonID, const int X, const int Y, const int MaxX, const int MaxY){
//
//	/* 変数の初期化&宣言 */
//	int ech = 0;// 初期化
//	int InputID = -1;
//	
//	for( int i=0; i<10; i++){
//			if( Btn[i].X == -1){// 開いてる変数があれば
//					InputID = i;
//					break;
//			}
//	}
//	if( InputID == -1){// 開いている配列がなければ
//			return -1;
//	}
//
//	/* 配列に代入する */
//	Btn[InputID].X = X;
//	Btn[InputID].Y = Y;
//	Btn[InputID].MaxX = MaxX;
//	Btn[InputID].MaxY = MaxY;
//
//	wsprintf( Btn[InputID].String, "%s" , Message);//文字列のコピー
//
//	/* ボタンIDを呼び出した関数へ返す */
//	*ButtonID = InputID;
//	
//
//
//
//	return 0;
//}
//
//int Menu::MakeFontButton_Auto( const char *Message, int *ButtonID, const int X, const int Y){
//
//
//	MakeFontButton( Message, ButtonID, X, Y, X + 150, Y + 50);
//
//	return 0;
//}
//
//int Menu::ChkFontButton( const int MouseX, const int MouseY){
//
//	/* 定数の宣言 */
//	int SelectedButton = -1;
//
//
//	for( int i=0; i<10; i++){
//
//
//			if( Btn[i].X == -1) continue;//存在しないボタンが選択されたら
//			
//			/* カーソルがボタンの範囲内にあれば */
//			if( ( ( Btn[i].X < MouseX) && (MouseX < Btn[i].MaxX)) // X座標
//				&& ( Btn[i].Y + 20  < MouseY) && ( MouseY < Btn[i].MaxY)){
//
//					/* 選択されている色の文字を表示 */
//					PutString( Btn[i].String, Btn[i].X, Btn[i].Y, F_SMALL, BLUE);
//					SelectedButton = i;
//			}
//			else{
//					PutString( Btn[i].String, Btn[i].X, Btn[i].Y, F_SMALL, WHITE);
//					
//			}
//	}
//
//
//	return SelectedButton;
//}
//
//int Menu::MakeBalloonFromButton( const char *Message, int *BalloonID, int *ButtonID, const int X, const int Y){
//
//	MakeBalloon( Message, BalloonID, X, Y, Btn[*ButtonID].X, Btn[*ButtonID].Y + 20, Btn[*ButtonID].MaxX, Btn[*ButtonID].MaxY);
//
//	return 0;
//}
//
//int Menu::MakeBalloon( const char *Message, int *BalloonID, const int X, const int Y , const int MouseX, const int MouseY, const int MouseMaxX, const int MouseMaxY){
//
//	/* 変数の初期化&宣言 */
//	int ech = 0;// 初期化
//	int InputID = -1;
//	SIZE FontSize;
//
//	for( int i=0; i<10; i++){
//			if( Bal[i].X == -1){// 開いてる変数があれば
//					InputID = i;
//					break;
//			}
//	}
//	if( InputID == -1){// 開いている配列がなければ
//			return -1;
//	}
//
//	/* フォントのサイズを測る */
//	ech = E3DGetStrSizeByFontID( F_SMALL, Message, &FontSize);
//	_ASSERT( ech != 1 );//エラーチェック
//
//
//	/* 配列に代入する */
//	Bal[InputID].X = X;
//	Bal[InputID].Y = Y;
//	Bal[InputID].MouseX = MouseX;
//	Bal[InputID].MouseY = MouseY;
//	Bal[InputID].MouseMaxX = MouseMaxX;
//	Bal[InputID].MouseMaxY = MouseMaxY;
//	Bal[InputID].Width = FontSize.cx;
//
//	wsprintf( Bal[InputID].String, "%s" , Message);//文字列のコピー
//
//	/* ボタンIDを呼び出した関数へ返す */
//	*BalloonID = InputID;
//
//
//	return 0;
//}
//
//int Menu::PutBalloon_Auto( const int MouseX, const int MouseY){
//
//	for( int i=0; i< 10; i++){
//		if( Bal[i].X != -1){
//			if( ( Bal[i].MouseX < MouseX) && ( MouseX < Bal[i].MouseMaxX) &&
//				( Bal[i].MouseY < MouseY) && ( MouseY < Bal[i].MouseMaxY)){
//					PutString( Bal[i].String, 620 - Bal[i].Width, Bal[i].Y, F_SMALL, WHITE);
//			}
//		}
//	}
//
//	return 0;
//}
//
//int Menu::PutBalloon( const int MouseX, const int MouseY){
//
//	for( int i=0; i< 10; i++){
//		if( Bal[i].X != -1){
//			if( ( Bal[i].MouseX < MouseX) && ( MouseX < Bal[i].MouseMaxX) &&
//				( Bal[i].MouseY < MouseY) && ( MouseY < Bal[i].MouseMaxY)){
//					PutString( Bal[i].String, Bal[i].X, Bal[i].Y, F_SMALL, WHITE);
//			}
//		}
//	}
//
//	return 0;
//}

int Menu::RenderBG(){

	/* 変数の初期化&宣言 */
	E3DCOLOR4UC Alpha = { 255,255,255,255};

	RenderBG_Alpha(Alpha);

	return 0;
}

int Menu::RenderBG_Alpha( const E3DCOLOR4UC Alpha){

	/* 定数の宣言 */
	int ech = 0;//エラーチェック用の変数宣言

	const D3DXVECTOR3 SpritePos1( 0.0, 0.0, 0.0);//背景の位置
	const D3DXVECTOR3 SpritePos2( 0.0, -20.0, 0.0);//十字バーの位置
	const D3DXVECTOR3 SpritePos3( 380.0, 45.0, 0.0);//上部の白いバー

	for( int i=0; i<3; i++){
			ech = E3DSetSpriteARGB( Foundation_BG[i], Alpha);
			_ASSERT( ech != 1 );//エラーチェック
	}


	ech = E3DRenderSprite( Foundation_BG[0], 640.0/1024.0, 480.0/512.0, SpritePos1);//背景の位置
	_ASSERT( ech != 1 );//エラーチェック
					
	ech = E3DRenderSprite( Foundation_BG[1], 1, 1, SpritePos2);//十字バーの位置
	_ASSERT( ech != 1 );//エラーチェック

	ech = E3DRenderSprite( Foundation_BG[2], 1, 1, SpritePos3);//上部の白いバー
	_ASSERT( ech != 1 );//エラーチェック


	return 0;
}

//int Menu::PutString( const char *Message, const int X, const int Y, const int FontID, const int Color){
//
//	/* 変数の初期化&宣言 */
//	POINT TextPos = { X, Y};//文字の位置を格納する構造体
//	char PutMesseage[256] = "";
//
//	wsprintf( PutMesseage, "%s" , Message);//スタミナの表示
//	E3DDrawTextByFontID( System::scid1, Font[FontID], TextPos, PutMesseage, Get_Color(Color) );//説明が書かれている文字列を表示する
//
//
//	return 0;
//}
//
//E3DCOLOR4UC Menu::Get_Color( const int ColorNum){
//
//	 E3DCOLOR4UC Color = { 0, 0, 0, 0};
//
//	 switch( ColorNum){
//			case 0:{// 白
//					Color.a = 255;
//					Color.r = 255;
//					Color.g = 255;
//					Color.b = 255;
//					break;
//			}
//			case 1:{// 黄
//					Color.a = 255;
//					Color.r = 200;
//					Color.g = 220;
//					Color.b = 90;
//					break;
//			}
//			case 2:{// 青
//					Color.a = 255;
//					Color.r = 100;
//					Color.g = 180;
//					Color.b = 240;
//					break;
//			}
//	 }
//
//	 return Color;
// }

Menu::~Menu(){

	/* 変数の初期化&宣言 */
	int ech = 0;// 

	for( int i=0; i<3; i++){
			ech = E3DDestroySprite( Foundation_BG[i]);// 背景の削除
			_ASSERT( ech != 1 );//エラーチェック

	}



	return;
}