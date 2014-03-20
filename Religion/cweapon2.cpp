/*ここでは、武器に関することを記述するクラスコードファイルです
//
*/
#include "cweapon.h"//武器に関することのクラスヘッダファイル
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include "cstage.h"//ステージ関係のクラスヘッダファイル
#include "clive.h"//敵やキャラの宣言ヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ
#include <stdlib.h>//乱数を作るのに使用します

//ここにグローバル変数を宣言
extern System *sys;//システムクラスを指す、クラスのポインタ

// ゲーム中の銃の操作に関することをします
int Weapon::TreatmentWhileGame( int Wp_equipment){

	/*変数の初期化*/
	int ech = 0;
	int keyin[20] = {0};
	float LightDistance = 0.0f;//光が届く距離
	float MuzzleFlashAlpha = 0.0f;//マズルフラッシュの透明度
	static int MuzzleFlashConter = 0;//マズルフラッシュカウンター
	D3DXVECTOR3 MuzzlePos( 0.0, 0.0, 0.0);//銃口位置
	D3DXVECTOR3 MuzzleFlashSound( 340.0, 340.0, 340.0);//マズルフラッシュサウンドの速度XYZ
	E3DCOLOR4UC MuzzleFlashColor = { 0, 0, 0, 0};//マズルフラッシュの色を指定

	/*キーを取得する*/
	sys->GetKeyData(keyin);



	if( Wp_equipment != -1){//武器があれば

		/*武器に新しいモーションを当てる*/
		ech = E3DSetNewPoseML( WeaponModel[Wp_equipment]);
		if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
		};

		if( WeaponBone[Wp_equipment][0] != 0){
			/*銃の置くボーンの座標を求めます*/
			ech = E3DGetCurrentBonePos( WeaponModel[Wp_equipment], WeaponBone[Wp_equipment][0], 1, &MuzzlePos);
			if(ech != 0 ){//エラーチェック
						_ASSERT( 0 );//エラーダイアログ
			};
		}

		/*重厚の位置に爆発エフェクトを置きます*/
		ech = E3DSetBillboardPos( WeaponEffect[Wp_equipment][0], MuzzlePos); 
		if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
		};

		if( keyin[9] == 1){
			if( 0 < WeaponDataWhileGame[Wp_equipment][0] ){
					MuzzleFlashConter = 4;

					/*ビルボードを回転させます*/
					ech = E3DRotateBillboard( WeaponEffect[Wp_equipment][0], float( rand() % 360), 1);
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
					};

					/*音の位置と速さを指定します*/
					ech = E3DSet3DSoundMovement( WeaponSoundEfeect[Wp_equipment][0], MuzzlePos, MuzzleFlashSound);
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
					};

					/*発射音を鳴らします*/
					ech = E3DPlaySound( WeaponSoundEfeect[Wp_equipment][0], 0, 0, 0);
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
					};

					/*変数操作*/

					//弾薬をひとつ減らします
					WeaponDataWhileGame[Wp_equipment][0] = WeaponDataWhileGame[Wp_equipment][0] - 1;
			}
			else{//空撃ち状態なら
					/*音の位置と速さを指定します*/
					ech = E3DSet3DSoundMovement( WeaponSoundEfeect[Wp_equipment][1], MuzzlePos, MuzzleFlashSound);
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
					};

					/*発射音を鳴らします*/
					ech = E3DPlaySound( WeaponSoundEfeect[Wp_equipment][1], 0, 0, 0);
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
					};
			}
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
			if(ech != 0 ){//エラーチェック
						_ASSERT( 0 );//エラーダイアログ
			};
			/*ライトを付ける*/
			if( MuzzleFlashConter != 1){
						ech = E3DSetPointLight( WeaponMuzzleLight[Wp_equipment], MuzzlePos, 700.0f, MuzzleFlashColor);
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
						};
			}
			else{//ライト消灯のお時間です
						ech = E3DSetPointLight( WeaponMuzzleLight[Wp_equipment], MuzzlePos, 0.0f, MuzzleFlashColor);
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
						};			
			}


			/*爆発のエフェクトを(すべてのビルボード)の描画*/
			ech = E3DRenderBillboard( sys->scid1, 0);
			if(ech != 0 ){//エラーチェック
						_ASSERT( 0 );//エラーダイアログ
			};

			/*フラッシュカウントをひとつ下げる*/
			MuzzleFlashConter = MuzzleFlashConter -1;

			/*透明度を変更する*/
			if( MuzzleFlashConter == 0){//カウントが0になったら
						ech = E3DSetBillboardAlpha( WeaponEffect[Wp_equipment][0], 0.0f);
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
						};	
			}



		}
	}

	return 0;
}