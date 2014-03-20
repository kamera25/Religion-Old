/*ここは、アイテム操作に関することのクラスです。
//主にバックパックやアイテム売買について書かれています。
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


/*コンストラクタ、アイテムのスプライトなどをロードします*/
Item_Manipulate::Item_Manipulate( PlayerChara *PC, Weapon *Wep){

	/*変数の宣言*/
	int ech = 0;//エラーチェック変数
	char loadname[256] = "";//ロードするファイル名の文字列配列
	E3DCOLOR4UC AlfaColor = { 200,255,255,255};//アイテムの詳細を書く画像の半透明

  /*画像のロードを行います*/

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

	wsprintf( loadname, "%s\\data\\img\\menu\\loading.png", sys->path);//ロード画像のロードします。
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[3]);
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};

	wsprintf( loadname, "%s\\data\\img\\item\\itstate.png", sys->path);//ロード画像のロードします。
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[4]);
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};

	wsprintf( loadname, "%s\\data\\img\\item\\itstate2.png", sys->path);//左向きのロード画像のロードします。
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[5]);
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};

	wsprintf( loadname, "%s\\data\\img\\item\\cure.png", sys->path);//回復アイコンのロード画像のロードします。
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[6]);
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};

	wsprintf( loadname, "%s\\data\\img\\item\\dump.png", sys->path);//ゴミ箱アイコンのロード画像のロードします。
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[7]);
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};

	wsprintf( loadname, "%s\\data\\img\\item\\info.png", sys->path);//情報アイコンのロード画像のロードします。
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[8]);
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};

	wsprintf( loadname, "%s\\data\\img\\item\\supply.png", sys->path);//供給マークのロード画像のロードします。
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[9]);
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};


	ech = E3DSetSpriteARGB( MenuSpriteIDs[4], AlfaColor);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/*ロード画像の表示*/
		D3DXVECTOR3 SpritePos4( 250.0, 170.0, 0.0);//ロード画像の位置
		/*描画準備を行います*/
		E3DBeginScene( sys->scid1, 1, -1);;
		E3DBeginSprite();

		ech = E3DRenderSprite( MenuSpriteIDs[3], 1, 1, SpritePos4);//ロードの画像
		if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
		};

		/*ここで、描画完了*/
		E3DEndSprite();

		E3DEndScene();
		E3DPresent(sys->scid1);

	/*次に武器の画像を読み込みます*/
	for( int i = 0; i<3; i++){
			if( Wep->GetSpriteData(i) != 0){//装備していれば
					BackPack_Weapon[i][0] = Wep->GetSpriteData(i) ;//画像データをロードする
					BackPack_Weapon[i][1] = Wep->GetWeaponData( i, 0);//武器の種類を代入する
					BackPack_Weapon[i][2] = Wep->GetWeaponData( i, 1);//武器のナンバーを代入する
			}
			else{//装備していなければ -> 空データロードします
					wsprintf( loadname, "%s\\data\\img\\item\\empty.png", sys->path);//空アイテム画像をロードします。
					ech = E3DCreateSprite( loadname, 0, 0, &BackPack_Weapon[i][0]);
					if(ech != 0){//エラーチェック
							_ASSERT(0);//エラーダイアログを表示
					}
					BackPack_Weapon[i][1] = -1;//武器の種類を空にする
					BackPack_Weapon[i][2] = -1;//武器のナンバーを空にする
			}
	}

	
	if( PC->BringWp == 0){//ステージで拾った武器の処理
			wsprintf( loadname, "%s\\data\\img\\item\\empty.png", sys->path);
			ech = E3DCreateSprite( loadname, 0, 0, &BackPack_Weapon[3][0]);
			if(ech != 0){//エラーチェック
					_ASSERT(0);//エラーダイアログを表示
			}
			//BackPack_Weapon[3] = GetLoadSprite();
	}

	/*次に弾薬の画像を読み込みます*/
	for( int i=0; i<4; i++){
			if( PC->Ammo[i] != 0){//装備していれば
					//BackPack_Ammo[i][0] = PC->wp_data[i][0][1];//空画像データをロードする
					wsprintf( loadname, "%s\\data\\img\\item\\empty.png", sys->path);//1次的に空アイテム画像をロードします。
					ech = E3DCreateSprite( loadname, 0, 0, &BackPack_Ammo[i][0]);
					if(ech != 0){//エラーチェック
							_ASSERT(0);//エラーダイアログを表示
					}
					BackPack_Ammo[i][1] = PC->Ammo[i];//武器の種類を代入する
			}
			else{//装備していなければ -> 空データロードします
					wsprintf( loadname, "%s\\data\\img\\item\\empty.png", sys->path);//空アイテム画像をロードします。
					ech = E3DCreateSprite( loadname, 0, 0, &BackPack_Ammo[i][0]);
					if(ech != 0){//エラーチェック
							_ASSERT(0);//エラーダイアログを表示
					}
					BackPack_Ammo[i][1] = -1;//武器のナンバーを空にする
			}
	}


	/**/
	//
	/**/

	/*アイテムメニューで使う文字IDを設定します。*/
	ech = E3DCreateFont( 35, 0, 800, 0, 0, 0, "MS Pゴシック", &TextID[0]);//大文字
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
	};

	ech = E3DCreateFont( 25, 0, 800, 0, 0, 0, "MS Pゴシック", &TextID[1]);//小文字
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
	};

	ech = E3DCreateFont( 15, 0, 800, 0, 0, 0, "MS Pゴシック", &TextID[2]);//最小文字
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
	};

}
/*デコントラクタ、ロードしたスプライトなどを削除します*/
Item_Manipulate::~Item_Manipulate(){

	int ech = 0;//エラーチェック変数

	/*スプライトを削除します*/
	for(int i = 0; i < 6; i++){
			ech = E3DDestroySprite( MenuSpriteIDs[i]);//メニュー画面での背景を削除します。
			if(ech != 0){//エラーチェック
						_ASSERT(0);//エラーダイアログを表示
			};
	}

	
	/*文字IDを削除します*/
	for(int i = 0; i < 3; i++){
			ech = E3DDestroyFont( TextID[i]);//大文字
			if(ech != 0){//エラーチェック
						_ASSERT(0);//エラーダイアログを表示
			};
	}



}
/*バックパックのメイン処理を行います*/
int Item_Manipulate::MainBackPack( PlayerChara *PC){


	/*変数の初期化*/
	int ChoseItem = 0;//選んだ武器

	do{

			sys->MsgQ(30);//メッセージループ

			/*変数の初期化*/
			int ech = 0;//エラーチェック変数
			int ExitFlag = 0;//このフラグがオンになったとき脱出します。
			int Counter = 0;//カウンター変数
			int ItemNumber = -1;//どのアイテムを選んだか、代入します
			int keyin[20];//キー情報配列を作成
			D3DXVECTOR3 SpritePos1( 0.0, -25.0, 0.0);//背景の位置
			D3DXVECTOR3 SpritePos2( 0.0, -60.0, 0.0);//十字バーの位置
			D3DXVECTOR3 SpritePos3( 380.0, 45.0, 0.0);//上部の白いバー
			D3DXVECTOR3 SpritePos4( 0.0, 0.0, 0.0);//アイテム画像の位置
			D3DXVECTOR3 SpritePos5( 0.0, 0.0, 0.0);//説明バーの位置
			E3DCOLOR4UC NormalColor = { 255,255,255,255};//白色の選ばれていない色
			E3DCOLOR4UC SelectColor = { 255,200,220,20};//黄色の選ばれている色
			E3DCOLOR4UC SetColor = { 255,0,120,170};//青色の武器が選ばれている色
			POINT TextPos;//文字の位置を格納する構造体

			sys->KeyRenewal(1);
			sys->GetKeyData(keyin);

			/*描画準備をスルヨ*/
			E3DBeginScene( sys->scid1, 0, -1);//描画の開始準備

			E3DBeginSprite();//スプライト描画の開始
			
			//基礎部品スプライトの部品を描画
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

			/*選んでいるアイテムカテゴリによって表示の分岐*/

			//武器のメニュー
			if( ChoseItem == 0){
				for(int i=0; i<2; i++){
						for(int j=0; j<2; j++){
								SpritePos4.x = 280+(j*160.0f);/**/SpritePos4.y = 100+(i*90.0f);
								ech = E3DRenderSprite( BackPack_Weapon[Counter][0], 1, 1, SpritePos4);//上部の白いバー
								if(ech != 0 ){//エラーチェック
											_ASSERT( 0 );//エラーダイアログ
								};
								Counter++;

								/*もしマウスの下が画像なら*/
								if(( 280 + ( j*160.0f ) < sys->MousePos.x ) && ( sys->MousePos.x < 408 + ( j*160.0f ))
										&& ( 120 + ( i*90.0f ) < sys->MousePos.y ) && ( sys->MousePos.y < 190 + ( i*90.0f ))){
											ItemNumber = Counter - 1;//カーソルと重なっていた画像のIDを代入
								}
						}
				};

				if( ItemNumber != -1 ){//もし、説明バーを表示させないといけないならば
						if( ( sys->MousePos.x + 256 ) < 640 ){//バーが右にはみ出ないのなら
								SpritePos5.x = float( sys->MousePos.x ); /**/ SpritePos5.y = float( sys->MousePos.y );
								ech = E3DRenderSprite( MenuSpriteIDs[4], 1, 1, SpritePos5);//上部の白いバー
								if(ech != 0 ){//エラーチェック
											_ASSERT( 0 );//エラーダイアログ
								};
						}
						else{//バーが右にはみ出るのなら
								SpritePos5.x = float( sys->MousePos.x - 256); /**/ SpritePos5.y = float( sys->MousePos.y );
								ech = E3DRenderSprite( MenuSpriteIDs[5], 1, 1, SpritePos5);//上部の白いバー
								if(ech != 0 ){//エラーチェック
											_ASSERT( 0 );//エラーダイアログ
								};
						}
				};
			}

			//弾薬のメニュー
			if( ChoseItem == 1){
				for(int i=0; i<2; i++){
						for(int j=0; j<2; j++){
								SpritePos4.x = 280+(j*160.0f);/**/SpritePos4.y = 100+(i*90.0f);
								ech = E3DRenderSprite( BackPack_Ammo[Counter][0], 1, 1, SpritePos4);//上部の白いバー
								if(ech != 0 ){//エラーチェック
											_ASSERT( 0 );//エラーダイアログ
								};
								Counter++;

								/*もしマウスの下が画像なら*/
								if(( 280 + ( j*160.0f ) < sys->MousePos.x ) && ( sys->MousePos.x < 408 + ( j*160.0f ))
										&& ( 120 + ( i*90.0f ) < sys->MousePos.y ) && ( sys->MousePos.y < 190 + ( i*90.0f ))){
											ItemNumber = Counter - 1;//カーソルと重なっていた画像のIDを代入
								}
						}
				};

				if( ItemNumber != -1 ){//もし、説明バーを表示させないといけないならば
						if( sys->MousePos.x + 256 < 640){//バーが右にはみ出ないのなら
								SpritePos5.x = float( sys->MousePos.x); /**/ SpritePos5.y = float( sys->MousePos.y);
								ech = E3DRenderSprite( MenuSpriteIDs[4], 1, 1, SpritePos5);//上部の白いバー
								if(ech != 0 ){//エラーチェック
											_ASSERT( 0 );//エラーダイアログ
								};
						}
						else{//バーが右にはみ出るのなら
								SpritePos5.x = float( sys->MousePos.x - 256); /**/ SpritePos5.y = float( sys->MousePos.y);
								ech = E3DRenderSprite( MenuSpriteIDs[5], 1, 1, SpritePos5);//上部の白いバー
								if(ech != 0 ){//エラーチェック
											_ASSERT( 0 );//エラーダイアログ
								};
						}
				};
			}

			E3DEndSprite();//スプライト描画の終了

			/**/
			//以下、文字の表示を行います
			/**/

			//一番上のポーズメニュー
			TextPos.x = 440;/**/TextPos.y = 5;
			E3DDrawTextByFontID( sys->scid1, TextID[0], TextPos, "バックパック", NormalColor);

			//以下、通常文字を表示
			TextPos.x = 100;
			TextPos.y = 100;//40ずつ下げる
			ech = E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "WEAPON", NormalColor);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			};

			TextPos.y = 140;//40ずつ下げる
			ech = E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "AMMO", NormalColor);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			};

			TextPos.y = 180;//40ずつ下げる
			ech = E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "RECOVERY", NormalColor);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			};

			TextPos.y = 220;//40ずつ下げる
			ech = E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "KEY", NormalColor);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			};

			TextPos.y = 260;//40ずつ下げる
			ech = E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "EQUIPMENT", NormalColor);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			};

			TextPos.y = 320;//60下げる
			ech = E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "バックパックを閉じる", NormalColor);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			};

			/*マウスが選択部にあるとき、文字を変更します*/
			if((100< sys->MousePos.x)&&(sys->MousePos.x<250)){
					if((120< sys->MousePos.y)&&( sys->MousePos.y<150)){//マウス座標が「WEAPON」の上なら
							TextPos.x = 100;
							TextPos.y = 100;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "WEAPON", SelectColor);//選択されている文字にする
							if(ech != 0){//エラーチェック
										_ASSERT(0);//エラーダイアログを表示
							};
							TextPos.x = 400;
							TextPos.y = 330;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "武器の操作をします", NormalColor);//説明が書かれている文字列を表示する
							if(ech != 0){//エラーチェック
										_ASSERT(0);//エラーダイアログを表示
							};
							if(keyin[9] == 1){//クリックしたら
										ChoseItem = 0;//ループ脱出フラグをオンにする。
							}
					}	
					if((160< sys->MousePos.y)&&( sys->MousePos.y<190)){//マウス座標が「AMMO」の上なら
							TextPos.x = 100;
							TextPos.y = 140;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "AMMO", SelectColor);//選択されている文字にする
							if(ech != 0){//エラーチェック
										_ASSERT(0);//エラーダイアログを表示
							};
							TextPos.x = 400;
							TextPos.y = 330;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "弾薬の操作をします", NormalColor);//説明が書かれている文字列を表示する
							if(ech != 0){//エラーチェック
										_ASSERT(0);//エラーダイアログを表示
							};
							if(keyin[9] == 1){//クリックしたら
										ChoseItem = 1;//ループ脱出フラグをオンにする。
							}
					}
					if((200< sys->MousePos.y)&&( sys->MousePos.y<230)){//マウス座標が「RECOVERY」の上なら
							TextPos.x = 100;
							TextPos.y = 180;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "RECOVERY", SelectColor);//選択されている文字にする
							if(ech != 0){//エラーチェック
										_ASSERT(0);//エラーダイアログを表示
							};
							TextPos.x = 400;
							TextPos.y = 330;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "回復系品の操作をします", NormalColor);//説明が書かれている文字列を表示する
							if(ech != 0){//エラーチェック
										_ASSERT(0);//エラーダイアログを表示
							};
							if(keyin[9] == 1){//クリックしたら
										ChoseItem = 2;//ループ脱出フラグをオンにする。
							}
					}	
					if((240< sys->MousePos.y)&&( sys->MousePos.y<270)){//マウス座標が「KEY」の上なら
							TextPos.x = 100;
							TextPos.y = 220;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "KEY", SelectColor);//選択されている文字にする
							if(ech != 0){//エラーチェック
										_ASSERT(0);//エラーダイアログを表示
							};
							TextPos.x = 400;
							TextPos.y = 330;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "重要品の操作をします", NormalColor);//説明が書かれている文字列を表示する
							if(ech != 0){//エラーチェック
										_ASSERT(0);//エラーダイアログを表示
							};
							if(keyin[9] == 1){//クリックしたら
										ChoseItem = 3;//ループ脱出フラグをオンにする。
							}
					}	
					if((280< sys->MousePos.y)&&( sys->MousePos.y<310)){//マウス座標が「EQUIPMENT」の上なら
							TextPos.x = 100;
							TextPos.y = 260;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "EQUIPMENT", SelectColor);//選択されている文字にする
							if(ech != 0){//エラーチェック
										_ASSERT(0);//エラーダイアログを表示
							};
							TextPos.x = 400;
							TextPos.y = 330;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "装備品の操作をします", NormalColor);//説明が書かれている文字列を表示する
							if(ech != 0){//エラーチェック
										_ASSERT(0);//エラーダイアログを表示
							};
							if(keyin[9] == 1){//クリックしたら
										ChoseItem = 4;//ループ脱出フラグをオンにする。
							}
					}	
					if((340< sys->MousePos.y)&&( sys->MousePos.y<370)){//マウス座標が「バックパックを閉じる」の上なら
							TextPos.x = 100;
							TextPos.y = 320;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "バックパックを閉じる", SelectColor);//選択されている文字にする
							if(ech != 0){//エラーチェック
										_ASSERT(0);//エラーダイアログを表示
							};
							TextPos.x = 400;
							TextPos.y = 330;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "ポーズメニューに戻ります", NormalColor);//説明が書かれている文字列を表示する
							if(ech != 0){//エラーチェック
										_ASSERT(0);//エラーダイアログを表示
							};
							if(keyin[9] == 1){//クリックしたら
										ExitFlag = 1;//ループ脱出フラグをオンにする。
							}
					}	
			}

			/*青色でどのアイテムの種類が選択されているを変更します*/
			//以下、通常文字を表示
			TextPos.x = 100;
			if( ChoseItem == 0){
					TextPos.y = 100;//40ずつ下げる
					E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "WEAPON", SetColor);
					if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
							return 1;//問題ありで終了
					};
			}
			if( ChoseItem == 1){
					TextPos.y = 140;//40ずつ下げる
					E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "AMMO", SetColor);
					if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
							return 1;//問題ありで終了
					};
			}
			if( ChoseItem == 2){
					TextPos.y = 180;//40ずつ下げる
					E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "RECOVERY", SetColor);
					if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
							return 1;//問題ありで終了
					};
			}
			if( ChoseItem == 3){
					TextPos.y = 220;//40ずつ下げる
					E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "KEY", SetColor);
					if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
							return 1;//問題ありで終了
					};
			}
			if( ChoseItem == 4){
					TextPos.y = 260;//40ずつ下げる
					E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "EQUIPMENT", SetColor);
					if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
							return 1;//問題ありで終了
					};
			}


			//最後に説明文を表示させます
			PutItemDescript( ChoseItem, ItemNumber);

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


	sys->KeyRenewal(1);//自動終了を行わないようにするための、キーチェック


	return 0;
}
/*アイテム処理に入る画像処理などを行います*/
int Item_Manipulate::InItemPack( PlayerChara *PC){



	/*右上のポーズメニュの表示をバックパックに徐々に変えます。*/
	for(int i = 0; i<17; i++){

					/*変数の初期化*/
					int ech = 0;//エラーチェック変数
					POINT TextPos;//テキストの座標変数
					E3DCOLOR4UC AlfaColor1 = { 255-(15*i) ,255,255,255};
					E3DCOLOR4UC AlfaColor2 = { 15*i ,255,255,255};
					D3DXVECTOR3 SpritePos1( 0.0, -25.0, 0.0);//背景の位置
					D3DXVECTOR3 SpritePos2( 0.0, -60.0, 0.0);//十字バーの位置
					D3DXVECTOR3 SpritePos3( 380.0, 45.0, 0.0);//上部の白いバー


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

					/*文字"ポーズメニュー"の描画を行います*/
					TextPos.x = 440;/**/TextPos.y = 5;
					E3DDrawTextByFontID( sys->scid1, TextID[0], TextPos, "ポーズメニュー", AlfaColor1);

					/*文字"バックパック"の描画を行います*/
					TextPos.x = 440;/**/TextPos.y = 5;
					E3DDrawTextByFontID( sys->scid1, TextID[0], TextPos, "バックパック", AlfaColor2);

					E3DEndScene();
					E3DPresent(sys->scid1);

					sys->MsgQ(30);//メッセージループ

			
	}/*ここまで*/

	

	/*バックパックのシステムに変わります*/
	MainBackPack( PC);///////

	/*右上のポーズメニュの表示をバックパックに徐々に変えます。*/
	for(int i = 0; i<17; i++){

					/*変数の初期化*/
					int ech = 0;//エラーチェック変数
					POINT TextPos;//テキストの座標変数
					E3DCOLOR4UC AlfaColor1 = { 15*i ,255,255,255};
					E3DCOLOR4UC AlfaColor2 = { 255-(15*i) ,255,255,255};
					D3DXVECTOR3 SpritePos1( 0.0, -25.0, 0.0);//背景の位置
					D3DXVECTOR3 SpritePos2( 0.0, -60.0, 0.0);//十字バーの位置
					D3DXVECTOR3 SpritePos3( 380.0, 45.0, 0.0);//上部の白いバー


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

					/*文字"ポーズメニュー"の描画を行います*/
					TextPos.x = 440;/**/TextPos.y = 5;
					E3DDrawTextByFontID( sys->scid1, TextID[0], TextPos, "ポーズメニュー", AlfaColor1);

					/*文字"バックパック"の描画を行います*/
					TextPos.x = 440;/**/TextPos.y = 5;
					E3DDrawTextByFontID( sys->scid1, TextID[0], TextPos, "バックパック", AlfaColor2);

					E3DEndScene();
					E3DPresent(sys->scid1);

					sys->MsgQ(30);//メッセージループ
		
	}/*ここまで*/





	return 0;
}
/*説明文を表示させる処理を行います*/
int Item_Manipulate::PutItemDescript( int ChoseItem, int ItemNumber){

	/*変数の初期化*/
	int ech = 0;//エラーチェック変数
	POINT TextPos1;//説明文字の位置を格納する構造体
	POINT TextPos2;//武器名文字の位置を格納する構造体
	POINT TextPos3;//武器の種類の名前文字の位置を格納する構造体
	E3DCOLOR4UC NormalColor = { 255,50,50,50};//文字の白色

	//文字の位置決め
	if( ( sys->MousePos.x + 256 ) < 640 ){//もしアイテムバーを右端を超えなければ
			TextPos1.x = sys->MousePos.x + 5;/**/TextPos1.y = sys->MousePos.y + 45;//説明文字の位置はマウスポインタから算出
			TextPos2.x = sys->MousePos.x + 160;/**/TextPos2.y = sys->MousePos.y + 5;//武器名文字の位置はマウスポインタから算出
			TextPos3.x = sys->MousePos.x + 5;/**/TextPos3.y = sys->MousePos.y + 5;//武器の種類の名前文字の位置はマウスポインタから算出
	}
	else{//超えれば
			TextPos1.x = sys->MousePos.x + 5 - 256;/**/TextPos1.y = sys->MousePos.y + 45;//説明文字の位置はマウスポインタから算出
			TextPos2.x = sys->MousePos.x + 160 - 256;/**/TextPos2.y = sys->MousePos.y + 5;//武器名文字の位置はマウスポインタから算出
			TextPos3.x = sys->MousePos.x + 5 - 256;/**/TextPos3.y = sys->MousePos.y + 5;//武器の種類の名前文字の位置はマウスポインタから算出
	}

	/**/
	//アイテムの種類によって分岐
	/**/

	if(ChoseItem == 0){//操作中のアイテムが「武器」なら
			if(BackPack_Weapon[ItemNumber][1] == 1){//武器がハンドガン系
					if(BackPack_Weapon[ItemNumber][2] == 0){//M1911
							ech = E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos2, "M1911", NormalColor);
							if(ech != 0){//エラーチェック
										_ASSERT(0);//エラーダイアログを表示
							}
							ech = E3DDrawTextByFontID( sys->scid1, TextID[2], TextPos1, "米国製の扱いやすい45口径拳銃", NormalColor);
							if(ech != 0){//エラーチェック
										_ASSERT(0);//エラーダイアログを表示
							}
					}
					if(BackPack_Weapon[ItemNumber][2] == 2){//Glock95
							ech = E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos2, "Glock95", NormalColor);
							if(ech != 0){//エラーチェック
										_ASSERT(0);//エラーダイアログを表示
							}
							ech = E3DDrawTextByFontID( sys->scid1, TextID[2], TextPos1, "ポリマーフレームのフルオート拳銃", NormalColor);
							if(ech != 0){//エラーチェック
										_ASSERT(0);//エラーダイアログを表示
							}
					}
					if(BackPack_Weapon[ItemNumber][2] == 3){//M92F
							ech = E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos2, "M92F", NormalColor);
							if(ech != 0){//エラーチェック
										_ASSERT(0);//エラーダイアログを表示
							}
							ech = E3DDrawTextByFontID( sys->scid1, TextID[2], TextPos1, "扱いやすい米軍の正式採用拳銃", NormalColor);
							if(ech != 0){//エラーチェック
										_ASSERT(0);//エラーダイアログを表示
							}
					}
			}
			if(BackPack_Weapon[ItemNumber][1] == 4){//武器がアサルトライフル系
					if(BackPack_Weapon[ItemNumber][2] == 0){//M4
							ech = E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos2, "M4", NormalColor);
							if(ech != 0){//エラーチェック
										_ASSERT(0);//エラーダイアログを表示
							}
							ech = E3DDrawTextByFontID( sys->scid1, TextID[2], TextPos1, "光学サイトを搭載したアメリカを代表する小銃", NormalColor);
							if(ech != 0){//エラーチェック
										_ASSERT(0);//エラーダイアログを表示
							}
					}
			}

		/**//////////
		/**////////

			if(BackPack_Weapon[ItemNumber][1] == -1){//何もないアイテム画像の上なら
					ech =E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos2, "EMPTY", NormalColor);
					if(ech != 0){//エラーチェック
							_ASSERT(0);//エラーダイアログを表示
					}
					ech = E3DDrawTextByFontID( sys->scid1, TextID[2], TextPos1, "武器がありません", NormalColor);
					if(ech != 0){//エラーチェック
							_ASSERT(0);//エラーダイアログを表示
					}
			}

			if(ItemNumber == 0){//マウスがメインウェポンの上にあれば
					ech = E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos3, "MAINWEAPON", NormalColor);
					if(ech != 0){//エラーチェック
								_ASSERT(0);//エラーダイアログを表示
					}
			}
			if(ItemNumber == 1){//マウスがサブウェポンの上にあれば
					ech = E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos3, "SUBWEAPON", NormalColor);
					if(ech != 0){//エラーチェック
								_ASSERT(0);//エラーダイアログを表示
					}
			}
			if(ItemNumber == 2){//マウスがグレネード系の上にあれば
					ech = E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos3, "GRENADE", NormalColor);
					if(ech != 0){//エラーチェック
								_ASSERT(0);//エラーダイアログを表示
					}
			}
			if(ItemNumber == 3){//マウスが修理が必要な武器の上にあれば
					ech = E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos3, "NEED REPAIR", NormalColor);
					if(ech != 0){//エラーチェック
								_ASSERT(0);//エラーダイアログを表示
					}
			}
	}

	if(ChoseItem == 1){//操作中のアイテムが「弾薬」なら

			if( BackPack_Ammo[ItemNumber][2] == 0){//M1911
					ech = E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos3, ".45ACP", NormalColor);
					if(ech != 0){//エラーチェック
									_ASSERT(0);//エラーダイアログを表示
					}
					ech = E3DDrawTextByFontID( sys->scid1, TextID[2], TextPos1, "米国製大型自動拳銃用の実包", NormalColor);
					if(ech != 0){//エラーチェック
									_ASSERT(0);//エラーダイアログを表示
					}
			}


	}

	return 0;
}