/*�����ł́A����Ɋւ��邱�Ƃ��L�q����N���X�R�[�h�t�@�C���ł�
//��ɁA�O���l�[�h�����[�h���邱�Ƃ�������Ă��܂�
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "cWeapon_Gun.h"//����Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��


/* �O���l�[�h�̏������[�h����֐� */
int Weapon_Gun::GunLoad_Grenade( const int Wpno){

	/* �ϐ��̏����� */
	int ech = 0;
	char loadname[256] = "";

	// ���݂��G���[�Ȃ̂ŋ����I��
	return -1;

	//�ꎞ�I�ȕϐ��i���f���i�[���Ȃǁj
	int hsid = 0;//�e���f����ID
	int g_spid = 0;//�e�X�v���C�g�̃X�v���C�gID
	int Garbage = 0;//����Ȃ��ϐ����i�[���܂�






	//�ϐ��������o�[�ϐ��Ɋi�[���܂�
	Set_Model( hsid);//����̃��f�����i�[
	Set_Sprite( g_spid);//����X�v���C�g���i�[
	OtherModel = 0;//����̎g�p�ςݒe�򃂃f�����i�[



	return 0;
}