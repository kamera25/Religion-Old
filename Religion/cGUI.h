#pragma once
/* ////////////////////////////////////////////////////////////////////////// */
// cGUIクラスヘッダファイルです。
// cGUIクラスを継承することで、GUIのパーツを簡単に組み込めるサブセットを利用できます。
/* ////////////////////////////////////////////////////////////////////////// */
#include <vector>

struct Button{
	char String[80];// ボタンの文字を格納する変数
	int X;
	int Y;
	int MaxX;
	int MaxY;
};

struct Balloon{
	char String[150];// バルーンの文字を格納する変数
	int X;
	int Y;
	int MouseX;
	int MouseY;
	int MouseMaxX;
	int MouseMaxY;
	int Width;
};

class cGUI{

private:

	static int Font[3];// 一般的に使うフォント
	int SpriteID[20];// ユーザー定義スプライトIDを格納する
	int SpriteSum;// ユーザー定義スプライトの合計数を格納する変数
	
	Button Btn[10];
	Balloon Bal[10];

	/* メンバ関数 */


public:
	static int Initialize();// 初期化関数
	static int Finalize();// ファイナライズ関数(すべてが終わりし時、その関数を呼び出せ)

	/* 静動変数:色 */
	static const int WHITE = 0;// 白
	static const int YELOW = 1;// 黄
	static const int BLUE = 2;// 青
	static const int BLACK = 3;// 黒
	static const int GRAY = 4;// 灰色

	/* 静動変数:文字サイズ */
	static const int F_BIG = 0;// 大文字
	static const int F_STANDARD = 1;// 標準
	static const int F_SMALL = 2;// 小文字

	cGUI();// 実際にGUIを使い始める前に呼び出す、コンストラクタ
	virtual ~cGUI();
	int LoadImg( const char *FilePath, int *SpriteID);// 画像を読み込む関数
	int PutString( const char *Message, const int X, const int Y, const int FontID, const int Color);// 文字を出力する関数
	int MakeFontButton( const char *Message, int *ButtonID, const int X, const int Y, const int MaxX, const int MaxY);// 文字ボタンを作成する関数
	int MakeFontButton_Auto( const char *Message, int *ButtonID, const int X, const int Y);
	int MakeBalloon( const char *Message, int *ButtonID, const int X, const int Y , const int MouseX, const int MouseY, const int MouseMaxX, const int MouseMaxY);
	int MakeBalloonFromButton( const char *Message, int *BalloonID, int *ButtonID, const int X, const int Y);
	int PutBalloon_Auto( const int MouseX, const int MouseY);
	int PutBalloon( const int MouseX, const int MouseY);
	int ChkFontButton( const int MouseX, const int MouseY);// 文字ボタンを描画、チェックする関数
	int ChkFontButtonWithColor( const int MouseX, const int MouseY, const int NonSelectedColor, const int SelectedColor);// ボタンの色を指定して、チェックする関数
	int StartBeginScene();
	int EndSprite();
	int EndScene();
	int DestorySprite( const int SpID);
	int PutSprite( const int ID, const int X, const int Y, const double MagX, const double MagY);
	E3DCOLOR4UC Get_Color( int ColorNum);
};