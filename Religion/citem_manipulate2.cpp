/*�����́A�A�C�e������Ɋւ��邱�Ƃ̃N���X�ł��B
//��Ƀo�b�N�p�b�N��A�C�e�������ɂ��ď�����Ă��܂��B
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "citem_manipulate.h"//�A�C�e������Ɋւ���w�b�_�t�@�C��





/*�ȈՐ�������\�������鏈�����s���܂�*/
int Item_Manipulate::PutItemDescript( const int ChoseItem, const int ItemNumber){

	/*�ϐ��̏�����*/
	int ech = 0;//�G���[�`�F�b�N�ϐ�
	char WeaponDetail[64] = "";//���핪�ނ̕�����z��

	/* ��������f�[�^ */
	const char ItemDetailData[8][9][70] ={

		/* �n���h�K�� */
		{ "�č����̈����₷��45���a���e", "M1911���������A���^���������f��", "�|���}�[�t���[���̃t���I�[�g���e",
		"�����₷���ČR�̐����̗p���e", "�������x�̍����`�F�R���̌��e", ".357�}�O�i���e���g�������H���o�[", 
		"�X�C�X���̌��e�B���[�U�[�T�C�g�𑕔�����", "���h�C�c�R��9mm���e�B8�C���`�o����������", "�T�v���b�T�[�t����45���a���e"},
		/* �T�u�}�V���K�� */
		{ "�����Ōy�ʁA�����₷���Z�@�֏e", "�ō��̘A�˗͂��ւ�A���������ꂽ�Z�@�֏e", "�C�^���A���́A�������x�̍����Z�@�֏e",
		"���w�T�C�g�t���̑΃e���p�h�C�c���Z�@�֏e", "�ˌ��e��Z�k���������w�T�C�g�t���Z�@�֏e", "����Z�@�֏e�AMP5�V���[�Y�̍ŒZ���f��",
		"�l�ԍH�w����g�����΃e���p�Z�@�֏e"},
		/* �V���b�g�K�� */
		{ "��ꎟ��킩��g����A�͍��햳�G�̎U�e�e", "�Čx�@��SWAT���̗p����C�^���A���������U�e�e", "�X���b�O�e�������o���t�����L�А��퓬�p�U�e�e",
		"���{���̃X�|�[�c�p��A���U�e�e�B�W�e��������", "�t���I�[�g�ˌ����\�Ȋ؍����̎U�e�e"},
		/* �A�T���g���C�t�� */
		{ "���w�T�C�g�𓋍ڂ����A�����J���\���鏬�e", "���V�A���̌��쏬�eAK�V���[�Y�̗A�o�������f��", "��䰂�r�o���Ȃ��A�h�C�c���̎����㎩�����e",
		"�������x�̍������C�t���e���g���č����̎������e", "���[�U�[�T�C�g�𑕔������������Ȏ������e",
		"�u���p�b�v���������e�BLAM�A�_�b�g�T�C�g�𑕔�", "M4�����C���A�������x��傫���グ���������e"},
		/* �}�V���K�� */
		{ "�����̍��Ő����̗p����Ă���AFN�Ђ̌y�@�֏e", "M4���e���J�X�^�������A���w�T�C�g�t���y�@�֏e",
		"AK�x�[�X�̌y�@�֏e�B�����Ȃ�����肵�����\", "WW�T����WW�U�܂Ŏg��ꂽ�A�ÎQ�y�@�֏e"},
		/* ���C�t�� */
		{ "�č���Ԑl�C�́A��������_���e", "M16���x�[�X�ɂ����������_���e", "���������z�肵���A�e�������������e", 
		"���ɍ����������x�����������_���e", "��[�ɓ����y������t���������{�E�K��", "��^�̑Ε��_���e�B�����������܂���"},
		/* �O���l�[�h */
		{ "�x�g�i���푈�ŏd�󂳂ꂽ�֒e���˓�", "�������֒e���˓��B6���̞֒e��f�������˂ł���",
		"�����\���^�y��e���g���ΐ�ԃ��P�b�g���ˋ@", "�g���̂Ă̑ΐ�Ԟ֒e�B���h�C�c�R�̃R�s�[�i"}
	};

	POINT TextPos1;//���������̈ʒu���i�[����\����
	E3DCOLOR4UC NormalColor = { 255,50,50,50};//�����̔��F

	//�����̈ʒu����
	if( ( System::MousePos.x + 256 ) < 640 ){//�����A�C�e���o�[���E�[�𒴂��Ȃ����
			TextPos1.x = System::MousePos.x + 5;/**/TextPos1.y = System::MousePos.y + 45;//���������̈ʒu�̓}�E�X�|�C���^����Z�o
	}
	else{//�������
			TextPos1.x = 5 + 384;/**/TextPos1.y = System::MousePos.y + 45;//���������̈ʒu�̓}�E�X�|�C���^����Z�o
	}

	/* //////////////////////// */
	// �A�C�e���̎�ނɂ���ĕ���
	/* /////////////////////// */

	if(ChoseItem == 0){//���쒆�̃A�C�e�����u����v�Ȃ�
			if( BackPack_Weapon[ItemNumber][1] == -1){//����Ȃ��Ȃ�
					wsprintf( WeaponDetail, "���킪����܂���");//��������������܂�
			}
			else{
					wsprintf( WeaponDetail, ItemDetailData[ (BackPack_Weapon[ItemNumber][1] - 1) ][ (BackPack_Weapon[ItemNumber][2]) ]);//��������������܂�
			}

			ech = E3DDrawTextByFontID( System::scid1, TextID[2], TextPos1, WeaponDetail, NormalColor);
			
					_ASSERT( ech != 1 );//�G���[�`�F�b�N
	}

	if(ChoseItem == 1){//���쒆�̃A�C�e�����u�e��v�Ȃ�

			if( BackPack_Ammo[ItemNumber][1] == 0){//.45ACP
						wsprintf( WeaponDetail, "�č�����^�������e�p�̎���");//��������������܂�
			}
			if( BackPack_Ammo[ItemNumber][1] == -1){//�e��Ȃ��Ȃ�
							wsprintf( WeaponDetail, "�e�򂪂���܂���");//��������������܂�

			}

			ech = E3DDrawTextByFontID( System::scid1, TextID[2], TextPos1, WeaponDetail, NormalColor);
			
					_ASSERT( ech != 1 );//�G���[�`�F�b�N

	}

	return 0;
}
/*����A�C�e������\�������鏈�����s���܂�*/
int Item_Manipulate::PutItemName( const int ChoseItem, const int ItemNumber){

	/*�ϐ��̏�����*/
	int ech = 0;//�G���[�`�F�b�N�ϐ�
	char WeaponName[32] = "";//���햼�O�̕�����z��
	char WeaponKind[32] = "";//���핪�ނ̕�����z��

	/* ���햼�O�z��f�[�^ */
	const char WeaponNameData[8][9][15] = {
		{ "M1911", "Offisers", "Glock95", "M92F", "Cz-75", "PYTHON", "sauerP226", "LugerP08", "USP.45"},// �n���h�K��
		{ "TMP", "INGLAM", "SPECTER", "UMP", "PATIRIOT", "MP5 kruz", "P90"},// �T�u�}�V���K��
		{ "M1897", "Benel M3", "SPAS-12", "Gold Stalker", "USAS12", "M700", "M82"},// �V���b�g�K��
		{ "M4", "AK-74", "G11", "M14", "G36", "Tabor", "HK 416"},// �A�T���g���C�t��
		{ "BAR A2", "MINIMI", "M4machine", "RPK"},// �}�V���K��
		{ "M700", "SR-25", "SVD", "PSG-1", "X BOW", "M82"},// ���C�t��
		{ "MGL", "M79", "RPG-7", "Panzher", "M201A1"},// �O���l�[�h
		{ "shild sauer", "shild TMP"}// ���̑�
	};

	POINT TextPos3;//����̎�ނ̖��O�����̈ʒu���i�[����\����
	E3DCOLOR4UC NormalColor = { 255,50,50,50};//�����̔��F

	//�����̈ʒu����
	if( MenuMode == 0){// ���j���[���[�h���ʏ�Ȃ�
			if( ( System::MousePos.x + 256 ) < 640 ){//�����A�C�e���o�[���E�[�𒴂��Ȃ����
					TextPos3.x = System::MousePos.x + 5;/**/TextPos3.y = System::MousePos.y + 5;//����̎�ނ̖��O�����̈ʒu�̓}�E�X�|�C���^����Z�o
			}
			else{//�������
					TextPos3.x = 5 + 384;/**/TextPos3.y = System::MousePos.y + 5;//����̎�ނ̖��O�����̈ʒu�̓}�E�X�|�C���^����Z�o
			}
	}
	else if( MenuMode == 1){// ���j���[���[�h���I�𒆂Ȃ�
			TextPos3.x = ItemSysSetPos.x + 5;/**/TextPos3.y = ItemSysSetPos.y + 5;//����̎�ނ̖��O�����̈ʒu�̓}�E�X�|�C���^����Z�o
	}



	/**/
	//�A�C�e���̎�ނɂ���ĕ���
	/**/

	if(ChoseItem == 0){//���쒆�̃A�C�e�����u����v�Ȃ�

			if( BackPack_Weapon[ItemNumber][1] == -1){
					wsprintf( WeaponName, "EMPTY");//���햼�O�������܂�
			}
			else{// ���햼�O�������܂�
					wsprintf( WeaponName, WeaponNameData[(BackPack_Weapon[ItemNumber][1] - 1)][(BackPack_Weapon[ItemNumber][2])]);
			}

		/**//////////
		/**////////
			if(ItemNumber == 0){//�}�E�X�����C���E�F�|���̏�ɂ����
					wsprintf( WeaponKind, "MainWeapon  %s", WeaponName);//���햼�O�������܂�
			}
			if(ItemNumber == 1){//�}�E�X���T�u�E�F�|���̏�ɂ����
					wsprintf( WeaponKind, "SubWeapon  %s", WeaponName);//���햼�O�������܂�
			}
			if(ItemNumber == 2){//�}�E�X���O���l�[�h�n�̏�ɂ����
					wsprintf( WeaponKind, "Grenade  %s", WeaponName);//���햼�O�������܂�
			}
			if(ItemNumber == 3){//�}�E�X���C�����K�v�ȕ���̏�ɂ����
					wsprintf( WeaponKind, "Need Repiar  %s", WeaponName);//���햼�O�������܂�
			}


			//���핪�ނ�\�������܂�
			ech = E3DDrawTextByFontID( System::scid1, TextID[1], TextPos3, WeaponKind, NormalColor);
			
					_ASSERT( ech != 1 );//�G���[�`�F�b�N


	}
	if(ChoseItem == 1){//���쒆�̃A�C�e�����u�e��v�Ȃ�

			if( BackPack_Ammo[ItemNumber][1] == 0){//.45ACP
				wsprintf( WeaponKind, ".45ACP");//���햼�O�������܂�
			}
			else if( BackPack_Ammo[ItemNumber][1] == -1){
							wsprintf( WeaponKind, "EMPTY");//���햼�O�������܂�

			}

			ech = E3DDrawTextByFontID( System::scid1, TextID[1], TextPos3, WeaponKind, NormalColor);
			
						_ASSERT( ech != 1 );//�G���[�`�F�b�N
	}




	return 0;
}
/*�A�C�e����ނ̃��j���[�̕\���E�I�����s���܂�*/
int Item_Manipulate::PutBackPackText( int *ChoseItem, int *ExitFlag){


		/* �ϐ��̐錾 */
		int ech = 0;//�G���[�`�F�b�N�ϐ�
		 ;//�L�[���z����쐬
		const char ItemKindName[5][12] = { "WEAPON" , "AMMO" , "RECOVERY" , "KEY" , "EQUIPMENT" };
		const char ItemKindDetal[5][50] = { "����̑�������܂�" , "�e��̑�������܂�" , "�񕜌n�i�̑�������܂�" 
											, "�d�v�i�̑�������܂�" , "�����i�̑�������܂�" };
		const E3DCOLOR4UC NormalColor = { 255,255,255,255};//���F�̑I�΂�Ă��Ȃ��F
		const E3DCOLOR4UC SetColor = { 255,0,120,170};//�F�̕��킪�I�΂�Ă���F
		const E3DCOLOR4UC SelectColor = { 255,200,220,20};//���F�̑I�΂�Ă���F
		POINT TextPos;//�����̈ʒu���i�[����\����

		//��ԏ�̃|�[�Y���j���[
		TextPos.x = 440;/**/TextPos.y = 5;
		E3DDrawTextByFontID( System::scid1, TextID[0], TextPos, "�o�b�N�p�b�N", NormalColor);


		/* ////////////////////// //
		// �A�C�e����ޕ�����\�� //
		// ////////////////////// */
		TextPos.x = 100;/**/TextPos.y = 100;
		for( int i=0; i<5; i++){
				ech = E3DDrawTextByFontID( System::scid1, TextID[1], TextPos, ItemKindName[i], NormalColor);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
							return 1;//��肠��ŏI��
				};
				TextPos.y = TextPos.y + 40;//40��������
		}


		/* //////////////////////////////////////// //
		// "�o�b�N�A�b�v�����"�̕\�����s�Ȃ��܂� //
		// //////////////////////////////////////// */

		TextPos.y = 320;//60������
		ech = E3DDrawTextByFontID( System::scid1, TextID[1], TextPos, "�o�b�N�p�b�N�����", NormalColor);
		if(ech != 0 ){//�G���[�`�F�b�N
			_ASSERT( 0 );//�G���[�_�C�A���O
			return 1;//��肠��ŏI��
		};



		/* /////////////////////////////////////////  //
		// �}�E�X���I�𕔂ɂ���Ƃ��A������ύX���܂� //
		// /////////////////////////////////////////  */
		if((100< System::MousePos.x)&&(System::MousePos.x<250) && ( MenuMode == 0)) {//�}�E�XX���W�����j���[�Q�̏��ɂ���Ȃ�

			for( int i=0; i<5; i++){
				if((120 + (40 * i) < System::MousePos.y)&&( System::MousePos.y< 150 + (40 * i) )){
					
						/* �}�E�X�|�C���^���u���Ă��镶�������点�� */
						TextPos.x = 100;/**/TextPos.y = 100 + (40 * i);
						E3DDrawTextByFontID( System::scid1, TextID[1], TextPos, ItemKindName[i], SelectColor);//�I������Ă��镶���ɂ���
						
								_ASSERT( ech != 1 );//�G���[�`�F�b�N

						/* �����Ƀ|�C���^��u���Ă���Ƃ���̐������L�q���� */
						TextPos.x = 400;/**/TextPos.y = 330;
						E3DDrawTextByFontID( System::scid1, TextID[1], TextPos, ItemKindDetal[i], NormalColor);//������������Ă��镶�����\������
						
								_ASSERT( ech != 1 );//�G���[�`�F�b�N

						/* �N���b�N������I���A�C�e����ς��� */
						if( (System::GetKeyData( System::KEY_LEFTMOUSE)) && ( MenuMode == 0)){
									*ChoseItem = i;//���[�v�E�o�t���O���I���ɂ���B
						}
				}
			}

			if((340< System::MousePos.y)&&( System::MousePos.y<370)){//�}�E�X���W���u�o�b�N�p�b�N�����v�̏�Ȃ�
					TextPos.x = 100;/**/TextPos.y = 320;
					E3DDrawTextByFontID( System::scid1, TextID[1], TextPos, "�o�b�N�p�b�N�����", SelectColor);//�I������Ă��镶���ɂ���
					
					_ASSERT( ech != 1 );//�G���[�`�F�b�N

					TextPos.x = 400;/**/TextPos.y = 330;
					E3DDrawTextByFontID( System::scid1, TextID[1], TextPos, "�|�[�Y���j���[�ɖ߂�܂�", NormalColor);//������������Ă��镶�����\������
					
					_ASSERT( ech != 1 );//�G���[�`�F�b�N

					if(System::GetKeyData( System::KEY_LEFTMOUSE)){//�N���b�N������
						*ExitFlag = 1;//���[�v�E�o�t���O���I���ɂ���B
					}
			}	
		}




		/* //////////////////////////////////////////////////// //
		// �F�łǂ̃A�C�e���̎�ނ��I������Ă����ύX���܂� //
		// //////////////////////////////////////////////////// */
		TextPos.x = 100;/**/TextPos.y = 100;
		for( int i=0; i<5; i++){
				if( *ChoseItem == i){
						ech = E3DDrawTextByFontID( System::scid1, TextID[1], TextPos, ItemKindName[i], SetColor);
						if(ech != 0 ){//�G���[�`�F�b�N
									_ASSERT( 0 );//�G���[�_�C�A���O
									return 1;//��肠��ŏI��
						};
				}
				TextPos.y = TextPos.y + 40;//40��������
		}



	return 0;
}
/*�A�C�e���摜�̕\���A������s�Ȃ��܂�*/
int Item_Manipulate::PutItemSprite( const int ChoseItem, const int MenuMode, const POINT ItemSysSetPos){

	/* �ϐ��̐錾 */
	int ech = 0;// �G���[�`�F�b�N�ϐ�
	int ItemNumber = -1;//�ǂ̃A�C�e����I�񂾂��A������܂�

	/* ����摜�ʒu�z��ϐ� */
	const float ItemSpritePosition[3][2][6] = {
		{ { 280, 440, 280, 440} , {100 , 100, 190, 190} },// ���탁�j���[
		{ { 280, 440, 280, 440} , {100 , 100, 190, 190}  },// �e�򃁃j���[
		{ { 280, 440, 280, 440 , 360} , {90 , 90, 170, 170 , 250}  } // �񕜌n���j���[
	};
	D3DXVECTOR3 ItemSpritePos( 0.0, 0.0, 0.0);// �A�C�e���摜�̈ʒu
	D3DXVECTOR3 DatilSpritePos( 0.0, 0.0, 0.0);//�����o�[�̈ʒu



	/* ///////////////////////////////////// */
	// ���ׂẲ摜�X�v���C�g�̕`����s�Ȃ��܂�
	/* ///////////////////////////////////// */
	switch( ChoseItem ){
		case 0:{//����̃��j���[
				for(int i=0; i<4; i++){
						ItemSpritePos.x = ItemSpritePosition[0][0][i];/**/ItemSpritePos.y = ItemSpritePosition[0][1][i];
						ech = E3DRenderSprite( BackPack_Weapon[i][0], 1, 1, ItemSpritePos);//�㕔�̔����o�[
						_ASSERT( ech != 1 );//�G���[�`�F�b�N
				}					
				break;
		}
		case 1:{//�e��̃��j���[
				for(int i=0; i<4; i++){
						ItemSpritePos.x = ItemSpritePosition[1][0][i];/**/ItemSpritePos.y = ItemSpritePosition[1][1][i];
						ech = E3DRenderSprite( BackPack_Ammo[i][0], 1, 1, ItemSpritePos);//�㕔�̔����o�[
						_ASSERT( ech != 1 );//�G���[�`�F�b�N
				}
				break;
		}
		case 2:{//�񕜌n�̃��j���[
				for(int i=0; i<5; i++){
						ItemSpritePos.x = ItemSpritePosition[2][0][i];/**/ItemSpritePos.y = ItemSpritePosition[2][1][i];
						ech = E3DRenderSprite( BackPack_Recovery[i][0], 1, 1, ItemSpritePos);//�㕔�̔����o�[
						_ASSERT( ech != 1 );//�G���[�`�F�b�N
				}
				break;
			}
	}

	/* �����܂� */


	/* ///////////////////////////////////////// */
	//  �A�C�e���摜�̏�Ƀ}�E�X�|�C���^������Ȃ�B
	//	���́A�摜ID���擾����
	// ///////////////////////////////////////// */
	if( MenuMode == 0){// ���[�h���u�A�C�e����I�����ĂȂ��v�Ȃ�
			switch( ChoseItem ){
					case 0:{//����̃��j���[
						for(int i=0; i<4; i++){
							if(( ItemSpritePosition[0][0][i] < System::MousePos.x ) && ( System::MousePos.x < ItemSpritePosition[0][0][i] + 128.0f )
									&& ( ItemSpritePosition[0][1][i]  + 16.0f < System::MousePos.y ) && ( System::MousePos.y < ItemSpritePosition[0][1][i] + 90.0f)){
										ItemNumber = i;//�J�[�\���Əd�Ȃ��Ă����摜��ID����
							}
						}
						break;
					}
					case 1:{//�e��̃��j���[
						for(int i=0; i<4; i++){
							if(( ItemSpritePosition[1][0][i] < System::MousePos.x ) && ( System::MousePos.x < ItemSpritePosition[1][0][i] + 128.0f )
									&& ( ItemSpritePosition[1][1][i] + 16.0f < System::MousePos.y ) && ( System::MousePos.y < ItemSpritePosition[1][1][i] + 90.0f)){
										ItemNumber = i;//�J�[�\���Əd�Ȃ��Ă����摜��ID����
							}
						}
						break;
					}
					case 2:{//�񕜌n�̃��j���[
						for(int i=0; i<5; i++){
							if(( ItemSpritePosition[2][0][i] < System::MousePos.x ) && ( System::MousePos.x < ItemSpritePosition[2][0][i] + 128.0f )
									&& ( ItemSpritePosition[2][1][i] + 16.0f < System::MousePos.y ) && ( System::MousePos.y < ItemSpritePosition[2][1][i] + 90.0f)){
										ItemNumber = i;//�J�[�\���Əd�Ȃ��Ă����摜��ID����
							}
						}
						break;
					}
			}

			/* //////////////////////////////////// */
			//  �����o�[��\�������Ȃ��Ƃ����Ȃ��Ȃ��
			/* //////////////////////////////////// */
			if( ItemNumber != -1 ){

					//�o�[���E�ɂ͂ݏo�Ȃ��̂Ȃ�
					if( ( System::MousePos.x + 256 ) < 640 ){
							DatilSpritePos.x = float( System::MousePos.x ); /**/ DatilSpritePos.y = float( System::MousePos.y );
					}
					//�o�[���E�ɂ͂ݏo��̂Ȃ�
					else{
							DatilSpritePos.x = 384.0f; /**/ DatilSpritePos.y = float( System::MousePos.y );
					}
					/* �X�v���C�g�̕`�� */
					ech = E3DRenderSprite( MenuSpriteIDs[4], 1, 1, DatilSpritePos);//�㕔�̔����o�[
					_ASSERT( ech != 1 );//�G���[�`�F�b�N
			};
	}
	else if( MenuMode == 1){// ���[�h���u�A�C�e����I�����Ă���v�Ȃ�

			/* ���W�̎w�� */
			DatilSpritePos.x = float( ItemSysSetPos.x ); /**/ DatilSpritePos.y = float( ItemSysSetPos.y );
			
			/* �X�v���C�g�̕`�� */
			ech = E3DRenderSprite( MenuSpriteIDs[4], 1, 1, DatilSpritePos);//�㕔�̔����o�[
			_ASSERT( ech != 1 );//�G���[�`�F�b�N
	}


	/* �����܂� */



	return ItemNumber;
}
/*�A�C�e�����g���A�폜�A�m�F�Ȃǂ��s�Ȃ��܂�*/
int Item_Manipulate::ItemUsingSystem( const int ChoseItem){

	/* �ϐ��̐錾 */
	int ech = 0;//�G���[�`�F�b�N�ϐ�
	D3DXVECTOR3 ItemIconPos( 0.0, 0.0, 0.0);//�A�C�e������A�C�R���̈ʒu
	
	/* �A�C�e���A�C�R����������ǂ̉摜��`�悷�邩���߂�ϐ� */
	const int ItemIconIDToRight[5][4] = {
		{ 8, 6, 7},
		{ 6, 7},
		{ 5, 6, 7},
		{ 7},
		{ 8, 6, 7}
	};

	/* �A�C�e���A�C�R�������\��������̂���`����ϐ� */
	const int ItemIconNumber[5] = { 3, 2, 3, 1, 3};

	// ���W����
	ItemIconPos.x = ItemSysSetPos.x + 10.0f;
	ItemIconPos.y = ItemSysSetPos.y + 30.0f;

	//�A�C�e������A�C�R���̕`��
	for( int i=0; i < ItemIconNumber[(ChoseItem)]; i++ ){

			ech = E3DRenderSprite( MenuSpriteIDs[(ItemIconIDToRight[(ChoseItem)][i])], 1, 1, ItemIconPos);//�w�i�̈ʒu
			_ASSERT( ech != 1 );//�G���[�`�F�b�N
			
			ItemIconPos.x = ItemIconPos.x + 40;
	 }




	return 0;
}