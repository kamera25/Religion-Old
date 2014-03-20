/*�����ł́A�Q�[�����̃��j���[�Ɋւ��邱�Ƃ̃N���X�ł��B
//��Ƀ|�[�Y���j���[�N���X�ƃh�b�O���j���[�N���X�ɂ��ď�����Ă��܂��B
*/
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include "cstage.h"//�X�e�[�W�֌W�̃N���X�w�b�_�t�@�C��
#include "clive.h"//�G��L�����̐錾�w�b�_�t�@�C��
#include "c_batch_preparat.h"//�`��ɕK�v�ȃN���X�̐錾�w�b�_�t�@�C��
#include "cmenu.h"//���j���[�N���X�Ɋւ���w�b�_�t�@�C��
#include "citem_manipulate.h"//�A�C�e������Ɋւ���w�b�_�t�@�C��
#include "cweapon.h"//����Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��

//�����ɃO���[�o���ϐ���錾
extern System *sys;//�V�X�e���N���X���w���A�N���X�̃|�C���^


/*�R���X�g���N�^�A���j���[�Ŏg���摜�̃��[�h*/
Menu::Menu(){

	/*�ϐ��̐錾*/
	int ech = 0;//�G���[�`�F�b�N�ϐ�
	char loadname[256] = "";//���[�h����t�@�C�����̕�����z��


	/*�X�v���C�g�����[�h���܂�*/
	wsprintf( loadname, "%s\\data\\img\\menu\\menubg.png", sys->path);//���j���[��ʂł̔w�i�����[�h���܂��B
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[0]);
	if(ech != 0){//�G���[�`�F�b�N
				_ASSERT(0);//�G���[�_�C�A���O��\��
	};

	wsprintf( loadname, "%s\\data\\img\\menu\\menuber.png", sys->path);//���j���[��ʂł̏\���o�[�����[�h���܂��B
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[1]);
	if(ech != 0){//�G���[�`�F�b�N
				_ASSERT(0);//�G���[�_�C�A���O��\��
	};

	wsprintf( loadname, "%s\\data\\img\\menu\\menu_up_ber.png", sys->path);//���j���[��ʂł̏㕔�����o�[�����[�h���܂��B
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[2]);
	if(ech != 0){//�G���[�`�F�b�N
				_ASSERT(0);//�G���[�_�C�A���O��\��
	};



	/*���j���[�Ŏg������ID��ݒ肵�܂��B*/
	ech = E3DCreateFont( 35, 0, 800, 0, 0, 0, "MS P�S�V�b�N", &TextID[0]);//�啶��
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
	};

	ech = E3DCreateFont( 25, 0, 800, 0, 0, 0, "MS P�S�V�b�N", &TextID[1]);//������
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
	};


}

/*�f�R���g���N�^�A���j���[�Ŏg�������̂̍폜���s���܂��B*/
Menu::~Menu(){

	/*�ϐ��̐錾*/
	int ech = 0;//�G���[�`�F�b�N�ϐ�
	

	/*�X�v���C�g���폜���܂�*/
	ech = E3DDestroySprite( MenuSpriteIDs[0]);//���j���[��ʂł̔w�i���폜���܂��B
	if(ech != 0){//�G���[�`�F�b�N
				_ASSERT(0);//�G���[�_�C�A���O��\��
	};

	ech = E3DDestroySprite( MenuSpriteIDs[1]);//���j���[��ʂł̏\���o�[���폜���܂��B
	if(ech != 0){//�G���[�`�F�b�N
				_ASSERT(0);//�G���[�_�C�A���O��\��
	};

	ech = E3DDestroySprite( MenuSpriteIDs[2]);//���j���[��ʂł̏㕔�����o�[���폜���܂��B
	if(ech != 0){//�G���[�`�F�b�N
				_ASSERT(0);//�G���[�_�C�A���O��\��
	};


	/*����ID���폜���܂�*/
	ech = E3DDestroyFont( TextID[0]);//�啶��
	if(ech != 0){//�G���[�`�F�b�N
				_ASSERT(0);//�G���[�_�C�A���O��\��
	};

	ech = E3DDestroyFont( TextID[1]);//������
	if(ech != 0){//�G���[�`�F�b�N
				_ASSERT(0);//�G���[�_�C�A���O��\��
	};


}


/*�|�[�Y���j���[�A�R�A�̕����ł��B*/
int Menu::PoseMenu( PlayerChara *PC, Weapon *Wep){

	/*�ϐ��̐錾*/
	int ech = 0;//�G���[�`�F�b�N�ϐ�
	int ExitFlag = 0;//���̃t���O���I���ɂȂ����Ƃ��E�o���܂��B
	int keyin[20];//�L�[���z����쐬
	D3DXVECTOR3 SpritePos1( 0.0, -25.0, 0.0);//�w�i�̈ʒu
	D3DXVECTOR3 SpritePos2( 0.0, -60.0, 0.0);//�\���o�[�̈ʒu
	D3DXVECTOR3 SpritePos3( 380.0, 45.0, 0.0);//�㕔�̔����o�[
	E3DCOLOR4UC NormalColor = { 255,255,255,255};//���F�̑I�΂�Ă��Ȃ��F
	E3DCOLOR4UC SelectColor = { 255,200,220,20};//���F�̑I�΂�Ă���F
	POINT TextPos;//�����̈ʒu���i�[����\����


	do{

			sys->MsgQ(30);//���b�Z�[�W���[�v

			sys->KeyRenewal(1);
			
			sys->GetKeyData(keyin);//�L�[���擾����

			/*�`�揀�����X����*/
			E3DBeginScene( sys->scid1, 0, -1);//�`��̊J�n����

			/*
			//�X�v���C�g��`���܂���B
			*/
			E3DBeginSprite();//�X�v���C�g�`��̊J�n
					
			ech = E3DRenderSprite( MenuSpriteIDs[0], 640.0/1024.0, 480.0/512.0, SpritePos1);//�w�i�̈ʒu
			if(ech != 0 ){//�G���[�`�F�b�N
						_ASSERT( 0 );//�G���[�_�C�A���O
			};
					
			ech = E3DRenderSprite( MenuSpriteIDs[1], 1, 1, SpritePos2);//�\���o�[�̈ʒu
			if(ech != 0 ){//�G���[�`�F�b�N
						_ASSERT( 0 );//�G���[�_�C�A���O
			};

			ech = E3DRenderSprite( MenuSpriteIDs[2], 1, 1, SpritePos3);//�㕔�̔����o�[
			if(ech != 0 ){//�G���[�`�F�b�N
						_ASSERT( 0 );//�G���[�_�C�A���O
			};

			E3DEndSprite();//�X�v���C�g�`��̏I��
			/*
			//�X�v���C�g�̕`��͂����܂ŁB
			//�@���ɕ����̕`����s���܂��B
			*/

					//��ԏ�̃|�[�Y���j���[
					TextPos.x = 440;/**/TextPos.y = 5;
					E3DDrawTextByFontID( sys->scid1, TextID[0], TextPos, "�|�[�Y���j���[", NormalColor);

					//�ȉ��A�ʏ핶����\��
					TextPos.x = 100;
					TextPos.y = 140;//40��������
					E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "�Q�[���ɖ߂�", NormalColor);
					if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
							return 1;//��肠��ŏI��
					};

					TextPos.y = 180;//40��������
					E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "�o�b�N�p�b�N", NormalColor);
					if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
							return 1;//��肠��ŏI��
					};

					TextPos.y = 220;//40��������
					E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "�I�v�V����", NormalColor);
					if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
							return 1;//��肠��ŏI��
					};

					TextPos.y = 260;//40��������
					E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "�~�b�V�����𒆒f����", NormalColor);
					if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
							return 1;//��肠��ŏI��
					};

					TextPos.y = 300;//40��������
					E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "�Q�[�����I������", NormalColor);
					if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
							return 1;//��肠��ŏI��
					};
			




			/*�}�E�X���I�𕔂ɂ���Ƃ��A������ύX���܂�*/
			if((100< sys->MousePos.x)&&(sys->MousePos.x<250)){	
					if((160< sys->MousePos.y)&&( sys->MousePos.y<190)){//�}�E�X���W���u�Q�[���ɖ߂�v�̏�Ȃ�
							TextPos.x = 100;
							TextPos.y = 140;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "�Q�[���ɖ߂�", SelectColor);//�I������Ă��镶���ɂ���
							if(ech != 0){//�G���[�`�F�b�N
										_ASSERT(0);//�G���[�_�C�A���O��\��
							};
							TextPos.x = 400;
							TextPos.y = 330;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "�Q�[���{�҂ɖ߂�܂�", NormalColor);//������������Ă��镶�����\������
							if(ech != 0){//�G���[�`�F�b�N
										_ASSERT(0);//�G���[�_�C�A���O��\��
							};
							if(keyin[9] == 1){//�N���b�N������
										ExitFlag = 1;//���[�v�E�o�t���O���I���ɂ���B
							}
					}	

					if((200< sys->MousePos.y)&&( sys->MousePos.y<230)){//�}�E�X���W���u�o�b�N�p�b�N�v�̏�Ȃ�
							TextPos.x = 100;
							TextPos.y = 180;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "�o�b�N�p�b�N", SelectColor);//�I������Ă��镶���ɂ���
							if(ech != 0){//�G���[�`�F�b�N
										_ASSERT(0);//�G���[�_�C�A���O��\��
							};
							TextPos.x = 250;
							TextPos.y = 330;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "�������̊m�F��A�C�e���̎g�p�Ȃǂ��o���܂�", NormalColor);//������������Ă��镶�����\������
							if(ech != 0){//�G���[�`�F�b�N
										_ASSERT(0);//�G���[�_�C�A���O��\��
							};
							if(keyin[9] == 1){//�N���b�N������
										Item_Manipulate BackPack( PC, Wep);//�o�b�N�p�b�N���Ăяo���܂��B
										BackPack.InItemPack( PC);//�o�b�N�p�b�N�ɓ���܂�
							}
					}

					if((240< sys->MousePos.y)&&( sys->MousePos.y<270)){//�}�E�X���W���u�I�v�V�����v�̏�Ȃ�
							TextPos.x = 100;
							TextPos.y = 220;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "�I�v�V����", SelectColor);//�I������Ă��镶���ɂ���
							if(ech != 0){//�G���[�`�F�b�N
										_ASSERT(0);//�G���[�_�C�A���O��\��
							};
							TextPos.x = 400;
							TextPos.y = 330;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "�Q�[�����̐ݒ肪�o���܂�", NormalColor);//������������Ă��镶�����\������
							if(ech != 0){//�G���[�`�F�b�N
										_ASSERT(0);//�G���[�_�C�A���O��\��
							};
					}

					if((280< sys->MousePos.y)&&( sys->MousePos.y<310)){//�}�E�X���W���u�Q�[���ɖ߂�v�̏�Ȃ�
							TextPos.x = 100;
							TextPos.y = 260;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "�~�b�V�����𒆒f����", SelectColor);//�I������Ă��镶���ɂ���
							if(ech != 0){//�G���[�`�F�b�N
										_ASSERT(0);//�G���[�_�C�A���O��\��
							};
							TextPos.x = 250;
							TextPos.y = 330;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "�~�b�V�����𒆒f���āA���O�̏�Ԃɖ߂�܂�", NormalColor);//������������Ă��镶�����\������
							if(ech != 0){//�G���[�`�F�b�N
										_ASSERT(0);//�G���[�_�C�A���O��\��
							};
					}

					if((320< sys->MousePos.y)&&( sys->MousePos.y<350)){//�}�E�X���W���u�Q�[���ɖ߂�v�̏�Ȃ�
							TextPos.x = 100;
							TextPos.y = 300;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "�Q�[�����I������", SelectColor);//�I������Ă��镶���ɂ���
							if(ech != 0){//�G���[�`�F�b�N
										_ASSERT(0);//�G���[�_�C�A���O��\��
							};
							TextPos.x = 230;
							TextPos.y = 330;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "�Q�[�����I�����܂��A�f�[�^�̕ۑ��͍s���܂���", NormalColor);//������������Ă��镶�����\������
							if(ech != 0){//�G���[�`�F�b�N
										_ASSERT(0);//�G���[�_�C�A���O��\��
							};
							if(keyin[9] == 1){//�N���b�N������
										SendMessage( sys->hwnd, WM_CLOSE, 0, 0);
							}
					}
			}


			PutStetus(PC);//�X�e�[�^�X��\������N���X


			/*�����܂łŉ�ʕ`�揀���I��*/
			E3DEndScene();
			ech = E3DPresent( sys->scid1);
			if(ech != 0){//�G���[�`�F�b�N
						_ASSERT(0);//�G���[�_�C�A���O��\��
			};
			

			if( ExitFlag == 1 ){//�����Q�[�����[�v�𔲂���OK�Ȃ�
						break;//���[�v�𔲂���
			}

	}while(WM_QUIT != sys->msg.message);
	




	return 0;
}
/*���j���[��ʂɓ����āA�����I�ɒʏ�`�惂�[�h���烁�j���[��ʂɔ����߂��Ă����܂��B*/
int Menu::FarstInMenu( Batch_Preparat *BatchPre, PlayerChara *PC, Weapon *Wep){

	/*�ϐ��̐錾*/
	int keyin[20];//�L�[���z����쐬

	sys->GetKeyData(keyin);//�L�[���擾����

	/*����ESC�L�[��������Ă�����*/
	if(keyin[15] == 1){

			/*�܂��͂��߂ɁA�ʏ��ʁ����j���[��ʂɂ��Ă����܂��B*/
			for(int i = 0; i<17; i++){

					/*�ϐ��̏�����*/
					int ech = 0;//�G���[�`�F�b�N�ϐ�
					E3DCOLOR4UC AlfaColor = { 15*i ,255,255,255};
					D3DXVECTOR3 SpritePos1( 0.0, -25.0, 0.0);//�w�i�̈ʒu
					D3DXVECTOR3 SpritePos2( 0.0, -60.0, 0.0);//�\���o�[�̈ʒu
					D3DXVECTOR3 SpritePos3( 380.0, 45.0, 0.0);//�㕔�̔����o�[

					/*�ʏ��ʂ̃����_�����O*/
					BatchPre->BatchChkInView();//����p���`�F�b�N
					BatchPre->BatchRender( 0);//�����_�����O

					/*�e�N�X�`���ɃA���t�@��K������*/
					for(int i = 0; i<3; i++){
							ech = E3DSetSpriteARGB( MenuSpriteIDs[i], AlfaColor);
							if(ech != 0 ){//�G���[�`�F�b�N
										_ASSERT( 0 );//�G���[�_�C�A���O
							};
					}

					/*�`�揀�����s���܂�*/
					E3DBeginScene( sys->scid1, 1, -1);;
					E3DBeginSprite();


					ech = E3DRenderSprite( MenuSpriteIDs[0], 640.0/1024.0, 480.0/512.0, SpritePos1);//�w�i�̈ʒu
					if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
					};
			
					ech = E3DRenderSprite( MenuSpriteIDs[1], 1, 1, SpritePos2);//�\���o�[�̈ʒu
					if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
					};

					ech = E3DRenderSprite( MenuSpriteIDs[2], 1, 1, SpritePos3);//�㕔�̔����o�[
					if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
					};

					/*�����ŁA�`�抮��*/
					E3DEndSprite();
					E3DEndScene();
					E3DPresent(sys->scid1);

			
			}/*�����܂�*/


			PoseMenu( PC, Wep);//�|�[�Y���j���[�ɓ���


			/*�I�����̃��[�v�ɓ���܂��B*/
			for(int i = 0; i<17; i++){

					/*�ϐ��̏�����*/
					int ech = 0;//�G���[�`�F�b�N�ϐ�
					E3DCOLOR4UC AlfaColor = { 255-(15*i) ,255,255,255};
					D3DXVECTOR3 SpritePos1( 0.0, -25.0, 0.0);//�w�i�̈ʒu
					D3DXVECTOR3 SpritePos2( 0.0, -60.0, 0.0);//�\���o�[�̈ʒu
					D3DXVECTOR3 SpritePos3( 380.0, 45.0, 0.0);//�㕔�̔����o�[

					/*�ʏ��ʂ̃����_�����O*/
					BatchPre->BatchChkInView();//����p���`�F�b�N
					BatchPre->BatchRender( 0);//�����_�����O

					/*�e�N�X�`���ɃA���t�@��K������*/
					for(int i = 0; i<3; i++){
							ech = E3DSetSpriteARGB( MenuSpriteIDs[i], AlfaColor);
							if(ech != 0 ){//�G���[�`�F�b�N
										_ASSERT( 0 );//�G���[�_�C�A���O
							};
					}

					/*�`�揀�����s���܂�*/
					E3DBeginScene( sys->scid1, 1, -1);;
					E3DBeginSprite();


					ech = E3DRenderSprite( MenuSpriteIDs[0], 640.0/1024.0, 480.0/512.0, SpritePos1);//�w�i�̈ʒu
					if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
					};
			
					ech = E3DRenderSprite( MenuSpriteIDs[1], 1, 1, SpritePos2);//�\���o�[�̈ʒu
					if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
					};

					ech = E3DRenderSprite( MenuSpriteIDs[2], 1, 1, SpritePos3);//�㕔�̔����o�[
					if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
					};

					/*�����ŁA�`�抮��*/
					E3DEndSprite();
					E3DEndScene();
					E3DPresent(sys->scid1);

			
			}/*�����܂�*/



	}


	return 0;
}
/*�X�e�[�^�X�\�����s�����̂��܂Ƃ߂��֐��ł��B*/
int Menu::PutStetus( PlayerChara *PC){

	//�ϐ��̏�����
	int ech = 0;//�G���[�`�F�b�N�ϐ�
	POINT TextPos;//�����̈ʒu���i�[����\����
	char StatusName[128] = "";//�X�e�[�^�X�\���Ŏg����ʕ�����
	E3DCOLOR4UC NormalColor = { 255,255,255,255};//���F�̑I�΂�Ă��Ȃ��F
	E3DCOLOR4UC SelectColor = { 255,200,220,20};//���F�̑I�΂�Ă���F

	/*�v���C���[�L�����N�^�[�̃X�e�[�^�X�\��*/
	TextPos.x = 80;
	TextPos.y = 370;
	wsprintf( StatusName, "HP 1000/1000" );//HP�̕\��
	E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, StatusName, NormalColor);//������������Ă��镶�����\������
	if(ech != 0){//�G���[�`�F�b�N
				_ASSERT(0);//�G���[�_�C�A���O��\��
	};
	TextPos.x = 80;
	TextPos.y = 390;
	wsprintf( StatusName, "STAMINA 100/100" );//�X�^�~�i�̕\��
	E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, StatusName, NormalColor);//������������Ă��镶�����\������
	if(ech != 0){//�G���[�`�F�b�N
				_ASSERT(0);//�G���[�_�C�A���O��\��
	};
	TextPos.x = 80;
	TextPos.y = 430;
	wsprintf( StatusName, "MAINWEAPON AMM:10/10 MAG:10/10" );//���C���E�F�|����MAG���AAMM��
	E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, StatusName, NormalColor);//������������Ă��镶�����\������
	if(ech != 0){//�G���[�`�F�b�N
				_ASSERT(0);//�G���[�_�C�A���O��\��
	};







	return 0;
}