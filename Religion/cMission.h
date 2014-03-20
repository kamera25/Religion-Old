#pragma once
/*
// �~�b�V�����N���X�̏����ɂ��ċL�q���܂�
//
*/
#include <list>
#include "cGUI.h"// GUI�̃T�u�Z�b�g���g���܂�
#include <time.h>

/* �v���g�^�C�v�錾 */
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
	int LimitTime;// �������Ԃ�ݒ肷��ۂɗ��p����
	clock_t FirstTime;// �Q�[���J�n����̎���
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

	/* �ϐ� */
	PlayerChara *pPlayer;
	Batch_Render *pBatP;
	PoseMenu *pMenu;
	NPC_Head *pNPC;
	Stage *pStg;
	Camera *pCam;
	int ScreenPosArray[2];
	int GameState;// �Q�[���̏�Ԃ�����(�萔�����̏�Ԃ�\���B)
	int SpGameOver;// �X�v���C�g
	int RPModelID;// ����̏ꏊ�ɏW�܂�̂ɗ��p���郂�f��
	struct SCatapult CatapultData[8];// �J�^�p���g�W�����v�̃��f��ID
	struct GameTimer Timer;


	/* �l�����ׂ��A����������\���z�� */
	bool WinningFlag[8];// ��������
	bool LosingFlag[8];// �s�k����
	bool NowWinConditionFlag[8];// ���݁A���ۂɖ������Ă��� ��������
	bool NowLosingConditionFlag[8];// ���݁A���ۂɖ������Ă��� �s�k����
	bool CatapultFlag;// �J�^�p���g�W�����v�𗘗p���邩�̃t���O
	
	/* �萔 */
	// ��������
	static const int COD_ALLKILL = 0;// �S�ł̏���
	static const int COD_REACHPOINT= 1;// ����̏ꏊ�ɂ�����

	// �s�k����
	static const int COD_TIMEUP= 0;// ���Ԑ����𒴂����������

	/* ���C������(�I�[�_�[)����Ƃ��́A�~�b�V�����o�������X�g*/
	std::list<MisOrder> MisList;

	/* �֐� */
	int TPSMainLoop();
	int NormalBatchProces();
	int GameOver();
	int RegisterCatapult(  const int ModelID, const double UpAcceleration, const double Degree, const double Speed);
	int ChkCatapult();// �J�^�p���g�֘A�̏������s��


public:

	/* �Ó��ϐ� */
	static const int WINIT = 0;// �����[
	static const int PSTORY = 1;// �X�g�[���J�n
	static const int PTPS = 2;// TPS���J�n
	static const int PINIT = 3;// �v���C���[������
	static const int NPCINIT = 4;// NPC�֘A�̏�����
	static const int SMYPOS = 5;// �����f���̍��W���w�肵�܂�
	static const int END = 6;// �Q�[�����I������
	static const int REGWIN = 7;// �����������w�肷��
	static const int WININIT= 8;// ��������������������(�s�k������)
	static const int REGLOSE = 9;// �s�k�������w�肷��
	static const int INSTOBJ = 10;// �I�u�W�F�N�g��ݒu����

	/* �萔(�C�x���g�֘A) */
	static const int NORMAL = 0;
	static const int CLEAR = 1;
	static const int GAMEOVER = 2;
	static const int GIVEUP = 3;
	static const int RETRY = 4;
	static const int ALLKILL = 5;
	static const int REACHPOINT = 6;// �|�C���g�ɓ���������
	static const int TIMEUP = 7;// �^�C���A�b�v������
	static const int CATAPULT = 8;// �J�^�p���g�W�����v��ݒu������


	static const int NAVI = 0;
	static const int WORLD = 1;

	/* �֐� */
	int Intialize();
	int Loading( char *File);
	int MainProc();
	
	int EventSupervision();// �C�x���g�֘A�̓������s��
	int CheckBattle();// �����E���������𖞂����Ă��邩�`�F�b�N����

	~Mission();


};


