/*�����ł́A�������E�I���E�v���[�W���[�ɓn���Ƃ����s�ׂ��s���N���X�R�[�h�t�@�C���ł��B
//
*/
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_



//�R���X�g���N�^ //Easy3D�̏������J�n�����B//
System::System( HINSTANCE chInst, HWND chwnd, char runpath[256]){


	int ech = 0;//�G���[�`�F�b�N�p�̕ϐ��錾
	char loadname[256] = "";//���[�h����t�@�C�����̕�����z��


	ech = E3DEnableDbgFile();//�f�o�b�O�e�L�X�g�o�͏���
	if(ech != 0){//�G���[�`�F�b�N
				_ASSERT(0);//�G���[�_�C�A���O��\��
	};

	ech = E3DInit( chInst, chwnd, 0, 16, 0, 1, 1, 1, 0, &scid1);//Easy3D�̏�����������B
	if(ech != 0){//�G���[�`�F�b�N
				_ASSERT(0);//�G���[�_�C�A���O��\��
	};

	ech = E3DSetProjection( 120.0, 100000.0, 60.0);//�v���W�F�N�V�����̐ݒ���s���܂�
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
	};


	PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE);//���b�Z�[�W���[�v�ɏ�����Ԃ�(���܂��Ȃ�)

	//�ϐ�����

	hInst = chInst;
	hwnd = chwnd;
	strcpy_s( path, runpath);


	/*�L�[�擾���߂̂��߂̃L�[�z�񂻂�1*/
	keydata1[0][0] = 1<<0; keydata1[0][1] = 0x25;//���L�[
	keydata1[1][0] = 1<<1; keydata1[1][1] = 0x26;//��L�[
	keydata1[2][0] = 1<<2; keydata1[2][1] = 0x27;//�E�L�[
	keydata1[3][0] = 1<<3; keydata1[3][1] = 0x28;//���L�[
	keydata1[4][0] = 1<<4; keydata1[4][1] = 0x20;//�X�y�[�X
	keydata1[5][0] = 1<<5; keydata1[5][1] = 0x0D;//�G���^�[�L�[
	keydata1[6][0] = 1<<6; keydata1[6][1] = 0x11;//�R���g���[���L�[
	keydata1[7][0] = 1<<7; keydata1[7][1] = 0x01;//���N���b�N
	keydata1[8][0] = 1<<8; keydata1[8][1] = 0x02;//�E�N���b�N
	keydata1[9][0] = 1<<9; keydata1[9][1] = 0x09;//TAB

	keydata1[10][0] = 1<<10; keydata1[10][1] = 0x41;//A�L�[
	keydata1[11][0] = 1<<11; keydata1[11][1] = 0x42;//B�L�[
	keydata1[12][0] = 1<<12; keydata1[12][1] = 0x43;//C�L�[
	keydata1[13][0] = 1<<13; keydata1[13][1] = 0x44;//D�L�[
	keydata1[14][0] = 1<<14; keydata1[14][1] = 0x45;//E�L�[
	keydata1[15][0] = 1<<15; keydata1[15][1] = 0x46;//F�L�[
	keydata1[16][0] = 1<<16; keydata1[16][1] = 0x47;//G�L�[
	keydata1[17][0] = 1<<17; keydata1[17][1] = 0x48;//H�L�[
	keydata1[18][0] = 1<<18; keydata1[18][1] = 0x49;//I�L�[
	keydata1[19][0] = 1<<19; keydata1[19][1] = 0x4A;//J�L�[
	keydata1[20][0] = 1<<20; keydata1[20][1] = 0x4B;//K�L�[
	keydata1[21][0] = 1<<21; keydata1[21][1] = 0x4C;//L�L�[
	keydata1[22][0] = 1<<22; keydata1[22][1] = 0x4D;//M�L�[
	keydata1[23][0] = 1<<23; keydata1[23][1] = 0x4E;//N�L�[
	keydata1[24][0] = 1<<24; keydata1[24][1] = 0x4F;//O�L�[
	keydata1[25][0] = 1<<25; keydata1[25][1] = 0x50;//P�L�[
	keydata1[26][0] = 1<<26; keydata1[26][1] = 0x51;//Q�L�[
	keydata1[27][0] = 1<<27; keydata1[27][1] = 0x52;//R�L�[
	keydata1[28][0] = 1<<28; keydata1[28][1] = 0x53;//S�L�[
	keydata1[29][0] = 1<<29; keydata1[29][1] = 0x54;//T�L�[


	/*�L�[�擾���߂̂��߂̃L�[�z�񂻂�2*/
	keydata2[0][0] = 1<<0; keydata2[0][1] = 0x55;//U�L�[
	keydata2[1][0] = 1<<1; keydata2[1][1] = 0x56;//V�L�[
	keydata2[2][0] = 1<<2; keydata2[2][1] = 0x57;//W�L�[
	keydata2[3][0] = 1<<3; keydata2[3][1] = 0x58;//X�L�[
	keydata2[4][0] = 1<<4; keydata2[4][1] = 0x59;//Y�L�[
	keydata2[5][0] = 1<<5; keydata2[5][1] = 0x5A;//Z�L�[

	keydata2[6][0] = 1<<6; keydata2[6][1] = 0x30;//���C��0�L�[
	keydata2[7][0] = 1<<7; keydata2[7][1] = 0x31;//���C��1�L�[
	keydata2[8][0] = 1<<8; keydata2[8][1] = 0x32;//���C��2�L�[
	keydata2[9][0] = 1<<9; keydata2[9][1] = 0x33;//���C��3�L�[
	keydata2[10][0] = 1<<10; keydata2[10][1] = 0x34;//���C��4�L�[
	keydata2[11][0] = 1<<11; keydata2[11][1] = 0x35;//���C��5�L�[
	keydata2[12][0] = 1<<12; keydata2[12][1] = 0x36;//���C��6�L�[
	keydata2[13][0] = 1<<13; keydata2[13][1] = 0x37;//���C��7�L�[
	keydata2[14][0] = 1<<14; keydata2[14][1] = 0x38;//���C��8�L�[
	keydata2[15][0] = 1<<15; keydata2[15][1] = 0x39;//���C��9�L�[

	keydata2[16][0] = 1<<16; keydata2[16][1] = 0x1B;//ESC�L�[
	keydata2[17][0] = 1<<17; keydata2[17][1] = 0x04;//�}�E�X�^��
	keydata2[18][0] = 1<<18; keydata2[18][1] = 0x10;//�V�t�g�L�[
	keydata2[19][0] = 1<<19; keydata2[19][1] = 0x08;//�o�b�N�X�y�[�X
	keydata2[20][0] = 1<<20; keydata2[20][1] = 0x12;//ALT�L�[
	keydata2[21][0] = 1<<21; keydata2[21][1] = 0x09;//TAB�L�[

	keydata2[22][0] = 1<<22; keydata2[22][1] = 0x70;//F1
	keydata2[23][0] = 1<<23; keydata2[23][1] = 0x71;//F2
	keydata2[24][0] = 1<<24; keydata2[24][1] = 0x72;//F3
	keydata2[25][0] = 1<<25; keydata2[25][1] = 0x73;//F4
	keydata2[26][0] = 1<<26; keydata2[26][1] = 0x74;//F5
	keydata2[27][0] = 1<<27; keydata2[27][1] = 0x75;//F6
	keydata2[28][0] = 1<<28; keydata2[28][1] = 0x76;//F7
	keydata2[29][0] = 1<<29; keydata2[29][1] = 0x77;//F8

	/*�}�E�X���g�����߂ɏ��������܂�*/
	MousePos.x = 0;
	MousePos.y = 0;
	BeforeMousePos.x = 0;//X���W������
	BeforeMousePos.y = 0;//Y���W������
	KeyQuickEnd = 0;//�t���O�ϐ�������������

	/*�ϐ��̏�����*/
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			KeyQuickPush[i][j] = 0;
		}
		keyinQuick[i] = 0;
	}


	/*�Œ���K�v�ȉ摜�̃��[�h���s���܂�*/

	wsprintf( loadname, "%s\\data\\img\\sys\\loading.png", path);//���j���[��ʂł̏㕔�����o�[�����[�h���܂��B
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteID[0]);
	if(ech != 0){//�G���[�`�F�b�N
				_ASSERT(0);//�G���[�_�C�A���O��\��
	}

	
};



//�f�X�g���N�^ //Easy3D�̏I���������s����B//
System::~System(){

	int ech = 0;//�G���[�`�F�b�N�p�̕ϐ��錾

	/*�摜�̔j�����s���܂�*/
	for(int i=0; i<1; i++){
			ech = E3DDestroySprite( SpriteID[i]);
			if(ech != 0){//�G���[�`�F�b�N
						_ASSERT(0);//�G���[�_�C�A���O��\��
			};
	}

	ech = E3DBye();
	if(ech != 0){//�G���[�`�F�b�N
				_ASSERT(0);//�G���[�_�C�A���O��\��
	};


};


int System::MsgQ(int fps){

	/*������������*/

	int ech = 0;//�G���[�`�F�b�N�p�̕ϐ��錾
	int rfps = 0;//����Ȃ�FPS�v���p�̕ϐ��B
	MouseWhole = 0;//�}�E�X�z�C�[���̈ړ��ʂ�����������

	GotMes = PeekMessage( &msg, NULL, 0, 0, PM_REMOVE);
	if( msg.message == WM_QUIT){
				return 0;
	}
	if( GotMes != 0){//���b�Z�[�W��������
				DispatchMessage(&msg);
				TranslateMessage(&msg);
				GetWindowRect( hwnd, &rewin);
	}
	ech = E3DWaitbyFPS( fps, &rfps);
	if(ech != 0){//�G���[�`�F�b�N
				_ASSERT(0);//�G���[�_�C�A���O��\��
	};




	return 0;//�����̐����ŏI�����������߂�B

};

/*�L�[�����X�V����֐�*/
int System::KeyRenewal( int SelectMode){


	 /*���������܂�*/

	for(int i=0; i < 20; i++){	
			keyin[i] = 0;
	}
	int imput1 = 0;
	int imput2 = 0;

	/*�@0.�g���K�[�L�[���H::1.�O�񉟂��ꂽ��*/
	int KeyTrigger1 = 0;
	int KeyTrigger2 = 0;

	 /*�����������܂�*/

	/*
	//�I���������[�h����g���K�[��ԂŎ擾����L�[�ϐ��������܂�
	*/

	if(SelectMode == 0){
			KeyTrigger1 = 0;
			KeyTrigger2 = 0;
	}
	if(SelectMode == 1){
			KeyTrigger1 = (1<<10)+(1<<13)+(1<<28);
			KeyTrigger2 = (1<<2);
	}


	for(int i = 0; i <= 30; i++){
				//������
				keyBox1[i][0] = 0;
				keyBox2[i][0] = 0;

				if(KeyTrigger1 & (1<<i)){//�����A�g���K�[����Ȃ�
									keyBox1[i][0] = 1;
				};
				if(KeyTrigger2 & (1<<i)){//�����A�g���K�[����Ȃ�
									keyBox2[i][0] = 1;
				};

				//�L�[��������
				if(GetAsyncKeyState(keydata1[i][1]) & 0x8000){//�L�[��������Ă�����
								imput1 = imput1 + keydata1[i][0];
								if((keyBox1[i][0] == 0) && (keyBox1[i][1] == 1)){
													imput1 = imput1 - keydata1[i][0];		
								}
								keyBox1[i][1] = 1; 
				}
				else{
					keyBox1[i][1] = 0; 
				}


				if(GetAsyncKeyState(keydata2[i][1]) & 0x8000){//�L�[��������Ă�����
								imput2 = imput2 + keydata2[i][0];
								if((keyBox2[i][0] == 0) && (keyBox2[i][1] == 1)){
													imput2 = imput2 - keydata2[i][0];
								}
								keyBox2[i][1] = 1; 
				}
				else{
						keyBox2[i][1] = 0; 
				}
	};



	/*
	//��L�ŉ����ꂽ�L�[�������ɃQ�[���{�҂Ŏg���f�[�^��g�ݗ��Ă܂�
	*/

	if(SelectMode == 0){//�������j���[�ł̌��o�Ȃ�
				if(imput1 & 1<<5){//�G���^�[
						keyin[0] = 1;
				}
				if(imput2 & 1<<19){//�o�b�N�X�y�[�X
						keyin[1] = 1;
				}
				if(imput1 & 1<<0){//��
						keyin[2] = 1;
				}
				if(imput1 & 1<<1){//��
						keyin[3] = 1;
				}
				if(imput1 & 1<<2){//��
						keyin[4] = 1;
				}
				if(imput1 & 1<<3){//��
						keyin[5] = 1;
				}
		}


	if(SelectMode == 1){//�����Q�[�����ł̌��o�Ȃ�
				if(imput1 & (1<<10)){//A�L�[�i���ֈړ��j
					keyin[0] = 1;
				}
				if(imput2 & (1<<2)){//W�L�[�i�O�i����j
						keyin[1] = 1;
				}
				if(imput1 & (1<<13)){//D�L�[�i�E�ֈړ��j
						keyin[2] = 1;
				}
				if(imput1 & (1<<28)){//S�L�[�i��ނ���j
						keyin[3] = 1;
				}
				if(imput1 & (1<<27)){//R�L�[�i�����[�h�j
						keyin[4] = 1;
				}
				if(imput1 & (1<<14)){//E�L�[�i���ׂ�j
						keyin[5] = 1;
				}
				if(imput1 & (1<<10)){//Q�L�[�i�Z���؂�ւ��j
						keyin[6] = 1;
				}
				if(imput2 & (1<<5)){//Z�L�[�i�����g�p�j
						keyin[7] = 1;
				}
				if(imput2 & (1<<18)){//�V�t�g�L�[�i�p���؂�ւ��j
						keyin[8] = 1;
				}
				if(imput1 & (1<<7)){//���N���b�N�i�e�����j
						keyin[9] = 1;
				}
				if(imput1 & (1<<8)){//�E�N���b�N�i�O���l�[�h�j
						keyin[10] = 1;
				}
				if(imput1 & (1<<4)){//�X�y�[�X�i�i���U���j
						keyin[11] = 1;
				}
				if(imput1 & (1<<5)){//�G���^�[�L�[�i���ׂ�j
						keyin[12] = 1;
				}
				if(imput2 & (1<<1)){//V�L�[�i����\�́j
						keyin[13]=1;
				}
				if(imput2 & (1<<17)){//�z�C�[���N���b�N�i���_�ς��j
						keyin[14] = 1;
				}
				if(imput2 & (1<<16)){//ESC�L�[
						keyin[15] = 1;
				}
		}


	/*
	//�Z���^�C�~���O�ŃL�[�����������ǂ����̌��o���s���܂�
	*/
		if(SelectMode == 1){//�����Q�[�����ł̌��o�Ȃ�
				for(int i=0; i<3; i++){//A�EW�ED�L�[��3��J��Ԃ�
						if( (keyin[i] == 0) && (KeyQuickPush[i][0] == 1) ){//�L�[��������ĂȂ��A�O��͉�����Ă����Ƃ�
								KeyQuickPush[i][1] = 5;//7���[�v��܂ŃJ�E���g����
						}
						if( KeyQuickPush[i][1] > 0){//7���[�v����
								KeyQuickPush[i][1] = KeyQuickPush[i][1] - 1;//���[�v�e�͉񐔂����炷
								if( keyin[i] == 1){//���̒��ŃL�[��������Ă���Ȃ�
										KeyQuickPush[i][2] = 1;//�_�b�V���t���O���I���ɂ���
								}
						}
						if( KeyQuickPush[i][2] == 1){//�_�b�V���t���O���I���Ȃ�
								keyinQuick[i] = 1;//�Q�[���_�b�V���t���O���I���ɂ���
								if( keyin[i] == 0){//�����A�u�_�b�V���t���O���I���ɂȂ��Ă���L�[��������ĂȂ��v�Ȃ�
										KeyQuickPush[i][2] = 0;//�_�b�V���L�[��������ĂȂ���Ԃɂ���
										keyinQuick[i] = 0;//�Q�[���_�b�V���t���O���I�t�ɂ���
								}
						}
						KeyQuickPush[i][0] = keyin[i];//�O��̃L�[�������܂�(�����[�v�Ŏg�p)
				}
		}

	/*
	//���Ƀ}�E�X���W���擾���܂��B
	*/

	GetCursorPos( &MousePos);//�}�E�X���W���i�[���܂�
	MousePos.x = MousePos.x - rewin.left;//�E�B���h�EX���W�̎擾
	MousePos.y = MousePos.y - rewin.top;//�E�B���h�EY���W�̎擾


	return 0;
}
/*���[�h��ʂ�`�悷��֐�*/
int System::WaitRender(){

	int ech = 0;//�G���[�`�F�b�N�ϐ�
	D3DXVECTOR3 SpritePos1( 0.0, -25.0, 0.0);//�w�i�̈ʒu
	//POINT TextPos;//�e�L�X�g�̍��W�ϐ�

	/*�`�揀�����s���܂�*/
	E3DBeginScene( scid1, 1, -1);
	E3DBeginSprite();

	ech = E3DRenderSprite( SpriteID[0], 640.0/1024.0, 480.0/512.0, SpritePos1);//�w�i
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
	};

	/*�����ŁA�`�抮��*/
	E3DEndSprite();

					/*����"�o�b�N�p�b�N"�̕`����s���܂�*/
					//TextPos.x = 440;/**/TextPos.y = 5;
					//E3DDrawTextByFontID( sys->scid1, TextID[0], TextPos, "�o�b�N�p�b�N", NormalColor1);

	E3DEndScene();
	E3DPresent(scid1);



	return 0;
}

/*�L�[������肷�邽�߂̊֐�*/
int System::GetKeyData( int *KeyDataArray){

	//�L�[�������ꂽ���̏����i�[���܂�
	for( int i=0; i<20; i++){
		*(KeyDataArray + i) = keyin[i];
	}


	return 0;
}