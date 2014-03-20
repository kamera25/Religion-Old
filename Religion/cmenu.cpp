/*ここでは、ゲーム中のメニューに関することのクラスです。
//主にポーズメニュークラスとドッグメニュークラスについて書かれています。
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "c_optionmenu.h"// オプションメニューに関することを宣言しているヘッダファイル
#include "cmenu.h"//メニュークラスに関するヘッダファイル
#include "clive.h"//敵やキャラの宣言ヘッダファイル
#include "cweapon.h"//武器に関することのクラスヘッダファイル
#include "c_batch_preparat.h"//描画に必要なクラスの宣言ヘッダファイル
#include "citem_manipulate.h"//アイテム操作に関するヘッダファイル



/*コンストラクタ、メニューで使う画像のロード*/
Menu::Menu(){

	/*変数の宣言*/
	int ech = 0;//エラーチェック変数
	char loadname[256] = "";//ロードするファイル名の文字列配列


	/*スプライトをロードします*/
	wsprintf( loadname, "%s\\data\\img\\menu\\menubg.png", System::path);//メニュー画面での背景をロードします。
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[0]);
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};

	wsprintf( loadname, "%s\\data\\img\\menu\\menuber.png", System::path);//メニュー画面での十字バーをロードします。
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[1]);
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};

	wsprintf( loadname, "%s\\data\\img\\menu\\menu_up_ber.png", System::path);//メニュー画面での上部白いバーをロードします。
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[2]);
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};



	/*メニューで使う文字IDを設定します。*/
	ech = E3DCreateFont( 35, 0, 800, 0, 0, 0, "MS Pゴシック", &TextID[0]);//大文字
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
	};

	ech = E3DCreateFont( 25, 0, 800, 0, 0, 0, "MS Pゴシック", &TextID[1]);//小文字
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
	};


}

/*デコントラクタ、メニューで使ったものの削除を行います。*/
Menu::~Menu(){

	/*変数の宣言*/
	int ech = 0;//エラーチェック変数
	

	/*スプライトを削除します*/
	ech = E3DDestroySprite( MenuSpriteIDs[0]);//メニュー画面での背景を削除します。
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};

	ech = E3DDestroySprite( MenuSpriteIDs[1]);//メニュー画面での十字バーを削除します。
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};

	ech = E3DDestroySprite( MenuSpriteIDs[2]);//メニュー画面での上部白いバーを削除します。
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};


	/*文字IDを削除します*/
	ech = E3DDestroyFont( TextID[0]);//大文字
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};

	ech = E3DDestroyFont( TextID[1]);//小文字
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};


}


/*ポーズメニュー、コアの部分です。*/
int Menu::PoseMenu( PlayerChara *PC, Batch_Preparat *BatchPre ){

	/*変数の宣言*/
	int ech = 0;//エラーチェック変数
	int ExitFlag = 0;//このフラグがオンになったとき脱出します。
	int keyin[20];//キー情報配列を作成
	const int DetailPossitionX[5] = { 400, 250, 400, 250, 230};// 詳細文字のX座標
	/* メニューネームの登録を行ないます。 */
	const char MenuKindName[5][32] = {  "ゲームに戻る" , "バックパック" , "オプション" ,
										"ミッションを中断する", "ゲームを終了する" };
	/* 各メニューの詳しい説明 */
	const char MenuKindDetail[5][80] = {
			"ゲーム本編に戻ります",
			"持ち物の確認やアイテムの使用などが出来ます",
			"ゲーム内の設定が出来ます",
			"ミッションを中断して、作戦前の状態に戻ります",
			"ゲームを終了します、データの保存は行われません"
	};
	const D3DXVECTOR3 SpritePos1( 0.0, -25.0, 0.0);//背景の位置
	const D3DXVECTOR3 SpritePos2( 0.0, -60.0, 0.0);//十字バーの位置
	const D3DXVECTOR3 SpritePos3( 380.0, 45.0, 0.0);//上部の白いバー
	const E3DCOLOR4UC NormalColor = { 255,255,255,255};//白色の選ばれていない色
	const E3DCOLOR4UC SelectColor = { 255,200,220,20};//黄色の選ばれている色
	POINT TextPos;//文字の位置を格納する構造体
	POINT TextPosDetail;//詳細の文字を表示する座標を格納する構造体

	do{
			/*変数の宣言*/
			int SelectKind = -1;// 選択しているアイテムを識別する変数

			System::MsgQ(30);//メッセージループ

			System::KeyRenewal(1);
			
			System::GetKeyData(keyin);//キーを取得する

			/*描画準備をスルヨ*/
			E3DBeginScene( System::scid1, 0, -1);//描画の開始準備

			/*
			//スプライトを描きますよ。
			*/
			E3DBeginSprite();//スプライト描画の開始
					
			ech = E3DRenderSprite( MenuSpriteIDs[0], 640.0/1024.0, 480.0/512.0, SpritePos1);//背景の位置
			if(ech != 0 ){//エラーチェック
						_ASSERT( 0 );//エラーダイアログ
			};
					
			ech = E3DRenderSprite( MenuSpriteIDs[1], 1, 1, SpritePos2);//十字バーの位置
			if(ech != 0 ){//エラーチェック
						_ASSERT( 0 );//エラーダイアログ
			};

			ech = E3DRenderSprite( MenuSpriteIDs[2], 1, 1, SpritePos3);//上部の白いバー
			if(ech != 0 ){//エラーチェック
						_ASSERT( 0 );//エラーダイアログ
			};

			E3DEndSprite();//スプライト描画の終了
			/*
			//スプライトの描画はここまで。
			//　次に文字の描画を行います。
			*/



			/* ///////////////////// */
			// 文字の表示を行ないます
			/* ///////////////////// */

			//一番上のポーズメニュー
			TextPos.x = 440;/**/TextPos.y = 5;
			E3DDrawTextByFontID( System::scid1, TextID[0], TextPos, "ポーズメニュー", NormalColor);

			//以下、メニューネーム(通常時・選択時)を表示
			TextPos.x = 100;/**/TextPos.y = 140;//40ずつ下げる
			for( int i=0; i<5;i++){
					
					/* 通常文字を表示*/
					E3DDrawTextByFontID( System::scid1, TextID[1], TextPos, MenuKindName[i], NormalColor);
					if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
							return 1;//問題ありで終了
					};

					/* 選択されている文字を表示 */
					if(( (100< System::MousePos.x) && (System::MousePos.x<250) ) &&// X座標
						( (TextPos.y + 20)< System::MousePos.y)&&( System::MousePos.y < (TextPos.y + 50))){// Y座標

							/* 選択されている色の文字を表示 */
							E3DDrawTextByFontID( System::scid1, TextID[1], TextPos, MenuKindName[i], SelectColor);
							if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
									return 1;//問題ありで終了
							}

							/* 選択されている文字の詳細情報を表示します */
							TextPosDetail.x = DetailPossitionX[i];/**/TextPosDetail.y = 330;
							E3DDrawTextByFontID( System::scid1, TextID[1], TextPosDetail, MenuKindDetail[i], NormalColor);//説明が書かれている文字列を表示する
							if(ech != 0){//エラーチェック
										_ASSERT(0);//エラーダイアログを表示
							};

							SelectKind = i;// マウスが乗ってる名前番号を代入
					}

					TextPos.y = TextPos.y + 40;
			}

			/* ////////////////////////////////// */
			/* クリックされた時の動作を設定します 
			/* ////////////////////////////////// */

			if( keyin[9] == 1){
					switch(SelectKind){
							case 0:{// ゲームに戻る
									ExitFlag = 1;//ループ脱出フラグをオンにする。
									break;
							}
							case 1:{// バックパック
									Item_Manipulate BackPack( PC);//バックパックを実体化させます
									BackPack.InItemPack( PC);//バックパックに入ります
									break;
							}
							case 2:{// オプション
									OptionMenu OptMenu;// オプションメニューを実体化させます
									OptMenu.MainOptionMenu( BatchPre);// オプションメニューに入ります
									break;
							}
							case 3:{// ミッションを中断する

									break;
							}
							case 4:{// ゲームを終了する
									SendMessage( System::hwnd, WM_CLOSE, 0, 0);
									break;
							}
					}
			}

			PutStetus(PC);//ステータスを表示するクラス


			/* //////////////////////////
			// ここまでで画面描画準備終了
			// ////////////////////////*/
			E3DEndScene();
			ech = E3DPresent( System::scid1);
			if(ech != 0){//エラーチェック
						_ASSERT(0);//エラーダイアログを表示
			};
			

			if( ExitFlag == 1 ){//もしゲームループを抜けてOKなら
						break;//ループを抜ける
			}

	}while(WM_QUIT != System::msg.message);
	




	return 0;
}
/*メニュー画面に入って、自動的に通常描画モードからメニュー画面に半透過していきます。*/
int Menu::FarstInMenu( Batch_Preparat *BatchPre, PlayerChara *PC){

	/*変数の宣言*/
	int keyin[20];//キー情報配列を作成

	System::GetKeyData(keyin);//キーを取得する

	/*もしESCキーが押されていたら*/
	if(keyin[15] == 1){

			/*まずはじめに、通常画面→メニュー画面にしていきます。*/
			for(int i = 0; i<17; i++){

					/*変数の初期化*/
					int ech = 0;//エラーチェック変数
					E3DCOLOR4UC AlfaColor = { 15*i ,255,255,255};
					D3DXVECTOR3 SpritePos1( 0.0, -25.0, 0.0);//背景の位置
					D3DXVECTOR3 SpritePos2( 0.0, -60.0, 0.0);//十字バーの位置
					D3DXVECTOR3 SpritePos3( 380.0, 45.0, 0.0);//上部の白いバー

					/*通常画面のレンダリング*/
					BatchPre->BatchChkInView();//視野角内チェック
					BatchPre->BatchRender( 0);//レンダリング

					/*テクスチャにアルファを適応する*/
					for(int i = 0; i<3; i++){
							ech = E3DSetSpriteARGB( MenuSpriteIDs[i], AlfaColor);
							if(ech != 0 ){//エラーチェック
										_ASSERT( 0 );//エラーダイアログ
							};
					}

					/*描画準備を行います*/
					E3DBeginScene( System::scid1, 1, -1);;
					E3DBeginSprite();


					ech = E3DRenderSprite( MenuSpriteIDs[0], 640.0/1024.0, 480.0/512.0, SpritePos1);//背景の位置
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
					};
			
					ech = E3DRenderSprite( MenuSpriteIDs[1], 1, 1, SpritePos2);//十字バーの位置
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
					};

					ech = E3DRenderSprite( MenuSpriteIDs[2], 1, 1, SpritePos3);//上部の白いバー
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
					};

					/*ここで、描画完了*/
					E3DEndSprite();
					E3DEndScene();
					E3DPresent(System::scid1);

			
			}/*ここまで*/


			PoseMenu( PC, BatchPre);//ポーズメニューに入る


			/*終了時のループに入ります。*/
			for(int i = 0; i<17; i++){

					/*変数の初期化*/
					int ech = 0;//エラーチェック変数
					E3DCOLOR4UC AlfaColor = { 255-(15*i) ,255,255,255};
					D3DXVECTOR3 SpritePos1( 0.0, -25.0, 0.0);//背景の位置
					D3DXVECTOR3 SpritePos2( 0.0, -60.0, 0.0);//十字バーの位置
					D3DXVECTOR3 SpritePos3( 380.0, 45.0, 0.0);//上部の白いバー

					/*通常画面のレンダリング*/
					BatchPre->BatchChkInView();//視野角内チェック
					BatchPre->BatchRender( 0);//レンダリング

					/*テクスチャにアルファを適応する*/
					for(int i = 0; i<3; i++){
							ech = E3DSetSpriteARGB( MenuSpriteIDs[i], AlfaColor);
							if(ech != 0 ){//エラーチェック
										_ASSERT( 0 );//エラーダイアログ
							};
					}

					/*描画準備を行います*/
					E3DBeginScene( System::scid1, 1, -1);;
					E3DBeginSprite();


					ech = E3DRenderSprite( MenuSpriteIDs[0], 640.0/1024.0, 480.0/512.0, SpritePos1);//背景の位置
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
					};
			
					ech = E3DRenderSprite( MenuSpriteIDs[1], 1, 1, SpritePos2);//十字バーの位置
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
					};

					ech = E3DRenderSprite( MenuSpriteIDs[2], 1, 1, SpritePos3);//上部の白いバー
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
					};

					/*ここで、描画完了*/
					E3DEndSprite();
					E3DEndScene();
					E3DPresent(System::scid1);

			
			}/*ここまで*/



	}


	return 0;
}
/*ステータス表示を行うものをまとめた関数です。*/
int Menu::PutStetus( PlayerChara *PC){

	//変数の初期化
	int ech = 0;//エラーチェック変数
	POINT TextPos;//文字の位置を格納する構造体
	char StatusName[128] = "";//ステータス表示で使う画面文字列
	E3DCOLOR4UC NormalColor = { 255,255,255,255};//白色の選ばれていない色
	E3DCOLOR4UC SelectColor = { 255,200,220,20};//黄色の選ばれている色

	/*プレイヤーキャラクターのステータス表示*/
	TextPos.x = 80;
	TextPos.y = 370;
	wsprintf( StatusName, "HP 1000/1000" );//HPの表示
	E3DDrawTextByFontID( System::scid1, TextID[1], TextPos, StatusName, NormalColor);//説明が書かれている文字列を表示する
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};
	TextPos.x = 80;
	TextPos.y = 390;
	wsprintf( StatusName, "STAMINA 100/100" );//スタミナの表示
	E3DDrawTextByFontID( System::scid1, TextID[1], TextPos, StatusName, NormalColor);//説明が書かれている文字列を表示する
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};
	TextPos.x = 80;
	TextPos.y = 430;
	wsprintf( StatusName, "MAINWEAPON AMM:10/10 MAG:10/10" );//メインウェポンのMAG数、AMM数
	E3DDrawTextByFontID( System::scid1, TextID[1], TextPos, StatusName, NormalColor);//説明が書かれている文字列を表示する
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};







	return 0;
}