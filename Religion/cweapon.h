#pragma once
/*����N���X�̃L����������w�b�_�t�@�C���B
//
*/

/*����N���X�Ɋւ��邱�Ƃ��L�q*/
class Weapon{

private:

	/*�ϐ��̐錾*/
	int WeaponModel[3];
	int WeaponSprite[3];
	int WeaponKind[3];
	int WeaponData[3][6];
	int WeaponDataWhileGame[3][6];
	int WeaponBone[3][6];
	int WeaponOtherModel[3][4];

	/*�֐��̐錾*/
	int GunLoad_Assault( int Selectkind, int Wpno);//�A�T���g���C�t���̏������[�h����֐�
	int GunLoad_Hand( int Selectkind, int Wpno);//�n���h�K���̏������[�h����֐�
	int GunLoad_Data( int Selectkind, int Wpkind, int Wpno);//����Ɋւ�������i�[����֐�

public:

	/*�֐��̐錾*/
	int GunLoad( int Selectkind, int Wpkind, int Wpno);//��������[�h���邽�߂̊֐�
	Weapon();//�R���X�g���N�^�A�ϐ��̏��������s���܂�
	~Weapon();//�f�X�g���N�^�A���f���̔j�������s���܂�




};