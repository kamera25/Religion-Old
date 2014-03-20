#pragma once
/*
// �~�b�V�����N���X�̏����ɂ��ċL�q���܂�
//
*/
#include <list>


/* �v���g�^�C�v�錾 */
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

	/* �ϐ� */
	PlayerChara *pPlayer;
	Batch_Render *pBatP;
	PoseMenu *pMenu;
	NPC_Head *pNPC;
	Stage *pStg;
	Camera *pCam;
	int ScreenPosArray[2];

	/* ���C������(�I�[�_�[)����Ƃ��́A�~�b�V�����o�������X�g*/
	std::list<MisOrder> MisList;

	/* �֐� */
	int TPSMainLoop();
	int NormalBatchProces();

public:

	/* �Ó��ϐ� */
	static const int WINIT = 0;// �����[
	static const int PSTORY = 1;// �����[
	static const int PTPS = 2;// �����[

	/* �֐� */
	int Intialize();
	int Loading( char *File);
	int MainProc();

	~Mission();


};


