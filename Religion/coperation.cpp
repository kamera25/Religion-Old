/* ���̃\�[�X�̓I�y���[�V�����̎d�󏈗�������AOpsMissionBranchStart�֐��Ȃ�
// �I�y���[�V�����֌W�ɂ��ċL�q����Ă���"cOperation.cpp"�\�[�X�ł�
/* ////////////////////////////////////////////////////////////////////// */

#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_
#include "coperation.h"//�I�y���[�V�����J�n�֌W�̃N���X�w�b�_�t�@�C��
#include "cMission.h"

#include "clive.h"//�G��L�����̐錾�w�b�_�t�@�C��


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
				OpsMissionFromFile( "shinryoku.mis");
				//OpsMission1_Shinryoku();
				break;
		}
	}









	return 0;
}

/* �t�@�C������~�b�V��������ǂݎ��A�~�b�V�������J�n���܂��B */
int Operation::OpsMissionFromFile( char *File)
{


	/* �ȉ��A�t�@�C����ǂݍ��񂾌�̏��� */

	
	Mission Mis;
	Mis.Intialize();
	Mis.Loading( File);

	// �Q�[���J�n
	Mis.MainProc();



	return 0;
}










// ��{�I�� BatchPreprate �̏�����S�čs���܂�
int Operation::NormalBatchProces(){

	pBatP->BatchSpriteSet( pPly);
	pBatP->BatchRender( 0);
	pBatP->Batch_BillBoard( 0);
	pBatP->BatchSpriteRender( 0);
	pBatP->BatchFont( 1, pPly);
	pBatP->Batch_Present();

	return 0;
}