/* �����ł́A�����N���X�֌W�̃A�V�X�g�֐����`����N���X�R�[�h�t�@�C���ł��B
// �A�V�X�g�֐��Ƃ̓N���X�ɂ�����v���C�x�[�g�ϐ��̎擾�E������s�Ȃ������̊֐��̑��̂ł��B
*/
#include "ccreature.h"// �����N���X�̃w�b�_�t�@�C��

/* MaxHP�ϐ��̎擾�֐� */
int Creature::Get_BodyModel() const{

	return BodyModel;
}
/* HP�ϐ��̎擾�֐� */
int Creature::Get_HP() const{

	return HP;
}
/* BodyModel�ϐ��̎擾�֐� */
int Creature::Get_MaxHP() const{

	return MaxHP;
}

int Creature::Set_BodyModel( int Number){

	BodyModel = Number;

	return 0;
}

int Creature::Set_HP( int Number){

	HP = Number;

	return 0;
}

int Creature::Set_MaxHP( int Number){

	MaxHP = Number;

	return 0;
}