#pragma once
/* ///////////////////////////////////// */
// ����N���X�̃L����������w�b�_�t�@�C���B
/* ///////////////////////////////////// */
#include "cWeapon.h"// �X�[�p�[�N���X�̕���N���X����`����Ă���w�b�_�t�@�C��




/* �T�|�[�g����̃N���X(Weapon�N���X����̔h��) */
class Weapon_Support : public Weapon{

private:


	/* �֐��̐錾 */
	int WpLoad_Support(  const int Wpno);// �T�|�[�g�n�̑����I�ȓǂݍ��ݏ���������֐�
	int SupportLoad_Data( int Wpkind, int Wpno);// �T�|�[�g�n�̕���f�[�^�����[�h����֐�

public:

	/* �֐��̐錾 */
	int InitWeapon();// ����̏�Ԃ������ɂ���
	int AttackEnemy( Enemy *Ene, PlayerChara *PC, int ScreenPosArray[2], Stage *Stg);
	int WeaponTreatment( const int WeaponLight, Stage *Stg);// �Q�[�����̏e�̑���Ɋւ��邱�Ƃ����܂�
	int ChkWeaponLaunch();// ����𔭖C�E�������Ă��悢���m�F���AOK�Ȃ甭�˃t���O�����Ă܂�
	Weapon_Support( const int Wpno);// �R���X�g���N�^(���[�h���s���܂�)
	~Weapon_Support();// �f�X�g���N�^(�A�����[�h���s���܂�)


};