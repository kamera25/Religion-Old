/*ここでは、モデルやスプライトの描画に必要な情報を収集、また描画で必要な
//関数を自動的に実行することができるようにするためのクラスコードファイル
*/

#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするための
#include <string>
#include <map>
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ


#include "c_batch_preparat.h"//描画に必要なクラスの宣言ヘッダファイル
#include "clive.h"//敵やキャラの宣言ヘッダファイル



/*コンストラクタ、ステージやプレイヤークラスを元に情報を収集、構成します*/
Batch_Render::Batch_Render( const PlayerChara *PcC, const Stage *StgC, NPC_Head *NPC_H, 
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
	BatchReset( PcC, StgC, NPC_H, Cam);

					
	/* /////////////////////////////////////////////////////// */
	//次にスプライトのロードを行います、同時にデータも代入します
	/* /////////////////////////////////////////////////////// */

	/*カーソル画像のロードを行う 配列は[0]番*/
	LoadSprite_AddName( "data\\img\\cursol\\cursol1.png", "Cursol1", 0.7f, 0.7f, 0.0f, 0.0f, 0.0f, true);
	
	/*半透明化します*/
	SetSpriteAlpha( "Cursol1", AlfaColor);

	/* ////////////////// */
	// 左側関連のスプライト
	/* ///////////////// */

	/*左ステータス画像の背景のロードを行う*/
	LoadSprite( "data\\img\\parameter\\parameter_leftBG.png", 1.0f, 1.0f, 0.0f, 390.0f, 0.00002f, true);

	/*左HPのバーのロードを行う*/
	LoadSprite_AddName( "data\\img\\parameter\\hpber.png", "HPber", 100.0f, 1.0f, 24.0f, 412.0f, 0.00001f, true);

	/*左スタミナのバーのロードを行う*/
	LoadSprite_AddName( "data\\img\\parameter\\stnber.png", "Staminaber", 100.0f, 0.5f, 24.0f, 435.0f, 0.00001f, true);

	/*左ステータス画像のロードを行う*/
	LoadSprite( "data\\img\\parameter\\parameter_left.png", 1.0f, 1.0f, 0.0f, 390.0f, 0.0f, true);


	/* ////////////////// */
	// 右側関連のスプライト
	/* ///////////////// */

	/*右ステータス画像の背景のロードを行う*/
	LoadSprite( "data\\img\\parameter\\parameter_rightBG.png", 1.0f, 1.0f, 506.0f, 390.0f, 0.00002f, true);

	/*右弾薬数のバーのロードを行う*/
	LoadSprite_AddName( "data\\img\\parameter\\ammber.png", "Ammober", 100.0f, 0.8125f, 530.0f, 407.0f, 0.00001f, true);

	/*右マガジン数のバーのロードを行う*/
	LoadSprite_AddName( "data\\img\\parameter\\magber.png", "Magber",100.0f, 0.8125f, 530.0f, 436.0f, 0.00001f, true);

	/*右ステータス画像のロードを行う*/
	LoadSprite( "data\\img\\parameter\\parameter_right.png", 1.0f, 1.0f, 506.0f, 390.0f, 0.0f, true);










	/* ///////////////////////////////////////////////////
	/* PCクラスからの武器スプライトをIDから読み込みます */
	/* ///////////////////////////////////////////////////

	/* メインウェポン*/
	if( PcC->Wpn.Get_WeaponPointer(0) != NULL) LoadSpriteFromID( PcC->Wpn.Get_WeaponPointer(0)->Get_Sprite(), "MainWp", 1.0f, 1.0f, 506.0f, 326.0f, 0.0f, false);

	/* サブウェポン*/
	if( PcC->Wpn.Get_WeaponPointer(1) != NULL) LoadSpriteFromID( PcC->Wpn.Get_WeaponPointer(1)->Get_Sprite(), "SubWp", 1.0f, 1.0f, 506.0f, 326.0f, 0.0f, false);

	/* グレネード*/
	if( PcC->Wpn.Get_WeaponPointer(2) != NULL) LoadSpriteFromID( PcC->Wpn.Get_WeaponPointer(2)->Get_Sprite(), "SupportWp", 1.0f, 1.0f, 506.0f, 326.0f, 0.0f, false);

	

	// ログを2個事前に入れておきます(エラー回避)


	return ;
};



/* デストラクタ、スプライトを削除します */
Batch_Render::~Batch_Render(){

	/*変数の初期化*/
	int ech = 0;//エラーチェック用の確認変数 
	map< string, Sprite>::iterator it;// イテレータ	

	for( it = Spt.begin(); it != Spt.end(); it++){//ロードしたスプライトの削除
			if( (*it).second.DeleteFromBRFlag == true){// Batch_Renderから消してもよいスプライトなら
					ech = E3DDestroySprite( (*it).second.ID);
					_ASSERT( ech != 1 );//エラーチェック
			}
	}

	if( ShadowFlag == 1){// 影用レンダーテクスチャが生成されているなら
			ech = E3DDestroyRenderTargetTexture( ShadowScid, ShadowTexture);
			_ASSERT( ech != 1 );//エラーチェック
	}

}

int Batch_Render::BatchBeforePos(){

	/*変数の初期化*/
	int ech = 0;//エラーチェック用の確認変数 
	map< string, Model>::iterator it;// イテレータ


	for( it = Mdl.begin(); it != Mdl.end(); it++ ){
			if( (*it).second.ID != 0){
					ech = E3DSetBeforePos( (*it).second.ID);
					_ASSERT( ech != 1 );//エラーチェック
			}
	}


	return 0;
}

///* モデルをロードします */
//int Batch_Render::LoadModel( const char Path, )
//{
//
//
//
//
//
//
//	return 0;
//}