/*ここでは、敵モデルや敵の動きに関することを
//関数を自動的に実行することができるようにするためのクラスコードファイル
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "cenemy.h"//NPCクラスの宣言ヘッダファイル
#include "cstage.h"//ステージ関係のクラスヘッダファイル
#include "csoldier.h"// 兵士クラスの宣言ヘッダファイル

#include <math.h>


/*コンストラクタ、クラス変数の初期化を行います*/
NPC_Head::NPC_Head(){


	return;
}

/*敵を情報やモデルをロードするための関数*/
int NPC_Head::LoadEnemyModel( const int Ene_Kind, const int Ene_No){

	LoadEnemyModelAddName( "", Ene_Kind, Ene_No);// 名前なしでLoadEnemyModelを実行する

	return 0;
}

/* 敵を情報やモデルをロードするための関数(名前付き) */
int NPC_Head::LoadEnemyModelAddName( const char *Name, const int Ene_Kind, const int Ene_No){

	//変数の初期化
	int ech = 0;//エラーチェック変数の初期化
	char loadname[256] = "";
	NPC_t NPCC;// NPCコンテナに入れるためのNPC構造体


	switch( Ene_Kind){
			case 0:{// 人間
					switch(Ene_No){
							case 0:{
									/* クリーチャークラスポインタを保持する
									// 変数に兵士クラスのポインタを代入 */
									NPCC.NPC_Mdl = new Soldier( 1, 0);

									/* モーション指定 */
									NPCC.NPC_Mdl->Set_UpMotion( 0);
									NPCC.NPC_Mdl->Set_MyState( 0);
									NPCC.NPC_Mdl->Set_UnderMotion( 1);

									/* 武器のロード */
									NPCC.NPC_Mdl->Get_WeaponH()->WpLoad(0,0,0);// アサルトライフルの入手

									break;
						   }
					}
					break;
		   }
	}


	/* 種族と種類を代入する */
	NPCC.NPCRace = Ene_Kind;
	NPCC.NPCNumber = Ene_No;	 
	NPCC.TargetNaviPointID = -1;


	wsprintf( NPCC.NPCName, "%s", Name);
	
	/* ロードしたNPC構造体をプッシュする */
	NPC.push_back( NPCC);

	/*エネミーの数を一つ増やす*/
//	EnemyNum = EnemyNum +1;


	return 0;
}

/*敵の動きをまとめて動かすための関数*/
int NPC_Head::MoveEnemys( Stage *Stg){

	//変数の初期化
	int ech = 0;//エラーチェック変数の初期化
	int GroundResult = 0;
	D3DXVECTOR3 ReflectVec( 0.0, 0.0, 0.0);
	vector<NPC_t>::iterator it;// イテレータ

	/* もし、ナビレールが使えないときは */
	if( Stg->Navi.Get_NaviRailAvailable() == false) return -1;// 処理終了


	/* ////////////////////////////////////////////////////////////// */
	// とりあえずナビポイントだけで動くように指定する、後々複雑化予定
	/* ////////////////////////////////////////////////////////////// */
	for( it = NPC.begin(); it != NPC.end(); it++){

		if( (*it).NPCRace == 0){
			if( (*it).NPCNumber == 0){
					
				if(0 < (*it).NPC_Mdl->Get_HP()){
						// ナビレールによってPC位置を決めます
						Stg->Navi.PCControlByNaviRail( (*it).NPC_Mdl->Get_BodyModel(), &(*it).TargetNaviPointID, Stg->Navi.NaviLineID[ (*it).TargetNaviLineID ]);
							
						(*it).NPC_Mdl->Set_UpMotion( 0);
						(*it).NPC_Mdl->Set_UnderMotion( 1);
				}
				else{// HPがないなら
						(*it).NPC_Mdl->Set_MyState(5);// 死亡状態にする
				}

				// PCの空中位置を制御します
				//Ene[i]->MovePosOnGround( Stg);

				// モーションまとめ処理
				(*it).NPC_Mdl->Batch_PeopleMotion();
						
				// 武器を手に置きます
				(*it).NPC_Mdl->GunPutOnHand();
			}
		}
	}





	return 0;
}
/* 敵の座標をナビポイントを基に設定します*/
int NPC_Head::SetEnemyPosByNaviPoint( Stage *Stg, const char *Name, const int NaviLine, const int NaviPoint){

	/* 変数の宣言&初期化 */
	vector<NPC_t>::iterator it;

	if( Stg->Navi.Get_NaviRailAvailable() == false) return 0;// ナビラインが利用不可なら、抜ける

	/* 名前からNPCのリストを検索 */
	SearchNPCFromName( Name, &it);

	Stg->Navi.SetPosByNaviPoint( (*it).NPC_Mdl->Get_BodyModel(), NaviLine, NaviPoint);

	(*it).TargetNaviLineID = NaviLine;

	return 0;
}
/* 敵の座標をまとめてナビポイントを基に設定します */
int NPC_Head::SetEnemyPosByNaviPointArray( Stage *Stg, const char *Name, const int *EnemyOnNaviLine, int const *EnemyOnNaviPoint, const int ArrayMax){

	for(int i=0; i<ArrayMax; i++){
			SetEnemyPosByNaviPoint( Stg, (Name+20*i), *(EnemyOnNaviLine + i), *(EnemyOnNaviPoint + i));
	}



	return 0;
}
/*デストラクタ、モデルの削除を行います*/
NPC_Head::~NPC_Head(){

	//変数の初期化
	int ech = 0;
	vector<NPC_t>::iterator it;// イテレータ

	for( it = NPC.begin(); it != NPC.end(); it++){
		delete (*it).NPC_Mdl;
	}

	return;
}

int NPC_Head::SearchNPCFromName( const char *ObjName, vector<NPC_t>::iterator *it){

	/* 変数の初期化&宣言 */
	vector<NPC_t>::iterator iit;// イテレータ

	for( iit = NPC.begin(); iit != NPC.end(); iit++){
			if( strcmp( ObjName, (*iit).NPCName) == 0){
					*it = iit;
					return 0;// ループを抜け出す
			}
	}

	// 検索した文字が見つからなければ
	_ASSERT( 1 );//エラーチェック


	return -1;
}