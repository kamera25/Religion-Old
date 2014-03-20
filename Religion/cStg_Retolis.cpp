/* �X�e�[�W�N���X�֐��n�̈ꕔ�ł���A����"cStg_Tronp.cpp"�R�[�h��
// �u���g���X�v�X�e�[�W�̃��[�h�E�������֌W�̂��Ƃ�������Ă��܂��B
/* /////////////////////////////////////////////////////////////////////////// */
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "cstage.h"//�X�e�[�W�֌W�̃N���X�w�b�_�t�@�C��


/* �g�����v�[���̓ǂݍ��݂��s�Ȃ��܂�*/
int Stage::LoadStage_Retolis( const int StageKind, float *FogDist){

	/* �ϐ��̐錾 */
	int ech = 0;// �G���[�`�F�b�N�ϐ��̏�����
	int NaviPoint = 0;//�V�����ǉ������i�r�|�C���g��ID����
	char loadname[256] = "";// �ǂݍ��݃f�[�^�p�̕�����z��
	E3DCOLOR4UC FogColor = {255,0,0,0};// ���̐F���w�肵�܂�
	D3DXVECTOR3 NaviPointPos( 0.0, 0.0, 0.0);//�i�r�|�C���g���W��������\����


	/* //////////////////////////// */
	// �X�e�[�W�̃��[�h���s�Ȃ��܂�
	/* /////////////////////////// */

	if(StageKind == 0){
					wsprintf( loadname, "%s\\data\\3d\\map\\st_retolis\\st_retolis.sig", System::path);
					ech = E3DLoadSigFileAsGround(loadname, 55.0, 0, &Stage_hsid[0]);
					if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
							return 1;//��肠��ŏI��
					};
	};


	/* //////////////////// */
	// ���̎w����s�Ȃ��܂�
	/* /////////////////// */

	ech = E3DSetLinearFogParams(1, FogColor, 0, 20000, -1);//�t�@�O�������܂��B
	_ASSERT( ech != 1 );//�G���[�_�C�A���O


	*FogDist = 8000.0f;//�w�i�̂���Ō����ɂ�������B
	Stage_GunTarget = 0;//�X�e�[�W�̏e�����"�ʏ�"�ɂ���
	Stage_GndMode = 0;//�L�����n�ʑ����"�ʏ�ɂ���"



	/* //////////////// */
	// �i�r���C���̍쐬 
	/* //////////////// */
	int ANaviPoint = 0;
	int BNaviPoint = 0;


	Navi.NaviRailOnOffSwitch( 1);// �i�r���[�����g�p����
	Navi.AddNaviPointToStage( -1, 0, -106.49518f, 2105.9500f, 4596.2803f);// �i�r���[��0
	Navi.AddNaviPointToStage( -1, 0, -727.48090f, 2105.9500f, -1364.0236f);
	Navi.AddNaviPointToStage( -1, 0, -4238.1382f, 2105.9500f, -4166.2183f);
	ANaviPoint = Navi.AddNaviPointToStage( -1, 0, -9303.3115f, 2105.9500f, -6399.7251f);
	Navi.AddNaviPointToStage( -1, 0, -6660.0215f, 2105.9500f, 2587.4690f);


	BNaviPoint = Navi.AddNaviPointToStage( -1, 1, -9587.6592f, 2105.9500f, -12795.226f);// �i�r���[��1
	Navi.AddNaviPointToStage( -1, 1, -15797.104f, 2105.9500f, -12412.747f);
	Navi.AddNaviPointToStage( -1, 1, -16401.408f, 2105.9500f, -15693.905f);
	Navi.AddNaviPointToStage( -1, 1, -14735.134f, 2105.9500f, -19126.313f);
	Navi.AddNaviPointToStage( -1, 1, -11618.377f, 2105.9500f, -20582.639f);
	Navi.AddNaviPointToStage( -1, 1, 3346.5337f, 2105.9500f, -21234.010f);
	Navi.AddNaviPointToStage( -1, 1, 6677.0371f, 2105.9500f, -18553.188f);
	Navi.AddNaviPointToStage( -1, 1, 2218.3247f, 2105.9500f, -14321.980f);
	Navi.AddNaviPointToStage( -1, 1, 266.76770f, 2105.9500f, -13969.053f);
	Navi.AddNaviPointToStage( -1, 1, -141.62057f, 2105.9500f, -16286.854f);
	Navi.AddNaviPointToStage( -1, 1, -8746.4385f, 2105.9500f, -16191.914f);


	Navi.AddNaviPointToStage( -1, 2, -9394.7578f, 2105.9500f, -8282.7041f);// �i�r���[��2(�ڑ���)
	Navi.AddNaviPointToStage( -1, 2, -9451.8779f, 2105.9500f, -10827.891f);
	Navi.NRGivenTransfarFromAToB( 2, 0, ANaviPoint, 1, BNaviPoint);

	return 0;
}