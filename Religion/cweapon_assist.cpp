/* �����ł́A����N���X�֌W�̃A�V�X�g�֐����`����N���X�R�[�h�t�@�C���ł��B
// �A�V�X�g�֐��Ƃ̓N���X�ɂ�����v���C�x�[�g�ϐ��̎擾�E������s�Ȃ������̊֐��̑��̂ł��B
*/

#include "cweapon.h"//����Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��


int Weapon::Set_Model( const int Number){

	Model = Number;

	return 0;
}
int Weapon::Get_Model() const{

	return Model;
}
int Weapon::Set_Sprite( const int Number){

	Sprite = Number;

	return 0;
}
int Weapon::Get_Sprite() const{

	return Sprite;
}
int Weapon::Set_Effects(  const int Number){

	Effects = Number;

	return 0;
}
int Weapon::Get_Effects() const{

	return Effects;
}
int Weapon::Set_Sounds( const int Number, const int ArrayNum){

	Sounds[ArrayNum] = Number;

	return 0;
}
int Weapon::Get_Sounds( const int ArrayNum) const{

	return Sounds[ArrayNum];
}
int Weapon::Set_Bones( const int Number, const int ArrayNum){

	Bones[ArrayNum] = Number;

	return 0;
}
int Weapon::Get_Bones( const int ArrayNum) const{

	return Bones[ArrayNum]; 
}
int Weapon::Set_Kind( const int Number){

	Kind = Number;

	return 0;
}
int Weapon::Get_Kind() const{

	return Kind;
}
int Weapon::Set_Number( const int Numbers){

	Number = Numbers;

	return 0;
}
int Weapon::Get_Number() const{

	return Number;
}
int Weapon::Set_Attack( const int Number){

	Attack = Number;

	return 0;
}
int Weapon::Get_Attack() const{

	return Attack;
}
int Weapon::Set_Ammo( const int Number){

	Ammo = Number;

	return 0;
}
int Weapon::Get_Ammo() const{

	return Ammo;
}
int Weapon::Get_FlashCounter(){

	return FlashCounter;
}
int Weapon::Set_FlashCounter( const int Number){

	FlashCounter = Number;

	return 0;
}
int Weapon::Set_NowAmmo( const int Number){

	NowAmmo = Number;

	return 0;
}
int Weapon::Get_NowAmmo(){

	return NowAmmo;
}
int Weapon::Set_WaitingTime( const int Number){

	WaitingTime = Number;

	return 0;
}
int Weapon::Get_WaitingTime() const{

	return WaitingTime;
}
int Weapon::Get_NowFireFlag() const{

	return NowFireFlag;
}
int Weapon::Set_NowFireFlag( int Number){

	NowFireFlag = Number;

	return 0;
}
int Weapon::Get_Range() const{
	
	return Range;
};
int Weapon::Set_Range( int Number){

	Range = Number;

	return 0;
}



/* ���z�֐� */
int Weapon::Get_NowMagazine() const{

	_ASSERT( 1 );//�G���[�_�C�A���O��\��
	return -1;
}
int Weapon::Get_Magazine() const{

	_ASSERT( 1 );//�G���[�_�C�A���O��\��
	return -1;
};
int Weapon::Get_RapidFire() const{

	_ASSERT( 1 );//�G���[�_�C�A���O��\��
	return -1;
}
int Weapon::Set_RapidFire( int Number){

	_ASSERT( 1 );//�G���[�_�C�A���O��\��
	return -1;
}