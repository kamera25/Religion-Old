/* �����ł́A�l�ԃN���X�֌W�̃A�V�X�g�֐����`����N���X�R�[�h�t�@�C���ł��B
// �A�V�X�g�֐��Ƃ̓N���X�ɂ�����v���C�x�[�g�ϐ��̎擾�E������s�Ȃ������̊֐��̑��̂ł��B
*/
#include "cpeople.h"// �����N���X�̃w�b�_�t�@�C��


int People::Get_UpMotion() const{

	return UpMotion;
}
int People::Set_UpMotion( int Number){

	UpMotion = Number;

	return 0;
}
int People::Get_UnderMotion() const{

	return UnderMotion;
}
int People::Set_UnderMotion( int Number){

	UnderMotion = Number;

	return 0;
}
int People::Get_Attitude() const{

	return Attitude;
}
int People::Set_Attitude( const int Number){

	Attitude = Number;

	return 0;
}
int People::Get_MyState() const{

	return MyState;
}
int People::Set_MyState( const int Number){

	MyState = Number;

	return 0;
}
int People::Get_AirOnPC(){

	return AirOnPC;
}
int People::Set_AirOnPC( int Number){

	AirOnPC = Number;

	return 0;
}
float People::Get_PC_Deg_XZ() const{

	return PC_Deg_XZ;
}
float People::Set_PC_Deg_XZ( float Number){

	PC_Deg_XZ = Number;

	return 0;
}
float People::Get_PC_Deg_Y() const{

	return PC_Deg_Y;
}
float People::Set_PC_Deg_Y( float Number){

	PC_Deg_Y = Number;

	return 0;
}
double People::Get_Acceleration() const{

	return Acceleration;
}
double People::Set_Acceleration( double Number){

	Acceleration = Number;

	return 0;
}
double People::Get_MoveSpeed() const{

	return MoveSpeed;
}
double People::Set_MoveSpeed( double Number){

	MoveSpeed = Number;

	return 0;
}