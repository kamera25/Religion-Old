/*ここでは、ステージの読み込み、制御を行う関数を定義するクラスコードファイルです。
//
*/
#include "cstage.h"//ステージや壁の宣言ヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

//ここで使うグローバル変数を宣言
extern System *sys;//システムクラスを指す、クラスのポインタ


/*ステージをロード・設定する関数です*/
int Stage::LoadStage(int StageID, int StageKind, int LightKind){

	int ech = 0;//エラーチェック変数の初期化
	int NaviPoint = 0;//新しく追加したナビポイントのIDを代入
	float FogDist = 1000.0;//背景の距離を指定する変数、通常は1000(近い)
	char loadname[256] = "";//読み込みデータ用の文字列配列
	D3DXVECTOR3 NaviPointPos( 0.0, 0.0, 0.0);//ナビポイント座標を代入する構造体


	//ステージ上のデータを初期化します。
	for(int i = 0; i < 3; i++){
		Stage_hsid[i]= 0;//ステージ配列を初期化します
		Wall_hsid[i] = 0;//壁配列を初期化します
	};

	//ナビラインを作成します
	ech = E3DCreateNaviLine( &NaviLineID); 
	if( ech != 0){
				_ASSERT( 0 );
	};




	/*
		以下より、マップを用意します。
	*/

	if(StageID == 0){//トロンプール

		if(StageKind == 0){//実戦MAP

						wsprintf( loadname, "%s\\data\\3d\\map\\st_trom\\trom.sig", sys->path);
						ech = E3DLoadSigFileAsGround(loadname, 30.0, 0, &Stage_hsid[0]);
						if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
								return 1;//問題ありで終了
						};

						wsprintf( loadname, "%s\\data\\3d\\map\\st_trom\\trom_wl2.mqo", sys->path);
						ech = E3DLoadMQOFileAsMovableArea(loadname, 50.0, &Wall_hsid[0]);
						if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
								return 1;//問題ありで終了
						};
		};

		if(StageKind == 1){//練習用MAP
						wsprintf( loadname, "%s\\data\\3d\\map\\st_trom\\trom_tr.sig", sys->path);
						ech = E3DLoadSigFileAsGround(loadname, 50.0, 0, &Stage_hsid[0]);
						if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
								return 1;//問題ありで終了
						};

						wsprintf( loadname, "%s\\data\\3d\\map\\st_trom\\trom_trwall.mqo", sys->path);
						ech = E3DLoadMQOFileAsMovableArea(loadname, 50.0, &Wall_hsid[0]);
						if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
								return 1;//問題ありで終了
						};
		};

		E3DCOLOR4UC FogColor = {255,255,255,255};
		E3DSetLinearFogParams(1, FogColor, 15000, 100000, -1);//ファグをかけます。
		if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
		}

		Stage_GunTarget = 0;//ステージの銃操作を"通常"にする
		Stage_GndMode = 0;//キャラ地面操作を"通常にする"

	};

	/////////////////

	if(StageID == 1){//ロビー

		if(StageKind == 0){//実戦MAP
						wsprintf( loadname, "%s\\data\\3d\\map\\st_trom\\trom.sig", sys->path);
						ech = E3DLoadSigFileAsGround(loadname, 50.0, 0, &Stage_hsid[0]);
						if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
								return 1;//問題ありで終了
						};

						wsprintf( loadname, "%s\\data\\3d\\map\\st_trom\\trom_wl2.mqo", sys->path);
						ech = E3DLoadMQOFileAsMovableArea(loadname, 50.0, &Wall_hsid[0]);
						if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
								return 1;//問題ありで終了
						};
		};

		E3DCOLOR4UC FogColor = {255,255,255,255};
		E3DSetLinearFogParams(1, FogColor, 15000, 100000, -1);//ファグをかけます。
		if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
								return 1;//問題ありで終了
		}

		Stage_GunTarget = 0;//ステージの銃操作を"通常"にする
		Stage_GndMode = 0;//キャラ地面操作を"通常にする"

	};

	////////////////

	if(StageID == 2){//森林

		if(StageKind == 0){
						wsprintf( loadname, "%s\\data\\3d\\map\\st_forest\\st_forest.sig", sys->path);
						ech = E3DLoadSigFileAsGround(loadname, 40.0, 0, &Stage_hsid[0]);
						if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
								return 1;//問題ありで終了
						};
		
						wsprintf( loadname, "%s\\data\\3d\\map\\st_forest\\gwl_forest.mqo", sys->path);
						ech = E3DLoadMQOFileAsMovableArea( loadname, 40.0, &Wall_hsid[1]);
						if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
								return 1;//問題ありで終了
						};

		};

		E3DCOLOR4UC FogColor = {100,100,100,100};
		E3DSetLinearFogParams(1, FogColor, 4000, 8000, -1);//ファグをかけます。
		if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
								return 1;//問題ありで終了
		}

		FogDist = 8000.0f;//背景のもやで見えにくくする。
		Stage_GunTarget = 0;//ステージの銃操作を"通常"にする
		Stage_GndMode = 0;//キャラ地面操作を"通常にする"

	};

	////////////////

	if(StageID == 3){//神ヶ一町（ビル街）

		if(StageKind == 0){
						wsprintf( loadname, "%s\\data\\3d\\map\\st_kamigaichi\\st_kamigaichi.sig", sys->path);
						ech = E3DLoadSigFileAsGround(loadname, 40.0, 0, &Stage_hsid[0]);
						if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
								return 1;//問題ありで終了
						};

		};

		/*モヤの設定*/
		E3DCOLOR4UC FogColor = {100,100,100,100};
		E3DSetLinearFogParams(1, FogColor, 15000, 100000, -1);//ファグをかけます。
		if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
								return 1;//問題ありで終了
		}

		//特殊環境設定
		Stage_GunTarget = 0;//ステージの銃操作を"通常"にする
		Stage_GndMode = 0;//キャラ地面操作を"通常にする"

		//ナビラインの作成
		NaviPointPos.x = -12300.0;/**/NaviPointPos.y = 0.0;/**/NaviPointPos.z = -3400.0;//次のナビポイントの座標を指定
		ech = E3DAddNaviPoint( NaviLineID, -1, &NaviPoint);//ナビポイントを追加
		if( ech != 0){
					_ASSERT( 0 );
		};
		ech = E3DSetNaviPointPos( NaviLineID, NaviPoint, NaviPointPos);//ナビポイントの座標を指定
		if( ech != 0){
					_ASSERT( 0 );
		};//

		NaviPointPos.x = -12000.0;/**/NaviPointPos.y = 0.0;/**/NaviPointPos.z = 7200.0;//次のナビポイントの座標を指定
		ech = E3DAddNaviPoint( NaviLineID, -1, &NaviPoint);//ナビポイントを追加
		if( ech != 0){
					_ASSERT( 0 );
		};
		ech = E3DSetNaviPointPos( NaviLineID, NaviPoint, NaviPointPos);//ナビポイントの座標を指定
		if( ech != 0){
					_ASSERT( 0 );
		};//

		NaviPointPos.x = 4000.0;/**/NaviPointPos.y = 0.0;/**/NaviPointPos.z = 7200.0;//次のナビポイントの座標を指定
	//	ech = E3DAddNaviPoint( NaviLineID, -1, &NaviPoint);//ナビポイントを追加
		if( ech != 0){
					_ASSERT( 0 );
		};
	//	ech = E3DSetNaviPointPos( NaviLineID, NaviPoint, NaviPointPos);//ナビポイントの座標を指定
		if( ech != 0){
					_ASSERT( 0 );
		};//

	//	NaviPointPos.x = 3200.0;/**/NaviPointPos.y = 0.0;/**/NaviPointPos.z = -3500.0;//次のナビポイントの座標を指定
		ech = E3DAddNaviPoint( NaviLineID, -1, &NaviPoint);//ナビポイントを追加
		if( ech != 0){
					_ASSERT( 0 );
		};
	//	ech = E3DSetNaviPointPos( NaviLineID, NaviPoint, NaviPointPos);//ナビポイントの座標を指定
		if( ech != 0){
					_ASSERT( 0 );
		};//

		NaviPointPos.x = -12300.0;/**/NaviPointPos.y = 0.0;/**/NaviPointPos.z = -3400.0;//次のナビポイントの座標を指定
	//	ech = E3DAddNaviPoint( NaviLineID, -1, &NaviPoint);//ナビポイントを追加
		if( ech != 0){
					_ASSERT( 0 );
		};
	//	ech = E3DSetNaviPointPos( NaviLineID, NaviPoint, NaviPointPos);//ナビポイントの座標を指定
		if( ech != 0){
					_ASSERT( 0 );
		};//

		/*//*/

	};

	/////////////////

	if(StageID == 4){//ReligionMall（レリギオンモール）

		if(StageKind == 0){
						wsprintf( loadname, "%s\\data\\3d\\map\\st_rm\\rm.sig", sys->path);
						ech = E3DLoadSigFileAsGround(loadname, 55.0, 0, &Stage_hsid[0]);
						if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
								return 1;//問題ありで終了
						};
		

		};

		/*モヤの設定*/
		E3DCOLOR4UC FogColor = {100,100,100,100};
		E3DSetLinearFogParams(1, FogColor, 15000, 100000, -1);//ファグをかけます。
		if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
								return 1;//問題ありで終了
		}

		Stage_GunTarget = 0;//ステージの銃操作を"通常"にする
		Stage_GndMode = 0;//キャラ地面操作を"通常にする"

	};

	////////////////

	if(StageID == 5){//基地前

		if(StageKind == 0){
						wsprintf( loadname, "%s\\data\\3d\\map\\st_kichimae\\kichimae.sig", sys->path);
						ech = E3DLoadSigFileAsGround(loadname, 20.0, 0, &Stage_hsid[0]);
						if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
								return 1;//問題ありで終了
						};
		

		};

		/*モヤの設定*/
		E3DCOLOR4UC FogColor = {100,100,100,100};
		E3DSetLinearFogParams(1, FogColor, 15000, 100000, -1);//ファグをかけます。
		if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
								return 1;//問題ありで終了
		}

		Stage_GunTarget = 0;//ステージの銃操作を"通常"にする
		Stage_GndMode = 0;//キャラ地面操作を"通常にする"

	};

	/*
		以下より、光源を用意します。
	*/

	//光源を作成します。
	ech = E3DCreateLight( &Light1_ID);//光源1を作成します。
	if( ech != 0){
				_ASSERT( 0 );
	};
	ech = E3DCreateLight( &Light2_ID);//光源2を作成します。
	if( ech != 0){
				_ASSERT( 0 );
	};

	//光源の属性を決定します。

	if(LightKind == 0){//晴れ

					D3DXVECTOR3 ldir1( -1.0, -1.0, -1.0);
					D3DXVECTOR3 ldir2( 1.0, 1.0, 1.0);
					E3DCOLOR4UC LightColor = { 255, 255, 255, 255};

					//一つ目のライト設定w
					ech = E3DSetDirectionalLight( Light1_ID, ldir1, LightColor);
					if( ech != 0){
								_ASSERT( 0 );
					};

					//二つ目のライト設定
					ech = E3DSetDirectionalLight( Light2_ID, ldir2, LightColor);
					if( ech != 0){
								_ASSERT( 0 );
					};

					//背景を作ります
					wsprintf( loadname, "%s\\data\\3d\\map\\360\\hare.jpg", sys->path);
					ech = E3DCreateBG( sys->scid1, loadname, "", 0, 0, 1, FogDist);
					if( ech != 0){
								_ASSERT( 0 );
					};
	}

	/////////////////
	if(LightKind == 1){//夕方

					D3DXVECTOR3 ldir1( -1.0, -1.0, -1.0);
					D3DXVECTOR3 ldir2( 1.0, 1.0, 1.0);
					E3DCOLOR4UC LightColor= { 200, 50, 50, 255};

					//一つ目のライトを設定する。
					ech = E3DSetDirectionalLight( Light1_ID, ldir1, LightColor);
					if( ech != 0){
								_ASSERT( 0 );
					};

					//二つ目のライトを設定する。
					ech = E3DSetDirectionalLight( Light2_ID, ldir2, LightColor);
					if( ech != 0){
								_ASSERT( 0 );
					};

					//背景を作ります
					wsprintf( loadname, "%s\\data\\3d\\map\\360\\sunset.jpg", sys->path);
					ech = E3DCreateBG( sys->scid1, loadname, "", 0, 0, 1, FogDist);
					if( ech != 0){
								_ASSERT( 0 );
					};
	}

	////////////////
	if(LightKind == 2){//夜

					D3DXVECTOR3 ldir1( -1.0, -1.0, -1.0);
					D3DXVECTOR3 ldir2( 1.0, 1.0, 1.0);
					E3DCOLOR4UC LightColor = { 50, 50, 50, 255};

					//一つ目のライトを設定する。
					ech = E3DSetDirectionalLight( Light1_ID, ldir1, LightColor);
					if( ech != 0){
								_ASSERT( 0 );
					};

					//二つ目のライトを設定する。
					ech = E3DSetDirectionalLight( Light2_ID, ldir2, LightColor);
					if( ech != 0){
								_ASSERT( 0 );
					};

					//背景を作ります
					wsprintf( loadname, "%s\\data\\3d\\map\\360\\night.jpg", sys->path);
					ech = E3DCreateBG( sys->scid1, loadname, "", 0, 0, 1, FogDist);
					if( ech != 0){
								_ASSERT( 0 );
					};
	}

	/**/
	//最後に変数操作を行います。
	/**/

	Stage_ID = StageID;//ステージIDを代入
	Stage_Kind = StageKind;//ステージの種類を代入



	return 0;
}

/*Stageクラスのデコンストラクタ、ロードした情報などを削除します。*/
Stage::~Stage(){

	//変数の初期化を行います
	int ech = 0;//エラーチェック変数の初期化
	

	//ステージと壁を削除します
	for(int i = 0; i < 3; i++){
		if(Stage_hsid[i] != 0){//ステージを削除します
				ech = E3DDestroyHandlerSet( Stage_hsid[i]);
				if( ech != 0){
							_ASSERT( 0 );
				};
		}
		if(Wall_hsid[i] != 0){//壁を削除します
				ech = E3DDestroyHandlerSet( Wall_hsid[i]);
				if( ech != 0){
							_ASSERT( 0 );
				};
		}
	};




	/*光源を削除するよ*/

	//一つ目の光源の削除
	ech = E3DDestroyLight( Light1_ID);
	if( ech != 0){
				_ASSERT( 0 );
	};
	//一つ目の光源の削除
	ech = E3DDestroyLight( Light2_ID);
	if( ech != 0){
				_ASSERT( 0 );
	};


	//背景を削除します
	ech = E3DDestroyBG( sys->scid1);
	if( ech != 0){
				_ASSERT( 0 );
	};

	//ナビラインを削除します
	ech = E3DDestroyNaviLine( NaviLineID);
	if( ech != 0){
				_ASSERT( 0 );
	};


}