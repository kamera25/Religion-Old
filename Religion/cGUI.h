#pragma once
/* ////////////////////////////////////////////////////////////////////////// */
// cGUI�N���X�w�b�_�t�@�C���ł��B
// cGUI�N���X���p�����邱�ƂŁAGUI�̃p�[�c���ȒP�ɑg�ݍ��߂�T�u�Z�b�g�𗘗p�ł��܂��B
/* ////////////////////////////////////////////////////////////////////////// */
#include <vector>

struct Button{
	char String[80];// �{�^���̕������i�[����ϐ�
	int X;
	int Y;
	int MaxX;
	int MaxY;
};

struct Balloon{
	char String[150];// �o���[���̕������i�[����ϐ�
	int X;
	int Y;
	int MouseX;
	int MouseY;
	int MouseMaxX;
	int MouseMaxY;
	int Width;
};

class cGUI{

private:

	static int Font[3];// ��ʓI�Ɏg���t�H���g
	int SpriteID[20];// ���[�U�[��`�X�v���C�gID���i�[����
	int SpriteSum;// ���[�U�[��`�X�v���C�g�̍��v�����i�[����ϐ�
	
	Button Btn[10];
	Balloon Bal[10];

	/* �����o�֐� */


public:
	static int Initialize();// �������֐�
	static int Finalize();// �t�@�C�i���C�Y�֐�(���ׂĂ��I��肵���A���̊֐����Ăяo��)

	/* �Ó��ϐ�:�F */
	static const int WHITE = 0;// ��
	static const int YELOW = 1;// ��
	static const int BLUE = 2;// ��
	static const int BLACK = 3;// ��
	static const int GRAY = 4;// �D�F

	/* �Ó��ϐ�:�����T�C�Y */
	static const int F_BIG = 0;// �啶��
	static const int F_STANDARD = 1;// �W��
	static const int F_SMALL = 2;// ������

	cGUI();// ���ۂ�GUI���g���n�߂�O�ɌĂяo���A�R���X�g���N�^
	virtual ~cGUI();
	int LoadImg( const char *FilePath, int *SpriteID);// �摜��ǂݍ��ފ֐�
	int PutString( const char *Message, const int X, const int Y, const int FontID, const int Color);// �������o�͂���֐�
	int MakeFontButton( const char *Message, int *ButtonID, const int X, const int Y, const int MaxX, const int MaxY);// �����{�^�����쐬����֐�
	int MakeFontButton_Auto( const char *Message, int *ButtonID, const int X, const int Y);
	int MakeBalloon( const char *Message, int *ButtonID, const int X, const int Y , const int MouseX, const int MouseY, const int MouseMaxX, const int MouseMaxY);
	int MakeBalloonFromButton( const char *Message, int *BalloonID, int *ButtonID, const int X, const int Y);
	int PutBalloon_Auto( const int MouseX, const int MouseY);
	int PutBalloon( const int MouseX, const int MouseY);
	int ChkFontButton( const int MouseX, const int MouseY);// �����{�^����`��A�`�F�b�N����֐�
	int ChkFontButtonWithColor( const int MouseX, const int MouseY, const int NonSelectedColor, const int SelectedColor);// �{�^���̐F���w�肵�āA�`�F�b�N����֐�
	int StartBeginScene();
	int EndSprite();
	int EndScene();
	int DestorySprite( const int SpID);
	int PutSprite( const int ID, const int X, const int Y, const double MagX, const double MagY);
	E3DCOLOR4UC Get_Color( int ColorNum);
};