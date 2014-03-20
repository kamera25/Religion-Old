#pragma once
/* ナビレールクラスヘッダである、この"cnavirail.cpp"コードは
// キャラクタやカメラを制御する要になる"ナビライン拡張"関係のクラスことが書かれています。
/* /////////////////////////////////////////////////////////////////////////// */

class Actor;

/* ナビレールクラスの定義 */
class NaviRail{

private:

	/* 変数の宣言 */
	bool NaviRailAvailable;// ナビレールを使用するかの変数が格納されます 



public:

	int NaviLineID[10];//ナビラインを識別するためのID配列を格納します
	int NaviPointID[100];// ナビポイントのID配列を格納します
	int CTPoint[20][2];// 乗り換えポイントの番号に対応する、ナビポイント番号が格納されています。 [0]ライン / [1] ポイント
	int PointSum;//ポイントの合計を表します

	/* 関数の宣言 */
	NaviRail();// コンストラクタ、ナビレール等の初期化を行ないます
	~NaviRail();// デストラクタ、ナビレール等の削除を行ないます

	// ナビラインの追加を行ないます
	int AddNaviPointToStage( const int NaviPointEdge, const int NaviLineNumberconst, float NaviPointPosx,
							const float NaviPointPosy, const float NaviPointPosz);
	int NaviRailOnOffSwitch( const bool RailOnOrOff);// ナビレールを有効/無効にする作業を行ないます
	int PCControlByNaviRail( const int ModelID, int *TargetNaviPointID, int NaviLineID) const;// ナビレールによってキャラクターをコントロールします
	int NRGivenTransfarFromAToB( const int CreateOnNaviLine, const int ANaviLine, const int ANaviPoint, 
							const int BNaviLine, const int BNaviPoint);// ナビレールの乗換ポイントを作成します
	int SetPosByNaviPoint( Actor *Act, const int NaviLine, const int NaviPoint);//ナビポイントによってモデルを設置します
	int AddConectCTPoint( const int ChangePoint, const int LineNum);// 乗り換えポイントから、指定したポイントへナビラインをつなげる 
	int AddNaviPointAsCT( const int NaviPointEdge, const int NaviLineNumber, const float NaviPointPosx,
									const float NaviPointPosy, const float NaviPointPosz, const int CTNum);// ナビラインにナビポイントを追加します
	int NVFLoading( char *File ); // ナビレールのファイルを読み込みます
	//int SetPosByNaviPoint2( const int ModelID, const int NaviLine, const int NaviPoint);
	/* アシスト関数系 */
	bool Get_NaviRailAvailable() const;// NaviRailAvailableを取得します

};
