#pragma once
/*キャラクタークラスの宣言をするヘッダファイル。
//
*/

#include "csoldier.h"// 兵士クラスの宣言ヘッダファイル

//プロトタイプ宣言
class Stage;
class Batch_Render;
class Camera;
class Weapon;
class NPC_Head;


//プレイヤーキャラクタークラスを作成、初期化（その他キャラはPeopleクラスにて作成可能）
class PlayerChara: public Soldier{

private:
	/* 変数の宣言 */
	int ChangePerspectiveMode;// 視点変更の状態変数


public:
	
	//関数の宣言
	PlayerChara( int selchara, int Wpselect_equipment);//コンストラクタ

	~PlayerChara();//デストラクタ


	//基本的な銃のまとめ関数の宣言
	int ThirdGunSys( Stage *Stg, Batch_Render *BatPre);//3人称視点からの銃関連まとめ関数
	int ShoulderGunSys( Batch_Render *BatPre, int ScreenPos[2]);//肩射ち視点からの銃関連まとめ関数
	int ThreePersonGunSys( Batch_Render *BatPre, int ScreenPos[2]);// 三人称視点からの銃関連まとめ関数
	int MoveChara();//キャラを動かします、前後左右に動けます
	int ShoulderGunSysBefore();//キャラクターののち処理を行う関数
	int GunConflictTarget( int ScreenPosArray[2], Stage *Stg, NPC_Head *NPC_H);//自分の向くべき方向を調節する関数
	int NormallyPCSystem( Stage *Stg, Batch_Render *BatPre, NPC_Head *NPC_H, Camera *Cam, int ScreenPos[2]);//普通のゲーム内での処理を行なう関数
	int ChangeWeapon( Batch_Render *BatPre);//武器を変更するさせる際に使用する関数
	int GunSystem( NPC_Head *NPC_H);//銃について作動させる関数、リロード、次打てるまでの時間計算、敵へのあたり判定、ダメージ計算など
	int TurnBackDir(  int Qid, D3DXVECTOR3 WantDeg, int FixFlag);// 肩を回転させる
	int PCDashControl();// ダッシュ関係の処理を行います
	int PCSideAvoidanceControl();// 横っ飛びの処理をさせます。
	float RegulateMoveSpeed( float Acceleration, float FixedMoveSpeed, float LimitSpeed);// キャラクタの動くスピードを設定、制限します
	int EventPublish();//ゲームオーバやクリアなどのイベントを発行します
	int StatusReset();// ソルジャークラスの状態を初期に戻します(リスタート等で利用)
	int JumpPosition( D3DXVECTOR3 CatPos, const double Degree, const double UpAcceleration, const double Speed);// 座標を指定して、ジャンプをさせる
	int MoveModel( double WantDeg, double SumSpeed);
};
