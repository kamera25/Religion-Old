/* ///////////////////////////////////////////////////////// */
// ここでは、武器に関することを記述するクラスコードファイルです
// 主に、銃武器関係のことが書かれています
/* /////////////////////////////////////////////////////////  */
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "cWeapon_Gun.h"//銃に関することのクラスヘッダファイル
#include "cenemy.h"//敵クラスの宣言ヘッダファイル
#include "cWeapon_Support.h"//サポート武器に関することのクラスヘッダファイル
#include "cstage.h"//ステージ関係のクラスヘッダファイル
#include "clive.h"//敵やキャラの宣言ヘッダファイル

// 銃武器クラスのコンストラクタ(ロードを行います) //
Weapon_Gun::Weapon_Gun( const int Selectkind, const int Wpkind, const int Wpno){

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

	/* ロードしたい武器によって選択分岐 */
	switch( Wpkind ){
			case 0:{
					GunLoad_Hand( Wpno);//ハンドガン系
					break;
			}
			case 1:{
					GunLoad_SMG( Wpno);//サブマシンガン系
					break;
		   }
			case 2:{
					GunLoad_Shot( Wpno);//ショットガン系
					break;
			}
			case 3:{
					GunLoad_Assault( Wpno);//アサルトライフル系
					break;
			}
			case 4:{
					GunLoad_Machine( Wpno);//マシンガン系
					break;
			}
			case 5:{
					GunLoad_Rifle( Wpno);//ライフル系
					break;
			}
			case 6:{
					GunLoad_Grenade( Wpno);//グレネード系
			}
	}

	
	/* エフェクトビルボードをロードします */
	wsprintf( loadname, "%s\\data\\img\\effect\\explosion1.png", System::path);
	ech = E3DCreateBillboard ( loadname, 96, 96, 0, 1, 1, &EffectNo);
	_ASSERT( ech != 1 );//エラーチェック

	/* エフェクトを予め透過しておく */
	ech = E3DSetBillboardAlpha( EffectNo, 0.0f);
	_ASSERT( ech != 1 );//エラーチェック

	/* エフェクトIDをメンバ変数に代入 */
	Set_Effects( EffectNo);

	/*武器データのロードをする*/
	GunLoad_Data( Wpkind, Wpno);

	return;
}

//  銃武器クラスのデストラクタ(アンロードを行います) //
Weapon_Gun::~Weapon_Gun(){




	return;
}

/* ゲーム中の銃の操作に関することをします */
int Weapon_Gun::WeaponTreatment( const int WeaponLight){

	/* 変数の宣言&初期化 */
	int ech = 0;// エラーチェック変数
	float MuzzleFlashAlpha = 0.0f;//マズルフラッシュスプライトの透明度
	float MuzzlePosArray[3] = {0};// 銃声が鳴っている銃口座標を入れる変数
	D3DXVECTOR3 MuzzlePos( 0.0, 0.0, 0.0);// 銃口位置
	E3DCOLOR4UC MuzzleFlashColor = { 0, 0, 0, 0};// マズルフラッシュの色を指定

	int Ammo = Get_Ammo();
	int Model = Get_Model();

	/* ここまで */



	/* ここから、本格的な処理を行います */
	

	/* 銃口の位置の座標を取得します */
	ech = E3DGetCurrentBonePos( Model, Get_Bones(0), 1, &MuzzlePos);
	_ASSERT( ech != 1 );//エラーチェック

	/* 銃口の位置に爆発エフェクトを置きます */
	ech = E3DSetBillboardPos(  Get_Effects(), MuzzlePos); 
	_ASSERT( ech != 1 );//エラーチェック


	/* どう弾を発射させたかで分岐 */
	switch( Get_NowFireFlag() ){
			case 1:{// 普通の状態で発射

					/*ビルボードを回転させます*/
					ech = E3DRotateBillboard( Get_Effects(), float( rand() % 360), 1);
					_ASSERT( ech != 1 );//エラーチェック

					/* 位置を代入 */
					MuzzlePosArray[0] = MuzzlePos.x;
					MuzzlePosArray[1] = MuzzlePos.y;
					MuzzlePosArray[2] = MuzzlePos.z;
					/* SEの再生 */
					PlayWeaponSound( 0, MuzzlePosArray);

					
					/* マズルフラッシュカウンターを表示させます */
					Set_FlashCounter(4);

					/*連射カウンタに一定数値を代入し射撃を一定停止させます*/
					Set_WaitingTime( RapidTime);

					Set_NowFireFlag(3);
					
					break;
		   }
		   case 2:{// 空の状態で発射

			   		//位置を代入
					MuzzlePosArray[0] = MuzzlePos.x;
					MuzzlePosArray[1] = MuzzlePos.y;
					MuzzlePosArray[2] = MuzzlePos.z;
					//サウンドの再生
					PlayWeaponSound( 1, MuzzlePosArray);

					/*連射カウンタに一定数値を代入し射撃を一定停止させます*/
					Set_WaitingTime( RapidTime);
					Set_NowFireFlag(3);					

					break;
		  }
	}

	/* マズルフラッシュカウンターがオンなら */
	if( 0 < Get_FlashCounter()){

			/* 最初に点灯した時間から、だんだんと光が消えていくようにします */
			switch( Get_FlashCounter() ){
					case 4:{
							MuzzleFlashAlpha = 0.7f;
							MuzzleFlashColor.r = 200;
							MuzzleFlashColor.g = 200;
							MuzzleFlashColor.b = 200;
							break;
				    }
					case 3:{
							MuzzleFlashAlpha = 0.9f;
							MuzzleFlashColor.r = 240;
							MuzzleFlashColor.g = 240;
							MuzzleFlashColor.b = 240;
							break;
					}
					case 2:{
							MuzzleFlashAlpha = 0.6f;
							MuzzleFlashColor.r = 160;
							MuzzleFlashColor.g = 160;
							MuzzleFlashColor.b = 160;
							break;
					}
					case 1:{
							MuzzleFlashAlpha = 0.2f;
							MuzzleFlashColor.r = 50;
							MuzzleFlashColor.g = 50;
							MuzzleFlashColor.b = 50;
					}
					case 0:{// ライトを消します
							MuzzleFlashAlpha = 0.0f;
							MuzzleFlashColor.r = 0;
							MuzzleFlashColor.g = 0;
							MuzzleFlashColor.b = 0;
					}
			}


			/* 透明度を変更する */
			ech = E3DSetBillboardAlpha( Get_Effects(), MuzzleFlashAlpha);
			_ASSERT( ech != 1 );//エラーチェック

			/* ライトを付ける */
			ech = E3DSetPointLight( WeaponLight, MuzzlePos, 700.0f, MuzzleFlashColor);
			_ASSERT( ech != 1 );//エラーチェック
			

			/*フラッシュカウントをひとつ下げる*/
			Set_FlashCounter( Get_FlashCounter() - 1);

	}


	/* 連射カウンタが0以上(打つのが不可能)なら */
	if( 0 < Get_WaitingTime()){
			Set_WaitingTime( Get_WaitingTime() - 1);// 連射カウンタを一つ繰り下げる
			if( Get_WaitingTime() == 0){
					Set_NowFireFlag(0);
			}
	}


	return 0;
}

/* 武器の状態を初期にする関数 */
int Weapon_Gun::InitWeapon(){

	/* それぞれの武器を初期状態にする */
	NowMagazine = Magazine;
	Set_NowAmmo( Get_Ammo());


	return 0;
}

/*ゲーム中の敵とのあたり&攻撃判定を行います。*/
int Weapon_Gun::AttackEnemy( NPC_Head *NPC_H, PlayerChara *PC, int ScreenPosArray[2], Stage *Stg){

	/*変数の初期*/
	int ech = 0;//エラー確認変数
	int EneHitResult = 0;//敵が照準に入っているかの結果を入れます
	int GarbageInt = 0;//いらないデータを格納します
	int NowWpKind = 0;//今の武器の種類を取得します
	bool EnemyConflict = false;//敵に当たった数の合計
	float NowWpRange = 0.0f;//今の武器の射程を代入します
	float EneDistance = 0.0f;//当たった敵のところからの距離が代入されます
	float EneNearDistance = 0.0f;//当たっている一番近い敵の距離が代入されます
	float Wall_HitDistance = 0.0f;//一番近い壁の距離が代入されます。
	D3DXVECTOR3 GunTargetPos( 0.0, 0.0, 0.0);//銃が向くべき座標
	D3DXVECTOR3 WantVec( 0.0, 0.0, 0.0);//「首つけ根」の向きたい方向へのベクトル
	D3DXVECTOR3 BaseVec( 0.0, 0.0, -1.0);//向きの初期方向ベクトル
	D3DXVECTOR3 GarbageD3DVec( 0.0, 0.0, 0.0);//要らないXYZのデータの一次入れ
	POINT ScreenPos = { ScreenPosArray[0], ScreenPosArray[1]};//2Dスクリーン座標構造体
	vector<NPC_t>::iterator it;// イテレータ
	vector<NPC_t>::iterator NearEnemyID;//一番近い敵キャラの識別番号

	/*当たり判定計測中以外 AND */
	if( ( Get_NowFireFlag() != 1) || ( NPC_H->Get_NPC_empty() == true)){
			return 0;
	}

	/*装備をきちんとつけていれば*/
	NowWpKind = Get_Kind();//武器の種類
	NowWpRange = float( Get_Range() * 500);
	EneNearDistance = float(NowWpRange);
	


	/* ///////////////////////////////////////// */
	//まず、状態的に攻撃判定させるかどうか決めます
	/* //////////////////////////////////////// */
	
	/* 武器の種類によって武器の処理を分岐させます。 */
	switch(NowWpKind){
			case 0://ハンドガンなら
			case 2:
			case 3:
			case 4:
			{
					/*通常モード( モデル[0]から取得する )*/
					if( Stg->Stage_GunTarget == 0){//壁データより敵が手前にいたら攻撃可能なので、ここでカーソル上のステージを取得しています
							ech = E3DPickFace( System::scid1, Stg->Stage_hsid[0], ScreenPos, NowWpRange, &GarbageInt, &GarbageInt, &GarbageD3DVec, &GarbageD3DVec, &Wall_HitDistance);
							_ASSERT( ech != 1 );//エラーチェック
					}

					/*当たり判定中にいる敵をチェックします*/
					for( it = NPC_H->Get_NPC_begin(); it != NPC_H->NPC_endit(); it++){//エネミーの数だけ

										ech = E3DPickFace( System::scid1, (*it).NPC_Mdl->Get_BodyModel(), ScreenPos, NowWpRange, &EneHitResult, 
															&EneHitResult, &GarbageD3DVec, &GarbageD3DVec, &EneDistance);
										_ASSERT( ech != 1 );//エラーチェック

										if( (EneHitResult != 0) && ( EneDistance < EneNearDistance) ){
													EneNearDistance = EneDistance;//一番近い敵の距離に更新します
													NearEnemyID = it;//一番近いモデル番号を入れます
													EnemyConflict = true;//近い敵がいることを代入します
										}
					}

					/*もし、当たり判定上に敵がいれば*/
					if( ( EnemyConflict == true) && ( EneNearDistance < Wall_HitDistance)){

							// !!ここに壁との当たり判定が必要!!

							//敵にダメージを与える

							(*NearEnemyID).NPC_Mdl->Set_HP( (*NearEnemyID).NPC_Mdl->Get_HP() - Get_Attack());
					}
			}
	}




	return 0;
}

/* 武器(ここでは銃)を発砲してもよいか確認し、OKなら発射フラグをたてます */
int Weapon_Gun::ChkWeaponLaunch(){

	/* 変数の初期化 */



	/* 発射可能ならフラグを立てます */

	if( ( System::GetKeyData( System::KEY_LEFTMOUSE)) && ( Get_NowFireFlag() == 0)){//左クリックされ、発射可能がオフなら
			if( 0 < Get_NowAmmo() ){//Ammoが残っていれば
					Set_NowFireFlag(1);// 発射状態にする
					Set_NowAmmo( Get_NowAmmo() -1 );// 弾薬をひとつ減らします
			}
			else{//弾なしで空撃ち状態なら
					Set_NowFireFlag(2);//空撃ち状態する
			}
	}


	return 0;
}

/* 武器のリロードを行います */
int Weapon_Gun::ReloadWeapon(){

	
	/* リロードの処理を行います */
	if( ( System::GetKeyData( System::KEY_R) == 1) && ( 0 < NowMagazine)){//Rキーが押されてて、マガジンがあるのなら

					if( ( Get_Ammo() <= Get_NowAmmo() ) && ( NowMagazine == Magazine)){// MAGもAMMOも一個も使ってなければ
							Set_NowAmmo( Get_Ammo() + 1);//AMMOを満タン+1にする
							NowMagazine =  NowMagazine - 1;// マガジンを使用したので-1する
					}
					else if( ( Get_Ammo() != Get_NowAmmo()) && ( Get_NowAmmo() != Get_Ammo() +1 )){//通常のリロードであれば
							Set_NowAmmo( Get_Ammo());//AMMOを満タンにする
							NowMagazine =  NowMagazine - 1;// マガジンを使用したので-1する
					}
	}

	return 0;
}