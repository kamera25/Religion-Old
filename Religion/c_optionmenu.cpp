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

	/*変数の宣言*/
	int ech = 0;//エラーチェック変数
	char loadname[256] = "";//ロードするファイル名の文字列配列


	/*スプライトをロードします*/
	wsprintf( loadname, "%s\\data\\img\\menu\\menubg.png", System::path);//メニュー画面での背景をロードします。
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[0]);
	
			_ASSERT( ech != 1 );//エラーチェック

	wsprintf( loadname, "%s\\data\\img\\menu\\menuber.png", System::path);//メニュー画面での十字バーをロードします。
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[1]);
	
			_ASSERT( ech != 1 );//エラーチェック

	wsprintf( loadname, "%s\\data\\img\\menu\\menu_up_ber.png", System::path);//メニュー画面での上部白いバーをロードします。
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[2]);
	
			_ASSERT( ech != 1 );//エラーチェック



	/*メニューで使う文字IDを設定します。*/
	ech = E3DCreateFont( 35, 0, 800, 0, 0, 0, "MS Pゴシック", &TextID[0]);//大文字
	_ASSERT( ech != 1 );//エラーチェック

	ech = E3DCreateFont( 30, 0, 800, 0, 0, 0, "MS Pゴシック", &TextID[1]);//中文字
	_ASSERT( ech != 1 );//エラーチェック

	ech = E3DCreateFont( 25, 0, 800, 0, 0, 0, "MS Pゴシック", &TextID[2]);//小文字
	_ASSERT( ech != 1 );//エラーチェック


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

			/* 基本動作 */
			System::MsgQ(30);//メッセージループ
			System::KeyRenewal(1);
			System::GetKeyData(keyin);


			/* 描画準備をスルヨ */
			E3DBeginScene( System::scid1, 0, -1);//描画の開始準備

			E3DBeginSprite();//スプライト描画の開始
			
			/* ////////////////////////////// */
			// 基礎部品スプライトの部品を描画
			/* ////////////////////////////// */
			ech = E3DRenderSprite( MenuSpriteIDs[0], 640.0/1024.0, 480.0/512.0, SpritePos1);//背景の位置
			_ASSERT( ech != 1 );//エラーチェック
			
			ech = E3DRenderSprite( MenuSpriteIDs[1], 1, 1, SpritePos2);//十字バーの位置
			_ASSERT( ech != 1 );//エラーチェック

			ech = E3DRenderSprite( MenuSpriteIDs[2], 1, 1, SpritePos3);//上部の白いバー
			_ASSERT( ech != 1 );//エラーチェック

			E3DEndSprite();//スプライト描画の終了
			
			/* ////////////////////// */
			// 文字の描画を行ないます
			/* ////////////////////// */

			//一番上の"オプション"テキスト
			TextPos.x = 440;/**/TextPos.y = 5;
			E3DDrawTextByFontID( System::scid1, TextID[0], TextPos, "オプション", NormalColor);

			TextPos.x = 100;/**/TextPos.y = 80;
			E3DDrawTextByFontID( System::scid1, TextID[1], TextPos, "影のレンダリング", NormalColor);
			if(ech != 0 ){//エラーチェック
						_ASSERT( 0 );//エラーダイアログ
						return 1;//問題ありで終了
			}

			TextPos.x = 100;/**/TextPos.y = 160;
			E3DDrawTextByFontID( System::scid1, TextID[1], TextPos, "バンプマップ", NormalColor);
			if(ech != 0 ){//エラーチェック
						_ASSERT( 0 );//エラーダイアログ
						return 1;//問題ありで終了
			}


			/* その他の文字を表示します */
			TextPos.x = 100;/**/TextPos.y = 320;
			ech = E3DDrawTextByFontID( System::scid1, TextID[2], TextPos, "オプションを閉じる", NormalColor);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			};

			/* マウス座標によって処理を変更します */
			if((100< System::MousePos.x)&&(System::MousePos.x<250) &&// マウス座標が「オプションを閉じる」の上なら
				((340< System::MousePos.y)&&( System::MousePos.y<370))){
						TextPos.x = 100;/**/TextPos.y = 320;
						E3DDrawTextByFontID( System::scid1, TextID[2], TextPos, "オプションを閉じる", SelectColor);//選択されている文字にする
						
						_ASSERT( ech != 1 );//エラーチェック

						if(keyin[9] == 1){//クリックしたら
							ExitFlag = 1;//ループ脱出フラグをオンにする。
						}
			}
			if((100< System::MousePos.x)&&(System::MousePos.x<320) &&// マウス座標が「影のレンダリング」らへんの上なら
				((80< System::MousePos.y)&&( System::MousePos.y<180))){

					TextPos.x = 300;/**/TextPos.y = 330;
					E3DDrawTextByFontID( System::scid1, TextID[2], TextPos, "影のレンダリング処理(Quality,ON/OFF)", NormalColor);//説明が書かれている文字列を表示する
					
					_ASSERT( ech != 1 );//エラーチェック
			}
			if((100< System::MousePos.x)&&(System::MousePos.x<320) &&// マウス座標が「バンプマップ」らへんの上なら
				((200< System::MousePos.y)&&( System::MousePos.y<300))){

					TextPos.x = 295;/**/TextPos.y = 330;
					E3DDrawTextByFontID( System::scid1, TextID[2], TextPos, "マップがデコボコぽく見える処理(ON/OFF)", NormalColor);//説明が書かれている文字列を表示する
					
					_ASSERT( ech != 1 );//エラーチェック
			}

			/* //////////////// */
			/* バンプマップ関連 
			/* //////////////// */
			TextPos.x = 120;/**/TextPos.y = 200;
			E3DDrawTextByFontID( System::scid1, TextID[2], TextPos, "ON", NormalColor);
			if(ech != 0 ){//エラーチェック
						_ASSERT( 0 );//エラーダイアログ
						return 1;//問題ありで終了
			}
			TextPos.x = 180;/**/TextPos.y = 200;
			E3DDrawTextByFontID( System::scid1, TextID[2], TextPos, "OFF", NormalColor);
			if(ech != 0 ){//エラーチェック
						_ASSERT( 0 );//エラーダイアログ
						return 1;//問題ありで終了
			}

			/* 選択中の文字を表示 */
			
			if((210< System::MousePos.y)&&( System::MousePos.y<250)){// マウス座標が"ON"の上なら
						if((100< System::MousePos.x)&&(System::MousePos.x<170)){
								TextPos.x = 120;/**/TextPos.y = 200;
								E3DDrawTextByFontID( System::scid1, TextID[2], TextPos, "ON", SelectColor);
								if(ech != 0 ){//エラーチェック
										_ASSERT( 0 );//エラーダイアログ
										return 1;//問題ありで終了
								}

								// クリックされたら
								if( keyin[9] == 1){
										BumpMapStatus = 1;
								}
						}
						if((180< System::MousePos.x)&&(System::MousePos.x<250)){
								TextPos.x = 180;/**/TextPos.y = 200;
								E3DDrawTextByFontID( System::scid1, TextID[2], TextPos, "OFF", SelectColor);
								if(ech != 0 ){//エラーチェック
										_ASSERT( 0 );//エラーダイアログ
										return 1;//問題ありで終了
								}

								// クリックされたら
								if( keyin[9] == 1){
										BumpMapStatus = 0;
								}
						}				
			}
			/* 青文字の表示 */
			if( BumpMapStatus == 1){// バンプマップがONの状態なら
					TextPos.x = 120;/**/TextPos.y = 200;
					E3DDrawTextByFontID( System::scid1, TextID[2], TextPos, "ON", SetColor);
					if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
							return 1;//問題ありで終了
					}
			}
			if( BumpMapStatus == 0){// バンプマップがOFFの状態なら
					TextPos.x = 180;/**/TextPos.y = 200;
					E3DDrawTextByFontID( System::scid1, TextID[2], TextPos, "OFF", SetColor);
					if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
							return 1;//問題ありで終了
					}
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

	int ech = 0;//エラーチェック変数

	/*スプライトを削除します*/
	for(int i = 0; i < 3; i++){
			ech = E3DDestroySprite( MenuSpriteIDs[i]);//メニュー画面での背景を削除します。
			
					_ASSERT( ech != 1 );//エラーチェック
	}

	
	/*文字IDを削除します*/
	for(int i = 0; i < 3; i++){
			ech = E3DDestroyFont( TextID[i]);//大文字
			
					_ASSERT( ech != 1 );//エラーチェック
	}



}