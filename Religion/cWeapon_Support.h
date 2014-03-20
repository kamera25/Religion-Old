#pragma once
/* ///////////////////////////////////// */
// 武器クラスのキャラをするヘッダファイル。
/* ///////////////////////////////////// */
#include "cWeapon.h"// スーパークラスの武器クラスが定義されているヘッダファイル




/* サポート武器のクラス(Weaponクラスからの派生) */
class Weapon_Support : public Weapon{

private:


	/* 関数の宣言 */
	int WpLoad_Support(  const int Wpno);// サポート系の総合的な読み込み処理をする関数
	int SupportLoad_Data( int Wpkind, int Wpno);// サポート系の武器データをロードする関数

public:

	/* 関数の宣言 */
	int InitWeapon();// 武器の状態を初期にする
	int AttackEnemy( Enemy *Ene, PlayerChara *PC, int ScreenPosArray[2], Stage *Stg);
	int WeaponTreatment( const int WeaponLight, Stage *Stg);// ゲーム中の銃の操作に関することをします
	int ChkWeaponLaunch();// 武器を発砲・投げしてもよいか確認し、OKなら発射フラグをたてます
	Weapon_Support( const int Wpno);// コンストラクタ(ロードを行います)
	~Weapon_Support();// デストラクタ(アンロードを行います)


};