#pragma once
/*ここでは、敵モデルや敵の動きに関することを
//関数を自動的に実行することができるようにするためのクラスヘッダファイル
*/

//プロトタイプ宣言
class Stage;

class Enemy{

public:

	//変数の宣言
	int Enemy_hsid[15];//敵のモデルを入れる配列変数
	int Enemy_HP[15];//敵のHPを代入する配列変数
	int Enemy_State[15];//敵が死んだ後の処理を指定する変数
	int EnemyNum;//現在ロードされているモデルの数



	//関数の宣言
	Enemy();//コンストラクタ、クラス変数の初期化を行います
	~Enemy();//デストラクタ、モデルの削除を行います
	int LoadEnemyModel( int Ene_Kind, int Ene_No);//敵を情報やモデルをロードするための関数
	int MoveEnemys( const Stage *Stg);//敵の動きをまとめて動かすための関数

};

