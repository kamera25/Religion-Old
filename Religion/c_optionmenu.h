/*ここでは、オプションメニューに関することのクラスソースファイルです。
//
*/
#include "cMenu.h"
class Batch_Render;


class OptionMenu: public Menu{

private:

	// 変数の宣言

public:

	// 関数の宣言
	OptionMenu();// コンストラクタ、画像のロードなどを行ないます。
	~OptionMenu();// デストラクタ、画像の破棄などを行ないます
	int MainOptionMenu( Batch_Render *BatchPre);// オプションメニューの中央処理を行ないます

};