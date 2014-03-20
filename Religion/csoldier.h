#pragma once
/* 兵士クラスの宣言をするヘッダファイル。
// !兵士!クラスは人間クラス(親は生物)を継承してつくられています
*/
#include "cpeople.h"// 人間クラスのヘッダファイル
#include "cWeapon_head.h"// 武器統括に関することのクラスヘッダファイル
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
	Weapon_Head Wpn;// ウェポンクラスの実体
	Item Item;// アイテムクラスの実体

	static const int AirOff = 0;
	static const int AirOn = 1;


	/* 関数の宣言 */
	int MovePosOnGround( Stage *Stg) ;// キャラクターをグラウンドの上に置くための関数
	int GunPutOnHand();// 現在持ってる銃を持つためのモーション・システムを管轄する関数
	int Batch_PeopleMotion();// 人間のモーションや姿勢などを設定します
	Soldier( const int selchara, const int Wpselect_equipment);// コンストラクタ、兵士モデルのロード等を行ないます
	virtual ~Soldier();//仮想コンストラクタ

	virtual int StatusReset();// ソルジャークラスの状態を初期に戻します(リスタート等で利用)

	/* アシスト(取得・代入)関数の宣言 */
	int Get_Wp_equipment() const; // Wp_equipmentの取得関数
	int Set_Wp_equipment( int Number);// Wp_equipmentの代入関数
	int Get_DummyModel() const;// ダミーモデルのID取得関数
	int Set_DummyModel( int Number);// ダミーモデルのID代入関数
	int Get_Bone_ID( int BoneNo) const;// ボーンIDの取得関数
	int Set_Bone_ID( int BoneNo, int Number);// ボーンIDの代入関数
	int Get_Quaternion( int QNo) const;// クォータニオンの取得関数
	int Set_Quaternion( int QNo, int Number);// クォータニオンの代入関数
	Weapon_Head* Get_WeaponH();// ウェポン統括クラスポインタの取得関数

};