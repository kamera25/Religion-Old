/*�����ł́A�����N���X�̃L�����E�G�̊֐����`����N���X�R�[�h�t�@�C���ł��B
//�ʏ퓮��Ɋ֌W���鎞�ɕK�v�Ȋ֐�������������Ă��܂��B
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_
#include "cstage.h"//�X�e�[�W�֌W�̃N���X�w�b�_�t�@�C��
#include "clive.h"//�G��L�����̃N���X�w�b�_�t�@�C��
#include "c_batch_preparat.h"//�`��ɕK�v�ȃN���X�̐錾�w�b�_�t�@�C��
#include "cmenu.h"//���j���[�N���X�Ɋւ���w�b�_�t�@�C��
#include <math.h>//���w�v�Z���g�����߂̃w�b�_�t�@�C��
#include "cweapon.h"//����Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��





/*�e�̌��ݎ����Ă�e�������߂̃��[�V�����E�V�X�e�����Ǌ�����֐�*/
int PlayerChara::GunPutOnHand(){

	/*�ϐ��̏�����*/
	int ech = 0;//�G���[�`�F�b�N�ϐ�
	int NowWpKind = Wpn.GetWeaponData( Wp_equipment, 0);//���̕���̎�ނ��擾���܂�
	int NowWpNo = Wpn.GetWeaponData( Wp_equipment, 1);//���̕���̃i���o�[���擾���܂�
	int NowGunhsid = Wpn.GetWeaponModelID( Wp_equipment, 0);//���̕���̃��f���f�[�^ID���擾���܂�
	D3DXVECTOR3 GunOnPos( 0.0, 0.0, 0.0);//�e��u�����W
	D3DXVECTOR3 GunHitPos( 0.0, 0.0, 0.0);//�����蔻�胂�f����u�����W
	D3DXVECTOR3 MoveVec( 0.0, 0.0, 0.0);
	D3DXVECTOR3 BaseVec( 0.0, 0.0, -1.0);

	/*�ȉ��A��ނɂ���ĐU�蕪�����s���܂�*/

	if(NowWpKind == 1){//����̎�ނ��A�n���h�K���ł����



				/*�e�̒u���{�[���̍��W�����߂܂�*/
				ech = E3DGetCurrentBonePos( cha_hsid[0], bone[0], 1, &GunOnPos);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				/*�e�����߂����W�ɂ����܂�*/
				ech = E3DSetPos( NowGunhsid, GunOnPos);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				/*�e�̌����ɂȂ�{�[���̃N�H�[�^�j�I�����擾*/
				ech = E3DGetCurrentBoneQ( cha_hsid[0], bone[1], 2, Qid[0]);//���̌������擾
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				/*�������������ւ̌v�Z���s���܂�*/
				ech = E3DLookAtQ( Qid[0], MoveVec, BaseVec, 0, 0);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				/*�e�̌������Z�b�g���܂�*/
				ech = E3DSetDirQ2( NowGunhsid, Qid[0]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};



	}
	if(NowWpKind == 4){//����̎�ނ��A�A�T���g���C�t���ł����

				/*�e�̒u���{�[���̍��W�����߂܂�*/
				ech = E3DGetCurrentBonePos( cha_hsid[0], bone[0], 1, &GunOnPos);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				/*�e�����߂����W�ɂ����܂�*/
				ech = E3DSetPos( NowGunhsid, GunOnPos);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				/*�e�̌����ɂȂ�{�[���̃N�H�[�^�j�I�����擾*/
				ech = E3DGetCurrentBoneQ( cha_hsid[0], bone[1], 2, Qid[0]);//���̌������擾
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				/*�������������ւ̌v�Z���s���܂�*/
				ech = E3DLookAtQ( Qid[0], MoveVec, BaseVec, 0, 0);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				/*�e�̌������Z�b�g���܂�*/
				ech = E3DSetDirQ2( NowGunhsid, Qid[0]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};



	}


		ech = E3DSetNewPoseML( NowGunhsid);
		if(ech != 0){//�G���[�`�F�b�N
					_ASSERT(0);//�G���[�_�C�A���O��\��
		};




	return 0;
}
/*�L�����𓮂����܂��A�O�㍶�E�ɓ����܂�*/
int PlayerChara::MoveChara(){

	/*�ϐ��̏�����*/
	int ech = 0;//�G���[�m�F�ϐ�
	int KeyMov = 0;//�L�[�������Ăǂ̕����ɓ������̕ϐ�
	int MovOn = 0;//�����Ă������̃t���O
	int keyin[20];//�L�[���z����쐬 
	float WantDeg = 0;//�������������̕ϐ�
	float FixedMoveSpeed = 0.0f;//���ꂼ��̏�Ԃ̌Œ葬�x
	D3DXVECTOR3 SubPos( 0.0, 0.0, 0.0);//�L�����N�^�[��u���ꏊ�̍��W
	D3DXVECTOR3 PCPos( 0.0, 0.0, 0.0);//�v���C���[�L�����N�^�[�̈ʒu�̍��W

	/*�_�b�V�����삪�I���ɂȂ��Ă��Ȃ����`�F�b�N*/


	/*�L�[�ɂ�镪��*/

	System::GetKeyData(keyin);//�L�[�����i�[

	if( keyin[0] == 1){//��
				KeyMov = KeyMov +1;
	}
	if( keyin[1] == 1){//��
				KeyMov = KeyMov +2;
	}
	if( keyin[2] == 1){//�E
				KeyMov = KeyMov +4;
	}
	if( keyin[3] == 1){//��
				KeyMov = KeyMov +8;
	}

	/*�L�[����擾��������ϊ�*/
	if(KeyMov == 1){//��
				WantDeg = -90.0f + PC_Deg_XZ;
				MovOn = 1;

				/*���[�V�������u�������v�ɂ���*/
				UnderMotion = 3;
	}
	if(KeyMov == 3){//����
				WantDeg = -45.0f + PC_Deg_XZ; 
				MovOn = 1;

				/*���[�V�������u���O�i�v�ɂ���*/
				UnderMotion = 4;
	}
	if(KeyMov == 2){//��
				WantDeg = PC_Deg_XZ; 
				MovOn = 1;

				/*���[�V�������u���s�v�ɂ���*/
				UnderMotion = 1;//�ʏ�

	}
	if(KeyMov == 6){//�E��
				WantDeg = 45.0f + PC_Deg_XZ; 
				MovOn = 1;

				/*���[�V�������u���O�i�v�ɂ���*/
				UnderMotion = 5;
	}
	if(KeyMov == 4){//�E
				WantDeg = 90.0f + PC_Deg_XZ; 
				MovOn = 1;

				/*���[�V�������u�E�����v�ɂ���*/
				UnderMotion = 2;
	}
	if(KeyMov == 12){//�E��
				WantDeg = 135.0f + PC_Deg_XZ; 
				MovOn = 1;

				/*���[�V�������u�E��i�v�ɂ���*/
				UnderMotion = 7;
	}
	if(KeyMov == 8){//��
				WantDeg = 180.0f + PC_Deg_XZ; 
				MovOn = 1;

				/*���[�V�������u��i�v�ɂ���*/
				UnderMotion = 8;
	}
	if(KeyMov == 9){//����
				WantDeg = -135.0f + PC_Deg_XZ; 
				MovOn = 1;

				/*���[�V�������u����i�v�ɂ���*/
				UnderMotion = 6;

	}

	//�L�[�����͂���Ă��Ă��A�L�b�N���Ȃ�
	if( MyState == 1) {
				MovOn = 0;//��Γ����Ȃ�
	}

	//�󒆂ŁA�_�b�V����ԂȂ�
	if( ( AirOnPC == 1) && ( MyState == 2)){
				WantDeg = PC_Deg_XZ;//�܂������i��
				MovOn = 1;//��Γ���
	}

	//����я�ԂȂ�
	if( MyState == 3) {
				WantDeg = -90.0f + PC_Deg_XZ;
				MovOn = 1;//��Γ���
	}

	//�E��я�ԂȂ�
	if( MyState == 4) {
				WantDeg = 90.0f + PC_Deg_XZ; 
				MovOn = 1;//��Γ���
	}


	/*�������������߂��*/
	if(MovOn == 1){

					if( MyState == 0){//�ʏ��ԂȂ�
							if( AirOnPC == 0){//�󒆂łȂ����
									if(Attitude == 0){//�p�����u�����Ă����ԁv�Ȃ�
											/*�X�s�[�h�𑝉�������*/
											MoveSpeed = MoveSpeed + 0.8f;

											//�X�s�[�h�ɐ�����������
											if( 25.0f <= MoveSpeed ){
														MoveSpeed = 25.0f;
											}

											//�Œ�X�s�[�h�̐ݒ�i�����j
											FixedMoveSpeed = 50.0f;
									}

									if(Attitude == 1){//�p�����u���Ⴊ�ݏ�ԁv�Ȃ�
											/*�X�s�[�h�𑝉�������*/
											MoveSpeed = MoveSpeed + 0.4f;

											//�X�s�[�h�ɐ�����������
											if( 20.0f <= MoveSpeed ){
														MoveSpeed = 20.0f;
											}

											//�Œ�X�s�[�h�̐ݒ�i���Ⴊ�݁j
											FixedMoveSpeed = 30.0f;
									}
							}
							if( AirOnPC == 1){//�󒆂ɂ���Ȃ�
									
									/*�X�s�[�h�𑝉�������*/
									MoveSpeed = MoveSpeed + 0.3f;

									//�X�s�[�h�ɐ�����������
									if( 10.0f <= MoveSpeed ){
												MoveSpeed = 10.0f;
									}

									//�Œ�X�s�[�h�̐ݒ�i���Ⴊ�݁j
									FixedMoveSpeed = 20.0f;
							}

					}
					if( MyState == 2){//�_�b�V����ԂȂ�

							if( AirOnPC == 0){//�n��ɂ���Ȃ�
									/*�X�s�[�h�𑝉�������*/
									MoveSpeed = MoveSpeed + 2.0f;

									//�X�s�[�h�ɐ�����������
									if( 40.0f <= MoveSpeed ){
												MoveSpeed = 40.0f;
									}

									//�Œ�X�s�[�h�̐ݒ�i���Ⴊ�݁j
									FixedMoveSpeed = 70.0f;
							}
							if( AirOnPC == 1){//�󒆂ɂ���Ȃ�
									/*�X�s�[�h�𑝉�������*/
									MoveSpeed = MoveSpeed + 2.0f;

									//�X�s�[�h�ɐ�����������
									if( 40.0f <= MoveSpeed ){
												MoveSpeed = 40.0f;
									}

									//�Œ�X�s�[�h�̐ݒ�i���Ⴊ�݁j
									FixedMoveSpeed = 70.0f;
							}
					}
					if( ( MyState == 3) || ( MyState == 4)){//����я�ԂȂ�
									/*�X�s�[�h���Œ�*/
									MoveSpeed = 0.0f;

									//�Œ�X�s�[�h�̐ݒ�i���Ⴊ�݁j
									FixedMoveSpeed = 90.0f;
					}



					/*�_�~�[���f���̍��W�ɐݒ�*/
					ech = E3DRotateInit ( DummyModel);
					if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
					};

					ech = E3DGetPos( cha_hsid[0], &PCPos);
					if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
					};

					ech = E3DSetPos( DummyModel, PCPos);
					if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
					};

					ech = E3DRotateY( DummyModel, WantDeg);
					if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
					};

					ech = E3DPosForward( DummyModel, (float)MoveSpeed + FixedMoveSpeed);
					if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
					};

					ech = E3DGetPos( DummyModel, &SubPos);
					if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
					};

					ech = E3DSetPos( cha_hsid[0], SubPos);
					if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
					};
	}
	else{//�����������Ȃ���΂Ȃ�Ȃ��Ȃ�
					if( AirOnPC == 0){//�󒆂ɂ���Ȃ�
								if( Attitude == 0) MoveSpeed = MoveSpeed - 0.8f;//�p�����u�ʏ��ԁv�Ȃ�
								if( Attitude == 1) MoveSpeed = MoveSpeed - 1.0f;//�p�����u���Ⴊ�ݏ�ԁv�Ȃ�
					}
					if( AirOnPC == 1) MoveSpeed = MoveSpeed - 0.6f;//�p�����u���Ⴊ�ݏ�ԁv�Ȃ�


					//�X�s�[�h�ɐ�����������
					if( MoveSpeed <= 0.0 ){
								MoveSpeed = 0.0f;
					}



					UnderMotion = 0;
	}




	return 0;
}
/*�L�����N�^�[���O���E���h�̏�ɒu�����߂̊֐�*/
int PlayerChara::MovePosOnGround( Stage *Stg){

	/*�ϐ��̏�����*/
	int ech = 0;//�G���[�`�F�b�N
	int GroundResult = 0;//�n�ʂ̓����蔻��̌���
	int MoveStopFlg = 0;//�󒆂ɕ�����ł���Ƃ��Ɉړ��ł��Ȃ��悤�ɂ��邽�߂̃t���O
	static int BeforeAirOnPC = 0;//�O��̃L�����N�^�[���󒆂ɂ��邩������܂�
	D3DXVECTOR3 ReflectVec( 0.0, 0.0, 0.0);//�n�ʂ̔��˃x�N�g���̍\����
	D3DXVECTOR3 GroundOnPos( 0.0, 0.0, 0.0);//���L������n�ʂɐ����ɂ��낵���ꍇ�̍��W
	D3DXVECTOR3 MyPos( 0.0, 0.0, 0.0);//�����̃L�����N�^�[���W


	/**/
	//�X�e�[�W�O���E���h���Ƃɂǂ̂悤�ȏ����ɂ����邩�U�蕪���܂�
	/**/

	if( Stg->Stage_GndMode == 0){

			/*�n�ʂ�PC�̓����蔻��̃`�F�b�N*/
			ech = E3DChkConfGround( cha_hsid[0], Stg->Stage_hsid[0], 1, 500, -1000, &GroundResult, &GroundOnPos, &ReflectVec);
			if(ech != 0 ){//�G���[�`�F�b�N
						_ASSERT( 0 );//�G���[�_�C�A���O
			};

			ech = E3DGetPos( cha_hsid[0], &MyPos);
			if(ech != 0 ){//�G���[�`�F�b�N
						_ASSERT( 0 );//�G���[�_�C�A���O
			};

			/*�����n�ʂ̍��������Ȃ藣��Ă��邩�A������я�ԂȂ�*/
			if( (400 < MyPos.y - GroundOnPos.y) || ( MyState == 3) || ( MyState == 4) ){

						/*�����x��ǉ�����*/
						Acceleration = Acceleration - 8.0;

						/*�O��͂Ƃ�łȂ������ꍇ*/
						if( BeforeAirOnPC == 0){
									/*�_�b�V�����̏ꍇ*/
									if( ( MyState == 2) && ( BeforeAirOnPC == 0)) {
												Acceleration = 100;//�󒆂ŃW�����v�������Ƃɂ���
									}
									/*������я�ԂȂ�*/
									if( (MyState == 3) || ( MyState == 4)) {
												Acceleration = 70;//�󒆂ŃW�����v�������Ƃɂ���
									}
						}

						/*�����x�ɐ�����������*/
						if(  Acceleration <= -700 ){
									Acceleration = -700;
						}

						/*�����̍��W��������*/
						MyPos.y = MyPos.y + float(Acceleration);

						/*�L�����N�^�[���󒆂ɒu��*/
						ech = E3DSetPos( cha_hsid[0], MyPos);
						if(ech != 0 ){//�G���[�`�F�b�N
									_ASSERT( 0 );//�G���[�_�C�A���O
						};

						/*�ړ��\�t���O���I�t�ɂ���*/
						MoveStopFlg = 1;

						/*���[�V�������u�W�����v���v�ɂ���*/
						UnderMotion = 9;

						/*�󒆃t���O���I���ɂ���*/
						AirOnPC = 1;

			}
			else{
						/*�L�����N�^�[��n�ʏ�ɒu��*/
						ech = E3DSetPos( cha_hsid[0], GroundOnPos);
						if(ech != 0 ){//�G���[�`�F�b�N
									_ASSERT( 0 );//�G���[�_�C�A���O
						};

						/*�����x��0�ɂ���*/
						Acceleration = 0.0;

						/*�ړ��\�t���O���I�t�ɂ���*/
						MoveStopFlg = 0;

						/*�󒆃t���O���I�t�ɂ���*/
						AirOnPC = 0;
			}
	}


	/*����̃L�����N�^�[���󒆂ɂ��邩������܂�(�����[�v���g�p)*/
	BeforeAirOnPC = AirOnPC;


	return 0;
}
