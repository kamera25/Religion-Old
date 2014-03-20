/*�����ł́A�G���f����G�̓����Ɋւ��邱�Ƃ�
//�֐��������I�Ɏ��s���邱�Ƃ��ł���悤�ɂ��邽�߂̃N���X�R�[�h�t�@�C��
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "cenemy.h"//NPC�N���X�̐錾�w�b�_�t�@�C��
#include "cstage.h"//�X�e�[�W�֌W�̃N���X�w�b�_�t�@�C��
#include "csoldier.h"// ���m�N���X�̐錾�w�b�_�t�@�C��

#include <math.h>


/*�R���X�g���N�^�A�N���X�ϐ��̏��������s���܂�*/
NPC_Head::NPC_Head(){


	return;
}

/*�G�����⃂�f�������[�h���邽�߂̊֐�*/
int NPC_Head::LoadEnemyModel( const int Ene_Kind, const int Ene_No){

	LoadEnemyModelAddName( "", Ene_Kind, Ene_No);// ���O�Ȃ���LoadEnemyModel�����s����

	return 0;
}

/* �G�����⃂�f�������[�h���邽�߂̊֐�(���O�t��) */
int NPC_Head::LoadEnemyModelAddName( const char *Name, const int Ene_Kind, const int Ene_No){

	//�ϐ��̏�����
	int ech = 0;//�G���[�`�F�b�N�ϐ��̏�����
	char loadname[256] = "";
	NPC_t NPCC;// NPC�R���e�i�ɓ���邽�߂�NPC�\����


	switch( Ene_Kind){
			case 0:{// �l��
					switch(Ene_No){
							case 0:{
									/* �N���[�`���[�N���X�|�C���^��ێ�����
									// �ϐ��ɕ��m�N���X�̃|�C���^���� */
									NPCC.NPC_Mdl = new Soldier( 1, 0);

									/* ���[�V�����w�� */
									NPCC.NPC_Mdl->Set_UpMotion( 0);
									NPCC.NPC_Mdl->Set_MyState( 0);
									NPCC.NPC_Mdl->Set_UnderMotion( 1);

									/* ����̃��[�h */
									NPCC.NPC_Mdl->Get_WeaponH()->WpLoad(0,0,0);// �A�T���g���C�t���̓���

									break;
						   }
					}
					break;
		   }
	}


	/* �푰�Ǝ�ނ������� */
	NPCC.NPCRace = Ene_Kind;
	NPCC.NPCNumber = Ene_No;	 
	NPCC.TargetNaviPointID = -1;


	wsprintf( NPCC.NPCName, "%s", Name);
	
	/* ���[�h����NPC�\���̂��v�b�V������ */
	NPC.push_back( NPCC);

	/*�G�l�~�[�̐�������₷*/
//	EnemyNum = EnemyNum +1;


	return 0;
}

/*�G�̓������܂Ƃ߂ē��������߂̊֐�*/
int NPC_Head::MoveEnemys( Stage *Stg){

	//�ϐ��̏�����
	int ech = 0;//�G���[�`�F�b�N�ϐ��̏�����
	int GroundResult = 0;
	D3DXVECTOR3 ReflectVec( 0.0, 0.0, 0.0);
	vector<NPC_t>::iterator it;// �C�e���[�^

	/* �����A�i�r���[�����g���Ȃ��Ƃ��� */
	if( Stg->Navi.Get_NaviRailAvailable() == false) return -1;// �����I��


	/* ////////////////////////////////////////////////////////////// */
	// �Ƃ肠�����i�r�|�C���g�����œ����悤�Ɏw�肷��A��X���G���\��
	/* ////////////////////////////////////////////////////////////// */
	for( it = NPC.begin(); it != NPC.end(); it++){

		if( (*it).NPCRace == 0){
			if( (*it).NPCNumber == 0){
					
				if(0 < (*it).NPC_Mdl->Get_HP()){
						// �i�r���[���ɂ����PC�ʒu�����߂܂�
						Stg->Navi.PCControlByNaviRail( (*it).NPC_Mdl->Get_BodyModel(), &(*it).TargetNaviPointID, Stg->Navi.NaviLineID[ (*it).TargetNaviLineID ]);
							
						(*it).NPC_Mdl->Set_UpMotion( 0);
						(*it).NPC_Mdl->Set_UnderMotion( 1);
				}
				else{// HP���Ȃ��Ȃ�
						(*it).NPC_Mdl->Set_MyState(5);// ���S��Ԃɂ���
				}

				// PC�̋󒆈ʒu�𐧌䂵�܂�
				//Ene[i]->MovePosOnGround( Stg);

				// ���[�V�����܂Ƃߏ���
				(*it).NPC_Mdl->Batch_PeopleMotion();
						
				// �������ɒu���܂�
				(*it).NPC_Mdl->GunPutOnHand();
			}
		}
	}





	return 0;
}
/* �G�̍��W���i�r�|�C���g����ɐݒ肵�܂�*/
int NPC_Head::SetEnemyPosByNaviPoint( Stage *Stg, const char *Name, const int NaviLine, const int NaviPoint){

	/* �ϐ��̐錾&������ */
	vector<NPC_t>::iterator it;

	if( Stg->Navi.Get_NaviRailAvailable() == false) return 0;// �i�r���C�������p�s�Ȃ�A������

	/* ���O����NPC�̃��X�g������ */
	SearchNPCFromName( Name, &it);

	Stg->Navi.SetPosByNaviPoint( (*it).NPC_Mdl->Get_BodyModel(), NaviLine, NaviPoint);

	(*it).TargetNaviLineID = NaviLine;

	return 0;
}
/* �G�̍��W���܂Ƃ߂ăi�r�|�C���g����ɐݒ肵�܂� */
int NPC_Head::SetEnemyPosByNaviPointArray( Stage *Stg, const char *Name, const int *EnemyOnNaviLine, int const *EnemyOnNaviPoint, const int ArrayMax){

	for(int i=0; i<ArrayMax; i++){
			SetEnemyPosByNaviPoint( Stg, (Name+20*i), *(EnemyOnNaviLine + i), *(EnemyOnNaviPoint + i));
	}



	return 0;
}
/*�f�X�g���N�^�A���f���̍폜���s���܂�*/
NPC_Head::~NPC_Head(){

	//�ϐ��̏�����
	int ech = 0;
	vector<NPC_t>::iterator it;// �C�e���[�^

	for( it = NPC.begin(); it != NPC.end(); it++){
		delete (*it).NPC_Mdl;
	}

	return;
}

int NPC_Head::SearchNPCFromName( const char *ObjName, vector<NPC_t>::iterator *it){

	/* �ϐ��̏�����&�錾 */
	vector<NPC_t>::iterator iit;// �C�e���[�^

	for( iit = NPC.begin(); iit != NPC.end(); iit++){
			if( strcmp( ObjName, (*iit).NPCName) == 0){
					*it = iit;
					return 0;// ���[�v�𔲂��o��
			}
	}

	// ��������������������Ȃ����
	_ASSERT( 1 );//�G���[�`�F�b�N


	return -1;
}