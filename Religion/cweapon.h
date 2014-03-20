#pragma once
/*武器クラスのキャラをするヘッダファイル。
//
*/

/*武器クラスに関することを記述*/
class Weapon{

private:

	/*変数の宣言*/
	int WeaponModel[3];
	int WeaponSprite[3];
	int WeaponKind[3];
	int WeaponData[3][6];
	int WeaponDataWhileGame[3][6];
	int WeaponBone[3][6];
	int WeaponOtherModel[3][4];

	/*関数の宣言*/
	int GunLoad_Assault( int Selectkind, int Wpno);//アサルトライフルの情報をロードする関数
	int GunLoad_Hand( int Selectkind, int Wpno);//ハンドガンの情報をロードする関数
	int GunLoad_Data( int Selectkind, int Wpkind, int Wpno);//武器に関する情報を格納する関数

public:

	/*関数の宣言*/
	int GunLoad( int Selectkind, int Wpkind, int Wpno);//武器をロードするための関数
	Weapon();//コンストラクタ、変数の初期化を行います
	~Weapon();//デストラクタ、モデルの破棄等を行います




};