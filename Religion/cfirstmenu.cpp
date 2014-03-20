/*ここは、最初のメニューに関することのクラスです。
//主に最初の画像をロードしたり処理をしたりするところについて書かれています。
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "cfirstmenu.h"//メインメニューに関するメニュクラスヘッダファイル




/*最初のメニューの処理を行います*/
int MainMenu::InMainMenu(){

	//変数の初期化
	int ech = 0;
	int ExitFlag = 0;//このフラグがオンになったとき脱出します。
	int PushAlfa = 0;//PushKeyIMGの透明度を指定
	int PushAlfaReduction = 1;//透明度の増減を指定
	int MenuMode = 0;
	int MenuSelectNo = 0;
	int keyin[20];//キー情報配列を作成 
	D3DXVECTOR3 MainSpritePos( 0.0, -28.0, 0.0);//背景の位置
	D3DXVECTOR3 PushKeySpritePos( 180.0, 390.0, 0.0);//PushKeyIMGの位置
	D3DXVECTOR3 MenuSpritePos1( 150.0, 400, 0.0);//モードの位置
	D3DXVECTOR3 MenuSpritePos2( 270.0, 400, 0.0);//背景の位置
	D3DXVECTOR3 MenuSpritePos3( 390.0, 400, 0.0);//背景の位置


	while( WM_QUIT != System::msg.message ){

			//変数の初期化
			E3DCOLOR4UC AlfaColor = { PushAlfa,255,255,255};//カラー構造体の半透過のデータ

			System::MsgQ(30);//メッセージループ
			System::KeyRenewal( 0);
			System::GetKeyData(keyin);/*キーを取得する*/	
	
			

			/*選択モードの時左右を押したら*/
			if( MenuMode == 1){
				if( keyin[2] == 1) MenuSelectNo = MenuSelectNo - 1;
				if( keyin[4] == 1) MenuSelectNo = MenuSelectNo + 1;
				if( keyin[0] == 1) ExitFlag = 1;//ループから脱出

				if( MenuSelectNo == -1) MenuSelectNo = 3;
				if( MenuSelectNo == 4) MenuSelectNo = 1;
			}

			/*メニュモードが最初でエンターが押されたら*/
			if( (keyin[0] == 1) && (MenuMode == 0)) MenuMode = 1;//モードを次に

			/**/
			//描画準備をスルヨ
			/**/
			E3DBeginScene( System::scid1, 0, -1);//描画の開始準備
			E3DBeginSprite();//スプライト描画の開始

					ech = E3DRenderSprite( MainBGImg, 640.0/1024.0, 480.0/512.0, MainSpritePos);//
					_ASSERT( ech != 1 );//エラーチェック

					if( MenuMode == 0){
							ech = E3DRenderSprite( PushKeyImg, 300.0/512.0, 18.0/32.0, PushKeySpritePos);//
							_ASSERT( ech != 1 );//エラーチェック
					}

					if( MenuMode == 1){

						if( MenuSelectNo == 0){//ロードゲームが先頭なら
								ech = E3DRenderSprite( MenuSelectImg[0], 87.0/128.0, 12.0/16.0, MenuSpritePos1);//
								_ASSERT( ech != 1 );//エラーダイアログを表示
								ech = E3DRenderSprite( MenuSelectImg[1], 94.0/128.0, 12.0/16.0, MenuSpritePos2);//選ばれているもの
								_ASSERT( ech != 1 );//エラーダイアログを表示
								ech = E3DRenderSprite( MenuSelectImg[2], 90.0/128.0, 12.0/16.0, MenuSpritePos3);//
								_ASSERT( ech != 1 );//エラーチェック
						}
						if( MenuSelectNo == 1){//オペレーションが先頭なら
								ech = E3DRenderSprite( MenuSelectImg[1], 94.0/128.0, 12.0/16.0, MenuSpritePos1);//
								_ASSERT( ech != 1 );//エラーダイアログを表示
								ech = E3DRenderSprite( MenuSelectImg[2], 90.0/128.0, 12.0/16.0, MenuSpritePos2);//選ばれているもの
								_ASSERT( ech != 1 );//エラーダイアログを表示
								ech = E3DRenderSprite( MenuSelectImg[3], 58.0/64.0, 12.0/16.0, MenuSpritePos3);//
								_ASSERT( ech != 1 );//エラーチェック
						}
						if( MenuSelectNo == 2){//オンラインが先頭なら
								ech = E3DRenderSprite( MenuSelectImg[2], 90.0/128.0, 12.0/16.0, MenuSpritePos1);//
								_ASSERT( ech != 1 );//エラーダイアログを表示
								ech = E3DRenderSprite( MenuSelectImg[3], 58.0/64.0, 12.0/16.0, MenuSpritePos2);//選ばれているもの
								_ASSERT( ech != 1 );//エラーダイアログを表示
								ech = E3DRenderSprite( MenuSelectImg[0], 87.0/128.0, 12.0/16.0, MenuSpritePos3);//
								_ASSERT( ech != 1 );//エラーチェック
						}
						if( MenuSelectNo == 3){//ニューゲームが先頭なら
								ech = E3DRenderSprite( MenuSelectImg[3], 58.0/64.0, 12.0/16.0, MenuSpritePos1);//
								_ASSERT( ech != 1 );//エラーダイアログを表示
								ech = E3DRenderSprite( MenuSelectImg[0], 87.0/128.0, 12.0/16.0, MenuSpritePos2);//選ばれているもの
								_ASSERT( ech != 1 );//エラーダイアログを表示
								ech = E3DRenderSprite( MenuSelectImg[1], 94.0/128.0, 12.0/16.0, MenuSpritePos3);//
								_ASSERT( ech != 1 );//エラーチェック
						}
					}

			E3DEndSprite();//スプライト描画の終了
			/*ここまでで画面描画準備終了*/
			E3DEndScene();
			ech = E3DPresent( System::scid1);
			
					_ASSERT( ech != 1 );//エラーチェック


			/**/
			//PushKeyImg画像の透明度を指定する
			/**/
			if( MenuMode == 0){
					ech = E3DSetSpriteARGB( PushKeyImg, AlfaColor);
					_ASSERT( ech != 1 );//エラーチェック

					if( PushAlfa == 255) PushAlfaReduction = -1;
					if( PushAlfa == 0) PushAlfaReduction = 1;
					PushAlfa = PushAlfa + ( 5 * PushAlfaReduction) ;
			}


			if( ExitFlag == 1 ){//もしゲームループを抜けてOKなら
						break;//ループを抜ける
			}


	}

	/*もし、プロージャーからの終了命令があれば*/
	if( WM_QUIT == System::msg.message){
		 MenuSelectNo = -1;//エラーを返す
	}


	/* 黒背景でフェードアウトさせる*/
	System::SetFadeOutOfScid(20);



	return MenuSelectNo;
}
/*コンストラクタ*/
MainMenu::MainMenu(){

	//変数の初期化
	int ech = 0;
	char loadname[256] = "";

	/**/
	//画像のロード
	/**/


	/*メインメニューに表示させる壁紙をロードします。*/
	wsprintf( loadname, "%s\\data\\img\\mainmenu\\op1.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &MainBGImg);//カーソルのロード
	_ASSERT( ech != 1 );//エラーチェック

	/*メインメニューに表示させるプッシュキー画像をロードします。*/
	wsprintf( loadname, "%s\\data\\img\\mainmenu\\pushkey.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &PushKeyImg);//カーソルのロード
	_ASSERT( ech != 1 );//エラーチェック


	/*メインメニューに表示させるニューゲーム画像をロードします。*/
	wsprintf( loadname, "%s\\data\\img\\mainmenu\\newgame.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSelectImg[0]);//カーソルのロード
	_ASSERT( ech != 1 );//エラーチェック

	/*メインメニューに表示させるロードゲーム画像をロードします。*/
	wsprintf( loadname, "%s\\data\\img\\mainmenu\\loadgame.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSelectImg[1]);//カーソルのロード
	_ASSERT( ech != 1 );//エラーチェック

	/*メインメニューに表示させるオペレーション画像をロードします。*/
	wsprintf( loadname, "%s\\data\\img\\mainmenu\\operation.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSelectImg[2]);//カーソルのロード
	_ASSERT( ech != 1 );//エラーチェック

	/*メインメニューに表示させるオンライン画像をロードします。*/
	wsprintf( loadname, "%s\\data\\img\\mainmenu\\online.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSelectImg[3]);//カーソルのロード
	_ASSERT( ech != 1 );//エラーチェック

	/*メインメニュー後に表示させる黒背景をロードします。*/
	wsprintf( loadname, "%s\\data\\img\\oth\\black.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSelectImg[4]);//カーソルのロード
	_ASSERT( ech != 1 );//エラーチェック



	return;
}
/*デストラクタ*/
MainMenu::~MainMenu(){

	//変数の初期化
	int ech = 0;

	/**/
	//画像の破棄を行います
	/**/

	ech = E3DDestroyHandlerSet( MainBGImg);//モデルを削除します
	_ASSERT( ech != 1 );//エラーチェック

	ech = E3DDestroyHandlerSet( PushKeyImg);//モデルを削除します
	_ASSERT( ech != 1 );//エラーチェック

	for(int i = 0;i < 5; i++){
			ech = E3DDestroyHandlerSet( MenuSelectImg[i]);//モデルを削除します
			_ASSERT( ech != 1 );//エラーチェック
	}


	return;
}