/*�����́A�ŏ��̃��j���[�Ɋւ��邱�Ƃ̃N���X�ł��B
//��ɍŏ��̉摜�����[�h�����菈���������肷��Ƃ���ɂ��ď�����Ă��܂��B
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "cfirstmenu.h"//���C�����j���[�Ɋւ��郁�j���N���X�w�b�_�t�@�C��




/*�ŏ��̃��j���[�̏������s���܂�*/
int MainMenu::InMainMenu(){

	//�ϐ��̏�����
	int ech = 0;
	int ExitFlag = 0;//���̃t���O���I���ɂȂ����Ƃ��E�o���܂��B
	int PushAlfa = 0;//PushKeyIMG�̓����x���w��
	int PushAlfaReduction = 1;//�����x�̑������w��
	int MenuMode = 0;
	int MenuSelectNo = 0;
	int keyin[20];//�L�[���z����쐬 
	D3DXVECTOR3 MainSpritePos( 0.0, -28.0, 0.0);//�w�i�̈ʒu
	D3DXVECTOR3 PushKeySpritePos( 180.0, 390.0, 0.0);//PushKeyIMG�̈ʒu
	D3DXVECTOR3 MenuSpritePos1( 150.0, 400, 0.0);//���[�h�̈ʒu
	D3DXVECTOR3 MenuSpritePos2( 270.0, 400, 0.0);//�w�i�̈ʒu
	D3DXVECTOR3 MenuSpritePos3( 390.0, 400, 0.0);//�w�i�̈ʒu


	while( WM_QUIT != System::msg.message ){

			//�ϐ��̏�����
			E3DCOLOR4UC AlfaColor = { PushAlfa,255,255,255};//�J���[�\���̂̔����߂̃f�[�^

			System::MsgQ(30);//���b�Z�[�W���[�v
			System::KeyRenewal( 0);
			System::GetKeyData(keyin);/*�L�[���擾����*/	
	
			

			/*�I�����[�h�̎����E����������*/
			if( MenuMode == 1){
				if( keyin[2] == 1) MenuSelectNo = MenuSelectNo - 1;
				if( keyin[4] == 1) MenuSelectNo = MenuSelectNo + 1;
				if( keyin[0] == 1) ExitFlag = 1;//���[�v����E�o

				if( MenuSelectNo == -1) MenuSelectNo = 3;
				if( MenuSelectNo == 4) MenuSelectNo = 1;
			}

			/*���j�����[�h���ŏ��ŃG���^�[�������ꂽ��*/
			if( (keyin[0] == 1) && (MenuMode == 0)) MenuMode = 1;//���[�h������

			/**/
			//�`�揀�����X����
			/**/
			E3DBeginScene( System::scid1, 0, -1);//�`��̊J�n����
			E3DBeginSprite();//�X�v���C�g�`��̊J�n

					ech = E3DRenderSprite( MainBGImg, 640.0/1024.0, 480.0/512.0, MainSpritePos);//
					_ASSERT( ech != 1 );//�G���[�`�F�b�N

					if( MenuMode == 0){
							ech = E3DRenderSprite( PushKeyImg, 300.0/512.0, 18.0/32.0, PushKeySpritePos);//
							_ASSERT( ech != 1 );//�G���[�`�F�b�N
					}

					if( MenuMode == 1){

						if( MenuSelectNo == 0){//���[�h�Q�[�����擪�Ȃ�
								ech = E3DRenderSprite( MenuSelectImg[0], 87.0/128.0, 12.0/16.0, MenuSpritePos1);//
								_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��
								ech = E3DRenderSprite( MenuSelectImg[1], 94.0/128.0, 12.0/16.0, MenuSpritePos2);//�I�΂�Ă������
								_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��
								ech = E3DRenderSprite( MenuSelectImg[2], 90.0/128.0, 12.0/16.0, MenuSpritePos3);//
								_ASSERT( ech != 1 );//�G���[�`�F�b�N
						}
						if( MenuSelectNo == 1){//�I�y���[�V�������擪�Ȃ�
								ech = E3DRenderSprite( MenuSelectImg[1], 94.0/128.0, 12.0/16.0, MenuSpritePos1);//
								_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��
								ech = E3DRenderSprite( MenuSelectImg[2], 90.0/128.0, 12.0/16.0, MenuSpritePos2);//�I�΂�Ă������
								_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��
								ech = E3DRenderSprite( MenuSelectImg[3], 58.0/64.0, 12.0/16.0, MenuSpritePos3);//
								_ASSERT( ech != 1 );//�G���[�`�F�b�N
						}
						if( MenuSelectNo == 2){//�I�����C�����擪�Ȃ�
								ech = E3DRenderSprite( MenuSelectImg[2], 90.0/128.0, 12.0/16.0, MenuSpritePos1);//
								_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��
								ech = E3DRenderSprite( MenuSelectImg[3], 58.0/64.0, 12.0/16.0, MenuSpritePos2);//�I�΂�Ă������
								_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��
								ech = E3DRenderSprite( MenuSelectImg[0], 87.0/128.0, 12.0/16.0, MenuSpritePos3);//
								_ASSERT( ech != 1 );//�G���[�`�F�b�N
						}
						if( MenuSelectNo == 3){//�j���[�Q�[�����擪�Ȃ�
								ech = E3DRenderSprite( MenuSelectImg[3], 58.0/64.0, 12.0/16.0, MenuSpritePos1);//
								_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��
								ech = E3DRenderSprite( MenuSelectImg[0], 87.0/128.0, 12.0/16.0, MenuSpritePos2);//�I�΂�Ă������
								_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��
								ech = E3DRenderSprite( MenuSelectImg[1], 94.0/128.0, 12.0/16.0, MenuSpritePos3);//
								_ASSERT( ech != 1 );//�G���[�`�F�b�N
						}
					}

			E3DEndSprite();//�X�v���C�g�`��̏I��
			/*�����܂łŉ�ʕ`�揀���I��*/
			E3DEndScene();
			ech = E3DPresent( System::scid1);
			
					_ASSERT( ech != 1 );//�G���[�`�F�b�N


			/**/
			//PushKeyImg�摜�̓����x���w�肷��
			/**/
			if( MenuMode == 0){
					ech = E3DSetSpriteARGB( PushKeyImg, AlfaColor);
					_ASSERT( ech != 1 );//�G���[�`�F�b�N

					if( PushAlfa == 255) PushAlfaReduction = -1;
					if( PushAlfa == 0) PushAlfaReduction = 1;
					PushAlfa = PushAlfa + ( 5 * PushAlfaReduction) ;
			}


			if( ExitFlag == 1 ){//�����Q�[�����[�v�𔲂���OK�Ȃ�
						break;//���[�v�𔲂���
			}


	}

	/*�����A�v���[�W���[����̏I�����߂������*/
	if( WM_QUIT == System::msg.message){
		 MenuSelectNo = -1;//�G���[��Ԃ�
	}


	/* ���w�i�Ńt�F�[�h�A�E�g������*/
	System::SetFadeOutOfScid(20);



	return MenuSelectNo;
}
/*�R���X�g���N�^*/
MainMenu::MainMenu(){

	//�ϐ��̏�����
	int ech = 0;
	char loadname[256] = "";

	/**/
	//�摜�̃��[�h
	/**/


	/*���C�����j���[�ɕ\��������ǎ������[�h���܂��B*/
	wsprintf( loadname, "%s\\data\\img\\mainmenu\\op1.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &MainBGImg);//�J�[�\���̃��[�h
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/*���C�����j���[�ɕ\��������v�b�V���L�[�摜�����[�h���܂��B*/
	wsprintf( loadname, "%s\\data\\img\\mainmenu\\pushkey.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &PushKeyImg);//�J�[�\���̃��[�h
	_ASSERT( ech != 1 );//�G���[�`�F�b�N


	/*���C�����j���[�ɕ\��������j���[�Q�[���摜�����[�h���܂��B*/
	wsprintf( loadname, "%s\\data\\img\\mainmenu\\newgame.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSelectImg[0]);//�J�[�\���̃��[�h
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/*���C�����j���[�ɕ\�������郍�[�h�Q�[���摜�����[�h���܂��B*/
	wsprintf( loadname, "%s\\data\\img\\mainmenu\\loadgame.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSelectImg[1]);//�J�[�\���̃��[�h
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/*���C�����j���[�ɕ\��������I�y���[�V�����摜�����[�h���܂��B*/
	wsprintf( loadname, "%s\\data\\img\\mainmenu\\operation.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSelectImg[2]);//�J�[�\���̃��[�h
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/*���C�����j���[�ɕ\��������I�����C���摜�����[�h���܂��B*/
	wsprintf( loadname, "%s\\data\\img\\mainmenu\\online.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSelectImg[3]);//�J�[�\���̃��[�h
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/*���C�����j���[��ɕ\�������鍕�w�i�����[�h���܂��B*/
	wsprintf( loadname, "%s\\data\\img\\oth\\black.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSelectImg[4]);//�J�[�\���̃��[�h
	_ASSERT( ech != 1 );//�G���[�`�F�b�N



	return;
}
/*�f�X�g���N�^*/
MainMenu::~MainMenu(){

	//�ϐ��̏�����
	int ech = 0;

	/**/
	//�摜�̔j�����s���܂�
	/**/

	ech = E3DDestroyHandlerSet( MainBGImg);//���f�����폜���܂�
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	ech = E3DDestroyHandlerSet( PushKeyImg);//���f�����폜���܂�
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	for(int i = 0;i < 5; i++){
			ech = E3DDestroyHandlerSet( MenuSelectImg[i]);//���f�����폜���܂�
			_ASSERT( ech != 1 );//�G���[�`�F�b�N
	}


	return;
}