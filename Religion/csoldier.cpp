/* �����ł́A���m�N���X�֌W�̊֐����`����N���X�R�[�h�t�@�C���ł��B
// ���m�̊�{�I�ȓ���Ɋ֌W���鎞�ɕK�v�Ȋ֐�������������Ă��܂��B
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "cstage.h"//�X�e�[�W�֌W�̃N���X�w�b�_�t�@�C��
#include "csoldier.h"// ���m�N���X�̐錾�w�b�_�t�@�C��


/* ���m�n���j�b�g���O���E���h�̏�ɒu�����߂̊֐� */
int Soldier::MovePosOnGround( Stage *Stg){

	/*�ϐ��̏�����*/
	int ech = 0;//�G���[�`�F�b�N
	int GroundResult = 0;//�n�ʂ̓����蔻��̌���
	int MoveStopFlg = 0;//�󒆂ɕ�����ł���Ƃ��Ɉړ��ł��Ȃ��悤�ɂ��邽�߂̃t���O
	D3DXVECTOR3 ReflectVec( 0.0, 0.0, 0.0);//�n�ʂ̔��˃x�N�g���̍\����
	D3DXVECTOR3 GroundOnPos( 0.0, 0.0, 0.0);//���L������n�ʂɐ����ɂ��낵���ꍇ�̍��W
	D3DXVECTOR3 MyPos( 0.0, 0.0, 0.0);//�����̃L�����N�^�[���W


	/**/
	//�X�e�[�W�O���E���h���Ƃɂǂ̂悤�ȏ����ɂ����邩�U�蕪���܂�
	/**/

	if( Stg->Stage_GndMode == 0){

			/*�n�ʂ�PC�̓����蔻��̃`�F�b�N*/
			ech = E3DChkConfGround( Get_BodyModel(), Stg->Stage_hsid[0], 1, 500, -1000, &GroundResult, &GroundOnPos, &ReflectVec);
			_ASSERT( ech != 1 );//�G���[�`�F�b�N

			ech = E3DGetPos( Get_BodyModel(), &MyPos);
			_ASSERT( ech != 1 );//�G���[�`�F�b�N

			/*�����n�ʂ̍��������Ȃ藣��Ă��邩�A������я�ԂȂ�*/
			if( (400 < MyPos.y - GroundOnPos.y) || ( Get_MyState() == 3) || ( Get_MyState() == 4) ){

						/*�����x��ǉ�����*/
						Set_Acceleration( Get_Acceleration() - 8.0);

						/*�O��͂Ƃ�łȂ������ꍇ*/
						if( BeforeAirOnPC == 0){
									/*�_�b�V�����̏ꍇ*/
									if( ( Get_MyState() == 2) && ( BeforeAirOnPC == 0)) {
												Set_Acceleration(100);//�󒆂ŃW�����v�������Ƃɂ���
									}
									/*������я�ԂȂ�*/
									if( (Get_MyState() == 3) || ( Get_MyState() == 4)) {
												Set_Acceleration(70);//�󒆂ŃW�����v�������Ƃɂ���
									}
						}

						/*�����x�ɐ�����������*/
						if(  Get_Acceleration() <= -700 ){
									Set_Acceleration(-700);
						}

						/*�����̍��W��������*/
						MyPos.y = MyPos.y + float(Get_Acceleration());

						/*�L�����N�^�[���󒆂ɒu��*/
						ech = E3DSetPos( Get_BodyModel(), MyPos);
						_ASSERT( ech != 1 );//�G���[�`�F�b�N

						/*�ړ��\�t���O���I�t�ɂ���*/
						MoveStopFlg = 1;

						/*���[�V�������u�W�����v���v�ɂ���*/
						Set_UnderMotion(9);

						/*�󒆃t���O���I���ɂ���*/
						Set_AirOnPC(1);

			}
			else{
						/*�L�����N�^�[��n�ʏ�ɒu��*/
						ech = E3DSetPos( Get_BodyModel(), GroundOnPos);
						_ASSERT( ech != 1 );//�G���[�`�F�b�N

						/*�����x��0�ɂ���*/
						Set_Acceleration( 0.0);

						/*�ړ��\�t���O���I�t�ɂ���*/
						MoveStopFlg = 0;

						/*�󒆃t���O���I�t�ɂ���*/
						Set_AirOnPC(0);
			}
	}


	/*����̃L�����N�^�[���󒆂ɂ��邩������܂�(�����[�v���g�p)*/
	BeforeAirOnPC = Get_AirOnPC();


	return 0;
}
/*�e�̌��ݎ����Ă�e�������߂̃��[�V�����E�V�X�e�����Ǌ�����֐�*/
int Soldier::GunPutOnHand(){

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

	if(NowWpKind == 0){//����̎�ނ��A�n���h�K���ł����



				/*�e�̒u���{�[���̍��W�����߂܂�*/
				ech = E3DGetCurrentBonePos( Get_BodyModel(), Get_Bone_ID(0), 1, &GunOnPos);
				_ASSERT( ech != 1 );//�G���[�`�F�b�N

				/*�e�����߂����W�ɂ����܂�*/
				ech = E3DSetPos( NowGunhsid, GunOnPos);
				_ASSERT( ech != 1 );//�G���[�`�F�b�N

				/*�e�̌����ɂȂ�{�[���̃N�H�[�^�j�I�����擾*/
				ech = E3DGetCurrentBoneQ( Get_BodyModel(), Get_Bone_ID(1), 2, Get_Quaternion(0));//���̌������擾
				_ASSERT( ech != 1 );//�G���[�`�F�b�N

				/*�������������ւ̌v�Z���s���܂�*/
				ech = E3DLookAtQ( Get_Quaternion(0), MoveVec, BaseVec, 0, 0);
				_ASSERT( ech != 1 );//�G���[�`�F�b�N

				/*�e�̌������Z�b�g���܂�*/
				ech = E3DSetDirQ2( NowGunhsid, Get_Quaternion(0));
				_ASSERT( ech != 1 );//�G���[�`�F�b�N



	}
	if(NowWpKind == 2){//����̎�ނ��A�V���b�g�K���ł����

				/*�e�̒u���{�[���̍��W�����߂܂�*/
				ech = E3DGetCurrentBonePos( Get_BodyModel(), Get_Bone_ID(0), 1, &GunOnPos);
				_ASSERT( ech != 1 );//�G���[�`�F�b�N

				/*�e�����߂����W�ɂ����܂�*/
				ech = E3DSetPos( NowGunhsid, GunOnPos);
				_ASSERT( ech != 1 );//�G���[�`�F�b�N

				/*�e�̌����ɂȂ�{�[���̃N�H�[�^�j�I�����擾*/
				ech = E3DGetCurrentBoneQ( Get_BodyModel(), Get_Bone_ID(1), 2, Get_Quaternion(0));//���̌������擾
				_ASSERT( ech != 1 );//�G���[�`�F�b�N

				/*�������������ւ̌v�Z���s���܂�*/
				ech = E3DLookAtQ( Get_Quaternion(0), MoveVec, BaseVec, 0, 0);
				_ASSERT( ech != 1 );//�G���[�`�F�b�N

				/*�e�̌������Z�b�g���܂�*/
				ech = E3DSetDirQ2( NowGunhsid, Get_Quaternion(0));
				_ASSERT( ech != 1 );//�G���[�`�F�b�N

	}
	if(NowWpKind == 3){//����̎�ނ��A�A�T���g���C�t���ł����

				/*�e�̒u���{�[���̍��W�����߂܂�*/
				ech = E3DGetCurrentBonePos( Get_BodyModel(), Get_Bone_ID(0), 1, &GunOnPos);
				_ASSERT( ech != 1 );//�G���[�`�F�b�N

				/*�e�����߂����W�ɂ����܂�*/
				ech = E3DSetPos( NowGunhsid, GunOnPos);
				_ASSERT( ech != 1 );//�G���[�`�F�b�N

				/*�e�̌����ɂȂ�{�[���̃N�H�[�^�j�I�����擾*/
				ech = E3DGetCurrentBoneQ( Get_BodyModel(), Get_Bone_ID(1), 2, Get_Quaternion(0));//���̌������擾
				_ASSERT( ech != 1 );//�G���[�`�F�b�N

				/*�������������ւ̌v�Z���s���܂�*/
				ech = E3DLookAtQ( Get_Quaternion(0), MoveVec, BaseVec, 0, 0);
				_ASSERT( ech != 1 );//�G���[�`�F�b�N

				/*�e�̌������Z�b�g���܂�*/
				ech = E3DSetDirQ2( NowGunhsid, Get_Quaternion(0));
				_ASSERT( ech != 1 );//�G���[�`�F�b�N

	}
	if(NowWpKind == 4){//����̎�ނ��A�}�V���K���ł����

				/*�e�̒u���{�[���̍��W�����߂܂�*/
				ech = E3DGetCurrentBonePos( Get_BodyModel(), Get_Bone_ID(0), 1, &GunOnPos);
				_ASSERT( ech != 1 );//�G���[�`�F�b�N

				/*�e�����߂����W�ɂ����܂�*/
				ech = E3DSetPos( NowGunhsid, GunOnPos);
				_ASSERT( ech != 1 );//�G���[�`�F�b�N

				/*�e�̌����ɂȂ�{�[���̃N�H�[�^�j�I�����擾*/
				ech = E3DGetCurrentBoneQ( Get_BodyModel(), Get_Bone_ID(1), 2, Get_Quaternion(0));//���̌������擾
				_ASSERT( ech != 1 );//�G���[�`�F�b�N

				/*�������������ւ̌v�Z���s���܂�*/
				ech = E3DLookAtQ( Get_Quaternion(0), MoveVec, BaseVec, 0, 0);
				_ASSERT( ech != 1 );//�G���[�`�F�b�N

				/*�e�̌������Z�b�g���܂�*/
				ech = E3DSetDirQ2( NowGunhsid, Get_Quaternion(0));
				_ASSERT( ech != 1 );//�G���[�`�F�b�N

	}
	if(NowWpKind == 5){//����̎�ނ��A�A�T���g���C�t���ł����

				/*�e�̒u���{�[���̍��W�����߂܂�*/
				ech = E3DGetCurrentBonePos( Get_BodyModel(), Get_Bone_ID(0), 1, &GunOnPos);
				_ASSERT( ech != 1 );//�G���[�`�F�b�N

				/*�e�����߂����W�ɂ����܂�*/
				ech = E3DSetPos( NowGunhsid, GunOnPos);
				_ASSERT( ech != 1 );//�G���[�`�F�b�N

				/*�e�̌����ɂȂ�{�[���̃N�H�[�^�j�I�����擾*/
				ech = E3DGetCurrentBoneQ( Get_BodyModel(), Get_Bone_ID(1), 2, Get_Quaternion(0));//���̌������擾
				_ASSERT( ech != 1 );//�G���[�`�F�b�N

				/*�������������ւ̌v�Z���s���܂�*/
				ech = E3DLookAtQ( Get_Quaternion(0), MoveVec, BaseVec, 0, 0);
				_ASSERT( ech != 1 );//�G���[�`�F�b�N

				/*�e�̌������Z�b�g���܂�*/
				ech = E3DSetDirQ2( NowGunhsid, Get_Quaternion(0));
				_ASSERT( ech != 1 );//�G���[�`�F�b�N

	}

		ech = E3DSetNewPoseML( NowGunhsid);
		_ASSERT( ech != 1 );//�G���[�`�F�b�N




	return 0;
}
/*�l�Ԃ̃��[�V������p���Ȃǂ�ݒ肵�܂�*/
int Soldier::Batch_PeopleMotion(){

	/*�ϐ��̏�����*/
	int ech = 0;//�G���[�m�F�ϐ�
	int MotionID = 0;//ML����擾�������݂́u��t�����v���[�V����ID
	int FrameNo = 0;//ML����擾�������݂́u��t�����v���[�V���������ݍĐ����Ă���ԍ�
	int MotionList[10];//�������������w�肷��z��
	int NoMotionList[10];//�������Ȃ��������w�肷��z��
	D3DXVECTOR3 Squat( 0.0, 0.0, 0.0);//���Ⴊ�񂾏�Ԃ̍��W������


	/*�z��ϐ��̏�����*/
	for( int i=0; i<10; i++){
			MotionList[i] = 0;//�������������w�肷��z���������
			NoMotionList[i] = 0;//�������Ȃ��������w�肷��z���������
	}

	if( Get_MyState() == 0){
			/**/
			/*�㔼�g�̃��[�V�����ݒ�*/

			if( Get_Attitude() == 0){//���Ⴊ�݃��[�h���I�t�Ȃ�
					if( Wp_equipment != -1){//����𑕔����Ă����ԂȂ�
						if( Wpn.GetWeaponData( Wp_equipment, 0) == 1){//�n���h�K�������̂Ȃ�
										if( Get_UpMotion() == 0){//���ʂ̍\��

												/*���[�V�����œ����������̎w��*/
												MotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�̃{�[�����w��
												MotionList[1] = 0;//�w��I��
							
												/*���[�V�����œ������Ȃ������̎w��*/
												NoMotionList[0] = 0;//�w��I��

												/*���[�V������ݒ肷��*/
												ech = E3DSetMOAEventNoML( Get_BodyModel(), 4, MotionList, NoMotionList);//�n���h�K���\��
												
														_ASSERT( ech != 1 );//�G���[�`�F�b�N
										}
							}
							if( Wpn.GetWeaponData( Wp_equipment, 0) == 3){//�V���b�g�K�������̂Ȃ�
										if( Get_UpMotion() == 0){//���ʂ̍\��
					
												/*���[�V�����œ����������̎w��*/
												MotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�̃{�[�����w��
												MotionList[1] = 0;//�w��I��
							
												/*���[�V�����œ������Ȃ������̎w��*/
												NoMotionList[0] = 0;//�w��I��

												/*���[�V������ݒ肷��*/
												ech = E3DSetMOAEventNoML( Get_BodyModel(), 3, MotionList, NoMotionList);//�A�T���g�\��
												
														_ASSERT( ech != 1 );//�G���[�`�F�b�N
										}
							}
							if( Wpn.GetWeaponData( Wp_equipment, 0) == 4){//�A�T���g�����̂Ȃ�
										if( Get_UpMotion() == 0){//���ʂ̍\��
					
												/*���[�V�����œ����������̎w��*/
												MotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�̃{�[�����w��
												MotionList[1] = 0;//�w��I��
							
												/*���[�V�����œ������Ȃ������̎w��*/
												NoMotionList[0] = 0;//�w��I��

												/*���[�V������ݒ肷��*/
												ech = E3DSetMOAEventNoML( Get_BodyModel(), 3, MotionList, NoMotionList);//�A�T���g�\��
												
														_ASSERT( ech != 1 );//�G���[�`�F�b�N
										}
							}
							if( Wpn.GetWeaponData( Wp_equipment, 0) == 5){//�}�V���K�������̂Ȃ�
										if( Get_UpMotion() == 0){//���ʂ̍\��
					
												/*���[�V�����œ����������̎w��*/
												MotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�̃{�[�����w��
												MotionList[1] = 0;//�w��I��
							
												/*���[�V�����œ������Ȃ������̎w��*/
												NoMotionList[0] = 0;//�w��I��

												/*���[�V������ݒ肷��*/
												ech = E3DSetMOAEventNoML( Get_BodyModel(), 3, MotionList, NoMotionList);//�A�T���g�\��
												
														_ASSERT( ech != 1 );//�G���[�`�F�b�N
										}
							}
							if( Wpn.GetWeaponData( Wp_equipment, 0) == 6){//���C�t�������̂Ȃ�
										if( Get_UpMotion() == 0){//���ʂ̍\��
					
												/*���[�V�����œ����������̎w��*/
												MotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�̃{�[�����w��
												MotionList[1] = 0;//�w��I��
							
												/*���[�V�����œ������Ȃ������̎w��*/
												NoMotionList[0] = 0;//�w��I��

												/*���[�V������ݒ肷��*/
												ech = E3DSetMOAEventNoML( Get_BodyModel(), 3, MotionList, NoMotionList);//�A�T���g�\��
												
														_ASSERT( ech != 1 );//�G���[�`�F�b�N
										}
							}
					}
					else{//����𑕔����Ă��Ȃ���ԂȂ�
							/*���[�V�����œ����������̎w��*/
												/*���[�V�����œ����������̎w��*/
												MotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�̃{�[�����w��
												MotionList[1] = 0;//�w��I��
							
												/*���[�V�����œ������Ȃ������̎w��*/
												NoMotionList[0] = 0;//�w��I��

												/*���[�V������ݒ肷��*/
												ech = E3DSetMOAEventNoML( Get_BodyModel(), 3, MotionList, NoMotionList);//�n���h�K���\��
												
														_ASSERT( ech != 1 );//�G���[�`�F�b�N
					}
			}

			/**/
			if( Get_Attitude() == 1){//���Ⴊ�݃��[�h���I���Ȃ�
					if( Wp_equipment != -1){//����𑕔����Ă����ԂȂ�
							if( Wpn.GetWeaponData( Wp_equipment, 0) == 1){//�n���h�K�������̂Ȃ�
										if( Get_UpMotion() == 0){//���ʂ̍\��

												/*���[�V�����œ����������̎w��*/
												MotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�̃{�[�����w��
												MotionList[1] = 0;//�w��I��
							
												/*���[�V�����œ������Ȃ������̎w��*/
												NoMotionList[0] = 0;//�w��I��

												/*���[�V������ݒ肷��*/
												ech = E3DSetMOAEventNoML( Get_BodyModel(), 4, MotionList, NoMotionList);//�n���h�K���\��
												
														_ASSERT( ech != 1 );//�G���[�`�F�b�N
										}
							}
							if( Wpn.GetWeaponData( Wp_equipment, 0) == 4){//�A�T���g�����̂Ȃ�
										if( Get_UpMotion() == 0){//���ʂ̍\��
					
												/*���[�V�����œ����������̎w��*/
												MotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�̃{�[�����w��
												MotionList[1] = 0;//�w��I��
							
												/*���[�V�����œ������Ȃ������̎w��*/
												NoMotionList[0] = 0;//�w��I��

												/*���[�V������ݒ肷��*/
												ech = E3DSetMOAEventNoML( Get_BodyModel(), 3, MotionList, NoMotionList);//�n���h�K���\��
												
														_ASSERT( ech != 1 );//�G���[�`�F�b�N
										}
							}
					}
					else{//����𑕔����Ă��Ȃ���ԂȂ�
							/*���[�V�����œ����������̎w��*/
												/*���[�V�����œ����������̎w��*/
												MotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�̃{�[�����w��
												MotionList[1] = 0;//�w��I��
							
												/*���[�V�����œ������Ȃ������̎w��*/
												NoMotionList[0] = 0;//�w��I��

												/*���[�V������ݒ肷��*/
												ech = E3DSetMOAEventNoML( Get_BodyModel(), 3, MotionList, NoMotionList);//�n���h�K���\��
												
														_ASSERT( ech != 1 );//�G���[�`�F�b�N
					}
			}


			

			/*�z��ϐ��̏�����*/
			for( int i=0; i<10; i++){
					MotionList[i] = 0;//�������������w�肷��z���������
					NoMotionList[i] = 0;//�������Ȃ��������w�肷��z���������
			}

			/**/
			/*�����g�̃��[�V�����ݒ�*/
			if( Get_Attitude() == 0){//���Ⴊ�݃��[�h���I�t�Ȃ�
					if( Get_UnderMotion() == 0){//�~�܂�̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								ech = E3DSetMOAEventNoML( Get_BodyModel(), 2, MotionList, NoMotionList);
								
										_ASSERT( ech != 1 );//�G���[�`�F�b�N
					}
					if( Get_UnderMotion() == 1){//�O�i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								ech = E3DSetMOAEventNoML( Get_BodyModel(), 1, MotionList, NoMotionList);
								
										_ASSERT( ech != 1 );//�G���[�`�F�b�N
					}
					if( Get_UnderMotion() == 2){//�E�i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								ech = E3DSetMOAEventNoML( Get_BodyModel(), 5, MotionList, NoMotionList);
								
										_ASSERT( ech != 1 );//�G���[�`�F�b�N
					}
					if( Get_UnderMotion() == 3){//���i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								ech = E3DSetMOAEventNoML( Get_BodyModel(), 6, MotionList, NoMotionList);
								
										_ASSERT( ech != 1 );//�G���[�`�F�b�N
					}
					if( Get_UnderMotion() == 4){//���O�i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								ech = E3DSetMOAEventNoML( Get_BodyModel(), 7, MotionList, NoMotionList);
								
										_ASSERT( ech != 1 );//�G���[�`�F�b�N
					}
					if( Get_UnderMotion() == 5){//�E�O�i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								ech = E3DSetMOAEventNoML( Get_BodyModel(), 8, MotionList, NoMotionList);
								
										_ASSERT( ech != 1 );//�G���[�`�F�b�N
					}
					if( Get_UnderMotion() == 6){//����i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								ech = E3DSetMOAEventNoML( Get_BodyModel(), 9, MotionList, NoMotionList);
								
										_ASSERT( ech != 1 );//�G���[�`�F�b�N
					}
					if( Get_UnderMotion() == 7){//�E��i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								ech = E3DSetMOAEventNoML( Get_BodyModel(), 10, MotionList, NoMotionList);
								
										_ASSERT( ech != 1 );//�G���[�`�F�b�N
					}
					if( Get_UnderMotion() == 8){//��i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								ech = E3DSetMOAEventNoML( Get_BodyModel(), 11, MotionList, NoMotionList);
								
										_ASSERT( ech != 1 );//�G���[�`�F�b�N
					}
					if( Get_UnderMotion() == 9){//�W�����v�ɂ���̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								ech = E3DSetMOAEventNoML( Get_BodyModel(), 24, MotionList, NoMotionList);
								
										_ASSERT( ech != 1 );//�G���[�`�F�b�N
					}
			}

			/**/
			if( Get_Attitude() == 1){//���Ⴊ�݃��[�h���I���Ȃ�
					if( Get_UnderMotion() == 0){//�~�܂�̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								ech = E3DSetMOAEventNoML( Get_BodyModel(), 13, MotionList, NoMotionList);
								
										_ASSERT( ech != 1 );//�G���[�`�F�b�N
					}
					if( Get_UnderMotion() == 1){//�O�i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								ech = E3DSetMOAEventNoML( Get_BodyModel(), 14, MotionList, NoMotionList);
								
										_ASSERT( ech != 1 );//�G���[�`�F�b�N
					}
					if( Get_UnderMotion() == 2){//�E�i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								ech = E3DSetMOAEventNoML( Get_BodyModel(), 16, MotionList, NoMotionList);
								
										_ASSERT( ech != 1 );//�G���[�`�F�b�N
					}
					if( Get_UnderMotion() == 3){//���i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								ech = E3DSetMOAEventNoML( Get_BodyModel(), 17, MotionList, NoMotionList);
								
										_ASSERT( ech != 1 );//�G���[�`�F�b�N
					}
					if( Get_UnderMotion() == 4){//���O�i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								ech = E3DSetMOAEventNoML( Get_BodyModel(), 19, MotionList, NoMotionList);
								
										_ASSERT( ech != 1 );//�G���[�`�F�b�N
					}
					if( Get_UnderMotion() == 5){//�E�O�i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								ech = E3DSetMOAEventNoML( Get_BodyModel(), 18, MotionList, NoMotionList);
								
										_ASSERT( ech != 1 );//�G���[�`�F�b�N
					}
					if( Get_UnderMotion() == 6){//����i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								ech = E3DSetMOAEventNoML( Get_BodyModel(), 21, MotionList, NoMotionList);
								
										_ASSERT( ech != 1 );//�G���[�`�F�b�N
					}
					if( Get_UnderMotion() == 7){//�E��i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								ech = E3DSetMOAEventNoML( Get_BodyModel(), 20, MotionList, NoMotionList);
								
										_ASSERT( ech != 1 );//�G���[�`�F�b�N
					}
					if( Get_UnderMotion() == 8){//��i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								ech = E3DSetMOAEventNoML( Get_BodyModel(), 15, MotionList, NoMotionList);
								
										_ASSERT( ech != 1 );//�G���[�`�F�b�N
					}
					if( Get_UnderMotion() == 9){//�W�����v�ɂ���̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								ech = E3DSetMOAEventNoML( Get_BodyModel(), 26, MotionList, NoMotionList);
								
										_ASSERT( ech != 1 );//�G���[�`�F�b�N
					}
			}
	}
	if( Get_MyState() == 1){//�L�b�N�t���O���I���Ȃ�
			/*���[�V�����œ����������̎w��*/
			MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
			MotionList[1] = 0;//�w��I��

			/*���[�V�����œ������Ȃ������̎w��*/
			NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
			NoMotionList[1] = 0;//�w��I��

			/*���[�V������ݒ肷��*/
			ech = E3DSetMOAEventNoML( Get_BodyModel(), 22, MotionList, NoMotionList);
			
					_ASSERT( ech != 1 );//�G���[�`�F�b�N
	}
	if( Get_MyState() == 2){//�_�b�V���t���O���I���Ȃ�
			if( Get_AirOnPC() == 0){//�W�����v���Ă��Ȃ��Ȃ�
					/*���[�V�����œ����������̎w��*/
					MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
					MotionList[1] = 0;//�w��I��

					/*���[�V�����œ������Ȃ������̎w��*/
					NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
					NoMotionList[1] = 0;//�w��I��

					/*���[�V������ݒ肷��*/
					ech = E3DSetMOAEventNoML( Get_BodyModel(), 23, MotionList, NoMotionList);
					
							_ASSERT( ech != 1 );//�G���[�`�F�b�N
			}
			if( Get_AirOnPC() == 1){//�W�����v���Ă���̂Ȃ�
					/*���[�V�����œ����������̎w��*/
					MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
					MotionList[1] = 0;//�w��I��

					/*���[�V�����œ������Ȃ������̎w��*/
					NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
					NoMotionList[1] = 0;//�w��I��

					/*���[�V������ݒ肷��*/
					ech = E3DSetMOAEventNoML( Get_BodyModel(), 25, MotionList, NoMotionList);
					
							_ASSERT( ech != 1 );//�G���[�`�F�b�N
			}
	}
	if( Get_MyState() == 3){//��������я�ԂȂ�
					/*���[�V�����œ����������̎w��*/
					MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
					MotionList[1] = 0;//�w��I��

					/*���[�V�����œ������Ȃ������̎w��*/
					NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
					NoMotionList[1] = 0;//�w��I��

					/*���[�V������ݒ肷��*/
					ech = E3DSetMOAEventNoML( Get_BodyModel(), 12, MotionList, NoMotionList);
					
							_ASSERT( ech != 1 );//�G���[�`�F�b�N
	}
	if( Get_MyState() == 4){//�E������я�ԂȂ�
					/*���[�V�����œ����������̎w��*/
					MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
					MotionList[1] = 0;//�w��I��

					/*���[�V�����œ������Ȃ������̎w��*/
					NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
					NoMotionList[1] = 0;//�w��I��

					/*���[�V������ݒ肷��*/
					ech = E3DSetMOAEventNoML( Get_BodyModel(), 12, MotionList, NoMotionList);
					
							_ASSERT( ech != 1 );//�G���[�`�F�b�N
	}
	if( Get_MyState() == 5){//���S��ԂȂ�
					/*���[�V�����œ����������̎w��*/
					MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
					MotionList[1] = 0;//�w��I��

					/*���[�V�����œ������Ȃ������̎w��*/
					NoMotionList[0] = 0;//�w��I��

					/*���[�V������ݒ肷��*/
					ech = E3DSetMOAEventNoML( Get_BodyModel(), 30, MotionList, NoMotionList);
					
							_ASSERT( ech != 1 );//�G���[�`�F�b�N
	}



	/*�}���`���C���[�ɉ����ĐV���[�V�����𓖂Ă�*/
	ech = E3DSetNewPoseML( Get_BodyModel());
	
			_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/*�u��t�����v�����̃��[�V�����͂ǂ������ׂ܂�*/
	ech = E3DGetMotionFrameNoML( Get_BodyModel(), Get_Bone_ID(2), &MotionID, &FrameNo);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/*�v�Z�����N�H�[�^�[�j�I���������܂�*/
	ech = E3DSetBoneQ( Get_BodyModel(), Get_Bone_ID(2), MotionID, FrameNo, Get_Quaternion(3));
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/*�}���`���C���[���[�V�����̌v�Z���s���܂�*/
	ech = E3DCalcMLMotion( Get_BodyModel());
	_ASSERT( ech != 1 );//�G���[�`�F�b�N


	return 0;
}
/*�R���X�g���N�^�A���m���f���̃��[�h�����s�Ȃ��܂�*/
Soldier::Soldier( const int selchara, const int Wpselect_equipment){

	//�ϐ��̏�����
	int ech = 0;
	int DummyModel = 0;
	int ModelID = 0;
	int Bone[10];
	int Qid[10];
	char loadname[256] = "";


	//�N���X�����o�ϐ��̏�����
	Set_PC_Deg_XZ(0.0f);// �����̌����iXZ���W�������j
	Set_PC_Deg_Y(0.0f);// �����̌����iY���W�������j
	Set_UpMotion(0);// �㔼�g�̃��[�V�����̏�����
	Set_UnderMotion(0);// �����g�̃��[�V�����̏�����
	Set_Attitude(0);// �����̎p�����u�����v�Ɏw��
	Set_MyState(0);// �����̓����Ԃ�������
	Set_AirOnPC(0);// �����̋󒆏�Ԃ�ʏ�ɂ���
	Set_Acceleration(0.0);// �d�͉����x��0�ɂ���
	Set_MoveSpeed(0.0);// ���ʉ����x��0�ɂ���
	BeforeAirOnPC = 0;
	Set_Skill( NULL);// �X�L���X���b�g�̃X�L���i�[�ϐ���NULL�|�C���^�[�ɂ��Ă���
	Set_EquipmentSkillSum( 0 );// �������X�L���̍��v��0�ɂ���

	//  ������m�[�}���ɂ��Ă���
	Set_StateFromBranch(-1);

	// �X�L����ǉ�����
	Add_Skill(Creature::COMMANDO);
	
	Add_Skill(Creature::VAN_POUCH);


	//�L�����N�^�[���f���̃��[�h

	if(selchara == 0){//�A�[�e�B�[���f��

			//�A�[�e�B�[���f���̎擾
			wsprintf( loadname, "%s\\data\\3d\\model\\demo\\hito.sig", System::path);//�A�[�e�B�[���f����sig���o�^
			ech = E3DSigLoad( loadname, 0, 0, &ModelID);//���f���̓ǂݍ��݁Acha_hsid�փ��f��������B
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( ech != 1 );//�G���[�_�C�A���O
			};

			//�_�~�[���f���̎擾
			wsprintf( loadname, "%s\\data\\3d\\model\\other\\demo.sig", System::path);//�����f����sig���o�^
			ech = E3DSigLoad( loadname, 0, 1, &DummyModel);//���f���̓ǂݍ��݁Asubmodid�փ��f��������B
			_ASSERT( ech != 1 );//�G���[�`�F�b�N

	}

	if(selchara == 1){//WF��1���f��

			//WF��1���f���̎擾
			wsprintf( loadname, "%s\\data\\3d\\chara\\wf1\\model.sig", System::path);//�A�[�e�B�[���f����sig���o�^
			ech = E3DSigLoad( loadname, 0, 0.15f, &ModelID);//���f���̓ǂݍ��݁Acha_hsid�փ��f��������B
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( ech != 1 );//�G���[�_�C�A���O
			};

			//�_�~�[���f���̎擾
			wsprintf( loadname, "%s\\data\\3d\\model\\other\\demo.sig", System::path);//�����f����sig���o�^
			ech = E3DSigLoad( loadname, 0, 0.01f, &DummyModel);//���f���̓ǂݍ��݁Asubmodid�փ��f��������B
			_ASSERT( ech != 1 );//�G���[�`�F�b�N

			//���[�V�����f�[�^�\��
			wsprintf( loadname, "%s\\data\\3d\\chara\\motion\\pc_motion.moa", System::path);//�����f����sig���o�^
			ech = E3DLoadMOAFile( ModelID, loadname, 3, 1.0f); 
			_ASSERT( ech != 1 );//�G���[�`�F�b�N

			//�{�[���l�[������{�[��ID�̎擾�u�e������_X+�v
			ech = E3DGetBoneNoByName( ModelID, "�e������_X+", &Bone[0]);
			_ASSERT( ech != 1 );//�G���[�`�F�b�N
			//�{�[���l�[������{�[��ID�̎擾�u�e�������_X+�v
			ech = E3DGetBoneNoByName( ModelID, "�e�������_X+", &Bone[1]);
			_ASSERT( ech != 1 );//�G���[�`�F�b�N
			//�{�[���l�[������{�[��ID�̎擾�u��t�����v
			ech = E3DGetBoneNoByName( ModelID, "��t����", &Bone[2]);
			_ASSERT( ech != 1 );//�G���[�`�F�b�N
			//�{�[���l�[������{�[��ID�̎擾�u���t����_X+�v
			ech = E3DGetBoneNoByName( ModelID, "���t����_X+", &Bone[3]);
			_ASSERT( ech != 1 );//�G���[�`�F�b�N
			//�{�[���l�[������{�[��ID�̎擾�u���t����_X-�v
			ech = E3DGetBoneNoByName( ModelID, "���t����_X-", &Bone[4]);
			_ASSERT( ech != 1 );//�G���[�`�F�b�N
			//�{�[���l�[������{�[��ID�̎擾�u���Ȃ��v
			ech = E3DGetBoneNoByName( ModelID, "���Ȃ�", &Bone[5]);
			_ASSERT( ech != 1 );//�G���[�`�F�b�N
			//�{�[���l�[������{�[��ID�̎擾�u�ړ���v
			ech = E3DGetBoneNoByName( ModelID, "�ړ���", &Bone[6]);
			_ASSERT( ech != 1 );//�G���[�`�F�b�N

			/*�ϐ��̑��*/
			Set_StateFromBranch(0);

			Set_HP( Get_MaxHP());//�ő�HP�܂ő��
			Set_Stamina( Get_MaxStamina() );//�Œ�X�^�~�i
	}


	/**/
	//�N�H�[�^�j�I�����쐬���܂�
	/**/	
	for(int i = 0; i<10; i++){
				ech = E3DCreateQ( &Qid[i]);
				_ASSERT( ech != 1 );//�G���[�`�F�b�N
				ech = E3DInitQ( Qid[i]);
				_ASSERT( ech != 1 );//�G���[�`�F�b�N
				Set_Quaternion( i, Qid[i]);
	}



	/*������������̒��ōŏ��ɉ��������Ă��邩�ݒ肵�܂�*/
	Set_Wp_equipment(Wpselect_equipment);
	
	/* ///////////////////////////// */
	// �܂Ƃ߂Ċe�����o�ϐ��ɑ�����܂�
	/* ///////////////////////////// */

	Set_BodyModel( ModelID);// ���f��ID�̑��
	Set_DummyModel( DummyModel);// �_�~�[���f��ID�̑��
	for( int i=0; i<7; i++){
			Set_Bone_ID( i, Bone[i]);
	}





	return;
}