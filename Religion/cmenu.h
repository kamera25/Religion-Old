#pragma once
/*ここでは、ゲーム中のメニューに関することのクラスヘッダです。
//主にポーズメニュークラスとドッグメニュークラスについて書かれています。
*/

//プロトタイプ宣言
class Batch_Preparat;
class PlayerChara;
class Weapon;
class Item;


class Menu{

public:

	//変数の宣言
	int MenuSpriteIDs[4];//メニューでつかうスプライト画像のID配列
	int TextID[2];//文字の識別を格納するID配列

	//アイテム画像の識別変数
	int BackPack_Ammo[4];
	int BackPack_Recovery[5];
	int BackPack_Key[10];
	int BackPack_Weapon[4];
	int BackPack_Equipment[3];



	//関数の宣言
	Menu();//コンストラクタ、メニュー画面で使うスプライトをロードします
	~Menu();//デコントラクタ、メニュー画面で使ったスプライトなどを削除します
	int FarstInMenu( Batch_Preparat *BatchPre, PlayerChara *PC);//メニュー画面に入って、自動的に通常描画モードからメニュー画面に半透過していきます。
	int PoseMenu( PlayerChara *PC, Batch_Preparat *BatchPre);//ポーズメニューに入ります、必要最低限のメニューです。
	int PutStetus( PlayerChara *PC);//下のステータスの表示

};