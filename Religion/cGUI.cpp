/* ////////////////////////////////////////////////////////////////////////// */
// cGUIクラスソースファイルです。
// cGUIクラスを継承することで、GUIのパーツを簡単に組み込めるサブセットを利用できます。
/* ////////////////////////////////////////////////////////////////////////// */
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "cGUI.h"// GUIのサブセットを使います

/* 静動変数 */
int cGUI::Font[3];


// 初期化関数
int cGUI::Initialize()
{
	int ech;

	/* メニューで使う文字IDを設定します。*/
	ech = E3DCreateFont( 35, 0, 800, 0, 0, 0, "MS Pゴシック", &Font[0]);//大文字
	_ASSERT( ech != 1 );//エラーチェック

	ech = E3DCreateFont( 30, 0, 800, 0, 0, 0, "MS Pゴシック", &Font[1]);//中文字
	_ASSERT( ech != 1 );//エラーチェック

	ech = E3DCreateFont( 25, 0, 800, 0, 0, 0, "MS Pゴシック", &Font[2]);//小文字
	_ASSERT( ech != 1 );//エラーチェック



	return 0;
}

cGUI::cGUI()
{
	/* 初期化 */
	/* 変数の初期化&宣言 */
	int ech = 0;// 初期化
	char loadname[256] = "";//ロードするファイル名の文字列配列

	/* メンバ変数の初期化 */
	SpriteSum = 0;
	for( int i=0; i<10; i++){
			Btn[i].X = -1;
			Bal[i].X = -1;
	}

	for( int i=0; i < 20; i++)
	{
		SpriteID[i] = -1;
	}


}

int cGUI::LoadImg( const char *FilePath, int *ID){

	/* 変数の初期化&宣言 */
	int ech = 0;// 
	int IDNum = 0;//  
	char loadname[256] = "";


	if( SpriteSum == 10){		
			return -1;
	}

	/* 空の配列を検索して、 */
	for( int i=0; i<20; i++){
			if( SpriteID[i] == -1){
					IDNum = i;
					break;
			}
	}

	wsprintf( loadname, "%s\\%s",  System::path, FilePath);//メニュー画面での上部白いバーをロードします。
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteID[IDNum]);
	_ASSERT( ech != 1 );//エラーチェック


	/* 代入されたIDをSpriteIDに返します */
	*ID = IDNum;

	return 0;
}

int cGUI::MakeFontButton( const char *Message, int *ButtonID, const int X, const int Y, const int MaxX, const int MaxY){

	/* 変数の初期化&宣言 */
	int ech = 0;// 初期化
	int InputID = -1;
	
	for( int i=0; i<10; i++){
			if( Btn[i].X == -1){// 開いてる変数があれば
					InputID = i;
					break;
			}
	}
	if( InputID == -1){// 開いている配列がなければ
			return -1;
	}

	/* 配列に代入する */
	Btn[InputID].X = X;
	Btn[InputID].Y = Y;
	Btn[InputID].MaxX = MaxX;
	Btn[InputID].MaxY = MaxY;

	wsprintf( Btn[InputID].String, "%s" , Message);//文字列のコピー

	/* ボタンIDを呼び出した関数へ返す */
	*ButtonID = InputID;
	



	return 0;
}

int cGUI::MakeFontButton_Auto( const char *Message, int *ButtonID, const int X, const int Y){


	MakeFontButton( Message, ButtonID, X, Y, X + 150, Y + 50);

	return 0;
}

int cGUI::ChkFontButtonWithColor( const int MouseX, const int MouseY, const int NonSelectedColor, const int SelectedColor)
{
	/* 定数の宣言 */
	int SelectedButton = -1;


	for( int i=0; i<10; i++){


			if( Btn[i].X == -1) continue;//存在しないボタンが選択されたら
			
			/* カーソルがボタンの範囲内にあれば */
			if( ( ( Btn[i].X < MouseX) && (MouseX < Btn[i].MaxX)) // X座標
				&& ( Btn[i].Y + 20  < MouseY) && ( MouseY < Btn[i].MaxY)){

					/* 選択されている色の文字を表示 */
					PutString( Btn[i].String, Btn[i].X, Btn[i].Y, F_SMALL, SelectedColor);
					SelectedButton = i;
			}
			else{
					PutString( Btn[i].String, Btn[i].X, Btn[i].Y, F_SMALL, NonSelectedColor);
					
			}
	}


	return SelectedButton;


}

/* 文字ボタンを描画、チェックする関数 */
int cGUI::ChkFontButton( const int MouseX, const int MouseY)
{

	return ChkFontButtonWithColor( MouseX, MouseY, WHITE, BLUE);
}

int cGUI::MakeBalloonFromButton( const char *Message, int *BalloonID, int *ButtonID, const int X, const int Y){

	MakeBalloon( Message, BalloonID, X, Y, Btn[*ButtonID].X, Btn[*ButtonID].Y + 20, Btn[*ButtonID].MaxX, Btn[*ButtonID].MaxY);

	return 0;
}

int cGUI::MakeBalloon( const char *Message, int *BalloonID, const int X, const int Y , const int MouseX, const int MouseY, const int MouseMaxX, const int MouseMaxY){

	/* 変数の初期化&宣言 */
	int ech = 0;// 初期化
	int InputID = -1;
	SIZE FontSize;

	for( int i=0; i<10; i++){
			if( Bal[i].X == -1){// 開いてる変数があれば
					InputID = i;
					break;
			}
	}
	if( InputID == -1){// 開いている配列がなければ
			return -1;
	}

	/* フォントのサイズを測る */
	ech = E3DGetStrSizeByFontID( Font[F_SMALL], Message, &FontSize);
	_ASSERT( ech != 1 );//エラーチェック


	/* 配列に代入する */
	Bal[InputID].X = X;
	Bal[InputID].Y = Y;
	Bal[InputID].MouseX = MouseX;
	Bal[InputID].MouseY = MouseY;
	Bal[InputID].MouseMaxX = MouseMaxX;
	Bal[InputID].MouseMaxY = MouseMaxY;
	Bal[InputID].Width = FontSize.cx;

	wsprintf( Bal[InputID].String, "%s" , Message);//文字列のコピー

	/* ボタンIDを呼び出した関数へ返す */
	*BalloonID = InputID;


	return 0;
}

int cGUI::PutBalloon_Auto( const int MouseX, const int MouseY){

	for( int i=0; i< 10; i++){
		if( Bal[i].X != -1){
			if( ( Bal[i].MouseX < MouseX) && ( MouseX < Bal[i].MouseMaxX) &&
				( Bal[i].MouseY < MouseY) && ( MouseY < Bal[i].MouseMaxY)){
					PutString( Bal[i].String, 620 - Bal[i].Width, Bal[i].Y, Font[F_SMALL], WHITE);
			}
		}
	}

	return 0;
}

int cGUI::PutBalloon( const int MouseX, const int MouseY){

	for( int i=0; i< 10; i++){
		if( Bal[i].X != -1){
			if( ( Bal[i].MouseX < MouseX) && ( MouseX < Bal[i].MouseMaxX) &&
				( Bal[i].MouseY < MouseY) && ( MouseY < Bal[i].MouseMaxY)){
					PutString( Bal[i].String, Bal[i].X, Bal[i].Y, Font[F_SMALL], WHITE);
			}
		}
	}

	return 0;
}



int cGUI::PutString( const char *Message, const int X, const int Y, const int FontID, const int Color)
{

	/* 変数の初期化&宣言 */
	POINT TextPos = { X, Y};//文字の位置を格納する構造体

	E3DDrawTextByFontID( System::scid1, Font[FontID], TextPos, Message, Get_Color(Color) );//説明が書かれている文字列を表示する


	return 0;
}

E3DCOLOR4UC cGUI::Get_Color( const int ColorNum){

	 E3DCOLOR4UC Color = { 0, 0, 0, 0};

	 switch( ColorNum){
			case WHITE:{// 白
					Color.a = 255;
					Color.r = 255;
					Color.g = 255;
					Color.b = 255;
					break;
			}
			case YELOW:{// 黄
					Color.a = 255;
					Color.r = 200;
					Color.g = 220;
					Color.b = 90;
					break;
			}
			case BLUE:{// 青
					Color.a = 255;
					Color.r = 100;
					Color.g = 180;
					Color.b = 240;
					break;
			}
			case BLACK:{// 黒
					Color.a = 255;
					Color.r = 0;
					Color.g = 0;
					Color.b = 0;
					break;
			}
			case GRAY:{// グレー
					Color.a = 255;
					Color.r = 130;
					Color.g = 130;
					Color.b = 130;
					break;
			}
	 }

	 return Color;
 }

cGUI::~cGUI()
{
	/* 変数の初期化&宣言 */
	int ech = 0;// 

		
	for( int i=0; i<20; i++){
			if( SpriteID[i] != -1){
					DestorySprite(i);
			}
	}

	return;
}

int cGUI::DestorySprite( const int SpID)
{
	/* 初期化 */
	int ech = 0;

	ech = E3DDestroySprite( SpriteID[SpID]);
	_ASSERT( ech != 1 );//エラーチェック

	return 0;
}

/* ファイナライズ関数 */
int cGUI::Finalize()
{
	/* 変数の初期化&宣言 */
	int ech = 0;// 

	for( int i=0; i<3; i++){

			ech = E3DDestroyFont( Font[i]);// 文字の削除
			_ASSERT( ech != 1 );//エラーチェック
	}

	return 0;
}

/* 描画のための準備をする */
int cGUI::StartBeginScene()
{
	/* 初期化 */
	int ech;
	
	ech = E3DBeginScene( System::scid1, 0, -1);
	_ASSERT( ech != 1 );//エラーダイアログを表示

	ech = E3DBeginSprite();
	_ASSERT( ech != 1 );//エラーダイアログを表示


	return 0;
}

/* 描画のための準備をする */
int cGUI::EndScene()
{
	/* 初期化 */
	int ech;
	
	ech = E3DEndScene();
	_ASSERT( ech != 1 );//エラーチェック

	ech = E3DPresent( System::scid1);
	_ASSERT( ech != 1 );//エラーダイアログを表示


	return 0;
}

/* スプライトの描画を終了する */
int cGUI::EndSprite()
{
	/* 初期化 */
	int ech;

	ech = E3DEndSprite();
	_ASSERT( ech != 1 );//エラーダイアログを表示

	return 0;
}

/* スプライトを描画する */
int cGUI::PutSprite( const int ID, const int X, const int Y, const double MagX, const double MagY)
{
	/* 初期化 */
	int ech;
	
	/* スプライトの描画 */
	D3DXVECTOR3 MesBarPos( X, Y, 0);//描画位置を指定する構造体
	ech = E3DRenderSprite( SpriteID[ID], MagX, MagY, MesBarPos);
	_ASSERT( ech != 1 );//エラーダイアログを表示


	return 0;
}