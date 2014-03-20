/*ここでは、武器に関することを記述するクラスコードファイルです
//
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "cenemy.h"//敵クラスの宣言ヘッダファイル
#include "cweapon.h"//武器に関することのクラスヘッダファイル





/*武器をロードするための関数*/
int Weapon::GunLoad( int Selectkind, int Wpkind, int Wpno){

	//変数の初期化
	int ech = 0;
	char loadname[256] = "";

	/*すでに銃を取得しており、その銃データに上書きするなら*/
	if( WeaponModel[Selectkind] != 0){//選択中のカテゴリにデータがあるのなら
				ech = E3DDestroyHandlerSet( WeaponModel[Selectkind]);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};

				ech = E3DDestroySprite( WeaponSprite[Selectkind]);//スプライトを削除します
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};
	}


	/*銃のモデルのロード*/
	if(Wpkind == 1) GunLoad_Hand( Selectkind, Wpno);//ハンドガン系
	if(Wpkind == 4) GunLoad_Assault( Selectkind, Wpno);//アサルトライフル系

	//エフェクトビルボードをロードします
	wsprintf( loadname, "%s\\data\\img\\effect\\explosion1.png", System::path);
	ech = E3DCreateBillboard ( loadname, 96, 96, 0, 1, 1, &WeaponEffect[Selectkind][0]);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	//エフェクトを予め透過しておく
	ech = E3DSetBillboardAlpha( WeaponEffect[Selectkind][0], 0.0f);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	//フラッシュの光源を作る(グレネードは爆発光)
	ech = E3DCreateLight( &WeaponMuzzleLight[Selectkind]);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};


	/*武器データのロードをする*/
	GunLoad_Data( Selectkind, Wpkind, Wpno);


	return 0;
}
/*武器に関するデータを格納する関数*/
int Weapon::GunLoad_Data( int Selectkind, int Wpkind, int Wpno){

	//一時的な変数（モデル格納等など）
	int ammo = 0;//弾薬の最大値
	int mag = 0;//マガジンの最大値
	int distance = 0;//射程距離の最大値
	int attack = 0;//武器の攻撃値
	int rapid_fire = 0;//連射可能銃か
	double firecounter = 0.0;//連射の数値


	/*ハンドガン関係*/
	if( Wpkind == 1){
			if(Wpno == 0){//M1911

						//M1911のデータを格納します。
						ammo = 7;
						mag = 7;
						distance = 100;
						attack = 100;
						firecounter = 1.0;
						rapid_fire = 0;
			}
			if(Wpno == 2){//Glock95
						
						//Glockのデータを格納します。
						ammo = 50;
						mag = 3;
						distance = 60;
						attack = 30;
						firecounter = 3.0;
						rapid_fire = 1;
			}
			if(Wpno == 3){//M92FS
								
						//M92Fのデータを格納します。
						ammo = 15;
						mag = 2;
						distance = 120;
						attack = 80;
						firecounter = 1.4;
						rapid_fire = 0;
			}
	}
	/*アサルトライフル関係*/
	if( Wpkind == 4){

			if( Wpno == 0){
						//M4のデータを格納します。
						ammo = 30;
						mag = 5;
						distance = 160;
						attack = 140;
						firecounter = 1.6;
						rapid_fire = 1;
			}
	}


	WeaponData[Selectkind][0] = Wpkind;
	WeaponData[Selectkind][1] = Wpno;
	WeaponData[Selectkind][2] = ammo;
	WeaponData[Selectkind][3] = mag;
	WeaponData[Selectkind][4] = distance;
	WeaponData[Selectkind][5] = attack;
	WeaponData[Selectkind][6] = int( 30 / firecounter) ;
	WeaponData[Selectkind][7] = rapid_fire;


	return 0;
}
/*武器モデルIDの取得を行います*/
int Weapon::GetWeaponModelID( int ItemNumber, int DataNumber){

	/*変数の初期化*/
	int DataID = 0;//返すIDを格納する変数

	if( DataNumber == 0){//メインモデルなら
			DataID = WeaponModel[ItemNumber];
	}
	if( DataNumber == 1){//使用済み弾薬のモデル
			DataID = WeaponOtherModel[ItemNumber][0];
	}




	return DataID;
}
/*武器の詳細データを取得します*/
int Weapon::GetWeaponData( int ItemNumber, int DataNumber){


	return WeaponData[ItemNumber][DataNumber];
}
/*ゲーム中の武器の詳細データを取得します*/
int Weapon::GetWeaponDataWhileGame( int ItemNumber, int DataNumber){


	return WeaponDataWhileGame[ItemNumber][DataNumber];
}
/*武器スプライトを取得します*/
int Weapon::GetSpriteData( int ItemNumber){


	return WeaponSprite[ItemNumber];
}
/* 武器の連射カウンタを取得します*/
int Weapon::GetWeaponRapidFire(){

	return WeaponRapidFire;
}
/*武器の状態を初期化し、銃弾やマガジンを一杯にします*/
int Weapon::SetInitWeaponData(){

	for( int i=0; i<3; i++){
			WeaponDataWhileGame[i][0] = WeaponData[i][2];
			WeaponDataWhileGame[i][1] = WeaponData[i][3];
	}

	return 0;
}
/*武器の音声を再生します(3DSE専用)*/
int Weapon::PlayWeaponSound( int Wp_equipment, int PlayNo, float MuzzlePosArray[3]){

	/*変数の初期化*/
	int ech = 0;//エラー確認変数
	D3DXVECTOR3 MuzzleFlashSound( 340.0, 340.0, 340.0);//マズルフラッシュサウンドの速度XYZ
	D3DXVECTOR3 MuzzlePos( MuzzlePosArray[0], MuzzlePosArray[1], MuzzlePosArray[2]);//マズルフラッシュサウンドの速度XYZ


	/*音の位置と速さを指定します*/
	ech = E3DSet3DSoundMovement( WeaponSoundEfeect[Wp_equipment][PlayNo], MuzzlePos, MuzzleFlashSound);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/*発射音を鳴らします*/
	ech = E3DPlaySound( WeaponSoundEfeect[Wp_equipment][PlayNo], 0, 0, 0);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};


	return 0;
}
/*武器発射フラグ変数を取得します*/
int Weapon::GetWeaponFireFlag(){

	return WeaponFireFlag;
}
/*コンストラクタ、変数の初期化を行います*/
Weapon::Weapon(){

	/*すべての配列変数の初期化を行います*/
	for( int i=0; i<3; i++){
			WeaponModel[i] = 0;
			WeaponSprite[i] = 0;
			WeaponMuzzleLight[i] = 0;
			for( int j=0; j<7; j++){
					WeaponData[i][j] = 0;
			}
			for( int j=0; j<6; j++){
					WeaponData[i][j] = 0;
					WeaponDataWhileGame[i][j] = 0;
					WeaponBone[i][j] = 0;	
					WeaponSoundEfeect[i][j] = 0;
			}
			for( int j=0; j<4; j++){
				WeaponOtherModel[i][j] = 0;
			}
			for( int j=0; j<2; j++){
				WeaponEffect[i][j] = 0; 
			}
	}

	WeaponRapidFire = 0;
	WeaponFireFlag = 0;

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
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
					};

					ech = E3DDestroySprite( WeaponSprite[i]);//スプライトを削除します
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
					};
					ech = E3DDestroyBillboard( WeaponEffect[i][0]);//エフェクトを削除します
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
					};
					ech = E3DDestroyLight( WeaponMuzzleLight[i]);
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
					};
					for( int j=0; j<6; j++){
						if( WeaponSoundEfeect[i][0] != 0){//音声ファイルを消す
							ech = E3DDestroySound( WeaponSoundEfeect[i][0]);
							if(ech != 0 ){//エラーチェック
										_ASSERT( 0 );//エラーダイアログ
							};
						}
					}
		}	
	}

	return;
}