//インクルードするファイル↓

#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <usercoef.h>//Easy3Dで必要な追加ヘッダ
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "resource1.h"//リソースファイルとかの関連付けヘッダ
#include <string.h>//文字列操作で必要
#include <stdio.h>//いろいろな関数のヘッダ

/////////////////////////////////////

//ユーザーヘッダファイル

#include "difine.h"


//グローバル変数の宣言

int scid1;
int hsid1;
char pat[MAX_PATH];
RECT recwindow;
HWND hwnd;

//パスを入れる変数


//WndProcを作りますよ
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){

	int hole;

	switch (msg){
		case WM_DESTROY:
				PostQuitMessage(0);
				return 0;

		case 0x020a://マウスホール
				hole = HIWORD(wp)/120;// 上は1、下は545
				return 0;

	}

	return DefWindowProc(hwnd, msg, wp, lp);
}


//メニュー画面の関数です。
int MenuRoops(){

	keyout(0,0);
	int ech;
	static int stalfa = 0;
	static int plamainus = 0;
	static int modeflg = 0;
	

	//メニュー描画
	E3DBeginScene(scid1,0);
	E3DBeginSprite();


	D3DXVECTOR3 ldpos1( 0.0, -27.0, 0.0);
	ech = E3DRenderSprite( opimg, 640.0/1024.0, 480.0/512.0, ldpos1);
	if(ech != 0 ){//エラーチェック
			_ASSERT( 0 );//エラーダイアログ
			return 1;//問題ありで終了

	};



	if(modeflg == 4){

			D3DXVECTOR3 ldpos4( 130.0 + 17.0, 400.0, 0.0);//ロードゲーム
			ech = E3DRenderSprite( lddata[2], 94.0/128.0, 12.0/16.0, ldpos4);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			}

			D3DXVECTOR3 ldpos5( 250.0 + 15.0, 400.0, 0.0);//オペレーション
			ech = E3DRenderSprite( lddata[3], 90.0/128.0, 12.0/16.0, ldpos5);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			}

			D3DXVECTOR3 ldpos6( 370.0 + 35.0, 400.0, 0.0);//オンライン
			ech = E3DRenderSprite( lddata[4], 58.0/64.0, 12.0/16.0, ldpos6);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			}

	}

	if(modeflg == 3){

			D3DXVECTOR3 ldpos5( 130.0 + 15.0, 400.0, 0.0);//オペレーション
			ech = E3DRenderSprite( lddata[3], 90.0/128.0, 12.0/16.0, ldpos5);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			}

			D3DXVECTOR3 ldpos6( 250.0 + 35.0, 400.0, 0.0);//オンライン
			ech = E3DRenderSprite( lddata[4], 58.0/64.0, 12.0/16.0, ldpos6);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			}

			D3DXVECTOR3 ldpos3( 370.0 + 20.0, 400.0, 0.0);//ニューゲーム
			ech = E3DRenderSprite( lddata[1], 87.0/128.0, 12.0/16.0, ldpos3);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			}	

	}

	if(modeflg == 2){

			D3DXVECTOR3 ldpos6( 130.0 + 35.0, 400.0, 0.0);//オンライン
			ech = E3DRenderSprite( lddata[4], 58.0/64.0, 12.0/16.0, ldpos6);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			}

			D3DXVECTOR3 ldpos3( 250.0 + 20.0, 400.0, 0.0);//ニューゲーム
			ech = E3DRenderSprite( lddata[1], 87.0/128.0, 12.0/16.0, ldpos3);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			}

			D3DXVECTOR3 ldpos4( 370.0 + 17.0, 400.0, 0.0);//ロードゲーム
			ech = E3DRenderSprite( lddata[2], 94.0/128.0, 12.0/16.0, ldpos4);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			}
		

	}

	if(modeflg == 1){

			D3DXVECTOR3 ldpos3( 130.0 + 20.0, 400.0, 0.0);//ニューゲーム
			ech = E3DRenderSprite( lddata[1], 87.0/128.0, 12.0/16.0, ldpos3);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			}

			D3DXVECTOR3 ldpos4( 250.0 + 17.0, 400.0, 0.0);//ロードゲーム
			ech = E3DRenderSprite( lddata[2], 94.0/128.0, 12.0/16.0, ldpos4);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			}

			D3DXVECTOR3 ldpos5( 370.0 + 15.0, 400.0, 0.0);//オペレーション
			ech = E3DRenderSprite( lddata[3], 90.0/128.0, 12.0/16.0, ldpos5);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			}
		

	}

	if(modeflg == 0){

			D3DXVECTOR3 ldpos2( 160.0, 400.0, 0.0);
			ech = E3DRenderSprite( lddata[0], 300.0/512.0, 18.0/32.0, ldpos2);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			}
		
			E3DCOLOR4UC col= {stalfa*5,255,255,255};
			E3DSetSpriteARGB(lddata[0], col);
			if(plamainus == 0){
					stalfa++;
					if(stalfa == 51){
							plamainus =1;
					}
			}
			if(plamainus == 1){
					stalfa--;
					if(stalfa == 0){
							plamainus =0;
					}
			}


	}
	

	E3DEndSprite();
	E3DEndScene();
	E3DPresent(scid1);


	if(4 >= modeflg  & modeflg >= 1){

		if(keyin[0] == 1){
					return modeflg + 2;
		}

		if(keyin[4] == 1){
					modeflg--;
		}
		if(keyin[2] == 1){
					modeflg++;
		}


		if(modeflg == 5){
					modeflg = 1;
		}
		if(modeflg == 0){
					modeflg = 4;
		}



	}

	if(0 == modeflg){
		if(keyin[0] == 1){
					modeflg = 1;
		}
	}





	return 0;
}






//宣言:メインループです。
int MainRoops(){
			
	static int flag = 0;
	unsigned long imput = 0;
	int retfps = 0;
	int chk = 0;

	if(flag == 0){//最初のロード画面に飛ばす。
					chk = opning();
					if(chk == 2){//描画終了、フラグ変更
								flag = 1;
					}
	}

	if(flag == 1){//メニュー画面
					chk = MenuRoops();

					if(chk == 6){//オペレーションモード選択なら
								flag = 4;
					}
	}


	if(flag == 4){//メニュー画面
					chk = OpsRoops();
	}
/*
	
	int a = 0;
	int b = 0;
	kabaddi(&a,&b,0,0);


	if(a & 1){
	//char str[100];
	//wsprintf( str, "%d", keyin[4]);
			MessageBox(NULL , "こんにちは" ,"変数コールダイアログ" , MB_ICONINFORMATION);
	}
*/
	
	E3DWaitbyFPS( 30, &retfps);


	return 0;
}




//WinMain関数を作ります、この関数は全てのウィンドウズアプリケーションがここからスタートします。
int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd){

	//初期化
	MSG msg;
	WNDCLASSEX winc;


	//ウィンドウズクラス製作

	winc.cbSize		   = sizeof(WNDCLASSEX);//クラスのサイズ
	winc.style		   = CS_HREDRAW | CS_VREDRAW;//横・縦がサイズ変更があったら再描画
	winc.lpfnWndProc   = WndProc;//どのプロシージャに返すか
	winc.cbClsExtra    = 0;//ウィンドウクラスの補足バイトを指定、たいてい0でOK
	winc.cbWndExtra    = 0;//ウィンドウインスタンスの補足バイトを指定、大抵0でOK
	winc.hInstance     = hInst;//どのインスタンスハンドルを指定
	winc.hIcon         = LoadIcon(NULL,MAKEINTRESOURCE(IDI_ICON1));//アイコンの指定
	winc.hCursor       = LoadCursor(NULL,IDC_ARROW);//カーソルの指定
	winc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);//背景の指定、ここでは白
	winc.lpszMenuName  = NULL;//メニューバーの指定、ここでは使わないからなし
	winc.lpszClassName = "WndCls";//作ったウィンドウクラス名
	winc.hIconSm       = LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1)) ;//小さいアイコンの指定

	//ウィンドウクラス完成！(↓ウィンドウクラスの登録
	if(!RegisterClassEx(&winc)) return 1;//もし、0の戻り値なら終了
	

	//メインウィンドウを作るョ
	hwnd = CreateWindow(
						"WndCls","Religion Ver 0.01d",//どのクラスか、タイトルバーの名前
						WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME,CW_USEDEFAULT,0,640,480,//オーバーラップウィンドウ、場所はY=0でX=任意、大きさは640×480
						NULL,NULL,hInst,NULL//親ウィンドウなし、メニュー使わない、インスタンス、プロシージャからのパラメータのポインタ
	);

	//もし、ウィンドウ作成に失敗したらエラーで終了
	if(hwnd == NULL) return 1;

	ShowWindow(hwnd, nShowCmd);//ウィンドウハンドルの指定、アプリの初期化･･･？
	UpdateWindow(hwnd);//プロシージャにWM_PAINT(再描画)の命令をする。



	///////////////パスの取得開始////////////////

	strcpy( pat, "" );
	char szpath[1024] = "";//実行中のパスを入れる文字列変数
	GetModuleFileName(hInst,szpath,MAX_PATH);//実行中のファイル名を取得
	
	char *p;//ポインタ、後ろから
	char ch = '\\' ;//検索する文字
	int index;//何文字目か

	p = strrchr(szpath,ch);//最後の\がつく文字列を探す。
	index = p - szpath;//最後に\がついたところまで文字数を検索

	strncpy(pat, szpath, index);//path変数にszpath変数から最後の\までの文字を取得


	//////////////パスの取得終わり///////////////



	//Easy3Dの処理を開始するよ。
	int ech = 0;//エラーチェック用の変数宣言
	ech = E3DEnableDbgFile();//デバッグテキスト出力準備
	if(ech != 0){//エラーチェック
					_ASSERT(0);//エラーダイアログを表示
					return 1;//問題ありで関数終了
	};
	ech = E3DInit(hInst,hwnd,0,32,0,1,1,1,&scid1);//Easy3Dの初期化をする。
	if(ech != 0){//エラーチェック
					_ASSERT(0);//エラーダイアログを表示
					return 1;//問題ありで関数終了
	};

	
	/////////以下、一回しかしない処理//////////////////


	ech = loadimg();//ロード画面を表示
	if(ech != 0){//エラーチェック
					_ASSERT(0);//エラーダイアログを表示
					return 1;//問題ありで関数終了
	};
	ech = firstload();//最初にロードしなければならない情報、設定読み込み
	if(ech != 0){//エラーチェック
					_ASSERT(0);//エラーダイアログを表示
					return 1;//問題ありで関数終了
	};



	BOOL GotMes;
	PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE);//メッセージループに処理を返す

	//メッセージループですよ。

	while(WM_QUIT != msg.message){

			GotMes = PeekMessage( &msg, NULL, 0, 0, PM_REMOVE);
			MainRoops();
			DispatchMessage(&msg);

			GetWindowRect( hwnd, &recwindow);
	};

	///////////////////////ここまで////////////////////

	E3DBye();
	return 0;
}


