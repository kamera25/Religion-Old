/*�����ł́A���f����X�v���C�g�̕`��ɕK�v�ȏ������W�A�܂��`��ŕK�v��
//�֐��������I�Ɏ��s���邱�Ƃ��ł���悤�ɂ��邽�߂̃N���X�R�[�h�t�@�C��
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "c_batch_preparat.h"//�`��ɕK�v�ȃN���X�̐錾�w�b�_�t�@�C��

/* �܂Ƃ߂�ꂽ�f�[�^��`�悵�܂��B */
int Batch_Render::BatchRender( const int SceneEndFlg){

	int ech = 0;// �G���[�`�F�b�N�p�̊m�F�ϐ�
	int i = 0;
	int Render_hsids[30];
	vector<Model>::iterator it;// �C�e���[�^

	for( it = Mdl.begin(); it != Mdl.end(); it++ ){
		
			/*�ϐ��̏�����*/
			if(( ((*it).ID != 0)) && ( (*it).ViewFlag == true)){
					Render_hsids[i] = (*it).ID;
					i++;
			}
	}

	switch(ShadowFlag){
			case 0:{// �����_�����O(�m�[�}��)
					ech = E3DRenderBatch( System::scid1, &Render_hsids[0], 30, 1, 0);
					_ASSERT( ech !=1 );//�G���[�_�C�A���O��\��

					break;
		    }
			case 1:{// �e�t�������_�����O
					ech = E3DRenderWithShadow( System::scid1, ShadowScid, ShadowTexture, &Render_hsids[0], 30, 0);
					_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

					break;
		    }
	}


	/*
	//�`��̏I������
	*/
	if( SceneEndFlg == 1){
			ech = E3DEndScene();
			_ASSERT( ech != 1 );//�G���[�`�F�b�N
	}

	return 0;
};

/* �܂Ƃ߂�ꂽ�X�v���C�g�������_�����O���邽�߂̊֐��ł� */
int Batch_Render::BatchSpriteRender( const int SceneEndFlg){

	/*�ϐ��̏�����*/
	int ech = 0;//�G���[�m�F�ϐ��̏�����
	vector<Sprite>::iterator it;// �C�e���[�^

	/*
	//�`�揈���̊J�n
	*/

	ech = E3DBeginScene( System::scid1, 1, -1);
	_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

	ech = E3DBeginSprite();
	_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��


	/*
	//�`����s���܂��A���[�v���ɕ`�悳��܂�
	*/

	for( it = Spt.begin(); it != Spt.end(); it++ ){
		
			/*�ϐ��̏�����*/
			if( (*it).ViewFlag == true){
					D3DXVECTOR3 ScreenPos( (*it).X, (*it).Y, (*it).Z);//�`��ʒu���w�肷��\����
					ech = E3DRenderSprite( (*it).ID, (*it).MagX, (*it).MagY, ScreenPos);
					_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��
			}
	}

	ech = E3DEndSprite();
	_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��


	/*
	//�`��̏I������
	*/
	if( SceneEndFlg == 1){
	
		ech = E3DEndScene();	
		_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��
	}


	return 0;
}

/* �o�b�N�o�b�t�@�̓��e���A�v���C�}���o�b�t�@�ɓ]�����܂� */
int Batch_Render::Batch_Present(){
	/* �ϐ��̏����� */
	int ech = 0;//�G���[�`�F�b�N�p�̊m�F�ϐ� 

	/* �o�b�N�o�b�t�@�̓��e���A�v���C�}���o�b�t�@�ɓ]�����܂� */ 
	ech = E3DPresent( System::scid1);
	_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��


	return 0;
}

/*����p���`�F�b�N���K�v�ȃf�[�^�i�`�悷��f�[�^���܂ށj���`�F�b�N���܂�*/
int Batch_Render::BatchChkInView(){

	int garbage = 0;//����Ȃ��ϐ����i�[���܂�
	int ech = 0;//�G���[�`�F�b�N�p�̊m�F�ϐ� 
	vector<Model>::iterator it;// �C�e���[�^


//	for(int i=0; i<40; i++){
		/*����p���̃`�F�b�N���s���܂�
		if(( ChkIn_hsids[i] != 0) && (ChkIn_hsids[i] != -1 )){//��̃��f���f�[�^�ȊO�Ȃ�
			ech = E3DChkInView( System::scid1, ChkIn_hsids[i], &garbage);
			_ASSERT( ech != 1 );//�G���[�`�F�b�N
		}
	};
	*/

	for( it = Mdl.begin(); it != Mdl.end(); it++){
		/*����p���̃`�F�b�N���s���܂�*/
		if( (*it).ID != 0 ){//��̃��f���f�[�^�ȊO�Ȃ�
			ech = E3DChkInView( System::scid1, (*it).ID, &garbage);
			_ASSERT( ech != 1 );//�G���[�`�F�b�N
		}
	};


	return 0;
};
