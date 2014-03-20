/* ///////////////////////////////////////////////////////// */
// ここでは、武器に関することを記述するクラスコードファイルです
// 主に、サポート武器関係のことが書かれています
/* /////////////////////////////////////////////////////////  */
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "cWeapon_Support.h"//サポート武器に関することのクラスヘッダファイル
#include "cstage.h"//ステージ関係のクラスヘッダファイル


// サポート武器クラスのコンストラクタ(ロードを行います) //
Weapon_Support::Weapon_Support( const int Wpno){

	/* 変数の初期化 */
	int ech = 0;
	int EffectNo = 0;
	char loadname[256] = "";


	/*すでに銃を取得しており、その銃データに上書きするなら*/
	/*if( Get_Model() != -1){//選択中のカテゴリにデータがあるのなら
				ech = E3DDestroyHandlerSet( Get_Model());
				_ASSERT( ech != 1 );//エラーチェック

				ech = E3DDestroySprite( Get_Sprite());//スプライトを削除します
				_ASSERT( ech != 1 );//エラーチェック
	}*/

	/* サポート武器をロード */
	WpLoad_Support( Wpno);

	
	/* エフェクトビルボードをロードします */
	wsprintf( loadname, "%s\\data\\img\\effect\\explosion1.png", System::path);
	ech = E3DCreateBillboard ( loadname, 96, 96, 0, 1, 1, &EffectNo);
	_ASSERT( ech != 1 );//エラーチェック

	/* エフェクトを予め透過しておく */
	ech = E3DSetBillboardAlpha( EffectNo, 0.0f);
	_ASSERT( ech != 1 );//エラーチェック

	/* エフェクトIDをメンバ変数に代入 */
	Set_Effects( EffectNo);

	/* サポート武器データのロードをする */
	SupportLoad_Data( 7, Wpno);

	return;
}

// サポート武器クラスのデストラクタ(アンロードを行います) //
Weapon_Support::~Weapon_Support(){




	return;
}

int Weapon_Support::SupportLoad_Data( int Wpkind, int Wpno){

		/* 変数の宣言・初期化 */

	// 定数列挙  "連射可能・不可"
	const int Enable_Rapid_Fire = 0;// 可能
	const int Disable_Rapid_Fire = 1;// 不可能


	// ここまで//

	const int GunData[4][3] = {

		//品目： 威力, 射程距離, 装弾数
		
		// ハンドガン

			{ 350,  15, 5},// M26
			{ 280,  18, 5},// M67
			{  50,  60, 5},// M18
			{ 420,   3, 3},// C4
	};



	Set_Kind( Wpkind);
	Set_Number( Wpno);

	Set_Attack( GunData[Wpno][0]);
	Set_Range( GunData[Wpno][1]);
	Set_Ammo( GunData[Wpno][2]);


	return 0;
}

/* 武器の情報を初期化する */
int Weapon_Support::InitWeapon(){

	/* それぞれの武器を初期状態にする */
	Set_NowAmmo( Get_Ammo());

	return 0;
}

/* ゲーム中の敵とのあたり&攻撃判定を行います。 */
int Weapon_Support::AttackEnemy( NPC_Head *NPC_H, PlayerChara *PC, int ScreenPosArray[2], Stage *Stg){



	return 0;
}

/* ゲーム中の武器の操作に関することをします */
int Weapon_Support::WeaponTreatment( const int WeaponLight, Stage *Stg){

	int ech = 0;// エラーチェック変数
	static float Acceleration = 0.0f;//グレネードの落ちる加速度
	//static int sw=0;
	static bool HitGranadeOnGround = false;// グレネードが地面にあたったか
	int Garbage;
	int Revface;// 裏面かどうか
	int GroundResult = 0;//地面の当たり判定の結果
	D3DXVECTOR3 BefGranadePos( 0.0, 0.0, 0.0);
	D3DXVECTOR3 AftGranadePos( 0.0, 0.0, 0.0);//グレネードを置く座
	D3DXVECTOR3 GranadePos( 0.0, 0.0, 0.0);
	D3DXVECTOR3 GroundOnPos( 0.0, 0.0, 0.0);//地面の座標
	D3DXVECTOR3 ReflectVec( 0.0, 0.0, 0.0);//反射座標

	/* グレネードのみの処理なのです！！ */
	if( Get_NowFireFlag() == 0){// グレネードを構えているときなら
			Acceleration = 0.0f;
	}
	else if( Get_NowFireFlag() == 1){// グレネードを投げているときなら
		

			/* グレネードの軌道を計算します */
			ech = E3DGetPos( Get_Model(), &BefGranadePos);
			_ASSERT( ech != 1 );//エラーチェック

			Acceleration = Acceleration - 7.0f;

			if( HitGranadeOnGround == false)
			{
				AftGranadePos = BefGranadePos;
				AftGranadePos.y = BefGranadePos.y + Acceleration;

			}

			ech = E3DSetPos( Get_Model(), AftGranadePos);
			_ASSERT( ech != 1 );//エラーチェック

		
			/* 地面との当たり判定を取ります */
			//ech = E3DChkConfGround( Get_Model(), Stg->Stage_hsid[0], 1, 100000, -1000, &GroundResult, &GroundOnPos, &ReflectVec);
			//_ASSERT( ech != 1 );//エラーチェック
			ech = E3DChkConfLineAndFace( BefGranadePos, AftGranadePos, Stg->Stage_hsid[0], 1, &GroundResult
										, &Garbage, &GroundOnPos, &ReflectVec, &Revface);


			/* 地面からほとんど離れてなく、表面なら */
			//float HeightFromGround = GranadePos.y - GroundOnPos.y;
			if( GroundResult != -1 && Revface == 0){

					AftGranadePos.y = GroundOnPos.y;

					/* 反動の加速度を加える */
					Acceleration = ReflectVec.y * abs(Acceleration) ;
			}



			//Acceleration = Acceleration + 7.0f;
			//if( 100.0f <= Acceleration) Acceleration = 100.0f;// 空気抵抗を考慮する

	}





	return 0;
}



/* 武器を発砲・投げしてもよいか確認し、OKなら発射フラグをたてます */
int Weapon_Support::ChkWeaponLaunch(){;

	/* 変数の初期化 */
	 ;//キー情報配列を作成
	static int KeyContinuity = 0;


	/* 発射可能ならフラグを立てます */
	if( 10 <= KeyContinuity ){
				KeyContinuity = 10;
				if( ( System::GetKeyData( System::KEY_LEFTMOUSE) == 0) && ( Get_NowFireFlag() == 0)){//左クリックが話されたら
						Set_NowFireFlag(1);// 発射状態にする
						Set_NowAmmo( Get_NowAmmo() -1 );// 弾薬をひとつ減らします
				}
	}

	/* キーのチェックを行います */
	if( System::GetKeyData( System::KEY_LEFTMOUSE)){
			KeyContinuity = KeyContinuity + 1;
	}
	else{
			KeyContinuity = 0;
	}




	return 0;
}