/*�����ł́A�Q�[�����̃��j���[�Ɋւ��邱�Ƃ̃N���X�ł��B
//��Ƀ|�[�Y���j���[�N���X�ƃh�b�O���j���[�N���X�ɂ��ď�����Ă��܂��B
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "c_optionmenu.h"// �I�v�V�������j���[�Ɋւ��邱�Ƃ�錾���Ă���w�b�_�t�@�C��
#include "cPoseMenu.h"//���j���[�N���X�Ɋւ���w�b�_�t�@�C��
#include "clive.h"//�G��L�����̐錾�w�b�_�t�@�C��
#include "cweapon.h"//����Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��
#include "c_batch_preparat.h"//�`��ɕK�v�ȃN���X�̐錾�w�b�_�t�@�C��
#include "citem_manipulate.h"//�A�C�e������Ɋւ���w�b�_�t�@�C��



/*�R���X�g���N�^�A���j���[�Ŏg���摜�̃��[�h*/
PoseMenu::PoseMenu(){

	/* �ϐ��̐錾&������ */
	int ButtonID = 0;
	int Garbage = 0;
	/* ���j���[�l�[���̓o�^���s�Ȃ��܂��B */
	const char MenuKindName[5][32] = {  "�Q�[���ɖ߂�" , "�o�b�N�p�b�N" , "�I�v�V����" ,
										"�~�b�V�����𒆒f����", "�Q�[�����I������" };
	const char MenuKindDetail[5][80] = {
			"�Q�[���{�҂ɖ߂�܂�",
			"�������̊m�F��A�C�e���̎g�p�Ȃǂ��o���܂�",
			"�Q�[�����̐ݒ肪�o���܂�",
			"�~�b�V�����𒆒f���āA���O�̏�Ԃɖ߂�܂�",
			"�Q�[�����I�����܂��A�f�[�^�̕ۑ��͍s���܂���"
	};

	for( int i=0; i<5; i++){

			MakeFontButton_Auto(  MenuKindName[i], &ButtonID, 100, 140 + 40 * i);
			MakeBalloonFromButton( MenuKindDetail[i], &Garbage, &ButtonID, 300, 330);
	}

	return;
}

/*�f�R���g���N�^�A���j���[�Ŏg�������̂̍폜���s���܂��B*/
PoseMenu::~PoseMenu(){

	return;
}


/*�|�[�Y���j���[�A�R�A�̕����ł��B*/
int PoseMenu::MainPoseMenu( PlayerChara *PC, Batch_Render *BatchPre ){

	/*�ϐ��̐錾*/
	int ech = 0;//�G���[�`�F�b�N�ϐ�
	int ExitFlag = 0;//���̃t���O���I���ɂȂ����Ƃ��E�o���܂��B
	const int DetailPossitionX[5] = { 400, 250, 400, 250, 230};// �ڍו�����X���W
	/* �e���j���[�̏ڂ������� */


	do{
			/*�ϐ��̐錾*/
			int SelectKind = -1;// �I�����Ă���A�C�e�������ʂ���ϐ�

			System::MsgQ(30);//���b�Z�[�W���[�v

			System::KeyRenewal(1);
			

			/*�`�揀�����X����*/
			E3DBeginScene( System::scid1, 0, -1);//�`��̊J�n����

			/*
			//�X�v���C�g��`���܂���B
			*/
			E3DBeginSprite();//�X�v���C�g�`��̊J�n
					
			RenderBG();//�w�i�̕`��

			E3DEndSprite();//�X�v���C�g�`��̏I��
			/*
			//�X�v���C�g�̕`��͂����܂ŁB
			//�@���ɕ����̕`����s���܂��B
			*/


			/* ///////////////////// */
			// �����̕\�����s�Ȃ��܂�
			/* ///////////////////// */

			//��ԏ�̃|�[�Y���j���[
			PutString( "�|�[�Y���j���[", 440, 5, F_BIG, WHITE);

			// �o���[���̕\�����s���܂�
			PutBalloon_Auto( System::MousePos.x, System::MousePos.y);

			//�ȉ��A���j���[�l�[��(�ʏ펞�E�I����)��\��
			SelectKind = ChkFontButton( System::MousePos.x, System::MousePos.y);


			/* ////////////////////////////////// */
			/* �N���b�N���ꂽ���̓����ݒ肵�܂� 
			/* ////////////////////////////////// */

			if( System::GetKeyData( System::KEY_LEFTMOUSE)){
					switch(SelectKind){
							case 0:{// �Q�[���ɖ߂�
									ExitFlag = 1;//���[�v�E�o�t���O���I���ɂ���B
									break;
							}
							case 1:{// �o�b�N�p�b�N
									Item_Manipulate BackPack( PC);//�o�b�N�p�b�N�����̉������܂�
									BackPack.InItemPack( PC);//�o�b�N�p�b�N�ɓ���܂�
									break;
							}
							case 2:{// �I�v�V����
									OptionMenu OptMenu;// �I�v�V�������j���[�����̉������܂�
									OptMenu.MainOptionMenu( BatchPre);// �I�v�V�������j���[�ɓ���܂�
									break;
							}
							case 3:{// �~�b�V�����𒆒f����

									break;
							}
							case 4:{// �Q�[�����I������
									SendMessage( System::hwnd, WM_CLOSE, 0, 0);
									break;
							}
					}
			}

			PutStetus(PC);//�X�e�[�^�X��\������N���X


			/* //////////////////////////
			// �����܂łŉ�ʕ`�揀���I��
			// ////////////////////////*/
			E3DEndScene();
			ech = E3DPresent( System::scid1);
			_ASSERT( ech != 1 );//�G���[�`�F�b�N
			

			if( ExitFlag == 1 ){//�����Q�[�����[�v�𔲂���OK�Ȃ�
						break;//���[�v�𔲂���
			}

	}while(WM_QUIT != System::msg.message);
	




	return 0;
}
/*���j���[��ʂɓ����āA�����I�ɒʏ�`�惂�[�h���烁�j���[��ʂɔ����߂��Ă����܂��B*/
int PoseMenu::FarstInMenu( Batch_Render *BatchPre, PlayerChara *PC){

	/*�ϐ��̐錾*/
	int ech = 0;//�G���[�`�F�b�N�ϐ�


	/*����ESC�L�[��������Ă��Ȃ�������*/
	if( System::GetKeyData( System::KEY_ESC) != 1){
			
			return 1;//�|�[�Y���j���[���N�����Ȃ�
	}

	/* ����p���`�F�b�N */
	BatchPre->BatchChkInView();

	/*�܂��͂��߂ɁA�ʏ��ʁ����j���[��ʂɂ��Ă����܂��B*/
	for(int i = 0; i<17; i++){

			/*�ϐ��̏�����*/

			E3DCOLOR4UC AlfaColor = { 15*i ,255,255,255};

			/*�ʏ��ʂ̃����_�����O*/
			BatchPre->BatchRender( 0);//�����_�����O

			/*�`�揀�����s���܂�*/
			E3DBeginScene( System::scid1, 1, -1);;
			E3DBeginSprite();

			RenderBG_Alpha(AlfaColor);

			/*�����ŁA�`�抮��*/
			E3DEndSprite();
			E3DEndScene();
			E3DPresent(System::scid1);

			
	}/*�����܂�*/

	MainPoseMenu( PC, BatchPre);//�|�[�Y���j���[�ɓ���


	/*�I�����̃��[�v�ɓ���܂��B*/
	for(int i = 0; i<17; i++){

			/*�ϐ��̏�����*/
			E3DCOLOR4UC AlfaColor = { 255-(15*i) ,255,255,255};

			/*�ʏ��ʂ̃����_�����O*/
			BatchPre->BatchRender( 0);//�����_�����O

			/*�`�揀�����s���܂�*/
			E3DBeginScene( System::scid1, 1, -1);;
			E3DBeginSprite();

			RenderBG_Alpha(AlfaColor);

			/*�����ŁA�`�抮��*/
			E3DEndSprite();
			E3DEndScene();
			E3DPresent(System::scid1);

			
	}/*�����܂�*/





	return 0;
}
/*�X�e�[�^�X�\�����s�����̂��܂Ƃ߂��֐��ł��B*/
int PoseMenu::PutStetus( PlayerChara *PC){

	//�ϐ��̏�����

	/*�v���C���[�L�����N�^�[�̃X�e�[�^�X�\��*/
	PutString( "HP 1000/1000", 80, 370, F_SMALL, WHITE);

	PutString( "STAMINA 100/100", 80, 390, F_SMALL, WHITE);

	PutString( "MAINWEAPON AMM:10/10 MAG:10/10", 80, 410, F_SMALL, WHITE);


	return 0;
}