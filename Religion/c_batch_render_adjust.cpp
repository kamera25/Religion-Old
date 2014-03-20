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


	if( Wp_equipment == -1){//装備品がなにもなしなら
			Render_hsids[4] = 0;
			Render_hsids[5] = 0;
			Render_hsids[6] = 0;
			ChkIn_hsids[4] = 0;
			ChkIn_hsids[5] = 0;
			ChkIn_hsids[6] = 0;
	}
	if( Wp_equipment == 0){//装備品がメインウェポンなら
			Render_hsids[4] = PCWp_hsids[0][0][0];
			Render_hsids[5] = PCWp_hsids[0][0][1];
			Render_hsids[6] = PCWp_hsids[0][0][2];
			ChkIn_hsids[4] = PCWp_hsids[0][0][0];
			ChkIn_hsids[5] = PCWp_hsids[0][0][1];
			ChkIn_hsids[6] = PCWp_hsids[0][0][2];
	}
	if( Wp_equipment == 1){//装備品がサブウェポンなら
			Render_hsids[4] = PCWp_hsids[0][1][0];
			Render_hsids[5] = PCWp_hsids[0][1][1];
			Render_hsids[6] = PCWp_hsids[0][1][2];
			ChkIn_hsids[4] = PCWp_hsids[0][1][0];
			ChkIn_hsids[5] = PCWp_hsids[0][1][1];
			ChkIn_hsids[6] = PCWp_hsids[0][1][2];
	}
	if( Wp_equipment == 2){//装備品がグレネード系なら
			Render_hsids[4] = PCWp_hsids[0][2][0];
			Render_hsids[5] = PCWp_hsids[0][2][1];
			Render_hsids[6] = PCWp_hsids[0][2][2];
			ChkIn_hsids[4] = PCWp_hsids[0][2][0];
			ChkIn_hsids[5] = PCWp_hsids[0][2][1];
			ChkIn_hsids[6] = PCWp_hsids[0][2][2];
	}







	return 0;
};

/* まとめられたデータを再構築します。この操作は装備品を変えた状態などで必要になります */
int Batch_Render::BatchReset( const PlayerChara *PcC, const Stage *StgC, const Enemy *EneC, const Camera *Cam){


	/*PCが持っている武器モデルデータ配列の初期化*/
	for(int i=0; i<2; i++){
		for(int j=0; j<3; j++){
			for(int k=0; k<4; k++){
				PCWp_hsids[i][j][k] = 0;
			}
		}
	};

	/*ロードしているPCモデルデータ配列の初期化*/
	for(int i=0; i<2; i++){
		PCmodel_hsid[i] = 0;
	};

	/*描画が必要な武器モデルデータ配列の初期化*/
	for(int i=0; i<2; i++){
		for(int j=0; j<4; j++){
			Wp_hsids[i][j] = 0;
		}
	}

	/*ステージモデルデータ配列の初期化*/
	for(int i=0; i<3; i++){
		Stage_hsids[i] = 0;
	};

	/*PCダミーモデルデータ配列の初期化*/
	for(int i=0; i<2; i++){
		PCDummyModel_hsids[i] = 0;
	}

	/*壁モデル配列の初期化*/
	for(int i=0; i<3; i++){
		Wall_hsids[i] = 0;
	};

	/*当たり判定モデル配列の初期化*/
	for(int i=0; i<2; i++){
		Hitmodel_hsids[i] = 0;
	};

	/*視野角内チェックが必要なモデルデータ配列の初期化*/
	for(int i=0; i<40; i++){
		ChkIn_hsids[i] = 0;
	};

	/*描画が必要なモデルデータ配列の初期化*/
	for(int i=0; i<30; i++){
		Render_hsids[i] = 0;
	};

	/*敵モデル配列の初期化*/
	for(int i=0; i<15; i++){
		Enemy_hsids[i] = 0;
	}

	/*スプライトのデータを格納するための配列の初期化*/
	for(int i=0; i<15; i++){
		for(int j=0; j<5; j++){
			SpriteData[i][j] = 0.0f;
		}
	}

	/*スプライトの識別IDを格納する配列の初期化*/
	for(int i=0; i<15; i++){
		SpriteIDs[i] = 0;
	}

	/*カメラのダミーモデルIDを初期化*/
	CamDummyModel_hsid = 0;

	/**/
	///////すべての初期化の終了。
	/////続いて、ステージクラスとプレイヤークラスからデータを読み込みます。
	/**/

	/*メインウェポンからデータを読み込みます*/
	PCWp_hsids[0][0][0] = PcC->Wpn.GetWeaponModelID( 0, 0); //武器モデルID
	PCWp_hsids[0][0][1] = PcC->Wpn.GetWeaponModelID( 0, 1); //使用済み弾薬モデルID
	/*サブウェポンからデータを読み込みます*/
	PCWp_hsids[0][1][0] = PcC->Wpn.GetWeaponModelID( 1, 0); 
	PCWp_hsids[0][1][1] = PcC->Wpn.GetWeaponModelID( 0, 1);
	/*グレネード系からデータを読み込みます*/
	PCWp_hsids[0][2][0] = PcC->Wpn.GetWeaponModelID( 2, 0);
	PCWp_hsids[0][2][1] = PcC->Wpn.GetWeaponModelID( 0, 1);


	/*PCのキャラクターモデルデータを読み込みます*/
	PCmodel_hsid[0] = PcC->Get_BodyModel();

	/*ステージモデルデータを読み込みます*/
	for(int i=0; i<3; i++){
		Stage_hsids[i] = StgC->Stage_hsid[i];
	};


	/**/
	///視野角内チェックだけ必要なもの
	/**/
	
	/*壁モデルデータを読み込みます*/
	for(int i=0; i<3; i++){
		Wall_hsids[i] = StgC->Stage_hsid[i];
	};
	/*ダミーモデルデータを読み込みます*/
	PCDummyModel_hsids[0] = PcC->Get_BodyModel();

	/*カメラダミーモデルを読み込みます*/
	CamDummyModel_hsid = Cam->DummyModel;


	/**/
	/////ステージクラスとプレイヤークラスからデータを読み込みが終わりますた。
	///次に、レンダリングが必要なモデルデータをRender_hsids配列に書き込みます
	/**/

	Render_hsids[0] = PCmodel_hsid[0];//PCモデル
	Render_hsids[1] = Stage_hsids[0];////
	Render_hsids[2] = Stage_hsids[1];//ステージデータ
	Render_hsids[3] = Stage_hsids[2];////

	if( PcC->Get_Wp_equipment() == -1){//装備品がなにもなしなら
			Render_hsids[4] = 0;
			Render_hsids[5] = 0;
	}
	if( PcC->Get_Wp_equipment() == 0){//装備品がメインウェポンなら
			Render_hsids[4] = PCWp_hsids[0][0][0];
			Render_hsids[5] = PCWp_hsids[0][0][1];
	}
	if( PcC->Get_Wp_equipment() == 1){//装備品がサブウェポンなら
			Render_hsids[4] = PCWp_hsids[0][1][0];
			Render_hsids[5] = PCWp_hsids[0][1][1];
	}
	if( PcC->Get_Wp_equipment() == 2){//装備品がグレネード系なら
			Render_hsids[4] = PCWp_hsids[0][2][0];
			Render_hsids[5] = PCWp_hsids[0][2][1];
	}

	for(int i=0; i < EneC->EnemyNum; i++){
			Render_hsids[ 7 + i ] = EneC->Ene[i]->Get_BodyModel();
			Render_hsids[ 7 + EneC->EnemyNum + i ] = EneC->Ene[i]->Get_Weapon()->GetWeaponModelID( 0, 0);
	}
	
	/*
	////レンダリングが必要なモデルデータの書き込みが終了しました
	//次に、視野角内チェックが必要なデータ
	*/

	for(int i=0; i<22; i++){
			ChkIn_hsids[i] = Render_hsids[i];
	}

	ChkIn_hsids[23] = Wall_hsids[0];////
	ChkIn_hsids[24] = Wall_hsids[1];//壁データ
	ChkIn_hsids[25] = Wall_hsids[2];////

	ChkIn_hsids[26] = PCDummyModel_hsids[0];//PCダミーモデルデータ
	ChkIn_hsids[26] = CamDummyModel_hsid;//Camダミーモデルデータ




	return 0;
};
