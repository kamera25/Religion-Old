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
	static int UpdataSoundflag;//音声情報を更新するかのフラグ
	static int keydata1[30][2];//キーのデータを入れている配列変数の一つ目
	static int keydata2[30][2];//キーのデータを入れている配列変数の二つ目
	static int keyin[20];//キーが押されているかの情報配列
	static int keyBox1[30][2];//動的に取得したキー情報を入れる配列
	static int keyBox2[30][2];
	static int scid2;// フェードアウトで使うスワップチェイン

	HINSTANCE hInst;//ハンドルインスタンスを格納する。
	static BOOL GotMes;//PeekMessageの状態を格納する。

public:
	//変数の宣言

	static int scid1;//メインスワップチェインのID
	static int keyinQuick[3];//キーが2押されたか格納する配列変数
	static int KeyQuickEnd;//ダッシュ操作が終了したときすべてのプッシュをリセットするフラグ変数
	static int MouseWhole;//マウスホイールの移動量を格納する変数
	static int KeyQuickPush[3][3];//キーを2回連打したときの情報を入れる変数
	static int SpriteID[2];//ロードしたスプライトを格納します

	static char path[256];//プログラムが起動しているパスの文字列

	static MSG msg;//メッセージを格納する構造体。
	static HWND hwnd;//ハンドルウィンドウを格納する。
	static RECT rewin;//4隅座標の構造体
	static POINT MousePos;//マウスの位置を格納するPoint構造体
	static POINT BeforeMousePos;//前回のマウスの位置を格納する構造体

	//関数の宣言
	System( HINSTANCE hInst, HWND hwnd);//コンストラクタ
	~System();//デストラクタ
	static int MsgQ( const int fps);//メッセージのループ処理
	static int KeyRenewal( const int SelectMode);//キー取得命令の関数
	static int GetKeyData( int *KeyDataArray);//キー情報を入手するための関数
	static int WaitRender();//読み込み中を表示するための関数
	static int SetUpdataSoundSys( const int Soundflag);//音声情報を更新するかどうかの関数
	static int SetFadeOutOfScid( const int FadeTime);//画像をフェードアウトさせる処理の関数


};

