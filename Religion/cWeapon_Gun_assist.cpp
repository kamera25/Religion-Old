/* ここでは、武器クラス関係のアシスト関数を定義するクラスコードファイルです。
// アシスト関数とはクラスにおけるプライベート変数の取得・代入を行なうだけの関数の総称です。
*/

#include "cWeapon_Gun.h"//武器に関することのクラスヘッダファイル




int Weapon_Gun::Get_NowMagazine() const{

	return NowMagazine;
}

int Weapon_Gun::Get_Magazine() const{

	return Magazine;
}

int Weapon_Gun::Get_Range() const{

	return Range;
}
