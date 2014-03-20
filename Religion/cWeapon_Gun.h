#pragma once
/* ///////////////////////////////////// */
// �e�@����N���X�̃L����������w�b�_�t�@�C���B
/* ///////////////////////////////////// */
#include "cWeapon.h"// �X�[�p�[�N���X�̕���N���X����`����Ă���w�b�_�t�@�C��

class NPC_Head;


/* �e�̃N���X(Weapon�N���X����̔h��) */
class Weapon_Gun : public Weapon{

private:

	/* �ϐ��̐錾 */
	int AmmoKind;//  �g�p�e��̎��
	int Accuracy;// ����̐��x
	int RapidFire;//  ���킪�A�ˉ\( 0:�\ 1:�s�\)
	int Magazine;// ����̃}�K�W����
	int OtherModel;// �{�̈ȊO�̃��f��(�e��Ȃ�)

	int RapidTime;//  1�b�ԂɑłĂ�A�ˉ�
	int ReloadTime;//  �����[�h����

	/* �Q�[�����̕ϐ� */
	int NowMagazine;//  �Q�[�����̃}�K�W����

	/* �֐��̐錾 */
	int GunLoad_Assault( const int Wpno);//�A�T���g���C�t���̏������[�h����֐�
	int GunLoad_Machine( const int Wpno);//�}�V���K���̏������[�h����֐�
	int GunLoad_Hand(  const int Wpno);//�n���h�K���̏������[�h����֐�
	int GunLoad_Shot(  const int Wpno);// �V���b�g�K���̏������[�h����֐�
	int GunLoad_Rifle(  const int Wpno);//���C�t���̏������[�h����֐�
	int GunLoad_Grenade(  const int Wpno);//�O���l�[�h�̏������[�h����֐�
	int GunLoad_SMG(  const int Wpno);//�T�u�}�V���K���̏������[�h����֐�
	int GunLoad_Data( const int Wpkind, const int Wpno);//����Ɋւ�������i�[����֐�

	int WeaponTreatment( const int WeaponLight);

public:

	int InitWeapon();// ����̏�Ԃ������ɂ���
	int AttackEnemy( NPC_Head *NPC_H, PlayerChara *PC, int ScreenPosArray[2], Stage *Stg);// �Q�[�����̓G�Ƃ̂�����&�U��������s���܂��B
	int ChkWeaponLaunch();// ����(�����ł͏e)�𔭖C���Ă��悢���m�F���AOK�Ȃ甭�˃t���O�����Ă܂�
	int ReloadWeapon();// ����̃����[�h���s���܂�

	/* �A�V�X�g�֐� */
	int Get_NowMagazine() const;
	int Get_Magazine() const;
	int Get_RapidFire() const;
	int Set_RapidFire( int Number);

	/* �֐��̐錾 */
	//int WpLoad( const int Selectkind, const int Wpkind, const int Wpno);//��������[�h���邽�߂̊֐�
	Weapon_Gun( const int Selectkind, const int Wpkind, const int Wpno);// �e����N���X�̃R���X�g���N�^(���[�h���s���܂�)
	~Weapon_Gun();// �e����N���X�̃f�X�g���N�^(�A�����[�h���s���܂�)
};