/* ここでは、生物クラス関係のアシスト関数を定義するクラスコードファイルです。
// アシスト関数とはクラスにおけるプライベート変数の取得・代入を行なうだけの関数の総称です。
*/
#include "ccreature.h"// 生物クラスのヘッダファイル

/* MaxHP変数の取得関数 */
int Creature::Get_BodyModel() const{

	return BodyModel;
}
/* HP変数の取得関数 */
int Creature::Get_HP() const{

	return HP;
}
/* BodyModel変数の取得関数 */
int Creature::Get_MaxHP() const{

	return MaxHP;
}

int Creature::Set_BodyModel( int Number){

	BodyModel = Number;

	return 0;
}

int Creature::Set_HP( int Number){

	HP = Number;

	return 0;
}

int Creature::Set_MaxHP( int Number){

	MaxHP = Number;

	return 0;
}