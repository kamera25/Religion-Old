#pragma once
/*
 *  �������E�I���E�v���[�W���[�ɓn���Ƃ����s�ׂ��s���N���X�w�b�_�t�@�C���ł��B
 */



//�����ɂ���֐���錾�B
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);//�v���[�W���[�̓o�^
class Weapon_Head;

//�������ƏI������
class System{

private:

	//�ϐ��̐錾
	static int UpdataSoundflag;//���������X�V���邩�̃t���O
	static bool keyin[20];//�L�[��������Ă��邩�̏��z��
	static int scid2;// �t�F�[�h�A�E�g�Ŏg���X���b�v�`�F�C��
	static int KeyQuickPush[3][3];//�L�[��2��A�ł����Ƃ��̏�������ϐ�

	HINSTANCE hInst;//�n���h���C���X�^���X���i�[����B
	static BOOL GotMes;//PeekMessage�̏�Ԃ��i�[����B

	
	//�֐��̐錾
	static int ChkKeyDoublePush( bool PushKey, int Count, int Element);	
	int Intialize( hInst, hwnd);// ������
	int Start();// �Q�[���J�n

public:
	//�ϐ��̐錾

	static int scid1;//���C���X���b�v�`�F�C����ID
	static int KeyQuickEnd;//�_�b�V�����삪�I�������Ƃ����ׂẴv�b�V�������Z�b�g����t���O�ϐ�
	static int MouseWhole;//�}�E�X�z�C�[���̈ړ��ʂ��i�[����ϐ�

	static int SpriteID[2];//���[�h�����X�v���C�g���i�[���܂�

	static char path[256];//�v���O�������N�����Ă���p�X�̕�����

	static MSG msg;//���b�Z�[�W���i�[����\���́B
	static HWND hwnd;//�n���h���E�B���h�E���i�[����B
	static RECT rewin;//4�����W�̍\����
	static POINT MousePos;//�}�E�X�̈ʒu���i�[����Point�\����
	static POINT BeforeMousePos;//�O��̃}�E�X�̈ʒu���i�[����\����

	/*�@�Ó��ϐ�  */
	/* ���[�h0�ł̃L�[�ԍ��萔 */
	static const int KEY_ENTER = 0;
	static const int KEY_BACKSPACE = 1;// �o�b�N�X�y�[�X
	static const int KEY_LEFT = 2;// ��
	static const int KEY_UP = 3;// ��
	static const int KEY_RIGHT = 4;// ��
	static const int KEY_DOWN = 5;// ��

	/* ���[�h1�ł̃L�[�ԍ��萔 */
	// static const int KEY_ENTER = 0;// �G���^�[ ! 1�Ŋ��ɒ�`�ς� !
	static const int KEY_W = 1;// W�L�[
	static const int KEY_D = 2;// D�L�[
	static const int KEY_S = 3;// S�L�[
	static const int KEY_R = 4;// R�L�[
	static const int KEY_E = 5;// E�L�[
	static const int KEY_Q = 6;// Q�L�[
	static const int KEY_Z = 7;// Z�L�[
	static const int KEY_SHIFT = 8;// �V�t�g�L�[
	static const int KEY_LEFTMOUSE = 9;// ���N���b�N
	static const int KEY_RIGHTMOUSE = 10;// ���N���b�N
	static const int KEY_SPACE = 11;// �X�y�[�X�L�[
	static const int KEY_A = 12;// A�L�[
	static const int KEY_V = 13;// V�L�[
	static const int KEY_WHILEMOUSE = 14;// �z�C�[���N���b�N
	static const int KEY_ESC = 15;// ESC�L�[
	static const int KEY_F = 16;// F�L�[

	//�֐��̐錾
	System();//�R���X�g���N�^
	~System();//�f�X�g���N�^
	static int MsgQ( const int fps);//���b�Z�[�W�̃��[�v����
	static int KeyRenewal( const int SelectMode);//�L�[�擾���߂̊֐�
	//static int GetKeyData( int *KeyDataArray);//�L�[������肷�邽�߂̊֐�
	static int WaitRender();//�ǂݍ��ݒ���\�����邽�߂̊֐�
	static int SetUpdataSoundSys( const int Soundflag);//���������X�V���邩�ǂ����̊֐�
	static int SetFadeOutOfScid( const int FadeTime);//�摜���t�F�[�h�A�E�g�����鏈���̊֐�
	static int KeyRenewalFromWp( const Weapon_Head *Wpn, const int Equipment);// ���������Ă��镐�킩��L�[�̎擾������֐�
	static int SetMouseCursol( const int X, const int Y);// �}�E�X���W���Z�b�g����֐�
	static int SetMouseBeforePos();// ���݂̃}�E�X���W��BeforeMousePos�ɃZ�b�g����֐�
	static bool GetKeyData( const int KeyNum);// �L�[�C���v�b�g���擾����֐�
	static int Get_DoublePush( int Element);// �v�f��n���āA�A���������ǂ����`�F�b�N���܂�
	static int ResetKeyDoublePush( int Element);// �v�f��I�����āA���A���L�[�̐ݒ胊�Z�b�g���s���܂��B
	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp); // �E�B���h�E�v���[�W��

	//�t�����h�֐��錾
	friend int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd);

};

