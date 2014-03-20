#pragma once
/*
// ミッションクラスの処理について記述します
//
*/
#include <list>


/* プロトタイプ宣言 */
class PlayerChara;
class Batch_Render;
class PoseMenu;
class NPC_Head;
class Stage;
class Camera;

struct MisOrder{
	int Statement;
	char cParameter[30];
};

class Mission
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

	/* メイン処理(オーダー)するときの、ミッション双方向リスト*/
	std::list<MisOrder> MisList;

	/* 関数 */
	int TPSMainLoop();
	int NormalBatchProces();

public:

	/* 静動変数 */
	static const int WINIT = 0;// 武器補充
	static const int PSTORY = 1;// 武器補充
	static const int PTPS = 2;// 武器補充

	/* 関数 */
	int Intialize();
	int Loading( char *File);
	int MainProc();

	~Mission();


};


