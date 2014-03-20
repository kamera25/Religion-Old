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



int PlayerChara::ThreePersonGunSys( Batch_Render *BatPre, int ScreenPos[2]){

	/*全体で使う変数の初期化*/
	int ech = 0;//エラー確認変数
	const D3DXVECTOR3 BaseVec( 0.0, 0.0, -1.0);//向きの初期方向ベクトル
	const D3DXVECTOR3 CameraUpVec( 0.0, 1.0, 0.0);//カメラの上部のベクトル

	/*キャラクターの位置を設定します*/
	int MotionID = 0;//MLから取得した現在の「首付け根」モーションID
	int FrameNo = 0;//MLから取得した現在の「首付け根」モーションが現在再生している番号
	static double Tm_DegQ_Y = 0.50;//ブレがある前の角度変数Y
	double Sin_Y = 0.0;//Y座標サイン変数
	const  double Sin_XZ = sin(4.8);//XZ座標サイン変数
	double Cos_Y = 0.0;//Y座標コサイン変数
	const double Cos_XZ = cos(4.8);//XZ座標コサイン変数
	D3DXVECTOR3 TurnPos( 0.0, 0.0, 0.0);//向くべきYベクトル
	D3DXVECTOR3 StomachPos( 0.0, 0.0, 0.0);//「首つけ根」の座標
	D3DXVECTOR3 WantDeg( 0.0, 0.0, 0.0);//向きたい方向へのベクトル
	D3DXVECTOR3 OriginPos( 0.0, 0.0, 0.0);//キャラクターをおくべき原点座標
	D3DXVECTOR3 MyPos1( 0.0, 0.0, 0.0);//最初自分の座標
	D3DXVECTOR3 MyPos2( 0.0, 0.0, 0.0);//次の自分の座標


	/**/
	//自分の向きを回転させます。
	/**/

	//最初に回転の計算します
	if(( Get_MyState() == 0) || ( (Get_MyState() == 2) && ( Get_AirOnPC() == 0))){//通常・空中ダッシュモードでなければ、以下取得せず

				if( ( System::MousePos.x < 100) || (  580< System::MousePos.x)){

						Set_PC_Deg_XZ( Get_PC_Deg_XZ() + float(0.30*(System::MousePos.x - System::BeforeMousePos.x) ));
						System::SetMouseCursol( System::BeforeMousePos.x, System::BeforeMousePos.y);// マウス座標を真ん中へ

				}
				Tm_DegQ_Y = Tm_DegQ_Y - 0.0020* float( System::MousePos.y - System::BeforeMousePos.y);
	}

	if( ( Get_MyState() == 3) || ( Get_MyState() == 4)){//よっこ飛びの時は
				Tm_DegQ_Y = Tm_DegQ_Y - 0.0020* float( System::MousePos.y - System::BeforeMousePos.y);
	}

	if( Get_PC_Deg_XZ() < 0){
				Set_PC_Deg_XZ( Get_PC_Deg_XZ() + 360);
	}
	if( 360 < Get_PC_Deg_XZ()){
				Set_PC_Deg_XZ( Get_PC_Deg_XZ() - 360);
	}
	if(Tm_DegQ_Y> 0.9){
				Tm_DegQ_Y = 0.9;
	}
	if(Tm_DegQ_Y< -0.6){
				Tm_DegQ_Y = -0.6;
	}



	Sin_Y = sin(Tm_DegQ_Y);//Y座標サインの取得
	Cos_Y = cos(Tm_DegQ_Y);//Y座標のコサインの取得
	TurnPos.x = float(Cos_XZ * Cos_Y * 2000);//向くべき方向のX座標
	TurnPos.y = float(Sin_Y * 2000);//向くべき方向のY座標を取得
	TurnPos.z = float(Sin_XZ * Cos_Y * 2000);//向くべき方向のZ座標を取得

	/**/
	//次に座標を取得したりしてモデルのボーンを操作します
	/**/
	System::SetMouseBeforePos();// マウス座標を格納します


	/*キャラクターモデルの方向を初期化します*/
	ech = E3DRotateInit( Get_BodyModel());
	_ASSERT( ech != 1 );//エラーチェック

	/*座標を取得する*/
	ech = E3DGetPos( Get_BodyModel(), &MyPos1);
	_ASSERT( ech != 1 );//エラーチェック

	/*キャラクターモデルの「首つけ根」の座標を取得します*/
	ech = E3DGetCurrentBonePos( Get_BodyModel(), Get_Bone_ID(2), 1, &StomachPos);
	_ASSERT( ech != 1 );//エラーチェック

	MyPos2.x = StomachPos.x * -1;
	MyPos2.y = StomachPos.y * -1;
	MyPos2.z = StomachPos.z * -1;

	/*座標を原点にする*/
	ech = E3DSetPos( Get_BodyModel(), MyPos2);
	_ASSERT( ech != 1 );//エラーチェック

	/*キャラクターモデルの「首つけ根」の座標を取得します*/
	ech = E3DGetCurrentBonePos( Get_BodyModel(), Get_Bone_ID(2), 1, &StomachPos);
	_ASSERT( ech != 1 );//エラーチェック

	WantDeg.x = float( TurnPos.x - 0);//X座標の向く方向のベクトルを取得
	WantDeg.y = float( TurnPos.y - 0);//Y座標の向く方向のベクトルを取得
	WantDeg.z = float( TurnPos.z - 0);//Z座標の向く方向のベクトルを取得

	/*「首付け根」部分のモーションはどうか調べます*/
	ech = E3DGetMotionFrameNoML( Get_BodyModel(), Get_Bone_ID(2), &MotionID, &FrameNo);
	_ASSERT( ech != 1 );//エラーチェック

	/*「首付け根」部分のクォータニオンを調べます*/
	ech = E3DGetCurrentBoneQ( Get_BodyModel(), Get_Bone_ID(2), 2, Get_Quaternion(3));
	_ASSERT( ech != 1 );//エラーチェック

	/*向きたい方向への計算を行います*/
	ech = E3DLookAtQ( Get_Quaternion(3), WantDeg, BaseVec, 0, 2);
	_ASSERT( ech != 1 );//エラーチェック

	/*計算したクォーターニオンを代入します*/
	ech = E3DSetBoneQ( Get_BodyModel(), Get_Bone_ID(2), MotionID, FrameNo, Get_Quaternion(3));
	_ASSERT( ech != 1 );//エラーチェック

	/*マルチレイヤーモーションの計算を行います*/
	ech = E3DCalcMLMotion( Get_BodyModel());
	_ASSERT( ech != 1 );//エラーチェック

	/*本来の自分の座標に戻す*/
	ech = E3DSetPos( Get_BodyModel(), MyPos1);
	_ASSERT( ech != 1 );//エラーチェック

	/*キャラクターを回転させます*/
	ech = E3DRotateY( Get_BodyModel(), Get_PC_Deg_XZ());
	_ASSERT( ech != 1 );//エラーチェック




	BatPre->Set_SpriteX( "Cursol1", System::MousePos.x - 25.0f);//カーソルのX座標
	BatPre->Set_SpriteY( "Cursol1", System::MousePos.y - 48.0f);//カーソルのY座標
	ScreenPos[0] = System::MousePos.x;/**/ScreenPos[1] = System::MousePos.y;


	return 0;
}




/*普通のゲーム内での処理を行う関数、銃器の出し入れ、敵へのあたり、銃を手に置くなど…etc*/
int PlayerChara::NormallyPCSystem( Stage *Stg, Batch_Render *BatPre, NPC_Head *NPC_H, Camera *Cam, int ScreenPos[2]){

	/*変数の初期化*/
	int ech = 0;
	int MotionID = 0;//モーションIDを入れます
	int Garbage = 0;//ゴミデータを入れます
	int MotionFrameNo = 0;//モーションのフレーム番号を入れます


	/*キャラクターを動かす*/
	MoveChara();

	/*キャラクターを地面に置く*/
	MovePosOnGround( Stg);


	switch(ChangePerspectiveMode){
			case 0:{
					/*視点関連の処理、切り替えや関数呼び出し等*/
					ThreePersonGunSys( BatPre, ScreenPos);//肩撃ち視点


					break;		
			}
			case 1:{// 肩撃ちモード

					/*視点関連の処理、切り替えや関数呼び出し等*/
					ShoulderGunSys( BatPre, ScreenPos);//肩撃ち視点

					//条件を基にカメラをセットします
					Cam->CamShoulderGunBack( Get_BodyModel(), Get_Quaternion(3), Get_Bone_ID(2), Get_PC_Deg_XZ(), Stg);

					break;
			}
	}


	//体の向きや、射撃を行う関数を呼び出し
	GunConflictTarget( ScreenPos, Stg, NPC_H);

	// 武器を変更する際の処理
	ChangeWeapon( BatPre);

	/*姿勢変換「立つ⇔しゃがむ」の処理*/
	if( ( System::GetKeyData( System::KEY_SHIFT) == 1) && (Get_AirOnPC() == 0)){//キーが押され、空中でない
				Set_Attitude( Get_Attitude() + 1);//姿勢変数を一つ増やす
				if( Get_Attitude() == 2){//変数が行き過ぎなら
						Set_Attitude( 0 );//「立つ」に固定
				}
	}

	/*格闘攻撃をする処理を行います*/
	if( ( System::GetKeyData( System::KEY_SPACE) == 1) && ( Get_Attitude() == 0) && ( Get_MyState() == 0)){//キーが押され、しゃがみ状態でなく、他の動作を行ってない
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

	/* 視点変えの切り替え制御を行う */
	if( System::GetKeyData( System::KEY_WHILEMOUSE) == 1){// ホイールクリックが押されたら
				ChangePerspectiveMode++;// 視点モードを進める
				if( ChangePerspectiveMode == 2){// 視点が行き過ぎたら
						ChangePerspectiveMode = 0;
				}
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


	/* //////////////// */
	// 武器の変更を行う
	/* //////////////// */
	switch(System::MouseWhole){
			case 1:{
					if( Get_Wp_equipment() == 3){
							Set_Wp_equipment(-1);//装備を「素手」にする
							break;
					}

					for(int i=0; i<3; i++){//
							Set_Wp_equipment( Get_Wp_equipment() - 1);//装備順を一つ繰り上げる
							if( Get_Wp_equipment() == -1){//装備が「素手」になったら
									break;//ループから抜ける、素手に確定
							}
							if( Get_Wp_equipment() == -2){//装備が行き過ぎたら
									Set_Wp_equipment(2);//装備を「グレネード」にする
							}
							if( Wpn.Get_WeaponPointer( Get_Wp_equipment()) != 0){//もし、武器が確認されているなら
									break;//ループを抜ける、装備確定
							}
					}

					break;
			}
			case 2:{//もし、マウスホイールが下へ行ったのなら
					if( Get_Wp_equipment() == 3){
							Set_Wp_equipment(-1);//装備を「素手」にする
							break;
					}

					for(int i=0; i<3; i++){//
								Set_Wp_equipment( Get_Wp_equipment() + 1);//装備順を一つ繰り下げる
								if( Get_Wp_equipment() == 3){//装備が行き過ぎたら
										Set_Wp_equipment(-1);//装備を「素手」にする
										break;//ループから抜ける、素手に確定
								}
								if( Wpn.Get_WeaponPointer( Get_Wp_equipment()) != 0){//もし、武器が確認されているなら
										break;//ループを抜ける、装備確定
								}
					}
							
					break;
			}
	}

	/* ///////////////////////// */
	// サポート武器の変更を行います
	/* ///////////////////////// */

	/* サポート武器への変更確認と変更を行う */
	//if( ( keyin[10] == 1) && ( Wpn.Get_WeaponPointer(2) != NULL)){//右クリックとサポート武器を所持していれば
	//		Set_Wp_equipment(2);// サポート武器に装備確定
	//}

	/* サポート武器を装備しているときに、左クリックをしたとき */
	//if( ( Get_Wp_equipment() == 2) && ( System::GetKeyData( System::KEY_LEFTMOUSE)) ){
	//		Set_Wp_equipment(-1);//装備を「素手」にする
	//}

	// 描画、視野角内チェックの武器変更
	if( Eqipment != Get_Wp_equipment()){
			BatPre->BacthGunTrade( Get_Wp_equipment());
	}




	return 0;
}
/*キャラを動かします、前後左右に動けます*/
int PlayerChara::MoveChara(){

	/*変数の初期化*/
	int ech = 0;//エラー確認変数
	int KeyMov = 0;//キーを押してどの方向に動くかの変数
	int MovOn = 0;//動いていいかのフラグ
	float WantDeg = 0;//向きたい方向の変数
	float FixedMoveSpeed = 0.0f;//それぞれの状態の固定速度
	D3DXVECTOR3 SubPos( 0.0, 0.0, 0.0);//キャラクターを置く場所の座標
	D3DXVECTOR3 PCPos( 0.0, 0.0, 0.0);//プレイヤーキャラクターの位置の座標

	/*ダッシュ操作がオンになっていないかチェック*/


	/* キーの状態を取得する */
	if( System::GetKeyData( System::KEY_A) == 1){//左
				KeyMov = KeyMov +1;
	}
	if( System::GetKeyData( System::KEY_W) == 1){//上
				KeyMov = KeyMov +2;
	}
	if( System::GetKeyData( System::KEY_D) == 1){//右
				KeyMov = KeyMov +4;
	}
	if( System::GetKeyData( System::KEY_S) == 1){//下
				KeyMov = KeyMov +8;
	}

	/*キーから取得した情報を変換*/
	switch(KeyMov){//左
		case 1:{
				WantDeg = -90.0f + Get_PC_Deg_XZ();
				MovOn = 1;

				/*モーションを「左歩き」にする*/
				Set_UnderMotion(3);
				break;
		}
		case 2:{//上
				WantDeg = Get_PC_Deg_XZ(); 
				MovOn = 1;

				/*モーションを「歩行」にする*/
				Set_UnderMotion(1);//通常
				break;
		}
		case 3:{//左上
				WantDeg = -45.0f + Get_PC_Deg_XZ(); 
				MovOn = 1;

				/*モーションを「左前進」にする*/
				Set_UnderMotion(4);
				break;
		}
		case 4:{//右
				WantDeg = 90.0f + Get_PC_Deg_XZ(); 
				MovOn = 1;

				/*モーションを「右歩き」にする*/
				Set_UnderMotion(2);
				break;
		}
		case 6:{//右上
				WantDeg = 45.0f + Get_PC_Deg_XZ(); 
				MovOn = 1;

				/*モーションを「左前進」にする*/
				Set_UnderMotion(5);
				break;
		}
		case 8:{//下
				WantDeg = 180.0f + Get_PC_Deg_XZ(); 
				MovOn = 1;

				/*モーションを「後進」にする*/
				Set_UnderMotion(8);
				break;
		}
		case 9:{//左下
				WantDeg = -135.0f + Get_PC_Deg_XZ(); 
				MovOn = 1;

				/*モーションを「左後進」にする*/
				Set_UnderMotion(6);
				break;

	    }
		case 12:{//右下
				WantDeg = 135.0f + Get_PC_Deg_XZ(); 
				MovOn = 1;

				/*モーションを「右後進」にする*/
				Set_UnderMotion(7);
				break;
		}
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
	switch(MovOn){
			case 1:{
					switch(Get_MyState()){
							case 0:{//通常状態なら
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
									break;
						    }
							case 2:{//ダッシュの時
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
									break;
							}
							case 3:// 横っ飛びのとき
							case 4:{
									/*スピードを固定*/
									Set_MoveSpeed(0.0f);

									//固定スピードの設定（しゃがみ）
									FixedMoveSpeed = 90.0f;
									break;
							}
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

					break;
		    }
			default:{
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
	}


	


	return 0;
}
