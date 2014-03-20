#pragma once
/*ここでは、敵モデルや敵の動きに関することを
//関数を自動的に実行することができるようにするためのクラスヘッダファイル
*/
#include <vector>
#include "cweapon.h"//武器に関することのクラスヘッダファイル
#include "ccreature.h"// 生物クラスのヘッダファイル

using namespace std;

//プロトタイプ宣言
class Stage;

class NPC_t{

	friend class NPC_Head;

private:

	/* 変数 */
	int TargetNaviPointID;// NPCが目指すナビポイントが格納されている変数
	int TargetNaviLineID;// NPCが目指すナビラインが格納されている変数
	int NPCRace;// NPCの種族を代入する変数
	int NPCNumber;// NPCの種類を代入する変数

	int NPCBelongingKind;// NPCが所属しているところを代入する変数( 0.味方 1.敵 )

	int NPCBehavior; // PCの行動について状態を代入します

	char NPCName[20];// NPCの名前を代入します

	/* 関数 */

public:
	/* 変数 */
	Creature* NPC_Mdl;

};


class NPC_Head{

private:

	vector<NPC_t> NPC;

	/* 変数の宣言 */
//	int TargetNaviPointID[15];// 敵が目指すナビポイントが格納されている変数
//	int TargetNaviLineID[15];// 敵が目指すナビラインが格納されている変数
//	int CreatureRace[15];// 敵の種族を代入する変数
//	int CreatureNumber[15];// 敵の種類を代入する変数
	/* コンテナ */



public:

	// メンバが保持しているクラス系変数
//	Creature* Ene[15];

	//変数の宣言
//	int EnemyNum;//現在ロードされているモデルの数






	//関数の宣言
	NPC_Head();//コンストラクタ、クラス変数の初期化を行います
	~NPC_Head();//デストラクタ、モデルの削除を行います
	int LoadEnemyModel( const int Ene_Kind, const int Ene_No);// 敵を情報やモデルをロードするための関数(名前なし)
	int LoadEnemyModelAddName( const char *Name, const int Ene_Kind, const int Ene_No);// 敵を情報やモデルをロードするための関数(名前付き)
	int MoveEnemys( Stage *Stg);//敵の動きをまとめて動かすための関数
	int EnemySetPos();
	int SetEnemyPosByNaviPoint( Stage *Stg, const char *Name, const int NaviLine, const int NaviPoint);// 敵の座標をナビポイントを基に設定します
	int SetEnemyPosByNaviPointArray( Stage *Stg, const char *Name, const int *EnemyOnNaviLine, int const *EnemyOnNaviPoint, const int ArrayMax);// 敵の座標をまとめてナビポイントを基に設定します
	int SearchNPCFromName( const char *ObjName, vector<NPC_t>::iterator *it);

	/* アシスト関数 */
	vector<NPC_t>::iterator NPC_endit();
	vector<NPC_t>::iterator Get_NPC_begin();
	bool Get_NPC_empty() const;

};

