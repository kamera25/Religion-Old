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
/* Stamina�̎擾�֐� */
int Creature::Get_Stamina() const{

	return Stamina;
}
/* Stamina�̑���֐� */
int Creature::Set_Stamina( int Number){

	if( Number <= 0){
		Number = 0;
	}
	
	Stamina = Number;
	

	return 0;
}
/* MaxStamina�̎擾�֐� */
int Creature::Get_MaxStamina() const{

	return MaxStamina;
}
/* MaxStamina�̑���֐� */
int Creature::Set_MaxStamina( int Number){

	MaxStamina = Number;

	return 0;
}

/* Attack�̎擾�֐� */
int Creature::Get_Attack() const{

	return Attack;
}
/* Attack�̑���֐� */
int Creature::Set_Attack( int Number){

	Attack = Number;

	return 0;
}

/* SkillSlot�̎擾�֐� */
int Creature::Get_SkillSlot() const{

	return SkillSlot;
}
/* SkillSlot�̑���֐� */
int Creature::Set_SkillSlot( int Number){

	SkillSlot = Number;

	return 0;
}

/* Branch�̎擾�֐� */
int Creature::Get_Branch() const{

	return Branch;
}
/* Branch�̑���֐� */
int Creature::Set_Branch( int Number){

	if( ( Number < 0)&&( 4 < Number)) Number = -1;// ���������肳��Ă��Ȃ�������A�m�[�}���ɓK��������
	Branch = Number;

	return 0;
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

int Creature::Delete_Skill(){

	delete [] Skill;

	return 0;
}

int Creature::Set_Skill( int *Pointer ){

	Skill = Pointer;

	return 0;
}

int Creature::Set_EquipmentSkillSum( int Number ){

	EquipmentSkillSum = Number;

	return 0;
}