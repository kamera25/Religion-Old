/*ここでは、ゲーム中のメニューに関することのクラスです。
//主にポーズメニュークラスとドッグメニュークラスについて書かれています。
*/
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include "cstage.h"//ステージ関係のクラスヘッダファイル
#include "clive.h"//敵やキャラの宣言ヘッダファイル
#include "c_batch_preparat.h"//描画に必要なクラスの宣言ヘッダファイル
#include "cmenu.h"//メニュークラスに関するヘッダファイル
#include "citem_manipulate.h"//アイテム操作に関するヘッダファイル
#include "cweapon.h"//武器に関することのクラスヘッダファイル

//ここにグローバル変数を宣言
extern System *sys;//システムクラスを指す、クラスのポインタ


/*コンストラクタ、メニューで使う画像のロード*/
Menu::Menu(){

	/*変数の宣言*/
	int ech = 0;//エラーチェック変数
	char loadname[256] = "";//ロードするファイル名の文字列配列


	/*スプライトをロードします*/
	wsprintf( loadname, "%s\\data\\img\\menu\\menubg.png", sys->path);//メニュー画面での背景をロードします。
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[0]);
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};

	wsprintf( loadname, "%s\\data\\img\\menu\\menuber.png", sys->path);//メニュー画面での十字バーをロードします。
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[1]);
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};

	wsprintf( loadname, "%s\\data\\img\\menu\\menu_up_ber.png", sys->path);//メニュー画面での上部白いバーをロードします。
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
int Menu::PoseMenu( PlayerChara *PC, Weapon *Wep){

	/*変数の宣言*/
	int ech = 0;//エラーチェック変数
	int ExitFlag = 0;//このフラグがオンになったとき脱出します。
	int keyin[20];//キー情報配列を作成
	D3DXVECTOR3 SpritePos1( 0.0, -25.0, 0.0);//背景の位置
	D3DXVECTOR3 SpritePos2( 0.0, -60.0, 0.0);//十字バーの位置
	D3DXVECTOR3 SpritePos3( 380.0, 45.0, 0.0);//上部の白いバー
	E3DCOLOR4UC NormalColor = { 255,255,255,255};//白色の選ばれていない色
	E3DCOLOR4UC SelectColor = { 255,200,220,20};//黄色の選ばれている色
	POINT TextPos;//文字の位置を格納する構造体


	do{

			sys->MsgQ(30);//メッセージループ

			sys->KeyRenewal(1);
			
			sys->GetKeyData(keyin);//キーを取得する

			/*描画準備をスルヨ*/
			E3DBeginScene( sys->scid1, 0, -1);//描画の開始準備

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

					//一番上のポーズメニュー
					TextPos.x = 440;/**/TextPos.y = 5;
					E3DDrawTextByFontID( sys->scid1, TextID[0], TextPos, "ポーズメニュー", NormalColor);

					//以下、通常文字を表示
					TextPos.x = 100;
					TextPos.y = 140;//40ずつ下げる
					E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "ゲームに戻る", NormalColor);
					if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
							return 1;//問題ありで終了
					};

					TextPos.y = 180;//40ずつ下げる
					E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "バックパック", NormalColor);
					if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
							return 1;//問題ありで終了
					};

					TextPos.y = 220;//40ずつ下げる
					E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "オプション", NormalColor);
					if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
							return 1;//問題ありで終了
					};

					TextPos.y = 260;//40ずつ下げる
					E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "ミッションを中断する", NormalColor);
					if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
							return 1;//問題ありで終了
					};

					TextPos.y = 300;//40ずつ下げる
					E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "ゲームを終了する", NormalColor);
					if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
							return 1;//問題ありで終了
					};
			




			/*マウスが選択部にあるとき、文字を変更します*/
			if((100< sys->MousePos.x)&&(sys->MousePos.x<250)){	
					if((160< sys->MousePos.y)&&( sys->MousePos.y<190)){//マウス座標が「ゲームに戻る」の上なら
							TextPos.x = 100;
							TextPos.y = 140;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "ゲームに戻る", SelectColor);//選択されている文字にする
							if(ech != 0){//エラーチェック
										_ASSERT(0);//エラーダイアログを表示
							};
							TextPos.x = 400;
							TextPos.y = 330;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "ゲーム本編に戻ります", NormalColor);//説明が書かれている文字列を表示する
							if(ech != 0){//エラーチェック
										_ASSERT(0);//エラーダイアログを表示
							};
							if(keyin[9] == 1){//クリックしたら
										ExitFlag = 1;//ループ脱出フラグをオンにする。
							}
					}	

					if((200< sys->MousePos.y)&&( sys->MousePos.y<230)){//マウス座標が「バックパック」の上なら
							TextPos.x = 100;
							TextPos.y = 180;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "バックパック", SelectColor);//選択されている文字にする
							if(ech != 0){//エラーチェック
										_ASSERT(0);//エラーダイアログを表示
							};
							TextPos.x = 250;
							TextPos.y = 330;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "持ち物の確認やアイテムの使用などが出来ます", NormalColor);//説明が書かれている文字列を表示する
							if(ech != 0){//エラーチェック
										_ASSERT(0);//エラーダイアログを表示
							};
							if(keyin[9] == 1){//クリックしたら
										Item_Manipulate BackPack( PC, Wep);//バックパックを呼び出します。
										BackPack.InItemPack( PC);//バックパックに入ります
							}
					}

					if((240< sys->MousePos.y)&&( sys->MousePos.y<270)){//マウス座標が「オプション」の上なら
							TextPos.x = 100;
							TextPos.y = 220;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "オプション", SelectColor);//選択されている文字にする
							if(ech != 0){//エラーチェック
										_ASSERT(0);//エラーダイアログを表示
							};
							TextPos.x = 400;
							TextPos.y = 330;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "ゲーム内の設定が出来ます", NormalColor);//説明が書かれている文字列を表示する
							if(ech != 0){//エラーチェック
										_ASSERT(0);//エラーダイアログを表示
							};
					}

					if((280< sys->MousePos.y)&&( sys->MousePos.y<310)){//マウス座標が「ゲームに戻る」の上なら
							TextPos.x = 100;
							TextPos.y = 260;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "ミッションを中断する", SelectColor);//選択されている文字にする
							if(ech != 0){//エラーチェック
										_ASSERT(0);//エラーダイアログを表示
							};
							TextPos.x = 250;
							TextPos.y = 330;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "ミッションを中断して、作戦前の状態に戻ります", NormalColor);//説明が書かれている文字列を表示する
							if(ech != 0){//エラーチェック
										_ASSERT(0);//エラーダイアログを表示
							};
					}

					if((320< sys->MousePos.y)&&( sys->MousePos.y<350)){//マウス座標が「ゲームに戻る」の上なら
							TextPos.x = 100;
							TextPos.y = 300;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "ゲームを終了する", SelectColor);//選択されている文字にする
							if(ech != 0){//エラーチェック
										_ASSERT(0);//エラーダイアログを表示
							};
							TextPos.x = 230;
							TextPos.y = 330;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "ゲームを終了します、データの保存は行われません", NormalColor);//説明が書かれている文字列を表示する
							if(ech != 0){//エラーチェック
										_ASSERT(0);//エラーダイアログを表示
							};
							if(keyin[9] == 1){//クリックしたら
										SendMessage( sys->hwnd, WM_CLOSE, 0, 0);
							}
					}
			}


			PutStetus(PC);//ステータスを表示するクラス


			/*ここまでで画面描画準備終了*/
			E3DEndScene();
			ech = E3DPresent( sys->scid1);
			if(ech != 0){//エラーチェック
						_ASSERT(0);//エラーダイアログを表示
			};
			

			if( ExitFlag == 1 ){//もしゲームループを抜けてOKなら
						break;//ループを抜ける
			}

	}while(WM_QUIT != sys->msg.message);
	




	return 0;
}
/*メニュー画面に入って、自動的に通常描画モードからメニュー画面に半透過していきます。*/
int Menu::FarstInMenu( Batch_Preparat *BatchPre, PlayerChara *PC, Weapon *Wep){

	/*変数の宣言*/
	int keyin[20];//キー情報配列を作成

	sys->GetKeyData(keyin);//キーを取得する

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
					E3DBeginScene( sys->scid1, 1, -1);;
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
					E3DPresent(sys->scid1);

			
			}/*ここまで*/


			PoseMenu( PC, Wep);//ポーズメニューに入る


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
					E3DBeginScene( sys->scid1, 1, -1);;
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
					E3DPresent(sys->scid1);

			
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
	E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, StatusName, NormalColor);//説明が書かれている文字列を表示する
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};
	TextPos.x = 80;
	TextPos.y = 390;
	wsprintf( StatusName, "STAMINA 100/100" );//スタミナの表示
	E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, StatusName, NormalColor);//説明が書かれている文字列を表示する
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};
	TextPos.x = 80;
	TextPos.y = 430;
	wsprintf( StatusName, "MAINWEAPON AMM:10/10 MAG:10/10" );//メインウェポンのMAG数、AMM数
	E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, StatusName, NormalColor);//説明が書かれている文字列を表示する
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};







	return 0;
}