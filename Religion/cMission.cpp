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

/* 読み込まれたMISファイルによって、処理を行います。 */
int Mission::MainProc()
{
	// イテレータ 及び 変数の宣言
	list<MisOrder>::iterator it; 

	// イテレータの中身が空になるまで繰り返す
	for( it = MisList.begin(); it != MisList.end(); it++)
	{

		
		// オーダーがWInit(Weapon INITialize)なら
		if( (*it).Statement == Mission::WINIT)
		{
			// 弾薬の初期化
			pPlayer->Wpn.SetInitWeapon( Weapon_Head::RESET);
		}

		// オーダーがPStory(Play Story)なら
		if( (*it).Statement == Mission::PSTORY)
		{
			Story StoryS;
			StoryS.LoadStoryFromSTD( (*it).cParameter);
			StoryS.StartStory(1);
		}


		// オーダーがPTPS(Play TPS)なら
		if( (*it).Statement == Mission::PTPS)
		{
			System::SetMouseCursol( 320, 240);//マウスをウィンドウ真ん中に設置

			// ゲーム開始
			while(  WM_QUIT != System::msg.message ){
				System::MsgQ(30);//メッセージループ
				TPSMainLoop();
			}
		}
	}

	return 0;
}

int Mission::Loading( char *File)
{

	/* 初期化 */
	int Parameter[6] = {0};
	int i = 0;
	int MaxStep = 1;
	int ech = 0;
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

		}

		// SMyPos( Set MYmodel POSition)なら、自分の設置
		else if( strcmp( Statement, "SMyPos") == NULL)
		{

			/* 初期化 */
			fscanf_s( fp, " %c", &CParameter);

			
			switch( CParameter)
			{
				// ナビレールで自分設置位置を決めるなら
				case 'n':
				{
					fscanf_s( fp, "%d %d", &Parameter[1], &Parameter[2]);
					pStg->Navi.SetPosByNaviPoint( pPlayer->Get_BodyModel(), Parameter[1], Parameter[2]);
					break;
				}
				case 'w':{
					fscanf_s( fp, "%d %d %d", &Parameter[1], &Parameter[2], &Parameter[3]);
					ech = E3DSetPos( pPlayer->Get_BodyModel(), D3DXVECTOR3( Parameter[1], Parameter[2], Parameter[3]));
					if( ech != 0){
						_ASSERT( 0 );
						return 1;
					};
					break;
				}
			}
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

		/* プログレスバーを進歩させる */ 
		E3DSetProgressBar( double(i) / double(MaxStep) * 100.0);

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
	ScreenPosArray[0] = 0;
	ScreenPosArray[1] = 0;

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

	return 0;
}

int Mission::TPSMainLoop()
{


				System::KeyRenewalFromWp( &pPlayer->Wpn, pPlayer->Get_Wp_equipment());


				pBatP->BatchChkInView();

				// 制御関係
				pPlayer->Wpn.ChkWeaponsLaunch( pPlayer->Get_Wp_equipment());
				pPlayer->NormallyPCSystem( pStg, pBatP, pNPC, pCam, ScreenPosArray);
				pPlayer->Wpn.AttackEnemys( pNPC, pPlayer, ScreenPosArray, pStg);
				pPlayer->Wpn.WeaponsTreatment( pPlayer->Get_Wp_equipment(), pStg);
				pNPC->MoveEnemys( pStg);

				// 描画関連
				NormalBatchProces();

				// 後処理関係
				pMenu->FarstInMenu( pBatP, pPlayer);
				pBatP->BatchBeforePos();
				pPlayer->Batch_PeopleMotion();



	return 0;
}

// 基本的な BatchPreprate の処理を全て行います
int Mission::NormalBatchProces(){

	pBatP->BatchSpriteSet( pPlayer);
	pBatP->BatchRender( 0);
	pBatP->Batch_BillBoard( 0);
	pBatP->BatchSpriteRender( 0);
	pBatP->BatchFont( 1, pPlayer);
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