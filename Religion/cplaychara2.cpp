/*ここでは、生物クラスのキャラ・敵の関数を定義するクラスコードファイルです。
//通常動作に関係する時に必要な関数が多く書かれています。
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ
#include "cstage.h"//ステージ関係のクラスヘッダファイル
#include "clive.h"//敵やキャラのクラスヘッダファイル
#include "c_batch_preparat.h"//描画に必要なクラスの宣言ヘッダファイル
#include "cmenu.h"//メニュークラスに関するヘッダファイル
#include <math.h>//数学計算を使うためのヘッダファイル
#include "cweapon.h"//武器に関することのクラスヘッダファイル





/*銃の現在持ってる銃を持つためのモーション・システムを管轄する関数*/
int PlayerChara::GunPutOnHand(){

	/*変数の初期化*/
	int ech = 0;//エラーチェック変数
	int NowWpKind = Wpn.GetWeaponData( Wp_equipment, 0);//今の武器の種類を取得します
	int NowWpNo = Wpn.GetWeaponData( Wp_equipment, 1);//今の武器のナンバーを取得します
	int NowGunhsid = Wpn.GetWeaponModelID( Wp_equipment, 0);//今の武器のモデルデータIDを取得します
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
