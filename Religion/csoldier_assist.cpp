/* �����ł́A���m�N���X�֌W�̃A�V�X�g�֐����`����N���X�R�[�h�t�@�C���ł��B
// �A�V�X�g�֐��Ƃ̓N���X�ɂ�����v���C�x�[�g�ϐ��̎擾�E������s�Ȃ������̊֐��̑��̂ł��B
*/
#include "csoldier.h"// ���m�N���X�̐錾�w�b�_�t�@�C��
#include "cWeapon_head.h"// ���퓝���Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��



/* Wp_equipment�̎擾�֐� */
int Soldier::Get_Wp_equipment() const{

	return Wp_equipment;
}
/* Wp_equipment�̑���֐�*/
int Soldier::Set_Wp_equipment( int Number){

	Wp_equipment = Number;

	return 0;
}
/* �_�~�[���f����ID�擾�֐� */
int Soldier::Get_DummyModel() const{

	return DummyModel;
}
/* �_�~�[���f����ID����֐� */
int Soldier::Set_DummyModel( int Number){

	DummyModel = Number;

	return 0;
}
/* �{�[��ID�̎擾�֐� */
int Soldier::Get_Bone_ID( int BoneNo) const{

	return Bone_ID[BoneNo];
}
/* �{�[��ID�̎擾�֐� */
int Soldier::Set_Bone_ID( int BoneNo, int Number){

	Bone_ID[BoneNo] = Number;

	return 0;
}
/* �N�H�[�^�j�I���̎擾�֐� */
int Soldier::Get_Quaternion( int QNo) const{

	return Quater_ID[QNo];
}
/* �N�H�[�^�j�I���̑���֐� */
int Soldier::Set_Quaternion( int QNo, int Number){

	Quater_ID[QNo] = Number;

	return 0;
}
/* �E�F�|���|�C���^�̎擾�֐� */
Weapon_Head* Soldier::Get_WeaponH(){

	return &Wpn;
}