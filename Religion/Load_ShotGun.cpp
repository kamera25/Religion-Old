/*�����ł́A����Ɋւ��邱�Ƃ��L�q����N���X�R�[�h�t�@�C���ł�
//��ɁA�V���b�g�K�������[�h���邱�Ƃ�������Ă��܂�
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "cWeapon_Gun.h"//����Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��


/* �V���b�g�K���̏������[�h����֐� */
int Weapon_Gun::GunLoad_Shot(  const int Wpno){

	//�ϐ��̏�����
	int ech = 0;
	char loadname[256] = "";

	//�ꎞ�I�ȕϐ��i���f���i�[���Ȃǁj
	int hsid;//�e���f����ID
	int g_spid;//�e�X�v���C�g�̃X�v���C�gID
	int bone[4];//�e�̃{�[��
	int Garbage = 0;//����Ȃ��ϐ����i�[���܂�
	int sound[5];//���ʉ���ID


	if(Wpno == 0){//M1897

			//���f���f�[�^�̃��[�h
			wsprintf( loadname, "%s\\data\\3d\\weapon\\shotgun\\m1897\\m1897.sig", System::path);
			ech = E3DSigLoad( loadname, 0, 0.040f, &hsid);
			_ASSERT( ech != 1 );//�G���[�`�F�b�N

			//����X�v���C�g�̃��[�h
			wsprintf( loadname, "%s\\data\\3d\\weapon\\shotgun\\m1897\\pict.png", System::path);
			ech = E3DCreateSprite( loadname, 1, 0, &g_spid);
			_ASSERT( ech != 1 );//�G���[�`�F�b�N

			//����̃��[�V������ǂݍ���
			wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\m1911\\wait.qua", System::path);
			//ech = E3DAddMotion( hsid, loadname, 1, &Garbage, &Garbage);
			_ASSERT( ech != 1 );//�G���[�`�F�b�N


			/**/
			//�{�[���f�[�^�̃��[�h���s���܂�
			/**/

			//�{�[���l�[������{�[��ID�̎擾�u�e������_X+�v
			E3DGetBoneNoByName( hsid, "�e��", &bone[0]);
			_ASSERT( ech != 1 );//�G���[�`�F�b�N
			//�{�[���l�[������{�[��ID�̎擾�u�e�������_X+�v
			E3DGetBoneNoByName( hsid, "�e��", &bone[1]);
			_ASSERT( ech != 1 );//�G���[�`�F�b�N


	}





	/*�T�E���h�����[�h���܂�*/
	//���ˉ�
	wsprintf( loadname, "%s\\data\\sound\\se\\shot\\fire1.wav", System::path);
	ech = E3DLoadSound( loadname, 0, 1, 20, &sound[0]);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	//�󌂂�
	wsprintf( loadname, "%s\\data\\sound\\se\\shot\\sky_fire.wav", System::path);
	ech = E3DLoadSound( loadname, 0, 1, 20, &sound[1]);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/*�����͂��͈͂��w��*/
	ech = E3DSet3DSoundEmiDist( sound[0], 25000.0f);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	ech = E3DSet3DSoundEmiDist( sound[1], 5000.0f);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N


	//�ϐ��������o�[�ϐ��Ɋi�[���܂�
	Set_Model( hsid);//����̃��f�����i�[
	Set_Sprite( g_spid);//����X�v���C�g���i�[
	OtherModel =  0;//����̎g�p�ςݒe�򃂃f�����i�[
	Set_Bones( bone[0], 0);//�e����O�̃{�[�����i�[
	Set_Bones( bone[1], 1);//�e�����̃{�[�����i�[
	Set_Sounds( sound[0], 0);
	Set_Sounds( sound[1], 1);






	return 0;
}