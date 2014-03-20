/*ここは、アイテム操作に関することのクラスです。
//主にバックパックやアイテム売買について書かれています。
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "citem_manipulate.h"//アイテム操作に関するヘッダファイル
#include "clive.h"//敵やキャラの宣言ヘッダファイル
#include "cweapon.h"//武器に関することのクラスヘッダファイル
#include "citem.h"//アイテムの宣言ヘッダファイル




/*コンストラクタ、アイテムのスプライトなどをロードします*/
Item_Manipulate::Item_Manipulate( Weapon *Wep, Item *item){

	/*変数の宣言*/
	int ech = 0;//エラーチェック変数
	char loadname[256] = "";//ロードするファイル名の文字列配列
	E3DCOLOR4UC AlfaColor = { 200,255,255,255};//アイテムの詳細を書く画像の半透明


	/* ********************** 
	// 画像のロードを行います
	// **********************
	*/

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

	wsprintf( loadname, "%s\\data\\img\\menu\\loading.png", System::path);//ロード画像のロードします。
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[3]);
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};

	wsprintf( loadname, "%s\\data\\img\\item\\itstate.png", System::path);//ロード画像のロードします。
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[4]);
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};

	wsprintf( loadname, "%s\\data\\img\\item\\itstate2.png", System::path);//左向きのロード画像のロードします。
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[5]);
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};

	wsprintf( loadname, "%s\\data\\img\\item\\cure.png", System::path);//回復アイコンのロード画像のロードします。
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[6]);
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};

	wsprintf( loadname, "%s\\data\\img\\item\\dump.png", System::path);//ゴミ箱アイコンのロード画像のロードします。
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[7]);
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};

	wsprintf( loadname, "%s\\data\\img\\item\\info.png", System::path);//情報アイコンのロード画像のロードします。
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[8]);
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};

	wsprintf( loadname, "%s\\data\\img\\item\\supply.png", System::path);//供給マークのロード画像のロードします。
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[9]);
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};


	ech = E3DSetSpriteARGB( MenuSpriteIDs[4], AlfaColor);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/* ****************
	// ロード画面の表示
	// ****************
	*/
	D3DXVECTOR3 SpritePos4( 250.0, 170.0, 0.0);//ロード画像の位置
	/*描画準備を行います*/
	E3DBeginScene( System::scid1, 1, -1);;
	E3DBeginSprite();

	ech = E3DRenderSprite( MenuSpriteIDs[3], 1, 1, SpritePos4);//ロードの画像
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/*ここで、描画完了*/
	E3DEndSprite();

	E3DEndScene();
	E3DPresent(System::scid1);

	/* ******************************
	// アイテム系の画像をロードします
	// ******************************
	*/

	/*次に武器の画像を読み込みます*/
	for( int i = 0; i<3; i++){
			if( Wep->GetSpriteData(i) != 0){//装備していれば
					BackPack_Weapon[i][0] = Wep->GetSpriteData(i) ;//画像データをロードする
					BackPack_Weapon[i][1] = Wep->GetWeaponData( i, 0);//武器の種類を代入する
					BackPack_Weapon[i][2] = Wep->GetWeaponData( i, 1);//武器のナンバーを代入する
			}
			else{//装備していなければ -> 空データロードします
					wsprintf( loadname, "%s\\data\\img\\item\\empty.png", System::path);//空アイテム画像をロードします。
					ech = E3DCreateSprite( loadname, 0, 0, &BackPack_Weapon[i][0]);
					if(ech != 0){//エラーチェック
							_ASSERT(0);//エラーダイアログを表示
					}
					BackPack_Weapon[i][1] = -1;//武器の種類を空にする
					BackPack_Weapon[i][2] = -1;//武器のナンバーを空にする
			}
	}

	
	if( item->GetItemNumber( 0, -1, -1) == 0){//ステージで拾った武器の処理
			wsprintf( loadname, "%s\\data\\img\\item\\empty.png", System::path);
			ech = E3DCreateSprite( loadname, 0, 0, &BackPack_Weapon[3][0]);
			if(ech != 0){//エラーチェック
					_ASSERT(0);//エラーダイアログを表示
			}
			BackPack_Weapon[3][1] = -1;//武器の種類を空にする
			BackPack_Weapon[3][2] = -1;//武器のナンバーを空にする
			//BackPack_Weapon[3] = GetLoadSprite();
	}

	/*次に弾薬の画像を読み込みます*/
	for( int i=0; i<4; i++){
			if( item->GetItemNumber( 1, i, -1) != -1){//装備していれば
					//BackPack_Ammo[i][0] = PC->wp_data[i][0][1];//空画像データをロードする
					wsprintf( loadname, "%s\\data\\img\\item\\empty.png", System::path);//1次的に空アイテム画像をロードします。
					ech = E3DCreateSprite( loadname, 0, 0, &BackPack_Ammo[i][0]);
					if(ech != 0){//エラーチェック
							_ASSERT(0);//エラーダイアログを表示
					}
					BackPack_Ammo[i][1] = item->GetItemNumber( 1, i, -1);//武器の種類を代入する
			}
			else{//装備していなければ -> 空データロードします
					wsprintf( loadname, "%s\\data\\img\\item\\empty.png", System::path);//空アイテム画像をロードします。
					ech = E3DCreateSprite( loadname, 0, 0, &BackPack_Ammo[i][0]);
					if(ech != 0){//エラーチェック
							_ASSERT(0);//エラーダイアログを表示
					}
					BackPack_Ammo[i][1] = -1;//武器のナンバーを空にする
			}
	}

	/*次にの画像を読み込みます*/
	for( int i=0; i<5; i++){
			if( item->GetItemNumber( 2, i, 0) != -1){//装備していれば
					//BackPack_Ammo[i][0] = PC->Recovery[i][0];//空画像データをロードする
					wsprintf( loadname, "%s\\data\\img\\item\\empty.png", System::path);//1次的に空アイテム画像をロードします。
					ech = E3DCreateSprite( loadname, 0, 0, &BackPack_Recovery[i][0]);
					if(ech != 0){//エラーチェック
							_ASSERT(0);//エラーダイアログを表示
					}
					BackPack_Recovery[i][1] = item->GetItemNumber( 2, i, 0);//武器の種類を代入する
			}
			else{//装備していなければ -> 空データロードします
					wsprintf( loadname, "%s\\data\\img\\item\\empty.png", System::path);//空アイテム画像をロードします。
					ech = E3DCreateSprite( loadname, 0, 0, &BackPack_Recovery[i][0]);
					if(ech != 0){//エラーチェック
							_ASSERT(0);//エラーダイアログを表示
					}
					BackPack_Recovery[i][1] = -1;//武器のナンバーを空にする
			}
	}

	/* ******************
	// フォントの読み込み
	// ******************
	*/
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



	return;
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


	/*変数の宣言*/
	int ChoseItem = 0;//選んだ武器

	do{

			System::MsgQ(30);//メッセージループ

			/* 変数の宣言 */
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

			/* 作成中関係変数 */
			const int ItemSpritePosition[3][2][6] = {
				{ { 280 , 440, 280, 440} , {100 , 100, 190, 190} },// 武器メニュー
				{ { 280 , 440, 280, 440} , {100 , 100, 190, 190}  },// 弾薬メニュー
				{ { 280 , 440, 280, 440 , 360} , {100 , 100, 190, 190 , 280}  } // 回復系メニュー
			};


			System::KeyRenewal(1);
			System::GetKeyData(keyin);

			/*描画準備をスルヨ*/
			E3DBeginScene( System::scid1, 0, -1);//描画の開始準備

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
			switch( ChoseItem ){
				case 0:{//武器のメニュー
					for(int i=0; i<2; i++){
							for(int j=0; j<2; j++){
									SpritePos4.x = 280+(j*160.0f);/**/SpritePos4.y = 100+(i*90.0f);
									ech = E3DRenderSprite( BackPack_Weapon[Counter][0], 1, 1, SpritePos4);//上部の白いバー
									if(ech != 0 ){//エラーチェック
												_ASSERT( 0 );//エラーダイアログ
									};
									Counter++;

									/*もしマウスの下が画像なら*/
									if(( 280 + ( j*160.0f ) < System::MousePos.x ) && ( System::MousePos.x < 408 + ( j*160.0f ))
											&& ( 120 + ( i*90.0f ) < System::MousePos.y ) && ( System::MousePos.y < 190 + ( i*90.0f ))){
												ItemNumber = Counter - 1;//カーソルと重なっていた画像のIDを代入
									}
							}
					};

					if( ItemNumber != -1 ){//もし、説明バーを表示させないといけないならば
							if( ( System::MousePos.x + 256 ) < 640 ){//バーが右にはみ出ないのなら
									SpritePos5.x = float( System::MousePos.x ); /**/ SpritePos5.y = float( System::MousePos.y );
									ech = E3DRenderSprite( MenuSpriteIDs[4], 1, 1, SpritePos5);//上部の白いバー
									if(ech != 0 ){//エラーチェック
												_ASSERT( 0 );//エラーダイアログ
									};
							}
							else{//バーが右にはみ出るのなら
									SpritePos5.x = float( System::MousePos.x - 256); /**/ SpritePos5.y = float( System::MousePos.y );
									ech = E3DRenderSprite( MenuSpriteIDs[5], 1, 1, SpritePos5);//上部の白いバー
									if(ech != 0 ){//エラーチェック
												_ASSERT( 0 );//エラーダイアログ
									};
							}
					};
					break;
				}
				/* ********* */
				/* ********* */
				case 1:{//弾薬のメニュー
						for(int i=0; i<2; i++){
								for(int j=0; j<2; j++){
										SpritePos4.x = 280+(j*160.0f);/**/SpritePos4.y = 100+(i*90.0f);
										ech = E3DRenderSprite( BackPack_Ammo[Counter][0], 1, 1, SpritePos4);//上部の白いバー
										if(ech != 0 ){//エラーチェック
													_ASSERT( 0 );//エラーダイアログ
										};
										Counter++;

										/*もしマウスの下が画像なら*/
										if(( 280 + ( j*160.0f ) < System::MousePos.x ) && ( System::MousePos.x < 408 + ( j*160.0f ))
												&& ( 120 + ( i*90.0f ) < System::MousePos.y ) && ( System::MousePos.y < 190 + ( i*90.0f ))){
													ItemNumber = Counter - 1;//カーソルと重なっていた画像のIDを代入
										}
								}
						};

						if( ItemNumber != -1 ){//もし、説明バーを表示させないといけないならば
								if( System::MousePos.x + 256 < 640){//バーが右にはみ出ないのなら
										SpritePos5.x = float( System::MousePos.x); /**/ SpritePos5.y = float( System::MousePos.y);
										ech = E3DRenderSprite( MenuSpriteIDs[4], 1, 1, SpritePos5);//上部の白いバー
										if(ech != 0 ){//エラーチェック
													_ASSERT( 0 );//エラーダイアログ
										};
								}
								else{//バーが右にはみ出るのなら
										SpritePos5.x = float( System::MousePos.x - 256); /**/ SpritePos5.y = float( System::MousePos.y);
										ech = E3DRenderSprite( MenuSpriteIDs[5], 1, 1, SpritePos5);//上部の白いバー
										if(ech != 0 ){//エラーチェック
													_ASSERT( 0 );//エラーダイアログ
										};
								}
						};
						break;
				}
				/* ********* */
				/* ********* */
				case 2:{//回復系のメニュー
						for(int i=0; i<2; i++){
								for(int j=0; j<2; j++){
										SpritePos4.x = 280+(j*160.0f);/**/SpritePos4.y = 100+(i*80.0f);
										ech = E3DRenderSprite( BackPack_Recovery[Counter][0], 1, 1, SpritePos4);//上部の白いバー
										if(ech != 0 ){//エラーチェック
													_ASSERT( 0 );//エラーダイアログ
										};
										Counter++;

										/*もしマウスの下が画像なら*/
										if(( 280 + ( j*160.0f ) < System::MousePos.x ) && ( System::MousePos.x < 408 + ( j*160.0f ))
												&& ( 120 + ( i*80.0f ) < System::MousePos.y ) && ( System::MousePos.y < 190 + ( i*80.0f ))){
													ItemNumber = Counter - 1;//カーソルと重なっていた画像のIDを代入
										}
								}
						};

						//5個目のアイテムを表示させる
						SpritePos4.x = 280+(0*160.0f);/**/SpritePos4.y = 100+(2*80.0f);
						ech = E3DRenderSprite( BackPack_Ammo[Counter][0], 1, 1, SpritePos4);//上部の白いバー
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
						};

						/*もしマウスの下が画像なら*/
						if(( 280 + ( 0*160.0f ) < System::MousePos.x ) && ( System::MousePos.x < 408 + ( 0*160.0f ))
							&& ( 120 + ( 2*80.0f ) < System::MousePos.y ) && ( System::MousePos.y < 190 + ( 2*80.0f ))){
										ItemNumber = 4;//カーソルと重なっていた画像のIDを代入
						}

						/**/
						///
						/**/




						if( ItemNumber != -1 ){//もし、説明バーを表示させないといけないならば
								if( System::MousePos.x + 256 < 640){//バーが右にはみ出ないのなら
										SpritePos5.x = float( System::MousePos.x); /**/ SpritePos5.y = float( System::MousePos.y);
										ech = E3DRenderSprite( MenuSpriteIDs[4], 1, 1, SpritePos5);//上部の白いバー
										if(ech != 0 ){//エラーチェック
													_ASSERT( 0 );//エラーダイアログ
										};
								}
								else{//バーが右にはみ出るのなら
										SpritePos5.x = float( System::MousePos.x - 256); /**/ SpritePos5.y = float( System::MousePos.y);
										ech = E3DRenderSprite( MenuSpriteIDs[5], 1, 1, SpritePos5);//上部の白いバー
										if(ech != 0 ){//エラーチェック
													_ASSERT( 0 );//エラーダイアログ
										};
								}
						};
						break;
				 }
			}
			




			E3DEndSprite();//スプライト描画の終了

			/* ////////////////////////// */
			// 以下、文字の表示を行います
			/* ////////////////////////// */

			PutBackPackText( &ChoseItem, &ExitFlag);


			//武器の名前を表示させます
			if( ItemNumber != -1) PutItemName( ChoseItem, ItemNumber);

			//最後に説明文を表示させます
			if( ItemNumber != -1) PutItemDescript( ChoseItem, ItemNumber);


			/*ここまでで画面描画準備終了*/
			E3DEndScene();
			ech = E3DPresent( System::scid1);
			if(ech != 0){//エラーチェック
						_ASSERT(0);//エラーダイアログを表示
			};


			if( ExitFlag == 1 ){//もしゲームループを抜けてOKなら
						break;//ループを抜ける
			}

	}while(WM_QUIT != System::msg.message);


	System::KeyRenewal(1);//自動終了を行わないようにするための、キーチェック


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

					/*文字"ポーズメニュー"の描画を行います*/
					TextPos.x = 440;/**/TextPos.y = 5;
					E3DDrawTextByFontID( System::scid1, TextID[0], TextPos, "ポーズメニュー", AlfaColor1);

					/*文字"バックパック"の描画を行います*/
					TextPos.x = 440;/**/TextPos.y = 5;
					E3DDrawTextByFontID( System::scid1, TextID[0], TextPos, "バックパック", AlfaColor2);

					E3DEndScene();
					E3DPresent(System::scid1);

					System::MsgQ(30);//メッセージループ

			
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

					/*文字"ポーズメニュー"の描画を行います*/
					TextPos.x = 440;/**/TextPos.y = 5;
					E3DDrawTextByFontID( System::scid1, TextID[0], TextPos, "ポーズメニュー", AlfaColor1);

					/*文字"バックパック"の描画を行います*/
					TextPos.x = 440;/**/TextPos.y = 5;
					E3DDrawTextByFontID( System::scid1, TextID[0], TextPos, "バックパック", AlfaColor2);

					E3DEndScene();
					E3DPresent(System::scid1);

					System::MsgQ(30);//メッセージループ
		
	}/*ここまで*/





	return 0;
}

