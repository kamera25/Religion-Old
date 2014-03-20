/*ここでは、モデルやスプライトの描画に必要な情報を収集、また描画で必要な
//関数を自動的に実行することができるようにするためのクラスコードファイル
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "c_batch_preparat.h"//描画に必要なクラスの宣言ヘッダファイル
#include "clive.h"//敵やキャラの宣言ヘッダファイル
#include "cweapon.h"//武器に関することのクラスヘッダファイル
#include "cstage.h"//ステージ関係のクラスヘッダファイル
#include "cenemy.h"//敵クラスの宣言ヘッダファイル
#include "ccamera.h"//カメラ関係のクラスヘッダファイル
#include <string>

/* 武器の変更があった際、描画すべき道具を変更します。 */
int Batch_Render::BacthGunTrade( const int Wp_equipment){

	// すべての武器モデルを表示しないように
	SetModel_ViewFlag( "MainWp", false);
	SetModel_ViewFlag( "SubWp", false);
	SetModel_ViewFlag( "SupportWp", false);

	// すべての武器スプライトを表示しないように
	Set_ViewFlag( "MainWp", false);
	Set_ViewFlag( "SubWp", false);
	Set_ViewFlag( "SupportWp", false);

	//銃の弾薬を表示に
	Set_ViewFlag( "Ammober", true);

	//銃のマガジンを表示に
	Set_ViewFlag( "Magber", true);


	switch(Wp_equipment){
			case -1:{// なにも装備していないなら
				
					//銃の弾薬を無表示に
					Set_ViewFlag( "Ammober", false);

					//銃のマガジンを無表示に
					Set_ViewFlag( "Magber", false);

					break;
			}
			case 0:{// 装備品がメインウェポンなら
					SetModel_ViewFlag( "MainWp", true);
					Set_ViewFlag( "MainWp", true);
					break;
			}
			case 1:{// 装備品がサブウェポンなら
					SetModel_ViewFlag( "SubWp", true);
					Set_ViewFlag( "SubWp", true);
					break;
			}
			case 2:{// 装備品がサポート武器なら
					SetModel_ViewFlag( "SupportWp", true);
					Set_ViewFlag( "SupportWp", true);
					break;
			}
	}



	return 0;
};

/* まとめられたデータを再構築します。この操作は装備品を変えた状態などで必要になります */
int Batch_Render::BatchReset( const PlayerChara *PcC, const Stage *StgC, NPC_Head *NPCC, const Camera *Cam){

	





	/* ////////////////////////////////////////////////////////////////// */
	// 続いて、ステージクラスとプレイヤークラスからデータを読み込みます。
	/* ////////////////////////////////////////////////////////////////// */

	/*メインウェポンからデータを読み込みます*/
	if( PcC->Wpn.Get_WeaponPointer(0) != NULL){
			SetModel_AddName( PcC->Wpn.Get_WeaponPointer(0)->Get_Model(), "MainWp", true);
	}
	/*サブウェポンからデータを読み込みます*/
	if( PcC->Wpn.Get_WeaponPointer(1) != NULL){
			SetModel_AddName( PcC->Wpn.Get_WeaponPointer(1)->Get_Model(), "SubWp", true);
	}
	/*グレネード系からデータを読み込みます*/
	if( PcC->Wpn.Get_WeaponPointer(2) != NULL){
			SetModel_AddName( PcC->Wpn.Get_WeaponPointer(2)->Get_Model(), "SupportWp", true);
	}


	/*PCのキャラクターモデルデータを読み込みます*/
	SetModel( PcC->Get_BodyModel(), true);

	/*ステージモデルデータを読み込みます*/
	for(int i=0; i<3; i++){
		SetModel( StgC->Stage_hsid[i], true);
	};


	/**/
	///視野角内チェックだけ必要なもの
	/**/
	
	/*壁モデルデータを読み込みます*/
	for(int i=0; i<3; i++){
		SetModel( StgC->Stage_hsid[i], false);
	};


	/*カメラダミーモデルを読み込みます*/
	SetModel( Cam->DummyModel, false);

	map<string, NPC_t>::iterator it;// イテレータ

	for( it = NPCC->Get_NPC_begin(); it != NPCC->NPC_endit(); it++){
			SetModel( (*it).second.NPC_Mdl->Get_BodyModel(), true);
			SetModel( (*it).second.NPC_Mdl->Get_WeaponH()->Get_WeaponPointer(0)->Get_Model(), true);
	}

//	BacthGunTrade( PcC->Get_Wp_equipment());


	return 0;
};


int Batch_Render::SetModel( const int ID, const bool ViewFlag){

	static int Number = 0;// 名前をつけないモデルは、数字のみで管理
	char cbuf[5];

	wsprintf( cbuf, "%d\0", Number);	
	SetModel_AddName( ID, cbuf, ViewFlag);

	Number++;
	if( Number >= 10000)
	{
		Number = 0;
	}

	return 0;
}


int Batch_Render::SetModel_AddName( const int ID, const char *Name, const bool ViewFlag){

	/* 変数の初期化&宣言 */
	Model MdlC;

	/* MdlC構造体に情報を代入します */
	MdlC.ID = ID;
	MdlC.ViewFlag = ViewFlag;

	Mdl.insert( make_pair( string(Name), MdlC));
	//Mdl.push_back( MdlC);// 登録した情報をMdlベクターにプッシュする

	return 0;
}

//int Batch_Render::SearchModelFromName( const char *ObjName, map< const char *, Model>::iterator *it){
//	
//
//
//	//vector<Model>::iterator iit;
//
//	//for( iit = Mdl.begin(); iit != Mdl.end(); iit++){
//	//		if( strcmp( ObjName, (*iit).Name) == 0){
//	//				*it = iit;
//	//				return 0;// ループを抜け出す
//	//		}
//	//}
//
//	/* 以下、検索された文字が見つからなかったときの処理 */
//	
//
//	return -1;
//}

int Batch_Render::SetModel_ViewFlag( const char *Name, const bool ViewFlag){

	/* 変数の初期化&宣言 */
	int ech = 0;
	map< string, Model>::iterator it;


	if( Mdl.count(Name))
	{
		it = Mdl.find(Name);
	}
	else// 検索した文字が見つからなければ
	{
			_ASSERT( 1 );//エラー
			return -1;
	}

		
	// 検索した文字が見つかれば	
	(*it).second.ViewFlag = ViewFlag;


	return 0;
}