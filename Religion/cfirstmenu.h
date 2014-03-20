#pragma once
/*メインメニューに関することのヘッダファイル
//
*/


//メインメニュークラス
class MainMenu{
private:

		int MainBGImg;//メインメニューの後ろの画像
		int PushKeyImg;//
		int MenuSelectImg[5];//メニューで使うスプライト画像

public:

		int InMainMenu();//最初のメニューの処理を行います
		MainMenu();//コンストラクタ、
		~MainMenu();//デスコントラクタ、


};