#pragma once
/*
 *  初期化・終了・プロージャーに渡すという行為を行うクラスヘッダファイルです。
 */



//ここにある関数を宣言。
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);//プロージャーの登録
class Weapon_Head;

//初期化と終了処理
class System{

private:

	//変数の宣言
	static int UpdataSoundflag;//音声情報を更新するかのフラグ
	static bool keyin[20];//キーが押されているかの情報配列
	static int scid2;// フェードアウトで使うスワップチェイン
	static int KeyQuickPush[3][3];//キーを2回連打したときの情報を入れる変数

	HINSTANCE hInst;//ハンドルインスタンスを格納する。
	static BOOL GotMes;//PeekMessageの状態を格納する。

	
	//関数の宣言
	static int ChkKeyDoublePush( bool PushKey, int Count, int Element);	
	int Intialize( hInst, hwnd);// 初期化
	int Start();// ゲーム開始

public:
	//変数の宣言

	static int scid1;//メインスワップチェインのID
	static int KeyQuickEnd;//ダッシュ操作が終了したときすべてのプッシュをリセットするフラグ変数
	static int MouseWhole;//マウスホイールの移動量を格納する変数

	static int SpriteID[2];//ロードしたスプライトを格納します

	static char path[256];//プログラムが起動しているパスの文字列

	static MSG msg;//メッセージを格納する構造体。
	static HWND hwnd;//ハンドルウィンドウを格納する。
	static RECT rewin;//4隅座標の構造体
	static POINT MousePos;//マウスの位置を格納するPoint構造体
	static POINT BeforeMousePos;//前回のマウスの位置を格納する構造体

	/*　静動変数  */
	/* モード0でのキー番号定数 */
	static const int KEY_ENTER = 0;
	static const int KEY_BACKSPACE = 1;// バックスペース
	static const int KEY_LEFT = 2;// ←
	static const int KEY_UP = 3;// ↑
	static const int KEY_RIGHT = 4;// →
	static const int KEY_DOWN = 5;// ↓

	/* モード1でのキー番号定数 */
	// static const int KEY_ENTER = 0;// エンター ! 1で既に定義済み !
	static const int KEY_W = 1;// Wキー
	static const int KEY_D = 2;// Dキー
	static const int KEY_S = 3;// Sキー
	static const int KEY_R = 4;// Rキー
	static const int KEY_E = 5;// Eキー
	static const int KEY_Q = 6;// Qキー
	static const int KEY_Z = 7;// Zキー
	static const int KEY_SHIFT = 8;// シフトキー
	static const int KEY_LEFTMOUSE = 9;// ←クリック
	static const int KEY_RIGHTMOUSE = 10;// →クリック
	static const int KEY_SPACE = 11;// スペースキー
	static const int KEY_A = 12;// Aキー
	static const int KEY_V = 13;// Vキー
	static const int KEY_WHILEMOUSE = 14;// ホイールクリック
	static const int KEY_ESC = 15;// ESCキー
	static const int KEY_F = 16;// Fキー

	//関数の宣言
	System();//コンストラクタ
	~System();//デストラクタ
	static int MsgQ( const int fps);//メッセージのループ処理
	static int KeyRenewal( const int SelectMode);//キー取得命令の関数
	//static int GetKeyData( int *KeyDataArray);//キー情報を入手するための関数
	static int WaitRender();//読み込み中を表示するための関数
	static int SetUpdataSoundSys( const int Soundflag);//音声情報を更新するかどうかの関数
	static int SetFadeOutOfScid( const int FadeTime);//画像をフェードアウトさせる処理の関数
	static int KeyRenewalFromWp( const Weapon_Head *Wpn, const int Equipment);// 今所持している武器からキーの取得をする関数
	static int SetMouseCursol( const int X, const int Y);// マウス座標をセットする関数
	static int SetMouseBeforePos();// 現在のマウス座標をBeforeMousePosにセットする関数
	static bool GetKeyData( const int KeyNum);// キーインプットを取得する関数
	static int Get_DoublePush( int Element);// 要素を渡して、連続押しかどうかチェックします
	static int ResetKeyDoublePush( int Element);// 要素を選択して、二回連続キーの設定リセットを行います。
	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp); // ウィンドウプロージャ

	//フレンド関数宣言
	friend int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd);

};

