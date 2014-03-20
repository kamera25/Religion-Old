/*ここでは、武器に関することを記述するクラスコードファイルです
//
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "cweapon.h"//武器に関することのクラスヘッダファイル

#include "cenemy.h"//敵クラスの宣言ヘッダファイル
#include "cstage.h"//ステージ関係のクラスヘッダファイル
#include "clive.h"//敵やキャラの宣言ヘッダファイル


/*武器の音声を再生します(3DSE専用)*/
int Weapon::PlayWeaponSound( const int Wp_equipment, const int PlayNo, const float MuzzlePosArray[3]){

	/*変数の初期化*/
	int ech = 0;//エラー確認変数
	D3DXVECTOR3 MuzzleFlashSound( 340.0, 340.0, 340.0);//マズルフラッシュサウンドの速度XYZ
	D3DXVECTOR3 MuzzlePos( MuzzlePosArray[0], MuzzlePosArray[1], MuzzlePosArray[2]);//マズルフラッシュサウンドの速度XYZ


	/*音の位置と速さを指定します*/
	ech = E3DSet3DSoundMovement( WeaponSoundEfeect[Wp_equipment][PlayNo], MuzzlePos, MuzzleFlashSound);
	_ASSERT( ech != 1 );//エラーチェック

	/*発射音を鳴らします*/
	ech = E3DPlaySound( WeaponSoundEfeect[Wp_equipment][PlayNo], 0, 0, 0);
	_ASSERT( ech != 1 );//エラーチェック


	return 0;
}


// ゲーム中の銃の操作に関することをします
int Weapon::TreatmentWhileGame( const int Wp_equipment){

	/*変数の初期化*/
	int ech = 0;
	int keyin[20] = {0};
	float LightDistance = 0.0f;//光が届く距離
	float MuzzleFlashAlpha = 0.0f;//マズルフラッシュの透明度
	float MuzzlePosArray[3];//マズルフラッシュを表示させる座標配列 
	static int MuzzleFlashConter = 0;//マズルフラッシュカウンター
	D3DXVECTOR3 MuzzlePos( 0.0, 0.0, 0.0);//銃口位置	
	E3DCOLOR4UC MuzzleFlashColor = { 0, 0, 0, 0};//マズルフラッシュの色を指定

	/*キーを取得する*/
	System::GetKeyData(keyin);



	if( Wp_equipment != -1){//武器があれば

			/*変数の初期化*/
			const int NowAmmo = WeaponDataWhileGame[Wp_equipment][0]; //現在の弾薬数
			const int NowMag = WeaponDataWhileGame[Wp_equipment][1]; //現在のマガジン数
			const int WeaponAmmo = WeaponData[Wp_equipment][2]; //武器性能上の弾薬数



			/*武器に新しいモーションを当てる*/
			ech = E3DSetNewPoseML( WeaponModel[Wp_equipment]);
			_ASSERT( ech != 1 );//エラーチェック


			if( WeaponBone[Wp_equipment][0] != 0){
				/*銃の置くボーンの座標を求めます*/
				ech = E3DGetCurrentBonePos( WeaponModel[Wp_equipment], WeaponBone[Wp_equipment][0], 1, &MuzzlePos);
				_ASSERT( ech != 1 );//エラーチェック
			}

			/*重厚の位置に爆発エフェクトを置きます*/
			ech = E3DSetBillboardPos( WeaponEffect[Wp_equipment][0], MuzzlePos); 
			_ASSERT( ech != 1 );//エラーチェック

			if( WeaponFireFlag == 1){

						/*ビルボードを回転させます*/
						ech = E3DRotateBillboard( WeaponEffect[Wp_equipment][0], float( rand() % 360), 1);
						_ASSERT( ech != 1 );//エラーチェック

						//位置を代入
						MuzzlePosArray[0] = MuzzlePos.x;
						MuzzlePosArray[1] = MuzzlePos.y;
						MuzzlePosArray[2] = MuzzlePos.z;
						//サウンドの再生
						PlayWeaponSound( Wp_equipment, 0, MuzzlePosArray);

						/*変数操作*/

						// マズルフラッシュカウンターを表示させます
						MuzzleFlashConter = 4;
						//弾薬をひとつ減らします
						WeaponDataWhileGame[Wp_equipment][0] = WeaponDataWhileGame[Wp_equipment][0] - 1;
						/*連射カウンタに一定数値を代入し射撃を一定停止させます*/
						WeaponRapidFire = WeaponData[Wp_equipment][6];

			}
			if( WeaponFireFlag == 2){//弾なしで空撃ち状態なら

						//位置を代入
						MuzzlePosArray[0] = MuzzlePos.x;
						MuzzlePosArray[1] = MuzzlePos.y;
						MuzzlePosArray[2] = MuzzlePos.z;
						//サウンドの再生
						PlayWeaponSound( Wp_equipment, 1, MuzzlePosArray);

						/*変数操作*/

						/*連射カウンタに一定数値を代入し射撃を一定停止させます*/
						WeaponRapidFire = WeaponData[Wp_equipment][6];
			}


			if( ( keyin[4] == 1) && ( 0 < NowMag) && //Rキーが押されてて //リロードできる状態(Magがあり、AMMOが満タンでないか銃未使用)でリロードするなら
				/**/ ( ( NowAmmo < WeaponAmmo) || ( NowMag == WeaponData[Wp_equipment][3]))){ 

					if( ( WeaponData[Wp_equipment][0] != 3) && ( WeaponData[Wp_equipment][0] != 7) && //グレネードでなく、ショットガンでもなければ
					/**/( NowAmmo >= WeaponAmmo) && ( NowMag == WeaponData[Wp_equipment][3])){// MAGもAMMOも一個も使ってなければ

							WeaponDataWhileGame[Wp_equipment][0] = WeaponAmmo + 1;//AMMOを満タン+1にする
					}
					else{//通常のリロードであれば

							WeaponDataWhileGame[Wp_equipment][0] = WeaponAmmo;//AMMOを満タンにする
					}
					//
					WeaponDataWhileGame[Wp_equipment][1] -= 1;//MAGをひとつ減らす
			}	


			/*マズルフラッシュカウンターがオンなら*/
			if( 0 < MuzzleFlashConter){

				if( MuzzleFlashConter == 4){
							MuzzleFlashAlpha = 0.7f;
							MuzzleFlashColor.r = 200;
							MuzzleFlashColor.g = 200;
							MuzzleFlashColor.b = 200;
				}
				if( MuzzleFlashConter == 3){
							MuzzleFlashAlpha = 0.9f;
							MuzzleFlashColor.r = 240;
							MuzzleFlashColor.g = 240;
							MuzzleFlashColor.b = 240;
				}
				if( MuzzleFlashConter == 2){
							MuzzleFlashAlpha = 0.6f;
							MuzzleFlashColor.r = 160;
							MuzzleFlashColor.g = 160;
							MuzzleFlashColor.b = 160;
				}
				if( MuzzleFlashConter == 1){
							/*ライトを無効にする*/
							MuzzleFlashAlpha = 0.2f;
							MuzzleFlashColor.r = 0;
							MuzzleFlashColor.g = 0;
							MuzzleFlashColor.b = 0;
				}

				/*透明度を変更する*/
				ech = E3DSetBillboardAlpha( WeaponEffect[Wp_equipment][0], MuzzleFlashAlpha);
				_ASSERT( ech != 1 );//エラーチェック
				/*ライトを付ける*/
				if( MuzzleFlashConter != 1){
							ech = E3DSetPointLight( WeaponMuzzleLight[Wp_equipment], MuzzlePos, 700.0f, MuzzleFlashColor);
							_ASSERT( ech != 1 );//エラーチェック
				}
				else{//ライト消灯のお時間です
							ech = E3DSetPointLight( WeaponMuzzleLight[Wp_equipment], MuzzlePos, 0.0f, MuzzleFlashColor);
							_ASSERT( ech != 1 );//エラーチェック			
				}


				/*爆発のエフェクトを(すべてのビルボード)の描画*/
				ech = E3DRenderBillboard( System::scid1, 0);
				_ASSERT( ech != 1 );//エラーチェック

				/*フラッシュカウントをひとつ下げる*/
				MuzzleFlashConter = MuzzleFlashConter -1;

				/*透明度を変更する*/
				if( MuzzleFlashConter == 0){//カウントが0になったら
							ech = E3DSetBillboardAlpha( WeaponEffect[Wp_equipment][0], 0.0f);
							_ASSERT( ech != 1 );//エラーチェック	
				}
			}

			/*連射停止カウンタがオンなら*/
			if( 0 < WeaponRapidFire){
					WeaponRapidFire = WeaponRapidFire - 1;//連射停止カウンタを一つ繰り下げる
			}
	}

	return 0;
}
/*ゲーム中の敵とのあたり&攻撃判定を行います。*/
int Weapon::AttackEnemy( Enemy *Ene, PlayerChara *PC, int ScreenPosArray[2], Stage *Stg){

	/*変数の初期*/
	int ech = 0;//エラー確認変数

	int NowWpKind = 0;//今の武器の種類を取得します
	int NearEnemyID = 0;//一番近い敵キャラの識別番号
	int EnemyConflict = 0;//敵に当たった数の合計
	int EneHitResult = 0;//敵が照準に入っているかの結果を入れます
	int GarbageInt = 0;//いらないデータを格納します
	float NowWpRange = 0.0f;//今の武器の射程を代入します
	float EneDistance = 0.0f;//当たった敵のところからの距離が代入されます
	float EneNearDistance = 0.0f;//当たっている一番近い敵の距離が代入されます
	float Wall_HitDistance = 0.0f;//一番近い壁の距離が代入されます。
	D3DXVECTOR3 GunTargetPos( 0.0, 0.0, 0.0);//銃が向くべき座標
	D3DXVECTOR3 WantVec( 0.0, 0.0, 0.0);//「首つけ根」の向きたい方向へのベクトル
	D3DXVECTOR3 BaseVec( 0.0, 0.0, -1.0);//向きの初期方向ベクトル
	D3DXVECTOR3 GarbageD3DVec( 0.0, 0.0, 0.0);//要らないXYZのデータの一次入れ
	POINT ScreenPos = { ScreenPosArray[0], ScreenPosArray[1]};//2Dスクリーン座標構造体


	/*装備をきちんとつけていれば*/
	if( PC->Get_Wp_equipment() != -1){

			NowWpKind = GetWeaponData( PC->Get_Wp_equipment(), 0);//武器の種類
			NowWpRange = float( GetWeaponData( PC->Get_Wp_equipment(), 4) * 500);//
			EneNearDistance = float(NowWpRange);
	}


	/**/
	//まず、状態的に攻撃判定させるかどうか決めます
	/**/

	/*発射状態で、敵がいるなら*/
	if( ( GetWeaponFireFlag() == 1) && ( 0 < Ene->EnemyNum)){

			//ハンドガンなら
			if( ( NowWpKind == 1) || ( NowWpKind == 4) || ( NowWpKind == 5)){

					/*通常モード( モデル[0]から取得する )*/
					if( Stg->Stage_GunTarget == 0){//壁データより敵が手前にいたら攻撃可能なので、ここでカーソル上のステージを取得しています
							ech = E3DPickFace( System::scid1, Stg->Stage_hsid[0], ScreenPos, NowWpRange, &GarbageInt, &GarbageInt, &GarbageD3DVec, &GarbageD3DVec, &Wall_HitDistance);
							_ASSERT( ech != 1 );//エラーチェック
					}

					/*当たり判定中にいる敵をチェックします*/
					for( int i=0; i < Ene->EnemyNum; i++){//エネミーの数だけ

										ech = E3DPickFace( System::scid1, Ene->Ene[i]->Get_BodyModel(), ScreenPos, NowWpRange, &EneHitResult, &EneHitResult, &GarbageD3DVec, &GarbageD3DVec, &EneDistance);
										_ASSERT( ech != 1 );//エラーチェック
										if( (EneHitResult != 0) && ( EneDistance < EneNearDistance) ){
													EneNearDistance = EneDistance;//一番近い敵の距離に更新します
													NearEnemyID = i;//一番近いモデル番号を入れます
													EnemyConflict = 1;//近い敵がいることを代入します
										}
					}

					/*もし、当たり判定上に敵がいれば*/
					if( ( EnemyConflict == 1) && ( EneNearDistance < Wall_HitDistance)){

							// !!壁との当たり判定が必要!!

							//敵にダメージを与える
							Ene->Ene[NearEnemyID]->Set_HP( Ene->Ene[NearEnemyID]->Get_HP() - GetWeaponData( PC->Get_Wp_equipment(), 5));
					}
			}
	}



	return 0;
}
/*武器を発射したかどうかの確認を行います*/
int Weapon::ChkWeaponLaunch( const int Wp_equipment){

	/*変数の初期化*/
	int keyin[20];//キー情報配列を作成
	WeaponFireFlag = 0;//一周したらフラグをオフにする

	/*キーを取得する*/
	System::GetKeyData(keyin);

	if( Wp_equipment != -1){//武器があれば

			/*変数の初期化*/
			int NowAmmo = WeaponDataWhileGame[Wp_equipment][0]; //現在の弾薬数

			if( ( keyin[9] == 1) && ( WeaponRapidFire == 0)){//左クリックされ、発射可能がオフなら
					if( 0 < WeaponDataWhileGame[Wp_equipment][0] ){//Ammoが残っていれば
							WeaponFireFlag = 1;// 発射状態にする
					}
					else if( NowAmmo == 0){//弾なしで空撃ち状態なら
							WeaponFireFlag = 2;//空撃ち状態する
					}
			}
	}

	return 0;
}