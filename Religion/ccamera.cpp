/*�����ł́A�J�����Ɋւ��鑀����s���܂�
//��:�J�����A�j���A�ʒu�A�ݒ�Ȃ�
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "ccamera.h"//�J�����֌W�̃N���X�w�b�_�t�@�C��
#include "cstage.h"//�X�e�[�W�֌W�̃N���X�w�b�_�t�@�C��




/*�J�����N���X�̃R���X�g���N�^�A�_�~�[���f���̃��[�h�Ȃ�*/
Camera::Camera(){

	//�ϐ��̏�����
	int ech = 0;
	char loadname[256] = "";

	/*�����o�ϐ��̏�����*/
	ShoulderComMode = 0;
	ShoulderComCounter = 0;
	ShoulderComMoveDeg = 0;


	//�_�~�[���f���̎擾
	wsprintf( loadname, "%s\\data\\3d\\model\\other\\demo.sig", System::path);//�����f����sig���o�^
	ech = E3DSigLoad( loadname, 0, 0.01f, &DummyModel);//���f���̓ǂݍ��݁Asubmodid�փ��f��������B
	_ASSERT( ech != 1 );//�G���[�`�F�b�N



	return;
}
/*�J�����N���X�̃f�X�g���N�^�A�_�~�[���f���Ȃǂ�j�����܂�*/
Camera::~Camera(){

	//�ϐ��̏�����
	int ech = 0;

	//1�ڂ̃L�����N�^�[�_�~�[���f�����폜���܂�
	E3DDestroyHandlerSet( DummyModel);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N


	return;
}
/*���ł����_�ł̃J������ݒ肷��֐�*/
int Camera::CamShoulderGunBack( const int cha_hsid, const int Qid, const int bone, const float PC_Deg_XZ, const Stage *Stg){

		//�ϐ��̏�����
		int ech = 0;
		int HitResult = 0;//�ǂɓ������Ă��邩����`�F�b�N���܂�
		 ;//�L�[���z����쐬 
		D3DXVECTOR3 CameraUpVec( 0.0, 1.0, 0.0);//�J�����̏㕔�̃x�N�g��
		D3DXVECTOR3 CameraPos( 0.0, 0.0, 0.0);//�J�����̍��W
		D3DXVECTOR3 CameraTarget( 0.0, 0.0, 0.0);//�J�����̒��ӓ_
		D3DXVECTOR3 StomachPos( 0.0, 0.0, 0.0);//�u������v�̍��W
		D3DXVECTOR3 GarbageD3DVec( 0.0, 0.0, 0.0);//�v��Ȃ�XYZ�̃f�[�^�̈ꎟ����



		/*�L�����N�^�[���f���́u������v�́I���I�̍��W���擾���܂�*/
		ech = E3DGetCurrentBonePos( cha_hsid, bone, 1, &StomachPos);
		_ASSERT( ech != 1 );//�G���[�`�F�b�N

		/*�_�~�[���f���������́u��t�����v���W�ɒu���܂�*/
		ech = E3DSetPos( DummyModel, StomachPos);
		_ASSERT( ech != 1 );//�G���[�`�F�b�N

		/*�_�~�[���f���Ɂu������v�̃N�H�[�^�j�I����ݒ肵�܂�*/
		ech = E3DSetDirQ2( DummyModel, Qid);
		_ASSERT( ech != 1 );//�G���[�`�F�b�N

		/*�L�����N�^�[����]�����܂�*/
		ech = E3DRotateY( DummyModel, PC_Deg_XZ);
		_ASSERT( ech != 1 );//�G���[�`�F�b�N

		/*�O�i�����邳����*/
		ech = E3DPosForward( DummyModel, 13000);
		_ASSERT( ech != 1 );//�G���[�`�F�b�N

		/*�J�����̃^�[�Q�b�g�ɂȂ�A�_�~�[���f���̈ʒu���擾*/
		ech = E3DGetPos( DummyModel, &CameraTarget);
		_ASSERT( ech != 1 );//�G���[�`�F�b�N

		/*�J�����̒����_��ݒ肵�܂�*/
		ech = E3DSetCameraTarget( CameraTarget, CameraUpVec);
		_ASSERT( ech != 1 );//�G���[�`�F�b�N

		/*�_�~�[���f���������́u��t�����v���W�ɒu���܂�*/
		ech = E3DSetPos( DummyModel, StomachPos);
		_ASSERT( ech != 1 );//�G���[�`�F�b�N

		/*�_�~�[���f������ނ�����*/
		ech = E3DPosForward( DummyModel, -435);
		_ASSERT( ech != 1 );//�G���[�`�F�b�N

		/* /////////////////////////////////////// */
		/* �������_�ł̃J��������(���E)�̐ݒ���s�Ȃ��܂�
		/* ////////////////////////////////////// */

		if( ShoulderComMode == 0){// �J�����ύX�Ȃ�

				if( ShoulderComMoveDeg == 0){// �J�������L�����N�^�̉E���ɒu�� (���E) 

						/* �_�~�[���f�����E�ɌX���� */
						ech = E3DRotateY( DummyModel, 90);
						_ASSERT( ech != 1 );//�G���[�`�F�b�N

						/* �O�i������ */
						ech = E3DPosForward( DummyModel, 270);
						_ASSERT( ech != 1 );//�G���[�`�F�b�N

				}
				else if( ShoulderComMoveDeg == 1){// �J�������L�����N�^�̍����ɒu�� (�E��)

						/* �_�~�[���f�������ɌX���� */
						ech = E3DRotateY( DummyModel, -90);
						_ASSERT( ech != 1 );//�G���[�`�F�b�N

						/*�O�i������*/
						ech = E3DPosForward( DummyModel, 270);
						_ASSERT( ech != 1 );//�G���[�`�F�b�N

				}
			
				// ���_�ύX���I�����ꂽ��
				if( System::GetKeyData( System::KEY_E) == 1){
						ShoulderComMode = 1;// �J�����ύX���[�h���I���ɂ���
						ShoulderComCounter = 0;//�J�E���^�������l"4"�ɃZ�b�g
				}

		}
		else if( ShoulderComMode == 1){// �J�����ύX��

				D3DXVECTOR3 DamModPosRight( 0.0, 0.0, 0.0);// �L�����N�^�̉E�����W
				D3DXVECTOR3 DamModPosLeft( 0.0, 0.0, 0.0);// �L�����N�^�̍������W
				D3DXVECTOR3 ReferencePos( 0.0, 0.0, 0.0);// ���Ɍ�ނ������Ƃ̃J�����̍��W

				/* //////////////////////////////////////// */
				// �_�~�[���f�����L�����N�^�̉E���ɒu�����W���擾���� (���E) 
				/* //////////////////////////////////////// */

				ech = E3DGetPos( DummyModel, &ReferencePos);
				_ASSERT( ech != 1 );//�G���[�`�F�b�N
				ech = E3DRotateY( DummyModel, 90);
				_ASSERT( ech != 1 );//�G���[�`�F�b�N
				ech = E3DPosForward( DummyModel, 270);
				_ASSERT( ech != 1 );//�G���[�`�F�b�N
				ech = E3DGetPos( DummyModel, &DamModPosRight);
				_ASSERT( ech != 1 );//�G���[�`�F�b�N

				/* //////////////////////////////////////// */
				// �_�~�[���f�����L�����N�^�̍����ɒu�����W���擾���� (�E��) 
				/* //////////////////////////////////////// */

				ech = E3DRotateInit( DummyModel);
				_ASSERT( ech != 1 );//�G���[�`�F�b�N
				/*�_�~�[���f���Ɂu������v�̃N�H�[�^�j�I����ݒ肵�܂�*/
				ech = E3DSetDirQ2( DummyModel, Qid);
				_ASSERT( ech != 1 );//�G���[�`�F�b�N

				/*�L�����N�^�[����]�����܂�*/
				ech = E3DRotateY( DummyModel, PC_Deg_XZ);
				_ASSERT( ech != 1 );//�G���[�`�F�b�N

				ech = E3DSetPos( DummyModel, ReferencePos);
				_ASSERT( ech != 1 );//�G���[�`�F�b�N
				ech = E3DRotateY( DummyModel, -90);
				_ASSERT( ech != 1 );//�G���[�`�F�b�N
				ech = E3DPosForward( DummyModel, 270);
				_ASSERT( ech != 1 );//�G���[�`�F�b�N
				ech = E3DGetPos( DummyModel, &DamModPosLeft);
				_ASSERT( ech != 1 );//�G���[�`�F�b�N

				/* //////////////// */
				// 
				/* //////////////// */

				D3DXVECTOR3 CameraRLPosDif( 0.0, 0.0, 0.0);
				D3DXVECTOR3 CameraRLPosDifUnit( 0.0, 0.0, 0.0);
				D3DXVECTOR3 CameraLastPos( 0.0, 0.0, 0.0);

				if( ShoulderComMoveDeg == 0){// �E�����獶���֕ψʂ�����(�E���E)

					CameraRLPosDifUnit.x = (DamModPosLeft.x - DamModPosRight.x) / 4.0f;
					CameraRLPosDifUnit.y = (DamModPosLeft.y - DamModPosRight.y) / 4.0f;
					CameraRLPosDifUnit.z = (DamModPosLeft.z - DamModPosRight.z) / 4.0f;

					CameraLastPos.x =  ( CameraRLPosDifUnit.x * ShoulderComCounter) + DamModPosRight.x;
					CameraLastPos.y =  ( CameraRLPosDifUnit.y * ShoulderComCounter) + DamModPosRight.y;
					CameraLastPos.z =  ( CameraRLPosDifUnit.z * ShoulderComCounter) + DamModPosRight.z;


				}
				else if( ShoulderComMoveDeg == 1){// �E�����獶���֕ψʂ�����(�E���E)

					CameraRLPosDifUnit.x = (DamModPosRight.x - DamModPosLeft.x) / 4.0f;
					CameraRLPosDifUnit.y = (DamModPosRight.y - DamModPosLeft.y) / 4.0f;
					CameraRLPosDifUnit.z = (DamModPosRight.z - DamModPosLeft.z) / 4.0f;

					CameraLastPos.x =  ( CameraRLPosDifUnit.x * ShoulderComCounter) + DamModPosLeft.x;
					CameraLastPos.y =  ( CameraRLPosDifUnit.y * ShoulderComCounter) + DamModPosLeft.y;
					CameraLastPos.z =  ( CameraRLPosDifUnit.z * ShoulderComCounter) + DamModPosLeft.z;

				}

				ech = E3DSetPos( DummyModel, CameraLastPos);
				_ASSERT( ech != 1 );//�G���[�`�F�b�N

				if( ShoulderComCounter == 4){
						if( ShoulderComMoveDeg == 0){
								ShoulderComMoveDeg = 1;
						}
						else if( ShoulderComMoveDeg == 1){
								ShoulderComMoveDeg = 0;
						}
						ShoulderComMode = 0;
				}
				
				/*�J�E���^�[������������*/
				ShoulderComCounter = ShoulderComCounter + 1;

		}








		/*�J�����̃|�W�V�����ɂȂ邩������Ȃ��APC���f���̈ʒu���擾*/
		ech = E3DGetPos( DummyModel, &CameraPos);
		_ASSERT( ech != 1 );//�G���[�`�F�b�N

		/*�ǂƓ����蔻��`�F�b�N�A�ǂɖ��܂����肵�ĂȂ����`�F�b�N���܂�*/
		ech = E3DChkConfGroundVec( StomachPos, CameraPos, Stg->Stage_hsid[0], 0, 200, -1000, 
					&HitResult, &CameraPos, &GarbageD3DVec);
		_ASSERT( ech != 1 );//�G���[�`�F�b�N

		/*�J�������Z�b�g����*/
		ech = E3DSetCameraPos( CameraPos);
		_ASSERT( ech != 1 );//�G���[�`�F�b�N

		/*�_�~�[���f���̕��������������܂�*/
		ech = E3DRotateInit( DummyModel);
		_ASSERT( ech != 1 );//�G���[�`�F�b�N


	return 0;
}

/* �O�l�̎��_�ł̃J������ݒ肷��֐� */
/*int Camera::CamThreePersonGunBack( const int cha_hsid, const int Qid, const int bone, const float PC_Deg_XZ, const Stage *Stg){








	return 0;
}*/