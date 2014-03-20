/*ここは、アイテムに関することのクラスのヘッダです。
//ゲーム中でのアイテム全般について書かれています。
*/



/* アイテムクラス */
class Item{

private:
	int BringWp;//ステージで拾った武器
	int Ammo[4];//手持ちの弾薬データを格納
	int Recovery[5][2];//手持ちの回復アイテムデータの格納
	int Key[10];//手持ちの回復アイテムデータの格納
	int Equipment[3];//手持ちの装備アイテムデータの格納


public:

	/* 関数の宣言 */
	Item();//コンストラクタ、初期動作を行ないます
	int GetItemNumber( int ItemKind, int ItemEle1, int ItemEle2);// 格納されているアイテムナンバーを取得します


};