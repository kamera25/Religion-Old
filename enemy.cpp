#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <usercoef.h>//Easy3Dで必要な追加ヘッダ
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "resource1.h"//リソースファイルとかの関連付けヘッダ
#include <string.h>//文字列操作で必要
#include <math.h>//数学計算で使用
#include <stdlib.h>//乱数を作るためのヘッダ

#include "difine.h"


int Eneinfo[20][5];

int Eneload(){
	//敵をロードするよ

	int Enekind = 3;
	int Eneno = 0;
	int ech;
	char loadname[MAX_PATH] = "";
	int Enenow = Iinfo[4][0];


	/*
	
	Eneinfoの説明

	0:敵の属性 1:敵の番号 2:モデル番号 3:必殺部位

	*/

	Eneinfo[(Iinfo[4][0])][0] = Enekind;
	Eneinfo[(Iinfo[4][0])][1] = Eneno;

	if(Enekind ==3){//無機物
		if(Eneno == 0){//もし箱をロードするなら

						wsprintf( loadname, "%s\\3d\\enemy\\Enecube.sig", pat);//前とった実行中のパスとsig名登録
						ech = E3DSigLoad( loadname, 0, 5, &Eneinfo[Enenow][2]);//モデルの読み込み、Iinfoへモデルを入れる。
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
									return 1;//問題ありで終了
						};
						E3DGetPartNoByName ( Eneinfo[Enenow][2], "必殺部位", &Eneinfo[Enenow][3]);//クリティカルが出る部位を設定
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
									return 1;//問題ありで終了
						};

		}

	}




	Iinfo[4][0]++;//敵の総数に足す


	return 0;
}