/*�����ł́A����Ɋւ��邱�Ƃ��L�q����N���X�R�[�h�t�@�C���ł�
//��ɁA�n���h�K�������[�h���邱�Ƃ�������Ă��܂�
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "cweapon.h"//����Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��



/* �n���h�K���̏������[�h����֐� */
int Weapon::GunLoad_Hand( const int Selectkind, const int Wpno){

	//�ϐ��̏�����
	int ech = 0;
	char loadname[256] = "";

	//�ꎞ�I�ȕϐ��i���f���i�[���Ȃǁj
	int hsid;//�e���f����ID
	int g_spid;//�e�X�v���C�g�̃X�v���C�gID
	int bone[4];//�e�̃{�[��
	int Garbage = 0;//����Ȃ��ϐ����i�[���܂�
	int sound[5];//���ʉ���ID


	if(Wpno == 0){//M1911

				//���f���f�[�^�̃��[�h
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\m1911\\m1911.sig", System::path);
				ech = E3DSigLoad( loadname, 0, 0.055f, &hsid);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				//����X�v���C�g�̃��[�h
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\m1911\\pict.png", System::path);
				ech = E3DCreateSprite( loadname, 1, 0, &g_spid);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				//����̃��[�V������ǂݍ���
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\m1911\\wait.qua", System::path);
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
		if(Wpno == 2){//Glock95

				//���f���f�[�^�̃��[�h
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\glock95\\glock.sig", System::path);
				ech = E3DSigLoad( loadname, 0, 0.037f, &hsid);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				//����X�v���C�g�̃��[�h
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\glock95\\pict.png", System::path);
				ech = E3DCreateSprite( loadname, 1, 0, &g_spid);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				//����̃��[�V������ǂݍ���
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\m1911\\wait.qua", System::path);
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


		}

		if(Wpno == 3){//M92F

				//���f���f�[�^�̃��[�h
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\m92f\\m92f.sig", System::path);
				ech = E3DSigLoad( loadname, 0, 0.039f, &hsid);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				//����X�v���C�g�̃��[�h
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\m92f\\pict.png", System::path);
				ech = E3DCreateSprite( loadname, 1, 0, &g_spid);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				//����̃��[�V������ǂݍ���
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\m92f\\wait.qua", System::path);
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
		wsprintf( loadname, "%s\\data\\sound\\se\\shot\\fire1.wav", System::path);
		ech = E3DLoadSound( loadname, 0, 1, 20, &sound[0]);
		if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
		};

		//�󌂂�
		wsprintf( loadname, "%s\\data\\sound\\se\\shot\\sky_fire.wav", System::path);
		ech = E3DLoadSound( loadname, 0, 1, 20, &sound[1]);
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