/*オペレーションモードの関することをするコードファイル。
//
*/

#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "copsmenu.h"//オペレーションモードメニュー関係のクラスヘッダファイル
#include "coperation.h"//オペレーション開始関係のクラスヘッダファイル


/*コンストラクタ、画像の読み込みなど*/
OperationMenu::OperationMenu(){

	//変数の初期化
	int ech = 0;
	char loadname[256] = "";


	/*スプライトをロードします*/
	wsprintf( loadname, "%s\\data\\img\\opration\\Ops_intro.png", System::path);//メニュー画面での画像をロードします。
	ech = E3DCreateSprite( loadname, 0, 0, &OpsImgIDs[0]);
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};

	wsprintf( loadname, "%s\\data\\img\\menu\\menu_up_ber.png", System::path);//メニュー画面での上部白いバーをロードします。
	ech = E3DCreateSprite( loadname, 0, 0, &OpsImgIDs[1]);
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};

	wsprintf( loadname, "%s\\data\\img\\opration\\Ops_sel.png", System::path);//メニュー画面での選択バーをロードします。
	ech = E3DCreateSprite( loadname, 0, 0, &OpsImgIDs[2]);
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};

	wsprintf( loadname, "%s\\data\\img\\menu\\menubg2.png", System::path);//メニュー画面での背景をロードします。
	ech = E3DCreateSprite( loadname, 0, 0, &OpsBGImg);
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};





	/*アイテムメニューで使う文字IDを設定します。*/
	ech = E3DCreateFont( 35, 0, 800, 0, 0, 0, "MS Pゴシック", &TextID[0]);//大文字
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
	};

	ech = E3DCreateFont( 25, 0, 800, 0, 0, 0, "MS Pゴシック", &TextID[1]);//通常文字
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
	};

	ech = E3DCreateFont( 18, 0, 800, 0, 0, 0, "MS Pゴシック", &TextID[2]);//説明文文字
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
	};


	return;
}
/*デスコントラクタ、画像の破棄など*/
OperationMenu::~OperationMenu(){

	//変数の初期化
	int ech = 0;

	/**/
	//画像の破棄を行います
	/**/

	ech = E3DDestroySprite( OpsImgIDs[0]);//画像を削除します。
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};

	ech = E3DDestroySprite( OpsBGImg);//背景画像を削除します。
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};


	return;
}
/*オペレーションモードの処理を行います*/
int OperationMenu::InOpsMenu(){

		//変数の初期化
		int keyin[20];//キー情報配列を作成 
		int ech = 0;
		int ExitFlag = 0;//このフラグがオンになったとき脱出します。
		int SelectMission = -1;// この変数に数字が入っているときミッションに入ります。
		const char MissionName[5][30] = { "新緑のブレスレッド" , "この街のどこかに" , "買い物大激戦" , "時計台のある街で" , "突撃!秘密基地潜入!" };
		const char MissionDetal[5][200] ={
											"森の中をお散歩しましょう",
											"神ヶ一町を探索しましょう",
											"レリギオンモールにでかけましょう",
											"レトリスにお散歩しに行きましょう",
											"秘密基地前に潜入しましょう"};
		D3DXVECTOR3 MainSpritePos( 0.0, -28.0, 0.0);//背景の位置
		D3DXVECTOR3 OpsIntroPos( 350.0, 70, 0.0);//説明文画像の位置
		D3DXVECTOR3 MenuAboveBerPos( 380.0, 45.0, 0.0);//上部の白いバー
		D3DXVECTOR3 SelectImgPos( 30.0, 45.0, 0.0);//選択部の画像座標
		E3DCOLOR4UC NormalColor = { 255,50,50,50};//白色の選ばれていない色
		E3DCOLOR4UC SelectColor = { 255,130,150,20};//緑色の選ばれている色
		POINT TextPos;//テキストの座標を格納します
		POINT TextPos2;//テキストの座標を格納します

		while( WM_QUIT != System::msg.message ){

				System::MsgQ(30);//メッセージループ
				System::KeyRenewal( 1);
				System::GetKeyData(keyin);/*キーを取得する*/	
	
			


				/**/
				//描画準備をスルヨ
				/**/
				E3DBeginScene( System::scid1, 0, -1);//描画の開始準備
				E3DBeginSprite();//スプライト描画の開始

					//背景を描画
					ech = E3DRenderSprite( OpsBGImg, 640.0/1024.0, 480.0/512.0, MainSpritePos);
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
					};

					//メニュー上部のバーを描画
					ech = E3DRenderSprite( OpsImgIDs[1], 1, 1, MenuAboveBerPos);
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
					};

					//メニュー選択部の画像を描画
					ech = E3DRenderSprite( OpsImgIDs[2], 250.0/512.0, 360.0/512.0, SelectImgPos);
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
					};


					//任務の説明画像を描画
					ech = E3DRenderSprite( OpsImgIDs[0], 250.0/512.0, 250.0/512.0, OpsIntroPos);
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
					};


				E3DEndSprite();//スプライト描画の終了
				/*ここまでで画面描画準備終了*/

				/**/
				//文字を描画します
				/**/

				//一番上のポーズメニュー
				TextPos.x = 430;/**/TextPos.y = 5;
				E3DDrawTextByFontID( System::scid1, TextID[0], TextPos, "オペレーション", NormalColor);

				TextPos.y = 420;//60下げる
				ech = E3DDrawTextByFontID( System::scid1, TextID[1], TextPos, "オペレーションを終える", NormalColor);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
							return 1;//問題ありで終了
				};
	



				/* ////////////// */
				// 任務名を載せます
				/* ///////////// */
				TextPos.x = 50;/**/TextPos.y = 75;
				for( int i=0; i<5; i++ ){
						E3DDrawTextByFontID( System::scid1, TextID[1], TextPos, MissionName[i], NormalColor);
						if(ech != 0){//エラーチェック
										_ASSERT(0);//エラーダイアログを表示
						};
						TextPos.y = TextPos.y + 35;
				}
				/* /////////////////////////////////////////// */
				// マウスカーソルを置いている任務名を緑色にします
				/* /////////////////////////////////////////// */
				TextPos.x = 50;/**/TextPos.y = 75;
				for( int i=0; i<5; i++ ){

						/* マウスカーソルが文字の範囲内に入っているなら */
						if( ( 50 < System::MousePos.x)&&( System::MousePos.x < 200) &&
							( 25 + TextPos.y < System::MousePos.y)&&( System::MousePos.y< TextPos.y + 45)){

									/* 選択されていることを示す「緑文字」を表示する*/
									E3DDrawTextByFontID( System::scid1, TextID[1], TextPos, MissionName[i], SelectColor);
									if(ech != 0){//エラーチェック
													_ASSERT(0);//エラーダイアログを表示
									};
									/* 選択されているミッション名の詳細な情報を表示する*/
									TextPos2.x = 360;/**/TextPos2.y = 105;
									E3DDrawTextByFontID( System::scid1, TextID[2], TextPos2, MissionDetal[i], NormalColor);
									if(ech != 0){//エラーチェック
													_ASSERT(0);//エラーダイアログを表示
									};	
									if(keyin[9] == 1){//クリックしたら
											ExitFlag = 1;//ループ脱出フラグをオンにする。
											SelectMission = i;//ミッション変数にミッションナンバーを入れる
									}
						}
						TextPos.y = TextPos.y + 35;
				}




				/**/
				//マウスである座標に来たら…
				/**/
				if( ( 430 < System::MousePos.x)&&( System::MousePos.x < 600) &&
					( 450 < System::MousePos.y)&&( System::MousePos.y < 470)){//マウス座標が「オペレーションを終える」の上なら
							TextPos.x = 430;/**/TextPos.y = 420;
							E3DDrawTextByFontID( System::scid1, TextID[1], TextPos, "オペレーションを終える", SelectColor);//選択されている文字にする
							if(ech != 0){//エラーチェック
										_ASSERT(0);//エラーダイアログを表示
							};
							if(keyin[9] == 1){//クリックしたら
										ExitFlag = 1;//ループ脱出フラグをオンにする。
							}
				}


				E3DEndScene();
				ech = E3DPresent( System::scid1);
				if(ech != 0){//エラーチェック
							_ASSERT(0);//エラーダイアログを表示
				};


				if( ExitFlag == 1 ){//もしゲームループを抜けてOKなら
						break;//ループを抜ける
				}
		}


		/* 黒背景でフェードアウトさせる*/
		System::SetFadeOutOfScid(20);
		if( SelectMission != -1){
				Operation OPS;//オペレーションを作る
				OPS.OpsMissionBranchStart( SelectMission);// ミッションを開始します
		}



	return 0;
}