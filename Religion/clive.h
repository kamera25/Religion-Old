#pragma once
/*キャラクタークラスの宣言をするヘッダファイル。
//
*/

#include "csoldier.h"// 兵士クラスの宣言ヘッダファイル

//プロトタイプ宣言
class Stage;
class Batch_Preparat;
class Camera;
class Weapon;
class Enemy;


//プレイヤーキャラクタークラスを作成、初期化（その他キャラはPeopleクラスにて作成可能）
class PlayerChara: public Soldier{

private:
	/* N/A */
public:
	
	//関数の宣言
	PlayerChara( int selchara, int Wpselect_equipment) : Soldier(  selchara, Wpselect_equipment){};//コンストラクタ

	~PlayerChara();//デストラクタ


	//基本的な銃のまとめ関数の宣言
	int ThirdGunSys( Stage *Stg, Batch_Preparat *BatPre);//3人称視点からの銃関連まとめ関数
	int ShoulderGunSys( Batch_Preparat *BatPre, int ScreenPos[2]);//肩射ち視点からの銃関連まとめ関数
	int MoveChara();//キャラを動かします、前後左右に動けます
	int ShoulderGunSysBefore();//キャラクターののち処理を行う関数
	int GunConflictTarget( int ScreenPosArray[2], Stage *Stg, Enemy *Ene);//自分の向くべき方向を調節する関数
	int NormallyPCSystem( Stage *Stg, Batch_Preparat *BatPre, Enemy *Ene, Camera *Cam, int ScreenPos[2]);//普通のゲーム内での処理を行なう関数
	int ChangeWeapon( Batch_Preparat *BatPre);//武器を変更するさせる際に使用する関数
	int GunSystem( Enemy *Ene);//銃について作動させる関数、リロード、次打てるまでの時間計算、敵へのあたり判定、ダメージ計算など

};
