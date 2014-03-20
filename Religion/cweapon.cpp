/*ここでは、武器に関することを記述するクラスコードファイルです
//主に、武器クラスのコンストラクタ・デストラクタについて書かれています
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "cenemy.h"//敵クラスの宣言ヘッダファイル
#include "cweapon.h"//武器に関することのクラスヘッダファイル


/*コンストラクタ、変数の初期化を行います*/
Weapon::Weapon(){

	/*すべての配列変数の初期化を行います*/
	for( int i=0; i<3; i++){
			WeaponModel[i] = -1;
			WeaponSprite[i] = -1;
			WeaponMuzzleLight[i] = -1;
			for( int j=0; j<10; j++){
					WeaponData[i][j] = -1;
			}
			for( int j=0; j<6; j++){
					WeaponData[i][j] = -1;
					WeaponDataWhileGame[i][j] = -1;
					WeaponBone[i][j] = -1;	
					WeaponSoundEfeect[i][j] = -1;
			}
			for( int j=0; j<4; j++){
				WeaponOtherModel[i][j] = -1;
			}
			for( int j=0; j<2; j++){
				WeaponEffect[i][j] = -1; 
			}
	}

	WeaponRapidFire = -1;
	WeaponFireFlag = -1;

	return;
}
/*デストラクタ、モデルの破棄等を行います*/
Weapon::~Weapon(){

	//変数の初期化
	int ech = 0;

	//銃のデータの削除します（最初から順番にメイン・サブ・グレネードの順番です）
	for(int i = 0;i < 3; i++){
		if( WeaponModel[i] != 0){//選択中のカテゴリにデータがあるのなら
					ech = E3DDestroyHandlerSet( WeaponModel[i]);//モデルを削除します
					_ASSERT( ech != 1 );//エラーチェック

					ech = E3DDestroySprite( WeaponSprite[i]);//スプライトを削除します
					_ASSERT( ech != 1 );//エラーチェック
					ech = E3DDestroyBillboard( WeaponEffect[i][0]);//エフェクトを削除します
					_ASSERT( ech != 1 );//エラーチェック
					ech = E3DDestroyLight( WeaponMuzzleLight[i]);
					_ASSERT( ech != 1 );//エラーチェック
					for( int j=0; j<6; j++){
						if( WeaponSoundEfeect[i][0] != 0){//音声ファイルを消す
							ech = E3DDestroySound( WeaponSoundEfeect[i][0]);
							_ASSERT( ech != 1 );//エラーチェック
						}
					}
		}	
	}

	return;
}