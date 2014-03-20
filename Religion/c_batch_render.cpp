/*ここでは、モデルやスプライトの描画に必要な情報を収集、また描画で必要な
//関数を自動的に実行することができるようにするためのクラスコードファイル
*/

#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "c_batch_preparat.h"//描画に必要なクラスの宣言ヘッダファイル


/*コンストラクタ、ステージやプレイヤークラスを元に情報を収集、構成します*/
Batch_Render::Batch_Render( const PlayerChara *PcC, const Stage *StgC, const Enemy *EneC, 
								const Camera *Cam)
{

	/* //////////////////////////////////// */
	// まずはじめにすべての変数を初期化します。
	/* //////////////////////////////////// */
	int ech = 0;//エラーチェック用の確認変数 
	const E3DCOLOR4UC AlfaColor = { 100,255,255,255};//カラー構造体の半透過のデータ
	char loadname[256] = "";//読み込む先のパスの文字列変数
	
	BumpMapFlag = 0;
	ShadowFlag = 0;

	/*描画、視野角データの構築を行います*/
	BatchReset( PcC, StgC, EneC, Cam);


	/* /////////////////////////////////////////////////////// */
	//次にスプライトのロードを行います、同時にデータも代入します
	/* /////////////////////////////////////////////////////// */

	/*カーソル画像のロードを行う 配列は[0]番*/
	wsprintf( loadname, "%s\\data\\img\\carsol.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteIDs[0]);//カーソルのロード
	_ASSERT( ech != 1 );//エラーチェック

	/*半透明化します*/
	ech = E3DSetSpriteARGB( SpriteIDs[0], AlfaColor);
	_ASSERT( ech != 1 );//エラーチェック
	/*データの格納*/
	SpriteData[0][0] = 0.1f;//X倍率（1/10）
	SpriteData[0][1] = 0.1f;//Y倍率（1/10）
	SpriteData[0][4] = 0.0f;//Z座標奥行（一番手前）


	/*右ステータス画像の背景のロードを行う 配列は[1]番*/
	wsprintf( loadname, "%s\\data\\img\\parameter\\parameter3.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteIDs[1]);//カーソルのロード
	_ASSERT( ech != 1 );//エラーチェック
	/*データの格納*/
	SpriteData[1][0] = 1.0f;//X倍率
	SpriteData[1][1] = 1.0f;//Y倍率
	SpriteData[1][2] = 0.0f;//X座標
	SpriteData[1][3] = 390.0f;//Y座標
	SpriteData[1][4] = 0.0f;//Z座標奥行（一番手前）


	/*右ステータス画像の背景のロードを行う 配列は[2]番*/
	wsprintf( loadname, "%s\\data\\img\\parameter\\parameter4.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteIDs[2]);//カーソルのロード
	_ASSERT( ech != 1 );//エラーチェック
	/*データの格納*/
	SpriteData[2][0] = 1.0f;//X倍率
	SpriteData[2][1] = 1.0f;//Y倍率
	SpriteData[2][2] = 506.0f;//X座標
	SpriteData[2][3] = 390.0f;//Y座標
	SpriteData[2][4] = 0.0f;//Z座標奥行（手前）


	/*左HPのバーのロードを行う 配列は[3]番*/
	wsprintf( loadname, "%s\\data\\img\\parameter\\hpber.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteIDs[3]);//カーソルのロード
	_ASSERT( ech != 1 );//エラーチェック
	/*データの格納*/
	SpriteData[3][0] = 100.0f;//X倍率
	SpriteData[3][1] = 1.0f;//Y倍率
	SpriteData[3][2] = 24.0f;//X座標
	SpriteData[3][3] = 412.0f;//Y座標
	SpriteData[3][4] = 0.0f;//Z座標奥行（手前）


	/*左スタミナのバーのロードを行う 配列は[4]番*/
	wsprintf( loadname, "%s\\data\\img\\parameter\\stnber.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteIDs[4]);//カーソルのロード
	_ASSERT( ech != 1 );//エラーチェック
	/*データの格納*/
	SpriteData[4][0] = 100.0f;//X倍率
	SpriteData[4][1] = 0.5f;//Y倍率
	SpriteData[4][2] = 24.0f;//X座標
	SpriteData[4][3] = 435.0f;//Y座標
	SpriteData[4][4] = 0.0f;//Z座標奥行（手前）


	/*右弾薬数のバーのロードを行う 配列は[5]番*/
	wsprintf( loadname, "%s\\data\\img\\parameter\\ammber.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteIDs[5]);//カーソルのロード
	_ASSERT( ech != 1 );//エラーチェック
	/*データの格納*/
	SpriteData[5][0] = 100.0f;//X倍率
	SpriteData[5][1] = 0.8125f;//Y倍率(13pix)
	SpriteData[5][2] = 530.0f;//X座標
	SpriteData[5][3] = 407.0f;//Y座標
	SpriteData[5][4] = 0.0f;//Z座標奥行（手前）


	/*右マガジン数のバーのロードを行う 配列は[6]番*/
	wsprintf( loadname, "%s\\data\\img\\parameter\\magber.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteIDs[6]);//カーソルのロード
	_ASSERT( ech != 1 );//エラーチェック
	/*データの格納*/
	SpriteData[6][0] = 100.0f;//X倍率
	SpriteData[6][1] = 0.8125f;//Y倍率(13pix)
	SpriteData[6][2] = 530.0f;//X座標
	SpriteData[6][3] = 436.0f;//Y座標
	SpriteData[6][4] = 0.0f;//Z座標奥行（手前）


	/*左ステータス画像のロードを行う 配列は[7]番*/
	wsprintf( loadname, "%s\\data\\img\\parameter\\parameter1.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteIDs[7]);//カーソルのロード
	_ASSERT( ech != 1 );//エラーチェック
	/*データの格納*/
	SpriteData[7][0] = 1.0f;//X倍率
	SpriteData[7][1] = 1.0f;//Y倍率
	SpriteData[7][2] = 0.0f;//X座標
	SpriteData[7][3] = 390.0f;//Y座標
	SpriteData[7][4] = 0.0f;//Z座標奥行（一番手前）


	/*右ステータス画像のロードを行う 配列は[8]番*/
	wsprintf( loadname, "%s\\data\\img\\parameter\\parameter2.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteIDs[8]);//カーソルのロード
	_ASSERT( ech != 1 );//エラーチェック
	/*データの格納*/
	SpriteData[8][0] = 1.0f;//X倍率
	SpriteData[8][1] = 1.0f;//Y倍率
	SpriteData[8][2] = 506.0f;//X座標
	SpriteData[8][3] = 390.0f;//Y座標
	SpriteData[8][4] = 0.0f;//Z座標奥行（一番手前）


	/*兵器に関する画像の設定、配列は[9]番*/
	SpriteData[9][0] = 1.0f;//X倍率
	SpriteData[9][1] = 1.0f;//Y倍率
	SpriteData[9][2] = 506.0f;//X座標
	SpriteData[9][3] = 326.0f;//Y座標
	SpriteData[9][4] = 0.0f;//Z座標奥行（一番手前）


};

/* デストラクタ、スプライトを削除します */
Batch_Render::~Batch_Render(){

	/*変数の初期化*/
	int ech = 0;//エラーチェック用の確認変数 
		
	for(int i=0; i<9; i++){//ロードしたスプライトの削除
			ech = E3DDestroySprite( SpriteIDs[i]);
			_ASSERT( ech != 1 );//エラーチェック
	}

	if( ShadowFlag == 1){// 影用レンダーテクスチャが生成されているなら
			ech = E3DDestroyRenderTargetTexture( ShadowScid, ShadowTexture);
			_ASSERT( ech != 1 );//エラーチェック
	}

}