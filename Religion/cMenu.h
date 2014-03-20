#pragma once
/* ////////////////////////////////////////////////////////////////////////// */
// cMenu2クラスヘッダファイルです。
// cMenu2クラスを継承することで、メニュー部分の共通システムを簡潔に組み込めます。
/* ////////////////////////////////////////////////////////////////////////// */

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


class Menu{

private:
	int Font[3];// Menuクラスが初期から用意する、文字の識別を格納するID配列
	int Foundation_BG[3];// Menuクラスが初期から用意する、通常の背景画像

	int SpriteID[10];// ユーザー定義スプライトIDを格納する変数
	int SpriteSum;// ユーザー定義スプライトの合計数を格納する変数

	Button Btn[10];
	Balloon Bal[10];

	/* メンバ関数 */

	E3DCOLOR4UC Get_Color( int ColorNum);

public:

	/* 静動変数:色 */
	static const int WHITE = 0;// 白
	static const int YELOW = 1;// 黄
	static const int BLUE = 2;// 青

	/* 静動変数:文字サイズ */
	static const int F_BIG = 0;// 大文字
	static const int F_STANDARD = 1;// 標準
	static const int F_SMALL = 2;// 小文字


	Menu();// コンストラクタ、
	~Menu();// デスコントラクタ
	int LoadImg( const char *FilePath, int *SpriteID);// 画像を読み込む関数
	int PutString( const char *Message, const int X, const int Y, const int FontID, const int Color);// 文字を出力する関数
	int MakeFontButton( const char *Message, int *ButtonID, const int X, const int Y, const int MaxX, const int MaxY);// 文字ボタンを作成する関数
	int MakeFontButton_Auto( const char *Message, int *ButtonID, const int X, const int Y);
	int MakeBalloon( const char *Message, int *ButtonID, const int X, const int Y , const int MouseX, const int MouseY, const int MouseMaxX, const int MouseMaxY);
	int MakeBalloonFromButton( const char *Message, int *BalloonID, int *ButtonID, const int X, const int Y);
	int PutBalloon_Auto( const int MouseX, const int MouseY);
	int PutBalloon( const int MouseX, const int MouseY);
	int ChkFontButton( const int MouseX, const int MouseY);// 文字ボタンを描画、チェックする関数
	int RenderBG();
	int RenderBG_Alpha( const E3DCOLOR4UC Alpha);//透過つきの背景描画


};