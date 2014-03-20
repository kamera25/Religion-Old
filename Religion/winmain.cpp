/*ここでは、アプリケーションの基礎を作成しWinMainを作成し次へ関数を渡す作業をします。
//
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include <cstring>//文字列操作で使うヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ


//ここにある関数を宣言。
int GMStart();//ゲームメインループの宣言


//ウィンドウズプロージャー
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){

	int Whole = 0;//ホイールの移動量を格納する変数

	switch (msg){
		case WM_MOUSEWHEEL://マウスホール
				Whole = HIWORD(wp)/120;// 上は1、下は545
				if( Whole == 1) System::MouseWhole = 1;
				if( Whole == 545) System::MouseWhole = 2;

				break;

		case WM_DESTROY:
				PostQuitMessage(0);

				break;




	};

	return DefWindowProc(hwnd, msg, wp, lp);
};



//WinMain関数作成
int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd){

	//初期化
	WNDCLASSEX winc;
	HWND hwnd;

	//_CrtSetDbgFlag(_CRTDBG_CHECK_ALWAYS_DF | _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//ウィンドウズクラス製作

	winc.cbSize		   = sizeof(WNDCLASSEX);//クラスのサイズ
	winc.style		   = CS_HREDRAW | CS_VREDRAW;//横・縦がサイズ変更があったら再描画
	winc.lpfnWndProc   = WndProc;//どのプロシージャに返すか
	winc.cbClsExtra    = 0;//ウィンドウクラスの補足バイトを指定、たいてい0でOK
	winc.cbWndExtra    = 0;//ウィンドウインスタンスの補足バイトを指定、大抵0でOK
	winc.hInstance     = hInst;//どのインスタンスハンドルを指定
	winc.hIcon         = LoadIcon( hInst, "KIRIN");//アイコンの指定
	winc.hCursor       = LoadCursor(NULL,IDC_ARROW);//カーソルの指定
	winc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);//背景の指定、ここでは白
	winc.lpszMenuName  = NULL;//メニューバーの指定、ここでは使わないからなし
	winc.lpszClassName = "WndCls";//作ったウィンドウクラス名
	winc.hIconSm       = LoadIcon( hInst, "KIRIN");//アイコンの指定

	//ウィンドウクラス完成！(↓ウィンドウクラスの登録
	if(!RegisterClassEx(&winc)) return 1;//もし、0の戻り値なら終了
	


	//メインウィンドウを作るョ
	hwnd = CreateWindow(
						"WndCls","Religion Gram_Ver 0.02",//どのクラスか、タイトルバーの名前
						WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME,CW_USEDEFAULT,0,640,480,//オーバーラップウィンドウ、場所はY=0でX=任意、大きさは640×480
						NULL,NULL,hInst,NULL//親ウィンドウなし、メニュー使わない、インスタンス、プロシージャからのパラメータのポインタ
	);

	/* 640×480のWindowサイズにする */

	RECT rcc;// クライアントの幅
	RECT rcw;// ウィンドウの幅
	LONG WindSX;
	LONG WindSY;

	GetWindowRect( hwnd, &rcw);
	GetClientRect( hwnd, &rcc);
	WindSX = 640 + ((rcw.right - rcw.left) - (rcc.right - rcc.left));
    WindSY = 480 + ((rcw.bottom - rcw.top) - (rcc.bottom - rcc.top));
	SetWindowPos( hwnd, NULL, 0, 0, WindSX, WindSY, (SWP_NOZORDER|SWP_NOOWNERZORDER|SWP_NOMOVE) );




	//もし、ウィンドウ作成に失敗したらエラーで終了
	if(hwnd == NULL) return 1;

	ShowWindow(hwnd, nShowCmd);//ウィンドウハンドルの指定、アプリの初期化･･･？
	UpdateWindow(hwnd);//プロシージャにWM_PAINT(再描画)の命令をする。

	//WinAPIによるウィンドウ作成終了
	//以下より、クラス・SystemによりE3D環境を作成

	{
		System system( hInst, hwnd);//E3D環境作成

		GMStart();//ゲームをスタートします。ようこそ、Religionへ。


	};

	return 0;
};