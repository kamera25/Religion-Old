/*ここは、ネット接続に関することのクラスです。
//主に接続準備、通信開始について書かれています。
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ
#include "cnetplay.h"//ネットワーク接続に関するヘッダファイル


/*コンストラクタ、接続準備をします*/
NetPlay::NetPlay( int NetMode){
/*
	//変数の宣言
	int ech = 0;//エラーチェック用の変数宣言
	SwitchNetWork = 1;

	//メンバ変数の初期化
	for( int i=0; i<16; i++){
			ClientDPNID[i] = 0;
	}

	if( NetMode == 0){

			ech = gHost( "NETTEST" , 50000 , 0 , 0 );
			if(ech != 0){//エラーチェック
						_ASSERT(0);//エラーダイアログを表示
						SwitchNetWork = 0;
						return;
			};
	}
	if( NetMode == 1){
			ech = gConnect( "127.0.0.1" , 50000 ,  0, 0 );
			if(ech != 0){//エラーチェック
						_ASSERT(0);//エラーダイアログを表示
						SwitchNetWork = 0;
						return;
			};
	}

	/*自分のDPNIDを取得する*/
/*	MyDPNID = gGetMyDPNID();

	/*接続台数を制限する*/
	/*ech = gSetMaxPlayers( 16);
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
				return;
	};

	*/

	return;
};
/*デストラクタ、ネットワークから切断をします*/
NetPlay::~NetPlay(){

	//変数の宣言
	int ech = 0;//エラーチェック用の変数宣言

	//ech = gDisConnect();
	if(ech != 0){//エラーチェック
				_ASSERT(0);//エラーダイアログを表示
				return;
	};

	return;
}
/*ネットワークから接続されているか、確認します*/
int NetPlay::NetMessage(){

	//変数の宣言
	int ech = 0;
	int DataOnSys = 0;
	int NetData = 0;
	int DPNID = 0;
	char Mes[256] = "";// 着いたメッセージ配列を代入

	while( 1 ){//
			if( SwitchNetWork == 1){//ネットワーク関連命令を実行して良いなら

					/*データが届いているかチェックします*/
			//		DataOnSys = gCheckBufferText();
					if(DataOnSys < 0){//エラーチェック
								_ASSERT(0);//エラーダイアログを表示
								return 1;
					}
					else if( DataOnSys == 0){//受信データがなしなら
							break;//ループから抜ける
					}

					/*もしデータが届いていれば*/
					if( 0 < DataOnSys ){
		//					ech = gGetText( Mes, 256);
							if(ech < 0){//エラーチェック
										_ASSERT(0);//エラーダイアログを表示
										return 1;
							};

							//もしそれが、何らかのメッセージだった場合
			//				NetData = gMessageToID( Mes);
							if( NetData == 0x0001 ){//メッセージが「接続開始」なら

//									ech = gGetText( Mes, 256);//DPNIDを取得します
									if(ech < 0){//エラーチェック
												_ASSERT(0);//エラーダイアログを表示
												return 1;
									};

									//文字列を数字に変換
									DPNID = atoi( Mes);

									//自分のDPNIDと違うなら
									if( DPNID != MyDPNID){
										for( int i=0; i<16; i++){//16回確認
											if( ClientDPNID[i] == 0){//空きのネットワークスペースが有れば
													ClientDPNID[i] = DPNID;//代入
													break;
											}
										}
									}
							}
							if( NetData== 0x0002){//メッセージが「クライアントが切断」なら

//									ech = gGetText( Mes, 256);//DPNIDを取得します
									if(ech < 0){//エラーチェック
												_ASSERT(0);//エラーダイアログを表示
												return 1;
									};

									//文字列を数字に変換
									DPNID = atoi( Mes);

									for( int i=0; i<16; i++){//16回確認
										if( ClientDPNID[i] == DPNID){//該当DPNIDがあれば
													ClientDPNID[i] = 0;//削除命令
													break;
										}
									}
							}
							if( NetData== 0x0004){//メッセージが「ホストから切断」なら

									for( int i=0; i<16; i++){//16回
												ClientDPNID[i] = 0;//削除命令
									}

									//ネットワークモードを終了させる
									SwitchNetWork = 0;
							}
					}
			}
			else{//ネットワークモードが利用できない
					break;//ループから抜ける
			}
	}



	return 0;
}