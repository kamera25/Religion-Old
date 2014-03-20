#pragma once
/*ここでは、敵モデルや敵の動きに関することを
//関数を自動的に実行することができるようにするためのクラスヘッダファイル
*/
#include "cweapon.h"//武器に関することのクラスヘッダファイル

#include "ccreature.h"// 生物クラスのヘッダファイル

//プロトタイプ宣言
class Stage;

class Enemy{

private:

	/* 変数の宣言 */
	int TargetNaviPointID[15];// 敵が目指すナビポイントが格納されている変数
	int TargetNaviLineID[15];// 敵が目指すナビラインが格納されている変数
	int CreatureRace[15];// 敵の種族を代入する変数
	int CreatureNumber[15];// 敵の種類を代入する変数

public:

	// メンバが保持しているクラス系変数
	Creature* Ene[15];

	//変数の宣言
	int EnemyNum;//現在ロードされているモデルの数



	//関数の宣言
	Enemy();//コンストラクタ、クラス変数の初期化を行います
	~Enemy();//デストラクタ、モデルの削除を行います
	int LoadEnemyModel( const int Ene_Kind, const int Ene_No);//敵を情報やモデルをロードするための関数
	int MoveEnemys( Stage *Stg);//敵の動きをまとめて動かすための関数
	int EnemySetPos();
	int SetEnemyPosByNaviPoint( Stage *Stg, const int EnemyNum, const int NaviLine, const int NaviPoint);// 敵の座標をナビポイントを基に設定します
	int SetEnemyPosByNaviPointArray( Stage *Stg, const int *EnemyOnNaviLine, int const *EnemyOnNaviPoint, const int ArrayMax);// 敵の座標をまとめてナビポイントを基に設定します

};

