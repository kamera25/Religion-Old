/* ここでは、兵士クラス関係のアシスト関数を定義するクラスコードファイルです。
// アシスト関数とはクラスにおけるプライベート変数の取得・代入を行なうだけの関数の総称です。
*/
#include "csoldier.h"// 兵士クラスの宣言ヘッダファイル
#include "cWeapon_head.h"// 武器統括に関することのクラスヘッダファイル



/* Wp_equipmentの取得関数 */
int Soldier::Get_Wp_equipment() const{

	return Wp_equipment;
}
/* Wp_equipmentの代入関数*/
int Soldier::Set_Wp_equipment( int Number){

	Wp_equipment = Number;

	return 0;
}
/* ダミーモデルのID取得関数 */
int Soldier::Get_DummyModel() const{

	return DummyModel;
}
/* ダミーモデルのID代入関数 */
int Soldier::Set_DummyModel( int Number){

	DummyModel = Number;

	return 0;
}
/* ボーンIDの取得関数 */
int Soldier::Get_Bone_ID( int BoneNo) const{

	return Bone_ID[BoneNo];
}
/* ボーンIDの取得関数 */
int Soldier::Set_Bone_ID( int BoneNo, int Number){

	Bone_ID[BoneNo] = Number;

	return 0;
}
/* クォータニオンの取得関数 */
int Soldier::Get_Quaternion( int QNo) const{

	return Quater_ID[QNo];
}
/* クォータニオンの代入関数 */
int Soldier::Set_Quaternion( int QNo, int Number){

	Quater_ID[QNo] = Number;

	return 0;
}
/* ウェポンポインタの取得関数 */
Weapon_Head* Soldier::Get_WeaponH(){

	return &Wpn;
}