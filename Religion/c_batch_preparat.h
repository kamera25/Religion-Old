#pragma once
/*ここでは、モデルやスプライトの描画に必要な情報を収集、また描画で必要な
//関数を自動的に実行することができるようにするためのクラスヘッダファイル
*/

//プロトタイプ宣言
class PlayerChara;
class Stage;
class Enemy;
class Camera;
class Weapon;


/*描画準備で必要な変数などを宣言するクラス*/
class Batch_Preparat{	

public:
	//変数の宣言
	int PCWp_hsids[2][3][4];//プレイヤーキャラクターが持っている武器モデルデータの配列

	/*以下、見えるモデルデータのレンダリング*/
	int PCmodel_hsid[2];//ロードしているプレイヤーモデルデータでレンダリングが必要なデータの変数
	int Wp_hsids[2][4];//ロードしている武器モデルデータでレンダリングが必要なデータの配列
	int Stage_hsids[3];//ロードしているステージモデルデータでレンダリングが必要なデータの配列
	int Enemy_hsids[15];//ロードしている敵データでレンダリングが必要なデータの配列

	/*以下、見えないモデルデータでE3DChkInViewが必要なデータ*/
	int Wall_hsids[3];//ロードしている壁モデルデータで視野角内チェックが必要なデータの配列
	int PCDummyModel_hsids[2];//ロードしているPCダミーモデルデータで視野角内チェックが必要なデータの配列
	int Hitmodel_hsids[2];//武器の当たり判定で必要なモデルデータで視野角内チェックが必要なデータの変数
	int CamDummyModel_hsid;//ロードしているカメラダミーモデルデータで視野角内チェックが必要なデータの配列

	/*以下、総合的にレンダリングが必要なモデルデータの配列*/
	int Render_hsids[30];

	/*以下、総合的にE3DChkInViewが必要なモデルデータの配列*/
	int ChkIn_hsids[40];

	/*スプライト関係の変数を宣言します*/

	/*	SpriteData配列には以下のようなデータが格納されています
	//	一番目の配列 スプライトIDと同じ番号にデータが格納されています
	//	二番目の配列 [0]スプライトの倍率X [1]スプライトの倍率Y
	//				 [2]スプライト位置X [3]スプライト位置Y [4]スプライト奥行Z
	*/
	float SpriteData[15][5];//スプライトのデータを格納します
	int SpriteIDs[15];//スプライトのIDを格納します


	//関数の宣言
	Batch_Preparat( const PlayerChara *PcC, const Stage *StgC, const Enemy *EneC, 
					const Camera *Cam, Weapon *Wep);//コンストラクタ、初期化をします
	~Batch_Preparat();//デストラクタ、スプライトを削除します
	int BatchRender( int SceneEndFlg);//今までのデータをまとめて描画するための関数
	int BatchChkInView();//今までのデータをまとめて視野角内チェックするための関数
	int BacthGunTrade( int Wp_equipment);//武器を交換した後、チェックと描画するモデルを変更する関数
	int BatchReset( const PlayerChara *PcC, const Stage *StgC, const Enemy *EneC, const Camera *Cam, Weapon *Wep);//構築していた、まとめデータを再構築する
	int BatchBeforePos();//一つ前の座標をまとめて保存するための関数
	int BatchSpriteRender( int SceneEndFlg);//まとめられたスプライトをレンダリングするための関数
	int BatchSpriteSet( const PlayerChara *PcC, Weapon *Wep);//最初にロードしたスプライトの倍率や描画指定するための関数
	int BatchFont( int SceneEndFlg, const PlayerChara *PcC, Weapon *Wep);//文字を描画することや設定をしたりする関数
	
	/*デコンストラクタが必要！！！*/

};