/*ここでは、初期化・終了・プロージャーに渡すという行為を行うクラスコードファイルです。
//
*/
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ



//コンストラクタ //Easy3Dの処理を開始するよ。//
System::System( HINSTANCE chInst, HWND chwnd, char runpath[256]){


	int ech = 0;//エラーチェック用の変数宣言
	char loadname[256] = "";//ロードするファイル名の文字列配列


	ech = E3DEnableDbgFile();//デバッグテキスト出力準備
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};

	ech = E3DInit( chInst, chwnd, 0, 16, 0, 1, 1, 1, 0, &scid1);//Easy3Dの初期化をする。
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};

	ech = E3DSetProjection( 120.0, 100000.0, 60.0);//プロジェクションの設定を行います
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
	};


	PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE);//メッセージループに処理を返す(おまじない)

	//変数操作

	hInst = chInst;
	hwnd = chwnd;
	strcpy_s( path, runpath);


	/*キー取得命令のためのキー配列その1*/
	keydata1[0][0] = 1<<0; keydata1[0][1] = 0x25;//左キー
	keydata1[1][0] = 1<<1; keydata1[1][1] = 0x26;//上キー
	keydata1[2][0] = 1<<2; keydata1[2][1] = 0x27;//右キー
	keydata1[3][0] = 1<<3; keydata1[3][1] = 0x28;//下キー
	keydata1[4][0] = 1<<4; keydata1[4][1] = 0x20;//スペース
	keydata1[5][0] = 1<<5; keydata1[5][1] = 0x0D;//エンターキー
	keydata1[6][0] = 1<<6; keydata1[6][1] = 0x11;//コントロールキー
	keydata1[7][0] = 1<<7; keydata1[7][1] = 0x01;//左クリック
	keydata1[8][0] = 1<<8; keydata1[8][1] = 0x02;//右クリック
	keydata1[9][0] = 1<<9; keydata1[9][1] = 0x09;//TAB

	keydata1[10][0] = 1<<10; keydata1[10][1] = 0x41;//Aキー
	keydata1[11][0] = 1<<11; keydata1[11][1] = 0x42;//Bキー
	keydata1[12][0] = 1<<12; keydata1[12][1] = 0x43;//Cキー
	keydata1[13][0] = 1<<13; keydata1[13][1] = 0x44;//Dキー
	keydata1[14][0] = 1<<14; keydata1[14][1] = 0x45;//Eキー
	keydata1[15][0] = 1<<15; keydata1[15][1] = 0x46;//Fキー
	keydata1[16][0] = 1<<16; keydata1[16][1] = 0x47;//Gキー
	keydata1[17][0] = 1<<17; keydata1[17][1] = 0x48;//Hキー
	keydata1[18][0] = 1<<18; keydata1[18][1] = 0x49;//Iキー
	keydata1[19][0] = 1<<19; keydata1[19][1] = 0x4A;//Jキー
	keydata1[20][0] = 1<<20; keydata1[20][1] = 0x4B;//Kキー
	keydata1[21][0] = 1<<21; keydata1[21][1] = 0x4C;//Lキー
	keydata1[22][0] = 1<<22; keydata1[22][1] = 0x4D;//Mキー
	keydata1[23][0] = 1<<23; keydata1[23][1] = 0x4E;//Nキー
	keydata1[24][0] = 1<<24; keydata1[24][1] = 0x4F;//Oキー
	keydata1[25][0] = 1<<25; keydata1[25][1] = 0x50;//Pキー
	keydata1[26][0] = 1<<26; keydata1[26][1] = 0x51;//Qキー
	keydata1[27][0] = 1<<27; keydata1[27][1] = 0x52;//Rキー
	keydata1[28][0] = 1<<28; keydata1[28][1] = 0x53;//Sキー
	keydata1[29][0] = 1<<29; keydata1[29][1] = 0x54;//Tキー


	/*キー取得命令のためのキー配列その2*/
	keydata2[0][0] = 1<<0; keydata2[0][1] = 0x55;//Uキー
	keydata2[1][0] = 1<<1; keydata2[1][1] = 0x56;//Vキー
	keydata2[2][0] = 1<<2; keydata2[2][1] = 0x57;//Wキー
	keydata2[3][0] = 1<<3; keydata2[3][1] = 0x58;//Xキー
	keydata2[4][0] = 1<<4; keydata2[4][1] = 0x59;//Yキー
	keydata2[5][0] = 1<<5; keydata2[5][1] = 0x5A;//Zキー

	keydata2[6][0] = 1<<6; keydata2[6][1] = 0x30;//メイン0キー
	keydata2[7][0] = 1<<7; keydata2[7][1] = 0x31;//メイン1キー
	keydata2[8][0] = 1<<8; keydata2[8][1] = 0x32;//メイン2キー
	keydata2[9][0] = 1<<9; keydata2[9][1] = 0x33;//メイン3キー
	keydata2[10][0] = 1<<10; keydata2[10][1] = 0x34;//メイン4キー
	keydata2[11][0] = 1<<11; keydata2[11][1] = 0x35;//メイン5キー
	keydata2[12][0] = 1<<12; keydata2[12][1] = 0x36;//メイン6キー
	keydata2[13][0] = 1<<13; keydata2[13][1] = 0x37;//メイン7キー
	keydata2[14][0] = 1<<14; keydata2[14][1] = 0x38;//メイン8キー
	keydata2[15][0] = 1<<15; keydata2[15][1] = 0x39;//メイン9キー

	keydata2[16][0] = 1<<16; keydata2[16][1] = 0x1B;//ESCキー
	keydata2[17][0] = 1<<17; keydata2[17][1] = 0x04;//マウス真ん中
	keydata2[18][0] = 1<<18; keydata2[18][1] = 0x10;//シフトキー
	keydata2[19][0] = 1<<19; keydata2[19][1] = 0x08;//バックスペース
	keydata2[20][0] = 1<<20; keydata2[20][1] = 0x12;//ALTキー
	keydata2[21][0] = 1<<21; keydata2[21][1] = 0x09;//TABキー

	keydata2[22][0] = 1<<22; keydata2[22][1] = 0x70;//F1
	keydata2[23][0] = 1<<23; keydata2[23][1] = 0x71;//F2
	keydata2[24][0] = 1<<24; keydata2[24][1] = 0x72;//F3
	keydata2[25][0] = 1<<25; keydata2[25][1] = 0x73;//F4
	keydata2[26][0] = 1<<26; keydata2[26][1] = 0x74;//F5
	keydata2[27][0] = 1<<27; keydata2[27][1] = 0x75;//F6
	keydata2[28][0] = 1<<28; keydata2[28][1] = 0x76;//F7
	keydata2[29][0] = 1<<29; keydata2[29][1] = 0x77;//F8

	/*マウスを使うために初期化します*/
	MousePos.x = 0;
	MousePos.y = 0;
	BeforeMousePos.x = 0;//X座標初期化
	BeforeMousePos.y = 0;//Y座標初期化
	KeyQuickEnd = 0;//フラグ変数を初期化する

	/*変数の初期化*/
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			KeyQuickPush[i][j] = 0;
		}
		keyinQuick[i] = 0;
	}


	/*最低限必要な画像のロードを行います*/

	wsprintf( loadname, "%s\\data\\img\\sys\\loading.png", path);//メニュー画面での上部白いバーをロードします。
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteID[0]);
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	}

	
};



//デストラクタ //Easy3Dの終了処理を行うよ。//
System::~System(){

	int ech = 0;//エラーチェック用の変数宣言

	/*画像の破棄を行います*/
	for(int i=0; i<1; i++){
			ech = E3DDestroySprite( SpriteID[i]);
			if(ech != 0){//エラーチェック
						_ASSERT(0);//エラーダイアログを表示
			};
	}

	ech = E3DBye();
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};


};


int System::MsgQ(int fps){

	/*初期化をする*/

	int ech = 0;//エラーチェック用の変数宣言
	int rfps = 0;//いらないFPS計測用の変数。
	MouseWhole = 0;//マウスホイールの移動量を初期化する

	GotMes = PeekMessage( &msg, NULL, 0, 0, PM_REMOVE);
	if( msg.message == WM_QUIT){
				return 0;
	}
	if( GotMes != 0){//メッセージが来たら
				DispatchMessage(&msg);
				TranslateMessage(&msg);
				GetWindowRect( hwnd, &rewin);
	}
	ech = E3DWaitbyFPS( fps, &rfps);
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};




	return 0;//ここの数字で終了処理を決めろ。

};

/*キー情報を更新する関数*/
int System::KeyRenewal( int SelectMode){


	 /*初期化します*/

	for(int i=0; i < 20; i++){	
			keyin[i] = 0;
	}
	int imput1 = 0;
	int imput2 = 0;

	/*　0.トリガーキーか？::1.前回押されたか*/
	int KeyTrigger1 = 0;
	int KeyTrigger2 = 0;

	 /*初期化ここまで*/

	/*
	//選択したモードからトリガー状態で取得するキー変数を代入します
	*/

	if(SelectMode == 0){
			KeyTrigger1 = 0;
			KeyTrigger2 = 0;
	}
	if(SelectMode == 1){
			KeyTrigger1 = (1<<10)+(1<<13)+(1<<28);
			KeyTrigger2 = (1<<2);
	}


	for(int i = 0; i <= 30; i++){
				//初期化
				keyBox1[i][0] = 0;
				keyBox2[i][0] = 0;

				if(KeyTrigger1 & (1<<i)){//もし、トリガーありなら
									keyBox1[i][0] = 1;
				};
				if(KeyTrigger2 & (1<<i)){//もし、トリガーありなら
									keyBox2[i][0] = 1;
				};

				//キー押し判定
				if(GetAsyncKeyState(keydata1[i][1]) & 0x8000){//キーが押されていたら
								imput1 = imput1 + keydata1[i][0];
								if((keyBox1[i][0] == 0) && (keyBox1[i][1] == 1)){
													imput1 = imput1 - keydata1[i][0];		
								}
								keyBox1[i][1] = 1; 
				}
				else{
					keyBox1[i][1] = 0; 
				}


				if(GetAsyncKeyState(keydata2[i][1]) & 0x8000){//キーが押されていたら
								imput2 = imput2 + keydata2[i][0];
								if((keyBox2[i][0] == 0) && (keyBox2[i][1] == 1)){
													imput2 = imput2 - keydata2[i][0];
								}
								keyBox2[i][1] = 1; 
				}
				else{
						keyBox2[i][1] = 0; 
				}
	};



	/*
	//上記で押されたキー情報を元にゲーム本編で使うデータを組み立てます
	*/

	if(SelectMode == 0){//もしメニューでの検出なら
				if(imput1 & 1<<5){//エンター
						keyin[0] = 1;
				}
				if(imput2 & 1<<19){//バックスペース
						keyin[1] = 1;
				}
				if(imput1 & 1<<0){//←
						keyin[2] = 1;
				}
				if(imput1 & 1<<1){//↑
						keyin[3] = 1;
				}
				if(imput1 & 1<<2){//→
						keyin[4] = 1;
				}
				if(imput1 & 1<<3){//↓
						keyin[5] = 1;
				}
		}


	if(SelectMode == 1){//もしゲーム中での検出なら
				if(imput1 & (1<<10)){//Aキー（左へ移動）
					keyin[0] = 1;
				}
				if(imput2 & (1<<2)){//Wキー（前進する）
						keyin[1] = 1;
				}
				if(imput1 & (1<<13)){//Dキー（右へ移動）
						keyin[2] = 1;
				}
				if(imput1 & (1<<28)){//Sキー（後退する）
						keyin[3] = 1;
				}
				if(imput1 & (1<<27)){//Rキー（リロード）
						keyin[4] = 1;
				}
				if(imput1 & (1<<14)){//Eキー（調べる）
						keyin[5] = 1;
				}
				if(imput1 & (1<<10)){//Qキー（セレ切り替え）
						keyin[6] = 1;
				}
				if(imput2 & (1<<5)){//Zキー（装備使用）
						keyin[7] = 1;
				}
				if(imput2 & (1<<18)){//シフトキー（姿勢切り替え）
						keyin[8] = 1;
				}
				if(imput1 & (1<<7)){//左クリック（銃を撃つ）
						keyin[9] = 1;
				}
				if(imput1 & (1<<8)){//右クリック（グレネード）
						keyin[10] = 1;
				}
				if(imput1 & (1<<4)){//スペース（格闘攻撃）
						keyin[11] = 1;
				}
				if(imput1 & (1<<5)){//エンターキー（調べる）
						keyin[12] = 1;
				}
				if(imput2 & (1<<1)){//Vキー（特殊能力）
						keyin[13]=1;
				}
				if(imput2 & (1<<17)){//ホイールクリック（視点変え）
						keyin[14] = 1;
				}
				if(imput2 & (1<<16)){//ESCキー
						keyin[15] = 1;
				}
		}


	/*
	//短いタイミングでキーをおしたかどうかの検出を行います
	*/
		if(SelectMode == 1){//もしゲーム中での検出なら
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
/*ロード画面を描画する関数*/
int System::WaitRender(){

	int ech = 0;//エラーチェック変数
	D3DXVECTOR3 SpritePos1( 0.0, -25.0, 0.0);//背景の位置
	//POINT TextPos;//テキストの座標変数

	/*描画準備を行います*/
	E3DBeginScene( scid1, 1, -1);
	E3DBeginSprite();

	ech = E3DRenderSprite( SpriteID[0], 640.0/1024.0, 480.0/512.0, SpritePos1);//背景
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
	};

	/*ここで、描画完了*/
	E3DEndSprite();

					/*文字"バックパック"の描画を行います*/
					//TextPos.x = 440;/**/TextPos.y = 5;
					//E3DDrawTextByFontID( sys->scid1, TextID[0], TextPos, "バックパック", NormalColor1);

	E3DEndScene();
	E3DPresent(scid1);



	return 0;
}

/*キー情報を入手するための関数*/
int System::GetKeyData( int *KeyDataArray){

	//キーが押されたかの情報を格納します
	for( int i=0; i<20; i++){
		*(KeyDataArray + i) = keyin[i];
	}


	return 0;
}