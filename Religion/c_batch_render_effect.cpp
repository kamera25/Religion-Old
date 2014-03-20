/*ここでは、モデルやスプライトの描画に必要な情報を収集、また描画で必要な
//関数を自動的に実行することができるようにするためのクラスコードファイル
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "c_batch_preparat.h"//描画に必要なクラスの宣言ヘッダファイル


/* バンプマップを有効/無効にします */
int Batch_Render::BatchEnableBumpMap( const int BumpFlag){

	/*変数の初期化*/
	int ech = 0;//エラーチェック用の確認変数

	ech = E3DEnableBumpMap( BumpFlag );
	if( ech != 0){
			_ASSERT( 0 );
	};

	BumpMapFlag = BumpFlag;

	return 0;
}

/* 影を作成するために関係する処理を行ないます */
int Batch_Render::BatchCreateShadow(){

	/* 変数の初期化 */
	int ech = 0;// エラーチェック変数
	int ShadowCRTFlug = 0;// 影を描画するテクスチャが作られたかどうか
	const D3DXVECTOR3 ldir1( -1.0, -1.0, -1.0);
	const SIZE TextureSize = { 1028, 1028};

	// Zバッファのバイアスを設定
	ech = E3DSetShadowBias( 0.005f);
	if( ech != 0){
			_ASSERT( 0 );
	};

	// 影の方向を指定します
	ech = E3DSetShadowMapLightDir( ldir1);
	if( ech != 0){
			_ASSERT( 0 );
	};


	// テクスチャの作成
	ech = E3DCreateRenderTargetTexture( TextureSize, D3DFMT_A8R8G8B8, &ShadowScid, &ShadowTexture, &ShadowCRTFlug);
	if( ech != 0){
			_ASSERT( 0 );
	};

	if( ShadowCRTFlug == 1){// 作成に成功したら
			ShadowFlag = 1;
	}



	return 0;
}