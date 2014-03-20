/*�����ł́A�J�����Ɋւ��鑀����s���܂�
//��:�J�����A�j���A�ʒu�A�ݒ�Ȃ�
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "ccamera.h"//�J�����֌W�̃N���X�w�b�_�t�@�C��

//�����Ŏg���O���[�o���ϐ���錾
extern System *sys;//�V�X�e���N���X���w���A�N���X�̃|�C���^

/*�J�����N���X�̃R���X�g���N�^�A�_�~�[���f���̃��[�h�Ȃ�*/
Camera::Camera(){

	//�ϐ��̏�����
	int ech = 0;
	char loadname[256] = "";


	//�_�~�[���f���̎擾
	wsprintf( loadname, "%s\\data\\3d\\model\\other\\demo.sig", sys->path);//�����f����sig���o�^
	ech = E3DSigLoad( loadname, 0, 0.01f, &DummyModel);//���f���̓ǂݍ��݁Asubmodid�փ��f��������B
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};



	return;
}
/*�J�����N���X�̃f�X�g���N�^�A�_�~�[���f���Ȃǂ�j�����܂�*/
Camera::~Camera(){

	//�ϐ��̏�����
	int ech = 0;

	//1�ڂ̃L�����N�^�[�_�~�[���f�����폜���܂�
	E3DDestroyHandlerSet( DummyModel);
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};


	return;
}
/*���ł����_�ł̃J������ݒ肷��֐�*/
int Camera::CamShoulderGunBack( int Qid, float PC_Deg_XZ, D3DXVECTOR3 StomachPos){

			//�ϐ��̏�����
			int ech = 0;
			D3DXVECTOR3 CameraUpVec( 0.0, 1.0, 0.0);//�J�����̏㕔�̃x�N�g��
			D3DXVECTOR3 CameraPos( 0.0, 0.0, 0.0);//�J�����̍��W
			D3DXVECTOR3 CameraTarget( 0.0, 0.0, 0.0);//�J�����̒��ӓ_


			/*�_�~�[���f���������́u��t�����v���W�ɒu���܂�*/
			ech = E3DSetPos( DummyModel, StomachPos);
			if(ech != 0 ){//�G���[�`�F�b�N
						_ASSERT( 0 );//�G���[�_�C�A���O
			};

			/*�_�~�[���f���Ɂu������v�̃N�H�[�^�j�I����ݒ肵�܂�*/
			ech = E3DSetDirQ2( DummyModel, Qid);
			if(ech != 0 ){//�G���[�`�F�b�N
						_ASSERT( 0 );//�G���[�_�C�A���O
			};

			/*�L�����N�^�[����]�����܂�*/
			ech = E3DRotateY( DummyModel, PC_Deg_XZ);
			if(ech != 0 ){//�G���[�`�F�b�N
						_ASSERT( 0 );//�G���[�_�C�A���O
			};

			/*�O�i�����邳����*/
			ech = E3DPosForward( DummyModel, 13000);
			if(ech != 0 ){//�G���[�`�F�b�N
						_ASSERT( 0 );//�G���[�_�C�A���O
			};

			/*�J�����̃^�[�Q�b�g�ɂȂ�A�_�~�[���f���̈ʒu���擾*/
			ech = E3DGetPos( DummyModel, &CameraTarget);
			if(ech != 0 ){//�G���[�`�F�b�N
						_ASSERT( 0 );//�G���[�_�C�A���O
			};

			/*�J�����̒����_��ݒ肵�܂�*/
			ech = E3DSetCameraTarget( CameraTarget, CameraUpVec);
			if(ech != 0 ){//�G���[�`�F�b�N
						_ASSERT( 0 );//�G���[�_�C�A���O
			};

			/*�_�~�[���f���������́u��t�����v���W�ɒu���܂�*/
			ech = E3DSetPos( DummyModel, StomachPos);
			if(ech != 0 ){//�G���[�`�F�b�N
						_ASSERT( 0 );//�G���[�_�C�A���O
			};

			/*�_�~�[���f������ނ�����*/
			ech = E3DPosForward( DummyModel, -435);
			if(ech != 0 ){//�G���[�`�F�b�N
						_ASSERT( 0 );//�G���[�_�C�A���O
			};

			/*90�x�X����*/
			ech = E3DRotateY( DummyModel, 90);
			if(ech != 0 ){//�G���[�`�F�b�N
						_ASSERT( 0 );//�G���[�_�C�A���O
			};

			/*�O�i�����邳����*/
			ech = E3DPosForward( DummyModel, 270);
			if(ech != 0 ){//�G���[�`�F�b�N
						_ASSERT( 0 );//�G���[�_�C�A���O
			};

			/*�J�����̃|�W�V�����ɂȂ�APC���f���̈ʒu���擾*/
			ech = E3DGetPos( DummyModel, &CameraPos);
			if(ech != 0 ){//�G���[�`�F�b�N
						_ASSERT( 0 );//�G���[�_�C�A���O
			};

			/*�J�������Z�b�g����*/
			ech = E3DSetCameraPos( CameraPos);
			if(ech != 0 ){//�G���[�`�F�b�N
						_ASSERT( 0 );//�G���[�_�C�A���O
			};

			/*�_�~�[���f���̕��������������܂�*/
			ech = E3DRotateInit( DummyModel);
			if(ech != 0 ){//�G���[�`�F�b�N
						_ASSERT( 0 );//�G���[�_�C�A���O
			};


	return 0;
}
