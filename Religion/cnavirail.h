#pragma once
/* ナビレールクラスヘッダである、この"cnavirail.cpp"コードは
// キャラクタやカメラを制御する要になる"ナビライン拡張"関係のクラスことが書かれています。
/* /////////////////////////////////////////////////////////////////////////// */


/* ナビレールクラスの定義 */
class NaviRail{

private:

	/* 変数の宣言 */
	int NaviRailAvailable;// ナビレールを使用するかの変数が格納されます 



public:

	int NaviLineID[10];//ナビラインを識別するためのID配列を格納します

	/* 関数の宣言 */
	NaviRail();// コンストラクタ、ナビレール等の初期化を行ないます
	~NaviRail();// デストラクタ、ナビレール等の削除を行ないます

	// ナビラインの追加を行ないます
	int AddNaviPointToStage( const int NaviPointEdge, const int NaviLineNumberconst, float NaviPointPosx,
							const float NaviPointPosy, const float NaviPointPosz);
	int NaviRailOnOffSwitch( const int RailOnOrOff);// ナビレールを有効/無効にする作業を行ないます
	int PCControlByNaviRail( const int ModelID, int *TargetNaviPointID, int NaviLineID) const;// ナビレールによってキャラクターをコントロールします
	int NRGivenTransfarFromAToB( const int CreateOnNaviLine, const int ANaviLine, const int ANaviPoint, 
							const int BNaviLine, const int BNaviPoint);// ナビレールの乗換ポイントを作成します
	int SetPosByNaviPoint( const int ModelID, const int NaviLine, const int NaviPoint);//ナビポイントによってモデルを設置します

	/* アシスト関数系 */
	int Get_NaviRailAvailable() const;// NaviRailAvailableを取得します

};