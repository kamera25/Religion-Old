/*�����ł́A���f����X�v���C�g�̕`��ɕK�v�ȏ������W�A�܂��`��ŕK�v��
//�֐��������I�Ɏ��s���邱�Ƃ��ł���悤�ɂ��邽�߂̃N���X�R�[�h�t�@�C��
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "c_batch_preparat.h"//�`��ɕK�v�ȃN���X�̐錾�w�b�_�t�@�C��
#include "clive.h"//�G��L�����̐錾�w�b�_�t�@�C��
#include "cweapon.h"//����Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��
#include "cstage.h"//�X�e�[�W�֌W�̃N���X�w�b�_�t�@�C��
#include "cenemy.h"//�G�N���X�̐錾�w�b�_�t�@�C��
#include "ccamera.h"//�J�����֌W�̃N���X�w�b�_�t�@�C��
#include <string>

/* ����̕ύX���������ہA�`�悷�ׂ������ύX���܂��B */
int Batch_Render::BacthGunTrade( const int Wp_equipment){

	// ���ׂĂ̕��탂�f����\�����Ȃ��悤��
	SetModel_ViewFlag( "MainWp", false);
	SetModel_ViewFlag( "SubWp", false);
	SetModel_ViewFlag( "SupportWp", false);

	// ���ׂĂ̕���X�v���C�g��\�����Ȃ��悤��
	Set_ViewFlag( "MainWp", false);
	Set_ViewFlag( "SubWp", false);
	Set_ViewFlag( "SupportWp", false);

	//�e�̒e���\����
	Set_ViewFlag( "Ammober", true);

	//�e�̃}�K�W����\����
	Set_ViewFlag( "Magber", true);


	switch(Wp_equipment){
			case -1:{// �Ȃɂ��������Ă��Ȃ��Ȃ�
				
					//�e�̒e��𖳕\����
					Set_ViewFlag( "Ammober", false);

					//�e�̃}�K�W���𖳕\����
					Set_ViewFlag( "Magber", false);

					break;
			}
			case 0:{// �����i�����C���E�F�|���Ȃ�
					SetModel_ViewFlag( "MainWp", true);
					Set_ViewFlag( "MainWp", true);
					break;
			}
			case 1:{// �����i���T�u�E�F�|���Ȃ�
					SetModel_ViewFlag( "SubWp", true);
					Set_ViewFlag( "SubWp", true);
					break;
			}
			case 2:{// �����i���T�|�[�g����Ȃ�
					SetModel_ViewFlag( "SupportWp", true);
					Set_ViewFlag( "SupportWp", true);
					break;
			}
	}



	return 0;
};

/* �܂Ƃ߂�ꂽ�f�[�^���č\�z���܂��B���̑���͑����i��ς�����ԂȂǂŕK�v�ɂȂ�܂� */
int Batch_Render::BatchReset( const PlayerChara *PcC, const Stage *StgC, NPC_Head *NPCC, const Camera *Cam){

	





	/* ////////////////////////////////////////////////////////////////// */
	// �����āA�X�e�[�W�N���X�ƃv���C���[�N���X����f�[�^��ǂݍ��݂܂��B
	/* ////////////////////////////////////////////////////////////////// */

	/*���C���E�F�|������f�[�^��ǂݍ��݂܂�*/
	if( PcC->Wpn.Get_WeaponPointer(0) != NULL){
			SetModel_AddName( PcC->Wpn.Get_WeaponPointer(0)->Get_Model(), "MainWp", true);
	}
	/*�T�u�E�F�|������f�[�^��ǂݍ��݂܂�*/
	if( PcC->Wpn.Get_WeaponPointer(1) != NULL){
			SetModel_AddName( PcC->Wpn.Get_WeaponPointer(1)->Get_Model(), "SubWp", true);
	}
	/*�O���l�[�h�n����f�[�^��ǂݍ��݂܂�*/
	if( PcC->Wpn.Get_WeaponPointer(2) != NULL){
			SetModel_AddName( PcC->Wpn.Get_WeaponPointer(2)->Get_Model(), "SupportWp", true);
	}


	/*PC�̃L�����N�^�[���f���f�[�^��ǂݍ��݂܂�*/
	SetModel( PcC->Get_BodyModel(), true);

	/*�X�e�[�W���f���f�[�^��ǂݍ��݂܂�*/
	for(int i=0; i<3; i++){
		SetModel( StgC->Stage_hsid[i], true);
	};


	/**/
	///����p���`�F�b�N�����K�v�Ȃ���
	/**/
	
	/*�ǃ��f���f�[�^��ǂݍ��݂܂�*/
	for(int i=0; i<3; i++){
		SetModel( StgC->Stage_hsid[i], false);
	};


	/*�J�����_�~�[���f����ǂݍ��݂܂�*/
	SetModel( Cam->DummyModel, false);

	map<string, NPC_t>::iterator it;// �C�e���[�^

	for( it = NPCC->Get_NPC_begin(); it != NPCC->NPC_endit(); it++){
			SetModel( (*it).second.NPC_Mdl->Get_BodyModel(), true);
			SetModel( (*it).second.NPC_Mdl->Get_WeaponH()->Get_WeaponPointer(0)->Get_Model(), true);
	}

//	BacthGunTrade( PcC->Get_Wp_equipment());


	return 0;
};


int Batch_Render::SetModel( const int ID, const bool ViewFlag){

	static int Number = 0;// ���O�����Ȃ����f���́A�����݂̂ŊǗ�
	char cbuf[5];

	wsprintf( cbuf, "%d\0", Number);	
	SetModel_AddName( ID, cbuf, ViewFlag);

	Number++;
	if( Number >= 10000)
	{
		Number = 0;
	}

	return 0;
}


int Batch_Render::SetModel_AddName( const int ID, const char *Name, const bool ViewFlag){

	/* �ϐ��̏�����&�錾 */
	Model MdlC;

	/* MdlC�\���̂ɏ��������܂� */
	MdlC.ID = ID;
	MdlC.ViewFlag = ViewFlag;

	Mdl.insert( make_pair( string(Name), MdlC));
	//Mdl.push_back( MdlC);// �o�^��������Mdl�x�N�^�[�Ƀv�b�V������

	return 0;
}

//int Batch_Render::SearchModelFromName( const char *ObjName, map< const char *, Model>::iterator *it){
//	
//
//
//	//vector<Model>::iterator iit;
//
//	//for( iit = Mdl.begin(); iit != Mdl.end(); iit++){
//	//		if( strcmp( ObjName, (*iit).Name) == 0){
//	//				*it = iit;
//	//				return 0;// ���[�v�𔲂��o��
//	//		}
//	//}
//
//	/* �ȉ��A�������ꂽ������������Ȃ������Ƃ��̏��� */
//	
//
//	return -1;
//}

int Batch_Render::SetModel_ViewFlag( const char *Name, const bool ViewFlag){

	/* �ϐ��̏�����&�錾 */
	int ech = 0;
	map< string, Model>::iterator it;


	if( Mdl.count(Name))
	{
		it = Mdl.find(Name);
	}
	else// ��������������������Ȃ����
	{
			_ASSERT( 1 );//�G���[
			return -1;
	}

		
	// ���������������������	
	(*it).second.ViewFlag = ViewFlag;


	return 0;
}