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

			switch(ShoulderComMode){
					case -1:{// �J�����ړ���

							/* "ShoulderComMoveDeg"�ϐ�(�ڂ�����ccamrea.h)�ŁA�ǂ����90�x�X���邩���߂�*/
							if(ShoulderComCounter >= 3){//�J�E���^��3�ȏ�̎�
									ech = E3DRotateY( DummyModel, 90 * (float)ShoulderComMoveDeg * -1.0);
									if(ech != 0 ){//�G���[�`�F�b�N
												_ASSERT( 0 );//�G���[�_�C�A���O
									};
							}else{//�J�E���^��2�ȉ��̎�
									ech = E3DRotateY( DummyModel, 90 * (float)ShoulderComMoveDeg);
									if(ech != 0 ){//�G���[�`�F�b�N
												_ASSERT( 0 );//�G���[�_�C�A���O
									};
							}


							/* �O�i������*/
							switch(ShoulderComCounter){
								   case 4:{
											ech = E3DPosForward( DummyModel, 200);
											if(ech != 0 ){//�G���[�`�F�b�N
														_ASSERT( 0 );//�G���[�_�C�A���O
											};
											break;
								   }
								   
								   case 3:{
											ech = E3DPosForward( DummyModel, 65);
											if(ech != 0 ){//�G���[�`�F�b�N
														_ASSERT( 0 );//�G���[�_�C�A���O
											};
											break;
								   }
								   
								   case 2:{
											ech = E3DPosForward( DummyModel, 70);
											if(ech != 0 ){//�G���[�`�F�b�N
														_ASSERT( 0 );//�G���[�_�C�A���O
											};
										    break;
								   }
								  
								   case 1:{
											ech = E3DPosForward( DummyModel, 205);
											if(ech != 0 ){//�G���[�`�F�b�N
														_ASSERT( 0 );//�G���[�_�C�A���O
											};
										    break;
								   }
								   case 0:{
											ech = E3DPosForward( DummyModel, 270);
											if(ech != 0 ){//�G���[�`�F�b�N
														_ASSERT( 0 );//�G���[�_�C�A���O
											};

											//�ړ��I���A"ShoulderComMode���Œ肳����"
											switch(ShoulderComMoveDeg){
												case -1:{
														ShoulderComMode = 0;
														break;
												}
												case 1:{
														ShoulderComMode = 1;
														break;
												}
											}
											break;
								   }
									
							}

							/*�J�E���^�[������������*/
							ShoulderComCounter = ShoulderComCounter - 1;
							
					}
					break;
					case 0:{// !�E!�ɃL����������Ƃ�

							/*90�x�X����*/
							ech = E3DRotateY( DummyModel, -90);
							if(ech != 0 ){//�G���[�`�F�b�N
										_ASSERT( 0 );//�G���[�_�C�A���O
							};

							/*�O�i������*/
							ech = E3DPosForward( DummyModel, 270);
							if(ech != 0 ){//�G���[�`�F�b�N
										_ASSERT( 0 );//�G���[�_�C�A���O
							};

							// ���_�ύX���I�����ꂽ��
							if( keyin[5] == 1){
									ShoulderComMode = -1;// �J�����ړ��t���O�I����
									ShoulderComCounter = 4;
									ShoulderComMoveDeg = 1;// �J�������E�֍s�����܂�
							}

							break;
					}
					
					case 1:{// !��!�ɃL����������Ƃ�

							/*90�x�X����*/
							ech = E3DRotateY( DummyModel, 90);
							if(ech != 0 ){//�G���[�`�F�b�N
										_ASSERT( 0 );//�G���[�_�C�A���O
							};

							/*�O�i������*/
							ech = E3DPosForward( DummyModel, 270);
							if(ech != 0 ){//�G���[�`�F�b�N
										_ASSERT( 0 );//�G���[�_�C�A���O
							};

							// ���_�ύX���I�����ꂽ��
							if( keyin[5] == 1){
									ShoulderComMode = -1;// �J�����ړ��t���O�I����
									ShoulderComCounter = 4;
									ShoulderComMoveDeg = -1;// �J���������֍s�����܂�
							}
							break;
					}			
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
