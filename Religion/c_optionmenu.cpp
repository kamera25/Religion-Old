/*�����ł́A�I�v�V�������j���[�Ɋւ��邱�Ƃ̃N���X�\�[�X�t�@�C���ł��B
//
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "c_optionmenu.h"// �I�v�V�������j���[�Ɋւ��邱�Ƃ�錾���Ă���w�b�_�t�@�C��
#include "c_batch_preparat.h"//�`��ɕK�v�ȃN���X�̐錾�w�b�_�t�@�C��

/* �R���X�g���N�^�A���j���[�Ŏg���摜�̃��[�h */
OptionMenu::OptionMenu(){

	/*�ϐ��̐錾*/
	int ech = 0;//�G���[�`�F�b�N�ϐ�
	char loadname[256] = "";//���[�h����t�@�C�����̕�����z��


	/*�X�v���C�g�����[�h���܂�*/
	wsprintf( loadname, "%s\\data\\img\\menu\\menubg.png", System::path);//���j���[��ʂł̔w�i�����[�h���܂��B
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[0]);
	
			_ASSERT( ech != 1 );//�G���[�`�F�b�N

	wsprintf( loadname, "%s\\data\\img\\menu\\menuber.png", System::path);//���j���[��ʂł̏\���o�[�����[�h���܂��B
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[1]);
	
			_ASSERT( ech != 1 );//�G���[�`�F�b�N

	wsprintf( loadname, "%s\\data\\img\\menu\\menu_up_ber.png", System::path);//���j���[��ʂł̏㕔�����o�[�����[�h���܂��B
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[2]);
	
			_ASSERT( ech != 1 );//�G���[�`�F�b�N



	/*���j���[�Ŏg������ID��ݒ肵�܂��B*/
	ech = E3DCreateFont( 35, 0, 800, 0, 0, 0, "MS P�S�V�b�N", &TextID[0]);//�啶��
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	ech = E3DCreateFont( 30, 0, 800, 0, 0, 0, "MS P�S�V�b�N", &TextID[1]);//������
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	ech = E3DCreateFont( 25, 0, 800, 0, 0, 0, "MS P�S�V�b�N", &TextID[2]);//������
	_ASSERT( ech != 1 );//�G���[�`�F�b�N


}

/* �I�v�V�������j���[�̒����������s�Ȃ��܂� */
int OptionMenu::MainOptionMenu( Batch_Render *BatchPre){

	/* �ϐ��̏����� */
	int keyin[20];//�L�[���z����쐬
	int ech = 0;//�G���[�`�F�b�N�ϐ�
	int BumpMapStatus = 0;//�o���v�}�b�v�̏�ԕϐ� 
	const D3DXVECTOR3 SpritePos1( 0.0, -25.0, 0.0);//�w�i�̈ʒu
	const D3DXVECTOR3 SpritePos2( 0.0, -60.0, 0.0);//�\���o�[�̈ʒu
	const D3DXVECTOR3 SpritePos3( 380.0, 45.0, 0.0);//�㕔�̔����o�[
	const E3DCOLOR4UC NormalColor = { 255,255,255,255};//���F�̑I�΂�Ă��Ȃ��F
	const E3DCOLOR4UC SelectColor = { 255,200,220,20};//���F�̑I�΂�Ă���F
	const E3DCOLOR4UC SetColor = { 255,0,120,170};//�F�̕��킪�I�΂�Ă���F
	POINT TextPos;// �e�L�X�g�̍��W���i�[����ϐ�

	/* ////////////////////// */
	// ��Ԃ̎擾���s�Ȃ��܂�
	/* ////////////////////// */

	// �o���v�}�b�v
	BumpMapStatus = BatchPre->BatchGetBumpMapStatus();



	/* ���C�����[�v */
	do{
			/* �ϐ��̏����� */
			int ExitFlag = 0;// �E�o�t���O�ϐ�

			/* ��{���� */
			System::MsgQ(30);//���b�Z�[�W���[�v
			System::KeyRenewal(1);
			System::GetKeyData(keyin);


			/* �`�揀�����X���� */
			E3DBeginScene( System::scid1, 0, -1);//�`��̊J�n����

			E3DBeginSprite();//�X�v���C�g�`��̊J�n
			
			/* ////////////////////////////// */
			// ��b���i�X�v���C�g�̕��i��`��
			/* ////////////////////////////// */
			ech = E3DRenderSprite( MenuSpriteIDs[0], 640.0/1024.0, 480.0/512.0, SpritePos1);//�w�i�̈ʒu
			_ASSERT( ech != 1 );//�G���[�`�F�b�N
			
			ech = E3DRenderSprite( MenuSpriteIDs[1], 1, 1, SpritePos2);//�\���o�[�̈ʒu
			_ASSERT( ech != 1 );//�G���[�`�F�b�N

			ech = E3DRenderSprite( MenuSpriteIDs[2], 1, 1, SpritePos3);//�㕔�̔����o�[
			_ASSERT( ech != 1 );//�G���[�`�F�b�N

			E3DEndSprite();//�X�v���C�g�`��̏I��
			
			/* ////////////////////// */
			// �����̕`����s�Ȃ��܂�
			/* ////////////////////// */

			//��ԏ��"�I�v�V����"�e�L�X�g
			TextPos.x = 440;/**/TextPos.y = 5;
			E3DDrawTextByFontID( System::scid1, TextID[0], TextPos, "�I�v�V����", NormalColor);

			TextPos.x = 100;/**/TextPos.y = 80;
			E3DDrawTextByFontID( System::scid1, TextID[1], TextPos, "�e�̃����_�����O", NormalColor);
			if(ech != 0 ){//�G���[�`�F�b�N
						_ASSERT( 0 );//�G���[�_�C�A���O
						return 1;//��肠��ŏI��
			}

			TextPos.x = 100;/**/TextPos.y = 160;
			E3DDrawTextByFontID( System::scid1, TextID[1], TextPos, "�o���v�}�b�v", NormalColor);
			if(ech != 0 ){//�G���[�`�F�b�N
						_ASSERT( 0 );//�G���[�_�C�A���O
						return 1;//��肠��ŏI��
			}


			/* ���̑��̕�����\�����܂� */
			TextPos.x = 100;/**/TextPos.y = 320;
			ech = E3DDrawTextByFontID( System::scid1, TextID[2], TextPos, "�I�v�V���������", NormalColor);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			};

			/* �}�E�X���W�ɂ���ď�����ύX���܂� */
			if((100< System::MousePos.x)&&(System::MousePos.x<250) &&// �}�E�X���W���u�I�v�V���������v�̏�Ȃ�
				((340< System::MousePos.y)&&( System::MousePos.y<370))){
						TextPos.x = 100;/**/TextPos.y = 320;
						E3DDrawTextByFontID( System::scid1, TextID[2], TextPos, "�I�v�V���������", SelectColor);//�I������Ă��镶���ɂ���
						
						_ASSERT( ech != 1 );//�G���[�`�F�b�N

						if(keyin[9] == 1){//�N���b�N������
							ExitFlag = 1;//���[�v�E�o�t���O���I���ɂ���B
						}
			}
			if((100< System::MousePos.x)&&(System::MousePos.x<320) &&// �}�E�X���W���u�e�̃����_�����O�v��ւ�̏�Ȃ�
				((80< System::MousePos.y)&&( System::MousePos.y<180))){

					TextPos.x = 300;/**/TextPos.y = 330;
					E3DDrawTextByFontID( System::scid1, TextID[2], TextPos, "�e�̃����_�����O����(Quality,ON/OFF)", NormalColor);//������������Ă��镶�����\������
					
					_ASSERT( ech != 1 );//�G���[�`�F�b�N
			}
			if((100< System::MousePos.x)&&(System::MousePos.x<320) &&// �}�E�X���W���u�o���v�}�b�v�v��ւ�̏�Ȃ�
				((200< System::MousePos.y)&&( System::MousePos.y<300))){

					TextPos.x = 295;/**/TextPos.y = 330;
					E3DDrawTextByFontID( System::scid1, TextID[2], TextPos, "�}�b�v���f�R�{�R�ۂ������鏈��(ON/OFF)", NormalColor);//������������Ă��镶�����\������
					
					_ASSERT( ech != 1 );//�G���[�`�F�b�N
			}

			/* //////////////// */
			/* �o���v�}�b�v�֘A 
			/* //////////////// */
			TextPos.x = 120;/**/TextPos.y = 200;
			E3DDrawTextByFontID( System::scid1, TextID[2], TextPos, "ON", NormalColor);
			if(ech != 0 ){//�G���[�`�F�b�N
						_ASSERT( 0 );//�G���[�_�C�A���O
						return 1;//��肠��ŏI��
			}
			TextPos.x = 180;/**/TextPos.y = 200;
			E3DDrawTextByFontID( System::scid1, TextID[2], TextPos, "OFF", NormalColor);
			if(ech != 0 ){//�G���[�`�F�b�N
						_ASSERT( 0 );//�G���[�_�C�A���O
						return 1;//��肠��ŏI��
			}

			/* �I�𒆂̕�����\�� */
			
			if((210< System::MousePos.y)&&( System::MousePos.y<250)){// �}�E�X���W��"ON"�̏�Ȃ�
						if((100< System::MousePos.x)&&(System::MousePos.x<170)){
								TextPos.x = 120;/**/TextPos.y = 200;
								E3DDrawTextByFontID( System::scid1, TextID[2], TextPos, "ON", SelectColor);
								if(ech != 0 ){//�G���[�`�F�b�N
										_ASSERT( 0 );//�G���[�_�C�A���O
										return 1;//��肠��ŏI��
								}

								// �N���b�N���ꂽ��
								if( keyin[9] == 1){
										BumpMapStatus = 1;
								}
						}
						if((180< System::MousePos.x)&&(System::MousePos.x<250)){
								TextPos.x = 180;/**/TextPos.y = 200;
								E3DDrawTextByFontID( System::scid1, TextID[2], TextPos, "OFF", SelectColor);
								if(ech != 0 ){//�G���[�`�F�b�N
										_ASSERT( 0 );//�G���[�_�C�A���O
										return 1;//��肠��ŏI��
								}

								// �N���b�N���ꂽ��
								if( keyin[9] == 1){
										BumpMapStatus = 0;
								}
						}				
			}
			/* �����̕\�� */
			if( BumpMapStatus == 1){// �o���v�}�b�v��ON�̏�ԂȂ�
					TextPos.x = 120;/**/TextPos.y = 200;
					E3DDrawTextByFontID( System::scid1, TextID[2], TextPos, "ON", SetColor);
					if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
							return 1;//��肠��ŏI��
					}
			}
			if( BumpMapStatus == 0){// �o���v�}�b�v��OFF�̏�ԂȂ�
					TextPos.x = 180;/**/TextPos.y = 200;
					E3DDrawTextByFontID( System::scid1, TextID[2], TextPos, "OFF", SetColor);
					if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
							return 1;//��肠��ŏI��
					}
			}

			/* �o���v�}�b�v�����͂����܂� */




			/*�����܂łŉ�ʕ`�揀���I��*/
			E3DEndScene();
			ech = E3DPresent( System::scid1);
			
					_ASSERT( ech != 1 );//�G���[�`�F�b�N

			/* �����Q�[�����[�v�𔲂���OK�Ȃ� */
			if( ExitFlag == 1 ){
						break;//���[�v�𔲂���
			}


	}while(WM_QUIT != System::msg.message);


	/* //////////////////////// */
	// �ŏI�I�ȏ������s�Ȃ��܂� */
	/* //////////////////////// */
	BatchPre->BatchEnableBumpMap( BumpMapStatus);// �o���v�}�b�v�̓K��


	return 0;
}

/* �f�X�g���N�^�A�摜�̔j���Ȃǂ��s�Ȃ��܂� */
OptionMenu::~OptionMenu(){

	int ech = 0;//�G���[�`�F�b�N�ϐ�

	/*�X�v���C�g���폜���܂�*/
	for(int i = 0; i < 3; i++){
			ech = E3DDestroySprite( MenuSpriteIDs[i]);//���j���[��ʂł̔w�i���폜���܂��B
			
					_ASSERT( ech != 1 );//�G���[�`�F�b�N
	}

	
	/*����ID���폜���܂�*/
	for(int i = 0; i < 3; i++){
			ech = E3DDestroyFont( TextID[i]);//�啶��
			
					_ASSERT( ech != 1 );//�G���[�`�F�b�N
	}



}