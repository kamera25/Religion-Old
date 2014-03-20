/*�����ł́A�X�e�[�W�̓ǂݍ��݁A������s���֐����`����N���X�R�[�h�t�@�C���ł��B
//
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "cstage.h"//�X�e�[�W�֌W�̃N���X�w�b�_�t�@�C��



/*�X�e�[�W�����[�h�E�ݒ肷��֐��ł�*/
int Stage::LoadStage(int StageID, int StageKind, int LightKind){

	/* �ϐ��̐錾 */
	int ech = 0;//�G���[�`�F�b�N�ϐ��̏�����
	int NaviPoint = 0;//�V�����ǉ������i�r�|�C���g��ID����
	float FogDist = 1000.0;//�w�i�̋������w�肷��ϐ��A�ʏ��1000(�߂�)
	char loadname[256] = "";//�ǂݍ��݃f�[�^�p�̕�����z��
	D3DXVECTOR3 NaviPointPos( 0.0, 0.0, 0.0);//�i�r�|�C���g���W��������\����


	//�X�e�[�W��̃f�[�^�����������܂��B
	for(int i = 0; i < 3; i++){
		Stage_hsid[i]= 0;//�X�e�[�W�z������������܂�
		Wall_hsid[i] = 0;//�ǔz������������܂�
	};



	/* ///////////////////////////// */
	// �ȉ����A�}�b�v���������܂�
	/* ///////////////////////////// */

	switch(StageID){
			case 0:{// �g�����v�[���Ȃ�
					LoadStage_Tronp( StageKind);
					break;
			}
			case 1:{// �C���^�[�l�b�g���r�[�Ȃ�
					LoadStage_IRoby( StageKind);
					break;
			}
			case 2:{// �X�тȂ�
					LoadStage_Forest( StageKind, &FogDist);
					break;
			}
			case 3:{// �_���꒬�Ȃ�
					LoadStage_Kamigaichi( StageKind);
					break;
			}
			case 4:{// �����M�I�����[���Ȃ�
					LoadStage_Mall( StageKind);
					break;
			}
			case 5:{// ��n�O�Ȃ�
					LoadStage_BaseFront( StageKind);
					break;
			}
			case 6:{// ���g���X�Ȃ�
					LoadStage_Retolis( StageKind, &FogDist);
					break;
			}
	}

	/* /////////////////////////// */
	//  �ȉ����A������p�ӂ��܂��B
	/* /////////////////////////// */

	//�����̑��������肵�܂��B
	SetStageLight( LightKind, FogDist);



	/* ////////////////////////// */
	//  �Ō�ɕϐ�������s���܂��B
	/* ////////////////////////// */

	Stage_ID = StageID;//�X�e�[�WID����
	Stage_Kind = StageKind;//�X�e�[�W�̎�ނ���



	return 0;
}
/* �X�e�[�W�ɃZ�b�g���郉�C�g�̐ݒ���s�Ȃ��܂� */
int Stage::SetStageLight( const int LightKind, const float FogDist){

	/* �ϐ��̐錾 */
	int ech = 0;//�G���[�`�F�b�N�ϐ��̏�����
	char loadname[256] = "";// �ǂݍ��݃f�[�^�p�̕�����z��
	const char LoadBGName[3][12] = { "hare.jpg", "sunset.jpg", "night.jpg"};// ���[�h����w�i�p�X�ϐ�
	const D3DXVECTOR3 ldir1( -1.0, -1.0, -1.0);
	const D3DXVECTOR3 ldir2( 1.0, 1.0, 1.0);
	E3DCOLOR4UC LightColor = { 0, 0, 0, 0};



	/* //////////////// */
	// �������쐬���܂�
	/* //////////////// */
	ech = E3DCreateLight( &Light1_ID);//����1���쐬���܂��B
	if( ech != 0){
			_ASSERT( 0 );
	};
	ech = E3DCreateLight( &Light2_ID);//����2���쐬���܂��B
	if( ech != 0){
			_ASSERT( 0 );
	};


	/* ///////////////// */
	// �����̐F�������܂�
	/* ///////////////// */
	switch(LightKind){
			case 0:{// ����Ȃ�
					LightColor.b = 255;
					LightColor.g = 255;
					LightColor.r = 255;
					break;
			}
			case 1:{// �[���Ȃ�
					LightColor.b = 50;
					LightColor.g = 50;
					LightColor.r = 255;
					break;
			}
			case 2:{// ��Ȃ�
					LightColor.b = 50;
					LightColor.g = 50;
					LightColor.r = 50;
					break;
			}
	}


	/* /////////////////// */
	// �����ɐF�����蓖�Ă܂�
	/* /////////////////// */

	//��ڂ̃��C�g��ݒ肷��B
	ech = E3DSetDirectionalLight( Light1_ID, ldir1, LightColor);
	if( ech != 0){
			_ASSERT( 0 );
	};

	//��ڂ̃��C�g��ݒ肷��B
	ech = E3DSetDirectionalLight( Light2_ID, ldir2, LightColor);
	if( ech != 0){
			_ASSERT( 0 );
	};


	/* /////////////// */
	// �w�i�����[�h���܂�
	/* /////////////// */
	wsprintf( loadname, "%s\\data\\3d\\map\\360\\%s", System::path, LoadBGName[LightKind]);
	ech = E3DCreateBG( System::scid1, loadname, "", 0, 0, 1, FogDist);
	if( ech != 0){
			_ASSERT( 0 );
	};



	//��ڂ̃o���v�}�b�v�̌������w�肵�܂�
	ech = E3DSetLightIdOfBumpMap( Light1_ID); 
	if( ech != 0){
				_ASSERT( 0 );
	};


	return 0;
}

/*Stage�N���X�̃f�R���X�g���N�^�A���[�h�������Ȃǂ��폜���܂��B*/
Stage::~Stage(){

	//�ϐ��̏��������s���܂�
	int ech = 0;//�G���[�`�F�b�N�ϐ��̏�����
	

	//�X�e�[�W�ƕǂ��폜���܂�
	for(int i = 0; i < 3; i++){
		if(Stage_hsid[i] != 0){//�X�e�[�W���폜���܂�
				ech = E3DDestroyHandlerSet( Stage_hsid[i]);
				if( ech != 0){
							_ASSERT( 0 );
				};
		}
		if(Wall_hsid[i] != 0){//�ǂ��폜���܂�
				ech = E3DDestroyHandlerSet( Wall_hsid[i]);
				if( ech != 0){
							_ASSERT( 0 );
				};
		}
	};




	/*�������폜�����*/

	//��ڂ̌����̍폜
	ech = E3DDestroyLight( Light1_ID);
	if( ech != 0){
				_ASSERT( 0 );
	};
	//��ڂ̌����̍폜
	ech = E3DDestroyLight( Light2_ID);
	if( ech != 0){
				_ASSERT( 0 );
	};


	//�w�i���폜���܂�
	ech = E3DDestroyBG( System::scid1);
	if( ech != 0){
				_ASSERT( 0 );
	};


}