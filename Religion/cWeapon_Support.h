#pragma once
/* ///////////////////////////////////// */
// ����N���X�̃L����������w�b�_�t�@�C���B
/* ///////////////////////////////////// */
#include "cWeapon.h"// �X�[�p�[�N���X�̕���N���X����`����Ă���w�b�_�t�@�C��




/* �T�|�[�g����̃N���X(Weapon�N���X����̔h��) */
class Weapon_Support : public Weapon{

private:


	/* �֐��̐錾 */
	int WpLoad_Support(  const int Wpno);// �T�|�[�g�n�̏������[�h����֐�


public:

	/* �֐��̐錾 */
	Weapon_Support( const int Wpno);// �R���X�g���N�^(���[�h���s���܂�)
	~Weapon_Support();// �f�X�g���N�^(�A�����[�h���s���܂�)


};