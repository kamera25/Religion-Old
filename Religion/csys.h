#pragma once
/*�����ł́A�������E�I���E�v���[�W���[�ɓn���Ƃ����s�ׂ��s���N���X�w�b�_�t�@�C���ł��B
//
*/
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B


//�����ɂ���֐���錾�B
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);//�v���[�W���[�̓o�^


//�������ƏI������
class System{

private:
	//�ϐ��̐錾
	HINSTANCE hInst;//�n���h���C���X�^���X���i�[����B
	BOOL GotMes;//PeekMessage�̏�Ԃ��i�[����B
	int keydata1[30][2];//�L�[�̃f�[�^�����Ă���z��ϐ��̈��
	int keydata2[30][2];//�L�[�̃f�[�^�����Ă���z��ϐ��̓��

public:
	//�ϐ��̐錾
	RECT rewin;//4���̏�Ԃ̍\���́H
	int scid1;//���C���X���b�v�`�F�C����ID
	char path[256];//�v���O�������N�����Ă���p�X�̕�����
	MSG msg;//���b�Z�[�W���i�[����\���́B
	HWND hwnd;//�n���h���E�B���h�E���i�[����B


	int keyBox1[30][2];
	int keyBox2[30][2];
	int keyin[20];
	int keyinQuick[3];//�L�[��2�����ꂽ���i�[����z��ϐ�
	int KeyQuickPush[3][3];//�L�[��2��A�ł����Ƃ��̏�������ϐ�
	int KeyQuickEnd;//�_�b�V�����삪�I�������Ƃ����ׂẴv�b�V�������Z�b�g����t���O�ϐ�
	int MouseWhole;//�}�E�X�z�C�[���̈ړ��ʂ��i�[����ϐ�

	POINT MousePos;//�}�E�X�̈ʒu���i�[����Point�\����
	POINT BeforeMousePos;//�O��̃}�E�X�̈ʒu���i�[����\����

	int SpriteID[1];//���[�h�����X�v���C�g���i�[���܂�
	
	//�֐��̐錾
	System( HINSTANCE hInst, HWND hwnd, char runpath[256]);//�R���X�g���N�^
	~System();//�f�X�g���N�^
	int MsgQ(int fps);//���b�Z�[�W�̃��[�v����
	int Keyget(int SelectMode);//�L�[�擾���߂̊֐�
	int WaitRender();//�ǂݍ��ݒ���\�����邽�߂̊֐�


};

