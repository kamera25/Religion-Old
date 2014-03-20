/*ここでは、カメラに関する操作を行います
//例:カメラアニメ、位置、設定など
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "ccamera.h"//カメラ関係のクラスヘッダファイル

//ここで使うグローバル変数を宣言
extern System *sys;//システムクラスを指す、クラスのポインタ

/*カメラクラスのコンストラクタ、ダミーモデルのロードなど*/
Camera::Camera(){

	//変数の初期化
	int ech = 0;
	char loadname[256] = "";


	//ダミーモデルの取得
	wsprintf( loadname, "%s\\data\\3d\\model\\other\\demo.sig", sys->path);//仮モデルのsig名登録
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
int Camera::CamShoulderGunBack( int Qid, float PC_Deg_XZ, D3DXVECTOR3 StomachPos){

			//変数の初期化
			int ech = 0;
			D3DXVECTOR3 CameraUpVec( 0.0, 1.0, 0.0);//カメラの上部のベクトル
			D3DXVECTOR3 CameraPos( 0.0, 0.0, 0.0);//カメラの座標
			D3DXVECTOR3 CameraTarget( 0.0, 0.0, 0.0);//カメラの注意点


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

			/*90度傾ける*/
			ech = E3DRotateY( DummyModel, 90);
			if(ech != 0 ){//エラーチェック
						_ASSERT( 0 );//エラーダイアログ
			};

			/*前進させるさせる*/
			ech = E3DPosForward( DummyModel, 270);
			if(ech != 0 ){//エラーチェック
						_ASSERT( 0 );//エラーダイアログ
			};

			/*カメラのポジションになる、PCモデルの位置を取得*/
			ech = E3DGetPos( DummyModel, &CameraPos);
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
