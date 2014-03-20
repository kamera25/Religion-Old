/*
// ミッションクラスの処理について記述します(whileGameファイルは、ゲーム中の処理が中心)
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
	bool RPModelUseFlag = false;// 所定の場所に集まるのに利用する、モデルがロードされているか
	int NextFlag = NORMAL;
	int ech;
	list<MisOrder>::iterator it; 
	int Event = NORMAL;
	GameState = NORMAL;// ゲーム状態をノーマルにする
	RPModelID = -1;// 所定の場所に集まるのに利用するモデル

	// イテレータの中身が空か、ゲーム状態がになるまで繰り返す
	for( it = MisList.begin(); it != MisList.end() ; it++)
	{
		/* 再挑戦のイベントが発行されていれば */
		if( Event == RETRY)
		{
			it = MisList.begin();
			Event = NORMAL;// ゲーム状態をノーマルにする
		}
		
		/* ////////////////////////////// */
		/* オーダーによって条件分岐を行う */
		/* ////////////////////////////// */

		switch( (*it).Statement )
		{
			// オーダーがSMyPos(Set MY POSition)なら
			case SMYPOS:
			{
				switch( (*it).iParameter[0])
				{
					// ナビレールで自分設置位置を決めるなら
					case NAVI:
					{
						pStg->Navi.SetPosByNaviPoint( pPlayer->Act, (*it).iParameter[1], (*it).iParameter[2]);
						break;
					}
					case WORLD:
					{
						pPlayer->Act->SetPos( (float)(*it).iParameter[1], (float)(*it).iParameter[2], (float)(*it).iParameter[3]));

						pBatP->test();
						break;
					}
				}
				break;
			}


			// オーダーがPInit(Player INITialize)なら
			case PINIT:
			{
				/* リセット */
				pPlayer->StatusReset();
				break;
			}

			// オーダーがNPCInit(NPC INITialize)なら
			case NPCINIT:
			{
				/* リセット */
				pNPC->StatusReset();
				break;
			}

			// オーダーがWInit(Weapon INITialize)なら
			case WINIT:
			{
				// 弾薬の初期化
				pPlayer->Wpn.SetInitWeapon( Weapon_Head::RESET);
				break;
			}

			// オーダーがPStory(Play Story)なら
			case PSTORY:
			{
				Story StoryS;
				StoryS.LoadStoryFromSTD( (*it).cParameter);
				StoryS.StartStory(1);
				System::WaitRender();
				break;
			}

			// オーダーがREGWIN(REGister WINning condition)なら
			case REGWIN:
			{
				switch((*it).iParameter[0])
				{
					/* 全滅なら */
					case ALLKILL:
					{
						WinningFlag[COD_ALLKILL] = true;
						break;
					}
					/* 所定のポイントについたら */
					case REACHPOINT:
					{
						WinningFlag[COD_REACHPOINT] = true;
						pBatP->SetModel( (*it).iParameter[1], true);
						RPModelID = (*it).iParameter[1];// モデルIDの代入
						RPModelUseFlag = true;

						break;
					}
				}
				break;
			}

			// オーダーがWININIT(WINning condition INITialize)なら
			case WININIT:
			{
				for( int i = 0; i < 8; i++){
					WinningFlag[i] = false;
					LosingFlag[i] = false;
					NowWinConditionFlag[i] = false;
					NowLosingConditionFlag[i] = false;
					CatapultFlag = false;
				}
				break;
			}

			// オーダーがPTPS(Play TPS)なら
			case PTPS:
			{
				System::SetMouseCursol( 320, 240);//マウスをウィンドウ真ん中に設置
				
				/* 時間制限ありなら */
				if( LosingFlag[COD_TIMEUP] == true)
				{
					Timer.FirstTime = clock();
				}
				pBatP->ResetLog();
				pBatP->BacthGunTrade( pPlayer->Get_Wp_equipment());

				// ゲーム開始
				do{
					System::MsgQ(30);//メッセージループ
					TPSMainLoop();
					Event = CheckBattle();
				}while( WM_QUIT != System::msg.message && Event != GAMEOVER && Event != CLEAR && Event != GIVEUP);

				//ゲームオーバーになったら
				if( Event == GAMEOVER)
				{
					Event = GameOver();
				}
			



				break;
			}

			// オーダーがEndなら
			case END:
			{
				/* もし、所定の場所に集まることが条件なら*/
				if( RPModelUseFlag == true)
				{
				
					ech = E3DDestroyHandlerSet( RPModelID);
					_ASSERT( ech != 1 );//エラーチェック
				
					RPModelUseFlag = false;
				}
				break;
			}

			// オーダーがRegLoseなら
			case REGLOSE:
			{

				// 敗北条件によって条件分岐
				switch( (*it).iParameter[0])
				{
					// 時間指定なら
					case TIMEUP:
					{
						LosingFlag[COD_TIMEUP] = true;
						break;
					}
				}


				break;
			}
			
			case INSTOBJ:
			{
				switch((*it).iParameter[0])
				{
					/* カタパルトジャンプについたら */
					case CATAPULT:
					{
						pBatP->SetModel( (*it).iParameter[1], true);
						CatapultFlag = true;
						break;
					}
				}
				break;
			}
		}


		


	
	}

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

				/* カタパルトジャンプ処理 */
				ChkCatapult();

				pNPC->MoveEnemys( pStg);

				// 描画関連
				NormalBatchProces();

				// 後処理関係
				pMenu->FarstInMenu( pBatP, pPlayer);
				pBatP->BatchBeforePos();
				pPlayer->Batch_PeopleMotion();

				//イベント処理
				EventSupervision();


	return 0;
}



// イベント関連の統括を行う
int Mission::EventSupervision()
{
	/* 初期化 */
	int Conflict;
	int Garbage;
	int ech;
	
	GameState = pPlayer->EventPublish();
	if( GameState == NORMAL) GameState = pMenu->EventPublish();
	if( GameState == NORMAL) GameState = pNPC->EventPublish();
	if( GameState == NORMAL)
	{
		/* 所定の場所に集まるなら */
		if( WinningFlag[COD_REACHPOINT] == true )
		{
			Conflict = pPlayer->Act->ConflictOBB( RPModelID);
			/*ech = E3DChkConflictOBB( pPlayer->Get_BodyModel(), -1, RPModelID, -1, &Conflict, &Garbage);*/
			if( Conflict == 1){// 衝突を検知したら
				GameState = REACHPOINT;
			}
		}

	}

	/* ログテスト */
	if( GameState == ALLKILL) pBatP->PutLog("Congratulations! You killed all Enemy around here!");
	if( System::GetKeyData(System::KEY_Z) == 1)
	{
		D3DXVECTOR3 MyPos;
		char LogText[120];
		MyPos = pPlayer->Act->GetPos();
		/*E3DGetPos( pPlayer->Get_BodyModel(), &MyPos);*/
		wsprintf( LogText, " %d %d %d(MyPos)", (int)MyPos.x, (int)MyPos.y, (int)MyPos.z);
		pBatP->PutLog(LogText);
	}

	return 0;
}

// 勝利・負け条件を満たしているかチェックする
int Mission::CheckBattle()
{
	/* 初期化 */
	int Event;
	
	if( GAMEOVER == GameState || GameState == GIVEUP)
	{
		return GameState;
	}

	/* ////////////////// */
	/* 勝利条件のチェック */
	/* ////////////////// */

	// 全滅なら
	if( WinningFlag[COD_ALLKILL] == true && GameState == ALLKILL)
	{
		NowWinConditionFlag[COD_ALLKILL] = true;
	}

	// 所定の場所に集まるなら
	if( WinningFlag[COD_REACHPOINT] == true && GameState == REACHPOINT)
	{
		NowWinConditionFlag[COD_REACHPOINT] = true;
	}

	/* ////////////////// */
	/* 敗北条件のチェック */
	/* ////////////////// */
	// 時間制限なら
	if( LosingFlag[COD_TIMEUP] == true &&  ( (double)( clock() - Timer.FirstTime) / (double)CLOCKS_PER_SEC) > Timer.LimitTime)
	{
		return GAMEOVER;
	}


	/* 全ての処理条件を満たしているかチェック */
	Event = CLEAR;
	for( int i = 0; i < 8; i++)
	{
		/* 必要勝利条件を現在満たしていなければ */
		if( WinningFlag[i] == true && NowWinConditionFlag[i] == false)
		{
			Event = NORMAL;
			break;
		}

	}

	return Event;
}

int Mission::ChkCatapult()
{
	/* 初期化 */
	int ech;
	int Garbage;
	int Conflict;
	D3DXVECTOR3 CatPos;

	/* カタパルトを利用していなければ */
	if( CatapultFlag == false)
	{
		return 1;
	} 

	for( int i = 0; i < 8; i++)
	{
		if( CatapultData[i].CatapultID == -1) continue;// IDが-1になっていれば、無視する

		Conflict = pPlayer->Act->ConflictOBB( CatapultData[i].CatapultID);
		//ech = E3DChkConflictOBB( pPlayer->Get_BodyModel(), -1, CatapultData[i].CatapultID, -1, &Conflict, &Garbage);
		
		if( Conflict == 1){// 衝突を検知したら

			ech = E3DGetPos( CatapultData[i].CatapultID, &CatPos);
			_ASSERT( ech != 1 );//エラーチェック

			pPlayer->JumpPosition( CatPos, CatapultData[i].Degree, CatapultData[i].UpAcceleration, CatapultData[i].Speed);
		}
	}



	return 0;
}