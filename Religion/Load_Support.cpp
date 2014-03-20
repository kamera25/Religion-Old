/*�����ł́A����Ɋւ��邱�Ƃ��L�q����N���X�R�[�h�t�@�C���ł�
//��ɁA�T�|�[�g�n�����[�h���邱�Ƃ�������Ă��܂�
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "cWeapon_Support.h"//�T�|�[�g����֌W�̃w�b�_�t�@�C��



/* �T�|�[�g�n�̏������[�h����֐� */
int Weapon_Support::WpLoad_Support( const int Wpno){

	/* �ϐ��̏�����&�錾 */
	int ech = 0;
	char loadname[256] = "";

	//�ꎞ�I�ȕϐ��i���f���i�[���Ȃǁj
	int hsid = 0;//�e���f����ID
	int s_spid = 0;//�e�X�v���C�g�̃X�v���C�gID
	int Garbage = 0;//����Ȃ��ϐ����i�[���܂�



	if(Wpno == 0){//M26

			//���f���f�[�^�̃��[�h
			wsprintf( loadname, "%s\\data\\3d\\weapon\\support\\m26\\m26.sig", System::path);
			ech = E3DSigLoad( loadname, 0, 0.02f, &hsid);
			_ASSERT( ech != 1 );//�G���[�`�F�b�N

			//����X�v���C�g�̃��[�h
			wsprintf( loadname, "%s\\data\\3d\\weapon\\support\\m26\\pict.png", System::path);
			ech = E3DCreateSprite( loadname, 0, 0, &s_spid);
			_ASSERT( ech != 1 );//�G���[�`�F�b�N
	}
	if(Wpno == 1){//M67

			//���f���f�[�^�̃��[�h
			wsprintf( loadname, "%s\\data\\3d\\weapon\\support\\m67\\m67.sig", System::path);
			ech = E3DSigLoad( loadname, 0, 0.01f, &hsid);
			_ASSERT( ech != 1 );//�G���[�`�F�b�N

			//����X�v���C�g�̃��[�h
			wsprintf( loadname, "%s\\data\\3d\\weapon\\support\\m67\\pict.png", System::path);
			ech = E3DCreateSprite( loadname, 0, 0, &s_spid);
			_ASSERT( ech != 1 );//�G���[�`�F�b�N
	}
	if(Wpno == 2){//M18 �N���C���A

			//���f���f�[�^�̃��[�h
			wsprintf( loadname, "%s\\data\\3d\\weapon\\support\\m18\\m18.sig", System::path);
			ech = E3DSigLoad( loadname, 0, 0.01f, &hsid);
			_ASSERT( ech != 1 );//�G���[�`�F�b�N

			//����X�v���C�g�̃��[�h
			wsprintf( loadname, "%s\\data\\3d\\weapon\\support\\m18\\pict.png", System::path);
			ech = E3DCreateSprite( loadname, 0, 0, &s_spid);
			_ASSERT( ech != 1 );//�G���[�`�F�b�N
	}
	if(Wpno == 3){//C4

			//���f���f�[�^�̃��[�h
			wsprintf( loadname, "%s\\data\\3d\\weapon\\support\\c4\\c4.sig", System::path);
			ech = E3DSigLoad( loadname, 0, 0.01f, &hsid);
			_ASSERT( ech != 1 );//�G���[�`�F�b�N

			//����X�v���C�g�̃��[�h
			wsprintf( loadname, "%s\\data\\3d\\weapon\\support\\c4\\pict.png", System::path);
			ech = E3DCreateSprite( loadname, 0, 0, &s_spid);
			_ASSERT( ech != 1 );//�G���[�`�F�b�N
	}







	//�ϐ��������o�[�ϐ��Ɋi�[���܂�
	Set_Model( hsid);//����̃��f�����i�[
	Set_Sprite( s_spid);//����X�v���C�g���i�[
	Set_Sounds( -1, 0);
	Set_Sounds( -1, 1);

	return 1;
}