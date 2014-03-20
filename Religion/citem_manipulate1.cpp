/*�����́A�A�C�e������Ɋւ��邱�Ƃ̃N���X�ł��B
//��Ƀo�b�N�p�b�N��A�C�e�������ɂ��ď�����Ă��܂��B
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "citem_manipulate.h"//�A�C�e������Ɋւ���w�b�_�t�@�C��
#include "clive.h"//�G��L�����̐錾�w�b�_�t�@�C��
#include "cweapon.h"//����Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��
#include "citem.h"//�A�C�e���̐錾�w�b�_�t�@�C��




/*�R���X�g���N�^�A�A�C�e���̃X�v���C�g�Ȃǂ����[�h���܂�*/
Item_Manipulate::Item_Manipulate( PlayerChara *PC){

	/*�ϐ��̐錾*/
	int ech = 0;//�G���[�`�F�b�N�ϐ�
	char loadname[256] = "";//���[�h����t�@�C�����̕�����z��
	E3DCOLOR4UC AlfaColor = { 200,255,255,255};//�A�C�e���̏ڍׂ������摜�̔�����
	
	/* �����o�ϐ��̏����� */
	MenuMode = 0;
	ItemSysSetPos.x = 0;
	ItemSysSetPos.y = 0;

	/* ********************** 
	// �摜�̃��[�h���s���܂�
	// **********************
	*/

	/*�X�v���C�g�����[�h���܂�*/
	wsprintf( loadname, "%s\\data\\img\\menu\\menubg.png", System::path);//���j���[��ʂł̔w�i�����[�h���܂��B
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[0]);
	_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��


	wsprintf( loadname, "%s\\data\\img\\menu\\menuber.png", System::path);//���j���[��ʂł̏\���o�[�����[�h���܂��B
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[1]);
	_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

	wsprintf( loadname, "%s\\data\\img\\menu\\menu_up_ber.png", System::path);//���j���[��ʂł̏㕔�����o�[�����[�h���܂��B
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[2]);
	_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��


	wsprintf( loadname, "%s\\data\\img\\menu\\loading.png", System::path);//���[�h�摜�̃��[�h���܂��B
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[3]);
	_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��


	wsprintf( loadname, "%s\\data\\img\\item\\itstate.png", System::path);//���[�h�摜�̃��[�h���܂��B
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[4]);
	_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

	wsprintf( loadname, "%s\\data\\img\\item\\cure.png", System::path);//�񕜃A�C�R���̃��[�h�摜�̃��[�h���܂��B
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[5]);
	_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

	wsprintf( loadname, "%s\\data\\img\\item\\dump.png", System::path);//�S�~���A�C�R���̃��[�h�摜�̃��[�h���܂��B
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[6]);
	_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��


	wsprintf( loadname, "%s\\data\\img\\item\\info.png", System::path);//���A�C�R���̃��[�h�摜�̃��[�h���܂��B
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[7]);
	_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��


	wsprintf( loadname, "%s\\data\\img\\item\\supply.png", System::path);//�����}�[�N�̃��[�h�摜�̃��[�h���܂��B
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[8]);
	_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��



	ech = E3DSetSpriteARGB( MenuSpriteIDs[4], AlfaColor);
	_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

	/* ****************
	// ���[�h��ʂ̕\��
	// ****************
	*/
	D3DXVECTOR3 SpritePos4( 250.0, 170.0, 0.0);//���[�h�摜�̈ʒu
	/*�`�揀�����s���܂�*/
	E3DBeginScene( System::scid1, 1, -1);;
	E3DBeginSprite();

	ech = E3DRenderSprite( MenuSpriteIDs[3], 1, 1, SpritePos4);//���[�h�̉摜
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/*�����ŁA�`�抮��*/
	E3DEndSprite();

	E3DEndScene();
	E3DPresent(System::scid1);

	/* ******************************
	// �A�C�e���n�̉摜�����[�h���܂�
	// ******************************
	*/

	PC->Wpn.Get_WeaponPointer(PC->Get_Wp_equipment())->Get_Sprite();

	/*���ɕ���̉摜��ǂݍ��݂܂�*/
	for( int i = 0; i<3; i++){
			if( PC->Wpn.Get_WeaponPointer(i) != NULL){//�������Ă����
					BackPack_Weapon[i][0] = PC->Wpn.Get_WeaponPointer(i)->Get_Sprite() ;//�摜�f�[�^�����[�h����
					BackPack_Weapon[i][1] = PC->Wpn.Get_WeaponPointer(i)->Get_Kind();//����̎�ނ�������
					BackPack_Weapon[i][2] = PC->Wpn.Get_WeaponPointer(i)->Get_Number();//����̃i���o�[��������
			}
			else{//�������Ă��Ȃ���� -> ��f�[�^���[�h���܂�
					wsprintf( loadname, "%s\\data\\img\\item\\empty.png", System::path);//��A�C�e���摜�����[�h���܂��B
					ech = E3DCreateSprite( loadname, 0, 0, &BackPack_Weapon[i][0]);
					_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

					BackPack_Weapon[i][1] = -1;//����̎�ނ���ɂ���
					BackPack_Weapon[i][2] = -1;//����̃i���o�[����ɂ���
			}
	}

	
	if( PC->Item.GetItemNumber( 0, -1, -1) == 0){//�X�e�[�W�ŏE��������̏���
			wsprintf( loadname, "%s\\data\\img\\item\\empty.png", System::path);
			ech = E3DCreateSprite( loadname, 0, 0, &BackPack_Weapon[3][0]);
			_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

			BackPack_Weapon[3][1] = -1;//����̎�ނ���ɂ���
			BackPack_Weapon[3][2] = -1;//����̃i���o�[����ɂ���
			//BackPack_Weapon[3] = GetLoadSprite();
	}

	/*���ɒe��̉摜��ǂݍ��݂܂�*/
	for( int i=0; i<4; i++){
			if( PC->Item.GetItemNumber( 1, i, -1) != -1){//�������Ă����
					//BackPack_Ammo[i][0] = PC->wp_data[i][0][1];//��摜�f�[�^�����[�h����
					wsprintf( loadname, "%s\\data\\img\\item\\empty.png", System::path);//1���I�ɋ�A�C�e���摜�����[�h���܂��B
					ech = E3DCreateSprite( loadname, 0, 0, &BackPack_Ammo[i][0]);
					_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

					BackPack_Ammo[i][1] = PC->Item.GetItemNumber( 1, i, -1);//����̎�ނ�������
			}
			else{//�������Ă��Ȃ���� -> ��f�[�^���[�h���܂�
					wsprintf( loadname, "%s\\data\\img\\item\\empty.png", System::path);//��A�C�e���摜�����[�h���܂��B
					ech = E3DCreateSprite( loadname, 0, 0, &BackPack_Ammo[i][0]);
					_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

					BackPack_Ammo[i][1] = -1;//����̃i���o�[����ɂ���
			}
	}

	/*���ɂ̉摜��ǂݍ��݂܂�*/
	for( int i=0; i<5; i++){
			if( PC->Item.GetItemNumber( 2, i, 0) != -1){//�������Ă����
					//BackPack_Ammo[i][0] = PC->Recovery[i][0];//��摜�f�[�^�����[�h����
					wsprintf( loadname, "%s\\data\\img\\item\\empty.png", System::path);//1���I�ɋ�A�C�e���摜�����[�h���܂��B
					ech = E3DCreateSprite( loadname, 0, 0, &BackPack_Recovery[i][0]);
					_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

					BackPack_Recovery[i][1] = PC->Item.GetItemNumber( 2, i, 0);//����̎�ނ�������
			}
			else{//�������Ă��Ȃ���� -> ��f�[�^���[�h���܂�
					wsprintf( loadname, "%s\\data\\img\\item\\empty.png", System::path);//��A�C�e���摜�����[�h���܂��B
					ech = E3DCreateSprite( loadname, 0, 0, &BackPack_Recovery[i][0]);
					_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

					BackPack_Recovery[i][1] = -1;//����̃i���o�[����ɂ���
			}
	}

	/* ******************
	// �t�H���g�̓ǂݍ���
	// ******************
	*/
	ech = E3DCreateFont( 35, 0, 800, 0, 0, 0, "MS P�S�V�b�N", &TextID[0]);//�啶��
	_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

	ech = E3DCreateFont( 25, 0, 800, 0, 0, 0, "MS P�S�V�b�N", &TextID[1]);//������
	_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

	ech = E3DCreateFont( 15, 0, 800, 0, 0, 0, "MS P�S�V�b�N", &TextID[2]);//�ŏ�����
	_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��



	return;
}
/*�f�R���g���N�^�A���[�h�����X�v���C�g�Ȃǂ��폜���܂�*/
Item_Manipulate::~Item_Manipulate(){

	int ech = 0;//�G���[�`�F�b�N�ϐ�

	/*�X�v���C�g���폜���܂�*/
	for(int i = 0; i < 9; i++){
			ech = E3DDestroySprite( MenuSpriteIDs[i]);//���j���[��ʂł̔w�i���폜���܂��B
			_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

	}

	
	/*����ID���폜���܂�*/
	for(int i = 0; i < 3; i++){
			ech = E3DDestroyFont( TextID[i]);//�啶��
			_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

	}



}
/*�o�b�N�p�b�N�̃��C���������s���܂�*/
int Item_Manipulate::MainBackPack( PlayerChara *PC){


	/*�ϐ��̐錾*/
	int ChoseItem = 0;//�I�񂾕���
	int ItemNumber = -1;//�ǂ̃A�C�e����I�񂾂��A������܂�

	do{

			System::MsgQ(30);//���b�Z�[�W���[�v

			/* �ϐ��̐錾 */
			int ech = 0;//�G���[�`�F�b�N�ϐ�
			int ExitFlag = 0;//���̃t���O���I���ɂȂ����Ƃ��E�o���܂��B
			int Counter = 0;//�J�E���^�[�ϐ�
			int ActingItemNumber = 0;
			int keyin[20];//�L�[���z����쐬

			const D3DXVECTOR3 SpritePos1( 0.0, -25.0, 0.0);//�w�i�̈ʒu
			const D3DXVECTOR3 SpritePos2( 0.0, -60.0, 0.0);//�\���o�[�̈ʒu
			const D3DXVECTOR3 SpritePos3( 380.0, 45.0, 0.0);//�㕔�̔����o�[
			const E3DCOLOR4UC NormalColor = { 255,255,255,255};//���F�̑I�΂�Ă��Ȃ��F
			const E3DCOLOR4UC SelectColor = { 255,200,220,20};//���F�̑I�΂�Ă���F
			const E3DCOLOR4UC SetColor = { 255,0,120,170};//�F�̕��킪�I�΂�Ă���F
			
			/* �ϐ��̑���*/
			if( MenuMode == 0) ItemNumber = -1;// ���[�h���ʏ�Ȃ�摜�ɍڂ��Ă��Ȃ��̂�"-1"

			/* �����܂� */

			/* ��{���� */
			System::KeyRenewal(1);
			System::GetKeyData(keyin);


			/* �`�揀�����X���� */
			E3DBeginScene( System::scid1, 0, -1);//�`��̊J�n����

			E3DBeginSprite();//�X�v���C�g�`��̊J�n
			
			//��b���i�X�v���C�g�̕��i��`��
			ech = E3DRenderSprite( MenuSpriteIDs[0], 640.0/1024.0, 480.0/512.0, SpritePos1);//�w�i�̈ʒu
			_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��
			
			ech = E3DRenderSprite( MenuSpriteIDs[1], 1, 1, SpritePos2);//�\���o�[�̈ʒu
			_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

			ech = E3DRenderSprite( MenuSpriteIDs[2], 1, 1, SpritePos3);//�㕔�̔����o�[
			_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��


			/*�I��ł���A�C�e���J�e�S���ɂ���ĕ\���̕���*/
			if( MenuMode == 0) ItemNumber = PutItemSprite( ChoseItem, MenuMode, ItemSysSetPos);// ���[�h���ʏ�Ȃ�
			else PutItemSprite( ChoseItem, MenuMode, ItemSysSetPos);// ���[�h���A�C�e���I�𒆂Ȃ�

			if( MenuMode == 1) ItemUsingSystem( ChoseItem);// �A�C�e�����샂�[�h�̏������s�Ȃ��܂�

			E3DEndSprite();//�X�v���C�g�`��̏I��

			/* ////////////////////////// */
			// �ȉ��A�����̕\�����s���܂�
			/* ////////////////////////// */

			// ��{�I�ȃo�b�N�p�b�N���̕�����\�������܂�
			PutBackPackText( &ChoseItem, &ExitFlag);

			// ����̖��O��\�������܂�
			if( ItemNumber != -1) PutItemName( ChoseItem, ItemNumber);

			// �Ō�ɐ�������\�������܂�
			if( ( ItemNumber != -1) && ( MenuMode == 0)) PutItemDescript( ChoseItem, ItemNumber);


			/*�����܂łŉ�ʕ`�揀���I��*/
			E3DEndScene();
			ech = E3DPresent( System::scid1);
			_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

			if( ( keyin[9] == 1) && ( ItemNumber != -1) && (MenuMode == 0) ){// �A�C�e���摜�̏�ŃN���b�N���ꂽ��
					MenuMode = 1;
					//�����̈ʒu����
					if( ( System::MousePos.x + 256 ) < 640 ){//�����A�C�e���o�[���E�[�𒴂��Ȃ����
							ItemSysSetPos.x = System::MousePos.x;
							ItemSysSetPos.y = System::MousePos.y;
					}
					else{//�������
							ItemSysSetPos.x = 384;
							ItemSysSetPos.y = System::MousePos.y;							
					}
					

			}
			else if( ( MenuMode == 1) && (keyin[9] == 1) &&// �A�C�e�����쒆���瑼�̊֌W�Ȃ��Ƃ������������
				(( ( System::MousePos.x < ItemSysSetPos.x) || ( ItemSysSetPos.x + 256 < System::MousePos.x)) ||
				( ( System::MousePos.y < ItemSysSetPos.y + 30 ) || ( ItemSysSetPos.y + 84 < System::MousePos.y)))

				){
					MenuMode = 0;//  ���샂�[�h����������
			}


			if( ExitFlag == 1 ){//�����Q�[�����[�v�𔲂���OK�Ȃ�
						break;//���[�v�𔲂���
			}

	}while(WM_QUIT != System::msg.message);





	return 0;
}
/*�A�C�e�������ɓ���摜�����Ȃǂ��s���܂�*/
int Item_Manipulate::InItemPack( PlayerChara *PC){



	/*�E��̃|�[�Y���j���̕\�����o�b�N�p�b�N�ɏ��X�ɕς��܂��B*/
	for(int i = 0; i<17; i++){

					/*�ϐ��̏�����*/
					int ech = 0;//�G���[�`�F�b�N�ϐ�
					POINT TextPos;//�e�L�X�g�̍��W�ϐ�
					E3DCOLOR4UC AlfaColor1 = { 255-(15*i) ,255,255,255};
					E3DCOLOR4UC AlfaColor2 = { 15*i ,255,255,255};
					D3DXVECTOR3 SpritePos1( 0.0, -25.0, 0.0);//�w�i�̈ʒu
					D3DXVECTOR3 SpritePos2( 0.0, -60.0, 0.0);//�\���o�[�̈ʒu
					D3DXVECTOR3 SpritePos3( 380.0, 45.0, 0.0);//�㕔�̔����o�[


					/*�`�揀�����s���܂�*/
					E3DBeginScene( System::scid1, 1, -1);;
					E3DBeginSprite();

					ech = E3DRenderSprite( MenuSpriteIDs[0], 640.0/1024.0, 480.0/512.0, SpritePos1);//�w�i�̈ʒu
					_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��
			
					ech = E3DRenderSprite( MenuSpriteIDs[1], 1, 1, SpritePos2);//�\���o�[�̈ʒu
					_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

					ech = E3DRenderSprite( MenuSpriteIDs[2], 1, 1, SpritePos3);//�㕔�̔����o�[
					_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

					/*�����ŁA�`�抮��*/
					E3DEndSprite();

					/*����"�|�[�Y���j���["�̕`����s���܂�*/
					TextPos.x = 440;/**/TextPos.y = 5;
					E3DDrawTextByFontID( System::scid1, TextID[0], TextPos, "�|�[�Y���j���[", AlfaColor1);

					/*����"�o�b�N�p�b�N"�̕`����s���܂�*/
					TextPos.x = 440;/**/TextPos.y = 5;
					E3DDrawTextByFontID( System::scid1, TextID[0], TextPos, "�o�b�N�p�b�N", AlfaColor2);

					E3DEndScene();
					E3DPresent(System::scid1);

					System::MsgQ(30);//���b�Z�[�W���[�v

			
	}/*�����܂�*/

	

	/*�o�b�N�p�b�N�̃V�X�e���ɕς��܂�*/
	MainBackPack( PC);///////

	/*�E��̃|�[�Y���j���̕\�����o�b�N�p�b�N�ɏ��X�ɕς��܂��B*/
	for(int i = 0; i<17; i++){

					/*�ϐ��̏�����*/
					int ech = 0;//�G���[�`�F�b�N�ϐ�
					POINT TextPos;//�e�L�X�g�̍��W�ϐ�
					E3DCOLOR4UC AlfaColor1 = { 15*i ,255,255,255};
					E3DCOLOR4UC AlfaColor2 = { 255-(15*i) ,255,255,255};
					D3DXVECTOR3 SpritePos1( 0.0, -25.0, 0.0);//�w�i�̈ʒu
					D3DXVECTOR3 SpritePos2( 0.0, -60.0, 0.0);//�\���o�[�̈ʒu
					D3DXVECTOR3 SpritePos3( 380.0, 45.0, 0.0);//�㕔�̔����o�[


					/*�`�揀�����s���܂�*/
					E3DBeginScene( System::scid1, 1, -1);;
					E3DBeginSprite();

					ech = E3DRenderSprite( MenuSpriteIDs[0], 640.0/1024.0, 480.0/512.0, SpritePos1);//�w�i�̈ʒu
					_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��
			
					ech = E3DRenderSprite( MenuSpriteIDs[1], 1, 1, SpritePos2);//�\���o�[�̈ʒu
					_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

					ech = E3DRenderSprite( MenuSpriteIDs[2], 1, 1, SpritePos3);//�㕔�̔����o�[
					_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

					/*�����ŁA�`�抮��*/
					E3DEndSprite();

					/*����"�|�[�Y���j���["�̕`����s���܂�*/
					TextPos.x = 440;/**/TextPos.y = 5;
					E3DDrawTextByFontID( System::scid1, TextID[0], TextPos, "�|�[�Y���j���[", AlfaColor1);

					/*����"�o�b�N�p�b�N"�̕`����s���܂�*/
					TextPos.x = 440;/**/TextPos.y = 5;
					E3DDrawTextByFontID( System::scid1, TextID[0], TextPos, "�o�b�N�p�b�N", AlfaColor2);

					E3DEndScene();
					E3DPresent(System::scid1);

					System::MsgQ(30);//���b�Z�[�W���[�v
		
	}/*�����܂�*/





	return 0;
}

