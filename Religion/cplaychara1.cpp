/*�����ł́A�����N���X�̃L�����E�G�̊֐����`����N���X�R�[�h�t�@�C���ł��B
//���ɃQ�[�����J�n���鎞�ɕK�v�Ȋ֐�������������Ă��܂��B
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "clive.h"//�G��L�����̐錾�w�b�_�t�@�C��





/*�v���C���[�L�����N�^�[�̃R���X�g���N�^*/
/*�v���C���[�L�����N�^�[�̃f�R���X�g���N�^*/
PlayerChara::~PlayerChara(){

	int ech = 0;//�G���[�m�F�ϐ��̏�����

	//�L�����N�^�[���f�����폜���܂�
	E3DDestroyHandlerSet( Get_BodyModel());
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};

	//1�ڂ̃L�����N�^�[�_�~�[���f�����폜���܂�
	E3DDestroyHandlerSet( Get_DummyModel());
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};

	/**/
	//�N�H�[�^�j�I�����폜���܂�
	/**/	
	for(int i = 0; i<4; i++){
				ech = E3DDestroyQ( Get_Quaternion(i));
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};
	}


}