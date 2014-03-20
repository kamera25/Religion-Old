/*ここでは、カメラに関する操作を行います
//例:カメラアニメ、位置、設定など
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "ccamera.h"//カメラ関係のクラスヘッダファイル
#include "cstage.h"//ステージ関係のクラスヘッダファイル




/*カメラクラスのコンストラクタ、ダミーモデルのロードなど*/
Camera::Camera(){

	//変数の初期化
	int ech = 0;
	char loadname[256] = "";

	/*メンバ変数の初期化*/
	ShoulderComMode = 0;
	ShoulderComCounter = 0;
	ShoulderComMoveDeg = 0;


	//ダミーモデルの取得
	wsprintf( loadname, "%s\\data\\3d\\model\\other\\demo.sig", System::path);//仮モデルのsig名登録
	ech = E3DSigLoad( loadname, 0, 0.01f, &DummyModel);//モデルの読み込み、submodidへモデルを入れる。
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};



	return;
}
/*カメラクラスのデストラクタ、ダミーモデルなどを破棄します*/
Camera::~Camera(){

	//変数の初期化
	int ech = 0;

	//1つ目のキャラクターダミーモデルを削除します
	E3DDestroyHandlerSet( DummyModel);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};


	return;
}
/*肩打ち視点でのカメラを設定する関数*/
int Camera::CamShoulderGunBack( int cha_hsid, int Qid, int bone, float PC_Deg_XZ, const Stage *Stg){

		//変数の初期化
		int ech = 0;
		int HitResult = 0;//壁に当たっているか判定チェックします
		int keyin[20];//キー情報配列を作成 
		D3DXVECTOR3 CameraUpVec( 0.0, 1.0, 0.0);//カメラの上部のベクトル
		D3DXVECTOR3 CameraPos( 0.0, 0.0, 0.0);//カメラの座標
		D3DXVECTOR3 CameraTarget( 0.0, 0.0, 0.0);//カメラの注意点
		D3DXVECTOR3 StomachPos( 0.0, 0.0, 0.0);//「首つけ根」の座標
		D3DXVECTOR3 GarbageD3DVec( 0.0, 0.0, 0.0);//要らないXYZのデータの一次入れ


		/*キーを取得する*/
		System::GetKeyData(keyin);

		/*キャラクターモデルの「首つけ根」の！今！の座標を取得します*/
		ech = E3DGetCurrentBonePos( cha_hsid, bone, 1, &StomachPos);
		if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
		};

		/*ダミーモデルを自分の「首付け根」座標に置きます*/
		ech = E3DSetPos( DummyModel, StomachPos);
		if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
		};

		/*ダミーモデルに「首つけ根」のクォータニオンを設定します*/
		ech = E3DSetDirQ2( DummyModel, Qid);
		if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
		};

		/*キャラクターを回転させます*/
		ech = E3DRotateY( DummyModel, PC_Deg_XZ);
		if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
		};

		/*前進させるさせる*/
		ech = E3DPosForward( DummyModel, 13000);
		if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
		};

		/*カメラのターゲットになる、ダミーモデルの位置を取得*/
		ech = E3DGetPos( DummyModel, &CameraTarget);
		if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
		};

		/*カメラの注視点を設定します*/
		ech = E3DSetCameraTarget( CameraTarget, CameraUpVec);
		if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
		};

		/*ダミーモデルを自分の「首付け根」座標に置きます*/
		ech = E3DSetPos( DummyModel, StomachPos);
		if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
		};

		/*ダミーモデルを後退させる*/
		ech = E3DPosForward( DummyModel, -435);
		if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
		};

		/* /////////////////////////////////////// */
		/* 肩内視点でのカメラ向き(左右)の設定を行ないます
		/* ////////////////////////////////////// */

		if( ShoulderComMode == 0){// カメラ変更なし

				if( ShoulderComMoveDeg == 0){// カメラをキャラクタの右肩に置く (●・) 

						/* ダミーモデルを右に傾ける */
						ech = E3DRotateY( DummyModel, 90);
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
						};

						/* 前進させる */
						ech = E3DPosForward( DummyModel, 270);
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
						};

				}
				else if( ShoulderComMoveDeg == 1){// カメラをキャラクタの左肩に置く (・●)

						/* ダミーモデルを左に傾ける */
						ech = E3DRotateY( DummyModel, -90);
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
						};

						/*前進させる*/
						ech = E3DPosForward( DummyModel, 270);
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
						};

				}
			
				// 視点変更がオンされたら
				if( keyin[5] == 1){
						ShoulderComMode = 1;// カメラ変更モードをオンにする
						ShoulderComCounter = 0;//カウンタを初期値"4"にセット
				}

		}
		else if( ShoulderComMode == 1){// カメラ変更中

				D3DXVECTOR3 DamModPosRight( 0.0, 0.0, 0.0);// キャラクタの右肩座標
				D3DXVECTOR3 DamModPosLeft( 0.0, 0.0, 0.0);// キャラクタの左肩座標
				D3DXVECTOR3 ReferencePos( 0.0, 0.0, 0.0);// 後ろに後退したあとのカメラの座標

				/* //////////////////////////////////////// */
				// ダミーモデルをキャラクタの右肩に置き座標を取得する (●・) 
				/* //////////////////////////////////////// */

				ech = E3DGetPos( DummyModel, &ReferencePos);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};
				ech = E3DRotateY( DummyModel, 90);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};
				ech = E3DPosForward( DummyModel, 270);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};
				ech = E3DGetPos( DummyModel, &DamModPosRight);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};

				/* //////////////////////////////////////// */
				// ダミーモデルをキャラクタの左肩に置き座標を取得する (・●) 
				/* //////////////////////////////////////// */

				ech = E3DRotateInit( DummyModel);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};
				/*ダミーモデルに「首つけ根」のクォータニオンを設定します*/
				ech = E3DSetDirQ2( DummyModel, Qid);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};

				/*キャラクターを回転させます*/
				ech = E3DRotateY( DummyModel, PC_Deg_XZ);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};

				ech = E3DSetPos( DummyModel, ReferencePos);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};
				ech = E3DRotateY( DummyModel, -90);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};
				ech = E3DPosForward( DummyModel, 270);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};
				ech = E3DGetPos( DummyModel, &DamModPosLeft);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};

				/* //////////////// */
				// 
				/* //////////////// */

				D3DXVECTOR3 CameraRLPosDif( 0.0, 0.0, 0.0);
				D3DXVECTOR3 CameraRLPosDifUnit( 0.0, 0.0, 0.0);
				D3DXVECTOR3 CameraLastPos( 0.0, 0.0, 0.0);

				if( ShoulderComMoveDeg == 0){// 右肩から左肩へ変位させる(・←・)

					CameraRLPosDifUnit.x = (DamModPosLeft.x - DamModPosRight.x) / 4.0f;
					CameraRLPosDifUnit.y = (DamModPosLeft.y - DamModPosRight.y) / 4.0f;
					CameraRLPosDifUnit.z = (DamModPosLeft.z - DamModPosRight.z) / 4.0f;

					CameraLastPos.x =  ( CameraRLPosDifUnit.x * ShoulderComCounter) + DamModPosRight.x;
					CameraLastPos.y =  ( CameraRLPosDifUnit.y * ShoulderComCounter) + DamModPosRight.y;
					CameraLastPos.z =  ( CameraRLPosDifUnit.z * ShoulderComCounter) + DamModPosRight.z;


				}
				else if( ShoulderComMoveDeg == 1){// 右肩から左肩へ変位させる(・→・)

					CameraRLPosDifUnit.x = (DamModPosRight.x - DamModPosLeft.x) / 4.0f;
					CameraRLPosDifUnit.y = (DamModPosRight.y - DamModPosLeft.y) / 4.0f;
					CameraRLPosDifUnit.z = (DamModPosRight.z - DamModPosLeft.z) / 4.0f;

					CameraLastPos.x =  ( CameraRLPosDifUnit.x * ShoulderComCounter) + DamModPosLeft.x;
					CameraLastPos.y =  ( CameraRLPosDifUnit.y * ShoulderComCounter) + DamModPosLeft.y;
					CameraLastPos.z =  ( CameraRLPosDifUnit.z * ShoulderComCounter) + DamModPosLeft.z;

				}

				ech = E3DSetPos( DummyModel, CameraLastPos);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};

				if( ShoulderComCounter == 4){
						if( ShoulderComMoveDeg == 0){
								ShoulderComMoveDeg = 1;
						}
						else if( ShoulderComMoveDeg == 1){
								ShoulderComMoveDeg = 0;
						}
						ShoulderComMode = 0;
				}
				
				/*カウンターを減少させる*/
				ShoulderComCounter = ShoulderComCounter + 1;

		}








		/*カメラのポジションになるかもしれない、PCモデルの位置を取得*/
		ech = E3DGetPos( DummyModel, &CameraPos);
		if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
		};

		/*壁と当たり判定チェック、壁に埋まったりしてないかチェックします*/
		ech = E3DChkConfGroundVec( StomachPos, CameraPos, Stg->Stage_hsid[0], 0, 200, -1000, 
					&HitResult, &CameraPos, &GarbageD3DVec);
		if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
		};

		/*カメラをセットする*/
		ech = E3DSetCameraPos( CameraPos);
		if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
		};

		/*ダミーモデルの方向を初期化します*/
		ech = E3DRotateInit( DummyModel);
		if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
		};


	return 0;
}
