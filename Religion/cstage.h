#pragma once
/*ここでは、ステージの読み込み、制御を行うクラスヘッダファイルです。
//
*/
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。


class Stage{

public:

	//変数の宣言
	int Stage_hsid[3];//ステージモデルのモデルIDを格納します
	int Wall_hsid[3];//壁モデルのモデルIDを格納します
	int Stage_ID;//ステージモデルの振り分けIDを格納します
	int Stage_Kind;//Stage_IDのステージモデルの種類を格納します
	int Stage_GndMode;//地面の判定する時にどのように処理するか識別します
	int Stage_GunTarget;//銃を地面に向ける時にどのように処理するか識別します

	 //ナビライン系
	int NaviLineID;//ナビラインを識別するためのIDを格納します

	int Light1_ID;//一つ目のライトの識別ID
	int Light2_ID;//二つ目のライトの識別ID

	//関数の宣言
	int LoadStage(int StageID, int StageKind, int LightKind);//ステージをロードするための関数
	~Stage();//ステージのデコンストラクタ、マップなどを削除します。


};