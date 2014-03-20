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


/* オペレーションミッション1「新緑の少女」についての処理を行ないます */
int Operation::OpsMission1_Shinryoku(){

	
		/* クラスの実体化を行う */
		PlayerChara Player(1,0);
		Stage Stg;
		Enemy Ene;

		E3DCreateProgressBar();// プログレスバーを作ります
		/**/E3DSetProgressBar( 10);// プログレスバーを進歩させる

		System::SetUpdataSoundSys( 1);// 音声情報フラグをオンにする

		/**/E3DSetProgressBar( 20);// プログレスバーを進歩させる
	
		/* Weapon関係処理 */		
		Player.Wpn.GunLoad(0,4,0);// 銃のロード
		Player.Wpn.GunLoad(1,1,0);// 銃のロード
		Player.Wpn.SetInitWeaponData();// 弾薬の初期化

		/**/E3DSetProgressBar( 40);// プログレスバーを進歩させる

		Stg.LoadStage(6,0,0);// ステージをロードします
		/**/E3DSetProgressBar( 60);// プログレスバーを進歩させる
		Ene.LoadEnemyModel( -1, 0);// 敵をロードします

		/**/E3DSetProgressBar( 90);// プログレスバーを進歩させる

		Batch_Preparat BatP( &Player, &Stg, &Ene, &Cam);// バッチプレパラートにすべての描画準備をさせます。

		E3DDestroyProgressBar();// プログレスバーを壊します		

		System::MsgQ(30);//メッセージループ
		SetCursorPos( System::rewin.left + 320, System::rewin.top + 240);//マウスをウィンドウ真ん中に設置
		System::MsgQ(30);//メッセージループ


		
		BatP.BatchChkInView();
		D3DXVECTOR3 GroundOnPos( 0.0, 10000.0, 0.0);//
		E3DSetPos( Player.cha_hsid[0], GroundOnPos);
		



		while( WM_QUIT != System::msg.message ){

				System::MsgQ(30);//メッセージループ

				//とりあえずここに書いてみる、後で複雑にいりこませる。
				//変数の宣言
				int ech = 0;//エラーチェック用の変数宣言
				int ScreenPosArray[2];



				System::KeyRenewal( Player.Wpn.GetWeaponData( Player.Wp_equipment, 7) + 1);
				BatP.BatchChkInView();
				Player.Wpn.ChkWeaponLaunch( Player.Wp_equipment);

				Player.NormallyPCSystem( &Stg, &BatP, &Ene, &Cam, ScreenPosArray);
				Player.Wpn.AttackEnemy( &Ene, &Player, ScreenPosArray, &Stg);
				Ene.MoveEnemys( &Stg);

				BatP.BatchSpriteSet( &Player);
				BatP.BatchRender( 0);
				Player.Wpn.TreatmentWhileGame( Player.Wp_equipment);
				BatP.BatchSpriteRender( 0);
				BatP.BatchFont( 1, &Player);


				ech = E3DPresent( System::scid1);
				if(ech != 0){//エラーチェック
							_ASSERT(0);//エラーダイアログを表示
				};

				Menu.FarstInMenu( &BatP, &Player);
				BatP.BatchBeforePos();
				Player.ShoulderGunSysBefore();

				//netP.NetMessage();
		}



	return 0;
}