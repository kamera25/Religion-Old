#pragma once
/*�����ł́A�������E�I���E�v���[�W���[�ɓn���Ƃ����s�ׂ��s���N���X�w�b�_�t�@�C���ł��B
//
*/



//�����ɂ���֐���錾�B
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);//�v���[�W���[�̓o�^


//�������ƏI������
class System{

private:

	//�ϐ��̐錾
	static int UpdataSoundflag;//���������X�V���邩�̃t���O
	static int keydata1[30][2];//�L�[�̃f�[�^�����Ă���z��ϐ��̈��
	static int keydata2[30][2];//�L�[�̃f�[�^�����Ă���z��ϐ��̓��
	static int keyin[20];//�L�[��������Ă��邩�̏��z��
	static int keyBox1[30][2];//���I�Ɏ擾�����L�[��������z��
	static int keyBox2[30][2];
	static int scid2;// �t�F�[�h�A�E�g�Ŏg���X���b�v�`�F�C��

	HINSTANCE hInst;//�n���h���C���X�^���X���i�[����B
	static BOOL GotMes;//PeekMessage�̏�Ԃ��i�[����B

public:
	//�ϐ��̐錾

	static int scid1;//���C���X���b�v�`�F�C����ID
	static int keyinQuick[3];//�L�[��2�����ꂽ���i�[����z��ϐ�
	static int KeyQuickEnd;//�_�b�V�����삪�I�������Ƃ����ׂẴv�b�V�������Z�b�g����t���O�ϐ�
	static int MouseWhole;//�}�E�X�z�C�[���̈ړ��ʂ��i�[����ϐ�
	static int KeyQuickPush[3][3];//�L�[��2��A�ł����Ƃ��̏�������ϐ�
	static int SpriteID[2];//���[�h�����X�v���C�g���i�[���܂�

	static char path[256];//�v���O�������N�����Ă���p�X�̕�����

	static MSG msg;//���b�Z�[�W���i�[����\���́B
	static HWND hwnd;//�n���h���E�B���h�E���i�[����B
	static RECT rewin;//4�����W�̍\����
	static POINT MousePos;//�}�E�X�̈ʒu���i�[����Point�\����
	static POINT BeforeMousePos;//�O��̃}�E�X�̈ʒu���i�[����\����

	//�֐��̐錾
	System( HINSTANCE hInst, HWND hwnd);//�R���X�g���N�^
	~System();//�f�X�g���N�^
	static int MsgQ( const int fps);//���b�Z�[�W�̃��[�v����
	static int KeyRenewal( const int SelectMode);//�L�[�擾���߂̊֐�
	static int GetKeyData( int *KeyDataArray);//�L�[������肷�邽�߂̊֐�
	static int WaitRender();//�ǂݍ��ݒ���\�����邽�߂̊֐�
	static int SetUpdataSoundSys( const int Soundflag);//���������X�V���邩�ǂ����̊֐�
	static int SetFadeOutOfScid( const int FadeTime);//�摜���t�F�[�h�A�E�g�����鏈���̊֐�


};

