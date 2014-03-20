/*ここでは、初期化・終了・プロージャーに渡すという行為を行うクラスコードファイルです。
//
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "cWeapon_head.h"// 武器統括に関することのクラスヘッダファイル

/*静動変数の宣言*/
//
int System::UpdataSoundflag;//音声情報を更新するかのフラグ
int System::keyin[20];//キーが押されているかの情報配列
int System::scid2;// フェードアウトで使うスワップチェイン

BOOL System::GotMes;//PeekMessageの状態を格納する。

int System::scid1;//メインスワップチェインのID
int System::keyinQuick[3];//キーが2押されたか格納する配列変数
int System::KeyQuickEnd;//ダッシュ操作が終了したときすべてのプッシュをリセットするフラグ変数
int System::MouseWhole;//マウスホイールの移動量を格納する変数
int System::KeyQuickPush[3][3];//キーを2回連打したときの情報を入れる変数
int System::SpriteID[2];//ロードしたスプライトを格納します

char System::path[256];//プログラムが起動しているパスの文字列

MSG System::msg;//メッセージを格納する構造体。
HWND System::hwnd;//ハンドルウィンドウを格納する。
RECT System::rewin;//4隅座標の構造体
POINT System::MousePos;//マウスの位置を格納するPoint構造体
POINT System::BeforeMousePos;//前回のマウスの位置を格納する構造体


// コンストラクタ:Easy3Dの処理を開始するよ。
System::System( const HINSTANCE chInst, const HWND chwnd){

	/*変数の*/
	int ech = 0;//エラーチェック用の変数宣言
	int index = 0;//何文字目か
	char loadname[256] = "";//ロードするファイル名の文字列配列
	char *p;//ポインタ、後ろから
	char ch = '\\' ;//検索する文字
	char szpath[256] = "";//実行中のパスを入れる文字列変数

	//パスの取得

	GetModuleFileName( chInst, szpath, 256);//実行中のファイル名を取得
	
	p = strrchr(szpath,ch);//最後の\がつく文字列を探す。
	index = p - szpath;//最後に\がついたところまで文字数を検索

	strncpy_s(path, szpath, index);//path変数にszpath変数から最後の\までの文字を取得
	/* ******* */


	ech = E3DEnableDbgFile();//デバッグテキスト出力準備
	_ASSERT( ech != 1 );//エラーチェック


	ech = E3DInit( chInst, chwnd, 0, 16, 0, 1, 1, 1, 0, &scid1);//Easy3Dの初期化をする。
	_ASSERT( ech != 1 );//エラーチェック

	ech = E3DSetProjection( 120.0, 100000.0, 60.0);//プロジェクションの設定を行います
	_ASSERT( ech != 1 );//エラーチェック

	PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE);//メッセージループに処理を返す(おまじない)

	//変数操作

	hInst = chInst;
	hwnd = chwnd;

	/*キー取得命令のためのキー配列その1*/




	/*キー取得命令のためのキー配列その2*/


	/*マウスを使うために初期化します*/
	MousePos.x = 0;
	MousePos.y = 0;
	BeforeMousePos.x = 0;//X座標初期化
	BeforeMousePos.y = 0;//Y座標初期化
	KeyQuickEnd = 0;//フラグ変数を初期化する
	UpdataSoundflag = 0;//音声情報を更新しない（デフォルト）

	/*変数の初期化*/
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			KeyQuickPush[i][j] = 0;
		}
		keyinQuick[i] = 0;
	}



	/* **************
	// スワップチェインを作成する
	// **************
	*/

	ech = E3DCreateSwapChain( chwnd, &scid2);
	
			_ASSERT( ech != 1 );//エラーチェック


	/* **************
	// 最低限必要な画像のロードを行います
	// **************
	*/

	// メニュー画面での上部白いバーをロードします。
	wsprintf( loadname, "%s\\data\\img\\sys\\loading.png", path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteID[0]);
	
			_ASSERT( ech != 1 );//エラーチェック

	// 画面全体を暗くするための、黒画像
	wsprintf( loadname, "%s\\data\\img\\oth\\black.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteID[1]);
	_ASSERT( ech != 1 );//エラーチェック

	
};
// デストラクタ:Easy3Dの終了処理を行うよ。
System::~System(){

	/* 変数の初期化 */
	int ech = 0;//エラーチェック用の変数宣言

	/* 画像の破棄を行います */
	for(int i=0; i<2; i++){
			ech = E3DDestroySprite( SpriteID[i]);
			_ASSERT( ech != 1 );//エラーチェック
	}

	/* スワップチェインを削除 */
	ech = E3DDestroySwapChain(scid2);
	_ASSERT( ech != 1 );//エラーチェック

	/* Easy3D終了処理 */
	ech = E3DBye();
	_ASSERT( ech != 1 );//エラーチェック


};
/* メッセージのループ処理 */
int System::MsgQ( const int fps){

	/*初期化をする*/

	int ech = 0;//エラーチェック用の変数宣言
	int rfps = 0;//いらないFPS計測用の変数。
	MouseWhole = 0;//マウスホイールの移動量を初期化する

	/* メッセージループの処理 */
	do{
			GotMes = PeekMessage( &msg, NULL, 0, 0, PM_REMOVE);
			if( msg.message == WM_QUIT){
						return 0;
			}
			if( GotMes != 0){//メッセージが来たら
						DispatchMessage(&msg);
						TranslateMessage(&msg);
						GetWindowRect( hwnd, &rewin);
			}

	}while( GotMes != NULL );// メッセージが来ていなかったら、ループを抜ける


	ech = E3DWaitbyFPS( fps, &rfps);
	_ASSERT( ech != 1 );//エラーチェック

	/**/
	//音声情報を更新するor無視
	/**/
	if( UpdataSoundflag != 0){

		/*リスナーの位置(カメラ位置)を設定*/
		ech = E3DSet3DSoundListenerMovement( -1);
		_ASSERT( ech != 1 );//エラーチェック
		/*音情報の更新を行います*/
		ech = E3DUpdateSound();
		_ASSERT( ech != 1 );//エラーチェック
	}


	return 0;//ここの数字で終了処理を決めろ。

};
/* キー情報を更新する関数 */
int System::KeyRenewal( const int SelectMode){


	/* 初期化 & 宣言を行います*/
	static int KeyBox[30][2][2];// 動的に取得したキー情報を入れる配列
	int imput[2] = { 0 , 0 };
	const int KeyTrigger[3][2] = // トリガーとなるキー番号をそれぞれの状況で指定したconst変数
	{
		{ 0 , 0 },									// メニュー中
		{ (1<<10)+(1<<13)+(1<<28)+(1<<8) , (1<<2) },		// ゲーム中,連続不可
		{ (1<<7)+(1<<10)+(1<<13)+(1<<28)+(1<<8) , (1<<2) }	// ゲーム中,連続可
	};
	const int KeyData[2][30] = {// キーの番号を格納した変数
		{
			0x25,//左キー 0
			0x26,//上キー 1
			0x27,//右キー 2
			0x28,//下キー 3
			0x20,//スペース 4
			0x0D,//エンターキー 5
			0x11,//コントロールキー 6
			0x01,//左クリック 7
			0x02,//右クリック 8
			0x09,//TAB 9

			0x41,//Aキー 10
			0x42,//Bキー 11
			0x43,//Cキー 12 
			0x44,//Dキー 13 
			0x45,//Eキー 14
			0x46,//Fキー 15
			0x47,//Gキー 16
			0x48,//Hキー 17
			0x49,//Iキー 18
			0x4A,//Jキー 19

			0x4B,//Kキー 20
			0x4C,//Lキー 21
			0x4D,//Mキー 22
			0x4E,//Nキー 23
			0x4F,//Oキー 24
			0x50,//Pキー 25
			0x51,//Qキー 26
			0x52,//Rキー 27
			0x53,//Sキー 28
			0x54,//Tキー 29
		},
		{
			0x55,//Uキー 0
			0x56,//Vキー 1
			0x57,//Wキー 2
			0x58,//Xキー 3
			0x59,//Yキー 4
			0x5A,//Zキー 5

			0x30,//メイン0キー 6
			0x31,//メイン1キー 7
			0x32,//メイン2キー 8
			0x33,//メイン3キー 9
			0x34,//メイン4キー 10
			0x35,//メイン5キー 11 
			0x36,//メイン6キー 12
			0x37,//メイン7キー 13
			0x38,//メイン8キー 14
			0x39,//メイン9キー 15

			0x1B,//ESCキー 16
			0x04,//マウス真ん中 17 
			0x10,//シフトキー 18
			0x08,//バックスペース 19
			0x12,//ALTキー 20
			0x09,//TABキー 21

			0x70,//F1 22
			0x71,//F2 23
			0x72,//F3 24
			0x73,//F4 25
			0x74,//F5 26
			0x75,//F6 27
			0x76,//F7 28
			0x77,//F8 39
		}
	};
	const int ModeKeyCheck[3][2][20] = 
	{
		{// もしメニューでの検出なら
			{ 0, 1, 0, 0, 0, 0, -1},
			{ 1<<5, 1<<19, 1<<0, 1<<1, 1<<2, 1<<3, -1}
		},
		{// もしゲーム中での検出なら(連続不可)
			{ 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, -1},
			{ 1<<10, 1<<2, 1<<13,1<<28, 1<<27, 1<<14, 1<<10, 1<<5, 1<<18, 1<<7,
				1<<8, 1<<4, 1<<5, 1<<1, 1<<17, 1<<16, 1<<15, -1},
		},
		{// もしゲーム中での検出なら(連続化) 
			{ 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, -1},
			{ 1<<10, 1<<2, 1<<13,1<<28, 1<<27, 1<<14, 1<<10, 1<<5, 1<<18, 1<<7,
				1<<8, 1<<4, 1<<5, 1<<1, 1<<17, 1<<16, 1<<15, -1},
		}
	};

	
	/* 初期化します */ 
	for(int i=0; i < 20; i++){	
			keyin[i] = 0;
	}
	for( int i=0; i < 30; i++ ){
		for( int j=0; j < 2; j++ ){
			KeyBox[i][0][j] = 0;
		}
	}

	/* 初期化 & 宣言はここまで */

	for(int i=0; i < 30; i++){

		/* 変数の初期化 */
		const int NowBitShiftNum = 1<<i;

		for( int j=0; j<2; j++){
			if(KeyTrigger[SelectMode][j] & (1<<i)){
					KeyBox[i][0][j] = 1;
			};

			/* キー押し判定 */
			if(GetAsyncKeyState( KeyData[j][i] ) & 0x8000){//キーが押されていたら
							imput[j] = imput[j] + NowBitShiftNum ;
							if( (KeyBox[i][0][j] == 0) && (KeyBox[i][1][j] == 1) ){
									imput[j] = imput[j] - NowBitShiftNum ;		
							}
							KeyBox[i][1][j] = 1; 
			}
			else{
				KeyBox[i][1][j] = 0; 
			}
		}
	}



	/*
	//上記で押されたキー情報を元にゲーム本編で使うデータを組み立てます
	*/
	for( int i=0; i<20; i++){
			const int NowImputNo = ModeKeyCheck[SelectMode][0][i];
			const int NowBitShiftNum = ModeKeyCheck[SelectMode][1][i];

			if( NowImputNo == -1) break;// ModeKeyCheck変数が最後なら、ループ脱出
			if( imput[NowImputNo] & NowBitShiftNum){// キーが押されているかチェックします
						keyin[i] = 1;
			}
	}
	
	/* ////////// */
	// !! メモ !!
	/* ////////// */

	/* もしメニューでの検出なら [SelectMode == 1] */
	//エンター 0
	//バックスペース 1
	//← 2
	//↑ 3
	//→ 4
	//↓ 5

	/* もしゲーム中での検出なら( 連続不可 / 連続化 ) [SelectMode == 1 OR 2] */
	//Aキー（左へ移動）0
	//Wキー（前進する）1
	//Dキー（右へ移動）2
	//Sキー（後退する）3
	//Rキー（リロード）4
	//Eキー（肩撃ち位置変え） 5
	//Qキー（セレ切り替え） 6
	//Zキー（装備使用） 7
	//シフトキー（姿勢切り替え）8
	//左クリック（銃を撃つ） 9
	//右クリック（グレネード） 10
	//スペース（格闘攻撃） 11
	//エンターキー（調べる） 12
	//Vキー（特殊能力） 13
	//ホイールクリック（視点変え）14
	//ESCキー 15
	//Fキー 16


	/*
	//短いタイミングでキーをおしたかどうかの検出を行います
	*/
	if(( SelectMode == 1) || ( SelectMode == 2)){//もしゲーム中での検出なら
			for(int i=0; i<3; i++){//A・W・Dキーで3回繰り返す
					if( (keyin[i] == 0) && (KeyQuickPush[i][0] == 1) ){//キーが押されてなく、前回は押されていたとき
							KeyQuickPush[i][1] = 5;//7ループ後までカウントする
					}
					if( KeyQuickPush[i][1] > 0){//7ループ内で
							KeyQuickPush[i][1] = KeyQuickPush[i][1] - 1;//ループ容赦回数を減らす
							if( keyin[i] == 1){//その中でキーが押されているなら
									KeyQuickPush[i][2] = 1;//ダッシュフラグをオンにする
							}
					}
					if( KeyQuickPush[i][2] == 1){//ダッシュフラグがオンなら
							keyinQuick[i] = 1;//ゲームダッシュフラグをオンにする
							if( keyin[i] == 0){//もし、「ダッシュフラグがオンになっているキーが押されてない」なら
									KeyQuickPush[i][2] = 0;//ダッシュキーが押されてない状態にする
									keyinQuick[i] = 0;//ゲームダッシュフラグをオフにする
							}
					}
					KeyQuickPush[i][0] = keyin[i];//前回のキーを代入します(次ループで使用)
			}
	}

	/*
	//次にマウス座標を取得します。
	*/

	GetCursorPos( &MousePos);//マウス座標を格納します
	MousePos.x = MousePos.x - rewin.left;//ウィンドウX座標の取得
	MousePos.y = MousePos.y - rewin.top;//ウィンドウY座標の取得


	return 0;
}
/* ロード画面を描画する関数 */
int System::WaitRender(){

	int ech = 0;//エラーチェック変数
	D3DXVECTOR3 SpritePos1( 0.0, -25.0, 0.0);//背景の位置
	//POINT TextPos;//テキストの座標変数

	/*描画準備を行います*/
	E3DBeginScene( scid1, 1, -1);
	E3DBeginSprite();

	ech = E3DRenderSprite( SpriteID[0], 640.0/1024.0, 480.0/512.0, SpritePos1);//背景
	_ASSERT( ech != 1 );//エラーチェック

	/*ここで、描画完了*/
	E3DEndSprite();

					/*文字"バックパック"の描画を行います*/
					//TextPos.x = 440;/**/TextPos.y = 5;
					//E3DDrawTextByFontID( System::scid1, TextID[0], TextPos, "バックパック", NormalColor1);

	E3DEndScene();
	E3DPresent(scid1);



	return 0;
}
/* キー情報を入手するための関数 */
int System::GetKeyData( int *KeyDataArray){

	//キーが押されたかの情報を格納します
	for( int i=0; i<20; i++){
		*(KeyDataArray + i) = keyin[i];
	}


	return 0;
}
/* 音声情報を更新するかどうかの関数 */
int System::SetUpdataSoundSys( const int Soundflag){

	UpdataSoundflag = Soundflag;

	return 0;
}
/* 画像をフェードアウトさせる処理の関数 */
int System::SetFadeOutOfScid( const int FadeTime){

	/*変数の初期化*/
	int ech = 0;
	D3DXVECTOR3 MainSpritePos( 0.0, -28.0, 0.0);// 背景の位置
	E3DCOLOR4UC BlackColor = { 0,255,255,255};// 黒背景の色構造体

	/* **********
	// 直前までレンダリングしていた画面をスワップチェイン(scid2)にコピー
	// **********
	*/
	ech = E3DBeginScene( scid2, 1, -1);
	
	_ASSERT( ech != 1 );//エラーチェック
	ech = E3DEndScene();
	
	_ASSERT( ech != 1 );//エラーチェック

	/* 処理終了 */


	/* 繰り返しの処理(ブラックフェードアウトする)*/
	for( int i=0; i<FadeTime; i++){

			MsgQ(30);//メッセージループ

			
			/* 透明度を更新(iカウンタで変位) */
			BlackColor.a = i * (255 / FadeTime);

			/*黒画像の透明度を指定する*/
			ech = E3DSetSpriteARGB( SpriteID[1], BlackColor);
			
			_ASSERT( ech != 1 );//エラーチェック

			/* 透明度を更新(iカウンタで変位) */
			BlackColor.a = i * (255 / FadeTime);

			/*黒画像の透明度を指定する*/
			ech = E3DSetSpriteARGB( SpriteID[1], BlackColor);
			
			_ASSERT( ech != 1 );//エラーチェック

		
			/* **********
			// 元画面(scid2)を先にレンダリングします
			// **********
			*/

			ech = E3DBeginScene( scid2, 0, -1);
			
			_ASSERT( ech != 1 );//エラーチェック
			ech = E3DEndScene();
			
			_ASSERT( ech != 1 );//エラーチェック

			/* 処理終了 */


			/* **********
			// scid2の上に黒画像(scid1による)をレンダリングします
			// **********
			*/

			ech = E3DBeginScene( scid1, 1, -1);
			
			_ASSERT( ech != 1 );//エラーチェック
			ech = E3DBeginSprite();//スプライト描画の開始
			
			_ASSERT( ech != 1 );//エラーチェック
			
			/* **************************************** */
			/* スプライト(透過付き黒画像)をレンダリング */
			/* **************************************** */

			ech = E3DRenderSprite( SpriteID[1], 1.0f, 1.0f, MainSpritePos);//黒背景
			_ASSERT( ech != 1 );//エラーチェック
			ech = E3DEndSprite();//スプライト描画の終了
			
			_ASSERT( ech != 1 );//エラーチェック

			/* 処理終了 */

			ech = E3DEndScene();
			
			_ASSERT( ech != 1 );//エラーチェック
			ech = E3DPresent( System::scid1);
			
			_ASSERT( ech != 1 );//エラーチェック

	}





	return 0;
}
/* 銃クラスを元にキー情報の取得を変更する関数 */
int System::KeyRenewalFromWp( const Weapon_Head *Wpn, const int Equipment){
	
	if( ( Equipment == -1) || ( Equipment == 2)){// 装備なしかサポート武器なら
			System::KeyRenewal(1);
	}
	else{
		if( Wpn->Get_WeaponPointer(Equipment)->Get_NowAmmo() != 0){
				System::KeyRenewal( Wpn->Get_WeaponPointer(Equipment)->Get_RapidFire() + 1);
		}
		else{
				System::KeyRenewal(1);
		}

	}


	return 0;
}
/* マウス座標をセットする関数 */
int System::SetMouseCursol( const int X, const int Y){

	SetCursorPos( System::rewin.left + X, System::rewin.top + Y);

	return 0;
}
/* 現在のマウス座標をBeforeMousePosにセットする関数 */
int System::SetMouseBeforePos(){

	/* 変数の初期化 */
	POINT BeforeMousePoseAddRewin;

	GetCursorPos( &BeforeMousePoseAddRewin);
	System::BeforeMousePos.x = BeforeMousePoseAddRewin.x - System::rewin.left;
	System::BeforeMousePos.y = BeforeMousePoseAddRewin.y - System::rewin.top;


	return 0;
}