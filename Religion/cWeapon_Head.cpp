/* /////////////////////////////////////////// */
// ���퓝���N���X�֌W�̂��Ƃ��L�q����Ă��܂��B
/* /////////////////////////////////////////// */
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "cWeapon_head.h"// ���퓝���Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��
#include "cWeapon_Gun.h"//�e�Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��
#include "cWeapon_Support.h"//�T�|�[�g����Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��
#include "cstage.h"//�X�e�[�W�֌W�̃N���X�w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

/* �R���X�g���N�^�A�ϐ��̏��������s���܂� */
Weapon_Head::Weapon_Head(){

	/* �ϐ��̏����� */
	int ech = 0;// �G���[�`�F�b�N�ϐ�

	/* �����o�ϐ��̏��������s���܂� */
	NormalWeapon[0] = NULL;
	NormalWeapon[1] = NULL;
	SupportWeapon = NULL;
	GunHitChkModelID = NULL;

	/* �u�ג����v���f����ID */


	/* �}�Y���t���b�V���ȂǂɎg����A���C�g���쐬���܂� */
	ech = E3DCreateLight( &WeaponLight);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	return;
}

/* ������w��̑�����ނɑ���(���[�h)���܂�  */
int Weapon_Head::WpLoad( int EquipKind, int WeaponKind, int WeaponNum){

	/* �ϐ��̏����� */
	Weapon **SelectedKind = NULL;// �I�����ꂽ������ʂ̕���|�C���^



	/* �I�����ꂽ������ʂ̕���|�C���^���� */
	switch( EquipKind ){
			case 0:{// �呕���̏ꍇ
					SelectedKind = &NormalWeapon[0];
					break;
			}
			case 1:{// �������̏ꍇ
					SelectedKind = &NormalWeapon[1];
					break;
			}
			case 2:{// �T�|�[�g����̏ꍇ
					SelectedKind = &SupportWeapon;
					break;
			}
			default:{// ���݂��Ȃ��ꍇ
					return -1;
			}
	}

	/* �����A�����u��������Ȃ� */
	if( SelectedKind != NULL){
		DeleteWeapon( EquipKind);// �����邪�悢!
	}



	/* ����̃N���X�����̉������܂� */
	if( ( 0 <= WeaponKind) && ( WeaponKind <= 6)){// �e�̃��[�h���s���̂Ȃ�
			*SelectedKind = new Weapon_Gun( EquipKind, WeaponKind, WeaponNum);
	}
	else if( WeaponKind == 7){// �T�|�[�g����̃��[�h���s���̂Ȃ�
			*SelectedKind = new Weapon_Support( WeaponNum);
	}
	else{// ����ȊO�̐������Ȃ������Ȃ�
			_ASSERT( 0 );
			return -1;
	}






	return 0;
}

/* ��������Ă��镐����폜���܂� */
int Weapon_Head::DeleteWeapon( int EquipKind){


	switch( EquipKind){
			case 0:{// �啺�����I������Ă���Ȃ�
					delete NormalWeapon[0];
					NormalWeapon[0] = NULL;
					break;
			}
			case 1:{// ���������I������Ă���̂Ȃ�
					delete NormalWeapon[1];
					NormalWeapon[1] = NULL;
					break;
			}
			case 2:{// �T�|�[�g���킪�I������Ă���̂Ȃ�
					delete SupportWeapon;
					SupportWeapon = NULL;
					break;
			}

	}


	return 0;
}

/* �f�X�g���N�^*/
Weapon_Head::~Weapon_Head(){

	/* ������ */
	int ech = 0;

	DeleteWeapon( MAINWEAPON);
	DeleteWeapon( SUBWEAPON);
	DeleteWeapon( SUPPORTWEAPON);

	// �����蔻��p�̍ג������f�����폜���܂�
	if( GunHitChkModelID != NULL){
		ech = E3DDestroyHandlerSet(	GunHitChkModelID);
		_ASSERT( ech != 1 );//�G���[�`�F�b�N
	}

	// �}�Y���t���b�V���p�������폜����
	if( WeaponLight != NULL){
		 ech = E3DDestroyLight( WeaponLight);
		_ASSERT( ech != 1 );//�G���[�`�F�b�N
	}

	return ;
}

/* ����̎��̂̃|�C���^�[���������Ă���|�C���^�[�𓾂�֐� */
Weapon* Weapon_Head::Get_WeaponPointer( int Now_Equipment) const{


	if( ( Now_Equipment < 0) && ( 1 < Now_Equipment)){// �͈͊O�Ȃ�
			return NULL;
	}

	if( Now_Equipment == 2){
			return SupportWeapon;
	}

	return NormalWeapon[Now_Equipment];
}

/* ����̃f�[�^�̏��������s�Ȃ��֐� */
int Weapon_Head::SetInitWeapon( int Wpkind){
	
	switch(Wpkind){
			case 0:{// ���C���E�F�|��
					NormalWeapon[0]->InitWeapon();
					break;
		    }
			case 1:{// �T�u�E�F�|��
					NormalWeapon[1]->InitWeapon();
					break;
			}
			case 2:{// �T�|�[�g�E�F�|��
					SupportWeapon->InitWeapon();
					break;
			}
			default:{// ����ȊO(�S��)
					if( NormalWeapon[0] != NULL){
							NormalWeapon[0]->InitWeapon();
					}
					if( NormalWeapon[1] != NULL){
							NormalWeapon[1]->InitWeapon();
					}
					if( SupportWeapon != NULL){
							SupportWeapon->InitWeapon();
					}
			}
	}

	
	
	return 0;
}

/* ���ׂĂ̕���𔭎ˁE���~���Ă��邩�`�F�b�N���� */
int Weapon_Head::ChkWeaponsLaunch( int Equipment){

	if( Equipment == -1){// �����Ȃ��Ȃ�
			return -1;// �G���[�Ԃ�
	}

	Get_WeaponPointer(Equipment)->ChkWeaponLaunch();// �������̕���̔��˃L�[�m�F���s��


	return 0;
}

/* �G�̓����蔻��`�F�b�N���s���֐� */
int Weapon_Head::AttackEnemys( NPC_Head *NPC_H, PlayerChara *PC, int ScreenPosArray[2], Stage *Stg){

	/* �������̕��킪����΁A�����蔻����s�� */
	for( int i=0; i<3; i++){
			if( Get_WeaponPointer(i) != NULL){
					Get_WeaponPointer(i)->AttackEnemy( NPC_H,  PC, ScreenPosArray, Stg);
			}
	}



	return 0;
}

/* ����̃}�Y���t���b�V���E�����[�h�E */
int Weapon_Head::WeaponsTreatment( int Equipment, Stage *Stg){

	/* �ϐ��̏����� */
	int ech = 0;

	/* �������̕��킪����΁A�����蔻����s�� */
	for( int i=0; i<2; i++){
			if( Get_WeaponPointer(i) != NULL){
					Get_WeaponPointer(i)->WeaponTreatment( WeaponLight);
			}
	}

	/* �T�|�[�g����͈������Ⴄ�̂ŕʋL�q */
	if( Get_WeaponPointer(2) != NULL){
					Get_WeaponPointer(2)->WeaponTreatment( WeaponLight, Stg);
	}


	/* ����̃����[�h���s���܂� */
	if( ( Equipment != -1) && ( Equipment != 2)) Get_WeaponPointer(Equipment)->ReloadWeapon();// �������T�|�[�g����łȂ����



	return 0;
}