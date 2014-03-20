#pragma once
/* 人間クラスの宣言をするヘッダファイル。
// !人間!クラスは生物クラスを継承してつくられています
*/
#include "ccreature.h"// 生物クラスのヘッダファイル

/* 人間クラス */
class People: public Creature{

private:

	/* 変数の宣言 */

	// モーションを状態を示す変数の指定
	int UpMotion;//上半身のモーションの指定
	int UnderMotion;//下半身のモーションの指定

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

	// プレイヤーキャラクターの状態変数
	int Attitude;//自分の姿勢状態を入れる変数
	int MyState;//自分の動作状態を入れる変数
	int AirOnPC;//自分が空中にいるか指定する変数

	//プレイヤーキャラクターの向きの変数
	float PC_Deg_XZ;
	float PC_Deg_Y;

	//プレイヤーの情報変数
	double Acceleration;//地面への加速度を代入する変数
	double MoveSpeed;//平面加速度を入れる変数

public:

	virtual int Batch_PeopleMotion() = 0;// 人間のモーションや姿勢などを設定します(仮想関数)
	virtual ~People(){};//仮想コンストラクタ

	/* クラス静動変数 */
	static const int NORMAL = 0;// 通常状態
	static const int KICK = 1;// キック状態
	static const int RUN = 2;// ダッシュ状態
	static const int LEFT_SJUMP = 3;// 左横っ飛び
	static const int RIGHT_SJUMP = 4;// 右横っ飛び

	/* アシスト(取得・代入)関数の宣言 */
	int Get_UpMotion() const;
	int Set_UpMotion( int Number);
	int Get_UnderMotion() const;
	int Set_UnderMotion( int Number);
	int Get_Attitude() const;
	int Set_Attitude( int Number);
	int Get_MyState() const;
	int Set_MyState( int Number);
	int Set_AirOnPC( int Number);
	float Get_PC_Deg_XZ() const;
	float Set_PC_Deg_XZ( float Number);
	float Get_PC_Deg_Y() const;
	float Set_PC_Deg_Y( float Number);
	double Get_Acceleration() const;
	double Set_Acceleration( double Number);
	double Get_MoveSpeed() const;
	double Set_MoveSpeed( double Number);

	int Get_AirOnPC();

};