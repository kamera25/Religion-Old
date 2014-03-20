/* �����ł́A����N���X�֌W�̃A�V�X�g�֐����`����N���X�R�[�h�t�@�C���ł��B
// �A�V�X�g�֐��Ƃ̓N���X�ɂ�����v���C�x�[�g�ϐ��̎擾�E������s�Ȃ������̊֐��̑��̂ł��B
*/

#include "cweapon.h"//����Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��


/*���탂�f��ID�̎擾���s���܂�*/
int Weapon::GetWeaponModelID( int ItemNumber, int DataNumber) const{

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
int Weapon::GetWeaponData( int ItemNumber, int DataNumber) const{


	return WeaponData[ItemNumber][DataNumber];
}

/*�Q�[�����̕���̏ڍ׃f�[�^���擾���܂�*/
int Weapon::GetWeaponDataWhileGame( int ItemNumber, int DataNumber) const{


	return WeaponDataWhileGame[ItemNumber][DataNumber];
}

/*����X�v���C�g���擾���܂�*/
int Weapon::GetSpriteData( int ItemNumber) const{


	return WeaponSprite[ItemNumber];
}

/*���픭�˃t���O�ϐ����擾���܂�*/
int Weapon::GetWeaponFireFlag() const{

	return WeaponFireFlag;
}

/* ����̘A�˃J�E���^���擾���܂�*/
int Weapon::GetWeaponRapidFire() const{

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