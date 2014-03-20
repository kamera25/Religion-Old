/*ここでは、生物クラスのキャラ・敵の関数を定義するクラスコードファイルです。
//特にゲームを開始する時に必要な関数が多く書かれています。
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "clive.h"//敵やキャラの宣言ヘッダファイル





/*プレイヤーキャラクターのコンストラクタ*/
/*プレイヤーキャラクターのデコンストラクタ*/
PlayerChara::~PlayerChara(){

	int ech = 0;//エラー確認変数の初期化

	//キャラクターモデルを削除します
	E3DDestroyHandlerSet( Get_BodyModel());
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	//1つ目のキャラクターダミーモデルを削除します
	E3DDestroyHandlerSet( Get_DummyModel());
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/**/
	//クォータニオンを削除します
	/**/	
	for(int i = 0; i<4; i++){
				ech = E3DDestroyQ( Get_Quaternion(i));
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};
	}


}