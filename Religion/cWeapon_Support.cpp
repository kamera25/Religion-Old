/* ///////////////////////////////////////////////////////// */
// ここでは、武器に関することを記述するクラスコードファイルです
// 主に、サポート武器関係のことが書かれています
/* /////////////////////////////////////////////////////////  */
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "cWeapon_Support.h"//サポート武器に関することのクラスヘッダファイル



// サポート武器クラスのコンストラクタ(ロードを行います) //
Weapon_Support::Weapon_Support( const int Wpno){

	/* 変数の初期化 */
	int ech = 0;
	int EffectNo = 0;
	char loadname[256] = "";


	/*すでに銃を取得しており、その銃データに上書きするなら*/
	/*if( Get_Model() != -1){//選択中のカテゴリにデータがあるのなら
				ech = E3DDestroyHandlerSet( Get_Model());
				_ASSERT( ech != 1 );//エラーチェック

				ech = E3DDestroySprite( Get_Sprite());//スプライトを削除します
				_ASSERT( ech != 1 );//エラーチェック
	}*/

	/* サポート武器をロード */
	WpLoad_Support( Wpno);

	
	/* エフェクトビルボードをロードします */
	wsprintf( loadname, "%s\\data\\img\\effect\\explosion1.png", System::path);
	ech = E3DCreateBillboard ( loadname, 96, 96, 0, 1, 1, &EffectNo);
	_ASSERT( ech != 1 );//エラーチェック

	/* エフェクトを予め透過しておく */
	ech = E3DSetBillboardAlpha( EffectNo, 0.0f);
	_ASSERT( ech != 1 );//エラーチェック

	/* エフェクトIDをメンバ変数に代入 */
	Set_Effects( EffectNo);

	/* サポート武器データのロードをする */
	

	return;
}

// サポート武器クラスのデストラクタ(アンロードを行います) //
Weapon_Support::~Weapon_Support(){




	return;
}