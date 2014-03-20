#pragma once
/*キャラクタークラスのキャラをするヘッダファイル。
//
*/

//プロトタイプ宣言
class Stage;
class Batch_Preparat;
class Camera;
class Weapon;
class Enemy;


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
	int ShoulderGunSys( Batch_Preparat *BatPre, int ScreenPos[2]);//肩射ち視点からの銃関連まとめ関数
	int GunPutOnHand( Weapon *Wep);//現在持ってる銃を持つためのモーション・システムを管轄する関数
	int MoveChara();//キャラを動かします、前後左右に動けます
	int MovePosOnGround( Stage *Stg);//キャラクターをグラウンドの上に置くための関数
	int ShoulderGunSysBefore( Weapon *Wep);//キャラクターののち処理を行う関数
	int GunConflictTarget( int ScreenPosArray[2], Stage *Stg, Enemy *Ene, Weapon *Wep);//自分の向くべき方向を調節する関数
	int NormallyPCSystem( Stage *Stg, Batch_Preparat *BatPre, Enemy *Ene, Camera *Cam, Weapon *Wep, int ScreenPos[2]);//普通のゲーム内での処理を行なう関数
	int GunSystem( Enemy *Ene);//銃について作動させる関数、リロード、次打てるまでの時間計算、敵へのあたり判定、ダメージ計算など
};
