/*�����ł́A�����N���X�̃L�����E�G�̊֐����`����N���X�R�[�h�t�@�C���ł��B
//���ɃQ�[�����J�n���鎞�ɕK�v�Ȋ֐�������������Ă��܂��B
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "clive.h"//�G��L�����̐錾�w�b�_�t�@�C��

/* �v���C���[�L�����N�^�[�̃R���X�g���N�^ */
PlayerChara::PlayerChara( int selchara, int Wpselect_equipment) : Soldier( selchara, Wpselect_equipment){

	StatusReset();

	return;
}

/*�v���C���[�L�����N�^�[�̃f�X�g���N�^*/
PlayerChara::~PlayerChara(){

	int ech = 0;//�G���[�m�F�ϐ��̏�����








}


/* �\���W���[�N���X�̏�Ԃ������ɖ߂��܂�(���X�^�[�g���ŗ��p) */
int PlayerChara::StatusReset()
{

	Soldier::StatusReset();

	ChangePerspectiveMode = 0;

	return 0;
}