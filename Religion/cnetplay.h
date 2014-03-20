/*ここは、ネット接続に関することのヘッダクラスファイルです。
//
*/



//ここにグローバル変数を宣言
extern System *sys;//システムクラスを指す、クラスのポインタ

class NetPlay{
private:

	//変数の宣言
	int MyDPNID;//自分のDPNIDを代入します
	int ClientDPNID[16];//他の人のDPNIDを代入します
	int SwitchNetWork;//ネットワーク関連を実行してもよいかのフラグ

public:

	//関数の宣言
	NetPlay( int NetMode);//コンストラクタ、接続準備をします
	~NetPlay();//デストラクタ、ネットワークから切断をします

	int NetMessage();//ネットワークから接続されているか、確認します

};