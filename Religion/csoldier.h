#pragma once
/* ���m�N���X�̐錾������w�b�_�t�@�C���B
// !���m!�N���X�͐l�ԃN���X(�e�͐���)���p�����Ă����Ă��܂�
*/
#include "cpeople.h"// �l�ԃN���X�̃w�b�_�t�@�C��
#include "cWeapon_head.h"// ���퓝���Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��
#include "citem.h"// �A�C�e���̐錾�w�b�_�t�@�C��

/* �v���g�^�C�v�錾 */
class Stage;

/* ���m�N���X�̐錾 */
class Soldier: public People{

private:

	/* ////////// */
	// �ϐ��̐錾 
	/* ////////// */

	// ���m�̏�ԕϐ�
	int Wp_equipment;//�������Ă��镐��̎��

	// ���f���n
	int DummyModel;//�_�~�[���f���̃��f��ID

	/* ///////////////////////////////////////////////////////// */
	// Bone_ID�z��ɂ̓{�[�����i�[����܂�!
	// [0]������E [1]�������E [2]���Ȃ�
	/* ///////////////////////////////////////////////////////// */
	int Bone_ID[10];

	/* ///////////////////////////////////////////////////////// */
	// !�N�I���^�[�j�I���̎���ID���i�[���܂�!
	// [0] �e�̌��� [1] �e�̓����蔻�胂�f���̌���
	// [2] ���f�����W�̌��� [3] �e�̕����APC�̎p��
	// [4]�����蔻�胂�f���̌���
	/* ///////////////////////////////////////////////////////// */
	int Quater_ID[10];


	int BeforeAirOnPC;// �L�������O��A�󒆂ɂ�����������܂�

public:

	/* �N���X�̐錾 */
	Weapon_Head Wpn;// �E�F�|���N���X�̎���
	Item Item;// �A�C�e���N���X�̎���

	static const int AirOff = 0;
	static const int AirOn = 1;


	/* �֐��̐錾 */
	int MovePosOnGround( Stage *Stg) ;// �L�����N�^�[���O���E���h�̏�ɒu�����߂̊֐�
	int GunPutOnHand();// ���ݎ����Ă�e�������߂̃��[�V�����E�V�X�e�����Ǌ�����֐�
	int Batch_PeopleMotion();// �l�Ԃ̃��[�V������p���Ȃǂ�ݒ肵�܂�
	Soldier( const int selchara, const int Wpselect_equipment);// �R���X�g���N�^�A���m���f���̃��[�h�����s�Ȃ��܂�
	virtual ~Soldier();//���z�R���X�g���N�^

	virtual int StatusReset();// �\���W���[�N���X�̏�Ԃ������ɖ߂��܂�(���X�^�[�g���ŗ��p)

	/* �A�V�X�g(�擾�E���)�֐��̐錾 */
	int Get_Wp_equipment() const; // Wp_equipment�̎擾�֐�
	int Set_Wp_equipment( int Number);// Wp_equipment�̑���֐�
	int Get_DummyModel() const;// �_�~�[���f����ID�擾�֐�
	int Set_DummyModel( int Number);// �_�~�[���f����ID����֐�
	int Get_Bone_ID( int BoneNo) const;// �{�[��ID�̎擾�֐�
	int Set_Bone_ID( int BoneNo, int Number);// �{�[��ID�̑���֐�
	int Get_Quaternion( int QNo) const;// �N�H�[�^�j�I���̎擾�֐�
	int Set_Quaternion( int QNo, int Number);// �N�H�[�^�j�I���̑���֐�
	Weapon_Head* Get_WeaponH();// �E�F�|�������N���X�|�C���^�̎擾�֐�

};