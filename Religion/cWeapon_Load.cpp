/* //////////////////////////////////////////////////////////// */
// ここでは、武器に関することを記述するクラスコードファイルです
// 主に、武器詳細データをロードすることが書かれています
/* //////////////////////////////////////////////////////////// */
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "cWeapon_Gun.h"//銃に関することのクラスヘッダファイル




/*武器に関するデータを格納する関数*/
int Weapon_Gun::GunLoad_Data( const int Wpkind, const int Wpno){

	/* 変数の宣言・初期化 */

	// 定数列挙  "銃弾種類"
	const int _45ACP = 0;// .45ACP
	const int _22L = 1;//  .22L
	const int _9MM = 2;//  .9mm
	const int _5_56MM = 3;// 5.56mm
	const int _5_75MM = 4;// 5.75mm 
	const int _12GAGE = 5;// 12GAGE
	const int _SLUG_SHOT = 6;// Slug Shot
	const int _10GAGE = 7;// 10GAGE
	const int _5_45MM = 8;// 5.45mm
	const int _7_62MM = 9;// 7.62mm
	const int _50BMG = 10;// .50BMG
	const int _40MM = 11;//  40mm
	const int _HEAT = 12;//  HEAT


	// 定数列挙  "銃精度"
	const int S_PULS = 0;	// S+
	const int S = 1;		// S
	const int S_MINUS = 2;	// S-

	const int A_PULS = 3;	// A+
	const int A = 4;		// A
	const int A_MINUS = 5;	// A-

	const int B_PULS = 6;	// B+
	const int B = 7;		// B
	const int B_MINUS = 8;	// B-

	const int C_PULS = 9;	// C+
	const int C = 10;		// C
	const int C_MINUS = 11;	// C-

	// 定数列挙  "連射可能・不可"
	const int Enable_Rapid_Fire = 1;// 可能
	const int Disable_Rapid_Fire = 0;// 不可能


	// ここまで//

	const int GunData[7][6][7] = {

		//品目：使用弾薬, 威力, 射程距離, 精度, 装弾数, マガジン数,  連射できる銃か
		
		// ハンドガン 0
		{	 
			{ _45ACP, 100, 150,	B,		  7,  8, Disable_Rapid_Fire},// M1911
			{ _45ACP,  80, 105,	B,		  5, 10, Disable_Rapid_Fire},// Offficers
			{ _22L,   45,   90,	A,		 50,  4, Enable_Rapid_Fire},// Glock95
			{ _9MM,   80,  180,	A,		 15,  3, Disable_Rapid_Fire},// M92F
			{ _9MM,   80,  150, S_MINUS, 15,  3, Disable_Rapid_Fire},// Cz-75
			{ _9MM,   80,  230,	A,		 15,  3, Disable_Rapid_Fire} // sauerP226
		},

		// サブマシンガン 1
		{
			{ _9MM,     70,  120,	A,		 30,  5, Enable_Rapid_Fire}, // TMP
			{ _45ACP,   70,   75,	B,		 20,  5, Enable_Rapid_Fire}, // INGLAM
			{ _45ACP,   90,  120,	S_MINUS, 25,  4, Enable_Rapid_Fire}, // UMP
			{ _5_56MM, 120,  130,	C_PULS,	 30,  3, Enable_Rapid_Fire}, // PATORIOT
			{ _9MM,     70,  150,	S_PULS,  15,  8, Enable_Rapid_Fire}, // MP5kruz
			{ _5_75MM,  80,  110,	B_MINUS, 50,  2, Enable_Rapid_Fire} // P90
		},

		// ショットガン 2
		{
			{ _12GAGE,     50,  60,	 C,		  5,  4, Disable_Rapid_Fire}, // M31
			{ _12GAGE,     40,  90,	 C_PULS,  7,  3, Disable_Rapid_Fire}, // Benel M3
			{ _SLUG_SHOT, 280,  270, B_MINUS, 7,  3, Disable_Rapid_Fire}, // SPAS-12
			{ _10GAGE,     58,  135, B,		  2,  5, Disable_Rapid_Fire}, // Gold Stalker
			{ _12GAGE,     35,  45,	 C,		  7,  3, Disable_Rapid_Fire} // M870

		},

		// アサルトライフル 3
		{
			{ _5_56MM, 140,  320, A,	   30,  5, Enable_Rapid_Fire}, // M4 A5
			{ _5_45MM, 160,  380, B,	   30,  4, Enable_Rapid_Fire}, // AK-74
			{ _7_62MM, 200,  410, B_MINUS, 20,  5, Enable_Rapid_Fire}, // M14
			{ _5_56MM, 140,  340, A_MINUS, 30,  5, Enable_Rapid_Fire}, // G36
			{ _5_56MM, 140,  340, S_PULS,  30,  5, Enable_Rapid_Fire} // HK 416
		},

		// マシンガン 4
		{
			{ _5_56MM,  90,  440, C_MINUS, 150,  2, Enable_Rapid_Fire}, // MINIMI
			{ _5_56MM,  90,  360, C_PULS,	90,  3, Enable_Rapid_Fire}, // M4 machine
			{ _7_62MM, 110,  400, C,		75,  4, Enable_Rapid_Fire} // RPK
		},

		// ライフル 5 
		{
			{ _7_62MM, 300,  500, A,	   5, 10, Disable_Rapid_Fire}, // M700
			{ _5_56MM, 140,  420, B_PULS, 20,  4, Disable_Rapid_Fire}, // SPR Mk12
			{ _7_62MM, 280,  440, B,	  10,  4, Disable_Rapid_Fire}, // SVD
			{ _7_62MM, 260,  460, B_PULS,  5,  8, Disable_Rapid_Fire}, // PSG-1
			{ _50BMG,  850,  500, C,	   5,  3, Disable_Rapid_Fire} // M82
		},

		// グレネード 6
		{
			{ _40MM, 350,  80,  A,	      6,   2, Disable_Rapid_Fire}, // MGL
			{ _40MM, 400,  100, A,	      1,  15, Disable_Rapid_Fire}, // M79
			{ _HEAT, 280,  180, C,		  1,   4, Disable_Rapid_Fire}, // RPG-7
			{ _HEAT, 340,  140, B_MINUS,  4,   2, Disable_Rapid_Fire} // M202A1
		}
	};

	const double GunDoubleData[7][6][2] = {

		//品目：連射時間, リロード時間
		
		// ハンドガン
		{	 
			{ 2.0, 1.0},// M1911
			{ 2.4, 1.0},// Offficers
			{ 4.3, 0.8},// Glock95
			{ 2.8, 1.3},// M92F
			{ 3.2, 1.3},// Cz-75
			{ 2.4, 1.7} // sauerP226
		},

		// サブマシンガン
		{
			{ 15.0, 2.0}, // TMP
			{ 20.0, 1.4}, // INGLAM
			{ 11.0, 1.3}, // UMP
			{ 13.0, 1.2}, // PATORIOT
			{ 15.0, 1.0}, // MP5kruz
			{ 15.0, 2.8} // P90
		},

		// ショットガン
		{
			{ 1.0,     1.0}, // M31
			{ 1.8,     1.8}, // Benel M3
			{ 1.5,	   1.8}, // SPAS-12
			{ 2.0,     2.7}, // Gold Stalker
			{ 1.0,     1.0} // M870

		},

		// アサルトライフル
		{
			{ 13.0, 1.2}, // M4 A5
			{ 10.0, 1.1}, // AK-74
			{ 12.5, 1.3}, // M14
			{ 12.5, 1.5}, // G36
			{ 11.0, 1.3} // HK 416
		},

		// マシンガン
		{
			{ 10.0,  4.0}, // MINIMI
			{ 13.0,  3.4}, // M4 machine
			{ 10.0, 3.7} // RPK
		},

		// ライフル
		{
			{ 1.0, 2.0}, // M4 A5
			{ 2.0, 2.4}, // AK-74
			{ 1.8, 1.9}, // M14
			{ 2.0, 2.7}, // G36
			{ 0.5, 3.2} // HK 416
		},

		// グレネード
		{
			{ 1.0, 5.7}, // MGL
			{  -1, 2.4}, // M79
			{  -1, 4.5}, // RPG-7
			{ 1.4, 6.4} // M202A1
		}
	};





	Set_Kind( Wpkind);
	Set_Number( Wpno);

	Set_Attack( GunData[Wpkind][Wpno][1]);
	Set_Range( GunData[Wpkind][Wpno][2]);
	Set_Ammo( GunData[Wpkind][Wpno][4]);
	Set_RapidFire( GunData[Wpkind][Wpno][6]);
	Magazine =  GunData[Wpkind][Wpno][5];

	RapidTime = int( 30 / GunDoubleData[Wpkind][Wpno][0] );
	ReloadTime = int( 30 * GunDoubleData[Wpkind][Wpno][1] );

	AmmoKind = GunData[Wpkind][Wpno][0];
	Accuracy = GunData[Wpkind][Wpno][3];

	return 0;
}