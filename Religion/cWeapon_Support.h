#pragma once
/* ///////////////////////////////////// */
// 武器クラスのキャラをするヘッダファイル。
/* ///////////////////////////////////// */
#include "cWeapon.h"// スーパークラスの武器クラスが定義されているヘッダファイル




/* サポート武器のクラス(Weaponクラスからの派生) */
class Weapon_Support : public Weapon{

private:


	/* 関数の宣言 */
	int WpLoad_Support(  const int Wpno);// サポート系の情報をロードする関数


public:

	/* 関数の宣言 */
	Weapon_Support( const int Wpno);// コンストラクタ(ロードを行います)
	~Weapon_Support();// デストラクタ(アンロードを行います)


};