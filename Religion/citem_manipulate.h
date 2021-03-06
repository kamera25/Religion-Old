#pragma once
/*ここは、アイテム操作に関することのクラスです。
//主にバックパックやアイテム売買について書かれています。
*/

//プロトタイプ宣言
class PlayerChara;
class Weapon;
class Item;

class Item_Manipulate{

private:

	// 変数の宣言
	int MenuMode;
	POINT ItemSysSetPos;

	//関数の宣言
	int MainBackPack( PlayerChara *PC);//バックパックのメイン処理を行います
	int PutItemDescript( const int ChoseItem, const int ItemNumber);//説明文を表示させる処理を行います
	int PutItemName( const int ChoseItem, const int ItemNumber);//武器アイテム名を表示させる処理を行います
	int PutBackPackText( int *ChoseItem, int *ExitFlag);//アイテム種類のメニューの表示・選択を行います
	int PutItemSprite( const int ChoseItem, const int MenuMode, const POINT ItemSysSetPos);//アイテム画像の表示、制御を行ないます
	int ItemUsingSystem( const int ChoseItem);// アイテムを使う、削除、確認などを行ないます

public:

	//アイテム画像の識別変数
	int BackPack_Ammo[4][2];
	int BackPack_Recovery[5][2];
	int BackPack_Key[10][2];
	int BackPack_Weapon[4][3];
	int BackPack_Equipment[3][2];


	int TextID[3];
	int MenuSpriteIDs[10];

	//関数の宣言
	Item_Manipulate( PlayerChara *PC);//コンストラクタ、アイテムのスプライトなどをロードします
	~Item_Manipulate();//デコントラクタ、ロードしたスプライトなどを削除します
	int InItemPack( PlayerChara *PC);//アイテム処理に入る画像処理などを行います



};