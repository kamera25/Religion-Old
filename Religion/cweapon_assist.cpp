/* ここでは、武器クラス関係のアシスト関数を定義するクラスコードファイルです。
// アシスト関数とはクラスにおけるプライベート変数の取得・代入を行なうだけの関数の総称です。
*/

#include "cweapon.h"//武器に関することのクラスヘッダファイル


/*武器モデルIDの取得を行います*/
int Weapon::GetWeaponModelID( int ItemNumber, int DataNumber) const{

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
int Weapon::GetWeaponData( int ItemNumber, int DataNumber) const{


	return WeaponData[ItemNumber][DataNumber];
}

/*ゲーム中の武器の詳細データを取得します*/
int Weapon::GetWeaponDataWhileGame( int ItemNumber, int DataNumber) const{


	return WeaponDataWhileGame[ItemNumber][DataNumber];
}

/*武器スプライトを取得します*/
int Weapon::GetSpriteData( int ItemNumber) const{


	return WeaponSprite[ItemNumber];
}

/*武器発射フラグ変数を取得します*/
int Weapon::GetWeaponFireFlag() const{

	return WeaponFireFlag;
}

/* 武器の連射カウンタを取得します*/
int Weapon::GetWeaponRapidFire() const{

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