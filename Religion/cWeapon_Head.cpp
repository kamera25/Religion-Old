/* /////////////////////////////////////////// */
// 武器統括クラス関係のことが記述されています。
/* /////////////////////////////////////////// */
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "cWeapon_head.h"// 武器統括に関することのクラスヘッダファイル
#include "cWeapon_Gun.h"//銃に関することのクラスヘッダファイル
#include "cWeapon_Support.h"//サポート武器に関することのクラスヘッダファイル
#include "cstage.h"//ステージ関係のクラスヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

/* コンストラクタ、変数の初期化を行います */
Weapon_Head::Weapon_Head(){

	/* 変数の初期化 */
	int ech = 0;// エラーチェック変数

	/* メンバ変数の初期化を行います */
	NormalWeapon[0] = NULL;
	NormalWeapon[1] = NULL;
	SupportWeapon = NULL;
	GunHitChkModelID = NULL;

	/* 「細長い」モデルのID */


	/* マズルフラッシュなどに使われる、ライトを作成します */
	ech = E3DCreateLight( &WeaponLight);
	_ASSERT( ech != 1 );//エラーチェック

	return;
}

/* 武器を指定の装備種類に装備(ロード)します  */
int Weapon_Head::WpLoad( int EquipKind, int WeaponKind, int WeaponNum){

	/* 変数の初期化 */
	Weapon **SelectedKind = NULL;// 選択された装備種別の武器ポインタ



	/* 選択された装備種別の武器ポインタを代入 */
	switch( EquipKind ){
			case 0:{// 主装備の場合
					SelectedKind = &NormalWeapon[0];
					break;
			}
			case 1:{// 副装備の場合
					SelectedKind = &NormalWeapon[1];
					break;
			}
			case 2:{// サポート武器の場合
					SelectedKind = &SupportWeapon;
					break;
			}
			default:{// 存在しない場合
					return -1;
			}
	}

	/* もし、武器を置き換えるなら */
	if( SelectedKind != NULL){
		DeleteWeapon( EquipKind);// 消えるがよい!
	}



	/* 武器のクラスを実体化させます */
	if( ( 0 <= WeaponKind) && ( WeaponKind <= 6)){// 銃のロードを行うのなら
			*SelectedKind = new Weapon_Gun( EquipKind, WeaponKind, WeaponNum);
	}
	else if( WeaponKind == 7){// サポート武器のロードを行うのなら
			*SelectedKind = new Weapon_Support( WeaponNum);
	}
	else{// それ以外の正しくない数字なら
			_ASSERT( 0 );
			return -1;
	}






	return 0;
}

/* 装備されている武器を削除します */
int Weapon_Head::DeleteWeapon( int EquipKind){


	switch( EquipKind){
			case 0:{// 主兵装が選択されているなら
					delete NormalWeapon[0];
					NormalWeapon[0] = NULL;
					break;
			}
			case 1:{// 副兵装が選択されているのなら
					delete NormalWeapon[1];
					NormalWeapon[1] = NULL;
					break;
			}
			case 2:{// サポート武器が選択されているのなら
					delete SupportWeapon;
					SupportWeapon = NULL;
					break;
			}

	}


	return 0;
}

/* デストラクタ*/
Weapon_Head::~Weapon_Head(){

	/* 初期化 */
	int ech = 0;

	DeleteWeapon( MAINWEAPON);
	DeleteWeapon( SUBWEAPON);
	DeleteWeapon( SUPPORTWEAPON);

	// 当たり判定用の細長いモデルを削除します
	if( GunHitChkModelID != NULL){
		ech = E3DDestroyHandlerSet(	GunHitChkModelID);
		_ASSERT( ech != 1 );//エラーチェック
	}

	// マズルフラッシュ用光源を削除する
	if( WeaponLight != NULL){
		 ech = E3DDestroyLight( WeaponLight);
		_ASSERT( ech != 1 );//エラーチェック
	}

	return ;
}

/* 武器の実体のポインターが代入されているポインターを得る関数 */
Weapon* Weapon_Head::Get_WeaponPointer( int Now_Equipment) const{


	if( ( Now_Equipment < 0) && ( 1 < Now_Equipment)){// 範囲外なら
			return NULL;
	}

	if( Now_Equipment == 2){
			return SupportWeapon;
	}

	return NormalWeapon[Now_Equipment];
}

/* 武器のデータの初期化を行なう関数 */
int Weapon_Head::SetInitWeapon( int Wpkind){
	
	switch(Wpkind){
			case 0:{// メインウェポン
					NormalWeapon[0]->InitWeapon();
					break;
		    }
			case 1:{// サブウェポン
					NormalWeapon[1]->InitWeapon();
					break;
			}
			case 2:{// サポートウェポン
					SupportWeapon->InitWeapon();
					break;
			}
			default:{// それ以外(全て)
					if( NormalWeapon[0] != NULL){
							NormalWeapon[0]->InitWeapon();
					}
					if( NormalWeapon[1] != NULL){
							NormalWeapon[1]->InitWeapon();
					}
					if( SupportWeapon != NULL){
							SupportWeapon->InitWeapon();
					}
			}
	}

	
	
	return 0;
}

/* すべての武器を発射・投降しているかチェックする */
int Weapon_Head::ChkWeaponsLaunch( int Equipment){

	if( Equipment == -1){// 装備なしなら
			return -1;// エラー返し
	}

	Get_WeaponPointer(Equipment)->ChkWeaponLaunch();// 装備中の武器の発射キー確認を行う


	return 0;
}

/* 敵の当たり判定チェックを行う関数 */
int Weapon_Head::AttackEnemys( NPC_Head *NPC_H, PlayerChara *PC, int ScreenPosArray[2], Stage *Stg){

	/* 装備中の武器があれば、当たり判定を行う */
	for( int i=0; i<3; i++){
			if( Get_WeaponPointer(i) != NULL){
					Get_WeaponPointer(i)->AttackEnemy( NPC_H,  PC, ScreenPosArray, Stg);
			}
	}



	return 0;
}

/* 武器のマズルフラッシュ・リロード・ */
int Weapon_Head::WeaponsTreatment( int Equipment, Stage *Stg){

	/* 変数の初期化 */
	int ech = 0;

	/* 装備中の武器があれば、当たり判定を行う */
	for( int i=0; i<2; i++){
			if( Get_WeaponPointer(i) != NULL){
					Get_WeaponPointer(i)->WeaponTreatment( WeaponLight);
			}
	}

	/* サポート武器は引数が違うので別記述 */
	if( Get_WeaponPointer(2) != NULL){
					Get_WeaponPointer(2)->WeaponTreatment( WeaponLight, Stg);
	}


	/* 武器のリロードを行います */
	if( ( Equipment != -1) && ( Equipment != 2)) Get_WeaponPointer(Equipment)->ReloadWeapon();// 装備がサポート武器でなければ



	return 0;
}