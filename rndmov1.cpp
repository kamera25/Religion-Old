#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <usercoef.h>//Easy3Dで必要な追加ヘッダ
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "resource1.h"//リソースファイルとかの関連付けヘッダ
#include <string.h>//文字列操作で必要
#include <stdio.h>//いろいろな関数のヘッダ

/////////////////////////////////////

//ユーザーヘッダファイル

#include "difine.h"



//ロード画面の表示をします。
int loadimg(){

			int ech;
			static int ldimg;
			static int then = 0;
			char loadname[MAX_PATH] = "";

			if(then == 0){
						wsprintf( loadname, "%s\\img\\oth\\loding.png", pat);
						ech = E3DCreateSprite( loadname, 0, 0, &ldimg);
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
									return 1;//問題ありで終了
						};
						then = 0;
			};



			E3DBeginScene(scid1,0);
			E3DBeginSprite();

			D3DXVECTOR3 ldpos( 0.0, -25.0, 0.0);
			ech = E3DRenderSprite( ldimg, 640.0/1024.0, 480.0/512.0, ldpos);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			};

			E3DEndSprite();
			E3DEndScene();
			E3DPresent(scid1);
			
			return 0;
}


//オープニングムービーのレンダリングをします。
int opning(){

	char loadname[MAX_PATH] = "";
	int ech;
	static int ldflg = 0;
	static int bgimg = 0;
	static int log1 = 0;
	static int log2 = 0;
	static int opimg1 = 0;
	static int i = 0;

	if(ldflg == 0){



		wsprintf( loadname, "%s\\img\\oth\\black.png", pat);
		ech = E3DCreateSprite( loadname, 0, 0, &bgimg);
		if(ech != 0 ){//エラーチェック
						_ASSERT( 0 );//エラーダイアログ
						return 1;//問題ありで終了
		};

		wsprintf( loadname, "%s\\img\\oth\\cslog.png", pat);
		ech = E3DCreateSprite( loadname, 0, 0, &log1);
		if(ech != 0 ){//エラーチェック
						_ASSERT( 0 );//エラーダイアログ
						return 1;//問題ありで終了
		};

		wsprintf( loadname, "%s\\img\\oth\\oudev.png", pat);
		ech = E3DCreateSprite( loadname, 0, 0, &log2);
		if(ech != 0 ){//エラーチェック
						_ASSERT( 0 );//エラーダイアログ
						return 1;//問題ありで終了
		};

		wsprintf( loadname, "%s\\img\\ops\\op2.jpg", pat);
		ech = E3DCreateSprite( loadname, 0, 0, &opimg1);
		if(ech != 0 ){//エラーチェック
						_ASSERT( 0 );//エラーダイアログ
						return 1;//問題ありで終了
		};
		ldflg = 1;
	}

	//ここからムービーを流しますよ

	if(i <= 153){

			int alf = 0;
			
			//透過度の設定
			if(i <= 51){
						alf = i * 5;
						E3DCOLOR4UC col= {alf,255,255,255};
						E3DSetSpriteARGB(log1, col);
			}
			if(50 < i && i < 120){
						E3DCOLOR4UC col= {255,255,255,255};
						E3DSetSpriteARGB(log1, col);
			}
			if(i >= 120){
						alf = 255 +(i * 5 * -1);
						E3DCOLOR4UC col= {alf,255,255,255};
						E3DSetSpriteARGB(log1, col);
			}


			E3DBeginScene(scid1,0);
			E3DBeginSprite();

			D3DXVECTOR3 ldpos1( 0.0, 0.0, 0.0);
			ech = E3DRenderSprite( bgimg, 640.0/1024.0, 480.0/512.0, ldpos1);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			};

			D3DXVECTOR3 ldpos2( 120.0, 120.0, 0.0);
			ech = E3DRenderSprite( log1, 1.0, 1.0, ldpos2);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			};

			E3DEndSprite();
			E3DEndScene();
			E3DPresent(scid1);
	}


	if(153 < i && i <= 305){

			int cnti = i - 153;
			int alf = 0;
			
			//透過度の設定
			if(i <= 204){
						alf = cnti * 5;
						E3DCOLOR4UC col= {alf,255,255,255};
						E3DSetSpriteARGB(log2, col);
			}
			if(204 < i && i < 274){
						E3DCOLOR4UC col= {255,255,255,255};
						E3DSetSpriteARGB(log2, col);
			}
			if(i >= 274){
						alf = 255 +(cnti * 5 * -1);
						E3DCOLOR4UC col= {alf,255,255,255};
						E3DSetSpriteARGB(log2, col);
			}


			E3DBeginScene(scid1,0);
			E3DBeginSprite();

			D3DXVECTOR3 ldpos1( 0.0, 0.0, 0.0);
			ech = E3DRenderSprite( bgimg, 640.0/1024.0, 480.0/512.0, ldpos1);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			};

			D3DXVECTOR3 ldpos2( 270.0, 230.0, 0.0);
			ech = E3DRenderSprite( log2, 1.0, 1.0, ldpos2);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			};

			E3DEndSprite();
			E3DEndScene();
			E3DPresent(scid1);
	}


	if(307 < i && i <= 460){

			int cnti = i - 307;
			int alf;
			
			//透過度の設定
			if(i <= 358){
						alf = cnti * 5;
						E3DCOLOR4UC col= {alf,255,255,255};
						E3DSetSpriteARGB(opimg1, col);
			}
			if(358 < i && i < 428){
						E3DCOLOR4UC col= {255,255,255,255};
						E3DSetSpriteARGB(opimg1, col);
			}
			if(i >= 438){
						alf = 255 +(cnti * 5 * -1);
						E3DCOLOR4UC col= {alf,255,255,255};
						E3DSetSpriteARGB(opimg1, col);
			}


			E3DBeginScene(scid1,0);
			E3DBeginSprite();

			D3DXVECTOR3 ldpos1( 0.0, 0.0, 0.0);
			ech = E3DRenderSprite( bgimg, 640.0/1024.0, 480.0/512.0, ldpos1);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			};

			D3DXVECTOR3 ldpos2( 0.0, 0.0, 0.0);
			ech = E3DRenderSprite( opimg1, 640.0/1024.0, 480.0/512.0, ldpos2);
			if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
			};

			E3DEndSprite();
			E3DEndScene();
			E3DPresent(scid1);
	}

	keyout( 0, 0);
	if((470 == i)||(keyin[0] == 1)){//終了
								i=0;
								return 2; 
	}



	i++;
			

	return 0;
}