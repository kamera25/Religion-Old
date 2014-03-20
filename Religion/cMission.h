#pragma once
/*
// ミッションクラスの処理について記述します
//
*/
#include <list>
#include "cGUI.h"// GUIのサブセットを使います
#include <time.h>

/* プロトタイプ宣言 */
class PlayerChara;
class Batch_Render;
class PoseMenu;
class NPC_Head;
class Stage;
class Camera;

struct MisOrder{
	int Statement;
	int iParameter[4];
	char cParameter[30];
};

struct GameTimer{
	int LimitTime;// 制限時間を設定する際に利用する
	clock_t FirstTime;// ゲーム開始直後の時間
	bool *TimeUsing;
	bool IndicateTimeNormal;
};

struct SCatapult{
	int CatapultID;
	double X;
	double Y;
	double Z;
	double Degree;
	double UpAcceleration;
	double Speed;
};

class Mission : public cGUI
{

private:

	/* 変数 */
	PlayerChara *pPlayer;
	Batch_Render *pBatP;
	PoseMenu *pMenu;
	NPC_Head *pNPC;
	Stage *pStg;
	Camera *pCam;
	int ScreenPosArray[2];
	int GameState;// ゲームの状態を示す(定数がその状態を表す。)
	int SpGameOver;// スプライト
	int RPModelID;// 所定の場所に集まるのに利用するモデル
	struct SCatapult CatapultData[8];// カタパルトジャンプのモデルID
	struct GameTimer Timer;


	/* 考慮すべき、勝利条件を表す配列 */
	bool WinningFlag[8];// 勝利条件
	bool LosingFlag[8];// 敗北条件
	bool NowWinConditionFlag[8];// 現在、実際に満たしている 勝利条件
	bool NowLosingConditionFlag[8];// 現在、実際に満たしている 敗北条件
	bool CatapultFlag;// カタパルトジャンプを利用するかのフラグ
	
	/* 定数 */
	// 勝利条件
	static const int COD_ALLKILL = 0;// 全滅の条件
	static const int COD_REACHPOINT= 1;// 所定の場所についたら

	// 敗北条件
	static const int COD_TIMEUP= 0;// 時間制限を超えたらついたら

	/* メイン処理(オーダー)するときの、ミッション双方向リスト*/
	std::list<MisOrder> MisList;

	/* 関数 */
	int TPSMainLoop();
	int NormalBatchProces();
	int GameOver();
	int RegisterCatapult(  const int ModelID, const double UpAcceleration, const double Degree, const double Speed);
	int ChkCatapult();// カタパルト関連の処理を行う


public:

	/* 静動変数 */
	static const int WINIT = 0;// 武器補充
	static const int PSTORY = 1;// ストーリ開始
	static const int PTPS = 2;// TPSを開始
	static const int PINIT = 3;// プレイヤー初期化
	static const int NPCINIT = 4;// NPC関連の初期化
	static const int SMYPOS = 5;// 自モデルの座標を指定します
	static const int END = 6;// ゲームを終了する
	static const int REGWIN = 7;// 勝利条件を指定する
	static const int WININIT= 8;// 勝利条件を初期化する(敗北条件も)
	static const int REGLOSE = 9;// 敗北条件を指定する
	static const int INSTOBJ = 10;// オブジェクトを設置する

	/* 定数(イベント関連) */
	static const int NORMAL = 0;
	static const int CLEAR = 1;
	static const int GAMEOVER = 2;
	static const int GIVEUP = 3;
	static const int RETRY = 4;
	static const int ALLKILL = 5;
	static const int REACHPOINT = 6;// ポイントに到着したら
	static const int TIMEUP = 7;// タイムアップしたら
	static const int CATAPULT = 8;// カタパルトジャンプを設置したら


	static const int NAVI = 0;
	static const int WORLD = 1;

	/* 関数 */
	int Intialize();
	int Loading( char *File);
	int MainProc();
	
	int EventSupervision();// イベント関連の統括を行う
	int CheckBattle();// 勝利・負け条件を満たしているかチェックする

	~Mission();


};


