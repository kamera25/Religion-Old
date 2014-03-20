/*ここでは、ゲームメインループを作り、および各システムを呼び出します。
//
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "clive.h"//敵やキャラの宣言ヘッダファイル
#include "cweapon.h"//武器に関することのクラスヘッダファイル
#include "cstage.h"//ステージ関係のクラスヘッダファイル
#include "cenemy.h"//敵クラスの宣言ヘッダファイル
#include "ccamera.h"//カメラ関係のクラスヘッダファイル
#include "c_batch_preparat.h"//描画に必要なクラスの宣言ヘッダファイル
#include "cmenu.h"//メニュークラスに関するヘッダファイル
#include "cnetplay.h"//ネットワーク接続に関するヘッダファイル


//ここで使うグローバル変数を宣言
extern System *sys;//システムクラスを指す、クラスのポインタ


//ゲームをスタートします。
int GMStart(){

	sys->WaitRender();//読み込み画面を表示させます
	E3DCreateProgressBar();//プログレスバーを作ります
	sys->SetUpdataSoundSys( 1);//音声情報フラグをオンにする
	
	PlayerChara wfarmy(1,0);
	/**/E3DSetProgressBar( 20);//プログレスバーを進歩させる
	Weapon weapon;//武器を使えるようにします
	weapon.GunLoad(0,4,0);//銃のロード
	weapon.GunLoad(1,1,0);//銃のロード
	weapon.SetInitWeaponData();//弾薬の初期化

	/**/E3DSetProgressBar( 40);//プログレスバーを進歩させる
	Stage trm;
	trm.LoadStage(3,0,2);
	/**/E3DSetProgressBar( 80);//プログレスバーを進歩させる
	Enemy ene;
	ene.LoadEnemyModel( -1, 0);
	/**/E3DSetProgressBar( 90);//プログレスバーを進歩させる
	Camera cam;
	Batch_Preparat bp( &wfarmy, &trm, &ene, &cam, &weapon);
	Menu menu;

	
	//NetPlay netP(0);
	

	E3DDestroyProgressBar();//プログレスバーを壊します

	sys->MsgQ(30);//メッセージループ
	SetCursorPos( sys->rewin.left + 320, sys->rewin.top + 240);//マウスをウィンドウ真ん中に設置
	sys->MsgQ(30);//メッセージループ

	/*
	D3DXVECTOR3 GroundOnPos( 18000.0, 300.0, -23000.0);//
	E3DSetPos( wfarmy.cha_hsid[0], GroundOnPos);
	*/



	do{

		sys->MsgQ(30);//メッセージループ

		//とりあえずここに書いてみる、後で複雑にいりこませる。
		//変数の宣言
		int ech = 0;//エラーチェック用の変数宣言
		int ScreenPosArray[2];



		sys->KeyRenewal( weapon.GetWeaponData( wfarmy.Wp_equipment, 7) + 1);
		bp.BatchChkInView();
		weapon.ChkWeaponLaunch( wfarmy.Wp_equipment);

		wfarmy.NormallyPCSystem( &trm, &bp, &ene, &cam, &weapon, ScreenPosArray);
		weapon.AttackEnemy( &ene, &wfarmy, ScreenPosArray);
		ene.MoveEnemys( &trm);

		bp.BatchSpriteSet( &wfarmy, &weapon);
		bp.BatchRender( 0);
		weapon.TreatmentWhileGame( wfarmy.Wp_equipment);
		bp.BatchSpriteRender( 0);
		bp.BatchFont( 1, &wfarmy, &weapon);


		ech = E3DPresent( sys->scid1);
		if(ech != 0){//エラーチェック
					_ASSERT(0);//エラーダイアログを表示
		};

		menu.FarstInMenu( &bp, &wfarmy, &weapon);
		bp.BatchBeforePos();
		wfarmy.ShoulderGunSysBefore( &weapon);

		//netP.NetMessage();

	}while( WM_QUIT != sys->msg.message );



	return 0;
}