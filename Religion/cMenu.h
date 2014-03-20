#pragma once
/* ////////////////////////////////////////////////////////////////////////// */
// cMenu2�N���X�w�b�_�t�@�C���ł��B
// cMenu2�N���X���p�����邱�ƂŁA���j���[�����̋��ʃV�X�e�����Ȍ��ɑg�ݍ��߂܂��B
/* ////////////////////////////////////////////////////////////////////////// */

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


class Menu{

private:
	int Font[3];// Menu�N���X����������p�ӂ���A�����̎��ʂ��i�[����ID�z��
	int Foundation_BG[3];// Menu�N���X����������p�ӂ���A�ʏ�̔w�i�摜

	int SpriteID[10];// ���[�U�[��`�X�v���C�gID���i�[����ϐ�
	int SpriteSum;// ���[�U�[��`�X�v���C�g�̍��v�����i�[����ϐ�

	Button Btn[10];
	Balloon Bal[10];

	/* �����o�֐� */

	E3DCOLOR4UC Get_Color( int ColorNum);

public:

	/* �Ó��ϐ�:�F */
	static const int WHITE = 0;// ��
	static const int YELOW = 1;// ��
	static const int BLUE = 2;// ��

	/* �Ó��ϐ�:�����T�C�Y */
	static const int F_BIG = 0;// �啶��
	static const int F_STANDARD = 1;// �W��
	static const int F_SMALL = 2;// ������


	Menu();// �R���X�g���N�^�A
	~Menu();// �f�X�R���g���N�^
	int LoadImg( const char *FilePath, int *SpriteID);// �摜��ǂݍ��ފ֐�
	int PutString( const char *Message, const int X, const int Y, const int FontID, const int Color);// �������o�͂���֐�
	int MakeFontButton( const char *Message, int *ButtonID, const int X, const int Y, const int MaxX, const int MaxY);// �����{�^�����쐬����֐�
	int MakeFontButton_Auto( const char *Message, int *ButtonID, const int X, const int Y);
	int MakeBalloon( const char *Message, int *ButtonID, const int X, const int Y , const int MouseX, const int MouseY, const int MouseMaxX, const int MouseMaxY);
	int MakeBalloonFromButton( const char *Message, int *BalloonID, int *ButtonID, const int X, const int Y);
	int PutBalloon_Auto( const int MouseX, const int MouseY);
	int PutBalloon( const int MouseX, const int MouseY);
	int ChkFontButton( const int MouseX, const int MouseY);// �����{�^����`��A�`�F�b�N����֐�
	int RenderBG();
	int RenderBG_Alpha( const E3DCOLOR4UC Alpha);//���߂��̔w�i�`��


};