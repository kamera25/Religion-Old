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

/* 武器の変更があった際、描画すべき道具を変更します。 */
int Batch_Render::BacthGunTrade( const int Wp_equipment){


	SetModel_ViewFlag( "MainWp", false);
	SetModel_ViewFlag( "SubWp", false);
	SetModel_ViewFlag( "SupportWp", false);

	switch(Wp_equipment){
			case 0:{//装備品がメインウェポンなら

					SetModel_ViewFlag( "MainWp", true);
					break;
			}
			case 1:{

					SetModel_ViewFlag( "SubWp", true);
					break;
			}
			case 2:{

					SetModel_ViewFlag( "SupportWp", true);
					break;
			}
	}


	return 0;
};

/* まとめられたデータを再構築します。この操作は装備品を変えた状態などで必要になります */
int Batch_Render::BatchReset( const PlayerChara *PcC, const Stage *StgC, const Enemy *EneC, const Camera *Cam){

	





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

	for(int i=0; i < EneC->EnemyNum; i++){
			SetModel( EneC->Ene[i]->Get_BodyModel(), true);
			SetModel( EneC->Ene[i]->Get_WeaponH()->Get_WeaponPointer(0)->Get_Model(), true);
	}




	return 0;
};


int Batch_Render::SetModel( const int ID, const bool ViewFlag){

	SetModel_AddName( ID, "", ViewFlag);

	return 0;
}


int Batch_Render::SetModel_AddName( const int ID, const char *Name, const bool ViewFlag){

	/* 変数の初期化&宣言 */
	Model MdlC;

	/* MdlC構造体に情報を代入します */
	MdlC.ID = ID;
	wsprintf( MdlC.Name, "%s", Name);
	MdlC.ViewFlag = ViewFlag;

	Mdl.push_back( MdlC);// 登録した情報をMdlベクターにプッシュする

	return 0;
}

vector<Model>::iterator Batch_Render::SearchModelFromName( const char *ObjName){

	/* 変数の初期化&宣言 */
	vector<Model>::iterator it;// イテレータ

	for( it = Mdl.begin(); it != Mdl.end(); it++){
			if( strcmp( ObjName, (*it).Name) == 0){
					break;// ループを抜け出す
			}
	}

	if( it == Mdl.end()){// 検索した文字が見つからなければ
			_ASSERT( 1 , "Such Name is not found!");//エラーチェック
	}


	return it;
}

int Batch_Render::SetModel_ViewFlag( const char *Name, const bool ViewFlag){

	/* 変数の初期化&宣言 */
	int ech = 0;
	vector<Model>::iterator it = SearchModelFromName( Name);// イテレータ

	(*it).ViewFlag = ViewFlag;


	return 0;
}