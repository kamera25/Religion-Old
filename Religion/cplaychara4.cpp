/*ここでは、生物クラスのキャラの関数を定義するクラスコードファイルです。
//通常動作に関係する時に必要な関数が多く書かれています。
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "clive.h"//敵やキャラの宣言ヘッダファイル
#include "cenemy.h"//敵クラスの宣言ヘッダファイル
#include "cweapon.h"//武器クラスの宣言ヘッダファイル
#include "cstage.h"//ステージ関係のクラスヘッダファイル
#include "c_batch_preparat.h"//描画に必要なクラスの宣言ヘッダファイル
#include "ccamera.h"//カメラ関係のクラスヘッダファイル




/*自分の向くべき方向を調節したり、射撃したりする関数*/
int PlayerChara::GunConflictTarget( int ScreenPosArray[2], Stage *Stg, Enemy *Ene, Weapon *Wep){
    /*キャラクターモデルを壁があれば壁に向ける
	なければ銃の攻撃が届く範囲までの距離を取得し、そこに向ける*/

	/*変数の初期化*/


	int NowWpKind = 0;//今の武器の種類を取得します
	int ech = 0;//エラー確認変数
	int MotionID = 0;//MLから取得した現在の「首付け根」モーションID
	int FrameNo = 0;//MLから取得した現在の「首付け根」モーションが現在再生している番号
	int NearEnemyID = 0;//一番近い敵キャラの識別番号
	int EnemyConflict = 0;//敵に当たった数の合計
	int Wall_HitResult = 0;//当たり判定モデルが壁に当たっているかどうか調べます
	int EneHitResult = 0;//敵が照準に入っているかの結果を入れます
	int HitResult = 0;//銃を向ける方向があるか入れますかの結果を入れます
	float NowWpRange = 0.0f;//今の武器の射程を代入します
	float Wall_HitDistance = 0.0f;//当たった面のところからの距離が代入されます
	float EneDistance = 0.0f;//当たった敵のところからの距離が代入されます
	float EneNearDistance = 0.0f;//当たっている一番近い敵の距離が代入されます
	D3DXVECTOR3 Wall_ReflectVec( 0.0, 0.0, 0.0);//地面の反射ベクトルの構造体
	D3DXVECTOR3 Wall_GunTargetPos( 0.0, 0.0, 0.0);//銃が向くべき座標
	D3DXVECTOR3 ReflectVec( 0.0, 0.0, 0.0);//反射ベクトルの構造体
	D3DXVECTOR3 GunTargetPos( 0.0, 0.0, 0.0);//銃が向くべき座標
	D3DXVECTOR3 WantVec( 0.0, 0.0, 0.0);//「首つけ根」の向きたい方向へのベクトル
	D3DXVECTOR3 BaseVec( 0.0, 0.0, -1.0);//向きの初期方向ベクトル
	D3DXVECTOR3 StomachPos( 0.0, 0.0, 0.0);//「首つけ根」の座標
	D3DXVECTOR3 MyPos1( 0.0, 0.0, 0.0);//最初自分の座標
	D3DXVECTOR3 OriginPos( 0.0, 0.0, 0.0);//キャラクターをおくべき原点座標
	D3DXVECTOR3 GarbageD3DVec( 0.0, 0.0, 0.0);//要らないXYZのデータの一次入れ
	POINT ScreenPos = { ScreenPosArray[0], ScreenPosArray[1]};//2Dスクリーン座標構造体

	/*装備をきちんとつけていれば*/
	if( Wp_equipment != -1){

			NowWpKind = Wep->GetWeaponData( Wp_equipment, 0);
			NowWpRange = float( Wep->GetWeaponData( Wp_equipment, 4) * 500);
			EneNearDistance = float(NowWpRange);
	}

	/**/
	//壁の銃取得をどのようにするか指定します*/
	/**/

	/*通常モード( モデル[0]から取得する )*/
	if( Stg->Stage_GunTarget == 0){
			ech = E3DPickFace( System::scid1, Stg->Stage_hsid[0], ScreenPos, NowWpRange, &Wall_HitResult, &HitResult, &Wall_GunTargetPos, &Wall_ReflectVec, &Wall_HitDistance);
			if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
			};
	}


	if(Wp_equipment != -1){//装備をきちんとつけていれば
		/*武器の種類が、ハンドガンであれば*/
		if((NowWpKind == 1) || (NowWpKind == 4)){
			
				/*敵にあたっていないかチェックします*/
				for( int i = 0; i < 15; i++){//エネミーの数だけ
						if( Ene->Enemy_hsid[i] != 0){
									ech = E3DPickFace( System::scid1, Ene->Enemy_hsid[i], ScreenPos, NowWpRange, &EneHitResult, &EneHitResult, &GarbageD3DVec, &GarbageD3DVec, &EneDistance);
									if(ech != 0 ){//エラーチェック
												_ASSERT( 0 );//エラーダイアログ
									};
									if( (EneHitResult != 0) && ( EneDistance < EneNearDistance) ){
												EneNearDistance = EneDistance;//一番近い敵の距離に更新します
												NearEnemyID = i;//一番近いモデル番号を入れます
												EnemyConflict = 1;//近い敵がいることを代入します
												HitResult = 1;//ヒットフラグを1にする
									}
						}
				}

				if( (EnemyConflict == 1) && ( Wall_HitDistance > EneNearDistance) ){//敵に銃先を向ける
						ech = E3DPickFace( System::scid1, Ene->Enemy_hsid[NearEnemyID], ScreenPos, NowWpRange, &EneHitResult, &EneHitResult, &GunTargetPos, &ReflectVec, &EneDistance);
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
						};
				}
				else{//壁に銃先を向ける
						GunTargetPos = Wall_GunTargetPos;
						ReflectVec = Wall_ReflectVec;
				}
			

				/*壁に当たっていれば*/
				if( HitResult != -1){

						/*「首付け根」部分の座標を取得します*/
						ech = E3DGetCurrentBonePos( cha_hsid[0], bone[2], 1, &StomachPos);
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
						};

						WantVec.x =  GunTargetPos.x - StomachPos.x;
						WantVec.y =  GunTargetPos.y - StomachPos.y;
						WantVec.z =  GunTargetPos.z - StomachPos.z;

						/*キャラクターの向きを初期化します*/
						ech = E3DRotateInit( cha_hsid[0]);
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
						};


						/*「首付け根」部分のクォータニオンを調べます*/
						ech = E3DGetCurrentBoneQ( cha_hsid[0], bone[2], 2, Qid[5]);
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
						};

						/*「首付け根」部分のモーションはどうか調べます*/
						ech = E3DGetMotionFrameNoML( cha_hsid[0], bone[2], &MotionID, &FrameNo);
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
						};

						/*向きたい方向への計算を行います*/
						ech = E3DLookAtQ( Qid[5], WantVec, BaseVec, 0, 0);
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
						};



						/*向きたい方向の修正を加えます*/
						ech = E3DRotateQY( Qid[5], -(PC_Deg_XZ));
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
						};

						/*計算したクォーターニオンを代入します*/
						ech = E3DSetBoneQ( cha_hsid[0], bone[2], MotionID, FrameNo, Qid[5]);
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
						};

						/*マルチレイヤーモーションの計算を行います*/
						ech = E3DCalcMLMotion( cha_hsid[0]);
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
						};

						/*キャラクターを回転させます*/
						ech = E3DRotateY( cha_hsid[0], PC_Deg_XZ);
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
						};
			}
		}
		else{



		}
	}




	return 0;
}
/*普通のゲーム内での処理を行う関数、銃器の出し入れ、敵へのあたり、銃を手に置くなど…etc*/
int PlayerChara::NormallyPCSystem( Stage *Stg, Batch_Preparat *BatPre, Enemy *Ene, Camera *Cam, Weapon *Wep, int ScreenPos[2]){

	/*変数の初期化*/
	int ech = 0;
	int MotionID = 0;//モーションIDを入れます
	int Garbage = 0;//ゴミデータを入れます
	int MotionFrameNo = 0;//モーションのフレーム番号を入れます
	int keyin[20];//キー情報配列を作成 

	/*キーを取得する*/
	System::GetKeyData(keyin);

	/*キャラクターを動かす*/
	MoveChara();

	/*キャラクターを地面に置く*/
	MovePosOnGround( Stg);

	/*視点関連の処理、切り替えや関数呼び出し等*/
	ShoulderGunSys( BatPre, ScreenPos);//肩撃ち視点
	/**/
	//カメラの位置を設定します、位置は自分の肩の後ろに設置します
	/**/

	//条件を基にカメラをセットします
	Cam->CamShoulderGunBack( cha_hsid[0], Qid[3], bone[2], PC_Deg_XZ, Stg);



	//体の向きや、射撃を行う関数を呼び出し
	GunConflictTarget( ScreenPos, Stg, Ene, Wep);

	/*敵への当たり判定の処理*/


	/*装備武器変更の処理*/
	if( Wep->GetWeaponRapidFire() == 0){// 武器攻撃可能なら
		if( System::MouseWhole == 1){//もし、マウスホイールが上へ行ったのなら
			for(int i=0; i<3; i++){//
					Wp_equipment = Wp_equipment - 1;//装備順を一つ繰り上げる
					if( Wp_equipment == -1){//装備が「素手」になったら
							break;//ループから抜ける、素手に確定
					}
					if( Wp_equipment == -2){//装備が行き過ぎたら
							Wp_equipment = 1;//装備を「サブウェポン」にする
					}
					if( Wep->GetWeaponModelID( Wp_equipment, 0) != 0){//もし、武器が確認されているなら
							break;//ループを抜ける、装備確定
					}
			}
			BatPre->BacthGunTrade( Wp_equipment);//描画、視野角内チェックの武器変更
		}

		if( System::MouseWhole == 2){//もし、マウスホイールが下へ行ったのなら
			for(int i=0; i<3; i++){//
					Wp_equipment = Wp_equipment + 1;//装備順を一つ繰り下げる
					if( Wp_equipment == 2){//装備が行き過ぎたら
							Wp_equipment = -1;//装備を「サブウェポン」にする
							break;//ループから抜ける、素手に確定
					}
					if( Wep->GetWeaponModelID( Wp_equipment, 0) != 0){//もし、武器が確認されているなら
							break;//ループを抜ける、装備確定
					}
			}
			BatPre->BacthGunTrade( Wp_equipment);//描画、視野角内チェックの武器変更
		}
	}


	/*姿勢変換「立つ⇔しゃがむ」の処理*/
	if( (keyin[8] == 1) && (AirOnPC == 0)){//キーが押され、空中でない
				Attitude = Attitude + 1;//姿勢変数を一つ増やす
				if( Attitude == 2){//変数が行き過ぎなら
						Attitude = 0;//「立つ」に固定
				}
	}

	/*格闘攻撃をする処理を行います*/
	if( ( keyin[11] == 1) && ( Attitude == 0) && ( MyState == 0)){//キーが押され、しゃがみ状態でなく、他の動作を行ってない
				MyState = 1;//キックをする
	}

	if( MyState == 1){//キック中なら
				ech = E3DGetMotionFrameNoML( cha_hsid[0], bone[6], &MotionID, &MotionFrameNo);
				if(ech != 0 ){//エラーチェック
							_ASSERT(0);//エラーダイアログ
				}

				if( MotionFrameNo == 19){//モーションが終了したら
							MyState = 0;//動作状態を通常に戻す
				}
	}

	/*ダッシュ関係の処理を行います*/
	if( ( System::keyinQuick[1] == 1) && ( Attitude == 0) && ( MyState == 0) && ( AirOnPC == 0)){//キーが連続で押され、しゃがみ状態でなく、他の動作を行ってなくて、地上なら
				MyState = 2;//ダッシュをする
	}

	if(( System::keyinQuick[1] == 1) && (( Attitude != 0) || (( MyState != 0) && ( MyState != 2) ))){//それ以外の条件では、ダッシュキャンセルする
				System::KeyQuickPush[1][2] = 0;//ダッシュキーが押されてない状態にする
				System::keyinQuick[1] = 0;//ゲームダッシュフラグをオフにする
	}


	if( ( MyState == 2) && ( System::keyinQuick[1] == 0) && ( AirOnPC == 0) ){//ダッシュ操作中で、キーが解除されたら
				MyState = 0;//ダッシュを解除する
	}

	if( MyState == 2){//ダッシュ中なら
				Stamina = Stamina - 1;//スタミナを減らす
				if( (Stamina < 1) && (AirOnPC == 0) ){//体力がなくなった&空中でないなら
						MyState = 0;//ダッシュを止める
						System::KeyQuickPush[1][2] = 0;//ダッシュキーが押されてない状態にする
						System::keyinQuick[1] = 0;//ゲームダッシュフラグをオフにする
				}
	}

	/*横っ飛び関係の処理を行います*/
	if( ( ( System::keyinQuick[0] == 1) || ( System::keyinQuick[2] == 1)) && ( Attitude == 0) //左右キーが連続で押され、しゃがみ状態でなく、
		&& ( MyState == 0) && ( AirOnPC == 0) && ( 0 < Stamina)){//他の動作を行ってなくて、地上で、スタミナがなくなってないなら

				if( System::keyinQuick[0] == 1) MyState = 3;//左横っ飛び状態にする;
				if( System::keyinQuick[2] == 1) MyState = 4;//右横っ飛び状態にする;
				if(( System::keyinQuick[0] == 1) && ( System::keyinQuick[2] == 1)) MyState = 0;//通常状態にする
	}

	//横っ飛び状態なら
	if( (MyState == 3) || ( MyState == 4)){
				//移動先のモーション状態はどうか確かめる
				ech = E3DGetMotionFrameNoML( cha_hsid[0], bone[6], &Garbage, &MotionFrameNo);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};

				Stamina = Stamina - 1;//スタミナを減らす

				if( MotionFrameNo == 20){//モーションが終了してたら
							MyState = 0;//通常状態に戻す
							System::KeyQuickPush[0][2] = 0;//ダッシュキーが押されてない状態にする
							System::KeyQuickPush[2][2] = 0;//ダッシュキーが押されてない状態にする
							System::keyinQuick[0] = 0;//横っ飛びフラグをオフにする
							System::keyinQuick[2] = 0;//横っ飛びフラグをオフにする
				}
	}

	/*スタミナの制御をする*/
	if( Stamina <= 0){//スタミナがマイナスなら
				Stamina = 0;//スタミナを固定する
	}

	/*武器をもち手のあるべき場所へ移動させる*/
	if( Wp_equipment != -1){
				GunPutOnHand( Wep);
	}



	return 0;

}