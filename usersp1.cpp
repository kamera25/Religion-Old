//インクルードするファイル↓
#include <windows.h>
#include "difine.h"

int keyin[20];


//キーを入力されたら配列に代入する関数。
int keyout(int keydev, int stuate){

	//初期化します

	int i = 0;
	while(i <= 20){
			
		keyin[i] = 0;
		i++;
	}
	i=0;


	if(keydev == 0){//もしキーボードからの検出なら

		if(stuate == 0){//もしメニューでの検出なら
				int imput1;
				int imput2;
				kabaddi( &imput1, &imput2, 0 , 0 );
				if(imput1 & 1<<5){//エンター
						keyin[0] = 1;
				}
				if(imput2 & 1<<19){//バックスペース
						keyin[1] = 1;
				}
				if(imput1 & 1<<0){//←
						keyin[2] = 1;
				}
				if(imput1 & 1<<1){//↑
						keyin[3] = 1;
				}
				if(imput1 & 1<<2){//→
						keyin[4] = 1;
				}
				if(imput1 & 1<<3){//↓
						keyin[5] = 1;
				}

		}

		/////////////////////
		////////////////////

		if(stuate == 1){//もしゲーム中での検出なら

				int imput1;
				int imput2;

				kabaddi( &imput1, &imput2, (1<<10)+(1<<13)+(1<<28), (1<<2) );
				if(imput1 & (1<<10)){//Aキー（左へ移動）
					keyin[0] = 1;
				}
				if(imput2 & (1<<2)){//Wキー（前進する）
						keyin[1] = 1;
				}
				if(imput1 & (1<<13)){//Dキー（右へ移動）
						keyin[2] = 1;
				}
				if(imput1 & (1<<28)){//Sキー（後退する）
						keyin[3] = 1;
				}
				if(imput1 & (1<<27)){//Rキー（リロード）
						keyin[4] = 1;
				}
				if(imput1 & (1<<14)){//Eキー（調べる）
						keyin[5] = 1;
				}
				if(imput1 & (1<<10)){//Qキー（セレ切り替え）
						keyin[6] = 1;
				}
				if(imput2 & (1<<5)){//Zキー（装備使用）
						keyin[7] = 1;
				}
				if(imput1 & (1<<13)){//シフトキー（姿勢切り替え）
						keyin[8] = 1;
				}
				if(imput1 & (1<<7)){//左クリック（銃を撃つ）
						keyin[9] = 1;
				}
				if(imput1 & (1<<8)){//右クリック（グレネード）
						keyin[10] = 1;
				}
				if(imput1 & (1<<4)){//スペース（格闘攻撃）
						keyin[11] = 1;
				}
				if(imput1 & (1<<5)){//エンターキー（調べる）
						keyin[12] = 1;
				}
				if(imput2 & (1<<1)){//Vキー（特殊能力）
						keyin[13]=1;
				}
				if(imput2 & (1<<17)){//ホイールクリック（視点変え）
						keyin[14] = 1;
				}
				if(imput2 & (1<<16)){//ESCキー
						keyin[15] = 1;
				}



		}

		

		




	}






	return 0;
}