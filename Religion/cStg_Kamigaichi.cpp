/* �X�e�[�W�N���X�֐��n�̈ꕔ�ł���A����"cStg_Tronp.cpp"�R�[�h��
// �u�_���꒬�v�X�e�[�W�̃��[�h�E�������֌W�̂��Ƃ�������Ă��܂��B
/* /////////////////////////////////////////////////////////////////////////// */
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "cstage.h"//�X�e�[�W�֌W�̃N���X�w�b�_�t�@�C��


/* �_���꒬�̓ǂݍ��݂��s�Ȃ��܂�*/
int Stage::LoadStage_Kamigaichi( const int StageKind){

	/* �ϐ��̐錾 */
	int ech = 0;// �G���[�`�F�b�N�ϐ��̏�����
	int NaviPoint = 0;//�V�����ǉ������i�r�|�C���g��ID����
	char loadname[256] = "";// �ǂݍ��݃f�[�^�p�̕�����z��
	E3DCOLOR4UC FogColor = {255,255,255,255};// ���̐F���w�肵�܂�
	D3DXVECTOR3 NaviPointPos( 0.0, 0.0, 0.0);//�i�r�|�C���g���W��������\����


	/* //////////////////////////// */
	// �X�e�[�W�̃��[�h���s�Ȃ��܂�
	/* /////////////////////////// */

	if(StageKind == 0){
			wsprintf( loadname, "%s\\data\\3d\\map\\st_kamigaichi\\st_kamigaichi.sig", System::path);
			ech = E3DLoadSigFileAsGround(loadname, 40.0, 0, &Stage_hsid[0]);
			if(ech != 0 ){//�G���[�`�F�b�N
						_ASSERT( 0 );//�G���[�_�C�A���O
						return 1;//��肠��ŏI��
			};

	};


	/* //////////////////// */
	// ���̎w����s�Ȃ��܂�
	/* /////////////////// */

	E3DSetLinearFogParams(1, FogColor, 15000, 100000, -1);//�t�@�O�������܂��B
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
				return 1;//��肠��ŏI��
	}

	//������ݒ�
	Stage_GunTarget = 0;//�X�e�[�W�̏e�����"�ʏ�"�ɂ���
	Stage_GndMode = 0;//�L�����n�ʑ����"�ʏ�ɂ���"


	/* //////////////// */
	// �i�r���C���̍쐬 
	/* //////////////// */





	return 0;
}