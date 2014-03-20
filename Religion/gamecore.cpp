/*ここでは、ゲームメインループを作り、および各システムを呼び出します。
//
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ
#include "cstage.h"//ステージ関係のクラスヘッダファイル
#include "clive.h"//敵やキャラのクラスヘッダファイル
#include "c_batch_preparat.h"//描画に必要なクラスの宣言ヘッダファイル
#include "cmenu.h"//メニュークラスに関するヘッダファイル
#include "cenemy.h"//敵クラスの宣言ヘッダファイル


//ここで使うグローバル変数を宣言
extern System *sys;//システムクラスを指す、クラスのポインタ


//ゲームをスタートします。
int GMStart(){

	sys->WaitRender();//読み込み画面を表示させます
	E3DCreateProgressBar();//プログレスバーを作ります
	
	PlayerChara wfarmy(1,0);
		E3DSetProgressBar( 20);//プログレスバーを進歩させる
	wfarmy.GunLoad(0,4,0);
	wfarmy.GunLoad(1,1,0);
		E3DSetProgressBar( 40);//プログレスバーを進歩させる
	Stage trm;
	trm.LoadStage(3,0,0);
		E3DSetProgressBar( 80);//プログレスバーを進歩させる
	Enemy ene;
	ene.LoadEnemyModel( -1, 0);
		E3DSetProgressBar( 90);//プログレスバーを進歩させる
	Camera cam;
	Batch_Preparat bp( &wfarmy, &trm, &ene, &cam);
	Menu menu;


	E3DDestroyProgressBar();//プログレスバーを壊します

	sys->MsgQ(30);//メッセージループ
	SetCursorPos( sys->rewin.left + 320, sys->rewin.top + 240);//マウスをウィンドウ真ん中に設置
	sys->MsgQ(30);//メッセージループ

	/**/
	D3DXVECTOR3 GroundOnPos( 23000.0, 1200.0, 0.0);//
	E3DSetPos( wfarmy.cha_hsid[0], GroundOnPos);
	/**/



	do{

		//とりあえずここに書いてみる、後で複雑にいりこませる。
		//変数の宣言
		int ech = 0;//エラーチェック用の変数宣言

		sys->Keyget(1);
		bp.BatchChkInView();

		//wfarmy.ThirdGunSys( &trm, &bp);
		wfarmy.NormallyPCSystem( &trm, &bp, &ene, &cam);

		ene.MoveEnemys( &trm);

		bp.BatchSpriteSet( &wfarmy);
		bp.BatchRender( 0);
		bp.BatchSpriteRender( 0);
		bp.BatchFont( 1);

		ech = E3DPresent( sys->scid1);
		if(ech != 0){//エラーチェック
					_ASSERT(0);//エラーダイアログを表示
		};

		menu.FarstInMenu( &bp, &wfarmy);


		bp.BatchBeforePos();
		wfarmy.ShoulderGunSysBefore();

		sys->MsgQ(30);//メッセージループ

	}while( WM_QUIT != sys->msg.message );



	return 0;
}