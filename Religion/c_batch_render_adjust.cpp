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


	if( Wp_equipment == -1){//�����i���Ȃɂ��Ȃ��Ȃ�
			Render_hsids[4] = 0;
			Render_hsids[5] = 0;
			Render_hsids[6] = 0;
			ChkIn_hsids[4] = 0;
			ChkIn_hsids[5] = 0;
			ChkIn_hsids[6] = 0;
	}
	if( Wp_equipment == 0){//�����i�����C���E�F�|���Ȃ�
			Render_hsids[4] = PCWp_hsids[0][0][0];
			Render_hsids[5] = PCWp_hsids[0][0][1];
			Render_hsids[6] = PCWp_hsids[0][0][2];
			ChkIn_hsids[4] = PCWp_hsids[0][0][0];
			ChkIn_hsids[5] = PCWp_hsids[0][0][1];
			ChkIn_hsids[6] = PCWp_hsids[0][0][2];
	}
	if( Wp_equipment == 1){//�����i���T�u�E�F�|���Ȃ�
			Render_hsids[4] = PCWp_hsids[0][1][0];
			Render_hsids[5] = PCWp_hsids[0][1][1];
			Render_hsids[6] = PCWp_hsids[0][1][2];
			ChkIn_hsids[4] = PCWp_hsids[0][1][0];
			ChkIn_hsids[5] = PCWp_hsids[0][1][1];
			ChkIn_hsids[6] = PCWp_hsids[0][1][2];
	}
	if( Wp_equipment == 2){//�����i���O���l�[�h�n�Ȃ�
			Render_hsids[4] = PCWp_hsids[0][2][0];
			Render_hsids[5] = PCWp_hsids[0][2][1];
			Render_hsids[6] = PCWp_hsids[0][2][2];
			ChkIn_hsids[4] = PCWp_hsids[0][2][0];
			ChkIn_hsids[5] = PCWp_hsids[0][2][1];
			ChkIn_hsids[6] = PCWp_hsids[0][2][2];
	}







	return 0;
};

/* �܂Ƃ߂�ꂽ�f�[�^���č\�z���܂��B���̑���͑����i��ς�����ԂȂǂŕK�v�ɂȂ�܂� */
int Batch_Render::BatchReset( const PlayerChara *PcC, const Stage *StgC, const Enemy *EneC, const Camera *Cam){


	/*PC�������Ă��镐�탂�f���f�[�^�z��̏�����*/
	for(int i=0; i<2; i++){
		for(int j=0; j<3; j++){
			for(int k=0; k<4; k++){
				PCWp_hsids[i][j][k] = 0;
			}
		}
	};

	/*���[�h���Ă���PC���f���f�[�^�z��̏�����*/
	for(int i=0; i<2; i++){
		PCmodel_hsid[i] = 0;
	};

	/*�`�悪�K�v�ȕ��탂�f���f�[�^�z��̏�����*/
	for(int i=0; i<2; i++){
		for(int j=0; j<4; j++){
			Wp_hsids[i][j] = 0;
		}
	}

	/*�X�e�[�W���f���f�[�^�z��̏�����*/
	for(int i=0; i<3; i++){
		Stage_hsids[i] = 0;
	};

	/*PC�_�~�[���f���f�[�^�z��̏�����*/
	for(int i=0; i<2; i++){
		PCDummyModel_hsids[i] = 0;
	}

	/*�ǃ��f���z��̏�����*/
	for(int i=0; i<3; i++){
		Wall_hsids[i] = 0;
	};

	/*�����蔻�胂�f���z��̏�����*/
	for(int i=0; i<2; i++){
		Hitmodel_hsids[i] = 0;
	};

	/*����p���`�F�b�N���K�v�ȃ��f���f�[�^�z��̏�����*/
	for(int i=0; i<40; i++){
		ChkIn_hsids[i] = 0;
	};

	/*�`�悪�K�v�ȃ��f���f�[�^�z��̏�����*/
	for(int i=0; i<30; i++){
		Render_hsids[i] = 0;
	};

	/*�G���f���z��̏�����*/
	for(int i=0; i<15; i++){
		Enemy_hsids[i] = 0;
	}

	/*�X�v���C�g�̃f�[�^���i�[���邽�߂̔z��̏�����*/
	for(int i=0; i<15; i++){
		for(int j=0; j<5; j++){
			SpriteData[i][j] = 0.0f;
		}
	}

	/*�X�v���C�g�̎���ID���i�[����z��̏�����*/
	for(int i=0; i<15; i++){
		SpriteIDs[i] = 0;
	}

	/*�J�����̃_�~�[���f��ID��������*/
	CamDummyModel_hsid = 0;

	/**/
	///////���ׂĂ̏������̏I���B
	/////�����āA�X�e�[�W�N���X�ƃv���C���[�N���X����f�[�^��ǂݍ��݂܂��B
	/**/

	/*���C���E�F�|������f�[�^��ǂݍ��݂܂�*/
	PCWp_hsids[0][0][0] = PcC->Wpn.GetWeaponModelID( 0, 0); //���탂�f��ID
	PCWp_hsids[0][0][1] = PcC->Wpn.GetWeaponModelID( 0, 1); //�g�p�ςݒe�򃂃f��ID
	/*�T�u�E�F�|������f�[�^��ǂݍ��݂܂�*/
	PCWp_hsids[0][1][0] = PcC->Wpn.GetWeaponModelID( 1, 0); 
	PCWp_hsids[0][1][1] = PcC->Wpn.GetWeaponModelID( 0, 1);
	/*�O���l�[�h�n����f�[�^��ǂݍ��݂܂�*/
	PCWp_hsids[0][2][0] = PcC->Wpn.GetWeaponModelID( 2, 0);
	PCWp_hsids[0][2][1] = PcC->Wpn.GetWeaponModelID( 0, 1);


	/*PC�̃L�����N�^�[���f���f�[�^��ǂݍ��݂܂�*/
	PCmodel_hsid[0] = PcC->Get_BodyModel();

	/*�X�e�[�W���f���f�[�^��ǂݍ��݂܂�*/
	for(int i=0; i<3; i++){
		Stage_hsids[i] = StgC->Stage_hsid[i];
	};


	/**/
	///����p���`�F�b�N�����K�v�Ȃ���
	/**/
	
	/*�ǃ��f���f�[�^��ǂݍ��݂܂�*/
	for(int i=0; i<3; i++){
		Wall_hsids[i] = StgC->Stage_hsid[i];
	};
	/*�_�~�[���f���f�[�^��ǂݍ��݂܂�*/
	PCDummyModel_hsids[0] = PcC->Get_BodyModel();

	/*�J�����_�~�[���f����ǂݍ��݂܂�*/
	CamDummyModel_hsid = Cam->DummyModel;


	/**/
	/////�X�e�[�W�N���X�ƃv���C���[�N���X����f�[�^��ǂݍ��݂��I���܂����B
	///���ɁA�����_�����O���K�v�ȃ��f���f�[�^��Render_hsids�z��ɏ������݂܂�
	/**/

	Render_hsids[0] = PCmodel_hsid[0];//PC���f��
	Render_hsids[1] = Stage_hsids[0];////
	Render_hsids[2] = Stage_hsids[1];//�X�e�[�W�f�[�^
	Render_hsids[3] = Stage_hsids[2];////

	if( PcC->Get_Wp_equipment() == -1){//�����i���Ȃɂ��Ȃ��Ȃ�
			Render_hsids[4] = 0;
			Render_hsids[5] = 0;
	}
	if( PcC->Get_Wp_equipment() == 0){//�����i�����C���E�F�|���Ȃ�
			Render_hsids[4] = PCWp_hsids[0][0][0];
			Render_hsids[5] = PCWp_hsids[0][0][1];
	}
	if( PcC->Get_Wp_equipment() == 1){//�����i���T�u�E�F�|���Ȃ�
			Render_hsids[4] = PCWp_hsids[0][1][0];
			Render_hsids[5] = PCWp_hsids[0][1][1];
	}
	if( PcC->Get_Wp_equipment() == 2){//�����i���O���l�[�h�n�Ȃ�
			Render_hsids[4] = PCWp_hsids[0][2][0];
			Render_hsids[5] = PCWp_hsids[0][2][1];
	}

	for(int i=0; i < EneC->EnemyNum; i++){
			Render_hsids[ 7 + i ] = EneC->Ene[i]->Get_BodyModel();
			Render_hsids[ 7 + EneC->EnemyNum + i ] = EneC->Ene[i]->Get_Weapon()->GetWeaponModelID( 0, 0);
	}
	
	/*
	////�����_�����O���K�v�ȃ��f���f�[�^�̏������݂��I�����܂���
	//���ɁA����p���`�F�b�N���K�v�ȃf�[�^
	*/

	for(int i=0; i<22; i++){
			ChkIn_hsids[i] = Render_hsids[i];
	}

	ChkIn_hsids[23] = Wall_hsids[0];////
	ChkIn_hsids[24] = Wall_hsids[1];//�ǃf�[�^
	ChkIn_hsids[25] = Wall_hsids[2];////

	ChkIn_hsids[26] = PCDummyModel_hsids[0];//PC�_�~�[���f���f�[�^
	ChkIn_hsids[26] = CamDummyModel_hsid;//Cam�_�~�[���f���f�[�^




	return 0;
};
