/*�I�y���[�V�������[�h�̊ւ��邱�Ƃ�����R�[�h�t�@�C���B
//
*/

#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "copsmenu.h"//�I�y���[�V�������[�h���j���[�֌W�̃N���X�w�b�_�t�@�C��
#include "coperation.h"//�I�y���[�V�����J�n�֌W�̃N���X�w�b�_�t�@�C��


/*�R���X�g���N�^�A�摜�̓ǂݍ��݂Ȃ�*/
OperationMenu::OperationMenu(){

	//�ϐ��̏�����
	int ech = 0;
	char loadname[256] = "";


	/*�X�v���C�g�����[�h���܂�*/
	wsprintf( loadname, "%s\\data\\img\\opration\\Ops_intro.png", System::path);//���j���[��ʂł̉摜�����[�h���܂��B
	ech = E3DCreateSprite( loadname, 0, 0, &OpsImgIDs[0]);
	
			_ASSERT( ech != 1 );//�G���[�`�F�b�N

	wsprintf( loadname, "%s\\data\\img\\menu\\menu_up_ber.png", System::path);//���j���[��ʂł̏㕔�����o�[�����[�h���܂��B
	ech = E3DCreateSprite( loadname, 0, 0, &OpsImgIDs[1]);
	
			_ASSERT( ech != 1 );//�G���[�`�F�b�N

	wsprintf( loadname, "%s\\data\\img\\opration\\Ops_sel.png", System::path);//���j���[��ʂł̑I���o�[�����[�h���܂��B
	ech = E3DCreateSprite( loadname, 0, 0, &OpsImgIDs[2]);
	
			_ASSERT( ech != 1 );//�G���[�`�F�b�N

	wsprintf( loadname, "%s\\data\\img\\menu\\menubg2.png", System::path);//���j���[��ʂł̔w�i�����[�h���܂��B
	ech = E3DCreateSprite( loadname, 0, 0, &OpsBGImg);
	
			_ASSERT( ech != 1 );//�G���[�`�F�b�N





	/*�A�C�e�����j���[�Ŏg������ID��ݒ肵�܂��B*/
	ech = E3DCreateFont( 35, 0, 800, 0, 0, 0, "MS P�S�V�b�N", &TextID[0]);//�啶��
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	ech = E3DCreateFont( 25, 0, 800, 0, 0, 0, "MS P�S�V�b�N", &TextID[1]);//�ʏ핶��
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	ech = E3DCreateFont( 18, 0, 800, 0, 0, 0, "MS P�S�V�b�N", &TextID[2]);//����������
	_ASSERT( ech != 1 );//�G���[�`�F�b�N


	return;
}
/*�f�X�R���g���N�^�A�摜�̔j���Ȃ�*/
OperationMenu::~OperationMenu(){

	//�ϐ��̏�����
	int ech = 0;

	/**/
	//�摜�̔j�����s���܂�
	/**/

	ech = E3DDestroySprite( OpsImgIDs[0]);//�摜���폜���܂��B
	
			_ASSERT( ech != 1 );//�G���[�`�F�b�N

	ech = E3DDestroySprite( OpsBGImg);//�w�i�摜���폜���܂��B
	
			_ASSERT( ech != 1 );//�G���[�`�F�b�N


	return;
}
/*�I�y���[�V�������[�h�̏������s���܂�*/
int OperationMenu::InOpsMenu(){

		//�ϐ��̏�����
		 ;//�L�[���z����쐬 
		int ech = 0;
		int ExitFlag = 0;//���̃t���O���I���ɂȂ����Ƃ��E�o���܂��B
		int SelectMission = -1;// ���̕ϐ��ɐ����������Ă���Ƃ��~�b�V�����ɓ���܂��B
		const char MissionName[5][30] = { "�V�΂̃u���X���b�h" , "���̊X�̂ǂ�����" , "�������匃��" , "���v��̂���X��" , "�ˌ�!�閧��n����!" };
		const char MissionDetal[5][200] ={
											"�X�̒������U�����܂��傤",
											"�_���꒬��T�����܂��傤",
											"�����M�I�����[���ɂł����܂��傤",
											"���g���X�ɂ��U�����ɍs���܂��傤",
											"�閧��n�O�ɐ������܂��傤"};
		D3DXVECTOR3 MainSpritePos( 0.0, -28.0, 0.0);//�w�i�̈ʒu
		D3DXVECTOR3 OpsIntroPos( 350.0, 70, 0.0);//�������摜�̈ʒu
		D3DXVECTOR3 MenuAboveBerPos( 380.0, 45.0, 0.0);//�㕔�̔����o�[
		D3DXVECTOR3 SelectImgPos( 30.0, 45.0, 0.0);//�I�𕔂̉摜���W
		E3DCOLOR4UC NormalColor = { 255,50,50,50};//���F�̑I�΂�Ă��Ȃ��F
		E3DCOLOR4UC SelectColor = { 255,130,150,20};//�ΐF�̑I�΂�Ă���F
		POINT TextPos;//�e�L�X�g�̍��W���i�[���܂�
		POINT TextPos2;//�e�L�X�g�̍��W���i�[���܂�

		while( WM_QUIT != System::msg.message ){

				System::MsgQ(30);//���b�Z�[�W���[�v
				System::KeyRenewal( 1);


				/* ****************
				 * �`�揀�����X����
				 * ****************
				 */

				E3DBeginScene( System::scid1, 0, -1);//�`��̊J�n����
				E3DBeginSprite();//�X�v���C�g�`��̊J�n

					//�w�i��`��
					ech = E3DRenderSprite( OpsBGImg, 640.0/1024.0, 480.0/512.0, MainSpritePos);
					_ASSERT( ech != 1 );//�G���[�`�F�b�N

					//���j���[�㕔�̃o�[��`��
					ech = E3DRenderSprite( OpsImgIDs[1], 1, 1, MenuAboveBerPos);
					_ASSERT( ech != 1 );//�G���[�`�F�b�N

					//���j���[�I�𕔂̉摜��`��
					ech = E3DRenderSprite( OpsImgIDs[2], 250.0/512.0, 360.0/512.0, SelectImgPos);
					_ASSERT( ech != 1 );//�G���[�`�F�b�N


					//�C���̐����摜��`��
					ech = E3DRenderSprite( OpsImgIDs[0], 250.0/512.0, 250.0/512.0, OpsIntroPos);
					_ASSERT( ech != 1 );//�G���[�`�F�b�N


				E3DEndSprite();//�X�v���C�g�`��̏I��
				/*�����܂łŉ�ʕ`�揀���I��*/

				/**/
				//������`�悵�܂�
				/**/

				//��ԏ�̃|�[�Y���j���[
				TextPos.x = 430;/**/TextPos.y = 5;
				E3DDrawTextByFontID( System::scid1, TextID[0], TextPos, "�I�y���[�V����", NormalColor);

				TextPos.y = 420;//60������
				ech = E3DDrawTextByFontID( System::scid1, TextID[1], TextPos, "�I�y���[�V�������I����", NormalColor);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
							return 1;//��肠��ŏI��
				};
	



				/* ////////////// */
				// �C�������ڂ��܂�
				/* ///////////// */
				TextPos.x = 50;/**/TextPos.y = 75;
				for( int i=0; i<5; i++ ){
						E3DDrawTextByFontID( System::scid1, TextID[1], TextPos, MissionName[i], NormalColor);
						
									_ASSERT( ech != 1 );//�G���[�`�F�b�N
						TextPos.y = TextPos.y + 35;
				}
				/* /////////////////////////////////////////// */
				// �}�E�X�J�[�\����u���Ă���C������ΐF�ɂ��܂�
				/* /////////////////////////////////////////// */
				TextPos.x = 50;/**/TextPos.y = 75;
				for( int i = 0; i<5; i++ ){

						/* �}�E�X�J�[�\���������͈͓̔��ɓ����Ă���Ȃ� */
						if( ( 50 < System::MousePos.x)&&( System::MousePos.x < 200) &&
							( 25 + TextPos.y < System::MousePos.y)&&( System::MousePos.y< TextPos.y + 45)){

									/* �I������Ă��邱�Ƃ������u�Ε����v��\������*/
									E3DDrawTextByFontID( System::scid1, TextID[1], TextPos, MissionName[i], SelectColor);
									_ASSERT( ech != 1 );//�G���[�`�F�b�N


									/* �I������Ă���~�b�V�������̏ڍׂȏ���\������*/
									TextPos2.x = 360;/**/TextPos2.y = 105;
									E3DDrawTextByFontID( System::scid1, TextID[2], TextPos2, MissionDetal[i], NormalColor);
									_ASSERT( ech != 1 );//�G���[�`�F�b�N	


									if(System::GetKeyData( System::KEY_LEFTMOUSE)){//�N���b�N������
											ExitFlag = 1;//���[�v�E�o�t���O���I���ɂ���B
											SelectMission = i;//�~�b�V�����ϐ��Ƀ~�b�V�����i���o�[������
									}
						}
						TextPos.y = TextPos.y + 35;
				}




				/**/
				//�}�E�X�ł�����W�ɗ�����c
				/**/
				if( ( 430 < System::MousePos.x)&&( System::MousePos.x < 600) &&
					( 450 < System::MousePos.y)&&( System::MousePos.y < 470)){//�}�E�X���W���u�I�y���[�V�������I����v�̏�Ȃ�
						
							TextPos.x = 430;/**/TextPos.y = 420;
							E3DDrawTextByFontID( System::scid1, TextID[1], TextPos, "�I�y���[�V�������I����", SelectColor);//�I������Ă��镶���ɂ���
							_ASSERT( ech != 1 );//�G���[�`�F�b�N

							if( System::GetKeyData( System::KEY_LEFTMOUSE)){//�N���b�N������
										ExitFlag = 1;//���[�v�E�o�t���O���I���ɂ���B
							}
				}


				E3DEndScene();
				ech = E3DPresent( System::scid1);
				
						_ASSERT( ech != 1 );//�G���[�`�F�b�N


				if( ExitFlag == 1 ){//�����Q�[�����[�v�𔲂���OK�Ȃ�
						break;//���[�v�𔲂���
				}
		}


		/* ���w�i�Ńt�F�[�h�A�E�g������*/
		System::SetFadeOutOfScid(20);
		if( SelectMission != -1){
				Operation OPS;//�I�y���[�V���������
				OPS.OpsMissionBranchStart( SelectMission);// �~�b�V�������J�n���܂�
		}



	return 0;
}