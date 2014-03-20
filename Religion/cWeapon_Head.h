#pragma once
/*  ///////////////////////////////////////// */
//  ���퓝���N���X��錾����w�b�_�t�@�C���ł�
/*  ///////////////////////////////////////// */
#include "cweapon.h"// ����Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��

//�v���g�^�C�v�錾
class Enemy;
class PlayerChara;
class Stage;

/*���퓝���N���X�Ɋւ��邱�Ƃ��L�q���܂�*/
class Weapon_Head{

private:

	/*�ϐ��̐錾*/

	Weapon *NormalWeapon[2];//  �ʏ핐��(�E�N���b�N)���i�[����ϐ��|�C���^
	Weapon *SupportWeapon;// �T�|�[�g����(���N���b�N)���i�[����ϐ��|�C���^

	int WeaponLight;// ����̃}�Y���t���b�V�����C�g�i�[�ϐ�


public:

	/*�֐��̐錾*/

	int WpLoad( int EquipKind, int WeaponKind, int WeaponNum);// ������w��̑�����ނɑ���(���[�h)���܂� 
	int DeleteWeapon( int EquipKind);// ��������Ă��镐����폜���܂�
	int SetInitWeapon( int WpKind);// ����̃f�[�^�̏��������s���܂� 
	int ChkWeaponsLaunch( int Equipment);// ���ׂĂ̕���𔭎ˁE���~���Ă��邩�`�F�b�N����
	int AttackEnemys( Enemy *Ene, PlayerChara *PC, int ScreenPosArray[2], Stage *Stg);// �G�̓����蔻��`�F�b�N���s���܂�
	int WeaponsTreatment( int Equipment);//

	Weapon *Get_WeaponPointer( int Now_Equipment) const;// ����̎��̂̃|�C���^�[���������Ă���|�C���^�[�𓾂�֐�
	Weapon_Head();//�R���X�g���N�^�A�ϐ��̏��������s���܂�
	~Weapon_Head(){};//�f�X�g���N�^�A���f���̔j�������s���܂�

};