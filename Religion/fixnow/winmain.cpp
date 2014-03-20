/*ここでは、アプリケーションの基礎を作成しWinMainを作成し次へ関数を渡す作業をします。
//
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include <cstring>//文字列操作で使うヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ


//WinMain関数作成
int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd){

	System system;
	system -> Intialize( hInst);//E3D環境作成
	system -> Start();//ゲームをスタートします。ようこそ、Religionへ。


	return 0;
};
