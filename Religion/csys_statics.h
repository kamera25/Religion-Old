/*
 *  システムクラスの静動変数・関数周りをまとめたヘッダファイル
 */


/* *****************
 * 静動変数の宣言
 * *****************
 */

int System::UpdataSoundflag;//音声情報を更新するかのフラグ
bool System::keyin[20];//キーが押されているかの情報配列
int System::scid2;// フェードアウトで使うスワップチェイン

BOOL System::GotMes;//PeekMessageの状態を格納する。
bool GetKeyData( const int KeyNum);

int System::scid1;//メインスワップチェインのID
int System::keyinQuick[3];//キーが2押されたか格納する配列変数
int System::KeyQuickEnd;//ダッシュ操作が終了したときすべてのプッシュをリセットするフラグ変数
int System::MouseWhole;//マウスホイールの移動量を格納する変数
int System::KeyQuickPush[3][3];//キーを2回連打したときの情報を入れる変数
int System::SpriteID[2];//ロードしたスプライトを格納します

char System::path[256];//プログラムが起動しているパスの文字列

MSG System::msg;//メッセージを格納する構造体。
HWND System::hwnd;//ハンドルウィンドウを格納する。
RECT System::rewin;//4隅座標の構造体
POINT System::MousePos;//マウスの位置を格納するPoint構造体
POINT System::BeforeMousePos;//前回のマウスの位置を格納する構造体