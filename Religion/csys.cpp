/*�����ł́A�������E�I���E�v���[�W���[�ɓn���Ƃ����s�ׂ��s���N���X�R�[�h�t�@�C���ł��B
//
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "cWeapon_head.h"// ���퓝���Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��

/*�Ó��ϐ��̐錾*/
//
int System::UpdataSoundflag;//���������X�V���邩�̃t���O
int System::keyin[20];//�L�[��������Ă��邩�̏��z��
int System::scid2;// �t�F�[�h�A�E�g�Ŏg���X���b�v�`�F�C��

BOOL System::GotMes;//PeekMessage�̏�Ԃ��i�[����B

int System::scid1;//���C���X���b�v�`�F�C����ID
int System::keyinQuick[3];//�L�[��2�����ꂽ���i�[����z��ϐ�
int System::KeyQuickEnd;//�_�b�V�����삪�I�������Ƃ����ׂẴv�b�V�������Z�b�g����t���O�ϐ�
int System::MouseWhole;//�}�E�X�z�C�[���̈ړ��ʂ��i�[����ϐ�
int System::KeyQuickPush[3][3];//�L�[��2��A�ł����Ƃ��̏�������ϐ�
int System::SpriteID[2];//���[�h�����X�v���C�g���i�[���܂�

char System::path[256];//�v���O�������N�����Ă���p�X�̕�����

MSG System::msg;//���b�Z�[�W���i�[����\���́B
HWND System::hwnd;//�n���h���E�B���h�E���i�[����B
RECT System::rewin;//4�����W�̍\����
POINT System::MousePos;//�}�E�X�̈ʒu���i�[����Point�\����
POINT System::BeforeMousePos;//�O��̃}�E�X�̈ʒu���i�[����\����


// �R���X�g���N�^:Easy3D�̏������J�n�����B
System::System( const HINSTANCE chInst, const HWND chwnd){

	/*�ϐ���*/
	int ech = 0;//�G���[�`�F�b�N�p�̕ϐ��錾
	int index = 0;//�������ڂ�
	char loadname[256] = "";//���[�h����t�@�C�����̕�����z��
	char *p;//�|�C���^�A��납��
	char ch = '\\' ;//�������镶��
	char szpath[256] = "";//���s���̃p�X�����镶����ϐ�

	//�p�X�̎擾

	GetModuleFileName( chInst, szpath, 256);//���s���̃t�@�C�������擾
	
	p = strrchr(szpath,ch);//�Ō��\�����������T���B
	index = p - szpath;//�Ō��\�������Ƃ���܂ŕ�����������

	strncpy_s(path, szpath, index);//path�ϐ���szpath�ϐ�����Ō��\�܂ł̕������擾
	/* ******* */


	ech = E3DEnableDbgFile();//�f�o�b�O�e�L�X�g�o�͏���
	_ASSERT( ech != 1 );//�G���[�`�F�b�N


	ech = E3DInit( chInst, chwnd, 0, 16, 0, 1, 1, 1, 0, &scid1);//Easy3D�̏�����������B
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	ech = E3DSetProjection( 120.0, 100000.0, 60.0);//�v���W�F�N�V�����̐ݒ���s���܂�
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE);//���b�Z�[�W���[�v�ɏ�����Ԃ�(���܂��Ȃ�)

	//�ϐ�����

	hInst = chInst;
	hwnd = chwnd;

	/*�L�[�擾���߂̂��߂̃L�[�z�񂻂�1*/




	/*�L�[�擾���߂̂��߂̃L�[�z�񂻂�2*/


	/*�}�E�X���g�����߂ɏ��������܂�*/
	MousePos.x = 0;
	MousePos.y = 0;
	BeforeMousePos.x = 0;//X���W������
	BeforeMousePos.y = 0;//Y���W������
	KeyQuickEnd = 0;//�t���O�ϐ�������������
	UpdataSoundflag = 0;//���������X�V���Ȃ��i�f�t�H���g�j

	/*�ϐ��̏�����*/
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			KeyQuickPush[i][j] = 0;
		}
		keyinQuick[i] = 0;
	}



	/* **************
	// �X���b�v�`�F�C�����쐬����
	// **************
	*/

	ech = E3DCreateSwapChain( chwnd, &scid2);
	
			_ASSERT( ech != 1 );//�G���[�`�F�b�N


	/* **************
	// �Œ���K�v�ȉ摜�̃��[�h���s���܂�
	// **************
	*/

	// ���j���[��ʂł̏㕔�����o�[�����[�h���܂��B
	wsprintf( loadname, "%s\\data\\img\\sys\\loading.png", path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteID[0]);
	
			_ASSERT( ech != 1 );//�G���[�`�F�b�N

	// ��ʑS�̂��Â����邽�߂́A���摜
	wsprintf( loadname, "%s\\data\\img\\oth\\black.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteID[1]);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	
};
// �f�X�g���N�^:Easy3D�̏I���������s����B
System::~System(){

	/* �ϐ��̏����� */
	int ech = 0;//�G���[�`�F�b�N�p�̕ϐ��錾

	/* �摜�̔j�����s���܂� */
	for(int i=0; i<2; i++){
			ech = E3DDestroySprite( SpriteID[i]);
			_ASSERT( ech != 1 );//�G���[�`�F�b�N
	}

	/* �X���b�v�`�F�C�����폜 */
	ech = E3DDestroySwapChain(scid2);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/* Easy3D�I������ */
	ech = E3DBye();
	_ASSERT( ech != 1 );//�G���[�`�F�b�N


};
/* ���b�Z�[�W�̃��[�v���� */
int System::MsgQ( const int fps){

	/*������������*/

	int ech = 0;//�G���[�`�F�b�N�p�̕ϐ��錾
	int rfps = 0;//����Ȃ�FPS�v���p�̕ϐ��B
	MouseWhole = 0;//�}�E�X�z�C�[���̈ړ��ʂ�����������

	/* ���b�Z�[�W���[�v�̏��� */
	do{
			GotMes = PeekMessage( &msg, NULL, 0, 0, PM_REMOVE);
			if( msg.message == WM_QUIT){
						return 0;
			}
			if( GotMes != 0){//���b�Z�[�W��������
						DispatchMessage(&msg);
						TranslateMessage(&msg);
						GetWindowRect( hwnd, &rewin);
			}

	}while( GotMes != NULL );// ���b�Z�[�W�����Ă��Ȃ�������A���[�v�𔲂���


	ech = E3DWaitbyFPS( fps, &rfps);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/**/
	//���������X�V����or����
	/**/
	if( UpdataSoundflag != 0){

		/*���X�i�[�̈ʒu(�J�����ʒu)��ݒ�*/
		ech = E3DSet3DSoundListenerMovement( -1);
		_ASSERT( ech != 1 );//�G���[�`�F�b�N
		/*�����̍X�V���s���܂�*/
		ech = E3DUpdateSound();
		_ASSERT( ech != 1 );//�G���[�`�F�b�N
	}


	return 0;//�����̐����ŏI�����������߂�B

};
/* �L�[�����X�V����֐� */
int System::KeyRenewal( const int SelectMode){


	/* ������ & �錾���s���܂�*/
	static int KeyBox[30][2][2];// ���I�Ɏ擾�����L�[��������z��
	int imput[2] = { 0 , 0 };
	const int KeyTrigger[3][2] = // �g���K�[�ƂȂ�L�[�ԍ������ꂼ��̏󋵂Ŏw�肵��const�ϐ�
	{
		{ 0 , 0 },									// ���j���[��
		{ (1<<10)+(1<<13)+(1<<28)+(1<<8) , (1<<2) },		// �Q�[����,�A���s��
		{ (1<<7)+(1<<10)+(1<<13)+(1<<28)+(1<<8) , (1<<2) }	// �Q�[����,�A����
	};
	const int KeyData[2][30] = {// �L�[�̔ԍ����i�[�����ϐ�
		{
			0x25,//���L�[ 0
			0x26,//��L�[ 1
			0x27,//�E�L�[ 2
			0x28,//���L�[ 3
			0x20,//�X�y�[�X 4
			0x0D,//�G���^�[�L�[ 5
			0x11,//�R���g���[���L�[ 6
			0x01,//���N���b�N 7
			0x02,//�E�N���b�N 8
			0x09,//TAB 9

			0x41,//A�L�[ 10
			0x42,//B�L�[ 11
			0x43,//C�L�[ 12 
			0x44,//D�L�[ 13 
			0x45,//E�L�[ 14
			0x46,//F�L�[ 15
			0x47,//G�L�[ 16
			0x48,//H�L�[ 17
			0x49,//I�L�[ 18
			0x4A,//J�L�[ 19

			0x4B,//K�L�[ 20
			0x4C,//L�L�[ 21
			0x4D,//M�L�[ 22
			0x4E,//N�L�[ 23
			0x4F,//O�L�[ 24
			0x50,//P�L�[ 25
			0x51,//Q�L�[ 26
			0x52,//R�L�[ 27
			0x53,//S�L�[ 28
			0x54,//T�L�[ 29
		},
		{
			0x55,//U�L�[ 0
			0x56,//V�L�[ 1
			0x57,//W�L�[ 2
			0x58,//X�L�[ 3
			0x59,//Y�L�[ 4
			0x5A,//Z�L�[ 5

			0x30,//���C��0�L�[ 6
			0x31,//���C��1�L�[ 7
			0x32,//���C��2�L�[ 8
			0x33,//���C��3�L�[ 9
			0x34,//���C��4�L�[ 10
			0x35,//���C��5�L�[ 11 
			0x36,//���C��6�L�[ 12
			0x37,//���C��7�L�[ 13
			0x38,//���C��8�L�[ 14
			0x39,//���C��9�L�[ 15

			0x1B,//ESC�L�[ 16
			0x04,//�}�E�X�^�� 17 
			0x10,//�V�t�g�L�[ 18
			0x08,//�o�b�N�X�y�[�X 19
			0x12,//ALT�L�[ 20
			0x09,//TAB�L�[ 21

			0x70,//F1 22
			0x71,//F2 23
			0x72,//F3 24
			0x73,//F4 25
			0x74,//F5 26
			0x75,//F6 27
			0x76,//F7 28
			0x77,//F8 39
		}
	};
	const int ModeKeyCheck[3][2][20] = 
	{
		{// �������j���[�ł̌��o�Ȃ�
			{ 0, 1, 0, 0, 0, 0, -1},
			{ 1<<5, 1<<19, 1<<0, 1<<1, 1<<2, 1<<3, -1}
		},
		{// �����Q�[�����ł̌��o�Ȃ�(�A���s��)
			{ 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, -1},
			{ 1<<10, 1<<2, 1<<13,1<<28, 1<<27, 1<<14, 1<<10, 1<<5, 1<<18, 1<<7,
				1<<8, 1<<4, 1<<5, 1<<1, 1<<17, 1<<16, 1<<15, -1},
		},
		{// �����Q�[�����ł̌��o�Ȃ�(�A����) 
			{ 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, -1},
			{ 1<<10, 1<<2, 1<<13,1<<28, 1<<27, 1<<14, 1<<10, 1<<5, 1<<18, 1<<7,
				1<<8, 1<<4, 1<<5, 1<<1, 1<<17, 1<<16, 1<<15, -1},
		}
	};

	
	/* ���������܂� */ 
	for(int i=0; i < 20; i++){	
			keyin[i] = 0;
	}
	for( int i=0; i < 30; i++ ){
		for( int j=0; j < 2; j++ ){
			KeyBox[i][0][j] = 0;
		}
	}

	/* ������ & �錾�͂����܂� */

	for(int i=0; i < 30; i++){

		/* �ϐ��̏����� */
		const int NowBitShiftNum = 1<<i;

		for( int j=0; j<2; j++){
			if(KeyTrigger[SelectMode][j] & (1<<i)){
					KeyBox[i][0][j] = 1;
			};

			/* �L�[�������� */
			if(GetAsyncKeyState( KeyData[j][i] ) & 0x8000){//�L�[��������Ă�����
							imput[j] = imput[j] + NowBitShiftNum ;
							if( (KeyBox[i][0][j] == 0) && (KeyBox[i][1][j] == 1) ){
									imput[j] = imput[j] - NowBitShiftNum ;		
							}
							KeyBox[i][1][j] = 1; 
			}
			else{
				KeyBox[i][1][j] = 0; 
			}
		}
	}



	/*
	//��L�ŉ����ꂽ�L�[�������ɃQ�[���{�҂Ŏg���f�[�^��g�ݗ��Ă܂�
	*/
	for( int i=0; i<20; i++){
			const int NowImputNo = ModeKeyCheck[SelectMode][0][i];
			const int NowBitShiftNum = ModeKeyCheck[SelectMode][1][i];

			if( NowImputNo == -1) break;// ModeKeyCheck�ϐ����Ō�Ȃ�A���[�v�E�o
			if( imput[NowImputNo] & NowBitShiftNum){// �L�[��������Ă��邩�`�F�b�N���܂�
						keyin[i] = 1;
			}
	}
	
	/* ////////// */
	// !! ���� !!
	/* ////////// */

	/* �������j���[�ł̌��o�Ȃ� [SelectMode == 1] */
	//�G���^�[ 0
	//�o�b�N�X�y�[�X 1
	//�� 2
	//�� 3
	//�� 4
	//�� 5

	/* �����Q�[�����ł̌��o�Ȃ�( �A���s�� / �A���� ) [SelectMode == 1 OR 2] */
	//A�L�[�i���ֈړ��j0
	//W�L�[�i�O�i����j1
	//D�L�[�i�E�ֈړ��j2
	//S�L�[�i��ނ���j3
	//R�L�[�i�����[�h�j4
	//E�L�[�i�������ʒu�ς��j 5
	//Q�L�[�i�Z���؂�ւ��j 6
	//Z�L�[�i�����g�p�j 7
	//�V�t�g�L�[�i�p���؂�ւ��j8
	//���N���b�N�i�e�����j 9
	//�E�N���b�N�i�O���l�[�h�j 10
	//�X�y�[�X�i�i���U���j 11
	//�G���^�[�L�[�i���ׂ�j 12
	//V�L�[�i����\�́j 13
	//�z�C�[���N���b�N�i���_�ς��j14
	//ESC�L�[ 15
	//F�L�[ 16


	/*
	//�Z���^�C�~���O�ŃL�[�����������ǂ����̌��o���s���܂�
	*/
	if(( SelectMode == 1) || ( SelectMode == 2)){//�����Q�[�����ł̌��o�Ȃ�
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
/* ���[�h��ʂ�`�悷��֐� */
int System::WaitRender(){

	int ech = 0;//�G���[�`�F�b�N�ϐ�
	D3DXVECTOR3 SpritePos1( 0.0, -25.0, 0.0);//�w�i�̈ʒu
	//POINT TextPos;//�e�L�X�g�̍��W�ϐ�

	/*�`�揀�����s���܂�*/
	E3DBeginScene( scid1, 1, -1);
	E3DBeginSprite();

	ech = E3DRenderSprite( SpriteID[0], 640.0/1024.0, 480.0/512.0, SpritePos1);//�w�i
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/*�����ŁA�`�抮��*/
	E3DEndSprite();

					/*����"�o�b�N�p�b�N"�̕`����s���܂�*/
					//TextPos.x = 440;/**/TextPos.y = 5;
					//E3DDrawTextByFontID( System::scid1, TextID[0], TextPos, "�o�b�N�p�b�N", NormalColor1);

	E3DEndScene();
	E3DPresent(scid1);



	return 0;
}
/* �L�[������肷�邽�߂̊֐� */
int System::GetKeyData( int *KeyDataArray){

	//�L�[�������ꂽ���̏����i�[���܂�
	for( int i=0; i<20; i++){
		*(KeyDataArray + i) = keyin[i];
	}


	return 0;
}
/* ���������X�V���邩�ǂ����̊֐� */
int System::SetUpdataSoundSys( const int Soundflag){

	UpdataSoundflag = Soundflag;

	return 0;
}
/* �摜���t�F�[�h�A�E�g�����鏈���̊֐� */
int System::SetFadeOutOfScid( const int FadeTime){

	/*�ϐ��̏�����*/
	int ech = 0;
	D3DXVECTOR3 MainSpritePos( 0.0, -28.0, 0.0);// �w�i�̈ʒu
	E3DCOLOR4UC BlackColor = { 0,255,255,255};// ���w�i�̐F�\����

	/* **********
	// ���O�܂Ń����_�����O���Ă�����ʂ��X���b�v�`�F�C��(scid2)�ɃR�s�[
	// **********
	*/
	ech = E3DBeginScene( scid2, 1, -1);
	
	_ASSERT( ech != 1 );//�G���[�`�F�b�N
	ech = E3DEndScene();
	
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/* �����I�� */


	/* �J��Ԃ��̏���(�u���b�N�t�F�[�h�A�E�g����)*/
	for( int i=0; i<FadeTime; i++){

			MsgQ(30);//���b�Z�[�W���[�v

			
			/* �����x���X�V(i�J�E���^�ŕψ�) */
			BlackColor.a = i * (255 / FadeTime);

			/*���摜�̓����x���w�肷��*/
			ech = E3DSetSpriteARGB( SpriteID[1], BlackColor);
			
			_ASSERT( ech != 1 );//�G���[�`�F�b�N

			/* �����x���X�V(i�J�E���^�ŕψ�) */
			BlackColor.a = i * (255 / FadeTime);

			/*���摜�̓����x���w�肷��*/
			ech = E3DSetSpriteARGB( SpriteID[1], BlackColor);
			
			_ASSERT( ech != 1 );//�G���[�`�F�b�N

		
			/* **********
			// �����(scid2)���Ƀ����_�����O���܂�
			// **********
			*/

			ech = E3DBeginScene( scid2, 0, -1);
			
			_ASSERT( ech != 1 );//�G���[�`�F�b�N
			ech = E3DEndScene();
			
			_ASSERT( ech != 1 );//�G���[�`�F�b�N

			/* �����I�� */


			/* **********
			// scid2�̏�ɍ��摜(scid1�ɂ��)�������_�����O���܂�
			// **********
			*/

			ech = E3DBeginScene( scid1, 1, -1);
			
			_ASSERT( ech != 1 );//�G���[�`�F�b�N
			ech = E3DBeginSprite();//�X�v���C�g�`��̊J�n
			
			_ASSERT( ech != 1 );//�G���[�`�F�b�N
			
			/* **************************************** */
			/* �X�v���C�g(���ߕt�����摜)�������_�����O */
			/* **************************************** */

			ech = E3DRenderSprite( SpriteID[1], 1.0f, 1.0f, MainSpritePos);//���w�i
			_ASSERT( ech != 1 );//�G���[�`�F�b�N
			ech = E3DEndSprite();//�X�v���C�g�`��̏I��
			
			_ASSERT( ech != 1 );//�G���[�`�F�b�N

			/* �����I�� */

			ech = E3DEndScene();
			
			_ASSERT( ech != 1 );//�G���[�`�F�b�N
			ech = E3DPresent( System::scid1);
			
			_ASSERT( ech != 1 );//�G���[�`�F�b�N

	}





	return 0;
}
/* �e�N���X�����ɃL�[���̎擾��ύX����֐� */
int System::KeyRenewalFromWp( const Weapon_Head *Wpn, const int Equipment){
	
	if( ( Equipment == -1) || ( Equipment == 2)){// �����Ȃ����T�|�[�g����Ȃ�
			System::KeyRenewal(1);
	}
	else{
		if( Wpn->Get_WeaponPointer(Equipment)->Get_NowAmmo() != 0){
				System::KeyRenewal( Wpn->Get_WeaponPointer(Equipment)->Get_RapidFire() + 1);
		}
		else{
				System::KeyRenewal(1);
		}

	}


	return 0;
}
/* �}�E�X���W���Z�b�g����֐� */
int System::SetMouseCursol( const int X, const int Y){

	SetCursorPos( System::rewin.left + X, System::rewin.top + Y);

	return 0;
}
/* ���݂̃}�E�X���W��BeforeMousePos�ɃZ�b�g����֐� */
int System::SetMouseBeforePos(){

	/* �ϐ��̏����� */
	POINT BeforeMousePoseAddRewin;

	GetCursorPos( &BeforeMousePoseAddRewin);
	System::BeforeMousePos.x = BeforeMousePoseAddRewin.x - System::rewin.left;
	System::BeforeMousePos.y = BeforeMousePoseAddRewin.y - System::rewin.top;


	return 0;
}