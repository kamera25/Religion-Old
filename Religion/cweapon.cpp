/*�����ł́A����Ɋւ��邱�Ƃ��L�q����N���X�R�[�h�t�@�C���ł�
//��ɁA����N���X�̃R���X�g���N�^�E�f�X�g���N�^�ɂ��ď�����Ă��܂�
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "cenemy.h"//�G�N���X�̐錾�w�b�_�t�@�C��
#include "cweapon.h"//����Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��


/*�R���X�g���N�^�A�ϐ��̏��������s���܂�*/
Weapon::Weapon(){

	/*���ׂĂ̔z��ϐ��̏��������s���܂�*/
	for( int i=0; i<3; i++){
			WeaponModel[i] = -1;
			WeaponSprite[i] = -1;
			WeaponMuzzleLight[i] = -1;
			for( int j=0; j<10; j++){
					WeaponData[i][j] = -1;
			}
			for( int j=0; j<6; j++){
					WeaponData[i][j] = -1;
					WeaponDataWhileGame[i][j] = -1;
					WeaponBone[i][j] = -1;	
					WeaponSoundEfeect[i][j] = -1;
			}
			for( int j=0; j<4; j++){
				WeaponOtherModel[i][j] = -1;
			}
			for( int j=0; j<2; j++){
				WeaponEffect[i][j] = -1; 
			}
	}

	WeaponRapidFire = -1;
	WeaponFireFlag = -1;

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
					_ASSERT( ech != 1 );//�G���[�`�F�b�N

					ech = E3DDestroySprite( WeaponSprite[i]);//�X�v���C�g���폜���܂�
					_ASSERT( ech != 1 );//�G���[�`�F�b�N
					ech = E3DDestroyBillboard( WeaponEffect[i][0]);//�G�t�F�N�g���폜���܂�
					_ASSERT( ech != 1 );//�G���[�`�F�b�N
					ech = E3DDestroyLight( WeaponMuzzleLight[i]);
					_ASSERT( ech != 1 );//�G���[�`�F�b�N
					for( int j=0; j<6; j++){
						if( WeaponSoundEfeect[i][0] != 0){//�����t�@�C��������
							ech = E3DDestroySound( WeaponSoundEfeect[i][0]);
							_ASSERT( ech != 1 );//�G���[�`�F�b�N
						}
					}
		}	
	}

	return;
}