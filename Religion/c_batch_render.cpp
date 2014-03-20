/*�����ł́A���f����X�v���C�g�̕`��ɕK�v�ȏ������W�A�܂��`��ŕK�v��
//�֐��������I�Ɏ��s���邱�Ƃ��ł���悤�ɂ��邽�߂̃N���X�R�[�h�t�@�C��
*/

#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "c_batch_preparat.h"//�`��ɕK�v�ȃN���X�̐錾�w�b�_�t�@�C��


/*�R���X�g���N�^�A�X�e�[�W��v���C���[�N���X�����ɏ������W�A�\�����܂�*/
Batch_Render::Batch_Render( const PlayerChara *PcC, const Stage *StgC, const Enemy *EneC, 
								const Camera *Cam)
{

	/* //////////////////////////////////// */
	// �܂��͂��߂ɂ��ׂĂ̕ϐ������������܂��B
	/* //////////////////////////////////// */
	int ech = 0;//�G���[�`�F�b�N�p�̊m�F�ϐ� 
	const E3DCOLOR4UC AlfaColor = { 100,255,255,255};//�J���[�\���̂̔����߂̃f�[�^
	char loadname[256] = "";//�ǂݍ��ސ�̃p�X�̕�����ϐ�
	
	BumpMapFlag = 0;
	ShadowFlag = 0;

	/*�`��A����p�f�[�^�̍\�z���s���܂�*/
	BatchReset( PcC, StgC, EneC, Cam);


	/* /////////////////////////////////////////////////////// */
	//���ɃX�v���C�g�̃��[�h���s���܂��A�����Ƀf�[�^��������܂�
	/* /////////////////////////////////////////////////////// */

	/*�J�[�\���摜�̃��[�h���s�� �z���[0]��*/
	wsprintf( loadname, "%s\\data\\img\\carsol.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteIDs[0]);//�J�[�\���̃��[�h
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/*�����������܂�*/
	ech = E3DSetSpriteARGB( SpriteIDs[0], AlfaColor);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N
	/*�f�[�^�̊i�[*/
	SpriteData[0][0] = 0.1f;//X�{���i1/10�j
	SpriteData[0][1] = 0.1f;//Y�{���i1/10�j
	SpriteData[0][4] = 0.0f;//Z���W���s�i��Ԏ�O�j


	/*�E�X�e�[�^�X�摜�̔w�i�̃��[�h���s�� �z���[1]��*/
	wsprintf( loadname, "%s\\data\\img\\parameter\\parameter3.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteIDs[1]);//�J�[�\���̃��[�h
	_ASSERT( ech != 1 );//�G���[�`�F�b�N
	/*�f�[�^�̊i�[*/
	SpriteData[1][0] = 1.0f;//X�{��
	SpriteData[1][1] = 1.0f;//Y�{��
	SpriteData[1][2] = 0.0f;//X���W
	SpriteData[1][3] = 390.0f;//Y���W
	SpriteData[1][4] = 0.0f;//Z���W���s�i��Ԏ�O�j


	/*�E�X�e�[�^�X�摜�̔w�i�̃��[�h���s�� �z���[2]��*/
	wsprintf( loadname, "%s\\data\\img\\parameter\\parameter4.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteIDs[2]);//�J�[�\���̃��[�h
	_ASSERT( ech != 1 );//�G���[�`�F�b�N
	/*�f�[�^�̊i�[*/
	SpriteData[2][0] = 1.0f;//X�{��
	SpriteData[2][1] = 1.0f;//Y�{��
	SpriteData[2][2] = 506.0f;//X���W
	SpriteData[2][3] = 390.0f;//Y���W
	SpriteData[2][4] = 0.0f;//Z���W���s�i��O�j


	/*��HP�̃o�[�̃��[�h���s�� �z���[3]��*/
	wsprintf( loadname, "%s\\data\\img\\parameter\\hpber.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteIDs[3]);//�J�[�\���̃��[�h
	_ASSERT( ech != 1 );//�G���[�`�F�b�N
	/*�f�[�^�̊i�[*/
	SpriteData[3][0] = 100.0f;//X�{��
	SpriteData[3][1] = 1.0f;//Y�{��
	SpriteData[3][2] = 24.0f;//X���W
	SpriteData[3][3] = 412.0f;//Y���W
	SpriteData[3][4] = 0.0f;//Z���W���s�i��O�j


	/*���X�^�~�i�̃o�[�̃��[�h���s�� �z���[4]��*/
	wsprintf( loadname, "%s\\data\\img\\parameter\\stnber.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteIDs[4]);//�J�[�\���̃��[�h
	_ASSERT( ech != 1 );//�G���[�`�F�b�N
	/*�f�[�^�̊i�[*/
	SpriteData[4][0] = 100.0f;//X�{��
	SpriteData[4][1] = 0.5f;//Y�{��
	SpriteData[4][2] = 24.0f;//X���W
	SpriteData[4][3] = 435.0f;//Y���W
	SpriteData[4][4] = 0.0f;//Z���W���s�i��O�j


	/*�E�e�򐔂̃o�[�̃��[�h���s�� �z���[5]��*/
	wsprintf( loadname, "%s\\data\\img\\parameter\\ammber.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteIDs[5]);//�J�[�\���̃��[�h
	_ASSERT( ech != 1 );//�G���[�`�F�b�N
	/*�f�[�^�̊i�[*/
	SpriteData[5][0] = 100.0f;//X�{��
	SpriteData[5][1] = 0.8125f;//Y�{��(13pix)
	SpriteData[5][2] = 530.0f;//X���W
	SpriteData[5][3] = 407.0f;//Y���W
	SpriteData[5][4] = 0.0f;//Z���W���s�i��O�j


	/*�E�}�K�W�����̃o�[�̃��[�h���s�� �z���[6]��*/
	wsprintf( loadname, "%s\\data\\img\\parameter\\magber.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteIDs[6]);//�J�[�\���̃��[�h
	_ASSERT( ech != 1 );//�G���[�`�F�b�N
	/*�f�[�^�̊i�[*/
	SpriteData[6][0] = 100.0f;//X�{��
	SpriteData[6][1] = 0.8125f;//Y�{��(13pix)
	SpriteData[6][2] = 530.0f;//X���W
	SpriteData[6][3] = 436.0f;//Y���W
	SpriteData[6][4] = 0.0f;//Z���W���s�i��O�j


	/*���X�e�[�^�X�摜�̃��[�h���s�� �z���[7]��*/
	wsprintf( loadname, "%s\\data\\img\\parameter\\parameter1.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteIDs[7]);//�J�[�\���̃��[�h
	_ASSERT( ech != 1 );//�G���[�`�F�b�N
	/*�f�[�^�̊i�[*/
	SpriteData[7][0] = 1.0f;//X�{��
	SpriteData[7][1] = 1.0f;//Y�{��
	SpriteData[7][2] = 0.0f;//X���W
	SpriteData[7][3] = 390.0f;//Y���W
	SpriteData[7][4] = 0.0f;//Z���W���s�i��Ԏ�O�j


	/*�E�X�e�[�^�X�摜�̃��[�h���s�� �z���[8]��*/
	wsprintf( loadname, "%s\\data\\img\\parameter\\parameter2.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteIDs[8]);//�J�[�\���̃��[�h
	_ASSERT( ech != 1 );//�G���[�`�F�b�N
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

/* �f�X�g���N�^�A�X�v���C�g���폜���܂� */
Batch_Render::~Batch_Render(){

	/*�ϐ��̏�����*/
	int ech = 0;//�G���[�`�F�b�N�p�̊m�F�ϐ� 
		
	for(int i=0; i<9; i++){//���[�h�����X�v���C�g�̍폜
			ech = E3DDestroySprite( SpriteIDs[i]);
			_ASSERT( ech != 1 );//�G���[�`�F�b�N
	}

	if( ShadowFlag == 1){// �e�p�����_�[�e�N�X�`������������Ă���Ȃ�
			ech = E3DDestroyRenderTargetTexture( ShadowScid, ShadowTexture);
			_ASSERT( ech != 1 );//�G���[�`�F�b�N
	}

}