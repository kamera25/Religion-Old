//�C���N���[�h����t�@�C����

#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <usercoef.h>//Easy3D�ŕK�v�Ȓǉ��w�b�_
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "resource1.h"//���\�[�X�t�@�C���Ƃ��̊֘A�t���w�b�_
#include <string.h>//�����񑀍�ŕK�v
#include <stdio.h>//���낢��Ȋ֐��̃w�b�_

/////////////////////////////////////

//���[�U�[�w�b�_�t�@�C��

#include "difine.h"


//�O���[�o���ϐ��̐錾

int scid1;
int hsid1;
char pat[MAX_PATH];
RECT recwindow;
HWND hwnd;

//�p�X������ϐ�


//WndProc�����܂���
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){

	int hole;

	switch (msg){
		case WM_DESTROY:
				PostQuitMessage(0);
				return 0;

		case 0x020a://�}�E�X�z�[��
				hole = HIWORD(wp)/120;// ���1�A����545
				return 0;

	}

	return DefWindowProc(hwnd, msg, wp, lp);
}


//���j���[��ʂ̊֐��ł��B
int MenuRoops(){

	keyout(0,0);
	int ech;
	static int stalfa = 0;
	static int plamainus = 0;
	static int modeflg = 0;
	

	//���j���[�`��
	E3DBeginScene(scid1,0);
	E3DBeginSprite();


	D3DXVECTOR3 ldpos1( 0.0, -27.0, 0.0);
	ech = E3DRenderSprite( opimg, 640.0/1024.0, 480.0/512.0, ldpos1);
	if(ech != 0 ){//�G���[�`�F�b�N
			_ASSERT( 0 );//�G���[�_�C�A���O
			return 1;//��肠��ŏI��

	};



	if(modeflg == 4){

			D3DXVECTOR3 ldpos4( 130.0 + 17.0, 400.0, 0.0);//���[�h�Q�[��
			ech = E3DRenderSprite( lddata[2], 94.0/128.0, 12.0/16.0, ldpos4);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			}

			D3DXVECTOR3 ldpos5( 250.0 + 15.0, 400.0, 0.0);//�I�y���[�V����
			ech = E3DRenderSprite( lddata[3], 90.0/128.0, 12.0/16.0, ldpos5);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			}

			D3DXVECTOR3 ldpos6( 370.0 + 35.0, 400.0, 0.0);//�I�����C��
			ech = E3DRenderSprite( lddata[4], 58.0/64.0, 12.0/16.0, ldpos6);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			}

	}

	if(modeflg == 3){

			D3DXVECTOR3 ldpos5( 130.0 + 15.0, 400.0, 0.0);//�I�y���[�V����
			ech = E3DRenderSprite( lddata[3], 90.0/128.0, 12.0/16.0, ldpos5);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			}

			D3DXVECTOR3 ldpos6( 250.0 + 35.0, 400.0, 0.0);//�I�����C��
			ech = E3DRenderSprite( lddata[4], 58.0/64.0, 12.0/16.0, ldpos6);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			}

			D3DXVECTOR3 ldpos3( 370.0 + 20.0, 400.0, 0.0);//�j���[�Q�[��
			ech = E3DRenderSprite( lddata[1], 87.0/128.0, 12.0/16.0, ldpos3);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			}	

	}

	if(modeflg == 2){

			D3DXVECTOR3 ldpos6( 130.0 + 35.0, 400.0, 0.0);//�I�����C��
			ech = E3DRenderSprite( lddata[4], 58.0/64.0, 12.0/16.0, ldpos6);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			}

			D3DXVECTOR3 ldpos3( 250.0 + 20.0, 400.0, 0.0);//�j���[�Q�[��
			ech = E3DRenderSprite( lddata[1], 87.0/128.0, 12.0/16.0, ldpos3);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			}

			D3DXVECTOR3 ldpos4( 370.0 + 17.0, 400.0, 0.0);//���[�h�Q�[��
			ech = E3DRenderSprite( lddata[2], 94.0/128.0, 12.0/16.0, ldpos4);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			}
		

	}

	if(modeflg == 1){

			D3DXVECTOR3 ldpos3( 130.0 + 20.0, 400.0, 0.0);//�j���[�Q�[��
			ech = E3DRenderSprite( lddata[1], 87.0/128.0, 12.0/16.0, ldpos3);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			}

			D3DXVECTOR3 ldpos4( 250.0 + 17.0, 400.0, 0.0);//���[�h�Q�[��
			ech = E3DRenderSprite( lddata[2], 94.0/128.0, 12.0/16.0, ldpos4);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			}

			D3DXVECTOR3 ldpos5( 370.0 + 15.0, 400.0, 0.0);//�I�y���[�V����
			ech = E3DRenderSprite( lddata[3], 90.0/128.0, 12.0/16.0, ldpos5);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			}
		

	}

	if(modeflg == 0){

			D3DXVECTOR3 ldpos2( 160.0, 400.0, 0.0);
			ech = E3DRenderSprite( lddata[0], 300.0/512.0, 18.0/32.0, ldpos2);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			}
		
			E3DCOLOR4UC col= {stalfa*5,255,255,255};
			E3DSetSpriteARGB(lddata[0], col);
			if(plamainus == 0){
					stalfa++;
					if(stalfa == 51){
							plamainus =1;
					}
			}
			if(plamainus == 1){
					stalfa--;
					if(stalfa == 0){
							plamainus =0;
					}
			}


	}
	

	E3DEndSprite();
	E3DEndScene();
	E3DPresent(scid1);


	if(4 >= modeflg  & modeflg >= 1){

		if(keyin[0] == 1){
					return modeflg + 2;
		}

		if(keyin[4] == 1){
					modeflg--;
		}
		if(keyin[2] == 1){
					modeflg++;
		}


		if(modeflg == 5){
					modeflg = 1;
		}
		if(modeflg == 0){
					modeflg = 4;
		}



	}

	if(0 == modeflg){
		if(keyin[0] == 1){
					modeflg = 1;
		}
	}





	return 0;
}






//�錾:���C�����[�v�ł��B
int MainRoops(){
			
	static int flag = 0;
	unsigned long imput = 0;
	int retfps = 0;
	int chk = 0;

	if(flag == 0){//�ŏ��̃��[�h��ʂɔ�΂��B
					chk = opning();
					if(chk == 2){//�`��I���A�t���O�ύX
								flag = 1;
					}
	}

	if(flag == 1){//���j���[���
					chk = MenuRoops();

					if(chk == 6){//�I�y���[�V�������[�h�I���Ȃ�
								flag = 4;
					}
	}


	if(flag == 4){//���j���[���
					chk = OpsRoops();
	}
/*
	
	int a = 0;
	int b = 0;
	kabaddi(&a,&b,0,0);


	if(a & 1){
	//char str[100];
	//wsprintf( str, "%d", keyin[4]);
			MessageBox(NULL , "����ɂ���" ,"�ϐ��R�[���_�C�A���O" , MB_ICONINFORMATION);
	}
*/
	
	E3DWaitbyFPS( 30, &retfps);


	return 0;
}




//WinMain�֐������܂��A���̊֐��͑S�ẴE�B���h�E�Y�A�v���P�[�V��������������X�^�[�g���܂��B
int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd){

	//������
	MSG msg;
	WNDCLASSEX winc;


	//�E�B���h�E�Y�N���X����

	winc.cbSize		   = sizeof(WNDCLASSEX);//�N���X�̃T�C�Y
	winc.style		   = CS_HREDRAW | CS_VREDRAW;//���E�c���T�C�Y�ύX����������ĕ`��
	winc.lpfnWndProc   = WndProc;//�ǂ̃v���V�[�W���ɕԂ���
	winc.cbClsExtra    = 0;//�E�B���h�E�N���X�̕⑫�o�C�g���w��A�����Ă�0��OK
	winc.cbWndExtra    = 0;//�E�B���h�E�C���X�^���X�̕⑫�o�C�g���w��A���0��OK
	winc.hInstance     = hInst;//�ǂ̃C���X�^���X�n���h�����w��
	winc.hIcon         = LoadIcon(NULL,MAKEINTRESOURCE(IDI_ICON1));//�A�C�R���̎w��
	winc.hCursor       = LoadCursor(NULL,IDC_ARROW);//�J�[�\���̎w��
	winc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);//�w�i�̎w��A�����ł͔�
	winc.lpszMenuName  = NULL;//���j���[�o�[�̎w��A�����ł͎g��Ȃ�����Ȃ�
	winc.lpszClassName = "WndCls";//������E�B���h�E�N���X��
	winc.hIconSm       = LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1)) ;//�������A�C�R���̎w��

	//�E�B���h�E�N���X�����I(���E�B���h�E�N���X�̓o�^
	if(!RegisterClassEx(&winc)) return 1;//�����A0�̖߂�l�Ȃ�I��
	

	//���C���E�B���h�E����郇
	hwnd = CreateWindow(
						"WndCls","Religion Ver 0.01d",//�ǂ̃N���X���A�^�C�g���o�[�̖��O
						WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME,CW_USEDEFAULT,0,640,480,//�I�[�o�[���b�v�E�B���h�E�A�ꏊ��Y=0��X=�C�ӁA�傫����640�~480
						NULL,NULL,hInst,NULL//�e�E�B���h�E�Ȃ��A���j���[�g��Ȃ��A�C���X�^���X�A�v���V�[�W������̃p�����[�^�̃|�C���^
	);

	//�����A�E�B���h�E�쐬�Ɏ��s������G���[�ŏI��
	if(hwnd == NULL) return 1;

	ShowWindow(hwnd, nShowCmd);//�E�B���h�E�n���h���̎w��A�A�v���̏���������H
	UpdateWindow(hwnd);//�v���V�[�W����WM_PAINT(�ĕ`��)�̖��߂�����B



	///////////////�p�X�̎擾�J�n////////////////

	strcpy( pat, "" );
	char szpath[1024] = "";//���s���̃p�X�����镶����ϐ�
	GetModuleFileName(hInst,szpath,MAX_PATH);//���s���̃t�@�C�������擾
	
	char *p;//�|�C���^�A��납��
	char ch = '\\' ;//�������镶��
	int index;//�������ڂ�

	p = strrchr(szpath,ch);//�Ō��\�����������T���B
	index = p - szpath;//�Ō��\�������Ƃ���܂ŕ�����������

	strncpy(pat, szpath, index);//path�ϐ���szpath�ϐ�����Ō��\�܂ł̕������擾


	//////////////�p�X�̎擾�I���///////////////



	//Easy3D�̏������J�n�����B
	int ech = 0;//�G���[�`�F�b�N�p�̕ϐ��錾
	ech = E3DEnableDbgFile();//�f�o�b�O�e�L�X�g�o�͏���
	if(ech != 0){//�G���[�`�F�b�N
					_ASSERT(0);//�G���[�_�C�A���O��\��
					return 1;//��肠��Ŋ֐��I��
	};
	ech = E3DInit(hInst,hwnd,0,32,0,1,1,1,&scid1);//Easy3D�̏�����������B
	if(ech != 0){//�G���[�`�F�b�N
					_ASSERT(0);//�G���[�_�C�A���O��\��
					return 1;//��肠��Ŋ֐��I��
	};

	
	/////////�ȉ��A��񂵂����Ȃ�����//////////////////


	ech = loadimg();//���[�h��ʂ�\��
	if(ech != 0){//�G���[�`�F�b�N
					_ASSERT(0);//�G���[�_�C�A���O��\��
					return 1;//��肠��Ŋ֐��I��
	};
	ech = firstload();//�ŏ��Ƀ��[�h���Ȃ���΂Ȃ�Ȃ����A�ݒ�ǂݍ���
	if(ech != 0){//�G���[�`�F�b�N
					_ASSERT(0);//�G���[�_�C�A���O��\��
					return 1;//��肠��Ŋ֐��I��
	};



	BOOL GotMes;
	PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE);//���b�Z�[�W���[�v�ɏ�����Ԃ�

	//���b�Z�[�W���[�v�ł���B

	while(WM_QUIT != msg.message){

			GotMes = PeekMessage( &msg, NULL, 0, 0, PM_REMOVE);
			MainRoops();
			DispatchMessage(&msg);

			GetWindowRect( hwnd, &recwindow);
	};

	///////////////////////�����܂�////////////////////

	E3DBye();
	return 0;
}


