/*ここでは、敵モデルや敵の動きに関することを
//関数を自動的に実行することができるようにするためのクラスコードファイル
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "cenemy.h"//敵クラスの宣言ヘッダファイル
#include "cstage.h"//ステージ関係のクラスヘッダファイル
#include "csoldier.h"// 兵士クラスの宣言ヘッダファイル

#include <math.h>


/*コンストラクタ、クラス変数の初期化を行います*/
Enemy::Enemy(){

	/* 変数の初期化*/
	for(int i = 0; i<15; i++){
			Ene[i] = NULL;
			TargetNaviPointID[i] = -1;
			CreatureRace[i] = 0;
			CreatureNumber[i] = 0;
			TargetNaviLineID[i] = 0;
	}

	/*敵の数を0にする*/
	EnemyNum = 0;

	/* テスト */
	TargetNaviLineID[0] = 2;
	TargetNaviLineID[1] = 1;
	TargetNaviLineID[2] = 1;
	TargetNaviLineID[3] = 0;
	TargetNaviLineID[4] = 0;

	return;
}
/*敵を情報やモデルをロードするための関数*/
int Enemy::LoadEnemyModel( const int Ene_Kind, const int Ene_No){

	//変数の初期化
	int ech = 0;//エラーチェック変数の初期化
	char loadname[256] = "";


	if( Ene_Kind == -1){//テストモデル
	}
	else if( Ene_Kind == 0){// 人間
			if( Ene_No == 0){// Wf兵
					
					/* クリーチャークラスポインタを保持する
					// 変数に兵士クラスのポインタを代入 */
					Ene[EnemyNum] = new Soldier( 1, 0);

					/* モーション指定 */
					Ene[EnemyNum]->Set_UpMotion( 0);
					Ene[EnemyNum]->Set_MyState( 0);
					Ene[EnemyNum]->Set_UnderMotion( 1);

					/* 武器のロード */
					Ene[EnemyNum]->Get_WeaponH()->WpLoad(0,0,0);// アサルトライフルの入手
			}
	}



	/* 種族と種類を代入する */
	CreatureRace[EnemyNum] = Ene_Kind;
	CreatureNumber[EnemyNum] = Ene_No;


	/*エネミーの数を一つ増やす*/
	EnemyNum = EnemyNum +1;


	return 0;
}
/*敵の動きをまとめて動かすための関数*/
int Enemy::MoveEnemys( Stage *Stg){

	//変数の初期化
	int ech = 0;//エラーチェック変数の初期化
	int GroundResult = 0;

	D3DXVECTOR3 ReflectVec( 0.0, 0.0, 0.0);



	/*とりあえずナビポイントだけで動くように指定する、後々複雑化予定*/
	if( Stg->Navi.Get_NaviRailAvailable() == 1){
		for( int i=0; i<EnemyNum; i++){

			if( CreatureRace[i] == 0){
				if( CreatureNumber[i] == 0){
					
					if(0 < Ene[i]->Get_HP()){
							// ナビレールによってPC位置を決めます
							Stg->Navi.PCControlByNaviRail( Ene[i]->Get_BodyModel(), &TargetNaviPointID[i], Stg->Navi.NaviLineID[ (TargetNaviLineID[i]) ]);
							
							Ene[i]->Set_UpMotion( 0);
							Ene[i]->Set_UnderMotion( 1);
					}
					else{// HPがないなら
							Ene[i]->Set_MyState(5);// 死亡状態にする
					}

					// PCの空中位置を制御します
					//Ene[i]->MovePosOnGround( Stg);

					// モーションまとめ処理
					Ene[i]->Batch_PeopleMotion();
						
					// 武器を手に置きます
					Ene[i]->GunPutOnHand();
				}
			}
		}
	}





	return 0;
}
/* 敵の座標をナビポイントを基に設定します*/
int Enemy::SetEnemyPosByNaviPoint( Stage *Stg, const int EnemyNum, const int NaviLine, const int NaviPoint){

	if( Stg->AvailableNaviLineFlag != true) return 0;// ナビラインが利用不可なら、抜ける

	Stg->Navi.SetPosByNaviPoint( Ene[EnemyNum]->Get_BodyModel(), NaviLine, NaviPoint);

	return 0;
}
/* 敵の座標をまとめてナビポイントを基に設定します */
int Enemy::SetEnemyPosByNaviPointArray( Stage *Stg, const int *EnemyOnNaviLine, int const *EnemyOnNaviPoint, const int ArrayMax){

	for(int i=0; i<ArrayMax; i++){
			SetEnemyPosByNaviPoint( Stg, i, *(EnemyOnNaviLine + i), *(EnemyOnNaviPoint + i));
	}



	return 0;
}
/*デストラクタ、モデルの削除を行います*/
Enemy::~Enemy(){

	//変数の初期化
	int ech = 0;

	for( int i=0; i<15; i++){
			delete Ene[i];
	}

	return;
}