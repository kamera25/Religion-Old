#pragma once
/* 兵士クラスの宣言をするヘッダファイル。
// !兵士!クラスは人間クラス(親は生物)を継承してつくられています
*/
#include "cpeople.h"// 人間クラスのヘッダファイル
#include "cweapon.h"// 武器に関することのクラスヘッダファイル
#include "citem.h"// アイテムの宣言ヘッダファイル

/* プロトタイプ宣言 */
class Stage;

/* 兵士クラスの宣言 */
class Soldier: public People{

private:

	/* ////////// */
	// 変数の宣言 
	/* ////////// */

	// 兵士の状態変数
	int Wp_equipment;//所持している武器の種類

	// ステータス系
	int Stamina;// キャラクタのスタミナ

	// モデル系
	int DummyModel;//ダミーモデルのモデルID

	/* ///////////////////////////////////////////////////////// */
	// Bone_ID配列にはボーンが格納されます!
	// [0]もち手右 [1]もち手先右 [2]おなか
	/* ///////////////////////////////////////////////////////// */
	int Bone_ID[10];

	/* ///////////////////////////////////////////////////////// */
	// !クオンターニオンの識別IDを格納します!
	// [0] 銃の向き [1] 銃の当たり判定モデルの向き
	// [2] モデル座標の向き [3] 銃の方向、PCの姿勢
	// [4]当たり判定モデルの向き
	/* ///////////////////////////////////////////////////////// */
	int Quater_ID[10];


	int BeforeAirOnPC;// キャラが前回、空中にいたか代入します


public:

	/* クラスの宣言 */
	Weapon Wpn;// ウェポンクラスの実体
	Item Item;// アイテムクラスの実体

	/* 関数の宣言 */
	int MovePosOnGround( Stage *Stg) ;// キャラクターをグラウンドの上に置くための関数
	int GunPutOnHand();// 現在持ってる銃を持つためのモーション・システムを管轄する関数
	int Batch_PeopleMotion();// 人間のモーションや姿勢などを設定します
	Soldier( const int selchara, const int Wpselect_equipment);// コンストラクタ、兵士モデルのロード等を行ないます
	virtual ~Soldier(){};//仮想コンストラクタ


	/* アシスト(取得・代入)関数の宣言 */
	int Get_Wp_equipment() const; // Wp_equipmentの取得関数
	int Set_Wp_equipment( int Number);// Wp_equipmentの代入関数
	int Get_Stamina() const;// Staminaの取得関数
	int Set_Stamina( int Number);// Staminaの代入関数
	int Get_DummyModel() const;// ダミーモデルのID取得関数
	int Set_DummyModel( int Number);// ダミーモデルのID代入関数
	int Get_Bone_ID( int BoneNo) const;// ボーンIDの取得関数
	int Set_Bone_ID( int BoneNo, int Number);// ボーンIDの代入関数
	int Get_Quaternion( int QNo) const;// クォータニオンの取得関数
	int Set_Quaternion( int QNo, int Number);// クォータニオンの代入関数
	Weapon* Get_Weapon();// ウェポンポインタの取得関数

};