#pragma once
/*生物クラスのキャラ・敵の宣言をするヘッダファイル。
//
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "c_batch_preparat.h"//描画に必要なクラスの宣言ヘッダファイル
#include "cenemy.h"//敵クラスの宣言ヘッダファイル
#include "ccamera.h"//カメラに関することのクラスヘッダファイル
class Batch_Preparat;//循環変数対策

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
	
	/*
	//
	//各データにはそれぞれの固有データを保持してます
	//
	// 一番目の要素には武器の種類に夜データが格納されています [0]メインウェポン [1]サブウェポン [2]グレネード
	//
	// 先頭[0]番にはモデルデータが格納されています [0]モデルのhsid [1]武器のスプライト画像 [2]武器の当たりモデルのhsid [3]使用済み弾薬のhsid
	//
	// 先頭[1]番には銃についての情報が格納されています [0]武器の種類 [1]武器のナンバー [2]弾薬の最大値
	//												   [3]マガジンの最大値 [4]射程能力 [5]威力
	//
	// 先頭[2]番にはボーンデータが格納されています [0]銃口手前 [1]銃口先 [2]飛弾先 [3]銃弾丸ストック [4]当たり判定モデル一番先
	//												[5]当たり判定モデル一番手前
	//
	// 先頭[3]番には弾薬等のゲーム中の情報が格納されています [0]現在の弾薬数 [1]マガジン数
	*/

	int wp_data[3][4][6];//武器の情報配列


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
	0:通常状態	1:キック状態  2:ダッシュ状態
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

	int GunLoad( int selwp_kind, int gunkind, int gunno);//武器をロードするための関数

	//基本的な銃のまとめ関数の宣言
	int ThirdGunSys( Stage *Stg, Batch_Preparat *BatPre);//3人称視点からの銃関連まとめ関数
	int ShoulderGunSys( Stage *Stg, Batch_Preparat *BatPre, Enemy *Ene, Camera *Cam);//肩射ち視点からの銃関連まとめ関数
	int GunPutOnHand();//現在持ってる銃を持つためのモーション・システムを管轄する関数
	int MoveChara();//キャラを動かします、前後左右に動けます
	int MovePosOnGround( Stage *Stg);//キャラクターをグラウンドの上に置くための関数
	int ShoulderGunSysBefore();//キャラクターののち処理を行う関数
	int GunConflictTarget( POINT ScreenPos, Stage *Stg, Enemy *Ene);//自分の向くべき方向を調節したり、射撃したりする関数
	int NormallyPCSystem( Stage *Stg, Batch_Preparat *BatPre, Enemy *Ene, Camera *Cam);//普通のゲーム内での処理を行なう関数
};
