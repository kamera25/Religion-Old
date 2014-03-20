/*ここでは、ゲーム中のメニューに関することのクラスです。
//主にポーズメニュークラスとドッグメニュークラスについて書かれています。
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "c_optionmenu.h"// オプションメニューに関することを宣言しているヘッダファイル
#include "cPoseMenu.h"//メニュークラスに関するヘッダファイル
#include "clive.h"//敵やキャラの宣言ヘッダファイル
#include "cweapon.h"//武器に関することのクラスヘッダファイル
#include "c_batch_preparat.h"//描画に必要なクラスの宣言ヘッダファイル
#include "citem_manipulate.h"//アイテム操作に関するヘッダファイル



/*コンストラクタ、メニューで使う画像のロード*/
PoseMenu::PoseMenu(){

	/* 変数の宣言&初期化 */
	int ButtonID = 0;
	int Garbage = 0;
	/* メニューネームの登録を行ないます。 */
	const char MenuKindName[5][32] = {  "ゲームに戻る" , "バックパック" , "オプション" ,
										"ミッションを中断する", "ゲームを終了する" };
	const char MenuKindDetail[5][80] = {
			"ゲーム本編に戻ります",
			"持ち物の確認やアイテムの使用などが出来ます",
			"ゲーム内の設定が出来ます",
			"ミッションを中断して、作戦前の状態に戻ります",
			"ゲームを終了します、データの保存は行われません"
	};

	for( int i=0; i<5; i++){

			MakeFontButton_Auto(  MenuKindName[i], &ButtonID, 100, 140 + 40 * i);
			MakeBalloonFromButton( MenuKindDetail[i], &Garbage, &ButtonID, 300, 330);
	}

	return;
}

/*デコントラクタ、メニューで使ったものの削除を行います。*/
PoseMenu::~PoseMenu(){

	return;
}


/*ポーズメニュー、コアの部分です。*/
int PoseMenu::MainPoseMenu( PlayerChara *PC, Batch_Render *BatchPre ){

	/*変数の宣言*/
	int ech = 0;//エラーチェック変数
	int ExitFlag = 0;//このフラグがオンになったとき脱出します。
	const int DetailPossitionX[5] = { 400, 250, 400, 250, 230};// 詳細文字のX座標
	/* 各メニューの詳しい説明 */


	do{
			/*変数の宣言*/
			int SelectKind = -1;// 選択しているアイテムを識別する変数

			System::MsgQ(30);//メッセージループ

			System::KeyRenewal(1);
			

			/*描画準備をスルヨ*/
			E3DBeginScene( System::scid1, 0, -1);//描画の開始準備

			/*
			//スプライトを描きますよ。
			*/
			E3DBeginSprite();//スプライト描画の開始
					
			RenderBG();//背景の描画

			E3DEndSprite();//スプライト描画の終了
			/*
			//スプライトの描画はここまで。
			//　次に文字の描画を行います。
			*/


			/* ///////////////////// */
			// 文字の表示を行ないます
			/* ///////////////////// */

			//一番上のポーズメニュー
			PutString( "ポーズメニュー", 440, 5, F_BIG, WHITE);

			// バルーンの表示を行います
			PutBalloon_Auto( System::MousePos.x, System::MousePos.y);

			//以下、メニューネーム(通常時・選択時)を表示
			SelectKind = ChkFontButton( System::MousePos.x, System::MousePos.y);


			/* ////////////////////////////////// */
			/* クリックされた時の動作を設定します 
			/* ////////////////////////////////// */

			if( System::GetKeyData( System::KEY_LEFTMOUSE)){
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
			_ASSERT( ech != 1 );//エラーチェック
			

			if( ExitFlag == 1 ){//もしゲームループを抜けてOKなら
						break;//ループを抜ける
			}

	}while(WM_QUIT != System::msg.message);
	




	return 0;
}
/*メニュー画面に入って、自動的に通常描画モードからメニュー画面に半透過していきます。*/
int PoseMenu::FarstInMenu( Batch_Render *BatchPre, PlayerChara *PC){

	/*変数の宣言*/
	int ech = 0;//エラーチェック変数


	/*もしESCキーが押されていなかったら*/
	if( System::GetKeyData( System::KEY_ESC) != 1){
			
			return 1;//ポーズメニューを起動しない
	}

	/* 視野角内チェック */
	BatchPre->BatchChkInView();

	/*まずはじめに、通常画面→メニュー画面にしていきます。*/
	for(int i = 0; i<17; i++){

			/*変数の初期化*/

			E3DCOLOR4UC AlfaColor = { 15*i ,255,255,255};

			/*通常画面のレンダリング*/
			BatchPre->BatchRender( 0);//レンダリング

			/*描画準備を行います*/
			E3DBeginScene( System::scid1, 1, -1);;
			E3DBeginSprite();

			RenderBG_Alpha(AlfaColor);

			/*ここで、描画完了*/
			E3DEndSprite();
			E3DEndScene();
			E3DPresent(System::scid1);

			
	}/*ここまで*/

	MainPoseMenu( PC, BatchPre);//ポーズメニューに入る


	/*終了時のループに入ります。*/
	for(int i = 0; i<17; i++){

			/*変数の初期化*/
			E3DCOLOR4UC AlfaColor = { 255-(15*i) ,255,255,255};

			/*通常画面のレンダリング*/
			BatchPre->BatchRender( 0);//レンダリング

			/*描画準備を行います*/
			E3DBeginScene( System::scid1, 1, -1);;
			E3DBeginSprite();

			RenderBG_Alpha(AlfaColor);

			/*ここで、描画完了*/
			E3DEndSprite();
			E3DEndScene();
			E3DPresent(System::scid1);

			
	}/*ここまで*/





	return 0;
}
/*ステータス表示を行うものをまとめた関数です。*/
int PoseMenu::PutStetus( PlayerChara *PC){

	//変数の初期化

	/*プレイヤーキャラクターのステータス表示*/
	PutString( "HP 1000/1000", 80, 370, F_SMALL, WHITE);

	PutString( "STAMINA 100/100", 80, 390, F_SMALL, WHITE);

	PutString( "MAINWEAPON AMM:10/10 MAG:10/10", 80, 410, F_SMALL, WHITE);


	return 0;
}