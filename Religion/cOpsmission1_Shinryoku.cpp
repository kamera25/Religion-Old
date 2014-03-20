/* オペレーションミッション関数系の一部である、この"cOpsmission1_Shinryoku.cpp"コードは
// ミッション「新緑のブレスレッド」についてのことが書かれています。
/* /////////////////////////////////////////////////////////////////////////// */

#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "coperation.h"//オペレーション開始関係のクラスヘッダファイル
#include "clive.h"//敵やキャラの宣言ヘッダファイル
#include "cweapon.h"//武器に関することのクラスヘッダファイル
#include "cstage.h"//ステージ関係のクラスヘッダファイル
#include "cenemy.h"//敵クラスの宣言ヘッダファイル
#include "ccamera.h"//カメラ関係のクラスヘッダファイル
#include "c_batch_preparat.h"//描画に必要なクラスの宣言ヘッダファイル
#include "cPoseMenu.h"//メニュークラスに関するヘッダファイル
#include "cnetplay.h"//ネットワーク接続に関するヘッダファイル
#include "citem.h"//アイテムの宣言ヘッダファイル]
#include "cStory.h"
#include "Ask.h"// 通信補助DLL、Askに関するヘッダファイル

/* ゲーム本体のまとめ構造体 */
struct GameManage{
	PlayerChara *PC;
	Stage *STG;
	NPC_Head *NPC_H;
};


/* オペレーションミッション1「新緑の少女」についての処理を行ないます */
int Operation::OpsMission1_Shinryoku(){

		/* 定数の宣言 */
		int ech = 0;//エラーチェック用の変数宣言
		int ScreenPosArray[2] ={0};
		const int EnemyOnNaviLine[6] = { 2, 1, 1, 0, 0};
		const int EnemyOnNaviPoint[6] = { 17, 10, 6, 3, 1};
		const char EnemyNames[6][20] = { "WF0", "WF1", "WF2", "WF3", "WF4", "WF5"} ;
		GameManage GMG;//まとめ構造体

		/* プログレスバーを作ります */
		E3DCreateProgressBar();

		/* クラスの実体化を行う */
		PlayerChara Player(1,1);
		pPly = &Player;
		Stage Stg;
		NPC_Head Npc_h;


		/* まとめ構造体に代入 */
		GMG.PC = &Player;
		GMG.STG = &Stg;
		GMG.NPC_H = &Npc_h;

		/* プログレスバーを進歩させる */
		E3DSetProgressBar( 10);

		/* 音声情報フラグをオンにする */
		System::SetUpdataSoundSys( 1);

		/**/E3DSetProgressBar( 20);// プログレスバーを進歩させる
	
		/* Weapon関係処理 */		
		GMG.PC->Wpn.WpLoad(1,0,0);// 銃のロード
		GMG.PC->Wpn.WpLoad(0,3,1);// 銃のロード
		GMG.PC->Wpn.WpLoad(2,7,0);// 銃のロード
		GMG.PC->Wpn.SetInitWeapon( Weapon_Head::RESET);// 弾薬の初期化

		/* プログレスバーを進歩させる */
		E3DSetProgressBar( 40); 
		
		/* ステージをロードします */
		Stg.LoadStage( 6, 0, Stage::NIGHT);

		/**/E3DSetProgressBar( 60);// プログレスバーを進歩させる

		/* 敵の設定 */

		for( int i=0; i<5; i++){
			GMG.NPC_H->LoadEnemyModelAddName( EnemyNames[i], 0, 0);// 敵をロードします
		}

//		GMG.NPC_H->SetEnemyPosByNaviPointArray( &Stg, EnemyNames[0], EnemyOnNaviLine, EnemyOnNaviPoint, 5);//敵の座標を設定
		/* 敵の設定ここまで */


		/**/E3DSetProgressBar( 90);// プログレスバーを進歩させる

		Batch_Render BatProc( &Player, &Stg, GMG.NPC_H, &Cam);// バッチプレパラートにすべての描画準備をさせます。
		pBatP = &BatProc;
		
		E3DDestroyProgressBar();// プログレスバーを壊します
		pBatP->BatchEnableBumpMap(0);// バンプマップを有効にします 
		//BatP.BatchCreateShadow();// 影を有効にします

		

		/* ****** ストーリの開始 *** */
		Story StoryS;
		StoryS.LoadStoryFromSTD( "test.std");
		StoryS.StartStory(1);
		/* ************************ */


		System::SetMouseCursol( 320, 240);//マウスをウィンドウ真ん中に設置


		pBatP->BacthGunTrade( Player.Get_Wp_equipment());
		pBatP->BatchChkInView();
		GMG.STG->Navi.SetPosByNaviPoint( Player.Get_BodyModel(), 0, 0);
		

		while( WM_QUIT != System::msg.message ){

				System::MsgQ(30);//メッセージループ
				System::KeyRenewalFromWp( &Player.Wpn, Player.Get_Wp_equipment());


				pBatP->BatchChkInView();

				// 制御関係
				Player.Wpn.ChkWeaponsLaunch( Player.Get_Wp_equipment());
				Player.NormallyPCSystem( &Stg, pBatP, GMG.NPC_H, &Cam, ScreenPosArray);
				Player.Wpn.AttackEnemys( GMG.NPC_H, &Player, ScreenPosArray, &Stg);
				Player.Wpn.WeaponsTreatment( Player.Get_Wp_equipment(), &Stg);
				GMG.NPC_H->MoveEnemys( &Stg);

				// 描画関連
				NormalBatchProces();

				// 後処理関係
				Menu.FarstInMenu( pBatP, &Player);
				pBatP->BatchBeforePos();
				Player.Batch_PeopleMotion();

		}



	return 0;
}