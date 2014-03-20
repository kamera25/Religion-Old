/*ここでは、オプションメニューに関することのクラスソースファイルです。
//
*/
class Batch_Render;


class OptionMenu{

private:

	// 変数の宣言
	int TextID[3];
	int MenuSpriteIDs[10];

public:

	// 関数の宣言
	OptionMenu();// コンストラクタ、画像のロードなどを行ないます。
	~OptionMenu();// デストラクタ、画像の破棄などを行ないます
	int MainOptionMenu( Batch_Render *BatchPre);// オプションメニューの中央処理を行ないます

};