//インクルードするファイル↓

#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <usercoef.h>//Easy3Dで必要な追加ヘッダ
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "resource1.h"//リソースファイルとかの関連付けヘッダ
#include <string.h>//文字列操作で必要

#include "difine.h"


//グローバル変数の宣言



//ゲーム中でのポーズメニューでのループ

int Posemenu(int *modsc){


			int ech;
			static int selemd = 0;
			D3DXVECTOR3 ldpos1( 0.0, -25.0, 0.0);
			D3DXVECTOR3 ldpos2( 0.0, -60.0, 0.0);
			D3DXVECTOR3 ldpos3( 380.0, 45.0, 0.0);
			E3DCOLOR4UC col= { 255,255,255,255};//白色の選ばれていない色
			E3DCOLOR4UC selcol= { 255,200,220,20};//黄色の選ばれている色
			POINT fontpos;
			POINT moupos;

			E3DBeginScene(scid1,0);
			E3DBeginSprite();
			
			ech = E3DRenderSprite( lddata[15], 640.0/1024.0, 480.0/512.0, ldpos1);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			};
			
			ech = E3DRenderSprite( lddata[16], 1, 1, ldpos2);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			};


			ech = E3DRenderSprite( lddata[17], 1, 1, ldpos3);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			};

			E3DEndSprite();


			//文字
			fontpos.x = 440;
			fontpos.y = 5;
			E3DDrawTextByFontID( scid1, FontID[0], fontpos, "ポーズメニュー", col);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			};



			fontpos.x = 100;


			fontpos.y = 140;//40ずつ下げる
			E3DDrawTextByFontID( scid1, FontID[1], fontpos, "ゲームに戻る", col);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			};

			fontpos.y = 180;//40ずつ下げる
			E3DDrawTextByFontID( scid1, FontID[1], fontpos, "バックパック", col);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			};

			fontpos.y = 220;
			E3DDrawTextByFontID( scid1, FontID[1], fontpos, "オプション", col);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			};

			fontpos.y = 260;
			E3DDrawTextByFontID( scid1, FontID[1], fontpos, "ミッションを中断する", col);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			};

			fontpos.y = 300;
			E3DDrawTextByFontID( scid1, FontID[1], fontpos, "ゲームを終了する", col);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			};


			//以下、メニューでの処理

			GetCursorPos( &moupos );//マウス座標を格納

			moupos.x = moupos.x - recwindow.left;//ウィンドウX座標の取得
			moupos.y = moupos.y - recwindow.top;//ウィンドウY座標の取得

					if((100<moupos.x)&&(moupos.x<250)){	

								if((160<moupos.y)&&(moupos.y<190)){//マウス座標が「ゲームに戻る」の上なら
														selemd = 1;	//選んでるモードを4にする
														fontpos.x = 100;
														fontpos.y = 140;
														E3DDrawTextByFontID( scid1, FontID[1], fontpos, "ゲームに戻る", selcol);//選択されている文字にする
														if(ech != 0 ){//エラーチェック
																_ASSERT( 0 );//エラーダイアログ
																return 1;//問題ありで終了
														};

														if(keyin[9] == 1){//右クリックを押したら
																*modsc = 3;//モードチェンジをする
														}
								}

								if((320<moupos.y)&&(moupos.y<350)){//マウス座標が「ゲームを終了する」の上なら
														selemd = 5;	//選んでるモードを4にする
														fontpos.x = 100;
														fontpos.y = 300;
														E3DDrawTextByFontID( scid1, FontID[1], fontpos, "ゲームを終了する", selcol);//選択されている文字にする
														if(ech != 0 ){//エラーチェック
																_ASSERT( 0 );//エラーダイアログ
																return 1;//問題ありで終了
														};

														if(keyin[9] == 1){//右クリックを押したら
																PostQuitMessage(0);//ゲームを終了する
														}
								}
					}

			E3DEndScene();
			E3DPresent(scid1);



			return 0;
}