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
/* Staminaの取得関数 */
int Creature::Get_Stamina() const{

	return Stamina;
}
/* Staminaの代入関数 */
int Creature::Set_Stamina( int Number){

	if( Number <= 0){
		Number = 0;
	}
	
	Stamina = Number;
	

	return 0;
}
/* MaxStaminaの取得関数 */
int Creature::Get_MaxStamina() const{

	return MaxStamina;
}
/* MaxStaminaの代入関数 */
int Creature::Set_MaxStamina( int Number){

	MaxStamina = Number;

	return 0;
}

/* Attackの取得関数 */
int Creature::Get_Attack() const{

	return Attack;
}
/* Attackの代入関数 */
int Creature::Set_Attack( int Number){

	Attack = Number;

	return 0;
}

/* SkillSlotの取得関数 */
int Creature::Get_SkillSlot() const{

	return SkillSlot;
}
/* SkillSlotの代入関数 */
int Creature::Set_SkillSlot( int Number){

	SkillSlot = Number;

	return 0;
}

/* Branchの取得関数 */
int Creature::Get_Branch() const{

	return Branch;
}
/* Branchの代入関数 */
int Creature::Set_Branch( int Number){

	if( ( Number < 0)&&( 4 < Number)) Number = -1;// 属性が制定されていなかったら、ノーマルに適応させる
	Branch = Number;

	return 0;
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

int Creature::Delete_Skill(){

	delete [] Skill;

	return 0;
}

int Creature::Set_Skill( int *Pointer ){

	Skill = Pointer;

	return 0;
}

int Creature::Set_EquipmentSkillSum( int Number ){

	EquipmentSkillSum = Number;

	return 0;
}