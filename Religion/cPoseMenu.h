#pragma once
/*ここでは、ゲーム中のメニューに関することのクラスヘッダです。
//主にポーズメニュークラスとドッグメニュークラスについて書かれています。
*/
#include "cMenu.h"

//プロトタイプ宣言
class Batch_Render;
class PlayerChara;
class Weapon;
class Item;


class PoseMenu: public Menu{

public:

	int MenuEvent;// メニューのイベントを戻り値として受け取ります

	//関数の宣言
	PoseMenu();//コンストラクタ、メニュー画面で使うスプライトをロードします
	virtual ~PoseMenu();//デコントラクタ、メニュー画面で使ったスプライトなどを削除します
	int FarstInMenu( Batch_Render *BatchPre, PlayerChara *PC);//メニュー画面に入って、自動的に通常描画モードからメニュー画面に半透過していきます。
	int MainPoseMenu( PlayerChara *PC, Batch_Render *BatchPre);//ポーズメニューに入ります、必要最低限のメニューです。
	int PutStetus( PlayerChara *PC);//下のステータスの表示
	int EventPublish();// イベントを発行します

};