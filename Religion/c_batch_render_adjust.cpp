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

/* ����̕ύX���������ہA�`�悷�ׂ������ύX���܂��B */
int Batch_Render::BacthGunTrade( const int Wp_equipment){


	SetModel_ViewFlag( "MainWp", false);
	SetModel_ViewFlag( "SubWp", false);
	SetModel_ViewFlag( "SupportWp", false);

	switch(Wp_equipment){
			case 0:{//�����i�����C���E�F�|���Ȃ�

					SetModel_ViewFlag( "MainWp", true);
					break;
			}
			case 1:{

					SetModel_ViewFlag( "SubWp", true);
					break;
			}
			case 2:{

					SetModel_ViewFlag( "SupportWp", true);
					break;
			}
	}


	return 0;
};

/* �܂Ƃ߂�ꂽ�f�[�^���č\�z���܂��B���̑���͑����i��ς�����ԂȂǂŕK�v�ɂȂ�܂� */
int Batch_Render::BatchReset( const PlayerChara *PcC, const Stage *StgC, const Enemy *EneC, const Camera *Cam){

	





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

	for(int i=0; i < EneC->EnemyNum; i++){
			SetModel( EneC->Ene[i]->Get_BodyModel(), true);
			SetModel( EneC->Ene[i]->Get_WeaponH()->Get_WeaponPointer(0)->Get_Model(), true);
	}




	return 0;
};


int Batch_Render::SetModel( const int ID, const bool ViewFlag){

	SetModel_AddName( ID, "", ViewFlag);

	return 0;
}


int Batch_Render::SetModel_AddName( const int ID, const char *Name, const bool ViewFlag){

	/* �ϐ��̏�����&�錾 */
	Model MdlC;

	/* MdlC�\���̂ɏ��������܂� */
	MdlC.ID = ID;
	wsprintf( MdlC.Name, "%s", Name);
	MdlC.ViewFlag = ViewFlag;

	Mdl.push_back( MdlC);// �o�^��������Mdl�x�N�^�[�Ƀv�b�V������

	return 0;
}

vector<Model>::iterator Batch_Render::SearchModelFromName( const char *ObjName){

	/* �ϐ��̏�����&�錾 */
	vector<Model>::iterator it;// �C�e���[�^

	for( it = Mdl.begin(); it != Mdl.end(); it++){
			if( strcmp( ObjName, (*it).Name) == 0){
					break;// ���[�v�𔲂��o��
			}
	}

	if( it == Mdl.end()){// ��������������������Ȃ����
			_ASSERT( 1 , "Such Name is not found!");//�G���[�`�F�b�N
	}


	return it;
}

int Batch_Render::SetModel_ViewFlag( const char *Name, const bool ViewFlag){

	/* �ϐ��̏�����&�錾 */
	int ech = 0;
	vector<Model>::iterator it = SearchModelFromName( Name);// �C�e���[�^

	(*it).ViewFlag = ViewFlag;


	return 0;
}