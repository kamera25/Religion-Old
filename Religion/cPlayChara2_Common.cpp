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





/*普通のゲーム内での処理を行う関数、銃器の出し入れ、敵へのあたり、銃を手に置くなど…etc*/
int PlayerChara::NormallyPCSystem( Stage *Stg, Batch_Render *BatPre, Enemy *Ene, Camera *Cam, int ScreenPos[2]){

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

	/* ////////////////////////////////////////////////////// */
	//カメラの位置を設定します、位置は自分の肩の後ろに設置します
	/* ////////////////////////////////////////////////////// */

	//条件を基にカメラをセットします
	Cam->CamShoulderGunBack( Get_BodyModel(), Get_Quaternion(3), Get_Bone_ID(2), Get_PC_Deg_XZ(), Stg);

	//体の向きや、射撃を行う関数を呼び出し
	GunConflictTarget( ScreenPos, Stg, Ene);

	// 武器を変更する際の処理
	ChangeWeapon( BatPre);

	/*姿勢変換「立つ⇔しゃがむ」の処理*/
	if( (keyin[8] == 1) && (Get_AirOnPC() == 0)){//キーが押され、空中でない
				Set_Attitude( Get_Attitude() + 1);//姿勢変数を一つ増やす
				if( Get_Attitude() == 2){//変数が行き過ぎなら
						Set_Attitude( 0 );//「立つ」に固定
				}
	}

	/*格闘攻撃をする処理を行います*/
	if( ( keyin[11] == 1) && ( Get_Attitude() == 0) && ( Get_MyState() == 0)){//キーが押され、しゃがみ状態でなく、他の動作を行ってない
				Set_MyState( 1 );//キックをする
	}

	if( Get_MyState() == 1){//キック中なら
				ech = E3DGetMotionFrameNoML( Get_BodyModel(), Get_Bone_ID(6), &MotionID, &MotionFrameNo);
				_ASSERT( ech != 1 );//エラーダイアログを表示

				if( MotionFrameNo == 19){//モーションが終了したら
							Set_MyState( 0 );//動作状態を通常に戻す
				}
	}

	/*ダッシュ関係の処理を行います*/
	if( ( System::keyinQuick[1] == 1) && ( Get_Attitude() == 0) && ( Get_MyState() == 0) && ( Get_AirOnPC() == 0)){//キーが連続で押され、しゃがみ状態でなく、他の動作を行ってなくて、地上なら
				Set_MyState( 2 );//ダッシュをする
	}

	if(( System::keyinQuick[1] == 1) && (( Get_Attitude() != 0) || (( Get_MyState() != 0) && ( Get_MyState() != 2) ))){//それ以外の条件では、ダッシュキャンセルする
				System::KeyQuickPush[1][2] = 0;//ダッシュキーが押されてない状態にする
				System::keyinQuick[1] = 0;//ゲームダッシュフラグをオフにする
	}


	if( ( Get_MyState() == 2) && ( System::keyinQuick[1] == 0) && ( Get_AirOnPC() == 0) ){//ダッシュ操作中で、キーが解除されたら
				Set_MyState( 0 );//ダッシュを解除する
	}

	if( Get_MyState() == 2){//ダッシュ中なら
				Set_Stamina( Get_Stamina() - 1);//スタミナを減らす
				if( (Get_Stamina() < 1) && (Get_AirOnPC() == 0) ){//体力がなくなった&空中でないなら
						Set_MyState(0);//ダッシュを止める
						System::KeyQuickPush[1][2] = 0;//ダッシュキーが押されてない状態にする
						System::keyinQuick[1] = 0;//ゲームダッシュフラグをオフにする
				}
	}

	/*横っ飛び関係の処理を行います*/
	if( ( ( System::keyinQuick[0] == 1) || ( System::keyinQuick[2] == 1)) && ( Get_Attitude() == 0) //左右キーが連続で押され、しゃがみ状態でなく、
		&& ( Get_MyState() == 0) && ( Get_AirOnPC() == 0) && ( 0 < Get_Stamina())){//他の動作を行ってなくて、地上で、スタミナがなくなってないなら

				if( System::keyinQuick[0] == 1) Set_MyState( 3 );//左横っ飛び状態にする;
				if( System::keyinQuick[2] == 1) Set_MyState( 4 );//右横っ飛び状態にする;
				if(( System::keyinQuick[0] == 1) && ( System::keyinQuick[2] == 1)) Set_MyState( 0 );//通常状態にする
	}

	//横っ飛び状態なら
	if( (Get_MyState() == 3) || ( Get_MyState() == 4)){
				//移動先のモーション状態はどうか確かめる
				ech = E3DGetMotionFrameNoML( Get_BodyModel(), Get_Bone_ID(6), &Garbage, &MotionFrameNo);
				_ASSERT( ech != 1 );//エラーダイアログを表示

				Set_Stamina( Get_Stamina() - 1);//スタミナを減らす

				if( MotionFrameNo == 20){//モーションが終了してたら
							Set_MyState( 0 );//通常状態に戻す
							System::KeyQuickPush[0][2] = 0;//ダッシュキーが押されてない状態にする
							System::KeyQuickPush[2][2] = 0;//ダッシュキーが押されてない状態にする
							System::keyinQuick[0] = 0;//横っ飛びフラグをオフにする
							System::keyinQuick[2] = 0;//横っ飛びフラグをオフにする
				}
	}

	/*スタミナの制御をする*/
	if( Get_Stamina() <= 0){//スタミナがマイナスなら
				Set_Stamina( 0 );//スタミナを固定する
	}

	/*武器をもち手のあるべき場所へ移動させる*/
	if( Get_Wp_equipment() != -1){
				GunPutOnHand();
	}



	return 0;

}
/*武器を変更するさせる際に使用する関数*/
int PlayerChara::ChangeWeapon( Batch_Render *BatPre){

	/* 変数の宣言&初期化 */
	int Eqipment = Get_Wp_equipment();


	/*装備武器変更の処理*/
	if( Eqipment != -1){//現在の状態が武器持ち
			if( Wpn.Get_WeaponPointer( Eqipment)->Get_NowFireFlag() != 0){// 武器攻撃可能でなければ
							return -1;//不可値返し
			}
	}


	

	/* 武器の変更を行う */
	switch(System::MouseWhole){
			case 1:{
					for(int i=0; i<3; i++){//
							Set_Wp_equipment( Get_Wp_equipment() - 1);//装備順を一つ繰り上げる
							if( Get_Wp_equipment() == -1){//装備が「素手」になったら
									break;//ループから抜ける、素手に確定
							}
							if( Get_Wp_equipment() == -2){//装備が行き過ぎたら
									Set_Wp_equipment(1);//装備を「サブウェポン」にする
							}
							if( Wpn.Get_WeaponPointer( Get_Wp_equipment()) != 0){//もし、武器が確認されているなら
									break;//ループを抜ける、装備確定
							}
					}

					break;
			}
			case 2:{//もし、マウスホイールが下へ行ったのなら
					for(int i=0; i<3; i++){//
								Set_Wp_equipment( Get_Wp_equipment() + 1);//装備順を一つ繰り下げる
								if( Get_Wp_equipment() == 2){//装備が行き過ぎたら
										Set_Wp_equipment(-1);//装備を「サブウェポン」にする
										break;//ループから抜ける、素手に確定
								}
								if( Wpn.Get_WeaponPointer( Get_Wp_equipment()) != 0){//もし、武器が確認されているなら
										break;//ループを抜ける、装備確定
								}
					}
							
					break;
			}
	}

	// 描画、視野角内チェックの武器変更
	BatPre->BacthGunTrade( Get_Wp_equipment());




	return 0;
}
/*キャラを動かします、前後左右に動けます*/
int PlayerChara::MoveChara(){

	/*変数の初期化*/
	int ech = 0;//エラー確認変数
	int KeyMov = 0;//キーを押してどの方向に動くかの変数
	int MovOn = 0;//動いていいかのフラグ
	int keyin[20];//キー情報配列を作成 
	float WantDeg = 0;//向きたい方向の変数
	float FixedMoveSpeed = 0.0f;//それぞれの状態の固定速度
	D3DXVECTOR3 SubPos( 0.0, 0.0, 0.0);//キャラクターを置く場所の座標
	D3DXVECTOR3 PCPos( 0.0, 0.0, 0.0);//プレイヤーキャラクターの位置の座標

	/*ダッシュ操作がオンになっていないかチェック*/


	/*キーによる分岐*/

	System::GetKeyData(keyin);//キー情報を格納

	if( keyin[0] == 1){//左
				KeyMov = KeyMov +1;
	}
	if( keyin[1] == 1){//上
				KeyMov = KeyMov +2;
	}
	if( keyin[2] == 1){//右
				KeyMov = KeyMov +4;
	}
	if( keyin[3] == 1){//下
				KeyMov = KeyMov +8;
	}

	/*キーから取得した情報を変換*/
	if(KeyMov == 1){//左
				WantDeg = -90.0f + Get_PC_Deg_XZ();
				MovOn = 1;

				/*モーションを「左歩き」にする*/
				Set_UnderMotion(3);
	}
	if(KeyMov == 3){//左上
				WantDeg = -45.0f + Get_PC_Deg_XZ(); 
				MovOn = 1;

				/*モーションを「左前進」にする*/
				Set_UnderMotion(4);
	}
	if(KeyMov == 2){//上
				WantDeg = Get_PC_Deg_XZ(); 
				MovOn = 1;

				/*モーションを「歩行」にする*/
				Set_UnderMotion(1);//通常

	}
	if(KeyMov == 6){//右上
				WantDeg = 45.0f + Get_PC_Deg_XZ(); 
				MovOn = 1;

				/*モーションを「左前進」にする*/
				Set_UnderMotion(5);
	}
	if(KeyMov == 4){//右
				WantDeg = 90.0f + Get_PC_Deg_XZ(); 
				MovOn = 1;

				/*モーションを「右歩き」にする*/
				Set_UnderMotion(2);
	}
	if(KeyMov == 12){//右下
				WantDeg = 135.0f + Get_PC_Deg_XZ(); 
				MovOn = 1;

				/*モーションを「右後進」にする*/
				Set_UnderMotion(7);
	}
	if(KeyMov == 8){//下
				WantDeg = 180.0f + Get_PC_Deg_XZ(); 
				MovOn = 1;

				/*モーションを「後進」にする*/
				Set_UnderMotion(8);
	}
	if(KeyMov == 9){//左下
				WantDeg = -135.0f + Get_PC_Deg_XZ(); 
				MovOn = 1;

				/*モーションを「左後進」にする*/
				Set_UnderMotion(6);

	}

	//キーが入力されていても、キック中なら
	if( Get_MyState() == 1) {
				MovOn = 0;//絶対動かない
	}

	//空中で、ダッシュ状態なら
	if( ( Get_AirOnPC() == 1) && ( Get_MyState() == 2)){
				WantDeg = Get_PC_Deg_XZ();//まっすぐ進む
				MovOn = 1;//絶対動く
	}

	//左飛び状態なら
	if( Get_MyState() == 3) {
				WantDeg = -90.0f + Get_PC_Deg_XZ();
				MovOn = 1;//絶対動く
	}

	//右飛び状態なら
	if( Get_MyState() == 4) {
				WantDeg = 90.0f + Get_PC_Deg_XZ(); 
				MovOn = 1;//絶対動く
	}


	/*動く方向を決めるよ*/
	if(MovOn == 1){

					if( Get_MyState() == 0){//通常状態なら
							if( Get_AirOnPC() == 0){//空中でなければ
									if(Get_Attitude() == 0){//姿勢が「立っている状態」なら
											/*スピードを増加させる*/
											Set_MoveSpeed( Get_MoveSpeed() + 0.8f);

											//スピードに制限をかける
											if( 25.0f <= Get_MoveSpeed() ){
														Set_MoveSpeed( 25.0f);
											}

											//固定スピードの設定（立ち）
											FixedMoveSpeed = 50.0f;
									}

									if(Get_Attitude() == 1){//姿勢が「しゃがみ状態」なら
											/*スピードを増加させる*/
											Set_MoveSpeed( Get_MoveSpeed() + 0.4f);

											//スピードに制限をかける
											if( 20.0f <= Get_MoveSpeed() ){
														Set_MoveSpeed( 20.0f);
											}

											//固定スピードの設定（しゃがみ）
											FixedMoveSpeed = 30.0f;
									}
							}
							if( Get_AirOnPC() == 1){//空中にいるなら
									
									/*スピードを増加させる*/
									Set_MoveSpeed(Get_MoveSpeed() + 0.3f);

									//スピードに制限をかける
									if( 10.0f <= Get_MoveSpeed() ){
												Set_MoveSpeed( 10.0f);
									}

									//固定スピードの設定（しゃがみ）
									FixedMoveSpeed = 20.0f;
							}

					}
					if( Get_MyState() == 2){//ダッシュ状態なら

							if( Get_AirOnPC() == 0){//地上にいるなら
									/*スピードを増加させる*/
									Set_MoveSpeed( Get_MoveSpeed() + 2.0f);

									//スピードに制限をかける
									if( 40.0f <= Get_MoveSpeed() ){
												Set_MoveSpeed(40.0f);
									}

									//固定スピードの設定（しゃがみ）
									FixedMoveSpeed = 70.0f;
							}
							if( Get_AirOnPC() == 1){//空中にいるなら
									/*スピードを増加させる*/
									Set_MoveSpeed( Get_MoveSpeed() + 2.0f);

									//スピードに制限をかける
									if( 40.0f <= Get_MoveSpeed() ){
												Set_MoveSpeed(40.0f);
									}

									//固定スピードの設定（しゃがみ）
									FixedMoveSpeed = 70.0f;
							}
					}
					if( ( Get_MyState() == 3) || ( Get_MyState() == 4)){//左飛び状態なら
									/*スピードを固定*/
									Set_MoveSpeed(0.0f);

									//固定スピードの設定（しゃがみ）
									FixedMoveSpeed = 90.0f;
					}



					/*ダミーモデルの座標に設定*/
					ech = E3DRotateInit ( Get_DummyModel());
					_ASSERT( ech != 1 );//エラーチェック

					ech = E3DGetPos( Get_BodyModel(), &PCPos);
					_ASSERT( ech != 1 );//エラーチェック

					ech = E3DSetPos( Get_DummyModel(), PCPos);
					_ASSERT( ech != 1 );//エラーチェック

					ech = E3DRotateY( Get_DummyModel(), WantDeg);
					_ASSERT( ech != 1 );//エラーチェック

					ech = E3DPosForward( Get_DummyModel(), (float)Get_MoveSpeed() + FixedMoveSpeed);
					_ASSERT( ech != 1 );//エラーチェック

					ech = E3DGetPos( Get_DummyModel(), &SubPos);
					_ASSERT( ech != 1 );//エラーチェック

					ech = E3DSetPos( Get_BodyModel(), SubPos);
					_ASSERT( ech != 1 );//エラーチェック
	}
	else{//減速をさせなければならないなら
					if( Get_AirOnPC() == 0){//空中にいるなら
								if( Get_Attitude() == 0) Set_MoveSpeed( Get_MoveSpeed() - 0.8f);//姿勢が「通常状態」なら
								if( Get_Attitude() == 1) Set_MoveSpeed( Get_MoveSpeed() - 1.0f);//姿勢が「しゃがみ状態」なら
					}
					if( Get_AirOnPC() == 1) Set_MoveSpeed( Get_MoveSpeed() - 0.6f);//姿勢が「しゃがみ状態」なら


					//スピードに制限をかける
					if( Get_MoveSpeed() <= 0.0 ){
								Set_MoveSpeed( 0.0f);
					}


					Set_UnderMotion(0);
	}




	return 0;
}
