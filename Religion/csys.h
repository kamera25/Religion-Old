#pragma once
/*ここでは、初期化・終了・プロージャーに渡すという行為を行うクラスヘッダファイルです。
//
*/



//ここにある関数を宣言。
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);//プロージャーの登録


//初期化と終了処理
class System{

private:

	//変数の宣言
	int UpdataSoundflag;//音声情報を更新するかのフラグ
	int keydata1[30][2];//キーのデータを入れている配列変数の一つ目
	int keydata2[30][2];//キーのデータを入れている配列変数の二つ目
	int keyin[20];//キーが押されているかの情報配列
	int keyBox1[30][2];//動的に取得したキー情報を入れる配列
	int keyBox2[30][2];

	HINSTANCE hInst;//ハンドルインスタンスを格納する。
	BOOL GotMes;//PeekMessageの状態を格納する。

public:
	//変数の宣言

	int scid1;//メインスワップチェインのID
	int keyinQuick[3];//キーが2押されたか格納する配列変数
	int KeyQuickEnd;//ダッシュ操作が終了したときすべてのプッシュをリセットするフラグ変数
	int MouseWhole;//マウスホイールの移動量を格納する変数
	int KeyQuickPush[3][3];//キーを2回連打したときの情報を入れる変数
	int SpriteID[1];//ロードしたスプライトを格納します

	char path[256];//プログラムが起動しているパスの文字列

	MSG msg;//メッセージを格納する構造体。
	HWND hwnd;//ハンドルウィンドウを格納する。
	RECT rewin;//4隅座標の構造体
	POINT MousePos;//マウスの位置を格納するPoint構造体
	POINT BeforeMousePos;//前回のマウスの位置を格納する構造体

	//関数の宣言
	System( HINSTANCE hInst, HWND hwnd, char runpath[256]);//コンストラクタ
	~System();//デストラクタ
	int MsgQ(int fps);//メッセージのループ処理
	int KeyRenewal( int SelectMode);//キー取得命令の関数
	int GetKeyData( int *KeyDataArray);//キー情報を入手するための関数
	int WaitRender();//読み込み中を表示するための関数
	int SetUpdataSoundSys( int Soundflag);//音声情報を更新するかどうかの関数


};

