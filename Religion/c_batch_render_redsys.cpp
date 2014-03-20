/*ここでは、モデルやスプライトの描画に必要な情報を収集、また描画で必要な
//関数を自動的に実行することができるようにするためのクラスコードファイル
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "c_batch_preparat.h"//描画に必要なクラスの宣言ヘッダファイル

/* まとめられたデータを描画します。 */
int Batch_Render::BatchRender( const int SceneEndFlg){

	int ech = 0;// エラーチェック用の確認変数
	int i = 0;
	int Render_hsids[30];
	vector<Model>::iterator it;// イテレータ

	for( it = Mdl.begin(); it != Mdl.end(); it++ ){
		
			/*変数の初期化*/
			if(( ((*it).ID != 0)) && ( (*it).ViewFlag == true)){
					Render_hsids[i] = (*it).ID;
					i++;
			}
	}

	switch(ShadowFlag){
			case 0:{// レンダリング(ノーマル)
					ech = E3DRenderBatch( System::scid1, &Render_hsids[0], 30, 1, 0);
					_ASSERT( ech !=1 );//エラーダイアログを表示

					break;
		    }
			case 1:{// 影付きレンダリング
					ech = E3DRenderWithShadow( System::scid1, ShadowScid, ShadowTexture, &Render_hsids[0], 30, 0);
					_ASSERT( ech != 1 );//エラーダイアログを表示

					break;
		    }
	}


	/*
	//描画の終了処理
	*/
	if( SceneEndFlg == 1){
			ech = E3DEndScene();
			_ASSERT( ech != 1 );//エラーチェック
	}

	return 0;
};

/* まとめられたスプライトをレンダリングするための関数です */
int Batch_Render::BatchSpriteRender( const int SceneEndFlg){

	/*変数の初期化*/
	int ech = 0;//エラー確認変数の初期化
	vector<Sprite>::iterator it;// イテレータ

	/*
	//描画処理の開始
	*/

	ech = E3DBeginScene( System::scid1, 1, -1);
	_ASSERT( ech != 1 );//エラーダイアログを表示

	ech = E3DBeginSprite();
	_ASSERT( ech != 1 );//エラーダイアログを表示


	/*
	//描画を行います、ループ中に描画されます
	*/

	for( it = Spt.begin(); it != Spt.end(); it++ ){
		
			/*変数の初期化*/
			if( (*it).ViewFlag == true){
					D3DXVECTOR3 ScreenPos( (*it).X, (*it).Y, (*it).Z);//描画位置を指定する構造体
					ech = E3DRenderSprite( (*it).ID, (*it).MagX, (*it).MagY, ScreenPos);
					_ASSERT( ech != 1 );//エラーダイアログを表示
			}
	}

	ech = E3DEndSprite();
	_ASSERT( ech != 1 );//エラーダイアログを表示


	/*
	//描画の終了処理
	*/
	if( SceneEndFlg == 1){
	
		ech = E3DEndScene();	
		_ASSERT( ech != 1 );//エラーダイアログを表示
	}


	return 0;
}

/* バックバッファの内容を、プライマリバッファに転送します */
int Batch_Render::Batch_Present(){
	/* 変数の初期化 */
	int ech = 0;//エラーチェック用の確認変数 

	/* バックバッファの内容を、プライマリバッファに転送します */ 
	ech = E3DPresent( System::scid1);
	_ASSERT( ech != 1 );//エラーダイアログを表示


	return 0;
}

/*視野角内チェックが必要なデータ（描画するデータも含む）をチェックします*/
int Batch_Render::BatchChkInView(){

	int garbage = 0;//いらない変数を格納します
	int ech = 0;//エラーチェック用の確認変数 
	vector<Model>::iterator it;// イテレータ


//	for(int i=0; i<40; i++){
		/*視野角内のチェックを行います
		if(( ChkIn_hsids[i] != 0) && (ChkIn_hsids[i] != -1 )){//空のモデルデータ以外なら
			ech = E3DChkInView( System::scid1, ChkIn_hsids[i], &garbage);
			_ASSERT( ech != 1 );//エラーチェック
		}
	};
	*/

	for( it = Mdl.begin(); it != Mdl.end(); it++){
		/*視野角内のチェックを行います*/
		if( (*it).ID != 0 ){//空のモデルデータ以外なら
			ech = E3DChkInView( System::scid1, (*it).ID, &garbage);
			_ASSERT( ech != 1 );//エラーチェック
		}
	};


	return 0;
};
