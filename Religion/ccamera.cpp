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
int Camera::CamShoulderGunBack( int cha_hsid, int Qid, int bone, float PC_Deg_XZ, const Stage *Stg){

		//�ϐ��̏�����
		int ech = 0;
		int HitResult = 0;//�ǂɓ������Ă��邩����`�F�b�N���܂�
		int keyin[20];//�L�[���z����쐬 
		D3DXVECTOR3 CameraUpVec( 0.0, 1.0, 0.0);//�J�����̏㕔�̃x�N�g��
		D3DXVECTOR3 CameraPos( 0.0, 0.0, 0.0);//�J�����̍��W
		D3DXVECTOR3 CameraTarget( 0.0, 0.0, 0.0);//�J�����̒��ӓ_
		D3DXVECTOR3 StomachPos( 0.0, 0.0, 0.0);//�u������v�̍��W
		D3DXVECTOR3 GarbageD3DVec( 0.0, 0.0, 0.0);//�v��Ȃ�XYZ�̃f�[�^�̈ꎟ����


		/*�L�[���擾����*/
		System::GetKeyData(keyin);

		/*�L�����N�^�[���f���́u������v�́I���I�̍��W���擾���܂�*/
		ech = E3DGetCurrentBonePos( cha_hsid, bone, 1, &StomachPos);
		if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
		};

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

		/* /////////////////////////////////////// */
		/* �������_�ł̃J��������(���E)�̐ݒ���s�Ȃ��܂�
		/* ////////////////////////////////////// */

		if( ShoulderComMode == 0){// �J�����ύX�Ȃ�

				if( ShoulderComMoveDeg == 0){// �J�������L�����N�^�̉E���ɒu�� (���E) 

						/* �_�~�[���f�����E�ɌX���� */
						ech = E3DRotateY( DummyModel, 90);
						if(ech != 0 ){//�G���[�`�F�b�N
									_ASSERT( 0 );//�G���[�_�C�A���O
						};

						/* �O�i������ */
						ech = E3DPosForward( DummyModel, 270);
						if(ech != 0 ){//�G���[�`�F�b�N
									_ASSERT( 0 );//�G���[�_�C�A���O
						};

				}
				else if( ShoulderComMoveDeg == 1){// �J�������L�����N�^�̍����ɒu�� (�E��)

						/* �_�~�[���f�������ɌX���� */
						ech = E3DRotateY( DummyModel, -90);
						if(ech != 0 ){//�G���[�`�F�b�N
									_ASSERT( 0 );//�G���[�_�C�A���O
						};

						/*�O�i������*/
						ech = E3DPosForward( DummyModel, 270);
						if(ech != 0 ){//�G���[�`�F�b�N
									_ASSERT( 0 );//�G���[�_�C�A���O
						};

				}
			
				// ���_�ύX���I�����ꂽ��
				if( keyin[5] == 1){
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
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};
				ech = E3DRotateY( DummyModel, 90);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};
				ech = E3DPosForward( DummyModel, 270);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};
				ech = E3DGetPos( DummyModel, &DamModPosRight);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				/* //////////////////////////////////////// */
				// �_�~�[���f�����L�����N�^�̍����ɒu�����W���擾���� (�E��) 
				/* //////////////////////////////////////// */

				ech = E3DRotateInit( DummyModel);
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

				ech = E3DSetPos( DummyModel, ReferencePos);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};
				ech = E3DRotateY( DummyModel, -90);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};
				ech = E3DPosForward( DummyModel, 270);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};
				ech = E3DGetPos( DummyModel, &DamModPosLeft);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

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
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

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
		if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
		};

		/*�ǂƓ����蔻��`�F�b�N�A�ǂɖ��܂����肵�ĂȂ����`�F�b�N���܂�*/
		ech = E3DChkConfGroundVec( StomachPos, CameraPos, Stg->Stage_hsid[0], 0, 200, -1000, 
					&HitResult, &CameraPos, &GarbageD3DVec);
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
