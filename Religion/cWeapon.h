#pragma once
/* /////////////////////////////////////// */
// 武器クラスのキャラをするヘッダファイル。
/* /////////////////////////////////////// */
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル


//プロトタイプ宣言
class Enemy;
class PlayerChara;
class Stage;

/* 武器クラス(Gun/Supportのスーパークラス) */
class Weapon{

private:

	/* 変数の宣言 */
	/* データ編 */
	int Model;//  武器モデルID
	int Sprite;// スプライト画像ID
	int Effects;//  武器のエフェクトを格納します
	int Sounds[2];//  武器関連の音声データを格納します

	int Kind;//  武器の種類
	int Number;//　武器の識別番号
	int Attack;//  武器の威力
	int Ammo;//  武器の銃弾数 or 投げ可能数

		
	// [0]銃口手前 [1]銃口先 [2]飛弾先 [3]銃弾丸ストック [4]当たり判定モデル一番先 [5]当たり判定モデル一番手前
	int Bones[6];// ボーン情報を格納します

	/* ゲーム中の変数 */
	int NowAmmo;// ゲーム中の銃弾数 or 投げ可能数
	int NowFireFlag;//  ゲーム中で武器を打っているかのフラグ
	int FlashCounter;// 武器の光っている部分(ビルボード&ライト)をカウントする変数
	int WaitingTime;// 銃を撃ったときの次発射できるまでの待機時間

public:

	/* 静動メンバ変数 */	
	static const int PlayerSide = 0;// プレイヤーキャラクタ側
	static const int EnemySide = 1;// エネミーキャラクタ側


	/* 子クラスで出てくる仮想関数 */
	//virtual int WpLoad( const int Selectkind, const int Wpkind, const int Wpno) = 0;//武器をロードするための関数(仮想)
	Weapon();
	virtual ~Weapon();// 仮想コンストラクタ

	int PlayWeaponSound( const int PlayNo, const float MuzzlePosArray[3]);// プリセットしてある武器関連音源を再生します
	virtual int ChkWeaponLaunch(){ _ASSERT( 0 );return -1;};// 武器を発砲・投げしてもよいか確認し、OKなら発射フラグをたてます
	virtual int AttackEnemy( Enemy *Ene, PlayerChara *PC, int ScreenPosArray[2], Stage *Stg){ _ASSERT( 0 );return -1;};// ゲーム中の敵とのあたり&攻撃判定を行います。
	virtual int InitWeapon(){ _ASSERT( 0 );return -1;};// 武器の状態を初期にする
	virtual int ReloadWeapon(){ _ASSERT( 0 );return -1;}// 武器のリロードを行います
	virtual int WeaponTreatment( const int WeaponLight){ _ASSERT( 0 );return -1;};

	/* アシスト関数 */
	int Set_Model( const int Number);
	int Get_Model() const;
	int Set_Sprite( const int Number);
	int Get_Sprite() const;
	int Set_Effects( const int Number);
	int Get_Effects() const;
	int Set_Sounds( const int Number, const int ArrayNum);
	int Get_Sounds( const int ArrayNum) const;
	int Set_Bones( const int Number, const int ArrayNum);
	int Get_Bones( const int ArrayNum) const;
	int Set_Kind( const int Number);
	int Get_Kind() const;
	int Set_Number( const int Numbers);
	int Get_Number() const;
	int Set_Attack( const int Number);
	int Get_Attack() const;
	int Set_Ammo( const int Number);
	int Get_Ammo() const;
	int Get_FlashCounter();
	int Set_FlashCounter( const int Number);
	int Get_NowAmmo();
	int Set_NowAmmo( const int Number);
	int Get_WaitingTime() const;
	int Set_WaitingTime( const int Number);
	int Get_NowFireFlag() const;
	int Set_NowFireFlag( int Number);

	/* 仮想関数 */
	virtual int Get_NowMagazine() const;
	virtual int Get_Magazine() const;
	virtual int Get_Range() const;
};


