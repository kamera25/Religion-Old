/*�����ł́A����Ɋւ��邱�Ƃ��L�q����N���X�R�[�h�t�@�C���ł�
//��ɁA�O���l�[�h�����[�h���邱�Ƃ�������Ă��܂�
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "cweapon.h"//����Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��


/* ���C�t���̏������[�h����֐� */
int Weapon::GunLoad_Grenade( const int Selectkind, const int Wpno){



	//�ϐ��̏�����
	int ech = 0;
	char loadname[256] = "";

	//�ꎞ�I�ȕϐ��i���f���i�[���Ȃǁj
	int hsid;//�e���f����ID
	int g_spid;//�e�X�v���C�g�̃X�v���C�gID
	int Garbage = 0;//����Ȃ��ϐ����i�[���܂�



	if(Wpno == 0){//�O���l�[�h

			//���f���f�[�^�̃��[�h
			wsprintf( loadname, "%s\\data\\3d\\weapon\\grenade\\grenade\\grenade.sig", System::path);
			ech = E3DSigLoad( loadname, 0, 0.01f, &hsid);
			if(ech != 0 ){//�G���[�`�F�b�N
						_ASSERT( 0 );//�G���[�_�C�A���O
			};

			//����X�v���C�g�̃��[�h
			wsprintf( loadname, "%s\\data\\3d\\weapon\\rifle\\sr-25\\pict.png", System::path);
			ech = E3DCreateSprite( loadname, 1, 0, &g_spid);
			if(ech != 0 ){//�G���[�`�F�b�N
						_ASSERT( 0 );//�G���[�_�C�A���O
			};


	}









	//�ϐ��������o�[�ϐ��Ɋi�[���܂�
	WeaponModel[Selectkind] = hsid;//����̃��f�����i�[
	WeaponSprite[Selectkind] = g_spid;//����X�v���C�g���i�[
	WeaponOtherModel[Selectkind][0] = 0;//����̎g�p�ςݒe�򃂃f�����i�[



	return 0;
}