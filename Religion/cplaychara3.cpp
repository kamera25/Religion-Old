/*ここでは、生物クラスのキャラ・敵の関数を定義するクラスコードファイルです。
//特に肩打ちモード時に関係する時に必要な関数が多く書かれています。
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ
#include "cstage.h"//ステージ関係のクラスヘッダファイル
#include "clive.h"//敵やキャラのクラスヘッダファイル
#include "c_batch_preparat.h"//描画に必要なクラスの宣言ヘッダファイル
#include <math.h>//数学計算を使うためのヘッダファイル
#include "cweapon.h"//武器に関することのクラスヘッダファイル





/*肩射ち視点からの銃関連まとめ関数*/
int PlayerChara::ShoulderGunSys( Batch_Preparat *BatPre, int ScreenPos[2]){

	/*全体で使う変数の初期化*/
	int ech = 0;//エラー確認変数
	D3DXVECTOR3 BaseVec( 0.0, 0.0, -1.0);//向きの初期方向ベクトル
	D3DXVECTOR3 CameraUpVec( 0.0, 1.0, 0.0);//カメラの上部のベクトル

  /*キャラクターの位置を設定します*/
	int MotionID = 0;//MLから取得した現在の「首付け根」モーションID
	int FrameNo = 0;//MLから取得した現在の「首付け根」モーションが現在再生している番号
	static double Tm_DegQ_Y = 0.50;//ブレがある前の角度変数Y
	double Sin_Y = 0.0;//Y座標サイン変数
	double Sin_XZ = 0.0;//XZ座標サイン変数
	double Cos_Y = 0.0;//Y座標コサイン変数
	double Cos_XZ = 0.0;//XZ座標コサイン変数
	D3DXVECTOR3 TurnPos( 0.0, 0.0, 0.0);//向くべきYベクトル
	D3DXVECTOR3 StomachPos( 0.0, 0.0, 0.0);//「首つけ根」の座標
	D3DXVECTOR3 WantDeg( 0.0, 0.0, 0.0);//向きたい方向へのベクトル
	D3DXVECTOR3 OriginPos( 0.0, 0.0, 0.0);//キャラクターをおくべき原点座標
	D3DXVECTOR3 MyPos1( 0.0, 0.0, 0.0);//最初自分の座標

	/**/
	//自分の向きを回転させます。
	/**/

	//最初に回転の計算します
	if(( MyState == 0) || ( (MyState == 2) && ( AirOnPC == 0))){//通常・空中ダッシュモードでなければ、以下取得せず
				PC_Deg_XZ = PC_Deg_XZ + float(0.30*(System::MousePos.x - (System::BeforeMousePos.x - System::rewin.left)));
				Tm_DegQ_Y = Tm_DegQ_Y - 0.0020* float( System::MousePos.y - System::BeforeMousePos.y + System::rewin.top);
	}

	if( ( MyState == 3) || ( MyState == 4)){//よっこ飛びの時は
				Tm_DegQ_Y = Tm_DegQ_Y - 0.0020* float( System::MousePos.y - System::BeforeMousePos.y + System::rewin.top);
	}

	if( PC_Deg_XZ < 0){
				PC_Deg_XZ = PC_Deg_XZ + 360;
	}
	if( 360 < PC_Deg_XZ){
				PC_Deg_XZ = PC_Deg_XZ - 360;
	}
	if(Tm_DegQ_Y> 0.9){
				Tm_DegQ_Y = 0.9;
	}
	if(Tm_DegQ_Y< -0.5){
				Tm_DegQ_Y = -0.5;
	}

	SetCursorPos( System::rewin.left + 320, System::rewin.top + 240);//マウス座標を真ん中へ
	GetCursorPos( &System::BeforeMousePos);//マウス座標を格納します

	Cos_XZ = cos(4.8);//XZ座標コサインの取得
	Sin_XZ = sin(4.8);//XZ座標サインの取得
	Sin_Y = sin(Tm_DegQ_Y);//Y座標サインの取得
	Cos_Y = cos(Tm_DegQ_Y);//Y座標のコサインの取得
	TurnPos.x = float(Cos_XZ * Cos_Y * 2000);//向くべき方向のX座標
	TurnPos.y = float(Sin_Y * 2000);//向くべき方向のY座標を取得
	TurnPos.z = float(Sin_XZ * Cos_Y * 2000);//向くべき方向のZ座標を取得

	/**/
	//次に座標を取得したりしてモデルのボーンを操作します
	/**/

	/*キャラクターモデルの方向を初期化します*/
	ech = E3DRotateInit( cha_hsid[0]);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/*座標を取得する*/
	ech = E3DGetPos( cha_hsid[0], &MyPos1);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/*座標を原点にする*/
	ech = E3DSetPos( cha_hsid[0], OriginPos);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/*キャラクターモデルの「首つけ根」の座標を取得します*/
	ech = E3DGetCurrentBonePos( cha_hsid[0], bone[2], 1, &StomachPos);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};



	WantDeg.x = float( TurnPos.x - StomachPos.x);//X座標の向く方向のベクトルを取得
	WantDeg.y = float( TurnPos.y - StomachPos.y);//Y座標の向く方向のベクトルを取得
	WantDeg.z = float( TurnPos.z - StomachPos.z);//Z座標の向く方向のベクトルを取得

	/*「首付け根」部分のモーションはどうか調べます*/
	ech = E3DGetMotionFrameNoML( cha_hsid[0], bone[2], &MotionID, &FrameNo);
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

	/*マルチレイヤーモーションの計算を行います*/
	ech = E3DCalcMLMotion( cha_hsid[0]);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/*本来の自分の座標に戻す*/
	ech = E3DSetPos( cha_hsid[0], MyPos1);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/*キャラクターを回転させます*/
	ech = E3DRotateY( cha_hsid[0], PC_Deg_XZ);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	
	/*スプライトの位置を決めて終了します*/
	BatPre->SpriteData[0][2] = 320 - 16.0f;//カーソルのX座標
	BatPre->SpriteData[0][3] = 220 - 18.0f;//カーソルのY座標

	ScreenPos[0] = 320;/**/ScreenPos[1] = 220;

	return 0;
}

/*キャラクターの後処理を行う関数、モーションや姿勢など*/
int PlayerChara::ShoulderGunSysBefore( ){

	/*変数の初期化*/
	int ech = 0;//エラー確認変数
	int MotionID = 0;//MLから取得した現在の「首付け根」モーションID
	int FrameNo = 0;//MLから取得した現在の「首付け根」モーションが現在再生している番号
	int MotionList[10];//動かす部分を指定する配列
	int NoMotionList[10];//動かさない部分を指定する配列
	D3DXVECTOR3 Squat( 0.0, 0.0, 0.0);//しゃがんだ状態の座標を入れる


	/*配列変数の初期化*/
	for( int i=0; i<10; i++){
			MotionList[i] = 0;//動かす部分を指定する配列を初期化
			NoMotionList[i] = 0;//動かさない部分を指定する配列を初期化
	}

	if( MyState == 0){
			/**/
			/*上半身のモーション設定*/

			if( Attitude == 0){//しゃがみモードがオフなら
					if( Wp_equipment != -1){//武器を装備している状態なら
						if( Wpn.GetWeaponData( Wp_equipment, 0) == 1){//ハンドガンを撃つのなら
										if( UpMotion == 0){//普通の構え

												/*モーションで動かす部分の指定*/
												MotionList[0] = bone[5];//「おなか」のボーンを指定
												MotionList[1] = 0;//指定終了
							
												/*モーションで動かさない部分の指定*/
												NoMotionList[0] = 0;//指定終了

												/*モーションを設定する*/
												ech = E3DSetMOAEventNoML( cha_hsid[0], 4, MotionList, NoMotionList);//ハンドガン構え
												if(ech != 0){//エラーチェック
															_ASSERT(0);//エラーダイアログを表示
												};
										}
							}
							if( Wpn.GetWeaponData( Wp_equipment, 0) == 4){//アサルトを撃つのなら
										if( UpMotion == 0){//普通の構え
					
												/*モーションで動かす部分の指定*/
												MotionList[0] = bone[5];//「おなか」のボーンを指定
												MotionList[1] = 0;//指定終了
							
												/*モーションで動かさない部分の指定*/
												NoMotionList[0] = 0;//指定終了

												/*モーションを設定する*/
												ech = E3DSetMOAEventNoML( cha_hsid[0], 3, MotionList, NoMotionList);//ハンドガン構え
												if(ech != 0){//エラーチェック
															_ASSERT(0);//エラーダイアログを表示
												};
										}
							}
					}
					else{//武器を装備していない状態なら
							/*モーションで動かす部分の指定*/
												/*モーションで動かす部分の指定*/
												MotionList[0] = bone[5];//「おなか」のボーンを指定
												MotionList[1] = 0;//指定終了
							
												/*モーションで動かさない部分の指定*/
												NoMotionList[0] = 0;//指定終了

												/*モーションを設定する*/
												ech = E3DSetMOAEventNoML( cha_hsid[0], 3, MotionList, NoMotionList);//ハンドガン構え
												if(ech != 0){//エラーチェック
															_ASSERT(0);//エラーダイアログを表示
												};
					}
			}

			/**/
			if( Attitude == 1){//しゃがみモードがオンなら
					if( Wp_equipment != -1){//武器を装備している状態なら
							if( Wpn.GetWeaponData( Wp_equipment, 0) == 1){//ハンドガンを撃つのなら
										if( UpMotion == 0){//普通の構え

												/*モーションで動かす部分の指定*/
												MotionList[0] = bone[5];//「おなか」のボーンを指定
												MotionList[1] = 0;//指定終了
							
												/*モーションで動かさない部分の指定*/
												NoMotionList[0] = 0;//指定終了

												/*モーションを設定する*/
												ech = E3DSetMOAEventNoML( cha_hsid[0], 4, MotionList, NoMotionList);//ハンドガン構え
												if(ech != 0){//エラーチェック
															_ASSERT(0);//エラーダイアログを表示
												};
										}
							}
							if( Wpn.GetWeaponData( Wp_equipment, 0) == 4){//アサルトを撃つのなら
										if( UpMotion == 0){//普通の構え
					
												/*モーションで動かす部分の指定*/
												MotionList[0] = bone[5];//「おなか」のボーンを指定
												MotionList[1] = 0;//指定終了
							
												/*モーションで動かさない部分の指定*/
												NoMotionList[0] = 0;//指定終了

												/*モーションを設定する*/
												ech = E3DSetMOAEventNoML( cha_hsid[0], 3, MotionList, NoMotionList);//ハンドガン構え
												if(ech != 0){//エラーチェック
															_ASSERT(0);//エラーダイアログを表示
												};
										}
							}
					}
					else{//武器を装備していない状態なら
							/*モーションで動かす部分の指定*/
												/*モーションで動かす部分の指定*/
												MotionList[0] = bone[5];//「おなか」のボーンを指定
												MotionList[1] = 0;//指定終了
							
												/*モーションで動かさない部分の指定*/
												NoMotionList[0] = 0;//指定終了

												/*モーションを設定する*/
												ech = E3DSetMOAEventNoML( cha_hsid[0], 3, MotionList, NoMotionList);//ハンドガン構え
												if(ech != 0){//エラーチェック
															_ASSERT(0);//エラーダイアログを表示
												};
					}
			}


			

			/*配列変数の初期化*/
			for( int i=0; i<10; i++){
					MotionList[i] = 0;//動かす部分を指定する配列を初期化
					NoMotionList[i] = 0;//動かさない部分を指定する配列を初期化
			}

			/**/
			/*下半身のモーション設定*/
			if( Attitude == 0){//しゃがみモードがオフなら
					if( UnderMotion == 0){//止まるのなら

								/*モーションで動かす部分の指定*/
								MotionList[0] = bone[6];//「移動先」のボーンを指定
								MotionList[1] = 0;//指定終了

								/*モーションで動かさない部分の指定*/
								NoMotionList[0] = bone[5];//「おなか」ボーンを指定
								NoMotionList[1] = 0;//指定終了

								/*モーションを設定する*/
								ech = E3DSetMOAEventNoML( cha_hsid[0], 2, MotionList, NoMotionList);
								if(ech != 0){//エラーチェック
											_ASSERT(0);//エラーダイアログを表示
								};
					}
					if( UnderMotion == 1){//前進するのなら

								/*モーションで動かす部分の指定*/
								MotionList[0] = bone[6];//「移動先」のボーンを指定
								MotionList[1] = 0;//指定終了

								/*モーションで動かさない部分の指定*/
								NoMotionList[0] = bone[5];//「おなか」ボーンを指定
								NoMotionList[1] = 0;//指定終了

								/*モーションを設定する*/
								ech = E3DSetMOAEventNoML( cha_hsid[0], 1, MotionList, NoMotionList);
								if(ech != 0){//エラーチェック
											_ASSERT(0);//エラーダイアログを表示
								};
					}
					if( UnderMotion == 2){//右進するのなら

								/*モーションで動かす部分の指定*/
								MotionList[0] = bone[6];//「移動先」のボーンを指定
								MotionList[1] = 0;//指定終了

								/*モーションで動かさない部分の指定*/
								NoMotionList[0] = bone[5];//「おなか」ボーンを指定
								NoMotionList[1] = 0;//指定終了

								/*モーションを設定する*/
								ech = E3DSetMOAEventNoML( cha_hsid[0], 5, MotionList, NoMotionList);
								if(ech != 0){//エラーチェック
											_ASSERT(0);//エラーダイアログを表示
								};
					}
					if( UnderMotion == 3){//左進するのなら

								/*モーションで動かす部分の指定*/
								MotionList[0] = bone[6];//「移動先」のボーンを指定
								MotionList[1] = 0;//指定終了

								/*モーションで動かさない部分の指定*/
								NoMotionList[0] = bone[5];//「おなか」ボーンを指定
								NoMotionList[1] = 0;//指定終了

								/*モーションを設定する*/
								ech = E3DSetMOAEventNoML( cha_hsid[0], 6, MotionList, NoMotionList);
								if(ech != 0){//エラーチェック
											_ASSERT(0);//エラーダイアログを表示
								};
					}
					if( UnderMotion == 4){//左前進するのなら

								/*モーションで動かす部分の指定*/
								MotionList[0] = bone[6];//「移動先」のボーンを指定
								MotionList[1] = 0;//指定終了

								/*モーションで動かさない部分の指定*/
								NoMotionList[0] = bone[5];//「おなか」ボーンを指定
								NoMotionList[1] = 0;//指定終了

								/*モーションを設定する*/
								ech = E3DSetMOAEventNoML( cha_hsid[0], 7, MotionList, NoMotionList);
								if(ech != 0){//エラーチェック
											_ASSERT(0);//エラーダイアログを表示
								};
					}
					if( UnderMotion == 5){//右前進するのなら

								/*モーションで動かす部分の指定*/
								MotionList[0] = bone[6];//「移動先」のボーンを指定
								MotionList[1] = 0;//指定終了

								/*モーションで動かさない部分の指定*/
								NoMotionList[0] = bone[5];//「おなか」ボーンを指定
								NoMotionList[1] = 0;//指定終了

								/*モーションを設定する*/
								ech = E3DSetMOAEventNoML( cha_hsid[0], 8, MotionList, NoMotionList);
								if(ech != 0){//エラーチェック
											_ASSERT(0);//エラーダイアログを表示
								};
					}
					if( UnderMotion == 6){//左後進するのなら

								/*モーションで動かす部分の指定*/
								MotionList[0] = bone[6];//「移動先」のボーンを指定
								MotionList[1] = 0;//指定終了

								/*モーションで動かさない部分の指定*/
								NoMotionList[0] = bone[5];//「おなか」ボーンを指定
								NoMotionList[1] = 0;//指定終了

								/*モーションを設定する*/
								ech = E3DSetMOAEventNoML( cha_hsid[0], 9, MotionList, NoMotionList);
								if(ech != 0){//エラーチェック
											_ASSERT(0);//エラーダイアログを表示
								};
					}
					if( UnderMotion == 7){//右後進するのなら

								/*モーションで動かす部分の指定*/
								MotionList[0] = bone[6];//「移動先」のボーンを指定
								MotionList[1] = 0;//指定終了

								/*モーションで動かさない部分の指定*/
								NoMotionList[0] = bone[5];//「おなか」ボーンを指定
								NoMotionList[1] = 0;//指定終了

								/*モーションを設定する*/
								ech = E3DSetMOAEventNoML( cha_hsid[0], 10, MotionList, NoMotionList);
								if(ech != 0){//エラーチェック
											_ASSERT(0);//エラーダイアログを表示
								};
					}
					if( UnderMotion == 8){//後進するのなら

								/*モーションで動かす部分の指定*/
								MotionList[0] = bone[6];//「移動先」のボーンを指定
								MotionList[1] = 0;//指定終了

								/*モーションで動かさない部分の指定*/
								NoMotionList[0] = bone[5];//「おなか」ボーンを指定
								NoMotionList[1] = 0;//指定終了

								/*モーションを設定する*/
								ech = E3DSetMOAEventNoML( cha_hsid[0], 11, MotionList, NoMotionList);
								if(ech != 0){//エラーチェック
											_ASSERT(0);//エラーダイアログを表示
								};
					}
					if( UnderMotion == 9){//ジャンプにするのなら

								/*モーションで動かす部分の指定*/
								MotionList[0] = bone[6];//「移動先」のボーンを指定
								MotionList[1] = 0;//指定終了

								/*モーションで動かさない部分の指定*/
								NoMotionList[0] = bone[5];//「おなか」ボーンを指定
								NoMotionList[1] = 0;//指定終了

								/*モーションを設定する*/
								ech = E3DSetMOAEventNoML( cha_hsid[0], 24, MotionList, NoMotionList);
								if(ech != 0){//エラーチェック
											_ASSERT(0);//エラーダイアログを表示
								};
					}
			}

			/**/
			if( Attitude == 1){//しゃがみモードがオンなら
					if( UnderMotion == 0){//止まるのなら

								/*モーションで動かす部分の指定*/
								MotionList[0] = bone[6];//「移動先」のボーンを指定
								MotionList[1] = 0;//指定終了

								/*モーションで動かさない部分の指定*/
								NoMotionList[0] = bone[5];//「おなか」ボーンを指定
								NoMotionList[1] = 0;//指定終了

								/*モーションを設定する*/
								ech = E3DSetMOAEventNoML( cha_hsid[0], 13, MotionList, NoMotionList);
								if(ech != 0){//エラーチェック
											_ASSERT(0);//エラーダイアログを表示
								};
					}
					if( UnderMotion == 1){//前進するのなら

								/*モーションで動かす部分の指定*/
								MotionList[0] = bone[6];//「移動先」のボーンを指定
								MotionList[1] = 0;//指定終了

								/*モーションで動かさない部分の指定*/
								NoMotionList[0] = bone[5];//「おなか」ボーンを指定
								NoMotionList[1] = 0;//指定終了

								/*モーションを設定する*/
								ech = E3DSetMOAEventNoML( cha_hsid[0], 14, MotionList, NoMotionList);
								if(ech != 0){//エラーチェック
											_ASSERT(0);//エラーダイアログを表示
								};
					}
					if( UnderMotion == 2){//右進するのなら

								/*モーションで動かす部分の指定*/
								MotionList[0] = bone[6];//「移動先」のボーンを指定
								MotionList[1] = 0;//指定終了

								/*モーションで動かさない部分の指定*/
								NoMotionList[0] = bone[5];//「おなか」ボーンを指定
								NoMotionList[1] = 0;//指定終了

								/*モーションを設定する*/
								ech = E3DSetMOAEventNoML( cha_hsid[0], 16, MotionList, NoMotionList);
								if(ech != 0){//エラーチェック
											_ASSERT(0);//エラーダイアログを表示
								};
					}
					if( UnderMotion == 3){//左進するのなら

								/*モーションで動かす部分の指定*/
								MotionList[0] = bone[6];//「移動先」のボーンを指定
								MotionList[1] = 0;//指定終了

								/*モーションで動かさない部分の指定*/
								NoMotionList[0] = bone[5];//「おなか」ボーンを指定
								NoMotionList[1] = 0;//指定終了

								/*モーションを設定する*/
								ech = E3DSetMOAEventNoML( cha_hsid[0], 17, MotionList, NoMotionList);
								if(ech != 0){//エラーチェック
											_ASSERT(0);//エラーダイアログを表示
								};
					}
					if( UnderMotion == 4){//左前進するのなら

								/*モーションで動かす部分の指定*/
								MotionList[0] = bone[6];//「移動先」のボーンを指定
								MotionList[1] = 0;//指定終了

								/*モーションで動かさない部分の指定*/
								NoMotionList[0] = bone[5];//「おなか」ボーンを指定
								NoMotionList[1] = 0;//指定終了

								/*モーションを設定する*/
								ech = E3DSetMOAEventNoML( cha_hsid[0], 19, MotionList, NoMotionList);
								if(ech != 0){//エラーチェック
											_ASSERT(0);//エラーダイアログを表示
								};
					}
					if( UnderMotion == 5){//右前進するのなら

								/*モーションで動かす部分の指定*/
								MotionList[0] = bone[6];//「移動先」のボーンを指定
								MotionList[1] = 0;//指定終了

								/*モーションで動かさない部分の指定*/
								NoMotionList[0] = bone[5];//「おなか」ボーンを指定
								NoMotionList[1] = 0;//指定終了

								/*モーションを設定する*/
								ech = E3DSetMOAEventNoML( cha_hsid[0], 18, MotionList, NoMotionList);
								if(ech != 0){//エラーチェック
											_ASSERT(0);//エラーダイアログを表示
								};
					}
					if( UnderMotion == 6){//左後進するのなら

								/*モーションで動かす部分の指定*/
								MotionList[0] = bone[6];//「移動先」のボーンを指定
								MotionList[1] = 0;//指定終了

								/*モーションで動かさない部分の指定*/
								NoMotionList[0] = bone[5];//「おなか」ボーンを指定
								NoMotionList[1] = 0;//指定終了

								/*モーションを設定する*/
								ech = E3DSetMOAEventNoML( cha_hsid[0], 21, MotionList, NoMotionList);
								if(ech != 0){//エラーチェック
											_ASSERT(0);//エラーダイアログを表示
								};
					}
					if( UnderMotion == 7){//右後進するのなら

								/*モーションで動かす部分の指定*/
								MotionList[0] = bone[6];//「移動先」のボーンを指定
								MotionList[1] = 0;//指定終了

								/*モーションで動かさない部分の指定*/
								NoMotionList[0] = bone[5];//「おなか」ボーンを指定
								NoMotionList[1] = 0;//指定終了

								/*モーションを設定する*/
								ech = E3DSetMOAEventNoML( cha_hsid[0], 20, MotionList, NoMotionList);
								if(ech != 0){//エラーチェック
											_ASSERT(0);//エラーダイアログを表示
								};
					}
					if( UnderMotion == 8){//後進するのなら

								/*モーションで動かす部分の指定*/
								MotionList[0] = bone[6];//「移動先」のボーンを指定
								MotionList[1] = 0;//指定終了

								/*モーションで動かさない部分の指定*/
								NoMotionList[0] = bone[5];//「おなか」ボーンを指定
								NoMotionList[1] = 0;//指定終了

								/*モーションを設定する*/
								ech = E3DSetMOAEventNoML( cha_hsid[0], 15, MotionList, NoMotionList);
								if(ech != 0){//エラーチェック
											_ASSERT(0);//エラーダイアログを表示
								};
					}
					if( UnderMotion == 9){//ジャンプにするのなら

								/*モーションで動かす部分の指定*/
								MotionList[0] = bone[6];//「移動先」のボーンを指定
								MotionList[1] = 0;//指定終了

								/*モーションで動かさない部分の指定*/
								NoMotionList[0] = bone[5];//「おなか」ボーンを指定
								NoMotionList[1] = 0;//指定終了

								/*モーションを設定する*/
								ech = E3DSetMOAEventNoML( cha_hsid[0], 26, MotionList, NoMotionList);
								if(ech != 0){//エラーチェック
											_ASSERT(0);//エラーダイアログを表示
								};
					}
			}
	}
	if( MyState == 1){//キックフラグがオンなら
			/*モーションで動かす部分の指定*/
			MotionList[0] = bone[6];//「移動先」のボーンを指定
			MotionList[1] = 0;//指定終了

			/*モーションで動かさない部分の指定*/
			NoMotionList[0] = bone[5];//「おなか」ボーンを指定
			NoMotionList[1] = 0;//指定終了

			/*モーションを設定する*/
			ech = E3DSetMOAEventNoML( cha_hsid[0], 22, MotionList, NoMotionList);
			if(ech != 0){//エラーチェック
						_ASSERT(0);//エラーダイアログを表示
			};
	}
	if( MyState == 2){//ダッシュフラグがオンなら
			if( AirOnPC == 0){//ジャンプしていないなら
					/*モーションで動かす部分の指定*/
					MotionList[0] = bone[6];//「移動先」のボーンを指定
					MotionList[1] = 0;//指定終了

					/*モーションで動かさない部分の指定*/
					NoMotionList[0] = bone[5];//「おなか」ボーンを指定
					NoMotionList[1] = 0;//指定終了

					/*モーションを設定する*/
					ech = E3DSetMOAEventNoML( cha_hsid[0], 23, MotionList, NoMotionList);
					if(ech != 0){//エラーチェック
								_ASSERT(0);//エラーダイアログを表示
					};
			}
			if( AirOnPC == 1){//ジャンプしているのなら
					/*モーションで動かす部分の指定*/
					MotionList[0] = bone[6];//「移動先」のボーンを指定
					MotionList[1] = 0;//指定終了

					/*モーションで動かさない部分の指定*/
					NoMotionList[0] = bone[5];//「おなか」ボーンを指定
					NoMotionList[1] = 0;//指定終了

					/*モーションを設定する*/
					ech = E3DSetMOAEventNoML( cha_hsid[0], 25, MotionList, NoMotionList);
					if(ech != 0){//エラーチェック
								_ASSERT(0);//エラーダイアログを表示
					};
			}
	}
	if( MyState == 3){//左横っ飛び状態なら
					/*モーションで動かす部分の指定*/
					MotionList[0] = bone[6];//「移動先」のボーンを指定
					MotionList[1] = 0;//指定終了

					/*モーションで動かさない部分の指定*/
					NoMotionList[0] = bone[5];//「おなか」ボーンを指定
					NoMotionList[1] = 0;//指定終了

					/*モーションを設定する*/
					ech = E3DSetMOAEventNoML( cha_hsid[0], 12, MotionList, NoMotionList);
					if(ech != 0){//エラーチェック
								_ASSERT(0);//エラーダイアログを表示
					};
	}
	if( MyState == 4){//右横っ飛び状態なら
					/*モーションで動かす部分の指定*/
					MotionList[0] = bone[6];//「移動先」のボーンを指定
					MotionList[1] = 0;//指定終了

					/*モーションで動かさない部分の指定*/
					NoMotionList[0] = bone[5];//「おなか」ボーンを指定
					NoMotionList[1] = 0;//指定終了

					/*モーションを設定する*/
					ech = E3DSetMOAEventNoML( cha_hsid[0], 12, MotionList, NoMotionList);
					if(ech != 0){//エラーチェック
								_ASSERT(0);//エラーダイアログを表示
					};
	}



	/*マルチレイヤーに沿って新モーションを当てる*/
	ech = E3DSetNewPoseML( cha_hsid[0]);
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};

	/*「首付け根」部分のモーションはどうか調べます*/
	ech = E3DGetMotionFrameNoML( cha_hsid[0], bone[2], &MotionID, &FrameNo);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/*計算したクォーターニオンを代入します*/
	ech = E3DSetBoneQ( cha_hsid[0], bone[2], MotionID, FrameNo, Qid[3]);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/*マルチレイヤーモーションの計算を行います*/
	ech = E3DCalcMLMotion( cha_hsid[0]);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};


	return 0;
}