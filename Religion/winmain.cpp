/*�����ł́A�A�v���P�[�V�����̊�b���쐬��WinMain���쐬�����֊֐���n����Ƃ����܂��B
//
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include <cstring>//�����񑀍�Ŏg���w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_


//�����ɂ���֐���錾�B
int GMStart();//�Q�[�����C�����[�v�̐錾


//�E�B���h�E�Y�v���[�W���[
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){

	int Whole = 0;//�z�C�[���̈ړ��ʂ��i�[����ϐ�

	switch (msg){
		case WM_MOUSEWHEEL://�}�E�X�z�[��
				Whole = HIWORD(wp)/120;// ���1�A����545
				if( Whole == 1) System::MouseWhole = 1;
				if( Whole == 545) System::MouseWhole = 2;

				break;

		case WM_DESTROY:
				PostQuitMessage(0);

				break;




	};

	return DefWindowProc(hwnd, msg, wp, lp);
};



//WinMain�֐��쐬
int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd){

	//������
	WNDCLASSEX winc;
	HWND hwnd;

	//_CrtSetDbgFlag(_CRTDBG_CHECK_ALWAYS_DF | _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//�E�B���h�E�Y�N���X����

	winc.cbSize		   = sizeof(WNDCLASSEX);//�N���X�̃T�C�Y
	winc.style		   = CS_HREDRAW | CS_VREDRAW;//���E�c���T�C�Y�ύX����������ĕ`��
	winc.lpfnWndProc   = WndProc;//�ǂ̃v���V�[�W���ɕԂ���
	winc.cbClsExtra    = 0;//�E�B���h�E�N���X�̕⑫�o�C�g���w��A�����Ă�0��OK
	winc.cbWndExtra    = 0;//�E�B���h�E�C���X�^���X�̕⑫�o�C�g���w��A���0��OK
	winc.hInstance     = hInst;//�ǂ̃C���X�^���X�n���h�����w��
	winc.hIcon         = LoadIcon( hInst, "KIRIN");//�A�C�R���̎w��
	winc.hCursor       = LoadCursor(NULL,IDC_ARROW);//�J�[�\���̎w��
	winc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);//�w�i�̎w��A�����ł͔�
	winc.lpszMenuName  = NULL;//���j���[�o�[�̎w��A�����ł͎g��Ȃ�����Ȃ�
	winc.lpszClassName = "WndCls";//������E�B���h�E�N���X��
	winc.hIconSm       = LoadIcon( hInst, "KIRIN");//�A�C�R���̎w��

	//�E�B���h�E�N���X�����I(���E�B���h�E�N���X�̓o�^
	if(!RegisterClassEx(&winc)) return 1;//�����A0�̖߂�l�Ȃ�I��
	


	//���C���E�B���h�E����郇
	hwnd = CreateWindow(
						"WndCls","Religion Gram_Ver 0.02",//�ǂ̃N���X���A�^�C�g���o�[�̖��O
						WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME,CW_USEDEFAULT,0,640,480,//�I�[�o�[���b�v�E�B���h�E�A�ꏊ��Y=0��X=�C�ӁA�傫����640�~480
						NULL,NULL,hInst,NULL//�e�E�B���h�E�Ȃ��A���j���[�g��Ȃ��A�C���X�^���X�A�v���V�[�W������̃p�����[�^�̃|�C���^
	);

	/* 640�~480��Window�T�C�Y�ɂ��� */

	RECT rcc;// �N���C�A���g�̕�
	RECT rcw;// �E�B���h�E�̕�
	LONG WindSX;
	LONG WindSY;

	GetWindowRect( hwnd, &rcw);
	GetClientRect( hwnd, &rcc);
	WindSX = 640 + ((rcw.right - rcw.left) - (rcc.right - rcc.left));
    WindSY = 480 + ((rcw.bottom - rcw.top) - (rcc.bottom - rcc.top));
	SetWindowPos( hwnd, NULL, 0, 0, WindSX, WindSY, (SWP_NOZORDER|SWP_NOOWNERZORDER|SWP_NOMOVE) );




	//�����A�E�B���h�E�쐬�Ɏ��s������G���[�ŏI��
	if(hwnd == NULL) return 1;

	ShowWindow(hwnd, nShowCmd);//�E�B���h�E�n���h���̎w��A�A�v���̏���������H
	UpdateWindow(hwnd);//�v���V�[�W����WM_PAINT(�ĕ`��)�̖��߂�����B

	//WinAPI�ɂ��E�B���h�E�쐬�I��
	//�ȉ����A�N���X�ESystem�ɂ��E3D�����쐬

	{
		System system( hInst, hwnd);//E3D���쐬

		GMStart();//�Q�[�����X�^�[�g���܂��B�悤�����AReligion�ցB


	};

	return 0;
};