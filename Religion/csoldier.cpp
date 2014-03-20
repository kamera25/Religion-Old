/* ここでは、兵士クラス関係の関数を定義するクラスコードファイルです。
// 兵士の基本的な動作に関係する時に必要な関数が多く書かれています。
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "cstage.h"//ステージ関係のクラスヘッダファイル
#include "csoldier.h"// 兵士クラスの宣言ヘッダファイル


/* 兵士系ユニットをグラウンドの上に置くための関数 */
int Soldier::MovePosOnGround( Stage *Stg){

	/*変数の初期化*/
	int ech = 0;//エラーチェック
	int GroundResult = 0;//地面の当たり判定の結果
	int MoveStopFlg = 0;//空中に浮かんでいるときに移動できないようにするためのフラグ
	D3DXVECTOR3 ReflectVec( 0.0, 0.0, 0.0);//地面の反射ベクトルの構造体
	D3DXVECTOR3 GroundOnPos( 0.0, 0.0, 0.0);//自キャラを地面に垂直におろした場合の座標
	D3DXVECTOR3 MyPos( 0.0, 0.0, 0.0);//自分のキャラクター座標


	/**/
	//ステージグラウンドごとにどのような処理にさせるか振り分けます
	/**/

	if( Stg->Stage_GndMode == 0){

			/*地面とPCの当たり判定のチェック*/
			ech = E3DChkConfGround( Get_BodyModel(), Stg->Stage_hsid[0], 1, 500, -1000, &GroundResult, &GroundOnPos, &ReflectVec);
			_ASSERT( ech != 1 );//エラーチェック

			ech = E3DGetPos( Get_BodyModel(), &MyPos);
			_ASSERT( ech != 1 );//エラーチェック

			/*もし地面の高さがかなり離れているか、横っ飛び状態なら*/
			if( (400 < MyPos.y - GroundOnPos.y) || ( Get_MyState() == 3) || ( Get_MyState() == 4) ){

						/*加速度を追加する*/
						Set_Acceleration( Get_Acceleration() - 8.0);

						/*前回はとんでなかった場合*/
						if( BeforeAirOnPC == 0){
									/*ダッシュ中の場合*/
									if( ( Get_MyState() == 2) && ( BeforeAirOnPC == 0)) {
												Set_Acceleration(100);//空中でジャンプしたことにする
									}
									/*横っ飛び状態なら*/
									if( (Get_MyState() == 3) || ( Get_MyState() == 4)) {
												Set_Acceleration(70);//空中でジャンプしたことにする
									}
						}

						/*加速度に制限をかける*/
						if(  Get_Acceleration() <= -700 ){
									Set_Acceleration(-700);
						}

						/*自分の座標を下げる*/
						MyPos.y = MyPos.y + float(Get_Acceleration());

						/*キャラクターを空中に置く*/
						ech = E3DSetPos( Get_BodyModel(), MyPos);
						_ASSERT( ech != 1 );//エラーチェック

						/*移動可能フラグをオフにする*/
						MoveStopFlg = 1;

						/*モーションを「ジャンプ中」にする*/
						Set_UnderMotion(9);

						/*空中フラグをオンにする*/
						Set_AirOnPC(1);

			}
			else{
						/*キャラクターを地面上に置く*/
						ech = E3DSetPos( Get_BodyModel(), GroundOnPos);
						_ASSERT( ech != 1 );//エラーチェック

						/*加速度を0にする*/
						Set_Acceleration( 0.0);

						/*移動可能フラグをオフにする*/
						MoveStopFlg = 0;

						/*空中フラグをオフにする*/
						Set_AirOnPC(0);
			}
	}


	/*今回のキャラクターが空中にいるか代入します(次ループ時使用)*/
	BeforeAirOnPC = Get_AirOnPC();


	return 0;
}
/*銃の現在持ってる銃を持つためのモーション・システムを管轄する関数*/
int Soldier::GunPutOnHand(){

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

	if(NowWpKind == 0){//武器の種類が、ハンドガンであれば



				/*銃の置くボーンの座標を求めます*/
				ech = E3DGetCurrentBonePos( Get_BodyModel(), Get_Bone_ID(0), 1, &GunOnPos);
				_ASSERT( ech != 1 );//エラーチェック

				/*銃を求めた座標におきます*/
				ech = E3DSetPos( NowGunhsid, GunOnPos);
				_ASSERT( ech != 1 );//エラーチェック

				/*銃の向きになるボーンのクォータニオンを取得*/
				ech = E3DGetCurrentBoneQ( Get_BodyModel(), Get_Bone_ID(1), 2, Get_Quaternion(0));//手先の向きを取得
				_ASSERT( ech != 1 );//エラーチェック

				/*向きたい方向への計算を行います*/
				ech = E3DLookAtQ( Get_Quaternion(0), MoveVec, BaseVec, 0, 0);
				_ASSERT( ech != 1 );//エラーチェック

				/*銃の向きをセットします*/
				ech = E3DSetDirQ2( NowGunhsid, Get_Quaternion(0));
				_ASSERT( ech != 1 );//エラーチェック



	}
	if(NowWpKind == 2){//武器の種類が、ショットガンであれば

				/*銃の置くボーンの座標を求めます*/
				ech = E3DGetCurrentBonePos( Get_BodyModel(), Get_Bone_ID(0), 1, &GunOnPos);
				_ASSERT( ech != 1 );//エラーチェック

				/*銃を求めた座標におきます*/
				ech = E3DSetPos( NowGunhsid, GunOnPos);
				_ASSERT( ech != 1 );//エラーチェック

				/*銃の向きになるボーンのクォータニオンを取得*/
				ech = E3DGetCurrentBoneQ( Get_BodyModel(), Get_Bone_ID(1), 2, Get_Quaternion(0));//手先の向きを取得
				_ASSERT( ech != 1 );//エラーチェック

				/*向きたい方向への計算を行います*/
				ech = E3DLookAtQ( Get_Quaternion(0), MoveVec, BaseVec, 0, 0);
				_ASSERT( ech != 1 );//エラーチェック

				/*銃の向きをセットします*/
				ech = E3DSetDirQ2( NowGunhsid, Get_Quaternion(0));
				_ASSERT( ech != 1 );//エラーチェック

	}
	if(NowWpKind == 3){//武器の種類が、アサルトライフルであれば

				/*銃の置くボーンの座標を求めます*/
				ech = E3DGetCurrentBonePos( Get_BodyModel(), Get_Bone_ID(0), 1, &GunOnPos);
				_ASSERT( ech != 1 );//エラーチェック

				/*銃を求めた座標におきます*/
				ech = E3DSetPos( NowGunhsid, GunOnPos);
				_ASSERT( ech != 1 );//エラーチェック

				/*銃の向きになるボーンのクォータニオンを取得*/
				ech = E3DGetCurrentBoneQ( Get_BodyModel(), Get_Bone_ID(1), 2, Get_Quaternion(0));//手先の向きを取得
				_ASSERT( ech != 1 );//エラーチェック

				/*向きたい方向への計算を行います*/
				ech = E3DLookAtQ( Get_Quaternion(0), MoveVec, BaseVec, 0, 0);
				_ASSERT( ech != 1 );//エラーチェック

				/*銃の向きをセットします*/
				ech = E3DSetDirQ2( NowGunhsid, Get_Quaternion(0));
				_ASSERT( ech != 1 );//エラーチェック

	}
	if(NowWpKind == 4){//武器の種類が、マシンガンであれば

				/*銃の置くボーンの座標を求めます*/
				ech = E3DGetCurrentBonePos( Get_BodyModel(), Get_Bone_ID(0), 1, &GunOnPos);
				_ASSERT( ech != 1 );//エラーチェック

				/*銃を求めた座標におきます*/
				ech = E3DSetPos( NowGunhsid, GunOnPos);
				_ASSERT( ech != 1 );//エラーチェック

				/*銃の向きになるボーンのクォータニオンを取得*/
				ech = E3DGetCurrentBoneQ( Get_BodyModel(), Get_Bone_ID(1), 2, Get_Quaternion(0));//手先の向きを取得
				_ASSERT( ech != 1 );//エラーチェック

				/*向きたい方向への計算を行います*/
				ech = E3DLookAtQ( Get_Quaternion(0), MoveVec, BaseVec, 0, 0);
				_ASSERT( ech != 1 );//エラーチェック

				/*銃の向きをセットします*/
				ech = E3DSetDirQ2( NowGunhsid, Get_Quaternion(0));
				_ASSERT( ech != 1 );//エラーチェック

	}
	if(NowWpKind == 5){//武器の種類が、アサルトライフルであれば

				/*銃の置くボーンの座標を求めます*/
				ech = E3DGetCurrentBonePos( Get_BodyModel(), Get_Bone_ID(0), 1, &GunOnPos);
				_ASSERT( ech != 1 );//エラーチェック

				/*銃を求めた座標におきます*/
				ech = E3DSetPos( NowGunhsid, GunOnPos);
				_ASSERT( ech != 1 );//エラーチェック

				/*銃の向きになるボーンのクォータニオンを取得*/
				ech = E3DGetCurrentBoneQ( Get_BodyModel(), Get_Bone_ID(1), 2, Get_Quaternion(0));//手先の向きを取得
				_ASSERT( ech != 1 );//エラーチェック

				/*向きたい方向への計算を行います*/
				ech = E3DLookAtQ( Get_Quaternion(0), MoveVec, BaseVec, 0, 0);
				_ASSERT( ech != 1 );//エラーチェック

				/*銃の向きをセットします*/
				ech = E3DSetDirQ2( NowGunhsid, Get_Quaternion(0));
				_ASSERT( ech != 1 );//エラーチェック

	}

		ech = E3DSetNewPoseML( NowGunhsid);
		_ASSERT( ech != 1 );//エラーチェック




	return 0;
}
/*人間のモーションや姿勢などを設定します*/
int Soldier::Batch_PeopleMotion(){

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

	if( Get_MyState() == 0){
			/**/
			/*上半身のモーション設定*/

			if( Get_Attitude() == 0){//しゃがみモードがオフなら
					if( Wp_equipment != -1){//武器を装備している状態なら
						if( Wpn.GetWeaponData( Wp_equipment, 0) == 1){//ハンドガンを撃つのなら
										if( Get_UpMotion() == 0){//普通の構え

												/*モーションで動かす部分の指定*/
												MotionList[0] = Get_Bone_ID(5);//「おなか」のボーンを指定
												MotionList[1] = 0;//指定終了
							
												/*モーションで動かさない部分の指定*/
												NoMotionList[0] = 0;//指定終了

												/*モーションを設定する*/
												ech = E3DSetMOAEventNoML( Get_BodyModel(), 4, MotionList, NoMotionList);//ハンドガン構え
												
														_ASSERT( ech != 1 );//エラーチェック
										}
							}
							if( Wpn.GetWeaponData( Wp_equipment, 0) == 3){//ショットガンを撃つのなら
										if( Get_UpMotion() == 0){//普通の構え
					
												/*モーションで動かす部分の指定*/
												MotionList[0] = Get_Bone_ID(5);//「おなか」のボーンを指定
												MotionList[1] = 0;//指定終了
							
												/*モーションで動かさない部分の指定*/
												NoMotionList[0] = 0;//指定終了

												/*モーションを設定する*/
												ech = E3DSetMOAEventNoML( Get_BodyModel(), 3, MotionList, NoMotionList);//アサルト構え
												
														_ASSERT( ech != 1 );//エラーチェック
										}
							}
							if( Wpn.GetWeaponData( Wp_equipment, 0) == 4){//アサルトを撃つのなら
										if( Get_UpMotion() == 0){//普通の構え
					
												/*モーションで動かす部分の指定*/
												MotionList[0] = Get_Bone_ID(5);//「おなか」のボーンを指定
												MotionList[1] = 0;//指定終了
							
												/*モーションで動かさない部分の指定*/
												NoMotionList[0] = 0;//指定終了

												/*モーションを設定する*/
												ech = E3DSetMOAEventNoML( Get_BodyModel(), 3, MotionList, NoMotionList);//アサルト構え
												
														_ASSERT( ech != 1 );//エラーチェック
										}
							}
							if( Wpn.GetWeaponData( Wp_equipment, 0) == 5){//マシンガンを撃つのなら
										if( Get_UpMotion() == 0){//普通の構え
					
												/*モーションで動かす部分の指定*/
												MotionList[0] = Get_Bone_ID(5);//「おなか」のボーンを指定
												MotionList[1] = 0;//指定終了
							
												/*モーションで動かさない部分の指定*/
												NoMotionList[0] = 0;//指定終了

												/*モーションを設定する*/
												ech = E3DSetMOAEventNoML( Get_BodyModel(), 3, MotionList, NoMotionList);//アサルト構え
												
														_ASSERT( ech != 1 );//エラーチェック
										}
							}
							if( Wpn.GetWeaponData( Wp_equipment, 0) == 6){//ライフルを撃つのなら
										if( Get_UpMotion() == 0){//普通の構え
					
												/*モーションで動かす部分の指定*/
												MotionList[0] = Get_Bone_ID(5);//「おなか」のボーンを指定
												MotionList[1] = 0;//指定終了
							
												/*モーションで動かさない部分の指定*/
												NoMotionList[0] = 0;//指定終了

												/*モーションを設定する*/
												ech = E3DSetMOAEventNoML( Get_BodyModel(), 3, MotionList, NoMotionList);//アサルト構え
												
														_ASSERT( ech != 1 );//エラーチェック
										}
							}
					}
					else{//武器を装備していない状態なら
							/*モーションで動かす部分の指定*/
												/*モーションで動かす部分の指定*/
												MotionList[0] = Get_Bone_ID(5);//「おなか」のボーンを指定
												MotionList[1] = 0;//指定終了
							
												/*モーションで動かさない部分の指定*/
												NoMotionList[0] = 0;//指定終了

												/*モーションを設定する*/
												ech = E3DSetMOAEventNoML( Get_BodyModel(), 3, MotionList, NoMotionList);//ハンドガン構え
												
														_ASSERT( ech != 1 );//エラーチェック
					}
			}

			/**/
			if( Get_Attitude() == 1){//しゃがみモードがオンなら
					if( Wp_equipment != -1){//武器を装備している状態なら
							if( Wpn.GetWeaponData( Wp_equipment, 0) == 1){//ハンドガンを撃つのなら
										if( Get_UpMotion() == 0){//普通の構え

												/*モーションで動かす部分の指定*/
												MotionList[0] = Get_Bone_ID(5);//「おなか」のボーンを指定
												MotionList[1] = 0;//指定終了
							
												/*モーションで動かさない部分の指定*/
												NoMotionList[0] = 0;//指定終了

												/*モーションを設定する*/
												ech = E3DSetMOAEventNoML( Get_BodyModel(), 4, MotionList, NoMotionList);//ハンドガン構え
												
														_ASSERT( ech != 1 );//エラーチェック
										}
							}
							if( Wpn.GetWeaponData( Wp_equipment, 0) == 4){//アサルトを撃つのなら
										if( Get_UpMotion() == 0){//普通の構え
					
												/*モーションで動かす部分の指定*/
												MotionList[0] = Get_Bone_ID(5);//「おなか」のボーンを指定
												MotionList[1] = 0;//指定終了
							
												/*モーションで動かさない部分の指定*/
												NoMotionList[0] = 0;//指定終了

												/*モーションを設定する*/
												ech = E3DSetMOAEventNoML( Get_BodyModel(), 3, MotionList, NoMotionList);//ハンドガン構え
												
														_ASSERT( ech != 1 );//エラーチェック
										}
							}
					}
					else{//武器を装備していない状態なら
							/*モーションで動かす部分の指定*/
												/*モーションで動かす部分の指定*/
												MotionList[0] = Get_Bone_ID(5);//「おなか」のボーンを指定
												MotionList[1] = 0;//指定終了
							
												/*モーションで動かさない部分の指定*/
												NoMotionList[0] = 0;//指定終了

												/*モーションを設定する*/
												ech = E3DSetMOAEventNoML( Get_BodyModel(), 3, MotionList, NoMotionList);//ハンドガン構え
												
														_ASSERT( ech != 1 );//エラーチェック
					}
			}


			

			/*配列変数の初期化*/
			for( int i=0; i<10; i++){
					MotionList[i] = 0;//動かす部分を指定する配列を初期化
					NoMotionList[i] = 0;//動かさない部分を指定する配列を初期化
			}

			/**/
			/*下半身のモーション設定*/
			if( Get_Attitude() == 0){//しゃがみモードがオフなら
					if( Get_UnderMotion() == 0){//止まるのなら

								/*モーションで動かす部分の指定*/
								MotionList[0] = Get_Bone_ID(6);//「移動先」のボーンを指定
								MotionList[1] = 0;//指定終了

								/*モーションで動かさない部分の指定*/
								NoMotionList[0] = Get_Bone_ID(5);//「おなか」ボーンを指定
								NoMotionList[1] = 0;//指定終了

								/*モーションを設定する*/
								ech = E3DSetMOAEventNoML( Get_BodyModel(), 2, MotionList, NoMotionList);
								
										_ASSERT( ech != 1 );//エラーチェック
					}
					if( Get_UnderMotion() == 1){//前進するのなら

								/*モーションで動かす部分の指定*/
								MotionList[0] = Get_Bone_ID(6);//「移動先」のボーンを指定
								MotionList[1] = 0;//指定終了

								/*モーションで動かさない部分の指定*/
								NoMotionList[0] = Get_Bone_ID(5);//「おなか」ボーンを指定
								NoMotionList[1] = 0;//指定終了

								/*モーションを設定する*/
								ech = E3DSetMOAEventNoML( Get_BodyModel(), 1, MotionList, NoMotionList);
								
										_ASSERT( ech != 1 );//エラーチェック
					}
					if( Get_UnderMotion() == 2){//右進するのなら

								/*モーションで動かす部分の指定*/
								MotionList[0] = Get_Bone_ID(6);//「移動先」のボーンを指定
								MotionList[1] = 0;//指定終了

								/*モーションで動かさない部分の指定*/
								NoMotionList[0] = Get_Bone_ID(5);//「おなか」ボーンを指定
								NoMotionList[1] = 0;//指定終了

								/*モーションを設定する*/
								ech = E3DSetMOAEventNoML( Get_BodyModel(), 5, MotionList, NoMotionList);
								
										_ASSERT( ech != 1 );//エラーチェック
					}
					if( Get_UnderMotion() == 3){//左進するのなら

								/*モーションで動かす部分の指定*/
								MotionList[0] = Get_Bone_ID(6);//「移動先」のボーンを指定
								MotionList[1] = 0;//指定終了

								/*モーションで動かさない部分の指定*/
								NoMotionList[0] = Get_Bone_ID(5);//「おなか」ボーンを指定
								NoMotionList[1] = 0;//指定終了

								/*モーションを設定する*/
								ech = E3DSetMOAEventNoML( Get_BodyModel(), 6, MotionList, NoMotionList);
								
										_ASSERT( ech != 1 );//エラーチェック
					}
					if( Get_UnderMotion() == 4){//左前進するのなら

								/*モーションで動かす部分の指定*/
								MotionList[0] = Get_Bone_ID(6);//「移動先」のボーンを指定
								MotionList[1] = 0;//指定終了

								/*モーションで動かさない部分の指定*/
								NoMotionList[0] = Get_Bone_ID(5);//「おなか」ボーンを指定
								NoMotionList[1] = 0;//指定終了

								/*モーションを設定する*/
								ech = E3DSetMOAEventNoML( Get_BodyModel(), 7, MotionList, NoMotionList);
								
										_ASSERT( ech != 1 );//エラーチェック
					}
					if( Get_UnderMotion() == 5){//右前進するのなら

								/*モーションで動かす部分の指定*/
								MotionList[0] = Get_Bone_ID(6);//「移動先」のボーンを指定
								MotionList[1] = 0;//指定終了

								/*モーションで動かさない部分の指定*/
								NoMotionList[0] = Get_Bone_ID(5);//「おなか」ボーンを指定
								NoMotionList[1] = 0;//指定終了

								/*モーションを設定する*/
								ech = E3DSetMOAEventNoML( Get_BodyModel(), 8, MotionList, NoMotionList);
								
										_ASSERT( ech != 1 );//エラーチェック
					}
					if( Get_UnderMotion() == 6){//左後進するのなら

								/*モーションで動かす部分の指定*/
								MotionList[0] = Get_Bone_ID(6);//「移動先」のボーンを指定
								MotionList[1] = 0;//指定終了

								/*モーションで動かさない部分の指定*/
								NoMotionList[0] = Get_Bone_ID(5);//「おなか」ボーンを指定
								NoMotionList[1] = 0;//指定終了

								/*モーションを設定する*/
								ech = E3DSetMOAEventNoML( Get_BodyModel(), 9, MotionList, NoMotionList);
								
										_ASSERT( ech != 1 );//エラーチェック
					}
					if( Get_UnderMotion() == 7){//右後進するのなら

								/*モーションで動かす部分の指定*/
								MotionList[0] = Get_Bone_ID(6);//「移動先」のボーンを指定
								MotionList[1] = 0;//指定終了

								/*モーションで動かさない部分の指定*/
								NoMotionList[0] = Get_Bone_ID(5);//「おなか」ボーンを指定
								NoMotionList[1] = 0;//指定終了

								/*モーションを設定する*/
								ech = E3DSetMOAEventNoML( Get_BodyModel(), 10, MotionList, NoMotionList);
								
										_ASSERT( ech != 1 );//エラーチェック
					}
					if( Get_UnderMotion() == 8){//後進するのなら

								/*モーションで動かす部分の指定*/
								MotionList[0] = Get_Bone_ID(6);//「移動先」のボーンを指定
								MotionList[1] = 0;//指定終了

								/*モーションで動かさない部分の指定*/
								NoMotionList[0] = Get_Bone_ID(5);//「おなか」ボーンを指定
								NoMotionList[1] = 0;//指定終了

								/*モーションを設定する*/
								ech = E3DSetMOAEventNoML( Get_BodyModel(), 11, MotionList, NoMotionList);
								
										_ASSERT( ech != 1 );//エラーチェック
					}
					if( Get_UnderMotion() == 9){//ジャンプにするのなら

								/*モーションで動かす部分の指定*/
								MotionList[0] = Get_Bone_ID(6);//「移動先」のボーンを指定
								MotionList[1] = 0;//指定終了

								/*モーションで動かさない部分の指定*/
								NoMotionList[0] = Get_Bone_ID(5);//「おなか」ボーンを指定
								NoMotionList[1] = 0;//指定終了

								/*モーションを設定する*/
								ech = E3DSetMOAEventNoML( Get_BodyModel(), 24, MotionList, NoMotionList);
								
										_ASSERT( ech != 1 );//エラーチェック
					}
			}

			/**/
			if( Get_Attitude() == 1){//しゃがみモードがオンなら
					if( Get_UnderMotion() == 0){//止まるのなら

								/*モーションで動かす部分の指定*/
								MotionList[0] = Get_Bone_ID(6);//「移動先」のボーンを指定
								MotionList[1] = 0;//指定終了

								/*モーションで動かさない部分の指定*/
								NoMotionList[0] = Get_Bone_ID(5);//「おなか」ボーンを指定
								NoMotionList[1] = 0;//指定終了

								/*モーションを設定する*/
								ech = E3DSetMOAEventNoML( Get_BodyModel(), 13, MotionList, NoMotionList);
								
										_ASSERT( ech != 1 );//エラーチェック
					}
					if( Get_UnderMotion() == 1){//前進するのなら

								/*モーションで動かす部分の指定*/
								MotionList[0] = Get_Bone_ID(6);//「移動先」のボーンを指定
								MotionList[1] = 0;//指定終了

								/*モーションで動かさない部分の指定*/
								NoMotionList[0] = Get_Bone_ID(5);//「おなか」ボーンを指定
								NoMotionList[1] = 0;//指定終了

								/*モーションを設定する*/
								ech = E3DSetMOAEventNoML( Get_BodyModel(), 14, MotionList, NoMotionList);
								
										_ASSERT( ech != 1 );//エラーチェック
					}
					if( Get_UnderMotion() == 2){//右進するのなら

								/*モーションで動かす部分の指定*/
								MotionList[0] = Get_Bone_ID(6);//「移動先」のボーンを指定
								MotionList[1] = 0;//指定終了

								/*モーションで動かさない部分の指定*/
								NoMotionList[0] = Get_Bone_ID(5);//「おなか」ボーンを指定
								NoMotionList[1] = 0;//指定終了

								/*モーションを設定する*/
								ech = E3DSetMOAEventNoML( Get_BodyModel(), 16, MotionList, NoMotionList);
								
										_ASSERT( ech != 1 );//エラーチェック
					}
					if( Get_UnderMotion() == 3){//左進するのなら

								/*モーションで動かす部分の指定*/
								MotionList[0] = Get_Bone_ID(6);//「移動先」のボーンを指定
								MotionList[1] = 0;//指定終了

								/*モーションで動かさない部分の指定*/
								NoMotionList[0] = Get_Bone_ID(5);//「おなか」ボーンを指定
								NoMotionList[1] = 0;//指定終了

								/*モーションを設定する*/
								ech = E3DSetMOAEventNoML( Get_BodyModel(), 17, MotionList, NoMotionList);
								
										_ASSERT( ech != 1 );//エラーチェック
					}
					if( Get_UnderMotion() == 4){//左前進するのなら

								/*モーションで動かす部分の指定*/
								MotionList[0] = Get_Bone_ID(6);//「移動先」のボーンを指定
								MotionList[1] = 0;//指定終了

								/*モーションで動かさない部分の指定*/
								NoMotionList[0] = Get_Bone_ID(5);//「おなか」ボーンを指定
								NoMotionList[1] = 0;//指定終了

								/*モーションを設定する*/
								ech = E3DSetMOAEventNoML( Get_BodyModel(), 19, MotionList, NoMotionList);
								
										_ASSERT( ech != 1 );//エラーチェック
					}
					if( Get_UnderMotion() == 5){//右前進するのなら

								/*モーションで動かす部分の指定*/
								MotionList[0] = Get_Bone_ID(6);//「移動先」のボーンを指定
								MotionList[1] = 0;//指定終了

								/*モーションで動かさない部分の指定*/
								NoMotionList[0] = Get_Bone_ID(5);//「おなか」ボーンを指定
								NoMotionList[1] = 0;//指定終了

								/*モーションを設定する*/
								ech = E3DSetMOAEventNoML( Get_BodyModel(), 18, MotionList, NoMotionList);
								
										_ASSERT( ech != 1 );//エラーチェック
					}
					if( Get_UnderMotion() == 6){//左後進するのなら

								/*モーションで動かす部分の指定*/
								MotionList[0] = Get_Bone_ID(6);//「移動先」のボーンを指定
								MotionList[1] = 0;//指定終了

								/*モーションで動かさない部分の指定*/
								NoMotionList[0] = Get_Bone_ID(5);//「おなか」ボーンを指定
								NoMotionList[1] = 0;//指定終了

								/*モーションを設定する*/
								ech = E3DSetMOAEventNoML( Get_BodyModel(), 21, MotionList, NoMotionList);
								
										_ASSERT( ech != 1 );//エラーチェック
					}
					if( Get_UnderMotion() == 7){//右後進するのなら

								/*モーションで動かす部分の指定*/
								MotionList[0] = Get_Bone_ID(6);//「移動先」のボーンを指定
								MotionList[1] = 0;//指定終了

								/*モーションで動かさない部分の指定*/
								NoMotionList[0] = Get_Bone_ID(5);//「おなか」ボーンを指定
								NoMotionList[1] = 0;//指定終了

								/*モーションを設定する*/
								ech = E3DSetMOAEventNoML( Get_BodyModel(), 20, MotionList, NoMotionList);
								
										_ASSERT( ech != 1 );//エラーチェック
					}
					if( Get_UnderMotion() == 8){//後進するのなら

								/*モーションで動かす部分の指定*/
								MotionList[0] = Get_Bone_ID(6);//「移動先」のボーンを指定
								MotionList[1] = 0;//指定終了

								/*モーションで動かさない部分の指定*/
								NoMotionList[0] = Get_Bone_ID(5);//「おなか」ボーンを指定
								NoMotionList[1] = 0;//指定終了

								/*モーションを設定する*/
								ech = E3DSetMOAEventNoML( Get_BodyModel(), 15, MotionList, NoMotionList);
								
										_ASSERT( ech != 1 );//エラーチェック
					}
					if( Get_UnderMotion() == 9){//ジャンプにするのなら

								/*モーションで動かす部分の指定*/
								MotionList[0] = Get_Bone_ID(6);//「移動先」のボーンを指定
								MotionList[1] = 0;//指定終了

								/*モーションで動かさない部分の指定*/
								NoMotionList[0] = Get_Bone_ID(5);//「おなか」ボーンを指定
								NoMotionList[1] = 0;//指定終了

								/*モーションを設定する*/
								ech = E3DSetMOAEventNoML( Get_BodyModel(), 26, MotionList, NoMotionList);
								
										_ASSERT( ech != 1 );//エラーチェック
					}
			}
	}
	if( Get_MyState() == 1){//キックフラグがオンなら
			/*モーションで動かす部分の指定*/
			MotionList[0] = Get_Bone_ID(6);//「移動先」のボーンを指定
			MotionList[1] = 0;//指定終了

			/*モーションで動かさない部分の指定*/
			NoMotionList[0] = Get_Bone_ID(5);//「おなか」ボーンを指定
			NoMotionList[1] = 0;//指定終了

			/*モーションを設定する*/
			ech = E3DSetMOAEventNoML( Get_BodyModel(), 22, MotionList, NoMotionList);
			
					_ASSERT( ech != 1 );//エラーチェック
	}
	if( Get_MyState() == 2){//ダッシュフラグがオンなら
			if( Get_AirOnPC() == 0){//ジャンプしていないなら
					/*モーションで動かす部分の指定*/
					MotionList[0] = Get_Bone_ID(6);//「移動先」のボーンを指定
					MotionList[1] = 0;//指定終了

					/*モーションで動かさない部分の指定*/
					NoMotionList[0] = Get_Bone_ID(5);//「おなか」ボーンを指定
					NoMotionList[1] = 0;//指定終了

					/*モーションを設定する*/
					ech = E3DSetMOAEventNoML( Get_BodyModel(), 23, MotionList, NoMotionList);
					
							_ASSERT( ech != 1 );//エラーチェック
			}
			if( Get_AirOnPC() == 1){//ジャンプしているのなら
					/*モーションで動かす部分の指定*/
					MotionList[0] = Get_Bone_ID(6);//「移動先」のボーンを指定
					MotionList[1] = 0;//指定終了

					/*モーションで動かさない部分の指定*/
					NoMotionList[0] = Get_Bone_ID(5);//「おなか」ボーンを指定
					NoMotionList[1] = 0;//指定終了

					/*モーションを設定する*/
					ech = E3DSetMOAEventNoML( Get_BodyModel(), 25, MotionList, NoMotionList);
					
							_ASSERT( ech != 1 );//エラーチェック
			}
	}
	if( Get_MyState() == 3){//左横っ飛び状態なら
					/*モーションで動かす部分の指定*/
					MotionList[0] = Get_Bone_ID(6);//「移動先」のボーンを指定
					MotionList[1] = 0;//指定終了

					/*モーションで動かさない部分の指定*/
					NoMotionList[0] = Get_Bone_ID(5);//「おなか」ボーンを指定
					NoMotionList[1] = 0;//指定終了

					/*モーションを設定する*/
					ech = E3DSetMOAEventNoML( Get_BodyModel(), 12, MotionList, NoMotionList);
					
							_ASSERT( ech != 1 );//エラーチェック
	}
	if( Get_MyState() == 4){//右横っ飛び状態なら
					/*モーションで動かす部分の指定*/
					MotionList[0] = Get_Bone_ID(6);//「移動先」のボーンを指定
					MotionList[1] = 0;//指定終了

					/*モーションで動かさない部分の指定*/
					NoMotionList[0] = Get_Bone_ID(5);//「おなか」ボーンを指定
					NoMotionList[1] = 0;//指定終了

					/*モーションを設定する*/
					ech = E3DSetMOAEventNoML( Get_BodyModel(), 12, MotionList, NoMotionList);
					
							_ASSERT( ech != 1 );//エラーチェック
	}
	if( Get_MyState() == 5){//死亡状態なら
					/*モーションで動かす部分の指定*/
					MotionList[0] = Get_Bone_ID(6);//「移動先」のボーンを指定
					MotionList[1] = 0;//指定終了

					/*モーションで動かさない部分の指定*/
					NoMotionList[0] = 0;//指定終了

					/*モーションを設定する*/
					ech = E3DSetMOAEventNoML( Get_BodyModel(), 30, MotionList, NoMotionList);
					
							_ASSERT( ech != 1 );//エラーチェック
	}



	/*マルチレイヤーに沿って新モーションを当てる*/
	ech = E3DSetNewPoseML( Get_BodyModel());
	
			_ASSERT( ech != 1 );//エラーチェック

	/*「首付け根」部分のモーションはどうか調べます*/
	ech = E3DGetMotionFrameNoML( Get_BodyModel(), Get_Bone_ID(2), &MotionID, &FrameNo);
	_ASSERT( ech != 1 );//エラーチェック

	/*計算したクォーターニオンを代入します*/
	ech = E3DSetBoneQ( Get_BodyModel(), Get_Bone_ID(2), MotionID, FrameNo, Get_Quaternion(3));
	_ASSERT( ech != 1 );//エラーチェック

	/*マルチレイヤーモーションの計算を行います*/
	ech = E3DCalcMLMotion( Get_BodyModel());
	_ASSERT( ech != 1 );//エラーチェック


	return 0;
}
/*コンストラクタ、兵士モデルのロード等を行ないます*/
Soldier::Soldier( const int selchara, const int Wpselect_equipment){

	//変数の初期化
	int ech = 0;
	int DummyModel = 0;
	int ModelID = 0;
	int Bone[10];
	int Qid[10];
	char loadname[256] = "";


	//クラスメンバ変数の初期化
	Set_PC_Deg_XZ(0.0f);// 自分の向き（XZ座標初期化）
	Set_PC_Deg_Y(0.0f);// 自分の向き（Y座標初期化）
	Set_UpMotion(0);// 上半身のモーションの初期化
	Set_UnderMotion(0);// 下半身のモーションの初期化
	Set_Attitude(0);// 自分の姿勢を「立ち」に指定
	Set_MyState(0);// 自分の動作状態を初期化
	Set_AirOnPC(0);// 自分の空中状態を通常にする
	Set_Acceleration(0.0);// 重力加速度を0にする
	Set_MoveSpeed(0.0);// 平面加速度を0にする
	BeforeAirOnPC = 0;
	Set_Skill( NULL);// スキルスロットのスキル格納変数をNULLポインターにしておく
	Set_EquipmentSkillSum( 0 );// 装備中スキルの合計を0にする

	//  兵種をノーマルにしておく
	Set_StateFromBranch(-1);

	// スキルを追加する
	Add_Skill(Creature::COMMANDO);
	
	Add_Skill(Creature::VAN_POUCH);


	//キャラクターモデルのロード

	if(selchara == 0){//アーティーモデル

			//アーティーモデルの取得
			wsprintf( loadname, "%s\\data\\3d\\model\\demo\\hito.sig", System::path);//アーティーモデルのsig名登録
			ech = E3DSigLoad( loadname, 0, 0, &ModelID);//モデルの読み込み、cha_hsidへモデルを入れる。
			if(ech != 0 ){//エラーチェック
					_ASSERT( ech != 1 );//エラーダイアログ
			};

			//ダミーモデルの取得
			wsprintf( loadname, "%s\\data\\3d\\model\\other\\demo.sig", System::path);//仮モデルのsig名登録
			ech = E3DSigLoad( loadname, 0, 1, &DummyModel);//モデルの読み込み、submodidへモデルを入れる。
			_ASSERT( ech != 1 );//エラーチェック

	}

	if(selchara == 1){//WF兵1モデル

			//WF兵1モデルの取得
			wsprintf( loadname, "%s\\data\\3d\\chara\\wf1\\model.sig", System::path);//アーティーモデルのsig名登録
			ech = E3DSigLoad( loadname, 0, 0.15f, &ModelID);//モデルの読み込み、cha_hsidへモデルを入れる。
			if(ech != 0 ){//エラーチェック
					_ASSERT( ech != 1 );//エラーダイアログ
			};

			//ダミーモデルの取得
			wsprintf( loadname, "%s\\data\\3d\\model\\other\\demo.sig", System::path);//仮モデルのsig名登録
			ech = E3DSigLoad( loadname, 0, 0.01f, &DummyModel);//モデルの読み込み、submodidへモデルを入れる。
			_ASSERT( ech != 1 );//エラーチェック

			//モーションデータ構え
			wsprintf( loadname, "%s\\data\\3d\\chara\\motion\\pc_motion.moa", System::path);//仮モデルのsig名登録
			ech = E3DLoadMOAFile( ModelID, loadname, 3, 1.0f); 
			_ASSERT( ech != 1 );//エラーチェック

			//ボーンネームからボーンIDの取得「銃もち手_X+」
			ech = E3DGetBoneNoByName( ModelID, "銃もち手_X+", &Bone[0]);
			_ASSERT( ech != 1 );//エラーチェック
			//ボーンネームからボーンIDの取得「銃もち手先_X+」
			ech = E3DGetBoneNoByName( ModelID, "銃もち手先_X+", &Bone[1]);
			_ASSERT( ech != 1 );//エラーチェック
			//ボーンネームからボーンIDの取得「首付け根」
			ech = E3DGetBoneNoByName( ModelID, "首付け根", &Bone[2]);
			_ASSERT( ech != 1 );//エラーチェック
			//ボーンネームからボーンIDの取得「足付け根_X+」
			ech = E3DGetBoneNoByName( ModelID, "足付け根_X+", &Bone[3]);
			_ASSERT( ech != 1 );//エラーチェック
			//ボーンネームからボーンIDの取得「足付け根_X-」
			ech = E3DGetBoneNoByName( ModelID, "足付け根_X-", &Bone[4]);
			_ASSERT( ech != 1 );//エラーチェック
			//ボーンネームからボーンIDの取得「おなか」
			ech = E3DGetBoneNoByName( ModelID, "おなか", &Bone[5]);
			_ASSERT( ech != 1 );//エラーチェック
			//ボーンネームからボーンIDの取得「移動先」
			ech = E3DGetBoneNoByName( ModelID, "移動先", &Bone[6]);
			_ASSERT( ech != 1 );//エラーチェック

			/*変数の代入*/
			Set_StateFromBranch(0);

			Set_HP( Get_MaxHP());//最大HPまで代入
			Set_Stamina( Get_MaxStamina() );//固定スタミナ
	}


	/**/
	//クォータニオンを作成します
	/**/	
	for(int i = 0; i<10; i++){
				ech = E3DCreateQ( &Qid[i]);
				_ASSERT( ech != 1 );//エラーチェック
				ech = E3DInitQ( Qid[i]);
				_ASSERT( ech != 1 );//エラーチェック
				Set_Quaternion( i, Qid[i]);
	}



	/*所持した武器の中で最初に何を持っているか設定します*/
	Set_Wp_equipment(Wpselect_equipment);
	
	/* ///////////////////////////// */
	// まとめて各メンバ変数に代入します
	/* ///////////////////////////// */

	Set_BodyModel( ModelID);// モデルIDの代入
	Set_DummyModel( DummyModel);// ダミーモデルIDの代入
	for( int i=0; i<7; i++){
			Set_Bone_ID( i, Bone[i]);
	}





	return;
}