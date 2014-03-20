/*ここでは、生物クラスのキャラ・敵の関数を定義するクラスコードファイルです。
//特に3人称モード時に関係する時に必要な関数が多く書かれています。
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ
#include "cstage.h"//ステージ関係のクラスヘッダファイル
#include "clive.h"//敵やキャラのクラスヘッダファイル
#include "c_batch_preparat.h"//描画に必要なクラスの宣言ヘッダファイル
#include "cmenu.h"//メニュークラスに関するヘッダファイル
#include <math.h>//数学計算を使うためのヘッダファイル

//ここにグローバル変数を宣言
extern System *sys;//システムクラスを指す、クラスのポインタ

/*3人称視点からの銃関連まとめ関数*/
int PlayerChara::ThirdGunSys( Stage *Stg, Batch_Preparat *BatPre){

	/*変数の初期化*/
	int ech = 0;//エラー確認変数
	D3DXVECTOR3 MyPos1( 0.0, 0.0, 0.0);//最初自分の座標
	D3DXVECTOR3 CameraPos( 0.0, 0.0, 0.0);//カメラの座標
	D3DXVECTOR3 CameraTarget( 0.0, 0.0, 0.0);//カメラの注意点
	D3DXVECTOR3 CameraUpVec( 0.0, 1.0, 0.0);//カメラの上部のベクトル

	/*自キャラを動かします*/
	MoveChara();
	MovePosOnGround( Stg);

	/**/
	//カメラの位置を設定します
	/**/

	/*座標を取得する*/
	ech = E3DGetPos( cha_hsid[0], &MyPos1);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/*後退させる*/
	ech = E3DPosForward( cha_hsid[0], -500);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/*90度傾ける*/
	ech = E3DRotateY( cha_hsid[0], 90);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/*前進させるさせる*/
	ech = E3DPosForward( cha_hsid[0], 270);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/*カメラのポジションになる、PCモデルの位置を取得*/
	ech = E3DGetPos( cha_hsid[0], &CameraPos);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/*90度傾ける*/
	ech = E3DRotateY( cha_hsid[0], -90);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/*カメラをセットする*/
	CameraPos.y = CameraPos.y + 800.0f;//少し高く座標を指定する
	ech = E3DSetCameraPos( CameraPos);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/*前進させるさせる*/
	ech = E3DPosForward( cha_hsid[0], 5000);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/*カメラのポジションになる、PCモデルの位置を取得*/
	ech = E3DGetPos( cha_hsid[0], &CameraTarget);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/*カメラの注意点を指定*/
	CameraTarget.y = CameraTarget.y + 800.0f;
	ech = E3DSetCameraTarget( CameraTarget, CameraUpVec);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/*本来の自分の座標に戻す*/
	ech = E3DSetPos( cha_hsid[0], MyPos1);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};



	/**/
	//手の部分の操縦部分を作ります。
	/**/

	/*中途変数の初期化*/
	int MotionID = 0;//「おなか」ボーンのモーションID
	int FrameNo = 0;//「おなか」ボーンのフレーム番号
	int Garbage = 0;//必要ない変数を格納します
	D3DXVECTOR3 BaseVec( 0.0, 0.0, 1.0);//初期の向きを決めます。
	D3DXVECTOR3 WantDeg( 0.0, 0.0, 0.0);//向きたい方向のベクトル
	D3DXVECTOR3 TurnPos( 0.0, 0.0, 0.0);//向くべき方向の位置
	D3DXVECTOR3 StomachPos( 0.0, 0.0, 0.0);//お腹の位置座標
	D3DXVECTOR3 OriginPos( 0.0, 0.0, 0.0);//キャラクターをおくべき原点
	D3DXVECTOR3 NowPCPos( 0.0, 0.0, 0.0);//キャラクターがいた座標
	D3DXVECTOR3 ScreenPos( 0.0, 0.0, 0.0);//銃先の2Dスクリーン座標
	D3DXVECTOR3 ScreenPos3D( 0.0, 0.0, 0.0);//銃先の2Dスクリーン座標
	static double Tm_DegQ_XZ = 5.25;//ブレがある前の角度変数XZ
	static double Tm_DegQ_Y = 0.50;//ブレがある前の角度変数Y
	double Cos_XZ = 0.0;
	double Sin_XZ = 0.0;
	double Cos_Y = 0.0;
	double Sin_Y = 0.0;



	ech = E3DGetPos( cha_hsid[0], &NowPCPos);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	ech = E3DSetPos ( cha_hsid[0], OriginPos);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	ech = E3DGetCurrentBonePos( cha_hsid[0], bone[2], 1, &StomachPos);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	GetCursorPos( &sys->MousePos);//マウス座標を格納します

	Tm_DegQ_XZ = Tm_DegQ_XZ - 0.0020 * float( sys->MousePos.x - sys->BeforeMousePos.x );//X座標を前マウス-マウスから角度
	Tm_DegQ_Y = Tm_DegQ_Y - 0.0020* float( sys->MousePos.y - sys->BeforeMousePos.y );//Y座標を前マウス-マウス角度

	SetCursorPos( sys->rewin.left + 320, sys->rewin.top + 240);//マウス座標を真ん中へ
	GetCursorPos( &sys->BeforeMousePos);//マウス座標を格納します
	

	if(Tm_DegQ_XZ > 4.8){
				PC_Deg_XZ = PC_Deg_XZ - float(30.0*(Tm_DegQ_XZ - 4.8));//自分の向きを左に回転させます。
				Tm_DegQ_XZ = 4.8;//角度の行き過ぎを調整
	}
	if(Tm_DegQ_XZ < 4.3){
				PC_Deg_XZ = PC_Deg_XZ - float(30.0*(Tm_DegQ_XZ - 4.3));//自分の向きを右に回転させます。
				Tm_DegQ_XZ = 4.3;//角度の行き過ぎを調整
	}
	if(Tm_DegQ_Y> 0.9){
				Tm_DegQ_Y = 0.9;
	}
	if(Tm_DegQ_Y< -0.1){
				Tm_DegQ_Y = -0.1;
	}

	Cos_XZ = cos(Tm_DegQ_XZ);
	Sin_XZ = sin(Tm_DegQ_XZ);
	Cos_Y = cos(Tm_DegQ_Y);
	Sin_Y = sin(Tm_DegQ_Y);

	TurnPos.x = float(Cos_XZ * Cos_Y * 2000);//向くべき方向のX座標
	TurnPos.y = float(Sin_Y * 2000);//向くべき方向のY座標を取得
	TurnPos.z = float(Sin_XZ * Cos_Y * 2000);//向くべき方向のZ座標を取得

	WantDeg.x = float(StomachPos.x - TurnPos.x);//X座標の向く方向のベクトルを取得
	WantDeg.y = float(StomachPos.y - TurnPos.y);//Y座標の向く方向のベクトルを取得
	WantDeg.z = float(StomachPos.z - TurnPos.z);//Z座標の向く方向のベクトルを取得



	/**/
	//最終的なボーン操作を行います
	/**/

	/*「首付け根」部分のモーションはどうか調べます*/
	ech = E3DGetMotionFrameNoML( cha_hsid[0], bone[2], &MotionID, &FrameNo);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/*キャラクターモデルの方向を初期化します*/
	ech = E3DRotateInit( cha_hsid[0]);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/*「首付け根」部分のクォータニオンを調べます*/
	ech = E3DGetCurrentBoneQ( cha_hsid[0], bone[2], 2, Qid[3]);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/*向きたい方向への計算を行います*/
	ech = E3DLookAtQ( Qid[3], WantDeg, BaseVec, 0, 2);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/*計算したクォーターニオンを代入します*/
	ech = E3DSetBoneQ( cha_hsid[0], bone[2], MotionID, FrameNo, Qid[3]);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/*最初の位置に戻す*/
	ech = E3DSetPos( cha_hsid[0], NowPCPos);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/*キャラクターを回転させます*/
	ech = E3DRotateY( cha_hsid[0], PC_Deg_XZ);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/*銃を手の位置に置きます*/
	GunPutOnHand();

	/*当たり判定モデルの一番先のボーン座標を3Dで取得*/
	ech = E3DGetCurrentBonePos( wp_data[(Wp_equipment)][0][2], wp_data[(Wp_equipment)][2][4], 1, &ScreenPos3D);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/*取得した3D座標を2Dに変換*/
	ech = E3DGetScreenPos3FVec( sys->scid1, ScreenPos3D, &ScreenPos);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	BatPre->SpriteData[0][2] = ScreenPos.x - 8.0f;//カーソルのX座標
	BatPre->SpriteData[0][3] = ScreenPos.y - 16.0f;//カーソルのY座標
	



	return 0;
}
/*銃の現在持ってる銃を持つためのモーション・システムを管轄する関数*/
int PlayerChara::GunPutOnHand(){

	/*変数の初期化*/
	int ech = 0;//エラーチェック変数
	int NowWpKind = wp_data[(Wp_equipment)][1][0];//今の武器の種類を取得します
	int NowWpNo = wp_data[(Wp_equipment)][1][4];//今の武器のナンバーを取得します
	int NowGunhsid = wp_data[(Wp_equipment)][0][0];//今の武器のモデルデータIDを取得します
	D3DXVECTOR3 GunOnPos( 0.0, 0.0, 0.0);//銃を置く座標
	D3DXVECTOR3 GunHitPos( 0.0, 0.0, 0.0);//当たり判定モデルを置く座標
	D3DXVECTOR3 MoveVec( 0.0, 0.0, 0.0);
	D3DXVECTOR3 BaseVec( 0.0, 0.0, -1.0);

	/*以下、種類によって振り分けを行います*/

	if(NowWpKind == 1){//武器の種類が、ハンドガンであれば



				/*銃の置くボーンの座標を求めます*/
				ech = E3DGetCurrentBonePos( cha_hsid[0], bone[0], 1, &GunOnPos);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};

				/*銃を求めた座標におきます*/
				ech = E3DSetPos( NowGunhsid, GunOnPos);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};

				/*銃の向きになるボーンのクォータニオンを取得*/
				ech = E3DGetCurrentBoneQ( cha_hsid[0], bone[1], 2, Qid[0]);//手先の向きを取得
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};

				/*向きたい方向への計算を行います*/
				ech = E3DLookAtQ( Qid[0], MoveVec, BaseVec, 0, 0);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};

				/*銃の向きをセットします*/
				ech = E3DSetDirQ2( NowGunhsid, Qid[0]);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};



	}
	if(NowWpKind == 4){//武器の種類が、アサルトライフルであれば

				/*銃の置くボーンの座標を求めます*/
				ech = E3DGetCurrentBonePos( cha_hsid[0], bone[0], 1, &GunOnPos);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};

				/*銃を求めた座標におきます*/
				ech = E3DSetPos( NowGunhsid, GunOnPos);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};

				/*銃の向きになるボーンのクォータニオンを取得*/
				ech = E3DGetCurrentBoneQ( cha_hsid[0], bone[1], 2, Qid[0]);//手先の向きを取得
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};

				/*向きたい方向への計算を行います*/
				ech = E3DLookAtQ( Qid[0], MoveVec, BaseVec, 0, 0);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};

				/*銃の向きをセットします*/
				ech = E3DSetDirQ2( NowGunhsid, Qid[0]);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};



	}


		ech = E3DSetNewPoseML( NowGunhsid);
		if(ech != 0){//エラーチェック
					_ASSERT(0);//エラーダイアログを表示
		};




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

	sys->GetKeyData(keyin);//キー情報を格納

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
				WantDeg = -90.0f + PC_Deg_XZ;
				MovOn = 1;

				/*モーションを「左歩き」にする*/
				UnderMotion = 3;
	}
	if(KeyMov == 3){//左上
				WantDeg = -45.0f + PC_Deg_XZ; 
				MovOn = 1;

				/*モーションを「左前進」にする*/
				UnderMotion = 4;
	}
	if(KeyMov == 2){//上
				WantDeg = PC_Deg_XZ; 
				MovOn = 1;

				/*モーションを「歩行」にする*/
				UnderMotion = 1;//通常

	}
	if(KeyMov == 6){//右上
				WantDeg = 45.0f + PC_Deg_XZ; 
				MovOn = 1;

				/*モーションを「左前進」にする*/
				UnderMotion = 5;
	}
	if(KeyMov == 4){//右
				WantDeg = 90.0f + PC_Deg_XZ; 
				MovOn = 1;

				/*モーションを「右歩き」にする*/
				UnderMotion = 2;
	}
	if(KeyMov == 12){//右下
				WantDeg = 135.0f + PC_Deg_XZ; 
				MovOn = 1;

				/*モーションを「右後進」にする*/
				UnderMotion = 7;
	}
	if(KeyMov == 8){//下
				WantDeg = 180.0f + PC_Deg_XZ; 
				MovOn = 1;

				/*モーションを「後進」にする*/
				UnderMotion = 8;
	}
	if(KeyMov == 9){//左下
				WantDeg = -135.0f + PC_Deg_XZ; 
				MovOn = 1;

				/*モーションを「左後進」にする*/
				UnderMotion = 6;

	}

	//キーが入力されていても、キック中なら
	if( MyState == 1) {
				MovOn = 0;//絶対動かない
	}

	//空中で、ダッシュ状態なら
	if( ( AirOnPC == 1) && ( MyState == 2)){
				WantDeg = PC_Deg_XZ;//まっすぐ進む
				MovOn = 1;//絶対動く
	}

	//左飛び状態なら
	if( MyState == 3) {
				WantDeg = -90.0f + PC_Deg_XZ;
				MovOn = 1;//絶対動く
	}

	//右飛び状態なら
	if( MyState == 4) {
				WantDeg = 90.0f + PC_Deg_XZ; 
				MovOn = 1;//絶対動く
	}


	/*動く方向を決めるよ*/
	if(MovOn == 1){

					if( MyState == 0){//通常状態なら
							if( AirOnPC == 0){//空中でなければ
									if(Attitude == 0){//姿勢が「立っている状態」なら
											/*スピードを増加させる*/
											MoveSpeed = MoveSpeed + 0.8f;

											//スピードに制限をかける
											if( 25.0f <= MoveSpeed ){
														MoveSpeed = 25.0f;
											}

											//固定スピードの設定（立ち）
											FixedMoveSpeed = 50.0f;
									}

									if(Attitude == 1){//姿勢が「しゃがみ状態」なら
											/*スピードを増加させる*/
											MoveSpeed = MoveSpeed + 0.4f;

											//スピードに制限をかける
											if( 20.0f <= MoveSpeed ){
														MoveSpeed = 20.0f;
											}

											//固定スピードの設定（しゃがみ）
											FixedMoveSpeed = 30.0f;
									}
							}
							if( AirOnPC == 1){//空中にいるなら
									
									/*スピードを増加させる*/
									MoveSpeed = MoveSpeed + 0.3f;

									//スピードに制限をかける
									if( 10.0f <= MoveSpeed ){
												MoveSpeed = 10.0f;
									}

									//固定スピードの設定（しゃがみ）
									FixedMoveSpeed = 20.0f;
							}

					}
					if( MyState == 2){//ダッシュ状態なら

							if( AirOnPC == 0){//地上にいるなら
									/*スピードを増加させる*/
									MoveSpeed = MoveSpeed + 2.0f;

									//スピードに制限をかける
									if( 40.0f <= MoveSpeed ){
												MoveSpeed = 40.0f;
									}

									//固定スピードの設定（しゃがみ）
									FixedMoveSpeed = 70.0f;
							}
							if( AirOnPC == 1){//空中にいるなら
									/*スピードを増加させる*/
									MoveSpeed = MoveSpeed + 2.0f;

									//スピードに制限をかける
									if( 40.0f <= MoveSpeed ){
												MoveSpeed = 40.0f;
									}

									//固定スピードの設定（しゃがみ）
									FixedMoveSpeed = 70.0f;
							}
					}
					if( ( MyState == 3) || ( MyState == 4)){//左飛び状態なら
									/*スピードを固定*/
									MoveSpeed = 0.0f;

									//固定スピードの設定（しゃがみ）
									FixedMoveSpeed = 90.0f;
					}



					/*ダミーモデルの座標に設定*/
					ech = E3DRotateInit ( DummyModel);
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
					};

					ech = E3DGetPos( cha_hsid[0], &PCPos);
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
					};

					ech = E3DSetPos( DummyModel, PCPos);
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
					};

					ech = E3DRotateY( DummyModel, WantDeg);
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
					};

					ech = E3DPosForward( DummyModel, (float)MoveSpeed + FixedMoveSpeed);
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
					};

					ech = E3DGetPos( DummyModel, &SubPos);
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
					};

					ech = E3DSetPos( cha_hsid[0], SubPos);
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
					};
	}
	else{//減速をさせなければならないなら
					if( AirOnPC == 0){//空中にいるなら
								if( Attitude == 0) MoveSpeed = MoveSpeed - 0.8f;//姿勢が「通常状態」なら
								if( Attitude == 1) MoveSpeed = MoveSpeed - 1.0f;//姿勢が「しゃがみ状態」なら
					}
					if( AirOnPC == 1) MoveSpeed = MoveSpeed - 0.6f;//姿勢が「しゃがみ状態」なら


					//スピードに制限をかける
					if( MoveSpeed <= 0.0 ){
								MoveSpeed = 0.0f;
					}



					UnderMotion = 0;
	}




	return 0;
}
/*キャラクターをグラウンドの上に置くための関数*/
int PlayerChara::MovePosOnGround( Stage *Stg){

	/*変数の初期化*/
	int ech = 0;//エラーチェック
	int GroundResult = 0;//地面の当たり判定の結果
	int MoveStopFlg = 0;//空中に浮かんでいるときに移動できないようにするためのフラグ
	static int BeforeAirOnPC = 0;//前回のキャラクターが空中にいるか代入します
	D3DXVECTOR3 ReflectVec( 0.0, 0.0, 0.0);//地面の反射ベクトルの構造体
	D3DXVECTOR3 GroundOnPos( 0.0, 0.0, 0.0);//自キャラを地面に垂直におろした場合の座標
	D3DXVECTOR3 MyPos( 0.0, 0.0, 0.0);//自分のキャラクター座標


	/**/
	//ステージグラウンドごとにどのような処理にさせるか振り分けます
	/**/

	if( Stg->Stage_GndMode == 0){

			/*地面とPCの当たり判定のチェック*/
			ech = E3DChkConfGround( cha_hsid[0], Stg->Stage_hsid[0], 1, 500, -1000, &GroundResult, &GroundOnPos, &ReflectVec);
			if(ech != 0 ){//エラーチェック
						_ASSERT( 0 );//エラーダイアログ
			};

			ech = E3DGetPos( cha_hsid[0], &MyPos);
			if(ech != 0 ){//エラーチェック
						_ASSERT( 0 );//エラーダイアログ
			};

			/*もし地面の高さがかなり離れているか、横っ飛び状態なら*/
			if( (400 < MyPos.y - GroundOnPos.y) || ( MyState == 3) || ( MyState == 4) ){

						/*加速度を追加する*/
						Acceleration = Acceleration - 8.0;

						/*前回はとんでなかった場合*/
						if( BeforeAirOnPC == 0){
									/*ダッシュ中の場合*/
									if( ( MyState == 2) && ( BeforeAirOnPC == 0)) {
												Acceleration = 100;//空中でジャンプしたことにする
									}
									/*横っ飛び状態なら*/
									if( (MyState == 3) || ( MyState == 4)) {
												Acceleration = 70;//空中でジャンプしたことにする
									}
						}

						/*加速度に制限をかける*/
						if(  Acceleration <= -700 ){
									Acceleration = -700;
						}

						/*自分の座標を下げる*/
						MyPos.y = MyPos.y + float(Acceleration);

						/*キャラクターを空中に置く*/
						ech = E3DSetPos( cha_hsid[0], MyPos);
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
						};

						/*移動可能フラグをオフにする*/
						MoveStopFlg = 1;

						/*モーションを「ジャンプ中」にする*/
						UnderMotion = 9;

						/*空中フラグをオンにする*/
						AirOnPC = 1;

			}
			else{
						/*キャラクターを地面上に置く*/
						ech = E3DSetPos( cha_hsid[0], GroundOnPos);
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
						};

						/*加速度を0にする*/
						Acceleration = 0.0;

						/*移動可能フラグをオフにする*/
						MoveStopFlg = 0;

						/*空中フラグをオフにする*/
						AirOnPC = 0;
			}
	}


	/*今回のキャラクターが空中にいるか代入します(次ループ時使用)*/
	BeforeAirOnPC = AirOnPC;


	return 0;
}
