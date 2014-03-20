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
#include "cmenu.h"//メニュークラスに関するヘッダファイル
#include "cnetplay.h"//ネットワーク接続に関するヘッダファイル
#include "citem.h"//アイテムの宣言ヘッダファイル
#include "Ask.h"// 通信補助DLL、Askに関するヘッダファイル

/* オペレーションミッション1「新緑の少女」についての処理を行ないます */
int Operation::OpsMission1_Shinryoku(){

		/* 定数の宣言 */
		int ech = 0;//エラーチェック用の変数宣言
		int ScreenPosArray[2] ={0};
		const int EnemyOnNaviLine[6] = { 2, 1, 1, 0, 0};
		const int EnemyOnNaviPoint[6] = { 17, 10, 6, 3, 1};

		/* クラスの実体化を行う */
		PlayerChara Player(1,1);
		Stage Stg;
		Enemy Ene;

		E3DCreateProgressBar();// プログレスバーを作ります
		/**/E3DSetProgressBar( 10);// プログレスバーを進歩させる

		System::SetUpdataSoundSys( 1);// 音声情報フラグをオンにする

		/**/E3DSetProgressBar( 20);// プログレスバーを進歩させる
	
		/* Weapon関係処理 */		
		Player.Wpn.WpLoad(1,0,0);// 銃のロード
		Player.Wpn.SetInitWeapon( -1);// 弾薬の初期化

		/**/E3DSetProgressBar( 40);// プログレスバーを進歩させる

		Stg.LoadStage(6,0,2);// ステージをロードします
		/**/E3DSetProgressBar( 60);// プログレスバーを進歩させる
		for( int i=0; i<5; i++){
			Ene.LoadEnemyModel( 0, 0);// 敵をロードします
		}
		Ene.SetEnemyPosByNaviPointArray( &Stg, EnemyOnNaviLine, EnemyOnNaviPoint, 5);//敵の座標を設定
		



		/**/E3DSetProgressBar( 90);// プログレスバーを進歩させる

		Batch_Render BatP( &Player, &Stg, &Ene, &Cam);// バッチプレパラートにすべての描画準備をさせます。
		E3DDestroyProgressBar();// プログレスバーを壊します		
		BatP.BatchEnableBumpMap(0);// バンプマップを有効にします 
		//BatP.BatchCreateShadow();// 影を有効にします

		SetCursorPos( System::rewin.left + 320, System::rewin.top + 240);//マウスをウィンドウ真ん中に設置



		
		BatP.BatchChkInView();
		D3DXVECTOR3 GroundOnPos( 0.0, 10000.0, 0.0);
		E3DSetPos( Player.Get_BodyModel(), GroundOnPos);
		



		while( WM_QUIT != System::msg.message ){

				System::MsgQ(30);//メッセージループ

			//	if( Player.Get_Wp_equipment() != -1 ) System::KeyRenewal( Player.Wpn.GetWeaponData( Player.Get_Wp_equipment(), 7) + 1);
				/*else*/ System::KeyRenewal(1);
				BatP.BatchChkInView();
				Player.Wpn.ChkWeaponsLaunch( Player.Get_Wp_equipment());

				Player.NormallyPCSystem( &Stg, &BatP, &Ene, &Cam, ScreenPosArray);
				Player.Wpn.AttackEnemys( &Ene, &Player, ScreenPosArray, &Stg);
				Ene.MoveEnemys( &Stg);

				BatP.BatchSpriteSet( &Player);
				BatP.BatchRender( 0);
				Player.Wpn.WeaponsTreatment( Player.Get_Wp_equipment());
				BatP.BatchSpriteRender( 0);
				BatP.BatchFont( 1, &Player);


				BatP.Batch_Present();

				Menu.FarstInMenu( &BatP, &Player);
				BatP.BatchBeforePos();
				Player.Batch_PeopleMotion();

		}



	return 0;
}