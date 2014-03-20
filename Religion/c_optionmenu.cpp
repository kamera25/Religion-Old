/*ここでは、オプションメニューに関することのクラスソースファイルです。
//
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "c_optionmenu.h"// オプションメニューに関することを宣言しているヘッダファイル
#include "c_batch_preparat.h"//描画に必要なクラスの宣言ヘッダファイル

/* コンストラクタ、メニューで使う画像のロード */
OptionMenu::OptionMenu(){

	int Garbage = 0;

	MakeFontButton_Auto(  "オプションを閉じる", &Garbage, 100, 320);
	MakeBalloon( "影のレンダリング処理(Quality,ON/OFF)", &Garbage, 300, 330, 100, 80, 320, 180);
	MakeBalloon( "マップがデコボコぽく見える処理(ON/OFF)", &Garbage, 295, 330, 100, 200, 320, 300);


	return;
}

/* オプションメニューの中央処理を行ないます */
int OptionMenu::MainOptionMenu( Batch_Render *BatchPre){

	/* 変数の初期化 */
	int keyin[20];//キー情報配列を作成
	int ech = 0;//エラーチェック変数
	int BumpMapStatus = 0;//バンプマップの状態変数 
	const D3DXVECTOR3 SpritePos1( 0.0, -25.0, 0.0);//背景の位置
	const D3DXVECTOR3 SpritePos2( 0.0, -60.0, 0.0);//十字バーの位置
	const D3DXVECTOR3 SpritePos3( 380.0, 45.0, 0.0);//上部の白いバー
	const E3DCOLOR4UC NormalColor = { 255,255,255,255};//白色の選ばれていない色
	const E3DCOLOR4UC SelectColor = { 255,200,220,20};//黄色の選ばれている色
	const E3DCOLOR4UC SetColor = { 255,0,120,170};//青色の武器が選ばれている色
	POINT TextPos;// テキストの座標を格納する変数

	/* ////////////////////// */
	// 状態の取得を行ないます
	/* ////////////////////// */

	// バンプマップ
	BumpMapStatus = BatchPre->BatchGetBumpMapStatus();



	/* メインループ */
	do{
			/* 変数の初期化 */
			int ExitFlag = 0;// 脱出フラグ変数
			int SelectKind = 0;

			/* 基本動作 */
			System::MsgQ(30);//メッセージループ
			System::KeyRenewal(1);
			System::GetKeyData(keyin);


			/* 描画準備をスルヨ */
			E3DBeginScene( System::scid1, 0, -1);//描画の開始準備
			
			/* ////////////////////////////// */
			// 基礎部品スプライトの部品を描画
			/* ////////////////////////////// */
			E3DBeginSprite();//スプライト描画の開始
					
			RenderBG();//背景の描画

			E3DEndSprite();//スプライト描画の終了
			
			/* ////////////////////// */
			// 文字の描画を行ないます
			/* ////////////////////// */

			//一番上の"オプション"テキスト
			PutString( "オプション", 440, 5, F_BIG, WHITE);

			PutString( "影のレンダリング", 100, 80, F_STANDARD, WHITE);

			PutString( "バンプマップ", 100, 160, F_STANDARD, WHITE);

			/* その他の文字を表示します */

			PutBalloon_Auto( System::MousePos.x, System::MousePos.y);

			SelectKind = ChkFontButton( System::MousePos.x, System::MousePos.y);
			if( SelectKind == 0){
						if(keyin[9] == 1){//クリックしたら
							ExitFlag = 1;//ループ脱出フラグをオンにする。
						}

			}



			/* //////////////// */
			/* バンプマップ関連 
			/* //////////////// */
			PutString( "ON", 120, 200, F_SMALL, WHITE);

			PutString( "OFF", 180, 200, F_SMALL, WHITE);

			/* 選択中の文字を表示 */
			
			if((210< System::MousePos.y)&&( System::MousePos.y<250)){// マウス座標が"ON"の上なら
						if((100< System::MousePos.x)&&(System::MousePos.x<170)){
								PutString( "ON", 120, 200, F_SMALL, BLUE);
								TextPos.x = 120;/**/TextPos.y = 200;

								// クリックされたら
								if( keyin[9] == 1){
										BumpMapStatus = 1;
								}
						}
						if((180< System::MousePos.x)&&(System::MousePos.x<250)){
								PutString( "OFF", 180, 200, F_SMALL, BLUE);

								// クリックされたら
								if( keyin[9] == 1){
										BumpMapStatus = 0;
								}
						}				
			}
			/* 青文字の表示 */
			if( BumpMapStatus == 1){// バンプマップがONの状態なら
					PutString( "ON", 120, 200, F_SMALL, YELOW);
					
			}
			if( BumpMapStatus == 0){// バンプマップがOFFの状態なら
					PutString( "OFF", 180, 200, F_SMALL, YELOW);
			}

			/* バンプマップ処理はここまで */




			/*ここまでで画面描画準備終了*/
			E3DEndScene();
			ech = E3DPresent( System::scid1);
			
					_ASSERT( ech != 1 );//エラーチェック

			/* もしゲームループを抜けてOKなら */
			if( ExitFlag == 1 ){
						break;//ループを抜ける
			}


	}while(WM_QUIT != System::msg.message);


	/* //////////////////////// */
	// 最終的な処理を行ないます */
	/* //////////////////////// */
	BatchPre->BatchEnableBumpMap( BumpMapStatus);// バンプマップの適応


	return 0;
}

/* デストラクタ、画像の破棄などを行ないます */
OptionMenu::~OptionMenu(){


	return;
}