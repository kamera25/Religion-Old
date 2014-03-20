/*�����ł́A����Ɋւ��邱�Ƃ��L�q����N���X�R�[�h�t�@�C���ł�
//
*/
#include "cweapon.h"//����Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include "cstage.h"//�X�e�[�W�֌W�̃N���X�w�b�_�t�@�C��
#include "clive.h"//�G��L�����̐錾�w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

//�����ɃO���[�o���ϐ���錾
extern System *sys;//�V�X�e���N���X���w���A�N���X�̃|�C���^

/*��������[�h���邽�߂̊֐�*/
int Weapon::GunLoad( int Selectkind, int Wpkind, int Wpno){

	//�ϐ��̏�����
	int ech = 0;

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


	/**/
	WeaponOtherModel[Selectkind][0] = WeaponData[Selectkind][2];//�e�򐔂������ς��ɂ���
	WeaponOtherModel[Selectkind][1] = WeaponData[Selectkind][3];//�}�K�W�����������ς��ɂ���


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

		//�ϐ��������o�[�ϐ��Ɋi�[���܂�
		WeaponModel[Selectkind] = hsid;//����̃��f�����i�[
		WeaponSprite[Selectkind] = g_spid;//����X�v���C�g���i�[
		WeaponOtherModel[Selectkind][0] = 0;//����̎g�p�ςݒe�򃂃f�����i�[
		WeaponBone[Selectkind][0] = bone[0];//�e����O�̃{�[�����i�[
		WeaponBone[Selectkind][1] = bone[1];//�e�����̃{�[�����i�[
		WeaponBone[Selectkind][2] = bone[2];//�e�����̃{�[�����i�[
		WeaponBone[Selectkind][3] = bone[3];//�e�����̃{�[�����i�[




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

				//�����蔻�胂�f���̃��[�h
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\hitchk\\hitber.sig", sys->path);
				ech = E3DSigLoad( loadname, 0, 5.0f, &hit_hsid);//���f���̓ǂݍ���
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
				//�{�[���l�[������{�[��ID�̎擾�u�����蔻���v
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

		//�ϐ��������o�[�ϐ��Ɋi�[���܂�
		WeaponModel[Selectkind] = hsid;//����̃��f�����i�[
		WeaponSprite[Selectkind] = g_spid;//����X�v���C�g���i�[
		WeaponOtherModel[Selectkind][0] = 0;//����̎g�p�ςݒe�򃂃f�����i�[
		WeaponBone[Selectkind][0] = bone[0];//�e����O�̃{�[�����i�[
		WeaponBone[Selectkind][1] = bone[1];//�e�����̃{�[�����i�[
		WeaponBone[Selectkind][2] = bone[2];//�e�����̃{�[�����i�[
		WeaponBone[Selectkind][3] = bone[3];//�e�����̃{�[�����i�[


	return 0;
}
/*����Ɋւ���f�[�^���i�[����֐�*/
int Weapon::GunLoad_Data( int Selectkind, int Wpkind, int Wpno){

	//�ꎞ�I�ȕϐ��i���f���i�[���Ȃǁj
	int ammo;//�e��̍ő�l
	int mag;//�}�K�W���̍ő�l
	int distance;//�˒������̍ő�l
	int attack;//����̍U���l


	/*�n���h�K���֌W*/
	if( Wpkind == 1){
			if(Wpno == 0){//M1911

						//M1911�̃f�[�^���i�[���܂��B
						ammo = 7;
						mag = 7;
						distance = 100;
						attack = 100;
			}
			if(Wpno == 2){//Glock95
						
						//Glock�̃f�[�^���i�[���܂��B
						ammo = 50;
						mag = 3;
						distance = 60;
						attack = 30;
			}
			if(Wpno == 3){//M92FS
								
						//M92F�̃f�[�^���i�[���܂��B
						ammo = 15;
						mag = 2;
						distance = 120;
						attack = 80;
			}
	}
	/*�A�T���g���C�t���֌W*/
	if( Wpkind == 4){

			if( Wpno == 3){
						//M4�̃f�[�^���i�[���܂��B
						ammo = 30;
						mag = 5;
						distance = 160;
						attack = 140;
			}
	}


	WeaponData[Selectkind][0] = Wpkind;
	WeaponData[Selectkind][1] = Wpno;
	WeaponData[Selectkind][2] = ammo;
	WeaponData[Selectkind][3] = mag;
	WeaponData[Selectkind][4] = distance;
	WeaponData[Selectkind][5] = attack;


	return 0;
}

/*�R���X�g���N�^�A�ϐ��̏��������s���܂�*/
Weapon::Weapon(){





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
		}
	}

	return;
}