#pragma once
/*オペレーションモードの関すること定義をするヘッダファイル。
//
*/


/*オペレーションモードクラス*/
class OperationMenu{

private:

	//変数の宣言
	int OpsImgIDs[4];//オペレーションモードの画像を代入する変数
	int OpsBGImg;//オペレーションモードの背景代入します
	int TextID[3];//テキストのフォントデータを格納します

public:

	//変数の宣言




	//関数の宣言
	OperationMenu();//コンストラクタ、画像の読み込みなど
	~OperationMenu();//デスコントラクタ、画像の破棄を行います
	int InOpsMenu();//オペレーションモードの処理を行います

};