/*ここでは、敵モデルや敵の動きに関することを
//関数を自動的に実行することができるようにするためのクラスコードファイル
*/

#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ
#include "cstage.h"//ステージ関係のクラスヘッダファイル
#include "clive.h"//敵やキャラのクラスヘッダファイル
#include "c_batch_preparat.h"//描画に必要なクラスの宣言ヘッダファイル
#include "cenemy.h"//敵クラスの宣言ヘッダファイル

//ここにグローバル変数を宣言
extern System *sys;//システムクラスを指す、クラスのポインタ


/*コンストラクタ、クラス変数の初期化を行います*/
Enemy::Enemy(){

	/*モデルデータを入れる「Enemy_hsid」の初期化*/
	for(int i = 0; i<15; i++){
			Enemy_hsid[i] = 0;
	}

	/*敵の数を0にする*/
	EnemyNum = 0;

}
/*敵を情報やモデルをロードするための関数*/
int Enemy::LoadEnemyModel( int Ene_Kind, int Ene_No){

	//変数の初期化
	int ech = 0;//エラーチェック変数の初期化
	char loadname[256] = "";


	if( Ene_Kind == -1){//テストモデル
		if( Ene_No == 0){
				//本命ボックスの取得
				wsprintf( loadname, "%s\\data\\3d\\enemy\\valentine\\honmei\\honmeibox.sig", sys->path);
				ech = E3DSigLoad( loadname, 0, 0.3f, &Enemy_hsid[EnemyNum]);//モデルの読み込み、Enemy_hsidへモデルを入れる。
				if(ech != 0 ){//エラーチェック
							_ASSERT(0);//エラーダイアログ
				};
		}
	};

	/*テスト*/
	D3DXVECTOR3 CharaPos( 0.0, 1500.0, 0.0);//エネミーを一応置く位置
	/*座標を取得する*/
	ech = E3DSetPos( Enemy_hsid[EnemyNum], CharaPos);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/**/

	/*エネミーの数を一つ増やす*/
	EnemyNum = EnemyNum +1;


	return 0;
}
/*敵の動きをまとめて動かすための関数*/
int Enemy::MoveEnemys( Stage *Stg){

	//変数の初期化
	int ech = 0;//エラーチェック変数の初期化
	int TargetNaviPointID;//今目指しているナビポイントを指定します
	D3DXQUATERNION NewhsidQ;//移動後のクォータニオンを代入します
	D3DXVECTOR3 NewhsidPos( 0.0, 0.0, 0.0);//移動後の座標を代入します

	/*とりあえずナビポイントだけで動くように指定する、後々複雑化予定*/
	if( Stg->Stage_ID == 3){
		for( int i=0; i<15; i++){
				if( Enemy_hsid[i] != 0){
						ech = E3DControlByNaviLine( Enemy_hsid[i], Stg->NaviLineID, 5, 1, 0, 200.0f, 50.0f, 200.0f, &NewhsidPos, &NewhsidQ, &TargetNaviPointID);
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
						};
						ech = E3DSetPos( Enemy_hsid[i], NewhsidPos);
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
						};
				}	
		}
	}




	return 0;
}
/*デストラクタ、モデルの削除を行います*/
Enemy::~Enemy(){

	//変数の初期化
	int ech = 0;

	for(int i=0; i<EnemyNum; i++){//ロードしたモデルの数だけ
			ech = E3DDestroyHandlerSet( Enemy_hsid[i]);//モデルを削除します
			if(ech != 0 ){//エラーチェック
						_ASSERT( 0 );//エラーダイアログ
			};
	}

}