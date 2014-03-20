/*ここでは、モデルやスプライトの描画に必要な情報を収集、また描画で必要な
//関数を自動的に実行することができるようにするためのクラスコードファイル
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "c_batch_preparat.h"//描画に必要なクラスの宣言ヘッダファイル
#include "clive.h"//敵やキャラの宣言ヘッダファイル
#include "cenemy.h"//敵クラスの宣言ヘッダファイル
#include "cweapon.h"//武器に関することのクラスヘッダファイル
#include "cstage.h"//ステージ関係のクラスヘッダファイル
#include "ccamera.h"//カメラ関係のクラスヘッダファイル






/*コンストラクタ、ステージやプレイヤークラスを元に情報を収集、構成します*/
Batch_Preparat::Batch_Preparat( const PlayerChara *PcC, const Stage *StgC, const Enemy *EneC, 
								const Camera *Cam, Weapon *Wep){

	/*
	//////まずはじめにすべての変数を初期化します。
	*/
	int ech = 0;//エラーチェック用の確認変数 
	E3DCOLOR4UC AlfaColor = { 100,255,255,255};//カラー構造体の半透過のデータ
	char loadname[256] = "";//読み込む先のパスの文字列変数

	
	/*描画、視野角データの構築を行います*/
	BatchReset( PcC, StgC, EneC, Cam, Wep);


	/*
	//次にスプライトのロードを行います、同時にデータも代入します
	*/

	/*カーソル画像のロードを行う 配列は[0]番*/
	wsprintf( loadname, "%s\\data\\img\\carsol.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteIDs[0]);//カーソルのロード
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
	};

	/*半透明化します*/
	ech = E3DSetSpriteARGB( SpriteIDs[0], AlfaColor);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
	};
	/*データの格納*/
	SpriteData[0][0] = 0.1f;//X倍率（1/10）
	SpriteData[0][1] = 0.1f;//Y倍率（1/10）
	SpriteData[0][4] = 0.0f;//Z座標奥行（一番手前）


	/*右ステータス画像の背景のロードを行う 配列は[1]番*/
	wsprintf( loadname, "%s\\data\\img\\parameter\\parameter3.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteIDs[1]);//カーソルのロード
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
	};
	/*データの格納*/
	SpriteData[1][0] = 1.0f;//X倍率
	SpriteData[1][1] = 1.0f;//Y倍率
	SpriteData[1][2] = 0.0f;//X座標
	SpriteData[1][3] = 390.0f;//Y座標
	SpriteData[1][4] = 0.0f;//Z座標奥行（一番手前）


	/*右ステータス画像の背景のロードを行う 配列は[2]番*/
	wsprintf( loadname, "%s\\data\\img\\parameter\\parameter4.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteIDs[2]);//カーソルのロード
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
	};
	/*データの格納*/
	SpriteData[2][0] = 1.0f;//X倍率
	SpriteData[2][1] = 1.0f;//Y倍率
	SpriteData[2][2] = 506.0f;//X座標
	SpriteData[2][3] = 390.0f;//Y座標
	SpriteData[2][4] = 0.0f;//Z座標奥行（手前）


	/*左HPのバーのロードを行う 配列は[3]番*/
	wsprintf( loadname, "%s\\data\\img\\parameter\\hpber.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteIDs[3]);//カーソルのロード
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
	};
	/*データの格納*/
	SpriteData[3][0] = 100.0f;//X倍率
	SpriteData[3][1] = 1.0f;//Y倍率
	SpriteData[3][2] = 24.0f;//X座標
	SpriteData[3][3] = 412.0f;//Y座標
	SpriteData[3][4] = 0.0f;//Z座標奥行（手前）


	/*左スタミナのバーのロードを行う 配列は[4]番*/
	wsprintf( loadname, "%s\\data\\img\\parameter\\stnber.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteIDs[4]);//カーソルのロード
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
	};
	/*データの格納*/
	SpriteData[4][0] = 100.0f;//X倍率
	SpriteData[4][1] = 0.5f;//Y倍率
	SpriteData[4][2] = 24.0f;//X座標
	SpriteData[4][3] = 435.0f;//Y座標
	SpriteData[4][4] = 0.0f;//Z座標奥行（手前）


	/*右弾薬数のバーのロードを行う 配列は[5]番*/
	wsprintf( loadname, "%s\\data\\img\\parameter\\ammber.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteIDs[5]);//カーソルのロード
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
	};
	/*データの格納*/
	SpriteData[5][0] = 100.0f;//X倍率
	SpriteData[5][1] = 0.8125f;//Y倍率(13pix)
	SpriteData[5][2] = 530.0f;//X座標
	SpriteData[5][3] = 407.0f;//Y座標
	SpriteData[5][4] = 0.0f;//Z座標奥行（手前）


	/*右マガジン数のバーのロードを行う 配列は[6]番*/
	wsprintf( loadname, "%s\\data\\img\\parameter\\magber.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteIDs[6]);//カーソルのロード
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
	};
	/*データの格納*/
	SpriteData[6][0] = 100.0f;//X倍率
	SpriteData[6][1] = 0.8125f;//Y倍率(13pix)
	SpriteData[6][2] = 530.0f;//X座標
	SpriteData[6][3] = 436.0f;//Y座標
	SpriteData[6][4] = 0.0f;//Z座標奥行（手前）


	/*左ステータス画像のロードを行う 配列は[7]番*/
	wsprintf( loadname, "%s\\data\\img\\parameter\\parameter1.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteIDs[7]);//カーソルのロード
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
	};
	/*データの格納*/
	SpriteData[7][0] = 1.0f;//X倍率
	SpriteData[7][1] = 1.0f;//Y倍率
	SpriteData[7][2] = 0.0f;//X座標
	SpriteData[7][3] = 390.0f;//Y座標
	SpriteData[7][4] = 0.0f;//Z座標奥行（一番手前）


	/*右ステータス画像のロードを行う 配列は[8]番*/
	wsprintf( loadname, "%s\\data\\img\\parameter\\parameter2.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteIDs[8]);//カーソルのロード
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
	};
	/*データの格納*/
	SpriteData[8][0] = 1.0f;//X倍率
	SpriteData[8][1] = 1.0f;//Y倍率
	SpriteData[8][2] = 506.0f;//X座標
	SpriteData[8][3] = 390.0f;//Y座標
	SpriteData[8][4] = 0.0f;//Z座標奥行（一番手前）


	/*兵器に関する画像の設定、配列は[9]番*/
	SpriteData[9][0] = 1.0f;//X倍率
	SpriteData[9][1] = 1.0f;//Y倍率
	SpriteData[9][2] = 506.0f;//X座標
	SpriteData[9][3] = 326.0f;//Y座標
	SpriteData[9][4] = 0.0f;//Z座標奥行（一番手前）


};
/*まとめられたデータを描画します。*/
int Batch_Preparat::BatchRender( int SceneEndFlg){

	int ech = 0;//エラーチェック用の確認変数

	ech = E3DRenderBatch( System::scid1, &Render_hsids[30], 30, 0, 0);
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};


	/*
	//描画の終了処理
	*/
	if( SceneEndFlg == 1){

		ech = E3DEndScene();
		if(ech != 0){//エラーチェック
					_ASSERT(0);//エラーダイアログを表示
		};
	}


	return 0;
};
/*まとめられたスプライトをレンダリングするための関数です*/
int Batch_Preparat::BatchSpriteRender( int SceneEndFlg){

	/*変数の初期化*/
	int ech = 0;//エラー確認変数の初期化


	/*
	//描画処理の開始
	*/

	ech = E3DBeginScene( System::scid1, 1, -1);
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};

	ech = E3DBeginSprite();
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};

	/*
	//描画を行います、ループ中に描画されます
	*/

	for(int i=0; i<15; i++ ){
		if( SpriteIDs[i] != 0){//データがちゃんとあれば
			/*変数の初期化*/
			D3DXVECTOR3 ScreenPos( SpriteData[i][2], SpriteData[i][3], SpriteData[i][4]);//描画位置を指定する構造体

			ech = E3DRenderSprite( SpriteIDs[i], SpriteData[i][0], SpriteData[i][1], ScreenPos);
			if(ech != 0){//エラーチェック
					_ASSERT(0);//エラーダイアログを表示
			};
		}
	}

	ech = E3DEndSprite();
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};

	/*
	//描画の終了処理
	*/
	if( SceneEndFlg == 1){
	
		ech = E3DEndScene();
		if(ech != 0){//エラーチェック
					_ASSERT(0);//エラーダイアログを表示
		};
	}


	return 0;
}
/*視野角内チェックが必要なデータ（描画するデータも含む）をチェックします*/
int Batch_Preparat::BatchChkInView(){

	int garbage = 0;//いらない変数を格納します
	int ech = 0;//エラーチェック用の確認変数 


	for(int i=0; i<40; i++){
		/*視野角内のチェックを行います*/
		if( ChkIn_hsids[i] != 0){//空のモデルデータ以外なら
			ech = E3DChkInView( System::scid1, ChkIn_hsids[i], &garbage);
			if(ech != 0){//エラーチェック
						_ASSERT(0);//エラーダイアログを表示
			}
		}
	};


	return 0;
};
/*一つ前の座標をまとめて保存するのに使います*/
int Batch_Preparat::BatchBeforePos(){

	/*変数の初期化*/
	int ech = 0;//エラーチェック用の確認変数 


	for(int i=0; i<40; i++){
		/*視野角内のチェックを行います*/
		if( ChkIn_hsids[i] != 0){//空のモデルデータ以外なら
			ech = E3DSetBeforePos( ChkIn_hsids[i]);
			if(ech != 0){//エラーチェック
						_ASSERT(0);//エラーダイアログを表示
			}
		}
	};


	return 0;
}
/*武器の変更があった際、描画すべき道具を変更します。*/
int Batch_Preparat::BacthGunTrade( int Wp_equipment){


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
/*まとめられたデータを再構築します。この操作は装備品を変えた状態などで必要になります*/
int Batch_Preparat::BatchReset( const PlayerChara *PcC, const Stage *StgC, const Enemy *EneC, const Camera *Cam, Weapon *Wep){


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
	PCWp_hsids[0][0][0] = Wep->GetWeaponModelID( 0, 0); //武器モデルID
	PCWp_hsids[0][0][1] = Wep->GetWeaponModelID( 0, 1); //使用済み弾薬モデルID
	/*サブウェポンからデータを読み込みます*/
	PCWp_hsids[0][1][0] = Wep->GetWeaponModelID( 1, 0); 
	PCWp_hsids[0][1][1] = Wep->GetWeaponModelID( 0, 1);
	/*グレネード系からデータを読み込みます*/
	PCWp_hsids[0][2][0] = Wep->GetWeaponModelID( 2, 0);
	PCWp_hsids[0][2][1] = Wep->GetWeaponModelID( 0, 1);


	/*PCのキャラクターモデルデータを読み込みます*/
	PCmodel_hsid[0] = PcC->cha_hsid[0];

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
	PCDummyModel_hsids[0] = PcC->DummyModel;

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

	if( PcC->Wp_equipment == -1){//装備品がなにもなしなら
			Render_hsids[4] = 0;
			Render_hsids[5] = 0;
	}
	if( PcC->Wp_equipment == 0){//装備品がメインウェポンなら
			Render_hsids[4] = PCWp_hsids[0][0][0];
			Render_hsids[5] = PCWp_hsids[0][0][1];
	}
	if( PcC->Wp_equipment == 1){//装備品がサブウェポンなら
			Render_hsids[4] = PCWp_hsids[0][1][0];
			Render_hsids[5] = PCWp_hsids[0][1][1];
	}
	if( PcC->Wp_equipment == 2){//装備品がグレネード系なら
			Render_hsids[4] = PCWp_hsids[0][2][0];
			Render_hsids[5] = PCWp_hsids[0][2][1];
	}

	for(int i=0; i<15; i++){
			Render_hsids[ 7+i ] = EneC->Enemy_hsid[i];
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
/*最初にロードしたスプライトの倍率や描画指定*/
int Batch_Preparat::BatchSpriteSet( const PlayerChara *PcC, Weapon *Wep){

	/*スプライトの倍率を変更します*/

	//HPバーについての倍率代入
	SpriteData[3][0] = float( PcC->HP) / float( PcC->MaxHP) * 100.0f;

	//スタミナバーについての倍率代入
	SpriteData[4][0] = float( PcC->Stamina) / 150.0f * 100.0f;

	if( PcC->Wp_equipment == -1){//武器なしなら

				//銃の弾薬を無表示に
				SpriteData[5][0] = 0.0f;

				//銃のマガジンを無表示に
				SpriteData[6][0] = 0.0f;

				//スプライトを表示しないように
				SpriteIDs[9] = 0;

	}
	else{//武器ありなら
				//銃の弾薬についての倍率変換
				SpriteData[5][0] = float( Wep->GetWeaponDataWhileGame( PcC->Wp_equipment, 0)) / float(Wep->GetWeaponData( PcC->Wp_equipment, 2)) * 100.0f;

				//銃のマガジンについての倍率変換
				SpriteData[6][0] = float( Wep->GetWeaponDataWhileGame( PcC->Wp_equipment, 1)) / float(Wep->GetWeaponData( PcC->Wp_equipment, 3)) * 100.0f;

				//表示すべき画像をSpriteIDsに代入する
				SpriteIDs[9] = Wep->GetSpriteData( PcC->Wp_equipment);
	}

	return 0;
}
/*文字を描画することや設定をしたりします*/
int Batch_Preparat::BatchFont( int SceneEndFlg, const PlayerChara *PcC, Weapon *Wep){

	/*変数の初期化*/
	int ech = 0;//エラーチェック用の確認変数
	float Scale = 1.6f;//文字の大きさを格納する変数
	char ParometaString[64] = "";//表示させる文字を入れます
	D3DXVECTOR2 Pos( 0.0, 0.0);//座標を代入する構造体
	E3DCOLOR4UC Color = { 255, 50, 50, 50};//空の構造体
	E3DCOLOR4UC Gray = { 255, 50, 50, 50};//色構造体、グレーを指定
	E3DCOLOR4UC White = { 255, 230, 230, 230};//色構造体、白を指定
	E3DCOLOR4UC Red = { 255, 255, 100, 100};//色構造体、赤を指定
	E3DCOLOR4UC Bule = { 255, 100, 100, 250};//色構造体、青を指定
	E3DCOLOR4UC Yellow = { 255, 255, 255, 100};//色構造体、黄を指定

	/*文字の描画*/
	//HP部分の描画
	Pos.x = 28.0f;/**/Pos.y = 394.0f;
	ech = E3DDrawText( Pos, Scale, Gray, "F19");
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
	};


	if( PcC->Wp_equipment != -1){ //武器がなし以外なら

			/*現在のAmmoの数を表示します*/
			if( Wep->GetWeaponDataWhileGame( PcC->Wp_equipment, 0) == 0){//弾薬がなくなったら
					Color = Red;// 赤色にします
			}
			else if( Wep->GetWeaponData( PcC->Wp_equipment, 2) < Wep->GetWeaponDataWhileGame( PcC->Wp_equipment, 0)){//弾が増えているならなら
					Color = Bule;// 青にします
			}
			else if( double(Wep->GetWeaponDataWhileGame( PcC->Wp_equipment, 0)) / double(Wep->GetWeaponData( PcC->Wp_equipment, 2)) < 0.3){//弾薬が3割以下なら
					Color = Yellow;// 黄にします
			}
			else{//通常モードなら
					Color = White;// 白にします
			}
			wsprintf( ParometaString, "%d", Wep->GetWeaponDataWhileGame( PcC->Wp_equipment, 0));
			Pos.x = 558.0f;/**/Pos.y = 394.0f;
			ech = E3DDrawText( Pos, 1.4f, Color, ParometaString);
			if(ech != 0){//エラーチェック
					_ASSERT(0);//エラーダイアログを表示
			};

			/*Ammoの数を表示します*/
			wsprintf( ParometaString, "%d", Wep->GetWeaponData( PcC->Wp_equipment, 2));
			Pos.x = 588.0f;/**/Pos.y = 394.0f;
			ech = E3DDrawText( Pos, 1.4f, White, ParometaString);
			if(ech != 0){//エラーチェック
					_ASSERT(0);//エラーダイアログを表示
			};

			/*現在のMagの数を表示します*/
			if( Wep->GetWeaponDataWhileGame( PcC->Wp_equipment, 1) == 0){//マガジンがなくなったら
					Color = Red;// 赤色にします
			}
			else if( double(Wep->GetWeaponDataWhileGame( PcC->Wp_equipment, 1)) / double(Wep->GetWeaponData( PcC->Wp_equipment, 3)) < 0.3){//弾薬が3割以下なら
					Color = Yellow;// 黄にします
			}
			else{//通常モードなら
					Color = White;// 白にします
			}
			wsprintf( ParometaString, "%d", Wep->GetWeaponDataWhileGame( PcC->Wp_equipment, 1));
			Pos.x = 558.0f;/**/Pos.y = 424.0f;
			ech = E3DDrawText( Pos, 1.4f, Color, ParometaString);
			if(ech != 0){//エラーチェック
					_ASSERT(0);//エラーダイアログを表示
			};

			/*Magの数を表示します*/
			wsprintf( ParometaString, "%d", Wep->GetWeaponData( PcC->Wp_equipment, 3));
			Pos.x = 588.0f;/**/Pos.y = 424.0f;
			ech = E3DDrawText( Pos, 1.4f, White, ParometaString);
			if(ech != 0){//エラーチェック
					_ASSERT(0);//エラーダイアログを表示
			};

	}


	/*
	//描画の終了処理
	*/
	if( SceneEndFlg == 1){

		ech = E3DEndScene();
		if(ech != 0){//エラーチェック
					_ASSERT(0);//エラーダイアログを表示
		};
	}

	return 0;
}
/*デストラクタ、スプライトを削除します*/
Batch_Preparat::~Batch_Preparat(){

	/*変数の初期化*/
	int ech = 0;//エラーチェック用の確認変数 
		
	for(int i=0; i<9; i++){//ロードしたスプライトの削除
			ech = E3DDestroySprite( SpriteIDs[i]);
			if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
			};
	}


}
