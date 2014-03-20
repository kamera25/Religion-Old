/*�����ł́A���f����X�v���C�g�̕`��ɕK�v�ȏ������W�A�܂��`��ŕK�v��
//�֐��������I�Ɏ��s���邱�Ƃ��ł���悤�ɂ��邽�߂̃N���X�R�[�h�t�@�C��
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "c_batch_preparat.h"//�`��ɕK�v�ȃN���X�̐錾�w�b�_�t�@�C��
#include "clive.h"//�G��L�����̐錾�w�b�_�t�@�C��
#include "cenemy.h"//�G�N���X�̐錾�w�b�_�t�@�C��
#include "cweapon.h"//����Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��
#include "cstage.h"//�X�e�[�W�֌W�̃N���X�w�b�_�t�@�C��
#include "ccamera.h"//�J�����֌W�̃N���X�w�b�_�t�@�C��






/*�R���X�g���N�^�A�X�e�[�W��v���C���[�N���X�����ɏ������W�A�\�����܂�*/
Batch_Preparat::Batch_Preparat( const PlayerChara *PcC, const Stage *StgC, const Enemy *EneC, 
								const Camera *Cam, Weapon *Wep){

	/*
	//////�܂��͂��߂ɂ��ׂĂ̕ϐ������������܂��B
	*/
	int ech = 0;//�G���[�`�F�b�N�p�̊m�F�ϐ� 
	E3DCOLOR4UC AlfaColor = { 100,255,255,255};//�J���[�\���̂̔����߂̃f�[�^
	char loadname[256] = "";//�ǂݍ��ސ�̃p�X�̕�����ϐ�

	
	/*�`��A����p�f�[�^�̍\�z���s���܂�*/
	BatchReset( PcC, StgC, EneC, Cam, Wep);


	/*
	//���ɃX�v���C�g�̃��[�h���s���܂��A�����Ƀf�[�^��������܂�
	*/

	/*�J�[�\���摜�̃��[�h���s�� �z���[0]��*/
	wsprintf( loadname, "%s\\data\\img\\carsol.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteIDs[0]);//�J�[�\���̃��[�h
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
	};

	/*�����������܂�*/
	ech = E3DSetSpriteARGB( SpriteIDs[0], AlfaColor);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
	};
	/*�f�[�^�̊i�[*/
	SpriteData[0][0] = 0.1f;//X�{���i1/10�j
	SpriteData[0][1] = 0.1f;//Y�{���i1/10�j
	SpriteData[0][4] = 0.0f;//Z���W���s�i��Ԏ�O�j


	/*�E�X�e�[�^�X�摜�̔w�i�̃��[�h���s�� �z���[1]��*/
	wsprintf( loadname, "%s\\data\\img\\parameter\\parameter3.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteIDs[1]);//�J�[�\���̃��[�h
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
	};
	/*�f�[�^�̊i�[*/
	SpriteData[1][0] = 1.0f;//X�{��
	SpriteData[1][1] = 1.0f;//Y�{��
	SpriteData[1][2] = 0.0f;//X���W
	SpriteData[1][3] = 390.0f;//Y���W
	SpriteData[1][4] = 0.0f;//Z���W���s�i��Ԏ�O�j


	/*�E�X�e�[�^�X�摜�̔w�i�̃��[�h���s�� �z���[2]��*/
	wsprintf( loadname, "%s\\data\\img\\parameter\\parameter4.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteIDs[2]);//�J�[�\���̃��[�h
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
	};
	/*�f�[�^�̊i�[*/
	SpriteData[2][0] = 1.0f;//X�{��
	SpriteData[2][1] = 1.0f;//Y�{��
	SpriteData[2][2] = 506.0f;//X���W
	SpriteData[2][3] = 390.0f;//Y���W
	SpriteData[2][4] = 0.0f;//Z���W���s�i��O�j


	/*��HP�̃o�[�̃��[�h���s�� �z���[3]��*/
	wsprintf( loadname, "%s\\data\\img\\parameter\\hpber.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteIDs[3]);//�J�[�\���̃��[�h
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
	};
	/*�f�[�^�̊i�[*/
	SpriteData[3][0] = 100.0f;//X�{��
	SpriteData[3][1] = 1.0f;//Y�{��
	SpriteData[3][2] = 24.0f;//X���W
	SpriteData[3][3] = 412.0f;//Y���W
	SpriteData[3][4] = 0.0f;//Z���W���s�i��O�j


	/*���X�^�~�i�̃o�[�̃��[�h���s�� �z���[4]��*/
	wsprintf( loadname, "%s\\data\\img\\parameter\\stnber.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteIDs[4]);//�J�[�\���̃��[�h
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
	};
	/*�f�[�^�̊i�[*/
	SpriteData[4][0] = 100.0f;//X�{��
	SpriteData[4][1] = 0.5f;//Y�{��
	SpriteData[4][2] = 24.0f;//X���W
	SpriteData[4][3] = 435.0f;//Y���W
	SpriteData[4][4] = 0.0f;//Z���W���s�i��O�j


	/*�E�e�򐔂̃o�[�̃��[�h���s�� �z���[5]��*/
	wsprintf( loadname, "%s\\data\\img\\parameter\\ammber.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteIDs[5]);//�J�[�\���̃��[�h
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
	};
	/*�f�[�^�̊i�[*/
	SpriteData[5][0] = 100.0f;//X�{��
	SpriteData[5][1] = 0.8125f;//Y�{��(13pix)
	SpriteData[5][2] = 530.0f;//X���W
	SpriteData[5][3] = 407.0f;//Y���W
	SpriteData[5][4] = 0.0f;//Z���W���s�i��O�j


	/*�E�}�K�W�����̃o�[�̃��[�h���s�� �z���[6]��*/
	wsprintf( loadname, "%s\\data\\img\\parameter\\magber.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteIDs[6]);//�J�[�\���̃��[�h
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
	};
	/*�f�[�^�̊i�[*/
	SpriteData[6][0] = 100.0f;//X�{��
	SpriteData[6][1] = 0.8125f;//Y�{��(13pix)
	SpriteData[6][2] = 530.0f;//X���W
	SpriteData[6][3] = 436.0f;//Y���W
	SpriteData[6][4] = 0.0f;//Z���W���s�i��O�j


	/*���X�e�[�^�X�摜�̃��[�h���s�� �z���[7]��*/
	wsprintf( loadname, "%s\\data\\img\\parameter\\parameter1.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteIDs[7]);//�J�[�\���̃��[�h
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
	};
	/*�f�[�^�̊i�[*/
	SpriteData[7][0] = 1.0f;//X�{��
	SpriteData[7][1] = 1.0f;//Y�{��
	SpriteData[7][2] = 0.0f;//X���W
	SpriteData[7][3] = 390.0f;//Y���W
	SpriteData[7][4] = 0.0f;//Z���W���s�i��Ԏ�O�j


	/*�E�X�e�[�^�X�摜�̃��[�h���s�� �z���[8]��*/
	wsprintf( loadname, "%s\\data\\img\\parameter\\parameter2.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteIDs[8]);//�J�[�\���̃��[�h
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
	};
	/*�f�[�^�̊i�[*/
	SpriteData[8][0] = 1.0f;//X�{��
	SpriteData[8][1] = 1.0f;//Y�{��
	SpriteData[8][2] = 506.0f;//X���W
	SpriteData[8][3] = 390.0f;//Y���W
	SpriteData[8][4] = 0.0f;//Z���W���s�i��Ԏ�O�j


	/*����Ɋւ���摜�̐ݒ�A�z���[9]��*/
	SpriteData[9][0] = 1.0f;//X�{��
	SpriteData[9][1] = 1.0f;//Y�{��
	SpriteData[9][2] = 506.0f;//X���W
	SpriteData[9][3] = 326.0f;//Y���W
	SpriteData[9][4] = 0.0f;//Z���W���s�i��Ԏ�O�j


};
/*�܂Ƃ߂�ꂽ�f�[�^��`�悵�܂��B*/
int Batch_Preparat::BatchRender( int SceneEndFlg){

	int ech = 0;//�G���[�`�F�b�N�p�̊m�F�ϐ�

	ech = E3DRenderBatch( System::scid1, &Render_hsids[30], 30, 0, 0);
	if(ech != 0){//�G���[�`�F�b�N
				_ASSERT(0);//�G���[�_�C�A���O��\��
	};


	/*
	//�`��̏I������
	*/
	if( SceneEndFlg == 1){

		ech = E3DEndScene();
		if(ech != 0){//�G���[�`�F�b�N
					_ASSERT(0);//�G���[�_�C�A���O��\��
		};
	}


	return 0;
};
/*�܂Ƃ߂�ꂽ�X�v���C�g�������_�����O���邽�߂̊֐��ł�*/
int Batch_Preparat::BatchSpriteRender( int SceneEndFlg){

	/*�ϐ��̏�����*/
	int ech = 0;//�G���[�m�F�ϐ��̏�����


	/*
	//�`�揈���̊J�n
	*/

	ech = E3DBeginScene( System::scid1, 1, -1);
	if(ech != 0){//�G���[�`�F�b�N
				_ASSERT(0);//�G���[�_�C�A���O��\��
	};

	ech = E3DBeginSprite();
	if(ech != 0){//�G���[�`�F�b�N
				_ASSERT(0);//�G���[�_�C�A���O��\��
	};

	/*
	//�`����s���܂��A���[�v���ɕ`�悳��܂�
	*/

	for(int i=0; i<15; i++ ){
		if( SpriteIDs[i] != 0){//�f�[�^�������Ƃ����
			/*�ϐ��̏�����*/
			D3DXVECTOR3 ScreenPos( SpriteData[i][2], SpriteData[i][3], SpriteData[i][4]);//�`��ʒu���w�肷��\����

			ech = E3DRenderSprite( SpriteIDs[i], SpriteData[i][0], SpriteData[i][1], ScreenPos);
			if(ech != 0){//�G���[�`�F�b�N
					_ASSERT(0);//�G���[�_�C�A���O��\��
			};
		}
	}

	ech = E3DEndSprite();
	if(ech != 0){//�G���[�`�F�b�N
				_ASSERT(0);//�G���[�_�C�A���O��\��
	};

	/*
	//�`��̏I������
	*/
	if( SceneEndFlg == 1){
	
		ech = E3DEndScene();
		if(ech != 0){//�G���[�`�F�b�N
					_ASSERT(0);//�G���[�_�C�A���O��\��
		};
	}


	return 0;
}
/*����p���`�F�b�N���K�v�ȃf�[�^�i�`�悷��f�[�^���܂ށj���`�F�b�N���܂�*/
int Batch_Preparat::BatchChkInView(){

	int garbage = 0;//����Ȃ��ϐ����i�[���܂�
	int ech = 0;//�G���[�`�F�b�N�p�̊m�F�ϐ� 


	for(int i=0; i<40; i++){
		/*����p���̃`�F�b�N���s���܂�*/
		if( ChkIn_hsids[i] != 0){//��̃��f���f�[�^�ȊO�Ȃ�
			ech = E3DChkInView( System::scid1, ChkIn_hsids[i], &garbage);
			if(ech != 0){//�G���[�`�F�b�N
						_ASSERT(0);//�G���[�_�C�A���O��\��
			}
		}
	};


	return 0;
};
/*��O�̍��W���܂Ƃ߂ĕۑ�����̂Ɏg���܂�*/
int Batch_Preparat::BatchBeforePos(){

	/*�ϐ��̏�����*/
	int ech = 0;//�G���[�`�F�b�N�p�̊m�F�ϐ� 


	for(int i=0; i<40; i++){
		/*����p���̃`�F�b�N���s���܂�*/
		if( ChkIn_hsids[i] != 0){//��̃��f���f�[�^�ȊO�Ȃ�
			ech = E3DSetBeforePos( ChkIn_hsids[i]);
			if(ech != 0){//�G���[�`�F�b�N
						_ASSERT(0);//�G���[�_�C�A���O��\��
			}
		}
	};


	return 0;
}
/*����̕ύX���������ہA�`�悷�ׂ������ύX���܂��B*/
int Batch_Preparat::BacthGunTrade( int Wp_equipment){


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
/*�܂Ƃ߂�ꂽ�f�[�^���č\�z���܂��B���̑���͑����i��ς�����ԂȂǂŕK�v�ɂȂ�܂�*/
int Batch_Preparat::BatchReset( const PlayerChara *PcC, const Stage *StgC, const Enemy *EneC, const Camera *Cam, Weapon *Wep){


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
	PCWp_hsids[0][0][0] = Wep->GetWeaponModelID( 0, 0); //���탂�f��ID
	PCWp_hsids[0][0][1] = Wep->GetWeaponModelID( 0, 1); //�g�p�ςݒe�򃂃f��ID
	/*�T�u�E�F�|������f�[�^��ǂݍ��݂܂�*/
	PCWp_hsids[0][1][0] = Wep->GetWeaponModelID( 1, 0); 
	PCWp_hsids[0][1][1] = Wep->GetWeaponModelID( 0, 1);
	/*�O���l�[�h�n����f�[�^��ǂݍ��݂܂�*/
	PCWp_hsids[0][2][0] = Wep->GetWeaponModelID( 2, 0);
	PCWp_hsids[0][2][1] = Wep->GetWeaponModelID( 0, 1);


	/*PC�̃L�����N�^�[���f���f�[�^��ǂݍ��݂܂�*/
	PCmodel_hsid[0] = PcC->cha_hsid[0];

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
	PCDummyModel_hsids[0] = PcC->DummyModel;

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

	if( PcC->Wp_equipment == -1){//�����i���Ȃɂ��Ȃ��Ȃ�
			Render_hsids[4] = 0;
			Render_hsids[5] = 0;
	}
	if( PcC->Wp_equipment == 0){//�����i�����C���E�F�|���Ȃ�
			Render_hsids[4] = PCWp_hsids[0][0][0];
			Render_hsids[5] = PCWp_hsids[0][0][1];
	}
	if( PcC->Wp_equipment == 1){//�����i���T�u�E�F�|���Ȃ�
			Render_hsids[4] = PCWp_hsids[0][1][0];
			Render_hsids[5] = PCWp_hsids[0][1][1];
	}
	if( PcC->Wp_equipment == 2){//�����i���O���l�[�h�n�Ȃ�
			Render_hsids[4] = PCWp_hsids[0][2][0];
			Render_hsids[5] = PCWp_hsids[0][2][1];
	}

	for(int i=0; i<15; i++){
			Render_hsids[ 7+i ] = EneC->Enemy_hsid[i];
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
/*�ŏ��Ƀ��[�h�����X�v���C�g�̔{����`��w��*/
int Batch_Preparat::BatchSpriteSet( const PlayerChara *PcC, Weapon *Wep){

	/*�X�v���C�g�̔{����ύX���܂�*/

	//HP�o�[�ɂ��Ă̔{�����
	SpriteData[3][0] = float( PcC->HP) / float( PcC->MaxHP) * 100.0f;

	//�X�^�~�i�o�[�ɂ��Ă̔{�����
	SpriteData[4][0] = float( PcC->Stamina) / 150.0f * 100.0f;

	if( PcC->Wp_equipment == -1){//����Ȃ��Ȃ�

				//�e�̒e��𖳕\����
				SpriteData[5][0] = 0.0f;

				//�e�̃}�K�W���𖳕\����
				SpriteData[6][0] = 0.0f;

				//�X�v���C�g��\�����Ȃ��悤��
				SpriteIDs[9] = 0;

	}
	else{//���킠��Ȃ�
				//�e�̒e��ɂ��Ă̔{���ϊ�
				SpriteData[5][0] = float( Wep->GetWeaponDataWhileGame( PcC->Wp_equipment, 0)) / float(Wep->GetWeaponData( PcC->Wp_equipment, 2)) * 100.0f;

				//�e�̃}�K�W���ɂ��Ă̔{���ϊ�
				SpriteData[6][0] = float( Wep->GetWeaponDataWhileGame( PcC->Wp_equipment, 1)) / float(Wep->GetWeaponData( PcC->Wp_equipment, 3)) * 100.0f;

				//�\�����ׂ��摜��SpriteIDs�ɑ������
				SpriteIDs[9] = Wep->GetSpriteData( PcC->Wp_equipment);
	}

	return 0;
}
/*������`�悷�邱�Ƃ�ݒ�������肵�܂�*/
int Batch_Preparat::BatchFont( int SceneEndFlg, const PlayerChara *PcC, Weapon *Wep){

	/*�ϐ��̏�����*/
	int ech = 0;//�G���[�`�F�b�N�p�̊m�F�ϐ�
	float Scale = 1.6f;//�����̑傫�����i�[����ϐ�
	char ParometaString[64] = "";//�\�������镶�������܂�
	D3DXVECTOR2 Pos( 0.0, 0.0);//���W��������\����
	E3DCOLOR4UC Color = { 255, 50, 50, 50};//��̍\����
	E3DCOLOR4UC Gray = { 255, 50, 50, 50};//�F�\���́A�O���[���w��
	E3DCOLOR4UC White = { 255, 230, 230, 230};//�F�\���́A�����w��
	E3DCOLOR4UC Red = { 255, 255, 100, 100};//�F�\���́A�Ԃ��w��
	E3DCOLOR4UC Bule = { 255, 100, 100, 250};//�F�\���́A���w��
	E3DCOLOR4UC Yellow = { 255, 255, 255, 100};//�F�\���́A�����w��

	/*�����̕`��*/
	//HP�����̕`��
	Pos.x = 28.0f;/**/Pos.y = 394.0f;
	ech = E3DDrawText( Pos, Scale, Gray, "F19");
	if(ech != 0){//�G���[�`�F�b�N
				_ASSERT(0);//�G���[�_�C�A���O��\��
	};


	if( PcC->Wp_equipment != -1){ //���킪�Ȃ��ȊO�Ȃ�

			/*���݂�Ammo�̐���\�����܂�*/
			if( Wep->GetWeaponDataWhileGame( PcC->Wp_equipment, 0) == 0){//�e�򂪂Ȃ��Ȃ�����
					Color = Red;// �ԐF�ɂ��܂�
			}
			else if( Wep->GetWeaponData( PcC->Wp_equipment, 2) < Wep->GetWeaponDataWhileGame( PcC->Wp_equipment, 0)){//�e�������Ă���Ȃ�Ȃ�
					Color = Bule;// �ɂ��܂�
			}
			else if( double(Wep->GetWeaponDataWhileGame( PcC->Wp_equipment, 0)) / double(Wep->GetWeaponData( PcC->Wp_equipment, 2)) < 0.3){//�e��3���ȉ��Ȃ�
					Color = Yellow;// ���ɂ��܂�
			}
			else{//�ʏ탂�[�h�Ȃ�
					Color = White;// ���ɂ��܂�
			}
			wsprintf( ParometaString, "%d", Wep->GetWeaponDataWhileGame( PcC->Wp_equipment, 0));
			Pos.x = 558.0f;/**/Pos.y = 394.0f;
			ech = E3DDrawText( Pos, 1.4f, Color, ParometaString);
			if(ech != 0){//�G���[�`�F�b�N
					_ASSERT(0);//�G���[�_�C�A���O��\��
			};

			/*Ammo�̐���\�����܂�*/
			wsprintf( ParometaString, "%d", Wep->GetWeaponData( PcC->Wp_equipment, 2));
			Pos.x = 588.0f;/**/Pos.y = 394.0f;
			ech = E3DDrawText( Pos, 1.4f, White, ParometaString);
			if(ech != 0){//�G���[�`�F�b�N
					_ASSERT(0);//�G���[�_�C�A���O��\��
			};

			/*���݂�Mag�̐���\�����܂�*/
			if( Wep->GetWeaponDataWhileGame( PcC->Wp_equipment, 1) == 0){//�}�K�W�����Ȃ��Ȃ�����
					Color = Red;// �ԐF�ɂ��܂�
			}
			else if( double(Wep->GetWeaponDataWhileGame( PcC->Wp_equipment, 1)) / double(Wep->GetWeaponData( PcC->Wp_equipment, 3)) < 0.3){//�e��3���ȉ��Ȃ�
					Color = Yellow;// ���ɂ��܂�
			}
			else{//�ʏ탂�[�h�Ȃ�
					Color = White;// ���ɂ��܂�
			}
			wsprintf( ParometaString, "%d", Wep->GetWeaponDataWhileGame( PcC->Wp_equipment, 1));
			Pos.x = 558.0f;/**/Pos.y = 424.0f;
			ech = E3DDrawText( Pos, 1.4f, Color, ParometaString);
			if(ech != 0){//�G���[�`�F�b�N
					_ASSERT(0);//�G���[�_�C�A���O��\��
			};

			/*Mag�̐���\�����܂�*/
			wsprintf( ParometaString, "%d", Wep->GetWeaponData( PcC->Wp_equipment, 3));
			Pos.x = 588.0f;/**/Pos.y = 424.0f;
			ech = E3DDrawText( Pos, 1.4f, White, ParometaString);
			if(ech != 0){//�G���[�`�F�b�N
					_ASSERT(0);//�G���[�_�C�A���O��\��
			};

	}


	/*
	//�`��̏I������
	*/
	if( SceneEndFlg == 1){

		ech = E3DEndScene();
		if(ech != 0){//�G���[�`�F�b�N
					_ASSERT(0);//�G���[�_�C�A���O��\��
		};
	}

	return 0;
}
/*�f�X�g���N�^�A�X�v���C�g���폜���܂�*/
Batch_Preparat::~Batch_Preparat(){

	/*�ϐ��̏�����*/
	int ech = 0;//�G���[�`�F�b�N�p�̊m�F�ϐ� 
		
	for(int i=0; i<9; i++){//���[�h�����X�v���C�g�̍폜
			ech = E3DDestroySprite( SpriteIDs[i]);
			if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
			};
	}


}
