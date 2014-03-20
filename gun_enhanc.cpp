//インクルードするファイル↓

#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <usercoef.h>//Easy3Dで必要な追加ヘッダ
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "resource1.h"//リソースファイルとかの関連付けヘッダ
#include <string.h>//文字列操作で必要
#include <math.h>//数学計算で使用
#include <stdlib.h>//乱数を作るためのヘッダ

#include "difine.h"


//グローバル変数の宣言



int Lunchergun(int subject, int Moveflg, int Gndflg){
//この関数は銃による敵への当たり判定、銃の移動を担う中心的な関数です。



	//以下、視点モードそれぞれの銃の移動

	//現時点での主観モードはどれか。!ダミーで主観にしています。!

	double handdeg_XZ;


	//主観モード時の銃の構え
	if(subject == 1){

					D3DXVECTOR3 ldpos1( 0.0, 0.0, 0.0);//座標取得Vecを格納
					D3DXVECTOR3 ldpos2;
					D3DXVECTOR3 ldpos3;
					D3DXVECTOR3 ldpos4( 0.0, 0.0, -1.0);
					D3DXVECTOR3 ldpos5;
					POINT pos;//マウスのデータ格納のポインター
					static double Tm_handdeg_XZ = 0;
					static double Tm_handdeg_Y = 0;
					
					double handdeg_Y = 0.0;

					double handcos_XZ = 0.0;
					double handsin_XZ = 0.0;
					double handcos_Y = 0.0;
					double handsin_Y = 0.0;

					double hdturnpos_X = 0.0;
					double hdturnpos_Y = 0.0;
					double hdturnpos_Z = 0.0;

					static int befMou_X = 0;
					static int befMou_Y = 0;
					int blur_X = 0;
					int blur_Y = 0;

					int ech = 0;

					ech = E3DGetPos( modelId[0], &ldpos5);//手の元座標を取得
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
								return 1;//問題ありで終了
					};
					ech = E3DSetPos(modelId[0], ldpos1);//基準点に移動セット
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
								return 1;//問題ありで終了
					};
					GetCursorPos( &pos );//マウス座標を格納

					Tm_handdeg_XZ = Tm_handdeg_XZ + 0.001*(befMou_X - pos.x);//X座標を前マウス-マウスから角度
					Tm_handdeg_Y = Tm_handdeg_Y - 0.001*(befMou_Y - pos.y);//Y座標を前マウス-マウス角度

					SetCursorPos( recwindow.left + 320, recwindow.top + 240);//マウスをウィンドウ真ん中に設置
					GetCursorPos( &pos );//マウス座標を格納
					befMou_X = pos.x;//前のマウス座標を取得
					befMou_Y = pos.y;//前のマウス座標を取得

					blur_X = rand()%2;//X軸のブレを乱数で決定
					blur_Y = rand()%2;//Y軸のぶれを乱数で決定
					if(blur_X == 0){
								blur_X = -1;//ブレが0なら、-の方向にぶれる。
					}
					if(blur_Y == 0){
								blur_Y = -1;//ブレが0なら、-の方向にぶれる。
					}


					if(Tm_handdeg_XZ>6.0){
											Tm_handdeg_XZ = Tm_handdeg_XZ - 6.0;
					}
					if(Tm_handdeg_XZ<0.0){
											Tm_handdeg_XZ = Tm_handdeg_XZ + 6.0;
					}
					if(Tm_handdeg_Y>0.8){
											Tm_handdeg_Y = 0.8;
					}
					if(Tm_handdeg_Y<-0.7){
											Tm_handdeg_Y = -0.7;
					}




					handdeg_XZ = Tm_handdeg_XZ;
					handdeg_Y = Tm_handdeg_Y;



					handcos_XZ = cos(handdeg_XZ);
					handsin_XZ = sin(handdeg_XZ);
					handcos_Y = cos(handdeg_Y);
					handsin_Y = sin(handdeg_Y);


					hdturnpos_X = handcos_XZ * handcos_Y * 2000;//向くべき方向のX座標
					hdturnpos_Y = handsin_Y * 2000;//向くべき方向のY座標を取得
					hdturnpos_Z = handsin_XZ * handcos_Y * 2000;//向くべき方向のZ座標を取得

					ech = E3DGetPos( modelId[0], &ldpos2);//手の座標を取得
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
								return 1;//問題ありで終了
					};

					ldpos3.x = ldpos2.x - hdturnpos_X;//X座標の向く方向のベクトルを取得
					ldpos3.y = ldpos2.y - hdturnpos_Y;//Y座標の向く方向のベクトルを取得
					ldpos3.z = ldpos2.z - hdturnpos_Z;//Z座標の向く方向のベクトルを取得

					//ブレがある状態の

					ech = E3DGetDirQ2( modelId[0], QId[0]);
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
								return 1;//問題ありで終了
					};
					ech = E3DLookAtQ( QId[0], ldpos3, ldpos4, 0, 10);
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
								return 1;//問題ありで終了
					};
					ech = E3DSetDirQ2( modelId[0], QId[0]);
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
								return 1;//問題ありで終了
					};

					
					ech = E3DSetPos( modelId[10], ldpos3);//手の元座標へ移動
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
								return 1;//問題ありで終了
					};



					ech = E3DSetPos( modelId[0], ldpos5);//手の元座標へ移動
					if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
								return 1;//問題ありで終了
					};



	}


	//以下、移動するためのモード作成

	if(Moveflg == 1){
					int ech = 0;
					int KeyMov = 0;
					int MovOn = 0;
					static int Speed = 0;
					double Mov_XZ = handdeg_XZ;
					double WantDeg = 0.0;
					double Movsin_XZ = 0.0;
					double Movcos_XZ = 0.0;
					double MovDeg_X = 0.0;
					double MovDeg_Z = 0.0;
					D3DXVECTOR3 ldpos1( 0.0, 0.0, -1.0);
					D3DXVECTOR3 ldpos2;
					D3DXVECTOR3 ldpos3( 0.0, 0.0, 0.0);

					//キーによる分岐
					if(keyin[0] == 1){//左
									KeyMov = KeyMov +1;
					}
					if(keyin[1] == 1){//上
									KeyMov = KeyMov +2;
					}
					if(keyin[2] == 1){//右
									KeyMov = KeyMov +4;
					}
					if(keyin[3] == 1){//下
									KeyMov = KeyMov +8;
					}

					//キーから取得した情報を変換
					if(KeyMov == 1){//左
									WantDeg = 1.5;
									MovOn = 1;
					}
					if(KeyMov == 3){//左上
									WantDeg = 0.75; 
									MovOn = 1;
					}
					if(KeyMov == 2){//上
									MovOn = 1;
					}
					if(KeyMov == 6){//右上
									WantDeg = -0.75; 
									MovOn = 1;
					}
					if(KeyMov == 4){//右
									WantDeg = -1.5;
									MovOn = 1;
					}
					if(KeyMov == 12){//右下
									WantDeg = -2.25; 
									MovOn = 1;
					}
					if(KeyMov == 8){//下
									WantDeg = -3.0;
									MovOn = 1;
					}
					if(KeyMov == 9){//左下
									WantDeg = 2.25; 
									MovOn = 1;
					}

					//移動速度の減少
					if(MovOn ==0 ){
							Speed = 0;
					}
					

					///動く方向を決めるよ
					if(MovOn == 1){

								Mov_XZ = Mov_XZ + WantDeg;//向きたい方向を設定
								if(Mov_XZ>6.0){
											Mov_XZ = Mov_XZ - 6.0;
								}
								if(Mov_XZ<0.0){
											Mov_XZ = Mov_XZ + 6.0;
								}

								Movcos_XZ = cos(Mov_XZ);//XZ上のコサインを求める
								Movsin_XZ = sin(Mov_XZ);//XZ上のサインを求める

								MovDeg_X = Movcos_XZ * 2000;//向くべき方向のX座標
								MovDeg_Z = Movsin_XZ * 2000;//向くべき方向のZ座標を取得

								ldpos3.x = 0.0 - MovDeg_X;//X座標のベクトルを求める
								ldpos3.z = 0.0 - MovDeg_Z;//Z座標のベクトルを求める

								//移動速度の設定
								Speed = Speed + 4;
								if(Speed >= 100){
										Speed = 100;
								}


								ech = E3DGetPos( modelId[0], &ldpos2);//手のモデルの座標を取得
								if(ech != 0 ){//エラーチェック
											_ASSERT( 0 );//エラーダイアログ
											return 1;//問題ありで終了
								};

								ech = E3DSetPos( modelId[10], ldpos2);//サブモデルの座標に設定
								if(ech != 0 ){//エラーチェック
											_ASSERT( 0 );//エラーダイアログ
											return 1;//問題ありで終了
								};

								ech = E3DLookAtQ( QId[4], ldpos3, ldpos1, 0, 0);//Qの向きを行きたい方向に設定
								if(ech != 0 ){//エラーチェック
											_ASSERT( 0 );//エラーダイアログ
											return 1;//問題ありで終了
								};

								ech = E3DSetDirQ2( modelId[10], QId[4]);//サブモデルにQをセット
								if(ech != 0 ){//エラーチェック
											_ASSERT( 0 );//エラーダイアログ
											return 1;//問題ありで終了
								};
								ech = E3DPosForward( modelId[10], Speed);//サブモデルを前進させる
								if(ech != 0 ){//エラーチェック
											_ASSERT( 0 );//エラーダイアログ
											return 1;//問題ありで終了
								};
								ech = E3DGetPos( modelId[10], &ldpos2);//サブモデルの座標を取得
								if(ech != 0 ){//エラーチェック
											_ASSERT( 0 );//エラーダイアログ
											return 1;//問題ありで終了
								};

								ech = E3DSetPos( modelId[0], ldpos2);//手のモデルをサブモデルの位置に設定
								if(ech != 0 ){//エラーチェック
											_ASSERT( 0 );//エラーダイアログ
											return 1;//問題ありで終了
								};

				}

	}


	//以下より、地面との当たり判定を設定します。

	

	if(Gndflg = 1){

			int ech = 0;
			int ChkGnd = 0; 
			D3DXVECTOR3 ldpos1( 0.0, 0.0, 0.0);
			D3DXVECTOR3 ldpos2( 0.0, 0.0, 0.0);


			ech = E3DGetPos( modelId[0], &ldpos1);//手の座標を取得
			if(ech != 0 ){//エラーチェック
						_ASSERT( 0 );//エラーダイアログ
						return 1;//問題ありで終了
			};

			ech = E3DSetPos( modelId[12], ldpos1);//手の座標にサブモデルを設置
			if(ech != 0 ){//エラーチェック
						_ASSERT( 0 );//エラーダイアログ
						return 1;//問題ありで終了
			};


			E3DChkConfGround( modelId[12], grd1, 1, 1500, 0, &ChkGnd, &ldpos1, &ldpos2);//地面とサブモデルの座標チェック
			if(ech != 0 ){//エラーチェック
						_ASSERT( 0 );//エラーダイアログ
						return 1;//問題ありで終了
			};

			if(ChkGnd != 0){
						ldpos1.y = ldpos1.y +1000;//座標をキャラと同じくらいにする。
						ech = E3DSetPos( modelId[0], ldpos1);
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
									return 1;//問題ありで終了
						};
			}
	}


	



	//下記より、銃の操作方法を設定

	int usewpkind = Iinfo[(Iinfo[3][3])][0];//使ってる武器の種類
	int usewpno = Iinfo[(Iinfo[3][3])][1];//使ってる武器のナンバー
	int lunchflg = 0;
	int ech;
	D3DXVECTOR3 ldpos1;
	D3DXVECTOR3 ldpos2( 0.0, 1.0, 0.0);//上向きのベクトル（カメラで使用後、何でもボックス化）

	//以下より、銃の方向を決定します

	if(Iinfo[3][3] != -1){//素手でなくて
	//主観状態ならば
		if(subject == 1){




			if(usewpkind == 0){//もし、使ってる銃がハンドガンなら


							//以下、銃の手部分の設置
							ech = E3DSetNewPoseML(modelId[0]);
							if(ech != 0 ){//エラーチェック
										_ASSERT( 0 );//エラーダイアログ
										return 1;//問題ありで終了
							};

							ech = E3DGetCurrentBonePos( modelId[0], BoneId[0], 1, &ldpos1);//手のポジション取得
							if(ech != 0 ){//エラーチェック
										_ASSERT( 0 );//エラーダイアログ
										return 1;//問題ありで終了
							};

							ech = E3DSetPos( Iinfo[(Iinfo[3][3])][2], ldpos1);//銃を持ち手に設置
							if(ech != 0 ){//エラーチェック
										_ASSERT( 0 );//エラーダイアログ
										return 1;//問題ありで終了
							};

							
							ech = E3DGetCurrentBoneQ( modelId[0], BoneId[2], 2, QId[2]);//手先の向きを取得
							if(ech != 0 ){//エラーチェック
										_ASSERT( 0 );//エラーダイアログ
										return 1;//問題ありで終了
							};
							ech = E3DSetDirQ2( Iinfo[(Iinfo[3][3])][2], QId[2]);
							if(ech != 0 ){//エラーチェック
										_ASSERT( 0 );//エラーダイアログ
										return 1;//問題ありで終了
							};
							
							//以下よりカメラを設定
							//

							ech = E3DGetCurrentBonePos( Iinfo[(Iinfo[3][3])][2], Iinfo[(Iinfo[3][3])][7], 1, &ldpos1);//カメラの先のポジション取得
							if(ech != 0 ){//エラーチェック
										_ASSERT( 0 );//エラーダイアログ
										return 1;//問題ありで終了
							};

							E3DSetCameraTarget(ldpos1,ldpos2);//カメラの注視点を設定する。
							if(ech != 0 ){//エラーチェック
										_ASSERT( 0 );//エラーダイアログ
										return 1;//問題ありで終了
							};


							//以下、銃コリジョンの設置
							//

							ech = E3DSetNewPoseML(Iinfo[(Iinfo[3][3])][2]);
							if(ech != 0 ){//エラーチェック
										_ASSERT( 0 );//エラーダイアログ
										return 1;//問題ありで終了
							};

							ech = E3DGetCurrentBonePos( Iinfo[(Iinfo[3][3])][2], Iinfo[(Iinfo[3][3])][6], 1, &ldpos1);//銃先のポジション取得
							if(ech != 0 ){//エラーチェック
										_ASSERT( 0 );//エラーダイアログ
										return 1;//問題ありで終了
							};

							ech = E3DSetPos( modelId[11], ldpos1);//銃のコリジョンモデルを設置
							if(ech != 0 ){//エラーチェック
										_ASSERT( 0 );//エラーダイアログ
										return 1;//問題ありで終了
							};

							ech = E3DGetCurrentBoneQ( Iinfo[(Iinfo[3][3])][2], Iinfo[(Iinfo[3][3])][7], 2, QId[1]);//銃口の向きを取得
							if(ech != 0 ){//エラーチェック
										_ASSERT( 0 );//エラーダイアログ
										return 1;//問題ありで終了
							};
							ech = E3DSetDirQ2( modelId[11], QId[1]);
							if(ech != 0 ){//エラーチェック
										_ASSERT( 0 );//エラーダイアログ
										return 1;//問題ありで終了
							};

							ech = E3DPosForward( modelId[11], -300);//コリジョンモデルを後退させる
							if(ech != 0 ){//エラーチェック
										_ASSERT( 0 );//エラーダイアログ
										return 1;//問題ありで終了
							};

							E3DGetPos( modelId[11], &ldpos1);//コリジョンモデルの位置を取得
							if(ech != 0 ){//エラーチェック
										_ASSERT( 0 );//エラーダイアログ
										return 1;//問題ありで終了
							};


							//バックしたところにカメラを設置
							//

							ech = E3DSetCameraPos( ldpos1);//カメラの位置をセットする
							if(ech != 0 ){//エラーチェック
										_ASSERT( 0 );//エラーダイアログ
										return 1;//問題ありで終了
							};


			}
		}
	}






	//以下より、銃のリロードやマグのシステムを決定します

	//状態が素手出なければ
	if((Iinfo[3][3]) != -1){

				if(keyin[9] == 1){//もし銃を撃ったら
									Iinfo[ (Iinfo[3][3]) ][3]--;//銃弾を減らす
									Iinfo[ (Iinfo[3][3]) ][5] = 0;//撃ったので、装填しても増加しない
									lunchflg = 1;//銃を撃ったというフラグ

									if((Iinfo[ (Iinfo[3][3]) ][4] == 0)&&(Iinfo[ (Iinfo[3][3]) ][3] == -1)){//マガジンなしで銃を撃ったら
																Iinfo[ (Iinfo[3][3]) ][3] = 0;//
																lunchflg = 0;
									}
									if(Iinfo[ (Iinfo[3][3]) ][3] == -1){//もし、銃弾がないのに撃ったことになっているなら
																lunchflg = 0;//フラグ消滅
									}
				}


				if((keyin[4] == 1)&&(Iinfo[ (Iinfo[3][3]) ][4] != 0 )){//もしリロードキーを押したら
									//ここに爆発系、ライフル系で場合わけを

									if(Iinfo[ (Iinfo[3][3]) ][5] == 1){//もし、MAGもAMMも満タンなら
																Iinfo[ (Iinfo[3][3]) ][4]--;//マガジンを減らす
																Iinfo[ (Iinfo[3][3]) ][3] = wpitem[usewpkind][usewpno][5] + 1;//銃弾を増やす+ 1	
																Iinfo[ (Iinfo[3][3]) ][5] = 0;
									}
									else{
																Iinfo[ (Iinfo[3][3]) ][4]--;//マガジンを減らす
																Iinfo[ (Iinfo[3][3]) ][3] = wpitem[usewpkind][usewpno][5];//銃弾を増やす
									}
				}
				if((keyin[9] == 1) && (Iinfo[ (Iinfo[3][3]) ][3] == -1 ) && (keyin[4] == 0) && (Iinfo[ (Iinfo[3][3]) ][4] != 0)){//もし銃弾0で、発射キーを押したら
																Iinfo[ (Iinfo[3][3]) ][4]--;//マガジンを減らす
																Iinfo[ (Iinfo[3][3]) ][3] = wpitem[usewpkind][usewpno][5];//銃弾を増やす
				}


	}


	//以下より、もし打ってるならそれぞれ個別の処理を行います。

	if((lunchflg == 1)&&(Iinfo[4][0] != 0)){//もし銃が発射していて、敵の数が0でなければ

				if((usewpkind != 6)&&(usewpkind != 7)){//特殊な武器でなければ
							
									int Conchk;//あたってるか大まかな計算
									int inview;//視野角内にあるか
									int Nearmodelid;//近いモデルのID
									int suita;//適当に使わな変数をぶち込む
									D3DXVECTOR3 MyPos;//自分の位置を取得
									D3DXVECTOR3 suitavec3;//適当な使わない変数をぶち込む
									double EneDistance = 0.0;//敵の距離
									double NearmodelVec = 1000000.0;//一番近い敵までの距離
									double Nearidytofar[30][2];//距離と自分の距離のID

		
									//↓当たったモデルを簡易的にチェック＆距離を変数へ↓


									int i = 0;//カウンタ
									int hitnum = 0;//敵に当たった数カウント
									ech = E3DGetPos( modelId[11], &MyPos);
									if(ech != 0 ){//エラーチェック
												_ASSERT( 0 );//エラーダイアログ
												return 1;//問題ありで終了
									};

									while(i<=Iinfo[4][0] - 1){

													//モデルとあたっているかどうか調べる
													E3DChkConflictOBB( modelId[11], -1, Eneinfo[i][2], -1, &Conchk, &inview);
													ech = E3DGetPos( modelId[11], &MyPos);
													if(ech != 0 ){//エラーチェック
																	_ASSERT( 0 );//エラーダイアログ
																	return 1;//問題ありで終了
													};


													if(Conchk == 1){
																	D3DXVECTOR3 EnePos;//敵座標の構造体
																	int i = 0;//カウンタの設置
																	double EneVecPlus[3];//敵の絶対値ベクトル

																	ech = E3DGetPos( Eneinfo[i][2], &EnePos);//敵の座標を取得
																	if(ech != 0 ){//エラーチェック
																				_ASSERT( 0 );//エラーダイアログ
																				return 1;//問題ありで終了
																	};


																	//ベクトルをチェック
																	
																	EneVecPlus[0] = fabs( EnePos.x - MyPos.x );//X座標の絶対値ベクトル
																	EneVecPlus[1] = fabs( EnePos.y - MyPos.y );//Y座標の絶対値ベクトル
																	EneVecPlus[2] = fabs( EnePos.z - MyPos.z );//Z座標の絶対値ベクトル


																	//一番近いモデルかどうかチェック			
																	EneDistance = EneVecPlus[0] + EneVecPlus[1] + EneVecPlus[2];
																	
																	
																	while(i<=Iinfo[4][0] - 1){
																			if(EneDistance <  Nearidytofar[i][1]){
																					Nearidytofar[i][0] = Eneinfo[i][2]
																			
																			
																			
																					hitnum = 1;
																			}

																			i++;
																	}	
													}
									i++;
									}
									i = 0;

									//もし、あたるモデルがあり、使用中の銃の当たりの範囲を超えなければ
									if((hitnum != 0)&&(wpitem[usewpkind][usewpno][4] * 100 > NearmodelVec)){

																	int Clticalhit = 0;//クリティカルの変数を入れる
																	int Wallconf = 0;//壁とあたってるかチェック
																	int bodyconf;//本当にあたっているかどうか精密な当たり判定の変数
																	D3DXVECTOR3 LineCnfPos;//線分で使う座標を取得
																	D3DXVECTOR3 ModelCnfPos;//銃とモデルが当たったところ
																	
																	ech = E3DChkConflictOBB( modelId[11], -1, Eneinfo[Nearmodelid][2], Eneinfo[Nearmodelid][3], &Clticalhit, &suita);
																	if(ech != 0 ){//エラーチェック
																				_ASSERT( 0 );//エラーダイアログ
																				return 1;//問題ありで終了
																	};

																	//壁に当たってないかチェックします。
																	E3DPosForward(  modelId[11], 50000);//棒をを前に
																	if(ech != 0 ){//エラーチェック
																				_ASSERT( 0 );//エラーダイアログ
																				return 1;//問題ありで終了
																	};
																	E3DGetPos(  modelId[11], &LineCnfPos);//線分棒の座標ゲッツ！
																	if(ech != 0 ){//エラーチェック
																				_ASSERT( 0 );//エラーダイアログ
																				return 1;//問題ありで終了
																	};
																	E3DPosForward(  modelId[11], -500000);//棒をを前に
																	if(ech != 0 ){//エラーチェック
																				_ASSERT( 0 );//エラーダイアログ
																				return 1;//問題ありで終了
																	};

																	//↓モデルとの部位あたり座標をゲット↓
																	E3DChkConfLineAndFace( MyPos, LineCnfPos, Eneinfo[Nearmodelid][2], 1, &bodyconf, &suita, &ModelCnfPos, &suitavec3, &suita);
																	if(ech != 0 ){//エラーチェック
																				_ASSERT( 0 );//エラーダイアログ
																				return 1;//問題ありで終了
																	};

																	//↓壁とのあたりをチェック↓
																	//E3DChkConfWallVec( MyPos, ModelCnfPos, グラウンドのID, 0, &Wallconf, &suitavec3, &suitavec3);
																	/*if(ech != 0 ){//エラーチェック
																				_ASSERT( 0 );//エラーダイアログ
																				return 1;//問題ありで終了
																	};*/

																	if(Wallconf == 0){
																		int a;
																		a = 30;
																		//あたっていないのでダメージ判定に行きましょう
																	}
									}
				}
	}
	lunchflg = 0;




	return 0;
}