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

