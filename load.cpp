//インクルードするファイル↓

#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <usercoef.h>//Easy3Dで必要な追加ヘッダ
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "resource1.h"//リソースファイルとかの関連付けヘッダ
#include <string.h>//文字列操作で必要

#include "difine.h"


//グローバル変数の宣言

int wpitem[10][10][10];//銃器配列
int lddata[100];
int modelId[30];
int motionId[30];
int QId[30];
int BoneId[30];
int litid1;
int litid2;
int opimg;
int grd1;
int wal1;
int wpbone[30][15];
int Iinfo[5][15];
int FontID[5];


//ロード関数の作成

int firstload(){
	
	//初期化
	char loadname[MAX_PATH] = "";
	int ech;
	int mult;
	int mov;


	//3Dモデルのロード


	//手関連

	wsprintf( loadname, "%s\\3d\\model\\hand\\hand.sig", pat);//前とった実行中のパスとsig名登録
	ech = E3DSigLoad( loadname, 0, 0.4, &modelId[0]);//モデルの読み込み、hsid1へモデルを入れる。
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wsprintf( loadname, "%s\\3d\\model\\hand\\wait.qua", pat);//前とった実行中のパスとsig名登録
	ech = E3DAddMotion( modelId[0], loadname, 1.0, &motionId[0], &mult);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};


	 //アーティー関連
	



	wsprintf( loadname, "%s\\3d\\model\\demo\\hito.sig", pat);//前とった実行中のパスとsig名登録
	ech = E3DSigLoad( loadname, 0, 2.0, &modelId[1]);//モデルの読み込み、hsid1へモデルを入れる。
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};





	  //その他必要なもの

	//サブモデルのロード ！10と12です！
	wsprintf( loadname, "%s\\3d\\model\\other\\demo.sig", pat);//前とった実行中のパスとsig名登録
	ech = E3DSigLoad( loadname, 0, 0.3, &modelId[10]);//モデルの読み込み、hsid1へモデルを入れる。
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wsprintf( loadname, "%s\\3d\\model\\other\\demo.sig", pat);//前とった実行中のパスとsig名登録
	ech = E3DSigLoad( loadname, 0, 1.0, &modelId[12]);//モデルの読み込み、hsid1へモデルを入れる。
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	//当たり判定モデルのロード
	wsprintf( loadname, "%s\\3d\\model\\demo\\hitber.sig", pat);//前とった実行中のパスとsig名登録
	ech = E3DSigLoad( loadname, 0, 200.0, &modelId[11]);//モデルの読み込み、hsid1へモデルを入れる。
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};


	 //クオンターニオン、ボーンネームなど


	E3DCreateQ(&QId[0]);//手の銃の向き
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};
	E3DCreateQ(&QId[1]);//銃口の向き
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};
	E3DCreateQ(&QId[2]);//アーティの手のむき
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};
	E3DCreateQ(&QId[3]);//アーティの銃の向き
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};
	E3DCreateQ(&QId[4]);//移動向きを設定するQ
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};


	//ボーン名前


	//手のボーンネーム取得
	E3DGetBoneNoByName( modelId[0], "もち手_X+", &BoneId[0]);//右手の銃手元の位置
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	E3DGetBoneNoByName( modelId[0], "もち手先_X+", &BoneId[1]);//右手の銃先の位置
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	

	//アーティーのボーンネームを取得
	E3DGetBoneNoByName( modelId[1], "手の平→", &BoneId[2]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};



	//////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////


   //スプライトをロード&銃器のデータをロード

	//銃・兵器系


	//弾薬 0:.45ACP 1:22L 2:9mm 3:5.7mm 4:トカレフ弾 5:PMM 6:.357Mag 7:12GAGE 8:10GAGE
	//	   9:5.56mm 10:5.54mm 11:7.62mm 12:矢 13:40mm 14:HEAT 15:4.73


	// S+:3     S:5     A:8		A-:10  B+:13   B:15   B-:18	  C+:25   C:30   C-:35
	// S+:1100  S:1000  A+:800  A:700  B+:600  B:500  B-:450  C+:400  C:350  C-:300




	//ハンドガン


	//M1911
	wsprintf( loadname, "%s\\3d\\weapon\\handgun\\m1911\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[0][0][0]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wpitem[0][0][1] = 0;//弾薬種類
	wpitem[0][0][2] = 100;//威力
	wpitem[0][0][3] = 15;//連射能力
	wpitem[0][0][4] = 450;//射程能力
	wpitem[0][0][5] = 7;//装弾数
	wpitem[0][0][6] = 10;//マガジン

	
	//D.E
	wsprintf( loadname, "%s\\3d\\weapon\\handgun\\de\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[0][1][0]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wpitem[0][1][1] = 0;//弾薬種類
	wpitem[0][1][2] = 100;//威力
	wpitem[0][1][3] = 13;//連射能力
	wpitem[0][1][4] = 400;//射程能力
	wpitem[0][1][5] = 5;//装弾数
	wpitem[0][1][6] = 14;//マガジン


	//Glock95
	wsprintf( loadname, "%s\\3d\\weapon\\handgun\\glock95\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[0][2][0]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wpitem[0][2][1] = 1;//弾薬種類
	wpitem[0][2][2] = 30;//威力
	wpitem[0][2][3] = 3;//連射能力
	wpitem[0][2][4] = 400;//射程能力
	wpitem[0][2][5] = 50;//装弾数
	wpitem[0][2][6] = 5;//マガジン


	//M92F
	wsprintf( loadname, "%s\\3d\\weapon\\handgun\\m92f\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[0][3][0]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wpitem[0][3][1] = 2;//弾薬種類
	wpitem[0][3][2] = 80;//威力
	wpitem[0][3][3] = 10;//連射能力
	wpitem[0][3][4] = 600;//射程能力
	wpitem[0][3][5] = 15;//装弾数
	wpitem[0][3][6] = 6;//マガジン


	//Five-seveN
	wsprintf( loadname, "%s\\3d\\weapon\\handgun\\five-seven\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[0][4][0]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wpitem[0][4][1] = 3;//弾薬種類
	wpitem[0][4][2] = 60;//威力
	wpitem[0][4][3] = 10;//連射能力
	wpitem[0][4][4] = 350;//射程能力
	wpitem[0][4][5] = 17;//装弾数
	wpitem[0][4][6] = 6;//マガジン


	//トカレフ
	wsprintf( loadname, "%s\\3d\\weapon\\handgun\\tokarev\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[0][5][0]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wpitem[0][5][1] = 4;//弾薬種類
	wpitem[0][5][2] = 110;//威力
	wpitem[0][5][3] = 15;//連射能力
	wpitem[0][5][4] = 650;//射程能力
	wpitem[0][5][5] = 8;//装弾数
	wpitem[0][5][6] = 8;//マガジン


	//マカロフ
	wsprintf( loadname, "%s\\3d\\weapon\\handgun\\makarova\\pict.bmp", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[0][6][0]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wpitem[0][6][1] = 5;//弾薬種類
	wpitem[0][6][2] = 90;//威力
	wpitem[0][6][3] = 13;//連射能力
	wpitem[0][6][4] = 600;//射程能力
	wpitem[0][6][5] = 8;//装弾数
	wpitem[0][6][6] = 9;//マガジン


	//PYTHON
	wsprintf( loadname, "%s\\3d\\weapon\\handgun\\python\\pict.bmp", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[0][7][0]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wpitem[0][7][1] = 6;//弾薬種類
	wpitem[0][7][2] = 130;//威力
	wpitem[0][7][3] = 18;//連射能力
	wpitem[0][7][4] = 600;//射程能力
	wpitem[0][7][5] = 6;//装弾数
	wpitem[0][7][6] = 8;//マガジン


	//SauerP22
	wsprintf( loadname, "%s\\3d\\weapon\\handgun\\sauerp226\\pict.bmp", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[0][8][0]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wpitem[0][8][1] = 2;//弾薬種類
	wpitem[0][8][2] = 80;//威力
	wpitem[0][8][3] = 13;//連射能力
	wpitem[0][8][4] = 650;//射程能力
	wpitem[0][8][5] = 15;//装弾数
	wpitem[0][8][6] = 5;//マガジン

	
	//LugerP08
	wsprintf( loadname, "%s\\3d\\weapon\\handgun\\lugerp08\\pict.bmp", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[0][9][0]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wpitem[0][9][1] = 2;//弾薬種類
	wpitem[0][9][2] = 80;//威力
	wpitem[0][9][3] = 8;//連射能力
	wpitem[0][9][4] = 300;//射程能力
	wpitem[0][9][5] = 32;//装弾数
	wpitem[0][9][6] = 2;//マガジン



	//サブマシンガン


	//TMP
	wsprintf( loadname, "%s\\3d\\weapon\\submachinegun\\tmp\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[1][0][0]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wpitem[1][0][1] = 2;//弾薬種類
	wpitem[1][0][2] = 80;//威力
	wpitem[1][0][3] = 8;//連射能力
	wpitem[1][0][4] = 450;//射程能力
	wpitem[1][0][5] = 30;//装弾数
	wpitem[1][0][6] = 5;//マガジン


	//INGLAM
	wsprintf( loadname, "%s\\3d\\weapon\\submachinegun\\inglam\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[1][1][0]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wpitem[1][1][1] = 0;//弾薬種類
	wpitem[1][1][2] = 100;//威力
	wpitem[1][1][3] = 3;//連射能力
	wpitem[1][1][4] = 300;//射程能力
	wpitem[1][1][5] = 20;//装弾数
	wpitem[1][1][6] = 6;//マガジン


	//TEC-9
	wsprintf( loadname, "%s\\3d\\weapon\\submachinegun\\tec-9\\pict.bmp", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[1][2][0]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wpitem[1][2][1] = 2;//弾薬種類
	wpitem[1][2][2] = 80;//威力
	wpitem[1][2][3] = 3;//連射能力
	wpitem[1][2][4] = 300;//射程能力
	wpitem[1][2][5] = 20;//装弾数
	wpitem[1][2][6] = 8;//マガジン


	//UMP
	wsprintf( loadname, "%s\\3d\\weapon\\submachinegun\\ump\\pict.bmp", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[1][3][0]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wpitem[1][3][1] = 0;//弾薬種類
	wpitem[1][3][2] = 100;//威力
	wpitem[1][3][3] = 3;//連射能力
	wpitem[1][3][4] = 450;//射程能力
	wpitem[1][3][5] = 25;//装弾数
	wpitem[1][3][6] = 5;//マガジン


	//PATRIOT
	wsprintf( loadname, "%s\\3d\\weapon\\submachinegun\\patriot\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[1][4][0]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};


	//わからない。ダミーデータ
	wpitem[1][4][1] = 0;//弾薬種類
	wpitem[1][4][2] = 100;//威力
	wpitem[1][4][3] = 8;//連射能力
	wpitem[1][4][4] = 450;//射程能力
	wpitem[1][4][5] = 25;//装弾数
	wpitem[1][4][6] = 5;//マガジン



	//ショットガン


	//M1897
	wsprintf( loadname, "%s\\3d\\weapon\\shotgun\\m1897\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[2][0][0]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wpitem[2][0][1] = 7;//弾薬種類
	wpitem[2][0][2] = 45;//威力
	wpitem[2][0][3] = 25;//連射能力
	wpitem[2][0][4] = 300;//射程能力
	wpitem[2][0][5] = 5;//装弾数
	wpitem[2][0][6] = 63;//マガジン


	//Benel M3
	wsprintf( loadname, "%s\\3d\\weapon\\shotgun\\benelm3\\pict.bmp", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[2][1][0]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};


	//////ここまで作業終了
	wpitem[2][1][1] = 7;//弾薬種類
	wpitem[2][1][2] = 45;//威力
	wpitem[2][1][3] = 18;//連射能力
	wpitem[2][1][4] = 300;//射程能力
	wpitem[2][1][5] = 7;//装弾数
	wpitem[2][1][6] = 61;//マガジン


	//SPAS-12
	wsprintf( loadname, "%s\\3d\\weapon\\shotgun\\sppas-12\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[2][2][0]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wpitem[2][2][1] = 7;//弾薬種類
	wpitem[2][2][2] = 45;//威力
	wpitem[2][2][3] = 15;//連射能力
	wpitem[2][2][4] = 500;//射程能力
	wpitem[2][2][5] = 7;//装弾数
	wpitem[2][2][6] = 61;//マガジン


	//Gold Stalke
	wsprintf( loadname, "%s\\3d\\weapon\\shotgun\\goldstalke\\pict.bmp", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[2][3][0]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wpitem[2][3][1] = 8;//弾薬種類
	wpitem[2][3][2] = 72;//威力
	wpitem[2][3][3] = 30;//連射能力
	wpitem[2][3][4] = 650;//射程能力
	wpitem[2][3][5] = 2;//装弾数
	wpitem[2][3][6] = 48;//マガジン



	//アサルトライフル


	//M4
	wsprintf( loadname, "%s\\3d\\weapon\\assault\\m4\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[3][0][0]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wpitem[3][0][1] = 9;//弾薬種類
	wpitem[3][0][2] = 140;//威力
	wpitem[3][0][3] = 8;//連射能力
	wpitem[3][0][4] = 700;//射程能力
	wpitem[3][0][5] = 30;//装弾数
	wpitem[3][0][6] = 5;//マガジン


	//RIS
	wsprintf( loadname, "%s\\3d\\weapon\\assault\\ris\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[3][1][0]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wpitem[3][1][1] = 9;//弾薬種類
	wpitem[3][1][2] = 140;//威力
	wpitem[3][1][3] = 8;//連射能力
	wpitem[3][1][4] = 700;//射程能力
	wpitem[3][1][5] = 20;//装弾数
	wpitem[3][1][6] = 7;//マガジン


	//ATRAS  5.56
	wsprintf( loadname, "%s\\3d\\weapon\\assault\\atras\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[3][2][0]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wpitem[3][2][1] = 9;//弾薬種類
	wpitem[3][2][2] = 140;//威力
	wpitem[3][2][3] = 8;//連射能力
	wpitem[3][2][4] = 700;//射程能力
	wpitem[3][2][5] = 20;//装弾数
	wpitem[3][2][6] = 5;//マガジン


	//ATRAS  5.7
	wsprintf( loadname, "%s\\3d\\weapon\\assault\\atras\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[3][3][0]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wpitem[3][3][1] = 3;//弾薬種類
	wpitem[3][3][2] = 60;//威力
	wpitem[3][3][3] = 5;//連射能力
	wpitem[3][3][4] = 400;//射程能力
	wpitem[3][3][5] = 10;//装弾数
	wpitem[3][3][6] = 10;//マガジン


	//AK-101
	wsprintf( loadname, "%s\\3d\\weapon\\assault\\ak-101\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[3][4][0]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wpitem[3][4][1] = 10;//弾薬種類
	wpitem[3][4][2] = 170;//威力
	wpitem[3][4][3] = 10;//連射能力
	wpitem[3][4][4] = 800;//射程能力
	wpitem[3][4][5] = 30;//装弾数
	wpitem[3][4][6] = 4;//マガジン


	//G11
	wsprintf( loadname, "%s\\3d\\weapon\\assault\\g11\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[3][5][0]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wpitem[3][5][1] = 15;//弾薬種類
	wpitem[3][5][2] = 120;//威力
	wpitem[3][5][3] = 8;//連射能力
	wpitem[3][5][4] = 700;//射程能力
	wpitem[3][5][5] = 45;//装弾数
	wpitem[3][5][6] = 4;//マガジン


	//M14
	wsprintf( loadname, "%s\\3d\\weapon\\assault\\m14\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[3][6][0]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wpitem[3][6][1] = 11;//弾薬種類
	wpitem[3][6][2] = 200;//威力
	wpitem[3][6][3] = 13;//連射能力
	wpitem[3][6][4] = 900;//射程能力
	wpitem[3][6][5] = 20;//装弾数
	wpitem[3][6][6] = 5;//マガジン


	//G36
	wsprintf( loadname, "%s\\3d\\weapon\\assault\\g36\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[3][7][0]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wpitem[3][7][1] = 9;//弾薬種類
	wpitem[3][7][2] = 140;//威力
	wpitem[3][7][3] = 8;//連射能力
	wpitem[3][7][4] = 700;//射程能力
	wpitem[3][7][5] = 30;//装弾数
	wpitem[3][7][6] = 5;//マガジン


	//マシンガン


	//BAR A2
	wsprintf( loadname, "%s\\3d\\weapon\\machinegun\\bara2\\pict.bmp", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[4][0][0]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wpitem[4][0][1] = 11;//弾薬種類
	wpitem[4][0][2] = 200;//威力
	wpitem[4][0][3] = 3;//連射能力
	wpitem[4][0][4] = 700;//射程能力
	wpitem[4][0][5] = 20;//装弾数
	wpitem[4][0][6] = 5;//マガジン


	//MINIMI
	wsprintf( loadname, "%s\\3d\\weapon\\machinegun\\minimi\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[4][1][0]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wpitem[4][1][1] = 9;//弾薬種類
	wpitem[4][1][2] = 140;//威力
	wpitem[4][1][3] = 5;//連射能力
	wpitem[4][1][4] = 1000;//射程能力
	wpitem[4][1][5] = 150;//装弾数
	wpitem[4][1][6] = 1;//マガジン


	//M2
	wsprintf( loadname, "%s\\3d\\weapon\\machinegun\\m2\\pict.bmp", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[4][2][0]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wpitem[4][2][1] = 11;//弾薬種類
	wpitem[4][2][2] = 200;//威力
	wpitem[4][2][3] = 8;//連射能力
	wpitem[4][2][4] = 900;//射程能力
	wpitem[4][2][5] = 500;//装弾数
	wpitem[4][2][6] = 1;//マガジン


	//ライフル


	//M700
	wsprintf( loadname, "%s\\3d\\weapon\\rifle\\m700\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[5][0][0]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wpitem[5][0][1] = 11;//弾薬種類
	wpitem[5][0][2] = 200;//威力
	wpitem[5][0][3] = 18;//連射能力
	wpitem[5][0][4] = 1100;//射程能力
	wpitem[5][0][5] = 5;//装弾数
	wpitem[5][0][6] = 30;//マガジン


	//SR-25
	wsprintf( loadname, "%s\\3d\\weapon\\rifle\\sr-25\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[5][1][0]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wpitem[5][1][1] = 9;//弾薬種類
	wpitem[5][1][2] = 140;//威力
	wpitem[5][1][3] = 8;//連射能力
	wpitem[5][1][4] = 1000;//射程能力
	wpitem[5][1][5] = 10;//装弾数
	wpitem[5][1][6] = 21;//マガジン


	//S.V.D
	wsprintf( loadname, "%s\\3d\\weapon\\rifle\\svd\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[5][2][0]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wpitem[5][2][1] = 11;//弾薬種類
	wpitem[5][2][2] = 200;//威力
	wpitem[5][2][3] = 13;//連射能力
	wpitem[5][2][4] = 900;//射程能力
	wpitem[5][2][5] = 10;//装弾数
	wpitem[5][2][6] = 15;//マガジン


	//PSG-1
	wsprintf( loadname, "%s\\3d\\weapon\\rifle\\psg-1\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[5][3][0]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wpitem[5][3][1] = 11;//弾薬種類
	wpitem[5][3][2] = 200;//威力
	wpitem[5][3][3] = 13;//連射能力
	wpitem[5][3][4] = 1100;//射程能力
	wpitem[5][3][5] = 5;//装弾数
	wpitem[5][3][6] = 25;//マガジン


	//X BOW
	wsprintf( loadname, "%s\\3d\\weapon\\rifle\\xbow\\pict.bmp", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[5][4][0]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wpitem[5][4][1] = 12;//弾薬種類
	wpitem[5][4][2] = 30;//威力
	wpitem[5][4][3] = 35;//連射能力
	wpitem[5][4][4] = 1000;//射程能力
	wpitem[5][4][5] = 1;//装弾数
	wpitem[5][4][6] = 300;//マガジン



	//グレネード


	//GRENADE
	wsprintf( loadname, "%s\\3d\\weapon\\grenade\\grenade\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[6][0][0]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wpitem[6][0][1] = 16;//弾薬種類
	wpitem[6][0][2] = 300;//威力
	wpitem[6][0][3] = 0;//連射能力
	wpitem[6][0][4] = 300;//射程能力
	wpitem[6][0][5] = 1;//装弾数
	wpitem[6][0][6] = 5;//マガジン


	//MGL
	wsprintf( loadname, "%s\\3d\\weapon\\grenade\\mgl\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[6][1][0]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wpitem[6][1][1] = 13;//弾薬種類
	wpitem[6][1][2] = 250;//威力
	wpitem[6][1][3] = 25;//連射能力
	wpitem[6][1][4] = 700;//射程能力
	wpitem[6][1][5] = 6;//装弾数
	wpitem[6][1][6] = 2;//マガジン


	//M79
	wsprintf( loadname, "%s\\3d\\weapon\\grenade\\m79\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[6][2][0]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wpitem[6][2][1] = 13;//弾薬種類
	wpitem[6][2][2] = 250;//威力
	wpitem[6][2][3] = 30;//連射能力
	wpitem[6][2][4] = 800;//射程能力
	wpitem[6][2][5] = 1;//装弾数
	wpitem[6][2][6] = 12;//マガジン



	//未分類（他）


	//RPG-7
	wsprintf( loadname, "%s\\3d\\weapon\\other\\rpg-7\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[7][0][0]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wpitem[7][0][1] = 14;//弾薬種類
	wpitem[7][0][2] = 280;//威力
	wpitem[7][0][3] = 30;//連射能力
	wpitem[7][0][4] = 1100;//射程能力
	wpitem[7][0][5] = 1;//装弾数
	wpitem[7][0][6] = 10;//マガジン


	//PANZER FAUST
	wsprintf( loadname, "%s\\3d\\weapon\\other\\panzer\\pict.png\0", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[7][1][0]);

	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wpitem[7][1][1] = 14;//弾薬種類
	wpitem[7][1][2] = 310;//威力
	wpitem[7][1][3] = 25;//連射能力
	wpitem[7][1][4] = 400;//射程能力
	wpitem[7][1][5] = 1;//装弾数
	wpitem[7][1][6] = 5;//マガジン



   //武器・兵器スプライトのロード終了

	//メニューで使うスプライトをロード
	wsprintf( loadname, "%s\\img\\ops\\op1.png\0", pat);
	ech = E3DCreateSprite( loadname, 0, 0, &opimg);

	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};



	//スタート表示でのロード
	wsprintf( loadname, "%s\\img\\ops\\pushkey.png\0", pat);
	ech = E3DCreateSprite( loadname, 0, 0, &lddata[0]);

	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wsprintf( loadname, "%s\\img\\ops\\1.png\0", pat);
	ech = E3DCreateSprite( loadname, 0, 0, &lddata[1]);

	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wsprintf( loadname, "%s\\img\\ops\\2.png\0", pat);
	ech = E3DCreateSprite( loadname, 0, 0, &lddata[2]);

	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wsprintf( loadname, "%s\\img\\ops\\3.png\0", pat);
	ech = E3DCreateSprite( loadname, 0, 0, &lddata[3]);

	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wsprintf( loadname, "%s\\img\\ops\\4.png\0", pat);
	ech = E3DCreateSprite( loadname, 0, 0, &lddata[4]);

	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	 //オペレーションモードで使うものをロード

	wsprintf( loadname, "%s\\img\\opration\\yazirusi.png\0", pat);
	ech = E3DCreateSprite( loadname, 0, 0, &lddata[5]);

	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};



	 //ゲーム本編中で使うものをロード

	wsprintf( loadname, "%s\\img\\main\\parometa1.png\0", pat);//HP&STパロメーター
	ech = E3DCreateSprite( loadname, 1, 0, &lddata[6]);

	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wsprintf( loadname, "%s\\img\\main\\parometa2.png\0", pat);//AMM&MAGパロメーター
	ech = E3DCreateSprite( loadname, 1, 0, &lddata[7]);

	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wsprintf( loadname, "%s\\img\\main\\hpber.png\0", pat);//HPバー
	ech = E3DCreateSprite( loadname, 0, 0, &lddata[8]);

	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wsprintf( loadname, "%s\\img\\main\\stnber.png\0", pat);//スタミナバー
	ech = E3DCreateSprite( loadname, 0, 0, &lddata[9]);

	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wsprintf( loadname, "%s\\img\\main\\ammber.png\0", pat);//銃弾バー
	ech = E3DCreateSprite( loadname, 0, 0, &lddata[10]);

	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};


	wsprintf( loadname, "%s\\img\\main\\magber.png\0", pat);//マガジンバー
	ech = E3DCreateSprite( loadname, 0, 0, &lddata[11]);

	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};



	wsprintf( loadname, "%s\\img\\main\\parometa3.png\0", pat);//バックHP&STパロメーター
	ech = E3DCreateSprite( loadname, 1, 0, &lddata[12]);

	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wsprintf( loadname, "%s\\img\\main\\parometa4.png\0", pat);//バックAMM&MAGパロメーター
	ech = E3DCreateSprite( loadname, 1, 0, &lddata[13]);

	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wsprintf( loadname, "%s\\img\\main\\+1.png\0", pat);//+1システム
	ech = E3DCreateSprite( loadname, 1, 0, &lddata[14]);

	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wsprintf( loadname, "%s\\img\\pose\\posebg.png\0", pat);//ポーズメニューでの背景
	ech = E3DCreateSprite( loadname, 1, 0, &lddata[15]);

	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wsprintf( loadname, "%s\\img\\pose\\poseber.png\0", pat);//ポーズメニューの白線
	ech = E3DCreateSprite( loadname, 1, 0, &lddata[16]);

	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	wsprintf( loadname, "%s\\img\\pose\\upposeber.png\0", pat);//ポーズメニューの上部白線
	ech = E3DCreateSprite( loadname, 1, 0, &lddata[17]);

	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};



	////////////////////////////////////////////////////
	///////////////////////////////////////////////////
	//////////////////////////////////////////////////



   //その他情報
	
	//光を作ります（キラッ★）

	ech = E3DCreateLight( &litid1 );//ライトを作る
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	ech = E3DCreateLight( &litid2 );//ライトを作る
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	//光id作成終了

	//初期設定をします

	ech = E3DSetProjection(100.0, 100000.0, 60.0);//プロジェクションの設定
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	//変数の初期化

	Iinfo[4][0] = 0;//敵の数を0にする


	//フォント番号を作ります。

	E3DCreateFont( 35, 0, 800, 0, 0, 0, "MS Pゴシック", &FontID[0]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};

	E3DCreateFont( 25, 0, 800, 0, 0, 0, "MS Pゴシック", &FontID[1]);
	if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
	};



	return 0;
}







int grdload(int grdid, int grdkd, int lightkd, int shodowkd){


	//マップデータのロード


	int ech;
	char loadname[MAX_PATH] = "";

	
	if(grdid == 0){//トロンプール

		if(grdkd == 0){//実戦MAP
						wsprintf( loadname, "%s\\3d\\map\\st_trom\\trom.sig", pat);
						ech = E3DLoadSigFileAsGround(loadname, 50.0, 0, &grd1);
						if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
								return 1;//問題ありで終了
						};

						wsprintf( loadname, "%s\\3d\\map\\st_trom\\trom_wl2.mqo", pat);
						ech = E3DLoadMQOFileAsMovableArea(loadname, 50.0, &wal1);
						if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
								return 1;//問題ありで終了
						};
		};

		if(grdkd == 1){//練習用MAP
						wsprintf( loadname, "%s\\3d\\map\\st_trom\\trom_tr.sig", pat);
						ech = E3DLoadSigFileAsGround(loadname, 50.0, 0, &grd1);
						if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
								return 1;//問題ありで終了
						};

						wsprintf( loadname, "%s\\3d\\map\\st_trom\\trom_trwall.mqo", pat);
						ech = E3DLoadMQOFileAsMovableArea(loadname, 50.0, &wal1);
						if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
								return 1;//問題ありで終了
						};
		};

		//*************//
		E3DCOLOR4UC col= {255,255,255,255};
		E3DSetLinearFogParams(1, col, 15000, 100000, -1);//ファグをかけます。
		if(ech != 0 ){//エラーチェック
					_ASSERT( 0 );//エラーダイアログ
					return 1;//問題ありで終了
		};

	};

	/////////////////

	if(grdid == 1){//ロビー

		if(grdkd == 0){//実戦MAP
						wsprintf( loadname, "%s\\3d\\map\\st_trom\\trom.sig", pat);
						ech = E3DLoadSigFileAsGround(loadname, 50.0, 0, &grd1);
						if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
								return 1;//問題ありで終了
						};

						wsprintf( loadname, "%s\\3d\\map\\st_trom\\trom_wl2.mqo", pat);
						ech = E3DLoadMQOFileAsMovableArea(loadname, 50.0, &wal1);
						if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
								return 1;//問題ありで終了
						};
		};

		//*************//
		E3DCOLOR4UC col= {255,255,255,255};
		E3DSetLinearFogParams(1, col, 15000, 100000, -1);//ファグをかけます。
		if(ech != 0 ){//エラーチェック
								_ASSERT( 0 );//エラーダイアログ
								return 1;//問題ありで終了
		}
	};


	 //ステージロード完了////////////////////////////
	////////////////////////////////////////////////



	//ライトの設定をします。

	if(lightkd == 0){//晴れ

					D3DXVECTOR3 ldir1( -1.0, -1.0, -1.0);
					D3DXVECTOR3 ldir2( 1.0, 1.0, 1.0);
					E3DCOLOR4UC col= { 255, 255, 255, 255};

					//一つ目のライト作成
					ech = E3DSetDirectionalLight( litid1, ldir1, col);
					if( ech != 0){
								_ASSERT( 0 );
								return 1;
					};

					//二つ目のライト作成
					ech = E3DSetDirectionalLight( litid2, ldir2, col);
					if( ech != 0){
								_ASSERT( 0 );
								return 1;
					};

					//背景を作ります
					wsprintf( loadname, "%s\\3d\\map\\360\\hare.jpg", pat);
					ech = E3DCreateBG(scid1, loadname, "", 0, 0, 1, 1000);
					if( ech != 0){
								_ASSERT( 0 );
								return 1;
					};
	}

	/////////////////
	if(lightkd == 1){//夕方

					D3DXVECTOR3 ldir1( -1.0, -1.0, -1.0);
					D3DXVECTOR3 ldir2( 1.0, 1.0, 1.0);
					E3DCOLOR4UC col= { 200, 50, 50, 255};

					//一つ目のライトを設定する。
					ech = E3DSetDirectionalLight( litid1, ldir1, col);
					if( ech != 0){
								_ASSERT( 0 );
								return 1;
					};

					//二つ目のライトを設定する。
					ech = E3DSetDirectionalLight( litid2, ldir2, col);
					if( ech != 0){
								_ASSERT( 0 );
								return 1;
					};

					//背景を作ります
					wsprintf( loadname, "%s\\3d\\map\\360\\sunset.jpg", pat);
					ech = E3DCreateBG(scid1, loadname, "", 0, 0, 1, 1000);
					if( ech != 0){
								_ASSERT( 0 );
								return 1;
					};
	}

	////////////////
	if(lightkd == 2){//夜

					D3DXVECTOR3 ldir1( -1.0, -1.0, -1.0);
					D3DXVECTOR3 ldir2( 1.0, 1.0, 1.0);
					E3DCOLOR4UC col= { 50, 50, 50, 255};

					//一つ目のライトを設定する。
					ech = E3DSetDirectionalLight( litid1, ldir1, col);
					if( ech != 0){
								_ASSERT( 0 );
								return 1;
					};

					//二つ目のライトを設定する。
					ech = E3DSetDirectionalLight( litid2, ldir2, col);
					if( ech != 0){
								_ASSERT( 0 );
								return 1;
					};

					//背景を作ります
					wsprintf( loadname, "%s\\3d\\map\\360\\night.jpg", pat);
					ech = E3DCreateBG(scid1, loadname, "", 0, 0, 1, 1000);
					if( ech != 0){
								_ASSERT( 0 );
								return 1;
					};
	}




	return 0;
}



int gunload(int wpkind, int wpno, int wpmin_sub_gl){
//銃器のロードをします。
//関数データ　銃器の種類,銃器のナンバー,銃器は主or副or弾



	char loadname[MAX_PATH] = "";
	int ech;
	int a;

	//ゲーム本編で必要なデータを格納
	Iinfo[(wpmin_sub_gl)][0] = wpkind;//武器の種類を格納
	Iinfo[(wpmin_sub_gl)][1] = wpno;//武器のナンバーを格納
	// 2: モデルを格納 
	Iinfo[(wpmin_sub_gl)][3] = wpitem[(wpkind)][(wpno)][5];//武器の装弾数を格納
	Iinfo[(wpmin_sub_gl)][4] = wpitem[(wpkind)][(wpno)][6];//武器のマガジン数を格納
	Iinfo[(wpmin_sub_gl)][5] = 1;//武器の使用状態を格納 !1なら未使用!

	/*
		Iinfoのこと

		0:メインウェポン 1:サブウェポン 2:グレネード系　3:自分自身のデータ 4:その他の情報が入ってます。

		//メイン・サブウェポン・グレネード系のデータ関係
		0:武器の種類 1:武器のナンバー 2:Sigの情報 3:AMMのデータ 4:MAGのデータ 5:武器の使用状態

		//自分自身
		0:キャラのID 1:自分のHP 2:自分のスタミナ 3:現在の装備状態 4:操作モードの状態

		//その他の情報
		0:敵の総数

	*/

	if(wpkind == 0){//ハンドガン

		if(wpno == 0){//M1911なら

						wsprintf( loadname, "%s\\3d\\weapon\\handgun\\m1911\\m1911.sig", pat);//前とった実行中のパスとsig名登録
						ech = E3DSigLoad( loadname, 0, 0.1, &Iinfo[(wpmin_sub_gl)][2]);//モデルの読み込み、Iinfoへモデルを入れる。
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
									return 1;//問題ありで終了
						};

						//ボーン取得
						ech = E3DGetBoneNoByName( Iinfo[(wpmin_sub_gl)][2], "銃根", &Iinfo[(wpmin_sub_gl)][6]);
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
									return 1;//問題ありで終了
						};
						ech = E3DGetBoneNoByName( Iinfo[(wpmin_sub_gl)][2], "銃先", &Iinfo[(wpmin_sub_gl)][7]);
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
									return 1;//問題ありで終了
						};
						ech = E3DGetBoneNoByName( Iinfo[(wpmin_sub_gl)][2], "飛段先", &Iinfo[(wpmin_sub_gl)][8]);
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
									return 1;//問題ありで終了
						};
						ech = E3DGetBoneNoByName( Iinfo[(wpmin_sub_gl)][2], "弾丸根", &Iinfo[(wpmin_sub_gl)][9]);
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
									return 1;//問題ありで終了
						};
						ech = E3DGetBoneNoByName( Iinfo[(wpmin_sub_gl)][2], "スライド根", &Iinfo[(wpmin_sub_gl)][10]);
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
									return 1;//問題ありで終了
						};
						ech = E3DGetBoneNoByName( Iinfo[(wpmin_sub_gl)][2], "スライド先", &Iinfo[(wpmin_sub_gl)][11]);
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
									return 1;//問題ありで終了
						};



						wsprintf( loadname, "%s\\3d\\weapon\\handgun\\m1911\\wait1.qua", pat);//前とった実行中のパスとsig名登録
						ech = E3DAddMotion( Iinfo[(wpmin_sub_gl)][2], loadname, 1.0, &Iinfo[(wpmin_sub_gl)][14], &a);
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
									return 1;//問題ありで終了
						};




		}
		if(wpno == 2){//M92fsなら


						//モデル読み込み
						wsprintf( loadname, "%s\\3d\\weapon\\handgun\\m92f\\m92f.sig", pat);//前とった実行中のパスとsig名登録
						ech = E3DSigLoad( loadname, 0, 0.1, &Iinfo[(wpmin_sub_gl)][2]);//モデルの読み込み、hsid1へモデルを入れる。
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
									return 1;//問題ありで終了
						};

						//ボーン取得
						ech = E3DGetBoneNoByName( Iinfo[(wpmin_sub_gl)][2], "銃根", &Iinfo[(wpmin_sub_gl)][6]);
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
									return 1;//問題ありで終了
						};
						ech = E3DGetBoneNoByName( Iinfo[(wpmin_sub_gl)][2], "銃先", &Iinfo[(wpmin_sub_gl)][7]);
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
									return 1;//問題ありで終了
						};
						ech = E3DGetBoneNoByName( Iinfo[(wpmin_sub_gl)][2], "飛段先", &Iinfo[(wpmin_sub_gl)][8]);
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
									return 1;//問題ありで終了
						};
						ech = E3DGetBoneNoByName( Iinfo[(wpmin_sub_gl)][2], "銃丸根", &Iinfo[(wpmin_sub_gl)][9]);
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
									return 1;//問題ありで終了
						};
		
						wsprintf( loadname, "%s\\3d\\weapon\\handgun\\m92f\\wait.qua", pat);//前とった実行中のパスとsig名登録
						ech = E3DAddMotion( Iinfo[(wpmin_sub_gl)][2], loadname, 1.0, &Iinfo[(wpmin_sub_gl)][10], &a);
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
									return 1;//問題ありで終了
						};


		}


	}


	return 0;
}