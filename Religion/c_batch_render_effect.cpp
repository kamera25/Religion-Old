/*�����ł́A���f����X�v���C�g�̕`��ɕK�v�ȏ������W�A�܂��`��ŕK�v��
//�֐��������I�Ɏ��s���邱�Ƃ��ł���悤�ɂ��邽�߂̃N���X�R�[�h�t�@�C��
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "c_batch_preparat.h"//�`��ɕK�v�ȃN���X�̐錾�w�b�_�t�@�C��


/* �o���v�}�b�v��L��/�����ɂ��܂� */
int Batch_Render::BatchEnableBumpMap( const int BumpFlag){

	/*�ϐ��̏�����*/
	int ech = 0;//�G���[�`�F�b�N�p�̊m�F�ϐ�

	ech = E3DEnableBumpMap( BumpFlag );
	if( ech != 0){
			_ASSERT( 0 );
	};

	BumpMapFlag = BumpFlag;

	return 0;
}

/* �e���쐬���邽�߂Ɋ֌W���鏈�����s�Ȃ��܂� */
int Batch_Render::BatchCreateShadow(){

	/* �ϐ��̏����� */
	int ech = 0;// �G���[�`�F�b�N�ϐ�
	int ShadowCRTFlug = 0;// �e��`�悷��e�N�X�`�������ꂽ���ǂ���
	const D3DXVECTOR3 ldir1( -1.0, -1.0, -1.0);
	const SIZE TextureSize = { 1028, 1028};

	// Z�o�b�t�@�̃o�C�A�X��ݒ�
	ech = E3DSetShadowBias( 0.005f);
	if( ech != 0){
			_ASSERT( 0 );
	};

	// �e�̕������w�肵�܂�
	ech = E3DSetShadowMapLightDir( ldir1);
	if( ech != 0){
			_ASSERT( 0 );
	};


	// �e�N�X�`���̍쐬
	ech = E3DCreateRenderTargetTexture( TextureSize, D3DFMT_A8R8G8B8, &ShadowScid, &ShadowTexture, &ShadowCRTFlug);
	if( ech != 0){
			_ASSERT( 0 );
	};

	if( ShadowCRTFlug == 1){// �쐬�ɐ���������
			ShadowFlag = 1;
	}



	return 0;
}