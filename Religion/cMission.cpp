/*
// ミッションクラスの処理について記述します
//
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include "cMission.h"
#include "clive.h"//敵やキャラの宣言ヘッダファイル
#include "cPoseMenu.h"//メニュークラスに関するヘッダファイル
#include "c_batch_preparat.h"//描画に必要なクラスの宣言ヘッダファイル
#include "cstage.h"//ステージ関係のクラスヘッダファイル
#include "cenemy.h"//敵クラスの宣言ヘッダファイル
#include "ccamera.h"//カメラ関係のクラスヘッダファイル
#include "cStory.h"

#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ



int Mission::Loading( char *File)
{

	/* 初期化 */
	int Parameter[7] = {0};
	int i = 0;
	int MaxStep = 1;
	int ech = 0;
	bool NPCStatementFlg = false;// NPCを一度でも読み込みしたかのフラグ変数
	bool WeaponStatementFlg = false;// Weaponを一度でも読み込みしたかのフラグ変数
	bool WinningStatementFlg = false;// 勝利条件を一度でも設定したかのフラグ
	char CParameter;
	char LoadFullPath[256];
	char Statement[32];
	FILE *fp;

	/* ファイルのオープンの処理 */
	wsprintf( LoadFullPath, "%s\\data\\prof\\mis\\%s", System::path, File);
	fopen_s( &fp, LoadFullPath, "r");//指定されたファイルをオープンします。 
	if( fp == NULL){
		_ASSERT( 0 );
		return -1;
	}
	
	/* プログレスバーを作ります */
	E3DCreateProgressBar();

	/* 読み取ったステートメントで分岐 */
	while( fscanf_s( fp, "%s", &Statement, 32) !=EOF)
	{
		// MaxStepなら、ステップ数の最大を代入
		if( strcmp( Statement, "MaxStep") == NULL)
		{
			
			fscanf_s( fp, "%d", &Parameter[0]);

			MaxStep = Parameter[0];

		}

		// MkPly( Make Player)なら、キャラクタを作成
		else if( strcmp( Statement, "MkPly") == NULL)
		{
			
			fscanf_s( fp, "%d %d", &Parameter[0], &Parameter[1]);

			if( pPlayer != 0)
			{
				delete pPlayer;
			}

			pPlayer = new PlayerChara( Parameter[0], Parameter[1]);

			/* プレイヤーリセットをプッシュする */
			struct MisOrder MiO;

			MiO.Statement = Mission::PINIT;
			MisList.push_back( MiO);

		}

		// WLoad( Weapon Load)なら、武器読み込み(ただし、先にプレイヤーの実体がなければダメ)
		else if( strcmp( Statement, "WLoad") == NULL )
		{

			fscanf_s( fp, "%d %d %d", &Parameter[0], &Parameter[1], &Parameter[2]);

			if( pPlayer == NULL){// プレイヤーインスタンスがなければ
				_ASSERT( 0 );
				return -1;
			}

			pPlayer->Wpn.WpLoad( Parameter[0], Parameter[1], Parameter[2]);// 銃のロード

			/* 武器リセットをプッシュする */
			if( WeaponStatementFlg == false)
			{
				struct MisOrder MiO;
				MiO.Statement = Mission::WINIT;
				MisList.push_back( MiO);

				WeaponStatementFlg = true;
			}
		}

		// SLoad( Stage Load)なら、地形読み込み
		else if( strcmp( Statement, "SLoad") == NULL)
		{

			/* 初期化 */
			int Time = 0;

			fscanf_s( fp, "%d %d %c", &Parameter[0], &Parameter[1], &Parameter[2]);
			
			switch( Parameter[2])
			{
				case 'n':
				{
						Time = Stage::NIGHT;
						break;
				}
				case 'e':
				{
						Time = Stage::EVENING;
						break;
				}
				case 'm':
				{
						Time = Stage::MORNING;
						break;
				}

			}
			
			
			pStg->LoadStage( Parameter[0], Parameter[1], Time);

		}

		// ELoad( Enemy Load)なら、敵読み込み
		else if( strcmp( Statement, "ELoad") == NULL)
		{

			/* 初期化 */
			char EneName[64];

			fscanf_s( fp, "%s %d %d %d %d", &EneName, 64, &Parameter[0], &Parameter[1], &Parameter[2], &Parameter[3]);
			
			// 敵をロードします
			pNPC->LoadEnemyModelAddName( EneName, Parameter[0], Parameter[1]);
			pNPC->SetEnemyPosByNaviPoint( pStg, EneName, Parameter[2], Parameter[3]);

			/* 武器リセットをプッシュする */
			if( NPCStatementFlg == false)
			{
				struct MisOrder MiO;
				MiO.Statement = Mission::NPCINIT;
				MisList.push_back( MiO);

				NPCStatementFlg = true;
			}

		}

		// SMyPos( Set MYmodel POSition)なら、自分の設置
		else if( strcmp( Statement, "SMyPos") == NULL)
		{

			struct MisOrder MiO;
			MiO.Statement = Mission::SMYPOS;


			/* 1番目のパラメータを呼び出す */
			fscanf_s( fp, " %c", &CParameter);
			switch (CParameter)
			{
				// ナビレールで自分設置位置を決めるなら
				case 'n':
				{
					fscanf_s( fp, "%d %d", &Parameter[1], &Parameter[2]);
					MiO.iParameter[0] = NAVI;
					break;
				}
				case 'w':
				{
					fscanf_s( fp, "%d %d %d", &Parameter[1], &Parameter[2], &Parameter[3]);
					MiO.iParameter[0] = WORLD;
				}
			}

			MiO.iParameter[1] = Parameter[1];
			MiO.iParameter[2] = Parameter[2];
			MiO.iParameter[3] = Parameter[3];
			
			MisList.push_back( MiO);

			///* 初期化 */
			//fscanf_s( fp, " %c", &CParameter);

			//
			//switch( CParameter)
			//{
			//	// ナビレールで自分設置位置を決めるなら
			//	case 'n':
			//	{
			//		fscanf_s( fp, "%d %d", &Parameter[1], &Parameter[2]);
			//		pStg->Navi.SetPosByNaviPoint( pPlayer->Get_BodyModel(), Parameter[1], Parameter[2]);
			//		break;
			//	}
			//	case 'w':
			//	{
			//		fscanf_s( fp, "%d %d %d", &Parameter[1], &Parameter[2], &Parameter[3]);
			//		ech = E3DSetPos( pPlayer->Get_BodyModel(), D3DXVECTOR3( (float)Parameter[1], (float)Parameter[2], (float)Parameter[3]));
			//		if( ech != 0){
			//			_ASSERT( 0 );
			//			return 1;
			//		};
			//		break;
			//	}
			//}
		}

		// WInit(Weapon INITialize)なら、弾薬初期化
		else if( strcmp( Statement, "WInit") == NULL)
		{
			struct MisOrder MiO;

			MiO.Statement = Mission::WINIT;
			MisList.push_back( MiO);
	
		}

		// PStory(Play Story)なら、ストーリを流す
		else if( strcmp( Statement, "PStory") == NULL)
		{
			struct MisOrder MiO;

			fscanf_s( fp, "%s", &MiO.cParameter, 30);

			MiO.Statement = Mission::PSTORY;
			MisList.push_back( MiO);

		}

		// PTPS(Play TPS)なら、ゲーム本編に移行する
		else if( strcmp( Statement, "PTPS") == NULL)
		{
			struct MisOrder MiO;

			MiO.Statement = Mission::PTPS;
			MisList.push_back( MiO);
			
		}

		// RegWin(REGister WINning condition)なら、勝利条件を指定する
		else if( strcmp( Statement, "RegWin") == NULL)
		{

			struct MisOrder MiO;

			/* 必ず勝利条件をリセットするようにする */
			if( WinningStatementFlg == false)
			{
				MiO.Statement = Mission::WININIT;
				MisList.push_back( MiO);
				WinningStatementFlg = true;
			}

			/* 勝利条件を指定する */
			fscanf_s( fp, " %c", &CParameter);
			
			switch( CParameter)
			{
				
				case 'a':// 全滅を勝利条件にするなら
				{
					MiO.iParameter[0] = ALLKILL;
					break;
				}
				case 'p':// 所定の場所に着いたら
				{
					/* 初期化 */
					char loadname[256];

					fscanf_s( fp, "%d %d %d", &Parameter[1], &Parameter[2], &Parameter[3]);

					MiO.iParameter[0] = REACHPOINT;

					/* 脱出場所モデルを読み込む */
					wsprintf( loadname, "%s\\data\\3d\\model\\install\\Exitpoint.sig", System::path);//アーティーモデルのsig名登録
					ech = E3DSigLoad( loadname, 0, 1.8f, &(MiO.iParameter[1]));//モデルの読み込み、cha_hsidへモデルを入れる。
					if(ech != 0 ){//エラーチェック
							_ASSERT( ech != 1 );//エラーダイアログ
					};

					/* 非常口マークビルボードをロードします */
					wsprintf( loadname, "%s\\data\\img\\identifier\\exit.png", System::path);
					ech = E3DCreateBillboard ( loadname, 512, 512, 0, 1, 1, &MiO.iParameter[2]);
					_ASSERT( ech != 1 );//エラーチェック

					ech = E3DSetBillboardPos( MiO.iParameter[2],  D3DXVECTOR3( (float)Parameter[1], (float)Parameter[2] + 2000.0f, (float)Parameter[3]));/* !!終了時にビルボードモデルを初期化すること!! */
					_ASSERT( ech != 1 );//エラーチェック

					/* 脱出場所モデル座標を指定する */
					ech = E3DSetPos( MiO.iParameter[1], D3DXVECTOR3( (float)Parameter[1], (float)Parameter[2], (float)Parameter[3]));
					_ASSERT( ech !=1);


					break;
				}
			}


			MiO.Statement = Mission::REGWIN;
			MisList.push_back( MiO);
			
		}

		// RegLose(REGister Losing condition)なら、敗北条件を決める
		else if( strcmp( Statement, "RegLose") == NULL)
		{

			struct MisOrder MiO;

			/* 必ず敗北条件をリセットするようにする */
			if( WinningStatementFlg == false)
			{
				MiO.Statement = Mission::WININIT;
				MisList.push_back( MiO);
				WinningStatementFlg = true;
			}

			/* 勝利条件を指定する */
			fscanf_s( fp, " %c", &CParameter);
			
			switch( CParameter)
			{
				
				case 't':// 時間制限を敗北条件にするなら
				{
					fscanf_s( fp, "%d", &Parameter[1]);
					
					MiO.iParameter[0] = Mission::TIMEUP;
					Timer.LimitTime = Parameter[1];// 制限時間の取得(秒単位)
					Timer.IndicateTimeNormal = false;
					break;
				}
			}


			MiO.Statement = Mission::REGLOSE;
			MisList.push_back( MiO);




		}

		// WinInit(WINning condition Init)なら、勝利条件を初期化
		else if( strcmp( Statement, "WinInit") == NULL)
		{

			struct MisOrder MiO;

			MiO.Statement = Mission::WININIT;
			MisList.push_back( MiO);
			
		}

		// InstOBJなら、ステージにオブジェクトを置くとする
		else if( strcmp( Statement, "InstOBJ") == NULL)
		{
		
			/* 初期化 */
			struct MisOrder MiO;
			char loadname[256];
			
			fscanf_s( fp, " %c", &CParameter);
			
			switch( CParameter)
			{
				case 'j':// カタパルトジャンプを設置する 
				{

					

					fscanf_s( fp, "%d %d %d %d %d %d", &Parameter[1], &Parameter[2], &Parameter[3], &Parameter[4], &Parameter[5], &Parameter[6]);

					MiO.iParameter[0] = CATAPULT;

					/* カタパルトジャンプを読み込む */
					wsprintf( loadname, "%s\\data\\3d\\model\\install\\catapult.sig", System::path);//
					ech = E3DSigLoad( loadname, 0, 0.5f, &(MiO.iParameter[1]));//モデルの読み込み、cha_hsidへモデルを入れる。
					if(ech != 0 ){//エラーチェック
							_ASSERT( ech != 1 );//エラーダイアログ
					};

					/* カタパルトジャンプを指定する */
					ech = E3DSetPos( MiO.iParameter[1], D3DXVECTOR3( (float)Parameter[1], (float)Parameter[2], (float)Parameter[3]));
					_ASSERT( ech !=1);

					///* 非常口マークビルボードをロードします */
					//wsprintf( loadname, "%s\\data\\img\\identifier\\exit.png", System::path);
					//ech = E3DCreateBillboard ( loadname, 512, 512, 0, 1, 1, &MiO.iParameter[2]);
					//_ASSERT( ech != 1 );//エラーチェック

					//ech = E3DSetBillboardPos( MiO.iParameter[2],  D3DXVECTOR3( (float)Parameter[1], (float)Parameter[2] + 2000.0f, (float)Parameter[3]));/* !!終了時にビルボードモデルを初期化すること!! */
					//_ASSERT( ech != 1 );//エラーチェック

					RegisterCatapult( MiO.iParameter[1], Parameter[4], Parameter[5], Parameter[6]);


					break;
				}
			}

			MiO.Statement = Mission::INSTOBJ;
			MisList.push_back( MiO);
			
		}

		// ENDなら、ゲームを終了とする
		else if( strcmp( Statement, "END") == NULL)
		{
			struct MisOrder MiO;

			MiO.Statement = Mission::END;
			MisList.push_back( MiO);
			
		}

		/* プログレスバーを進歩させる */ 
		E3DSetProgressBar( int( double(i) / double(MaxStep) * 100.0));

		i++;
	}

	/* プログレスバーを壊します */
	E3DDestroyProgressBar();

	/* 行検地用プログラム !Debug時に使用! 

	char StepStrings[100];
	wsprintf( StepStrings, "ステップ数は%d回です", i);	
	MessageBox( NULL, StepStrings, "このファイルのステップ数", MB_OK );
	/* ここまで */

	/* FILEの開放 */
	fclose(fp);

	/* その他必要な処理 */

	// バッチプレパラートにすべての描画準備をさせます。
	pBatP = new Batch_Render( pPlayer, pStg, pNPC, pCam);

	/* 音声情報フラグをオンにする */
	System::SetUpdataSoundSys( 1);

	/* バンプマップを有効にします */
	pBatP->BatchEnableBumpMap(0);


	return 0;
}

int Mission::Intialize()
{

	/* 変数の初期化 */
	int ech;
	int ButtonID = 0;
	int Garbage = 0;
	char loadname[256] = "";//読み込む先のパスの文字列変数
	const char MenuKindName[2][32] = {  "再出撃" , "撤退"  };
	ScreenPosArray[0] = 0;
	ScreenPosArray[1] = 0;
	
	for( int i = 0; i<8; i++)
	{
		CatapultData[i].CatapultID = -1;
	}

	pPlayer = 0; 
	pBatP = 0;
	pStg = 0;

	/* カメラインスタンスの生成 */
	pCam = new Camera ;

	/* NPCインスタンスの作成 */;
	pNPC = new NPC_Head;

	/* ステージインスタンスの作成 */
	pStg = new Stage;

	/* メニューインスタンスの作成 */
	pMenu = new PoseMenu;

	/* タイマー構造体にポインタの代入 */
	Timer.TimeUsing = &LosingFlag[COD_TIMEUP];

	/* ゲームオーバースプライトのロード */
	wsprintf( loadname, "%s\\data\\img\\sys\\gameover.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpGameOver);
	_ASSERT( ech != 1 );//エラーチェック

	/* ボタンを作る処理 */
	MakeFontButton_Auto(  MenuKindName[0], &ButtonID, 210, 300);
	MakeFontButton_Auto(  MenuKindName[1], &ButtonID, 380, 300);



	return 0;
}

// 基本的な BatchPreprate の処理を全て行います
int Mission::NormalBatchProces(){

	pBatP->BatchSpriteSet( pPlayer);

	pBatP->BatchRender( 0);
	pBatP->BatchSpriteRender( 0);
	pBatP->Batch_BillBoard( 0);
	pBatP->BatchFont( 1, pPlayer, Timer);



	pBatP->Batch_Present();

	return 0;
}

// デストラクタ 資源の解放をやります
Mission::~Mission(){

	/* 資源の開放 */
	delete pCam;
	delete pNPC;
	delete pMenu;

	if( pPlayer != NULL){
		delete pPlayer;
	}

	if( pBatP != NULL){
		delete pBatP;
	}

	if( pStg != NULL){
		delete pStg;
	}


	return ;
}

//ゲームオーバーした時、再挑戦するか尋ねる。
int Mission::GameOver(){

	/* 初期化 */
	int ech = 0;
	int NextFlag = -1;// ユーザーの選択が入ります
	 int SelectKind = -1;// 選択しているアイテムを識別する変数

	D3DXVECTOR3 SpritePos1( 0.0, 0.0, 0.0);//背景の位置
	//POINT TextPos;//テキストの座標変数


	/*まずはじめに、通常画面→メニュー画面にしていきます。*/
	for(int i = 0; i<17; i++){

			/*変数の初期化*/

			E3DCOLOR4UC AlfaColor = { 15*i ,255,255,255};
			
			/*半透明化します*/
			ech = E3DSetSpriteARGB( SpGameOver, AlfaColor);
			_ASSERT( ech != 1 );//エラーチェック

			/*通常画面のレンダリング*/
			pBatP->BatchRender( 0);//レンダリング

			/*描画準備を行います*/
			E3DBeginScene( System::scid1, 1, -1);;
			E3DBeginSprite();

			ech = E3DRenderSprite( SpGameOver, 640.0/1024.0, 1, SpritePos1);
			_ASSERT( ech != 1 );//エラーダイアログを表示

			/*ここで、描画完了*/
			E3DEndSprite();
			E3DEndScene();
			E3DPresent(System::scid1);

			
	}/*ここまで*/

	while( NextFlag == -1 && WM_QUIT != System::msg.message){

			System::MsgQ(30);//メッセージループ
			System::KeyRenewal(1);

			/*描画準備を行います*/
			E3DBeginScene( System::scid1, 1, -1);;
			E3DBeginSprite();

			ech = E3DRenderSprite( SpGameOver, 640.0/1024.0, 1, SpritePos1);
			_ASSERT( ech != 1 );//エラーダイアログを表示

			E3DEndSprite();


			// バルーンの表示を行います
			PutBalloon_Auto( System::MousePos.x, System::MousePos.y);

			//以下、メニューネーム(通常時・選択時)を表示
			SelectKind = ChkFontButton( System::MousePos.x, System::MousePos.y);

			/* ////////////////////////////////// */
			/* クリックされた時の動作を設定します 
			/* ////////////////////////////////// */
			if( System::GetKeyData( System::KEY_LEFTMOUSE)){
					switch(SelectKind){
							case 0:{// 再挑戦
									NextFlag = RETRY;
									break;
							}
							case 1:{// あきらめる
									NextFlag = GIVEUP;
									break;
							}
					}
			}




			E3DEndScene();
			E3DPresent(System::scid1);

	}




	return NextFlag;
}

int Mission::RegisterCatapult( const int ModelID, const double UpAcceleration, const double Degree, const double Speed)
{
	/* 初期化 */
	int IDNum;

	/* 空の配列を検索して、 */
	for( int i=0; i<8; i++){
			if( CatapultData[i].CatapultID == -1){
					IDNum = i;
					break;
			}
	}

	CatapultData[IDNum].CatapultID = ModelID;
	/*CatapultData[IDNum].X = X;
	CatapultData[IDNum].Y = Y;
	CatapultData[IDNum].Z = Z;*/
	CatapultData[IDNum].UpAcceleration = UpAcceleration;
	CatapultData[IDNum].Degree = Degree;
	CatapultData[IDNum].Speed = Speed;

	return 0;
}