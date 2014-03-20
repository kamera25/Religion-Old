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
#include "ccamera.h"//カメラに関することのクラスヘッダファイル
#include "cweapon.h"//武器に関することのクラスヘッダファイル

//ここにグローバル変数を宣言
extern System *sys;//システムクラスを指す、クラスのポインタ


/*肩射ち視点からの銃関連まとめ関数*/
int PlayerChara::ShoulderGunSys( Batch_Preparat *BatPre, Camera *Cam, int ScreenPos[2]){

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

	//自分の向きを回転させます。
		//最初に回転の計算します

	if(( MyState == 0) || ( (MyState == 2) && ( AirOnPC == 0))){//通常・空中ダッシュモードでなければ、以下取得せず
				PC_Deg_XZ = PC_Deg_XZ + float(0.30*(sys->MousePos.x - (sys->BeforeMousePos.x - sys->rewin.left)));
				Tm_DegQ_Y = Tm_DegQ_Y - 0.0020* float( sys->MousePos.y - sys->BeforeMousePos.y + sys->rewin.top);
	}

	if( ( MyState == 3) || ( MyState == 4)){//よっこ飛びの時は
				Tm_DegQ_Y = Tm_DegQ_Y - 0.0020* float( sys->MousePos.y - sys->BeforeMousePos.y + sys->rewin.top);
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

	SetCursorPos( sys->rewin.left + 320, sys->rewin.top + 240);//マウス座標を真ん中へ
	GetCursorPos( &sys->BeforeMousePos);//マウス座標を格納します

	Cos_XZ = cos(4.8);//XZ座標コサインの取得
	Sin_XZ = sin(4.8);//XZ座標サインの取得
	Sin_Y = sin(Tm_DegQ_Y);//Y座標サインの取得
	Cos_Y = cos(Tm_DegQ_Y);//Y座標のコサインの取得
	TurnPos.x = float(Cos_XZ * Cos_Y * 2000);//向くべき方向のX座標
	TurnPos.y = float(Sin_Y * 2000);//向くべき方向のY座標を取得
	TurnPos.z = float(Sin_XZ * Cos_Y * 2000);//向くべき方向のZ座標を取得


		//次に座標を取得したりしてモデルのボーンを操作します
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



  /*カメラの位置を設定します、位置は自分の肩の後ろに設置します*/

	/*キャラクターモデルの「首つけ根」の！今！の座標を取得します*/
	ech = E3DGetCurrentBonePos( cha_hsid[0], bone[2], 1, &StomachPos);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	//条件を基にカメラをセットします
	Cam->CamShoulderGunBack( Qid[3], PC_Deg_XZ, StomachPos);

	



	BatPre->SpriteData[0][2] = 320 - 16.0f;//カーソルのX座標
	BatPre->SpriteData[0][3] = 220 - 18.0f;//カーソルのY座標

	ScreenPos[0] = 320;/**/ScreenPos[1] = 220;

	return 0;
}
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

	/*装備をしていないのなら*/
	if( Wp_equipment != -1){

			NowWpKind = Wep->GetWeaponData( Wp_equipment, 0);
			NowWpRange = float( Wep->GetWeaponData( Wp_equipment, 4) * 500);
			EneNearDistance = float(NowWpRange);
	}


	  /*壁の銃取得をどのようにするか指定します*/

	/*通常モード( モデル[0]から取得する )*/
	if( Stg->Stage_GunTarget == 0){
			ech = E3DPickFace( sys->scid1, Stg->Stage_hsid[0], ScreenPos, NowWpRange, &Wall_HitResult, &HitResult, &Wall_GunTargetPos, &Wall_ReflectVec, &Wall_HitDistance);
			if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
			};
	}


	if(Wp_equipment != -1){//装備をきちんとつけていれば
		/*武器の種類が、ハンドガンであれば*/
		if((NowWpKind == 1) || (NowWpKind == 4)){
			
				/*敵5にあたっていないかチェックします*/
				for( int i = 0; i < 15; i++){//エネミーの数だけ
						if( Ene->Enemy_hsid[i] != 0){
									ech = E3DPickFace( sys->scid1, Ene->Enemy_hsid[i], ScreenPos, NowWpRange, &EneHitResult, &EneHitResult, &GarbageD3DVec, &GarbageD3DVec, &EneDistance);
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
						ech = E3DPickFace( sys->scid1, Ene->Enemy_hsid[NearEnemyID], ScreenPos, NowWpRange, &EneHitResult, &EneHitResult, &GunTargetPos, &ReflectVec, &EneDistance);
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
	}




	return 0;
}
/*キャラクターの後処理を行う関数、モーションや姿勢など*/
int PlayerChara::ShoulderGunSysBefore( Weapon *Wep){

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
						if( Wep->GetWeaponData( Wp_equipment, 0) == 1){//ハンドガンを撃つのなら
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
							if( Wep->GetWeaponData( Wp_equipment, 0) == 4){//アサルトを撃つのなら
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
							if( Wep->GetWeaponData( Wp_equipment, 0) == 1){//ハンドガンを撃つのなら
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
							if( Wep->GetWeaponData( Wp_equipment, 0) == 4){//アサルトを撃つのなら
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
					ech = E3DSetMOAEventNoML( cha_hsid[0], 27, MotionList, NoMotionList);
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
/*普通のゲーム内での処理を行う関数、銃器の出し入れ、敵へのあたり、銃を手に置くなど…etc*/
int PlayerChara::NormallyPCSystem( Stage *Stg, Batch_Preparat *BatPre, Enemy *Ene, Camera *Cam, Weapon *Wep){

	/*変数の初期化*/
	int ech = 0;
	int MotionID = 0;//モーションIDを入れます
	int Garbage = 0;//ゴミデータを入れます
	int MotionFrameNo = 0;//モーションのフレーム番号を入れます
	int ScreenPos[2] = { 0, 0};//スクリーン座標配列を初期化
	int keyin[20];//キー情報配列を作成 

	/*キーを取得する*/
	sys->GetKeyData(keyin);

	/*キャラクターを動かす*/
	MoveChara();

	/*キャラクターを地面に置く*/
	MovePosOnGround( Stg);

	/*視点関連の処理、切り替えや関数呼び出し等*/
	ShoulderGunSys( BatPre, Cam, ScreenPos);//肩撃ち視点

	//体の向きや、射撃を行う関数を呼び出し
	GunConflictTarget( ScreenPos, Stg, Ene, Wep);

	/*敵への当たり判定の処理*/


	/*装備武器変更の処理*/
	if( sys->MouseWhole == 1){//もし、マウスホイールが上へ行ったのなら
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

	if( sys->MouseWhole == 2){//もし、マウスホイールが下へ行ったのなら
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
	if( ( sys->keyinQuick[1] == 1) && ( Attitude == 0) && ( MyState == 0) && ( AirOnPC == 0)){//キーが連続で押され、しゃがみ状態でなく、他の動作を行ってなくて、地上なら
				MyState = 2;//ダッシュをする
	}

	if(( sys->keyinQuick[1] == 1) && (( Attitude != 0) || (( MyState != 0) && ( MyState != 2) ))){//それ以外の条件では、ダッシュキャンセルする
				sys->KeyQuickPush[1][2] = 0;//ダッシュキーが押されてない状態にする
				sys->keyinQuick[1] = 0;//ゲームダッシュフラグをオフにする
	}


	if( ( MyState == 2) && ( sys->keyinQuick[1] == 0) && ( AirOnPC == 0) ){//ダッシュ操作中で、キーが解除されたら
				MyState = 0;//ダッシュを解除する
	}

	if( MyState == 2){//ダッシュ中なら
				Stamina = Stamina - 1;//スタミナを減らす
				if( (Stamina < 1) && (AirOnPC == 0) ){//体力がなくなった&空中でないなら
						MyState = 0;//ダッシュを止める
						sys->KeyQuickPush[1][2] = 0;//ダッシュキーが押されてない状態にする
						sys->keyinQuick[1] = 0;//ゲームダッシュフラグをオフにする
				}
	}

	/*横っ飛び関係の処理を行います*/
	if( ( ( sys->keyinQuick[0] == 1) || ( sys->keyinQuick[2] == 1)) && ( Attitude == 0) //左右キーが連続で押され、しゃがみ状態でなく、
		&& ( MyState == 0) && ( AirOnPC == 0) && ( 0 < Stamina)){//他の動作を行ってなくて、地上で、スタミナがなくなってないなら

				if( sys->keyinQuick[0] == 1) MyState = 3;//左横っ飛び状態にする;
				if( sys->keyinQuick[2] == 1) MyState = 4;//右横っ飛び状態にする;
				if(( sys->keyinQuick[0] == 1) && ( sys->keyinQuick[2] == 1)) MyState = 0;//通常状態にする
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
							sys->KeyQuickPush[0][2] = 0;//ダッシュキーが押されてない状態にする
							sys->KeyQuickPush[2][2] = 0;//ダッシュキーが押されてない状態にする
							sys->keyinQuick[0] = 0;//横っ飛びフラグをオフにする
							sys->keyinQuick[2] = 0;//横っ飛びフラグをオフにする
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