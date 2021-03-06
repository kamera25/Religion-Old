#pragma once
/*  ///////////////////////////////////////// */
//  武器統括クラスを宣言するヘッダファイルです
/*  ///////////////////////////////////////// */
#include "cweapon.h"// 武器に関することのクラスヘッダファイル

//プロトタイプ宣言
class NPC_Head;
class PlayerChara;
class Stage;

/*武器統括クラスに関することを記述します*/
class Weapon_Head{

private:

	/*変数の宣言*/

	Weapon *NormalWeapon[2];//  通常武器(右クリック)を格納する変数ポインタ
	Weapon *SupportWeapon;// サポート武器(左クリック)を格納する変数ポインタ

	int WeaponLight;// 武器のマズルフラッシュライト格納変数
	int GunHitChkModelID;// 銃の当たりを求めるときに使う「細長い」モデルのID


public:

	/* 変数の宣言 */
	// SetInitWeapon関数で使う
	static const int RESET = -1;// 全てをリセットする

	// DeleteWeapon関数で使う
	static const int MAINWEAPON = 0;// 主装備を表す
	static const int SUBWEAPON = 1;// 副装備を表す
	static const int SUPPORTWEAPON = 2;// サポート武器を表す


	/*関数の宣言*/

	int WpLoad( int EquipKind, int WeaponKind, int WeaponNum);// 武器を指定の装備種類に装備(ロード)します 
	int DeleteWeapon( int EquipKind);// 装備されている武器を削除します
	int SetInitWeapon( int WpKind);// 武器のデータの初期化を行います 
	int ChkWeaponsLaunch( int Equipment);// すべての武器を発射・投降しているかチェックする
	int AttackEnemys( NPC_Head *NPC, PlayerChara *PC, int ScreenPosArray[2], Stage *Stg);// 敵の当たり判定チェックを行います
	int WeaponsTreatment( int Equipment, Stage *Stg);//

	Weapon *Get_WeaponPointer( int Now_Equipment) const;// 武器の実体のポインターが代入されているポインターを得る関数
	Weapon_Head();//コンストラクタ、変数の初期化を行います
	~Weapon_Head();//デストラクタ、モデルの破棄等を行います

};