#pragma once
/*ここでは、初期化・終了・プロージャーに渡すという行為を行うクラスヘッダファイルです。
//
*/
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。


//ここにある関数を宣言。
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);//プロージャーの登録


//初期化と終了処理
class System{

private:
	//変数の宣言
	HINSTANCE hInst;//ハンドルインスタンスを格納する。
	BOOL GotMes;//PeekMessageの状態を格納する。
	int keydata1[30][2];//キーのデータを入れている配列変数の一つ目
	int keydata2[30][2];//キーのデータを入れている配列変数の二つ目

public:
	//変数の宣言
	RECT rewin;//4隅の状態の構造体？
	int scid1;//メインスワップチェインのID
	char path[256];//プログラムが起動しているパスの文字列
	MSG msg;//メッセージを格納する構造体。
	HWND hwnd;//ハンドルウィンドウを格納する。


	int keyBox1[30][2];
	int keyBox2[30][2];
	int keyin[20];
	int keyinQuick[3];//キーが2押されたか格納する配列変数
	int KeyQuickPush[3][3];//キーを2回連打したときの情報を入れる変数
	int KeyQuickEnd;//ダッシュ操作が終了したときすべてのプッシュをリセットするフラグ変数
	int MouseWhole;//マウスホイールの移動量を格納する変数

	POINT MousePos;//マウスの位置を格納するPoint構造体
	POINT BeforeMousePos;//前回のマウスの位置を格納する構造体

	int SpriteID[1];//ロードしたスプライトを格納します
	
	//関数の宣言
	System( HINSTANCE hInst, HWND hwnd, char runpath[256]);//コンストラクタ
	~System();//デストラクタ
	int MsgQ(int fps);//メッセージのループ処理
	int Keyget(int SelectMode);//キー取得命令の関数
	int WaitRender();//読み込み中を表示するための関数


};

