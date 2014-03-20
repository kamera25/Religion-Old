/*�����ł́A����Ɋւ��邱�Ƃ��L�q����N���X�R�[�h�t�@�C���ł�
//
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "cenemy.h"//�G�N���X�̐錾�w�b�_�t�@�C��
#include "cweapon.h"//����Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��


//�����ɃO���[�o���ϐ���錾
extern System *sys;//�V�X�e���N���X���w���A�N���X�̃|�C���^

/*��������[�h���邽�߂̊֐�*/
int Weapon::GunLoad( int Selectkind, int Wpkind, int Wpno){

	//�ϐ��̏�����
	int ech = 0;
	char loadname[256] = "";

	/*���łɏe���擾���Ă���A���̏e�f�[�^�ɏ㏑������Ȃ�*/
	if( WeaponModel[Selectkind] != 0){//�I�𒆂̃J�e�S���Ƀf�[�^������̂Ȃ�
				ech = E3DDestroyHandlerSet( WeaponModel[Selectkind]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				ech = E3DDestroySprite( WeaponSprite[Selectkind]);//�X�v���C�g���폜���܂�
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};
	}


	/*�e�̃��f���̃��[�h*/
	if(Wpkind == 1) GunLoad_Hand( Selectkind, Wpno);//�n���h�K���n
	if(Wpkind == 4) GunLoad_Assault( Selectkind, Wpno);//�A�T���g���C�t���n

	//�G�t�F�N�g�r���{�[�h�����[�h���܂�
	wsprintf( loadname, "%s\\data\\img\\effect\\explosion1.png", sys->path);
	ech = E3DCreateBillboard ( loadname, 96, 96, 0, 1, 1, &WeaponEffect[Selectkind][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};

	//�G�t�F�N�g��\�ߓ��߂��Ă���
	ech = E3DSetBillboardAlpha( WeaponEffect[Selectkind][0], 0.0f);
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};

	//�t���b�V���̌��������(�O���l�[�h�͔�����)
	ech = E3DCreateLight( &WeaponMuzzleLight[Selectkind]);
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};


	/*����f�[�^�̃��[�h������*/
	GunLoad_Data( Selectkind, Wpkind, Wpno);


	return 0;
}
/*�A�T���g���C�t���̏������[�h����֐�*/
int Weapon::GunLoad_Assault( int Selectkind, int Wpno){

	//�ϐ��̏�����
	int ech = 0;
	char loadname[256] = "";

	//�ꎞ�I�ȕϐ��i���f���i�[���Ȃǁj
	int hsid;//�e���f����ID
	int hit_hsid;//�e�̓����蔻�胂�f��ID
	int g_spid;//�e�X�v���C�g�̃X�v���C�gID
	int bone[4];//�e�̃{�[��
	int sound[6];//���ʉ��f�[�^
	int Garbage = 0;//����Ȃ��ϐ����i�[���܂�


	if(Wpno == 0){//M4

				//���f���f�[�^�̃��[�h
				wsprintf( loadname, "%s\\data\\3d\\weapon\\assault\\m4\\m4a5.sig", sys->path);
				ech = E3DSigLoad( loadname, 0, 0.042f, &hsid);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				//�����蔻�胂�f���̃��[�h
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\hitchk\\hitber.sig", sys->path);
				ech = E3DSigLoad( loadname, 0, 5.0f, &hit_hsid);//���f���̓ǂݍ���
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				//����X�v���C�g�̃��[�h
				wsprintf( loadname, "%s\\data\\3d\\weapon\\assault\\m4\\pict.png", sys->path);
				ech = E3DCreateSprite( loadname, 1, 0, &g_spid);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				//����̃��[�V������ǂݍ���
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\m1911\\wait.qua", sys->path);
				ech = E3DAddMotion( hsid, loadname, 1, &Garbage, &Garbage);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};


				/**/
				//�{�[���f�[�^�̃��[�h���s���܂�
				/**/

				/*//�{�[���l�[������{�[��ID�̎擾�u�e������_X+�v
				E3DGetBoneNoByName( hsid, "�e��", &bone[0]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};
				//�{�[���l�[������{�[��ID�̎擾�u�e�������_X+�v
				E3DGetBoneNoByName( hsid, "�e��", &bone[1]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};*/

				bone[0] = 0;//�e����O�̃{�[�����i�[
				bone[1] = 0;//�e�����̃{�[�����i�[

				//�{�[���l�[�����瓖���蔻��{�[��ID�̎擾�u�����蔻���v
				E3DGetBoneNoByName( hit_hsid, "�����蔻���", &bone[2]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};
				//�{�[���l�[������{�[��ID�̎擾�u�����蔻�荪�v
				E3DGetBoneNoByName( hit_hsid, "�����蔻�荪", &bone[3]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};



		}

		/*�T�E���h�����[�h���܂�*/
		//���ˉ�
		wsprintf( loadname, "%s\\data\\sound\\se\\shot\\rifle_fire.wav", sys->path);
		ech = E3DLoadSound( loadname, 1, 1, 20, &sound[0], 16);
		if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
		};

		//�󌂂�
		wsprintf( loadname, "%s\\data\\sound\\se\\shot\\sky_fire.wav", sys->path);
		ech = E3DLoadSound( loadname, 1, 1, 20, &sound[1], 16);
		if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
		};

		/*�����͂��͈͂��w��*/
		ech = E3DSet3DSoundEmiDist( sound[0], 25000.0f);
		if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
		};

		ech = E3DSet3DSoundEmiDist( sound[1], 4000.0f);
		if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
		};



		//�ϐ��������o�[�ϐ��Ɋi�[���܂�
		WeaponModel[Selectkind] = hsid;//����̃��f�����i�[
		WeaponSprite[Selectkind] = g_spid;//����X�v���C�g���i�[
		WeaponOtherModel[Selectkind][0] = 0;//����̎g�p�ςݒe�򃂃f�����i�[
		/*WeaponBone[Selectkind][0] = bone[0];//�e����O�̃{�[�����i�[
		WeaponBone[Selectkind][1] = bone[1];//�e�����̃{�[�����i�[
		WeaponBone[Selectkind][2] = bone[2];//�e�����̃{�[�����i�[
		WeaponBone[Selectkind][3] = bone[3];//�e�����̃{�[�����i�[*/
		WeaponSoundEfeect[Selectkind][0] = sound[0];
		WeaponSoundEfeect[Selectkind][1] = sound[1];



	return 0;
}
/*�n���h�K���̏������[�h����֐�*/
int Weapon::GunLoad_Hand( int Selectkind, int Wpno){

	//�ϐ��̏�����
	int ech = 0;
	char loadname[256] = "";

	//�ꎞ�I�ȕϐ��i���f���i�[���Ȃǁj
	int hsid;//�e���f����ID
	int hit_hsid;//�e�̓����蔻�胂�f��ID
	int g_spid;//�e�X�v���C�g�̃X�v���C�gID
	int bone[4];//�e�̃{�[��
	int Garbage = 0;//����Ȃ��ϐ����i�[���܂�
	int sound[5];//���ʉ���ID


	if(Wpno == 0){//M1911

				//���f���f�[�^�̃��[�h
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\m1911\\m1911.sig", sys->path);
				ech = E3DSigLoad( loadname, 0, 0.055f, &hsid);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				//�����蔻�胂�f���̃��[�h
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\hitchk\\hitber.sig", sys->path);
				ech = E3DSigLoad( loadname, 0, 5.0f, &hit_hsid);//���f���̓ǂݍ���
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				//����X�v���C�g�̃��[�h
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\m1911\\pict.png", sys->path);
				ech = E3DCreateSprite( loadname, 1, 0, &g_spid);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				//����̃��[�V������ǂݍ���
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\m1911\\wait.qua", sys->path);
				ech = E3DAddMotion( hsid, loadname, 1, &Garbage, &Garbage);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};


				/**/
				//�{�[���f�[�^�̃��[�h���s���܂�
				/**/

				//�{�[���l�[������{�[��ID�̎擾�u�e������_X+�v
				E3DGetBoneNoByName( hsid, "�e��", &bone[0]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};
				//�{�[���l�[������{�[��ID�̎擾�u�e�������_X+�v
				E3DGetBoneNoByName( hsid, "�e��", &bone[1]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};
				//�{�[���l�[�����瓖���蔻��{�[��ID�̎擾�u�����蔻���v
				E3DGetBoneNoByName( hit_hsid, "�����蔻���", &bone[2]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};
				//�{�[���l�[������{�[��ID�̎擾�u�����蔻�荪�v
				E3DGetBoneNoByName( hit_hsid, "�����蔻�荪", &bone[3]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};


		}
		if(Wpno == 2){//Glock95

				//���f���f�[�^�̃��[�h
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\glock95\\glock.sig", sys->path);
				ech = E3DSigLoad( loadname, 0, 0.037f, &hsid);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				//�����蔻�胂�f���̃��[�h
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\hitchk\\hitber.sig", sys->path);
				ech = E3DSigLoad( loadname, 0, 5.0f, &hit_hsid);//���f���̓ǂݍ���
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				//����X�v���C�g�̃��[�h
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\glock95\\pict.png", sys->path);
				ech = E3DCreateSprite( loadname, 1, 0, &g_spid);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				//����̃��[�V������ǂݍ���
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\m1911\\wait.qua", sys->path);
				ech = E3DAddMotion( hsid, loadname, 1, &Garbage, &Garbage);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};


				/**/
				//�{�[���f�[�^�̃��[�h���s���܂�
				/**/

				/*//�{�[���l�[������{�[��ID�̎擾�u�e������_X+�v
				E3DGetBoneNoByName( hsid, "�e��", &bone[0]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};
				//�{�[���l�[������{�[��ID�̎擾�u�e�������_X+�v
				E3DGetBoneNoByName( hsid, "�e��", &bone[1]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};*/

				bone[0] = 0;//�e����O�̃{�[�����i�[
				bone[1] = 0;//�e�����̃{�[�����i�[
				//�{�[���l�[�����瓖���蔻��{�[��ID�̎擾�u�����蔻���v
				E3DGetBoneNoByName( hit_hsid, "�����蔻���", &bone[2]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};
				//�{�[���l�[������{�[��ID�̎擾�u�����蔻�荪�v
				E3DGetBoneNoByName( hit_hsid, "�����蔻�荪", &bone[3]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};



		}

		if(Wpno == 3){//M92F

				//���f���f�[�^�̃��[�h
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\m92f\\m92f.sig", sys->path);
				ech = E3DSigLoad( loadname, 0, 0.039f, &hsid);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				//����X�v���C�g�̃��[�h
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\m92f\\pict.png", sys->path);
				ech = E3DCreateSprite( loadname, 1, 0, &g_spid);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				//����̃��[�V������ǂݍ���
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\m92f\\wait.qua", sys->path);
				ech = E3DAddMotion( hsid, loadname, 1, &Garbage, &Garbage);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};


				/**/
				//�{�[���f�[�^�̃��[�h���s���܂�
				/**/

				//�{�[���l�[������{�[��ID�̎擾�u�e������_X+�v
				E3DGetBoneNoByName( hsid, "�e��", &bone[0]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};
				//�{�[���l�[������{�[��ID�̎擾�u�e�������_X+�v
				E3DGetBoneNoByName( hsid, "�e��", &bone[1]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};


		}

		/*�T�E���h�����[�h���܂�*/
		//���ˉ�
		wsprintf( loadname, "%s\\data\\sound\\se\\shot\\fire1.wav", sys->path);
		ech = E3DLoadSound( loadname, 0, 1, 20, &sound[0], 16);
		if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
		};

		//�󌂂�
		wsprintf( loadname, "%s\\data\\sound\\se\\shot\\sky_fire.wav", sys->path);
		ech = E3DLoadSound( loadname, 0, 1, 20, &sound[1], 16);
		if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
		};

		/*�����͂��͈͂��w��*/
		ech = E3DSet3DSoundEmiDist( sound[0], 25000.0f);
		if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
		};

		ech = E3DSet3DSoundEmiDist( sound[1], 5000.0f);
		if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
		};


		//�ϐ��������o�[�ϐ��Ɋi�[���܂�
		WeaponModel[Selectkind] = hsid;//����̃��f�����i�[
		WeaponSprite[Selectkind] = g_spid;//����X�v���C�g���i�[
		WeaponOtherModel[Selectkind][0] = 0;//����̎g�p�ςݒe�򃂃f�����i�[
		WeaponBone[Selectkind][0] = bone[0];//�e����O�̃{�[�����i�[
		WeaponBone[Selectkind][1] = bone[1];//�e�����̃{�[�����i�[
		WeaponSoundEfeect[Selectkind][0] = sound[0];
		WeaponSoundEfeect[Selectkind][1] = sound[1];


	return 0;
}
/*����Ɋւ���f�[�^���i�[����֐�*/
int Weapon::GunLoad_Data( int Selectkind, int Wpkind, int Wpno){

	//�ꎞ�I�ȕϐ��i���f���i�[���Ȃǁj
	int ammo = 0;//�e��̍ő�l
	int mag = 0;//�}�K�W���̍ő�l
	int distance = 0;//�˒������̍ő�l
	int attack = 0;//����̍U���l
	int rapid_fire = 0;//�A�ˉ\�e��
	double firecounter = 0.0;//�A�˂̐��l


	/*�n���h�K���֌W*/
	if( Wpkind == 1){
			if(Wpno == 0){//M1911

						//M1911�̃f�[�^���i�[���܂��B
						ammo = 7;
						mag = 7;
						distance = 100;
						attack = 100;
						firecounter = 1.0;
						rapid_fire = 0;
			}
			if(Wpno == 2){//Glock95
						
						//Glock�̃f�[�^���i�[���܂��B
						ammo = 50;
						mag = 3;
						distance = 60;
						attack = 30;
						firecounter = 3.0;
						rapid_fire = 1;
			}
			if(Wpno == 3){//M92FS
								
						//M92F�̃f�[�^���i�[���܂��B
						ammo = 15;
						mag = 2;
						distance = 120;
						attack = 80;
						firecounter = 1.4;
						rapid_fire = 0;
			}
	}
	/*�A�T���g���C�t���֌W*/
	if( Wpkind == 4){

			if( Wpno == 0){
						//M4�̃f�[�^���i�[���܂��B
						ammo = 30;
						mag = 5;
						distance = 160;
						attack = 140;
						firecounter = 1.6;
						rapid_fire = 1;
			}
	}


	WeaponData[Selectkind][0] = Wpkind;
	WeaponData[Selectkind][1] = Wpno;
	WeaponData[Selectkind][2] = ammo;
	WeaponData[Selectkind][3] = mag;
	WeaponData[Selectkind][4] = distance;
	WeaponData[Selectkind][5] = attack;
	WeaponData[Selectkind][6] = int( 30 / firecounter) ;
	WeaponData[Selectkind][7] = rapid_fire;


	return 0;
}
/*���탂�f��ID�̎擾���s���܂�*/
int Weapon::GetWeaponModelID( int ItemNumber, int DataNumber){

	/*�ϐ��̏�����*/
	int DataID = 0;//�Ԃ�ID���i�[����ϐ�

	if( DataNumber == 0){//���C�����f���Ȃ�
			DataID = WeaponModel[ItemNumber];
	}
	if( DataNumber == 1){//�g�p�ςݒe��̃��f��
			DataID = WeaponOtherModel[ItemNumber][0];
	}




	return DataID;
}
/*����̏ڍ׃f�[�^���擾���܂�*/
int Weapon::GetWeaponData( int ItemNumber, int DataNumber){


	return WeaponData[ItemNumber][DataNumber];
}
/*�Q�[�����̕���̏ڍ׃f�[�^���擾���܂�*/
int Weapon::GetWeaponDataWhileGame( int ItemNumber, int DataNumber){


	return WeaponDataWhileGame[ItemNumber][DataNumber];
}
/*����X�v���C�g���擾���܂�*/
int Weapon::GetSpriteData( int ItemNumber){


	return WeaponSprite[ItemNumber];
}
/* ����̘A�˃J�E���^���擾���܂�*/
int Weapon::GetWeaponRapidFire(){

	return WeaponRapidFire;
}
/*����̏�Ԃ����������A�e�e��}�K�W������t�ɂ��܂�*/
int Weapon::SetInitWeaponData(){

	for( int i=0; i<3; i++){
			WeaponDataWhileGame[i][0] = WeaponData[i][2];
			WeaponDataWhileGame[i][1] = WeaponData[i][3];
	}

	return 0;
}
/*����̉������Đ����܂�(3DSE��p)*/
int Weapon::PlayWeaponSound( int Wp_equipment, int PlayNo, float MuzzlePosArray[3]){

	/*�ϐ��̏�����*/
	int ech = 0;//�G���[�m�F�ϐ�
	D3DXVECTOR3 MuzzleFlashSound( 340.0, 340.0, 340.0);//�}�Y���t���b�V���T�E���h�̑��xXYZ
	D3DXVECTOR3 MuzzlePos( MuzzlePosArray[0], MuzzlePosArray[1], MuzzlePosArray[2]);//�}�Y���t���b�V���T�E���h�̑��xXYZ


	/*���̈ʒu�Ƒ������w�肵�܂�*/
	ech = E3DSet3DSoundMovement( WeaponSoundEfeect[Wp_equipment][PlayNo], MuzzlePos, MuzzleFlashSound);
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};

	/*���ˉ���炵�܂�*/
	ech = E3DPlaySound( WeaponSoundEfeect[Wp_equipment][PlayNo], 0, 0, 0);
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};


	return 0;
}
/*���픭�˃t���O�ϐ����擾���܂�*/
int Weapon::GetWeaponFireFlag(){

	return WeaponFireFlag;
}
/*�R���X�g���N�^�A�ϐ��̏��������s���܂�*/
Weapon::Weapon(){

	/*���ׂĂ̔z��ϐ��̏��������s���܂�*/
	for( int i=0; i<3; i++){
			WeaponModel[i] = 0;
			WeaponSprite[i] = 0;
			WeaponMuzzleLight[i] = 0;
			for( int j=0; j<7; j++){
					WeaponData[i][j] = 0;
			}
			for( int j=0; j<6; j++){
					WeaponData[i][j] = 0;
					WeaponDataWhileGame[i][j] = 0;
					WeaponBone[i][j] = 0;	
					WeaponSoundEfeect[i][j] = 0;
			}
			for( int j=0; j<4; j++){
				WeaponOtherModel[i][j] = 0;
			}
			for( int j=0; j<2; j++){
				WeaponEffect[i][j] = 0; 
			}
	}

	WeaponRapidFire = 0;
	WeaponFireFlag = 0;

	return;
}
/*�f�X�g���N�^�A���f���̔j�������s���܂�*/
Weapon::~Weapon(){

	//�ϐ��̏�����
	int ech = 0;

	//�e�̃f�[�^�̍폜���܂��i�ŏ����珇�ԂɃ��C���E�T�u�E�O���l�[�h�̏��Ԃł��j
	for(int i = 0;i < 3; i++){
		if( WeaponModel[i] != 0){//�I�𒆂̃J�e�S���Ƀf�[�^������̂Ȃ�
					ech = E3DDestroyHandlerSet( WeaponModel[i]);//���f�����폜���܂�
					if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
					};

					ech = E3DDestroySprite( WeaponSprite[i]);//�X�v���C�g���폜���܂�
					if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
					};
					ech = E3DDestroyBillboard( WeaponEffect[i][0]);//�G�t�F�N�g���폜���܂�
					if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
					};
					ech = E3DDestroyLight( WeaponMuzzleLight[i]);
					if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
					};
					for( int j=0; j<6; j++){
						if( WeaponSoundEfeect[i][0] != 0){//�����t�@�C��������
							ech = E3DDestroySound( WeaponSoundEfeect[i][0]);
							if(ech != 0 ){//�G���[�`�F�b�N
										_ASSERT( 0 );//�G���[�_�C�A���O
							};
						}
					}
		}	
	}

	return;
}