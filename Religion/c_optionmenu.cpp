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

	int Garbage = 0;

	MakeFontButton_Auto(  "�I�v�V���������", &Garbage, 100, 320);
	MakeBalloon( "�e�̃����_�����O����(Quality,ON/OFF)", &Garbage, 300, 330, 100, 80, 320, 180);
	MakeBalloon( "�}�b�v���f�R�{�R�ۂ������鏈��(ON/OFF)", &Garbage, 295, 330, 100, 200, 320, 300);


	return;
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
			int SelectKind = 0;

			/* ��{���� */
			System::MsgQ(30);//���b�Z�[�W���[�v
			System::KeyRenewal(1);
			System::GetKeyData(keyin);


			/* �`�揀�����X���� */
			E3DBeginScene( System::scid1, 0, -1);//�`��̊J�n����
			
			/* ////////////////////////////// */
			// ��b���i�X�v���C�g�̕��i��`��
			/* ////////////////////////////// */
			E3DBeginSprite();//�X�v���C�g�`��̊J�n
					
			RenderBG();//�w�i�̕`��

			E3DEndSprite();//�X�v���C�g�`��̏I��
			
			/* ////////////////////// */
			// �����̕`����s�Ȃ��܂�
			/* ////////////////////// */

			//��ԏ��"�I�v�V����"�e�L�X�g
			PutString( "�I�v�V����", 440, 5, F_BIG, WHITE);

			PutString( "�e�̃����_�����O", 100, 80, F_STANDARD, WHITE);

			PutString( "�o���v�}�b�v", 100, 160, F_STANDARD, WHITE);

			/* ���̑��̕�����\�����܂� */

			PutBalloon_Auto( System::MousePos.x, System::MousePos.y);

			SelectKind = ChkFontButton( System::MousePos.x, System::MousePos.y);
			if( SelectKind == 0){
						if(keyin[9] == 1){//�N���b�N������
							ExitFlag = 1;//���[�v�E�o�t���O���I���ɂ���B
						}

			}



			/* //////////////// */
			/* �o���v�}�b�v�֘A 
			/* //////////////// */
			PutString( "ON", 120, 200, F_SMALL, WHITE);

			PutString( "OFF", 180, 200, F_SMALL, WHITE);

			/* �I�𒆂̕�����\�� */
			
			if((210< System::MousePos.y)&&( System::MousePos.y<250)){// �}�E�X���W��"ON"�̏�Ȃ�
						if((100< System::MousePos.x)&&(System::MousePos.x<170)){
								PutString( "ON", 120, 200, F_SMALL, BLUE);
								TextPos.x = 120;/**/TextPos.y = 200;

								// �N���b�N���ꂽ��
								if( keyin[9] == 1){
										BumpMapStatus = 1;
								}
						}
						if((180< System::MousePos.x)&&(System::MousePos.x<250)){
								PutString( "OFF", 180, 200, F_SMALL, BLUE);

								// �N���b�N���ꂽ��
								if( keyin[9] == 1){
										BumpMapStatus = 0;
								}
						}				
			}
			/* �����̕\�� */
			if( BumpMapStatus == 1){// �o���v�}�b�v��ON�̏�ԂȂ�
					PutString( "ON", 120, 200, F_SMALL, YELOW);
					
			}
			if( BumpMapStatus == 0){// �o���v�}�b�v��OFF�̏�ԂȂ�
					PutString( "OFF", 180, 200, F_SMALL, YELOW);
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


	return;
}