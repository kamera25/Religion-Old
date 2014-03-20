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
#include "citem.h"//アイテムの宣言ヘッダファイル
#include "Ask.h"// 通信補助DLL、Askに関するヘッダファイル

/* ゲーム本体のまとめ構造体 */
typedef struct GameManage{
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
		GMG.PC->Wpn.SetInitWeapon( -1);// 弾薬の初期化

		/* プログレスバーを進歩させる */
		E3DSetProgressBar( 40); 
		
		/* ステージをロードします */
		Stg.LoadStage( 3, 0, Stage::Night);

		/**/E3DSetProgressBar( 60);// プログレスバーを進歩させる

		/* 敵の設定 */

		for( int i=0; i<5; i++){
			GMG.NPC_H->LoadEnemyModelAddName( EnemyNames[i], 0, 0);// 敵をロードします
		}

		GMG.NPC_H->SetEnemyPosByNaviPointArray( &Stg, EnemyNames[0], EnemyOnNaviLine, EnemyOnNaviPoint, 5);//敵の座標を設定
		/* 敵の設定ここまで */


		/**/E3DSetProgressBar( 90);// プログレスバーを進歩させる

		Batch_Render BatP( &Player, &Stg, GMG.NPC_H, &Cam);// バッチプレパラートにすべての描画準備をさせます。
		E3DDestroyProgressBar();// プログレスバーを壊します		
		BatP.BatchEnableBumpMap(0);// バンプマップを有効にします 
		//BatP.BatchCreateShadow();// 影を有効にします

		System::SetMouseCursol( 320, 240);//マウスをウィンドウ真ん中に設置


		BatP.BacthGunTrade( Player.Get_Wp_equipment());
		BatP.BatchChkInView();
		D3DXVECTOR3 GroundOnPos( 0.0, 10000.0, 0.0);
		E3DSetPos( Player.Get_BodyModel(), GroundOnPos);
		



		while( WM_QUIT != System::msg.message ){

				System::MsgQ(30);//メッセージループ
				System::KeyRenewalFromWp( &Player.Wpn, Player.Get_Wp_equipment());


				BatP.BatchChkInView();
				Player.Wpn.ChkWeaponsLaunch( Player.Get_Wp_equipment());

				Player.NormallyPCSystem( &Stg, &BatP, GMG.NPC_H, &Cam, ScreenPosArray);
				Player.Wpn.AttackEnemys( GMG.NPC_H, &Player, ScreenPosArray, &Stg);
				GMG.NPC_H->MoveEnemys( &Stg);

				BatP.BatchSpriteSet( &Player);
				BatP.BatchRender( 0);
				Player.Wpn.WeaponsTreatment( Player.Get_Wp_equipment(), &Stg);
				BatP.BatchSpriteRender( 0);
				BatP.BatchFont( 1, &Player);


				BatP.Batch_Present();

				Menu.FarstInMenu( &BatP, &Player);
				BatP.BatchBeforePos();
				Player.Batch_PeopleMotion();

		}



	return 0;
}