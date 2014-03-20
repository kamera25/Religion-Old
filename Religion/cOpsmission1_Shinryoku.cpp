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

	
			E3DCreateProgressBar();//プログレスバーを作ります
			System::SetUpdataSoundSys( 1);//音声情報フラグをオンにする
	
			PlayerChara wfarmy(1,0);
			/**/E3DSetProgressBar( 20);//プログレスバーを進歩させる
			Weapon weapon;//武器を使えるようにします
			weapon.GunLoad(0,4,0);//銃のロード
			weapon.GunLoad(1,1,0);//銃のロード
			weapon.SetInitWeaponData();//弾薬の初期化

			Item item;// アイテムの実体を作成

			/**/E3DSetProgressBar( 40);//プログレスバーを進歩させる
			Stage trm;
			trm.LoadStage(6,0,0);
			/**/E3DSetProgressBar( 80);//プログレスバーを進歩させる
			Enemy ene;
			ene.LoadEnemyModel( -1, 0);
			/**/E3DSetProgressBar( 90);//プログレスバーを進歩させる
			Camera cam;
			Batch_Preparat bp( &wfarmy, &trm, &ene, &cam, &weapon);
			Menu menu;

	
			//NetPlay netP(0);
	

			E3DDestroyProgressBar();//プログレスバーを壊します

			System::MsgQ(30);//メッセージループ
			SetCursorPos( System::rewin.left + 320, System::rewin.top + 240);//マウスをウィンドウ真ん中に設置
			System::MsgQ(30);//メッセージループ

			/*
			D3DXVECTOR3 GroundOnPos( 18000.0, 300.0, -23000.0);//
			E3DSetPos( wfarmy.cha_hsid[0], GroundOnPos);
			*/



			while( WM_QUIT != System::msg.message ){

					System::MsgQ(30);//メッセージループ

					//とりあえずここに書いてみる、後で複雑にいりこませる。
					//変数の宣言
					int ech = 0;//エラーチェック用の変数宣言
					int ScreenPosArray[2];



					System::KeyRenewal( weapon.GetWeaponData( wfarmy.Wp_equipment, 7) + 1);
					bp.BatchChkInView();
					weapon.ChkWeaponLaunch( wfarmy.Wp_equipment);

					wfarmy.NormallyPCSystem( &trm, &bp, &ene, &cam, &weapon, ScreenPosArray);
					weapon.AttackEnemy( &ene, &wfarmy, ScreenPosArray, &trm);
					ene.MoveEnemys( &trm);

					bp.BatchSpriteSet( &wfarmy, &weapon);
					bp.BatchRender( 0);
					weapon.TreatmentWhileGame( wfarmy.Wp_equipment);
					bp.BatchSpriteRender( 0);
					bp.BatchFont( 1, &wfarmy, &weapon);


					ech = E3DPresent( System::scid1);
					if(ech != 0){//エラーチェック
								_ASSERT(0);//エラーダイアログを表示
					};

					menu.FarstInMenu( &bp, &wfarmy, &weapon, &item);
					bp.BatchBeforePos();
					wfarmy.ShoulderGunSysBefore( &weapon);

					//netP.NetMessage();
			}



	return 0;
}