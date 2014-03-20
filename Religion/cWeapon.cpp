/* ///////////////////////////////////////////////////////// */
// ここでは、武器に関することを記述するクラスコードファイルです
// 主に、根底武器クラス関係のことが書かれています
/* /////////////////////////////////////////////////////////  */
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "cweapon.h"// 武器に関することのクラスヘッダファイル
#include "cenemy.h"//敵クラスの宣言ヘッダファイル
#include "cstage.h"//ステージ関係のクラスヘッダファイル
#include "clive.h"//敵やキャラの宣言ヘッダファイル

Weapon::Weapon(){

	/* 変数の宣言&初期化 */
	int ech = 0;
	NowFireFlag = 0;


	return;
}

Weapon::~Weapon(){

	/* 変数の初期化 */
	int ech = 0;// エラーチェック変数

	ech = E3DDestroyHandlerSet( Model);//モデルを削除します
	_ASSERT( ech != 1 );//エラーチェック

	ech = E3DDestroySprite( Sprite);//スプライトを削除します
	_ASSERT( ech != 1 );//エラーチェック

	ech = E3DDestroyBillboard( Effects);//エフェクトを削除します
	_ASSERT( ech != 1 );//エラーチェック

	for( int i=0; i<2; i++){// サウンドを削除します

		if( Sounds[i] == -1){
			ech = E3DDestroySound( Sounds[i]);
			_ASSERT( ech != 1 );//エラーチェック
		}
	}

	return;
}

/* プリセットしてある武器関連音源を再生します */
int Weapon::PlayWeaponSound( const int PlayNo, const float MuzzlePosArray[3]){

	/* 変数の初期化 */
	int ech = 0;//エラー確認変数
	D3DXVECTOR3 SoundVelocity( 340.0, 340.0, 340.0);//音速の指定を行います
	D3DXVECTOR3 MuzzlePos( MuzzlePosArray[0], MuzzlePosArray[1], MuzzlePosArray[2]);//マズルフラッシュサウンドの速度XYZ


	/*音の位置と速さを指定します*/
	ech = E3DSet3DSoundMovement( Sounds[PlayNo], MuzzlePos, SoundVelocity);
	_ASSERT( ech != 1 );//エラーチェック

	/*発射音を鳴らします*/
	ech = E3DPlaySound( Sounds[PlayNo], 0, 0, 0);
	_ASSERT( ech != 1 );//エラーチェック


	return 0;
}



