/* ���̃\�[�X�̓I�y���[�V�����̎d�󏈗�������AOpsMissionBranchStart�֐��Ȃ�
// �I�y���[�V�����֌W�ɂ��ċL�q����Ă���"cOperation.cpp"�\�[�X�ł�
/* ////////////////////////////////////////////////////////////////////// */

#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_
#include "coperation.h"//�I�y���[�V�����J�n�֌W�̃N���X�w�b�_�t�@�C��




int Operation::OpsMissionBranchStart( const int MissionNumber){

	/* �ϐ��̏����� & �錾 */
	/* N/a */

	/* ���[�h��ʂ�\�����܂� */
	System::WaitRender();//�ǂݍ��݉�ʂ�\�������܂�


	/* ///////////////////////////////////////////////////////////// */
	// !! �C������ !! 
	// 
	//  ���ꂩ�牺�͂��ꂼ��̃~�b�V�������J�n���邽�߂̕���ł��B
	// �ϐ�:MissionNumber�ł��ꂼ�ꕪ��A�֐��͊�{�I��Operation�N���X
	// ���ɋL�q����܂��B��:OpsMission1_Shinryoku();...
	// ���Ƃ̃V�X�e���͂��ׂĂ��ꂼ��̊֐��Ɋۓ������܂��B
	/* //////////////////////////////////////////////////////////// */
	switch( MissionNumber){
			
		case(0):{ // �V�΂̃u���X���b�h
				OpsMission1_Shinryoku();
				break;
		}
	}









	return 0;
}