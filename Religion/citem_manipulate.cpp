/*�����́A�A�C�e������Ɋւ��邱�Ƃ̃N���X�ł��B
//��Ƀo�b�N�p�b�N��A�C�e�������ɂ��ď�����Ă��܂��B
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


/*�R���X�g���N�^�A�A�C�e���̃X�v���C�g�Ȃǂ����[�h���܂�*/
Item_Manipulate::Item_Manipulate( PlayerChara *PC, Weapon *Wep){

	/*�ϐ��̐錾*/
	int ech = 0;//�G���[�`�F�b�N�ϐ�
	char loadname[256] = "";//���[�h����t�@�C�����̕�����z��
	E3DCOLOR4UC AlfaColor = { 200,255,255,255};//�A�C�e���̏ڍׂ������摜�̔�����

  /*�摜�̃��[�h���s���܂�*/

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

	wsprintf( loadname, "%s\\data\\img\\menu\\loading.png", sys->path);//���[�h�摜�̃��[�h���܂��B
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[3]);
	if(ech != 0){//�G���[�`�F�b�N
				_ASSERT(0);//�G���[�_�C�A���O��\��
	};

	wsprintf( loadname, "%s\\data\\img\\item\\itstate.png", sys->path);//���[�h�摜�̃��[�h���܂��B
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[4]);
	if(ech != 0){//�G���[�`�F�b�N
				_ASSERT(0);//�G���[�_�C�A���O��\��
	};

	wsprintf( loadname, "%s\\data\\img\\item\\itstate2.png", sys->path);//�������̃��[�h�摜�̃��[�h���܂��B
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[5]);
	if(ech != 0){//�G���[�`�F�b�N
				_ASSERT(0);//�G���[�_�C�A���O��\��
	};

	wsprintf( loadname, "%s\\data\\img\\item\\cure.png", sys->path);//�񕜃A�C�R���̃��[�h�摜�̃��[�h���܂��B
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[6]);
	if(ech != 0){//�G���[�`�F�b�N
				_ASSERT(0);//�G���[�_�C�A���O��\��
	};

	wsprintf( loadname, "%s\\data\\img\\item\\dump.png", sys->path);//�S�~���A�C�R���̃��[�h�摜�̃��[�h���܂��B
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[7]);
	if(ech != 0){//�G���[�`�F�b�N
				_ASSERT(0);//�G���[�_�C�A���O��\��
	};

	wsprintf( loadname, "%s\\data\\img\\item\\info.png", sys->path);//���A�C�R���̃��[�h�摜�̃��[�h���܂��B
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[8]);
	if(ech != 0){//�G���[�`�F�b�N
				_ASSERT(0);//�G���[�_�C�A���O��\��
	};

	wsprintf( loadname, "%s\\data\\img\\item\\supply.png", sys->path);//�����}�[�N�̃��[�h�摜�̃��[�h���܂��B
	ech = E3DCreateSprite( loadname, 0, 0, &MenuSpriteIDs[9]);
	if(ech != 0){//�G���[�`�F�b�N
				_ASSERT(0);//�G���[�_�C�A���O��\��
	};


	ech = E3DSetSpriteARGB( MenuSpriteIDs[4], AlfaColor);
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};

	/*���[�h�摜�̕\��*/
		D3DXVECTOR3 SpritePos4( 250.0, 170.0, 0.0);//���[�h�摜�̈ʒu
		/*�`�揀�����s���܂�*/
		E3DBeginScene( sys->scid1, 1, -1);;
		E3DBeginSprite();

		ech = E3DRenderSprite( MenuSpriteIDs[3], 1, 1, SpritePos4);//���[�h�̉摜
		if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
		};

		/*�����ŁA�`�抮��*/
		E3DEndSprite();

		E3DEndScene();
		E3DPresent(sys->scid1);

	/*���ɕ���̉摜��ǂݍ��݂܂�*/
	for( int i = 0; i<3; i++){
			if( Wep->GetSpriteData(i) != 0){//�������Ă����
					BackPack_Weapon[i][0] = Wep->GetSpriteData(i) ;//�摜�f�[�^�����[�h����
					BackPack_Weapon[i][1] = Wep->GetWeaponData( i, 0);//����̎�ނ�������
					BackPack_Weapon[i][2] = Wep->GetWeaponData( i, 1);//����̃i���o�[��������
			}
			else{//�������Ă��Ȃ���� -> ��f�[�^���[�h���܂�
					wsprintf( loadname, "%s\\data\\img\\item\\empty.png", sys->path);//��A�C�e���摜�����[�h���܂��B
					ech = E3DCreateSprite( loadname, 0, 0, &BackPack_Weapon[i][0]);
					if(ech != 0){//�G���[�`�F�b�N
							_ASSERT(0);//�G���[�_�C�A���O��\��
					}
					BackPack_Weapon[i][1] = -1;//����̎�ނ���ɂ���
					BackPack_Weapon[i][2] = -1;//����̃i���o�[����ɂ���
			}
	}

	
	if( PC->BringWp == 0){//�X�e�[�W�ŏE��������̏���
			wsprintf( loadname, "%s\\data\\img\\item\\empty.png", sys->path);
			ech = E3DCreateSprite( loadname, 0, 0, &BackPack_Weapon[3][0]);
			if(ech != 0){//�G���[�`�F�b�N
					_ASSERT(0);//�G���[�_�C�A���O��\��
			}
			//BackPack_Weapon[3] = GetLoadSprite();
	}

	/*���ɒe��̉摜��ǂݍ��݂܂�*/
	for( int i=0; i<4; i++){
			if( PC->Ammo[i] != 0){//�������Ă����
					//BackPack_Ammo[i][0] = PC->wp_data[i][0][1];//��摜�f�[�^�����[�h����
					wsprintf( loadname, "%s\\data\\img\\item\\empty.png", sys->path);//1���I�ɋ�A�C�e���摜�����[�h���܂��B
					ech = E3DCreateSprite( loadname, 0, 0, &BackPack_Ammo[i][0]);
					if(ech != 0){//�G���[�`�F�b�N
							_ASSERT(0);//�G���[�_�C�A���O��\��
					}
					BackPack_Ammo[i][1] = PC->Ammo[i];//����̎�ނ�������
			}
			else{//�������Ă��Ȃ���� -> ��f�[�^���[�h���܂�
					wsprintf( loadname, "%s\\data\\img\\item\\empty.png", sys->path);//��A�C�e���摜�����[�h���܂��B
					ech = E3DCreateSprite( loadname, 0, 0, &BackPack_Ammo[i][0]);
					if(ech != 0){//�G���[�`�F�b�N
							_ASSERT(0);//�G���[�_�C�A���O��\��
					}
					BackPack_Ammo[i][1] = -1;//����̃i���o�[����ɂ���
			}
	}


	/**/
	//
	/**/

	/*�A�C�e�����j���[�Ŏg������ID��ݒ肵�܂��B*/
	ech = E3DCreateFont( 35, 0, 800, 0, 0, 0, "MS P�S�V�b�N", &TextID[0]);//�啶��
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
	};

	ech = E3DCreateFont( 25, 0, 800, 0, 0, 0, "MS P�S�V�b�N", &TextID[1]);//������
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
	};

	ech = E3DCreateFont( 15, 0, 800, 0, 0, 0, "MS P�S�V�b�N", &TextID[2]);//�ŏ�����
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
	};

}
/*�f�R���g���N�^�A���[�h�����X�v���C�g�Ȃǂ��폜���܂�*/
Item_Manipulate::~Item_Manipulate(){

	int ech = 0;//�G���[�`�F�b�N�ϐ�

	/*�X�v���C�g���폜���܂�*/
	for(int i = 0; i < 6; i++){
			ech = E3DDestroySprite( MenuSpriteIDs[i]);//���j���[��ʂł̔w�i���폜���܂��B
			if(ech != 0){//�G���[�`�F�b�N
						_ASSERT(0);//�G���[�_�C�A���O��\��
			};
	}

	
	/*����ID���폜���܂�*/
	for(int i = 0; i < 3; i++){
			ech = E3DDestroyFont( TextID[i]);//�啶��
			if(ech != 0){//�G���[�`�F�b�N
						_ASSERT(0);//�G���[�_�C�A���O��\��
			};
	}



}
/*�o�b�N�p�b�N�̃��C���������s���܂�*/
int Item_Manipulate::MainBackPack( PlayerChara *PC){


	/*�ϐ��̏�����*/
	int ChoseItem = 0;//�I�񂾕���

	do{

			sys->MsgQ(30);//���b�Z�[�W���[�v

			/*�ϐ��̏�����*/
			int ech = 0;//�G���[�`�F�b�N�ϐ�
			int ExitFlag = 0;//���̃t���O���I���ɂȂ����Ƃ��E�o���܂��B
			int Counter = 0;//�J�E���^�[�ϐ�
			int ItemNumber = -1;//�ǂ̃A�C�e����I�񂾂��A������܂�
			int keyin[20];//�L�[���z����쐬
			D3DXVECTOR3 SpritePos1( 0.0, -25.0, 0.0);//�w�i�̈ʒu
			D3DXVECTOR3 SpritePos2( 0.0, -60.0, 0.0);//�\���o�[�̈ʒu
			D3DXVECTOR3 SpritePos3( 380.0, 45.0, 0.0);//�㕔�̔����o�[
			D3DXVECTOR3 SpritePos4( 0.0, 0.0, 0.0);//�A�C�e���摜�̈ʒu
			D3DXVECTOR3 SpritePos5( 0.0, 0.0, 0.0);//�����o�[�̈ʒu
			E3DCOLOR4UC NormalColor = { 255,255,255,255};//���F�̑I�΂�Ă��Ȃ��F
			E3DCOLOR4UC SelectColor = { 255,200,220,20};//���F�̑I�΂�Ă���F
			E3DCOLOR4UC SetColor = { 255,0,120,170};//�F�̕��킪�I�΂�Ă���F
			POINT TextPos;//�����̈ʒu���i�[����\����

			sys->KeyRenewal(1);
			sys->GetKeyData(keyin);

			/*�`�揀�����X����*/
			E3DBeginScene( sys->scid1, 0, -1);//�`��̊J�n����

			E3DBeginSprite();//�X�v���C�g�`��̊J�n
			
			//��b���i�X�v���C�g�̕��i��`��
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

			/*�I��ł���A�C�e���J�e�S���ɂ���ĕ\���̕���*/

			//����̃��j���[
			if( ChoseItem == 0){
				for(int i=0; i<2; i++){
						for(int j=0; j<2; j++){
								SpritePos4.x = 280+(j*160.0f);/**/SpritePos4.y = 100+(i*90.0f);
								ech = E3DRenderSprite( BackPack_Weapon[Counter][0], 1, 1, SpritePos4);//�㕔�̔����o�[
								if(ech != 0 ){//�G���[�`�F�b�N
											_ASSERT( 0 );//�G���[�_�C�A���O
								};
								Counter++;

								/*�����}�E�X�̉����摜�Ȃ�*/
								if(( 280 + ( j*160.0f ) < sys->MousePos.x ) && ( sys->MousePos.x < 408 + ( j*160.0f ))
										&& ( 120 + ( i*90.0f ) < sys->MousePos.y ) && ( sys->MousePos.y < 190 + ( i*90.0f ))){
											ItemNumber = Counter - 1;//�J�[�\���Əd�Ȃ��Ă����摜��ID����
								}
						}
				};

				if( ItemNumber != -1 ){//�����A�����o�[��\�������Ȃ��Ƃ����Ȃ��Ȃ��
						if( ( sys->MousePos.x + 256 ) < 640 ){//�o�[���E�ɂ͂ݏo�Ȃ��̂Ȃ�
								SpritePos5.x = float( sys->MousePos.x ); /**/ SpritePos5.y = float( sys->MousePos.y );
								ech = E3DRenderSprite( MenuSpriteIDs[4], 1, 1, SpritePos5);//�㕔�̔����o�[
								if(ech != 0 ){//�G���[�`�F�b�N
											_ASSERT( 0 );//�G���[�_�C�A���O
								};
						}
						else{//�o�[���E�ɂ͂ݏo��̂Ȃ�
								SpritePos5.x = float( sys->MousePos.x - 256); /**/ SpritePos5.y = float( sys->MousePos.y );
								ech = E3DRenderSprite( MenuSpriteIDs[5], 1, 1, SpritePos5);//�㕔�̔����o�[
								if(ech != 0 ){//�G���[�`�F�b�N
											_ASSERT( 0 );//�G���[�_�C�A���O
								};
						}
				};
			}

			//�e��̃��j���[
			if( ChoseItem == 1){
				for(int i=0; i<2; i++){
						for(int j=0; j<2; j++){
								SpritePos4.x = 280+(j*160.0f);/**/SpritePos4.y = 100+(i*90.0f);
								ech = E3DRenderSprite( BackPack_Ammo[Counter][0], 1, 1, SpritePos4);//�㕔�̔����o�[
								if(ech != 0 ){//�G���[�`�F�b�N
											_ASSERT( 0 );//�G���[�_�C�A���O
								};
								Counter++;

								/*�����}�E�X�̉����摜�Ȃ�*/
								if(( 280 + ( j*160.0f ) < sys->MousePos.x ) && ( sys->MousePos.x < 408 + ( j*160.0f ))
										&& ( 120 + ( i*90.0f ) < sys->MousePos.y ) && ( sys->MousePos.y < 190 + ( i*90.0f ))){
											ItemNumber = Counter - 1;//�J�[�\���Əd�Ȃ��Ă����摜��ID����
								}
						}
				};

				if( ItemNumber != -1 ){//�����A�����o�[��\�������Ȃ��Ƃ����Ȃ��Ȃ��
						if( sys->MousePos.x + 256 < 640){//�o�[���E�ɂ͂ݏo�Ȃ��̂Ȃ�
								SpritePos5.x = float( sys->MousePos.x); /**/ SpritePos5.y = float( sys->MousePos.y);
								ech = E3DRenderSprite( MenuSpriteIDs[4], 1, 1, SpritePos5);//�㕔�̔����o�[
								if(ech != 0 ){//�G���[�`�F�b�N
											_ASSERT( 0 );//�G���[�_�C�A���O
								};
						}
						else{//�o�[���E�ɂ͂ݏo��̂Ȃ�
								SpritePos5.x = float( sys->MousePos.x - 256); /**/ SpritePos5.y = float( sys->MousePos.y);
								ech = E3DRenderSprite( MenuSpriteIDs[5], 1, 1, SpritePos5);//�㕔�̔����o�[
								if(ech != 0 ){//�G���[�`�F�b�N
											_ASSERT( 0 );//�G���[�_�C�A���O
								};
						}
				};
			}

			E3DEndSprite();//�X�v���C�g�`��̏I��

			/**/
			//�ȉ��A�����̕\�����s���܂�
			/**/

			//��ԏ�̃|�[�Y���j���[
			TextPos.x = 440;/**/TextPos.y = 5;
			E3DDrawTextByFontID( sys->scid1, TextID[0], TextPos, "�o�b�N�p�b�N", NormalColor);

			//�ȉ��A�ʏ핶����\��
			TextPos.x = 100;
			TextPos.y = 100;//40��������
			ech = E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "WEAPON", NormalColor);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			};

			TextPos.y = 140;//40��������
			ech = E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "AMMO", NormalColor);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			};

			TextPos.y = 180;//40��������
			ech = E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "RECOVERY", NormalColor);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			};

			TextPos.y = 220;//40��������
			ech = E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "KEY", NormalColor);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			};

			TextPos.y = 260;//40��������
			ech = E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "EQUIPMENT", NormalColor);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			};

			TextPos.y = 320;//60������
			ech = E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "�o�b�N�p�b�N�����", NormalColor);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			};

			/*�}�E�X���I�𕔂ɂ���Ƃ��A������ύX���܂�*/
			if((100< sys->MousePos.x)&&(sys->MousePos.x<250)){
					if((120< sys->MousePos.y)&&( sys->MousePos.y<150)){//�}�E�X���W���uWEAPON�v�̏�Ȃ�
							TextPos.x = 100;
							TextPos.y = 100;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "WEAPON", SelectColor);//�I������Ă��镶���ɂ���
							if(ech != 0){//�G���[�`�F�b�N
										_ASSERT(0);//�G���[�_�C�A���O��\��
							};
							TextPos.x = 400;
							TextPos.y = 330;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "����̑�������܂�", NormalColor);//������������Ă��镶�����\������
							if(ech != 0){//�G���[�`�F�b�N
										_ASSERT(0);//�G���[�_�C�A���O��\��
							};
							if(keyin[9] == 1){//�N���b�N������
										ChoseItem = 0;//���[�v�E�o�t���O���I���ɂ���B
							}
					}	
					if((160< sys->MousePos.y)&&( sys->MousePos.y<190)){//�}�E�X���W���uAMMO�v�̏�Ȃ�
							TextPos.x = 100;
							TextPos.y = 140;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "AMMO", SelectColor);//�I������Ă��镶���ɂ���
							if(ech != 0){//�G���[�`�F�b�N
										_ASSERT(0);//�G���[�_�C�A���O��\��
							};
							TextPos.x = 400;
							TextPos.y = 330;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "�e��̑�������܂�", NormalColor);//������������Ă��镶�����\������
							if(ech != 0){//�G���[�`�F�b�N
										_ASSERT(0);//�G���[�_�C�A���O��\��
							};
							if(keyin[9] == 1){//�N���b�N������
										ChoseItem = 1;//���[�v�E�o�t���O���I���ɂ���B
							}
					}
					if((200< sys->MousePos.y)&&( sys->MousePos.y<230)){//�}�E�X���W���uRECOVERY�v�̏�Ȃ�
							TextPos.x = 100;
							TextPos.y = 180;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "RECOVERY", SelectColor);//�I������Ă��镶���ɂ���
							if(ech != 0){//�G���[�`�F�b�N
										_ASSERT(0);//�G���[�_�C�A���O��\��
							};
							TextPos.x = 400;
							TextPos.y = 330;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "�񕜌n�i�̑�������܂�", NormalColor);//������������Ă��镶�����\������
							if(ech != 0){//�G���[�`�F�b�N
										_ASSERT(0);//�G���[�_�C�A���O��\��
							};
							if(keyin[9] == 1){//�N���b�N������
										ChoseItem = 2;//���[�v�E�o�t���O���I���ɂ���B
							}
					}	
					if((240< sys->MousePos.y)&&( sys->MousePos.y<270)){//�}�E�X���W���uKEY�v�̏�Ȃ�
							TextPos.x = 100;
							TextPos.y = 220;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "KEY", SelectColor);//�I������Ă��镶���ɂ���
							if(ech != 0){//�G���[�`�F�b�N
										_ASSERT(0);//�G���[�_�C�A���O��\��
							};
							TextPos.x = 400;
							TextPos.y = 330;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "�d�v�i�̑�������܂�", NormalColor);//������������Ă��镶�����\������
							if(ech != 0){//�G���[�`�F�b�N
										_ASSERT(0);//�G���[�_�C�A���O��\��
							};
							if(keyin[9] == 1){//�N���b�N������
										ChoseItem = 3;//���[�v�E�o�t���O���I���ɂ���B
							}
					}	
					if((280< sys->MousePos.y)&&( sys->MousePos.y<310)){//�}�E�X���W���uEQUIPMENT�v�̏�Ȃ�
							TextPos.x = 100;
							TextPos.y = 260;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "EQUIPMENT", SelectColor);//�I������Ă��镶���ɂ���
							if(ech != 0){//�G���[�`�F�b�N
										_ASSERT(0);//�G���[�_�C�A���O��\��
							};
							TextPos.x = 400;
							TextPos.y = 330;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "�����i�̑�������܂�", NormalColor);//������������Ă��镶�����\������
							if(ech != 0){//�G���[�`�F�b�N
										_ASSERT(0);//�G���[�_�C�A���O��\��
							};
							if(keyin[9] == 1){//�N���b�N������
										ChoseItem = 4;//���[�v�E�o�t���O���I���ɂ���B
							}
					}	
					if((340< sys->MousePos.y)&&( sys->MousePos.y<370)){//�}�E�X���W���u�o�b�N�p�b�N�����v�̏�Ȃ�
							TextPos.x = 100;
							TextPos.y = 320;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "�o�b�N�p�b�N�����", SelectColor);//�I������Ă��镶���ɂ���
							if(ech != 0){//�G���[�`�F�b�N
										_ASSERT(0);//�G���[�_�C�A���O��\��
							};
							TextPos.x = 400;
							TextPos.y = 330;
							E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "�|�[�Y���j���[�ɖ߂�܂�", NormalColor);//������������Ă��镶�����\������
							if(ech != 0){//�G���[�`�F�b�N
										_ASSERT(0);//�G���[�_�C�A���O��\��
							};
							if(keyin[9] == 1){//�N���b�N������
										ExitFlag = 1;//���[�v�E�o�t���O���I���ɂ���B
							}
					}	
			}

			/*�F�łǂ̃A�C�e���̎�ނ��I������Ă����ύX���܂�*/
			//�ȉ��A�ʏ핶����\��
			TextPos.x = 100;
			if( ChoseItem == 0){
					TextPos.y = 100;//40��������
					E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "WEAPON", SetColor);
					if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
							return 1;//��肠��ŏI��
					};
			}
			if( ChoseItem == 1){
					TextPos.y = 140;//40��������
					E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "AMMO", SetColor);
					if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
							return 1;//��肠��ŏI��
					};
			}
			if( ChoseItem == 2){
					TextPos.y = 180;//40��������
					E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "RECOVERY", SetColor);
					if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
							return 1;//��肠��ŏI��
					};
			}
			if( ChoseItem == 3){
					TextPos.y = 220;//40��������
					E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "KEY", SetColor);
					if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
							return 1;//��肠��ŏI��
					};
			}
			if( ChoseItem == 4){
					TextPos.y = 260;//40��������
					E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos, "EQUIPMENT", SetColor);
					if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
							return 1;//��肠��ŏI��
					};
			}


			//�Ō�ɐ�������\�������܂�
			PutItemDescript( ChoseItem, ItemNumber);

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


	sys->KeyRenewal(1);//�����I�����s��Ȃ��悤�ɂ��邽�߂́A�L�[�`�F�b�N


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

					/*����"�|�[�Y���j���["�̕`����s���܂�*/
					TextPos.x = 440;/**/TextPos.y = 5;
					E3DDrawTextByFontID( sys->scid1, TextID[0], TextPos, "�|�[�Y���j���[", AlfaColor1);

					/*����"�o�b�N�p�b�N"�̕`����s���܂�*/
					TextPos.x = 440;/**/TextPos.y = 5;
					E3DDrawTextByFontID( sys->scid1, TextID[0], TextPos, "�o�b�N�p�b�N", AlfaColor2);

					E3DEndScene();
					E3DPresent(sys->scid1);

					sys->MsgQ(30);//���b�Z�[�W���[�v

			
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

					/*����"�|�[�Y���j���["�̕`����s���܂�*/
					TextPos.x = 440;/**/TextPos.y = 5;
					E3DDrawTextByFontID( sys->scid1, TextID[0], TextPos, "�|�[�Y���j���[", AlfaColor1);

					/*����"�o�b�N�p�b�N"�̕`����s���܂�*/
					TextPos.x = 440;/**/TextPos.y = 5;
					E3DDrawTextByFontID( sys->scid1, TextID[0], TextPos, "�o�b�N�p�b�N", AlfaColor2);

					E3DEndScene();
					E3DPresent(sys->scid1);

					sys->MsgQ(30);//���b�Z�[�W���[�v
		
	}/*�����܂�*/





	return 0;
}
/*��������\�������鏈�����s���܂�*/
int Item_Manipulate::PutItemDescript( int ChoseItem, int ItemNumber){

	/*�ϐ��̏�����*/
	int ech = 0;//�G���[�`�F�b�N�ϐ�
	POINT TextPos1;//���������̈ʒu���i�[����\����
	POINT TextPos2;//���햼�����̈ʒu���i�[����\����
	POINT TextPos3;//����̎�ނ̖��O�����̈ʒu���i�[����\����
	E3DCOLOR4UC NormalColor = { 255,50,50,50};//�����̔��F

	//�����̈ʒu����
	if( ( sys->MousePos.x + 256 ) < 640 ){//�����A�C�e���o�[���E�[�𒴂��Ȃ����
			TextPos1.x = sys->MousePos.x + 5;/**/TextPos1.y = sys->MousePos.y + 45;//���������̈ʒu�̓}�E�X�|�C���^����Z�o
			TextPos2.x = sys->MousePos.x + 160;/**/TextPos2.y = sys->MousePos.y + 5;//���햼�����̈ʒu�̓}�E�X�|�C���^����Z�o
			TextPos3.x = sys->MousePos.x + 5;/**/TextPos3.y = sys->MousePos.y + 5;//����̎�ނ̖��O�����̈ʒu�̓}�E�X�|�C���^����Z�o
	}
	else{//�������
			TextPos1.x = sys->MousePos.x + 5 - 256;/**/TextPos1.y = sys->MousePos.y + 45;//���������̈ʒu�̓}�E�X�|�C���^����Z�o
			TextPos2.x = sys->MousePos.x + 160 - 256;/**/TextPos2.y = sys->MousePos.y + 5;//���햼�����̈ʒu�̓}�E�X�|�C���^����Z�o
			TextPos3.x = sys->MousePos.x + 5 - 256;/**/TextPos3.y = sys->MousePos.y + 5;//����̎�ނ̖��O�����̈ʒu�̓}�E�X�|�C���^����Z�o
	}

	/**/
	//�A�C�e���̎�ނɂ���ĕ���
	/**/

	if(ChoseItem == 0){//���쒆�̃A�C�e�����u����v�Ȃ�
			if(BackPack_Weapon[ItemNumber][1] == 1){//���킪�n���h�K���n
					if(BackPack_Weapon[ItemNumber][2] == 0){//M1911
							ech = E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos2, "M1911", NormalColor);
							if(ech != 0){//�G���[�`�F�b�N
										_ASSERT(0);//�G���[�_�C�A���O��\��
							}
							ech = E3DDrawTextByFontID( sys->scid1, TextID[2], TextPos1, "�č����̈����₷��45���a���e", NormalColor);
							if(ech != 0){//�G���[�`�F�b�N
										_ASSERT(0);//�G���[�_�C�A���O��\��
							}
					}
					if(BackPack_Weapon[ItemNumber][2] == 2){//Glock95
							ech = E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos2, "Glock95", NormalColor);
							if(ech != 0){//�G���[�`�F�b�N
										_ASSERT(0);//�G���[�_�C�A���O��\��
							}
							ech = E3DDrawTextByFontID( sys->scid1, TextID[2], TextPos1, "�|���}�[�t���[���̃t���I�[�g���e", NormalColor);
							if(ech != 0){//�G���[�`�F�b�N
										_ASSERT(0);//�G���[�_�C�A���O��\��
							}
					}
					if(BackPack_Weapon[ItemNumber][2] == 3){//M92F
							ech = E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos2, "M92F", NormalColor);
							if(ech != 0){//�G���[�`�F�b�N
										_ASSERT(0);//�G���[�_�C�A���O��\��
							}
							ech = E3DDrawTextByFontID( sys->scid1, TextID[2], TextPos1, "�����₷���ČR�̐����̗p���e", NormalColor);
							if(ech != 0){//�G���[�`�F�b�N
										_ASSERT(0);//�G���[�_�C�A���O��\��
							}
					}
			}
			if(BackPack_Weapon[ItemNumber][1] == 4){//���킪�A�T���g���C�t���n
					if(BackPack_Weapon[ItemNumber][2] == 0){//M4
							ech = E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos2, "M4", NormalColor);
							if(ech != 0){//�G���[�`�F�b�N
										_ASSERT(0);//�G���[�_�C�A���O��\��
							}
							ech = E3DDrawTextByFontID( sys->scid1, TextID[2], TextPos1, "���w�T�C�g�𓋍ڂ����A�����J���\���鏬�e", NormalColor);
							if(ech != 0){//�G���[�`�F�b�N
										_ASSERT(0);//�G���[�_�C�A���O��\��
							}
					}
			}

		/**//////////
		/**////////

			if(BackPack_Weapon[ItemNumber][1] == -1){//�����Ȃ��A�C�e���摜�̏�Ȃ�
					ech =E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos2, "EMPTY", NormalColor);
					if(ech != 0){//�G���[�`�F�b�N
							_ASSERT(0);//�G���[�_�C�A���O��\��
					}
					ech = E3DDrawTextByFontID( sys->scid1, TextID[2], TextPos1, "���킪����܂���", NormalColor);
					if(ech != 0){//�G���[�`�F�b�N
							_ASSERT(0);//�G���[�_�C�A���O��\��
					}
			}

			if(ItemNumber == 0){//�}�E�X�����C���E�F�|���̏�ɂ����
					ech = E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos3, "MAINWEAPON", NormalColor);
					if(ech != 0){//�G���[�`�F�b�N
								_ASSERT(0);//�G���[�_�C�A���O��\��
					}
			}
			if(ItemNumber == 1){//�}�E�X���T�u�E�F�|���̏�ɂ����
					ech = E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos3, "SUBWEAPON", NormalColor);
					if(ech != 0){//�G���[�`�F�b�N
								_ASSERT(0);//�G���[�_�C�A���O��\��
					}
			}
			if(ItemNumber == 2){//�}�E�X���O���l�[�h�n�̏�ɂ����
					ech = E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos3, "GRENADE", NormalColor);
					if(ech != 0){//�G���[�`�F�b�N
								_ASSERT(0);//�G���[�_�C�A���O��\��
					}
			}
			if(ItemNumber == 3){//�}�E�X���C�����K�v�ȕ���̏�ɂ����
					ech = E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos3, "NEED REPAIR", NormalColor);
					if(ech != 0){//�G���[�`�F�b�N
								_ASSERT(0);//�G���[�_�C�A���O��\��
					}
			}
	}

	if(ChoseItem == 1){//���쒆�̃A�C�e�����u�e��v�Ȃ�

			if( BackPack_Ammo[ItemNumber][2] == 0){//M1911
					ech = E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos3, ".45ACP", NormalColor);
					if(ech != 0){//�G���[�`�F�b�N
									_ASSERT(0);//�G���[�_�C�A���O��\��
					}
					ech = E3DDrawTextByFontID( sys->scid1, TextID[2], TextPos1, "�č�����^�������e�p�̎���", NormalColor);
					if(ech != 0){//�G���[�`�F�b�N
									_ASSERT(0);//�G���[�_�C�A���O��\��
					}
			}


	}

	return 0;
}