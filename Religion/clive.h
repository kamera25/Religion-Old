#pragma once
/*キャラクタークラスのキャラをするヘッダファイル。
//
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "cweapon.h"//武器に関することのクラスヘッダファイル
#include "c_batch_preparat.h"//描画に必要なクラスの宣言ヘッダファイル
#include "cenemy.h"//敵クラスの宣言ヘッダファイル
#include "ccamera.h"//カメラに関することのクラスヘッダファイル

class Batch_Preparat;//循環変数対策
class Weapon;//循環変数対策


//プレイヤーキャラクタークラスを作成、初期化（その他キャラはcharaクラスにて作成可能）
class PlayerChara{

public:

	//変数の宣言

	int MaxHP;//キャラクタの最大HP
	int HP;//キャラクタのHP
	int Stamina;//キャラクタのスタミナ

	//モデルデータ
	int cha_hsid[2];//キャラクタのモデルID [0]ノーマルモデルのhsid [1]手のモデルのhsid
	int DummyModel;//ダミーモデルのモデルID
	
	/*
	//bone配列にはボーンが格納されます [0]もち手右 [1]もち手先右 [2]おなか
	// [3] 
	*/
	int bone[10];//キャラクターの骨を格納します

	/*
	// [0] 銃の向き [1] 銃の当たり判定モデルの向き
	// [2] モデル座標の向き [3] 銃の方向、PCの姿勢 [4]当たり判定モデルの向き
	*/
	int Qid[10];//クオンターニオンの識別IDを格納します
	





	//アイテムデータ
	int BringWp;//ステージで拾った武器
	int Ammo[4];//手持ちの弾薬データを格納
	int Recovery[5][2];//手持ちの回復アイテムデータの格納
	int Key[10];//手持ちの回復アイテムデータの格納
	int Equipment[3];//手持ちの装備アイテムデータの格納

	//プレイヤーキャラクターの状態変数
	int Wp_equipment;//所持している武器の種類
	int Attitude;//自分の姿勢状態を入れる変数
	int MyState;//自分の動作状態を入れる変数
	int AirOnPC;//自分が空中にいるか指定する変数


	/*説明*//*
	Atitude変数
	0:立ち  1:しゃがみ
	//
	MyState変数
	0:通常状態	1:キック状態  2:ダッシュ状態  3:左横っ飛び状態　4:右横っ飛び状態
	//
	AirOnPC変数
	0:地上  1:空中
	*/


	//プレイヤーの情報変数
	double Acceleration;//地面への加速度を代入する変数
	double MoveSpeed;//平面加速度を入れる変数

	//モーションを状態を示す変数の指定
	int UpMotion;//上半身のモーションの指定
	int UnderMotion;//下半身のモーションの指定

	//プレイヤーキャラクターの向きの変数
	float PC_Deg_XZ;
	float PC_Deg_Y;
	
	//関数の宣言
	PlayerChara(int selchara, int Wp_equipment);//コンストラクタ
	~PlayerChara();//デストラクタ


	//基本的な銃のまとめ関数の宣言
	int ThirdGunSys( Stage *Stg, Batch_Preparat *BatPre);//3人称視点からの銃関連まとめ関数
	int ShoulderGunSys( Batch_Preparat *BatPre, Camera *Cam, int ScreenPos[2]);//肩射ち視点からの銃関連まとめ関数
	int GunPutOnHand( Weapon *Wep);//現在持ってる銃を持つためのモーション・システムを管轄する関数
	int MoveChara();//キャラを動かします、前後左右に動けます
	int MovePosOnGround( Stage *Stg);//キャラクターをグラウンドの上に置くための関数
	int ShoulderGunSysBefore( Weapon *Wep);//キャラクターののち処理を行う関数
	int GunConflictTarget( int ScreenPosArray[2], Stage *Stg, Enemy *Ene, Weapon *Wep);//自分の向くべき方向を調節する関数
	int NormallyPCSystem( Stage *Stg, Batch_Preparat *BatPre, Enemy *Ene, Camera *Cam, Weapon *Wep);//普通のゲーム内での処理を行なう関数
	int GunSystem( Enemy *Ene);//銃について作動させる関数、リロード、次打てるまでの時間計算、敵へのあたり判定、ダメージ計算など
};
