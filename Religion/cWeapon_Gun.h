#pragma once
/* ///////////////////////////////////// */
// 銃機武器クラスのキャラをするヘッダファイル。
/* ///////////////////////////////////// */
#include "cWeapon.h"// スーパークラスの武器クラスが定義されているヘッダファイル

class NPC_Head;


/* 銃のクラス(Weaponクラスからの派生) */
class Weapon_Gun : public Weapon{

private:

	/* 変数の宣言 */
	int AmmoKind;//  使用弾薬の種類
	int Accuracy;// 武器の精度
	int RapidFire;//  武器が連射可能( 0:可能 1:不可能)
	int Magazine;// 武器のマガジン数
	int OtherModel;// 本体以外のモデル(弾薬など)

	int RapidTime;//  1秒間に打てる連射回数
	int ReloadTime;//  リロード時間

	/* ゲーム中の変数 */
	int NowMagazine;//  ゲーム中のマガジン数

	/* 関数の宣言 */
	int GunLoad_Assault( const int Wpno);//アサルトライフルの情報をロードする関数
	int GunLoad_Machine( const int Wpno);//マシンガンの情報をロードする関数
	int GunLoad_Hand(  const int Wpno);//ハンドガンの情報をロードする関数
	int GunLoad_Shot(  const int Wpno);// ショットガンの情報をロードする関数
	int GunLoad_Rifle(  const int Wpno);//ライフルの情報をロードする関数
	int GunLoad_Grenade(  const int Wpno);//グレネードの情報をロードする関数
	int GunLoad_SMG(  const int Wpno);//サブマシンガンの情報をロードする関数
	int GunLoad_Data( const int Wpkind, const int Wpno);//武器に関する情報を格納する関数

	int WeaponTreatment( const int WeaponLight);

public:

	int InitWeapon();// 武器の状態を初期にする
	int AttackEnemy( NPC_Head *NPC_H, PlayerChara *PC, int ScreenPosArray[2], Stage *Stg);// ゲーム中の敵とのあたり&攻撃判定を行います。
	int ChkWeaponLaunch();// 武器(ここでは銃)を発砲してもよいか確認し、OKなら発射フラグをたてます
	int ReloadWeapon();// 武器のリロードを行います

	/* アシスト関数 */
	int Get_NowMagazine() const;
	int Get_Magazine() const;
	int Get_RapidFire() const;
	int Set_RapidFire( int Number);

	/* 関数の宣言 */
	//int WpLoad( const int Selectkind, const int Wpkind, const int Wpno);//武器をロードするための関数
	Weapon_Gun( const int Selectkind, const int Wpkind, const int Wpno);// 銃武器クラスのコンストラクタ(ロードを行います)
	~Weapon_Gun();// 銃武器クラスのデストラクタ(アンロードを行います)
};