//インクルードするファイル↓

#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <usercoef.h>//Easy3Dで必要な追加ヘッダ
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "resource1.h"//リソースファイルとかの関連付けヘッダ
#include <string.h>//文字列操作で必要

#include "difine.h"


//グローバル変数の宣言




int SpriteRed(){

	int ech;
	int usewpno;
	int usewpkind;
	char metor[MAX_PATH] = "";


	D3DXVECTOR3 ldpos1( 0.0, 390.0, 0.0);
	D3DXVECTOR3 ldpos2( 508.0, 325.0, 0.0);
	D3DXVECTOR3 ldpos3( 508.0, 390.0, 0.0);
	D3DXVECTOR3 ldpos4( 23.0, 413.0, 0.0);
	D3DXVECTOR3 ldpos5( 23.0, 432.0, 0.0);
	D3DXVECTOR3 ldpos6( 532.0, 405.0, 0.0);
	D3DXVECTOR3 ldpos7( 532.0, 434.0, 0.0);
	D3DXVECTOR2 ftpos1( 555.0, 393.0);
	D3DXVECTOR2 ftpos2( 590.0, 395.0);
	D3DXVECTOR2 ftpos3( 555.0, 423.0);
	D3DXVECTOR2 ftpos4( 590.0, 425.0);
	D3DXVECTOR2 ftpos5( 30.0, 392.0);



	

	ech = E3DBeginScene( scid1,1);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終
	};


  E3DBeginSprite();

	//本編で使う画像レンダリング

	ech = E3DRenderSprite( lddata[12], 1.0, 1.0, ldpos1);//バックHP&STパロメーター
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終
	};

	ech = E3DRenderSprite( lddata[8], (double)Iinfo[3][1]/100.0*100.0, 1.0, ldpos4);//HPバー
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終
	};

	ech = E3DRenderSprite( lddata[9], (double)Iinfo[3][2]/100.0*100.0, 1.0, ldpos5);//STAMINAバー
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終
	};

	ech = E3DRenderSprite( lddata[6], 1.0, 1.0, ldpos1);//HP&STパロメーター
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終
	};


	if(Iinfo[3][3] != -1){//素手でなかったら

			usewpkind = Iinfo[(Iinfo[3][3])][0];//使ってる武器の種類
			usewpno = Iinfo[(Iinfo[3][3])][1];//使ってる武器のナンバー

			ech = E3DRenderSprite( lddata[13], 1.0, 1.0, ldpos3);//バックAMM&MAGパロメーター
			if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
							return 1;//問題ありで終
			};
			

			ech = E3DRenderSprite( lddata[10], (double)Iinfo[ (Iinfo[3][3]) ][3] / wpitem[usewpkind][usewpno][5]*100.0, 1.0, ldpos6);//AMMOバー
			if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
							return 1;//問題ありで終
			};

			ech = E3DRenderSprite( lddata[11], (double)Iinfo[ (Iinfo[3][3]) ][4] / wpitem[usewpkind][usewpno][6]*100.0, 1.0, ldpos7);//MAGバー
			if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
							return 1;//問題ありで終
			};


			ech = E3DRenderSprite( wpitem[usewpkind][usewpno][0], 1.0, 1.0, ldpos2);//銃選択中IMGの配置
			if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
							return 1;//問題ありで終
			};

			ech = E3DRenderSprite( lddata[7], 1.0, 1.0, ldpos3);//AMM&MAGパロメーター
			if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
							return 1;//問題ありで終
			};

	}

	E3DEndSprite();

	//文字のレンダリング

	if(Iinfo[3][3] != -1){//素手でなかったら

					E3DCOLOR4UC col1= { 0,255,255,255};
					E3DCOLOR4UC col2= { 0,255,255,255};
					E3DCOLOR4UC col3= { 0,255,255,255};


					if(Iinfo[ (Iinfo[3][3]) ][3] <= (wpitem[usewpkind][usewpno][5] / 2)){//AMMが半分になったら
										col2.b = 0;
										col2.g = 255;
										col2.r = 255;
					}
					if(Iinfo[ (Iinfo[3][3]) ][3] == 0){//AMMが0になったら
										col2.b = 0;
										col2.g = 0;
										col2.r = 255;
					}
					if(Iinfo[ (Iinfo[3][3]) ][3] == wpitem[usewpkind][usewpno][5] + 1){//AMMが+1されたら
										col2.b = 255;
										col2.g = 150;
										col2.r = 0;
					}


					wsprintf( metor, "%d", (Iinfo[ (Iinfo[3][3]) ][3]));//持ってる武器の今のAMM
					E3DDrawText( ftpos1, 1.4, col2, metor);
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
								return 1;//問題ありで終
					};

					wsprintf( metor, "%d", (wpitem[usewpkind][usewpno][5]));//持ってる武器の最大AMM
					E3DDrawText( ftpos2, 1.5, col1, metor);
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
								return 1;//問題ありで終
					};

					wsprintf( metor, "%d", Iinfo[ (Iinfo[3][3]) ][4]);//持ってる武器のMAG
					E3DDrawText( ftpos3, 1.4, col1, metor);
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
								return 1;//問題ありで終
					};

					wsprintf( metor, "%d", (wpitem[usewpkind][usewpno][6]));//持ってる武器の最大MAG
					E3DDrawText( ftpos4, 1.5, col1, metor);
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
								return 1;//問題ありで終
					};
	}

	if(Iinfo[3][0] == 0){
						E3DCOLOR4UC col= { 0,40,40,40};
						wsprintf( metor, "Arty" );
						E3DDrawText( ftpos5, 1.35, col, metor);
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
									return 1;//問題ありで終
						};
	}

	
	ech = E3DEndScene();
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
				return 1;//問題ありで終		
	};
	

	E3DEndScene();



	return 0;
}




//ゲームの核の部分です。

int Ops1Render(){
	
	int render[15];
	int ech;

	render[0] = Iinfo[(Iinfo[3][3])][2];
	render[1] = grd1;
	render[2] = modelId[0];
	render[3] = modelId[1];
	render[3] = modelId[10];
	render[5] = modelId[11];
	render[6] = Eneinfo[0][2];//テストです！



	ech = E3DRenderBatch( scid1, &render[0], 8, 1, 0);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終
					
	};

	return 0;

}

int Ops1Main(){

	int ech;
	int a;
	static int subjemode = 0;//主観モード変数
	static int Weaponmode = 0;//武器変更モード変数


	//銃関係のシステム

	if(keyin[14] == 1){//もし主観モードチェンジキーが押されたら
					Iinfo[3][4]++;
					if(Iinfo[3][4] == 1){
								SetCursorPos( recwindow.left + 320, recwindow.top + 240);//マウスをウィンドウ真ん中に設置
					}
					if(Iinfo[3][4] == 2){
								Iinfo[3][4] = 0;
					}
	}

	if(keyin[7] == 1){//もし武器交換キーが押されたら(z)
					Iinfo[3][3]++;
					if(Iinfo[3][3] == 1){
								Iinfo[3][3] = -1;//素手の状態に戻す
					}
	}





	//E3DChkInViewでチェック!

	ech = E3DChkInView( scid1, grd1,&a);//地面の当たり判定
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};
	ech = E3DChkInView( scid1, wal1,&a);//壁の当たり判定
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};
	ech = E3DChkInView( scid1, modelId[11],&a);//銃の当たり判定
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};
	ech = E3DChkInView( scid1, modelId[0],&a);//手の当たり判定
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};
	ech = E3DChkInView( scid1, modelId[1],&a);//アーティーの判定
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};
	ech = E3DChkInView( scid1, modelId[10],&a);//サブモデル1の判定
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};
	ech = E3DChkInView( scid1, modelId[12],&a);//サブモデル2の判定
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	ech = E3DChkInView( scid1, Eneinfo[0][2],&a);//！テストです！
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};


	if((Iinfo[3][3]) != -1){
				ech = E3DChkInView( scid1, Iinfo[(Iinfo[3][3])][2],&a);//所持している武器の判定
				if(ech != 0 ){//エラーチェック
						_ASSERT( 0 );//エラーダイアログ
						return 1;//問題ありで終了
				};
	}




	
	Lunchergun( Iinfo[3][4], Iinfo[3][4], 0);//一時的な処理、本編では括弧消し





	//画面のレンダリング
	Ops1Render();
	SpriteRed();

	E3DPresent(scid1);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};


	E3DSetBeforePos( modelId[12]);//移動モデルの前座標を取得
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};


	

	return 0;
}





//オペレーションモードの1番目の任務
int Ops1HQ(){

	int ech;
	static int loaddt = 0;//データのロード状況用の変数
	static int scmode = 0;//ゲームモードの確認変数

	if(loaddt == 0){

			ech = loadimg();//ロード画面を表示
			if(ech != 0){//エラーチェック
					_ASSERT(0);//エラーダイアログを表示
					return 1;//問題ありで関数終了
			};
			grdload( 0, 1, 2, 0);//地面をロード
			gunload( 0, 0, 0);//銃「M1911」をロード
			Eneload();//テスト、エネミーキューブをロード
			Iinfo[3][0] = 0;//自分のID
			Iinfo[3][1] = 75;//HP
			Iinfo[3][2] = 75;//スタミナ
			Iinfo[1][0] = -1;//サブ武器をなしに
			Iinfo[2][0] = -1;//グレネード武器をなしに
			Iinfo[3][3] = -1;//武器の種類を「素手」に
			Iinfo[3][4] = 0;//操作モードを「3人称」に

			loaddt++;

	}
	
	keyout( 0, 1);//キー入力を取得

	if(scmode == 0){//モードがゲームモードなら
					
					if(keyin[15] == 1){//もしポーズキーが押されて
									scmode = 1;
									int a = 250;
					}
					ech = Ops1Main();
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
								return 1;//問題ありで終了
					};

	}
	if(scmode == 1){//モードを切り替え中なら

			int static altime = 0;
			altime++;

			Ops1Render();//ゲーム画面をレンダリング

			E3DCOLOR4UC col= { 15*altime ,255,255,255};
			ech = E3DSetSpriteARGB( lddata[15], col);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			};
			ech = E3DSetSpriteARGB( lddata[16], col);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			};
			ech = E3DSetSpriteARGB( lddata[17], col);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			};

			E3DBeginScene(scid1,1);
			E3DBeginSprite();

			D3DXVECTOR3 ldpos1( 0.0, -25.0, 0.0);
			ech = E3DRenderSprite( lddata[15], 640.0/1024.0, 480.0/512.0, ldpos1);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			};
			D3DXVECTOR3 ldpos2( 0.0, -60.0, 0.0);
			ech = E3DRenderSprite( lddata[16], 1, 1, ldpos2);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			};

			D3DXVECTOR3 ldpos3( 380.0, 45.0, 0.0);
			ech = E3DRenderSprite( lddata[17], 1, 1, ldpos3);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			};

			E3DEndSprite();
			E3DEndScene();
			E3DPresent(scid1);

			if(altime == 17){
						scmode = 2;//モードを「ポーズメニューに」
						altime = 0;//タイムを初期化
			}

	}
	if(scmode == 2){//ポーズモードなら
					Posemenu(&scmode);
	}

	if(scmode == 3){//ポーズからゲームへ切り替え中なら

			int static altime = 17;
			altime--;

			Ops1Render();//ゲーム画面をレンダリング

			E3DCOLOR4UC col= { 15*altime ,255,255,255};
			ech = E3DSetSpriteARGB( lddata[15], col);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			};
			ech = E3DSetSpriteARGB( lddata[16], col);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			};
			ech = E3DSetSpriteARGB( lddata[17], col);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			};

			E3DBeginScene(scid1,1);
			E3DBeginSprite();

			D3DXVECTOR3 ldpos1( 0.0, -25.0, 0.0);
			ech = E3DRenderSprite( lddata[15], 640.0/1024.0, 480.0/512.0, ldpos1);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			};
			D3DXVECTOR3 ldpos2( 0.0, -60.0, 0.0);
			ech = E3DRenderSprite( lddata[16], 1, 1, ldpos2);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			};

			D3DXVECTOR3 ldpos3( 380.0, 45.0, 0.0);
			ech = E3DRenderSprite( lddata[17], 1, 1, ldpos3);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			};

			E3DEndSprite();
			E3DEndScene();
			E3DPresent(scid1);

			if(altime == 0){
						scmode = 0;//モードをゲーム本編に
						altime = 17;//タイムを初期化
			}

	}






	return 0;
}





