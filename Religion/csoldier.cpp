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
	int ech = 0;// �G���[�`�F�b�N
	int GroundResult = 0;// �n�ʂ̓����蔻��̌���
	int MoveStopFlg = 0;// �󒆂ɕ�����ł���Ƃ��Ɉړ��ł��Ȃ��悤�ɂ��邽�߂̃t���O
	Set_AirOnPC(1);//�@�����t���O
	int Garbage = 0;
	int FaceNo = 0;
	const float MYSIZE = 140;
	D3DXVECTOR3 ReflectVec( 0.0, 0.0, 0.0);//�n�ʂ̔��˃x�N�g���̍\����
	D3DXVECTOR3 GroundOnPos( 0.0, 0.0, 0.0);//���L������n�ʂɐ����ɂ��낵���ꍇ�̍��W
	D3DXVECTOR3 MyPos( 0.0, 0.0, 0.0);//�����̃L�����N�^�[���W
	D3DXVECTOR3 NewMyPos( 0.0, 0.0, 0.0);// �V���������̃L�����N�^�[���W
	D3DXVECTOR3 PointConflictPos( 0.0, 0.0, 0.0);
	D3DXVECTOR3 PointConflictVec( 0.0, 0.0, 0.0);
	static D3DXVECTOR3 MyChkBeforePointPos[4];
	D3DXVECTOR3 MyChkPointPos[4];//
	
	/* ///////////////////////////////////////// */
	// ���W�̎擾���s���܂��B
	/* ///////////////////////////////////////// */

	MyPos = Act->GetPos();

	MyChkPointPos[0].x = MyPos.x - MYSIZE; MyChkPointPos[0].y = MyPos.y; MyChkPointPos[0].z = MyPos.z + MYSIZE;//���A��
	MyChkPointPos[1].x = MyPos.x + MYSIZE; MyChkPointPos[1].y = MyPos.y; MyChkPointPos[1].z = MyPos.z + MYSIZE;//���A��
	MyChkPointPos[2].x = MyPos.x - MYSIZE; MyChkPointPos[2].y = MyPos.y; MyChkPointPos[2].z = MyPos.z - MYSIZE;//��O�A��
	MyChkPointPos[3].x = MyPos.x + MYSIZE; MyChkPointPos[3].y = MyPos.y; MyChkPointPos[3].z = MyPos.z - MYSIZE;//��O�A��

	/* ///////////////////////////////////////////////////////// */
	// �X�e�[�W�O���E���h���Ƃɂǂ̂悤�ȏ����ɂ����邩�U�蕪���܂�
	/* ///////////////////////////////////////////////////////// */

	/* /////////////////////////////////// */
	/* ���������x�̐ݒ���s���܂��B
	/* /////////////////////////////////// */
	
	Set_Acceleration( Get_Acceleration() - 8.0);

	//if( Stg->Stage_GndMode == 0){


	/* ////////////////////////////////////// */
	// ���̓����蔻����s���܂�
	/* ////////////////////////////////////// */

	for( int i = 0; i < 4; i++){

			// �`�F�b�N������W����A���������x�����������̂���
			D3DXVECTOR3 MyPos_AddAcceleration( MyChkPointPos[i].x, MyChkPointPos[i].y + (float)Get_Acceleration(), MyChkPointPos[i].z);
		
			// ��قǂ̍��W���`�F�b�N����B
			ech = E3DChkConfLineAndFace( MyChkBeforePointPos[i], MyPos_AddAcceleration, Stg->Stage_hsid[0], 1, &Garbage, &FaceNo
										, &PointConflictPos, &PointConflictVec, &Garbage);
			_ASSERT( ech != 1 );//�G���[�`�F�b�N

			// �����A�������Ă����
			if( FaceNo != -1){
					NewMyPos.x = MyPos.x;
					NewMyPos.y = PointConflictPos.y;
					NewMyPos.z = MyPos.z;

					Act->SetPos( NewMyPos);
					//ech = E3DSetPos( Get_BodyModel(), NewMyPos);
					//_ASSERT( ech != 1 );//�G���[�`�F�b�N

					
					Set_Acceleration( 0.0);// �����x��0�ɂ���
					Set_AirOnPC(AirOff);//�@�����t���O���I�t�ɂ���
			}
	}

	if( Get_AirOnPC() == AirOn){//�@�����t���O���I���Ȃ�

		if( Get_MyState() == 2 && BeforeAirOnPC != Get_AirOnPC())// �_�b�V����ԂŁA�󒆂ɑJ�ڂ�����
		{
			Set_Acceleration( Get_Acceleration() + 80.0);
		}

		NewMyPos.x = MyPos.x;
		NewMyPos.y = MyPos.y + (float)Get_Acceleration();
		NewMyPos.z = MyPos.z;
	
		Act->SetPos( NewMyPos);
		/*E3DSetPos( Get_BodyModel(), NewMyPos);*/
		
	}
	else//�@�����t���O���I�t�Ȃ�
	{
		if( Get_MyState() == S_JUMP) Set_MyState( NORMAL);
	}



	for( int i=0; i<4; i++){
			MyChkBeforePointPos[i].x = MyChkPointPos[i].x;
			MyChkBeforePointPos[i].z = MyChkPointPos[i].z;
			MyChkBeforePointPos[i].y = MyChkPointPos[i].y + 300.0f;
	}


	/*����̃L�����N�^�[���󒆂ɂ��邩������܂�(�����[�v���g�p)*/
	BeforeAirOnPC = Get_AirOnPC();


	return 0;
}
/*�e�̌��ݎ����Ă�e�������߂̃��[�V�����E�V�X�e�����Ǌ�����֐�*/
int Soldier::GunPutOnHand(){


	/* �������Ȃ��Ȃ� */
	if( Get_Wp_equipment() == -1){
		return -1;// ���[�v�𔲂���
	}

	/*�ϐ��̏�����*/
	int ech = 0;//�G���[�`�F�b�N�ϐ�
	int QID;
	int NowWpKind = Wpn.Get_WeaponPointer(Wp_equipment)->Get_Kind();//���̕���̎�ނ��擾���܂�
	int NowWpNo = Wpn.Get_WeaponPointer(Wp_equipment)->Get_Number();//���̕���̃i���o�[���擾���܂�
	int NowGunhsid = Wpn.Get_WeaponPointer(Wp_equipment)->Get_Model();//���̕���̃��f���f�[�^ID���擾���܂�
	int NowFireFlag = Wpn.Get_WeaponPointer(Wp_equipment)->Get_NowFireFlag();//���̕���̑ł��Ă��邩�̏����擾���܂�
	D3DXVECTOR3 GunOnPos( 0.0, 0.0, 0.0);//�e��u�����W
	D3DXVECTOR3 GunHitPos( 0.0, 0.0, 0.0);//�����蔻�胂�f����u�����W
	D3DXVECTOR3 MoveVec( 0.0, 0.0, 0.0);
	D3DXVECTOR3 BaseVec( 0.0, 0.0, -1.0);





	/*�ȉ��A��ނɂ���ĐU�蕪�����s���܂�*/
	switch(NowWpKind){
			case 0://����̎�ނ��A�n���h�K���ł����
			case 2://����̎�ނ��A�V���b�g�K���ł����
			case 3://����̎�ނ��A�A�T���g���C�t���ł����
			case 4://����̎�ނ��A�}�V���K���ł����
			case 5://����̎�ނ��A�A�T���g���C�t���ł����
				{

					/*�e�̒u���{�[���̍��W�����߂܂�*/
					GunOnPos = Act->BonePos( "�e������_X+");
					//ech = E3DGetCurrentBonePos( Get_BodyModel(), Get_Bone_ID(0), 1, &GunOnPos);
					//_ASSERT( ech != 1 );//�G���[�`�F�b�N

					/*�e�����߂����W�ɂ����܂�*/
					ech = E3DSetPos( NowGunhsid, GunOnPos);
					_ASSERT( ech != 1 );//�G���[�`�F�b�N

					/*�e�̌����ɂȂ�{�[���̃N�H�[�^�j�I�����擾*/
					QID = Act->GetBoneQ( "�e������_X+", ""ada);
					//ech = E3DGetCurrentBoneQ( Get_BodyModel(), Get_Bone_ID(1), 2, Get_Quaternion(0));//���̌������擾
					//_ASSERT( ech != 1 );//�G���[�`�F�b�N

					/*�������������ւ̌v�Z���s���܂�*/
					ech = E3DLookAtQ( QID, MoveVec, BaseVec, 0, 0);
					_ASSERT( ech != 1 );//�G���[�`�F�b�N

					/*�e�̌������Z�b�g���܂�*/
					ech = E3DSetDirQ2( NowGunhsid, QID);
					_ASSERT( ech != 1 );//�G���[�`�F�b�N

					break;
			}
			case 7:{//����̎�ނ��A�T�|�[�g����ł����

					if( NowFireFlag == 0){// ����������Ă��Ȃ��Ȃ�
								/*�T�|�[�g����̒u���{�[���̍��W�����߂܂�*/
								GunOnPos = Act->BonePos( "�e������_X+");
								//ech = E3DGetCurrentBonePos( Get_BodyModel(), Get_Bone_ID(0), 1, &GunOnPos);
								//_ASSERT( ech != 1 );//�G���[�`�F�b�N

								/*�T�|�[�g��������߂����W�ɂ����܂�*/
								ech = E3DSetPos( NowGunhsid, GunOnPos);
								_ASSERT( ech != 1 );//�G���[�`�F�b�N

								/*�T�|�[�g����̌����ɂȂ�{�[���̃N�H�[�^�j�I�����擾*/
								QID = Act->GetBoneQ( "�e������_X+", ""error);
								//ech = E3DGetCurrentBoneQ( Get_BodyModel(), Get_Bone_ID(1), 2, Get_Quaternion(0));//���̌������擾
								//_ASSERT( ech != 1 );//�G���[�`�F�b�N

								/*�������������ւ̌v�Z���s���܂�*/
								ech = E3DLookAtQ( QID, MoveVec, BaseVec, 0, 0);
								_ASSERT( ech != 1 );//�G���[�`�F�b�N

								/*�T�|�[�g����̌������Z�b�g���܂�*/
								ech = E3DSetDirQ2( NowGunhsid, QID);
								_ASSERT( ech != 1 );//�G���[�`�F�b�N
					}




					break;
			}
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
	int NowEquipmentKind = 0;
	int MotionList[10];//�������������w�肷��z��
	int NoMotionList[10];//�������Ȃ��������w�肷��z��
	D3DXVECTOR3 Squat( 0.0, 0.0, 0.0);//���Ⴊ�񂾏�Ԃ̍��W������


	/*�z��ϐ��̏�����*/
	for( int i=0; i<10; i++){
			MotionList[i] = 0;//�������������w�肷��z���������
			NoMotionList[i] = 0;//�������Ȃ��������w�肷��z���������
	}

	/* �������ʔԍ����������Ă��ȊO�ŁA���̑��������݂��Ă���� */
	if( Wp_equipment != -1){
			NowEquipmentKind = Wpn.Get_WeaponPointer(Wp_equipment)->Get_Kind();
	}

	
	if( Get_MyState() == NORMAL){
			/**/
			/*�㔼�g�̃��[�V�����ݒ�*/

			if( Get_Attitude() == 0){//���Ⴊ�݃��[�h���I�t�Ȃ�
					if( Wp_equipment != -1){//����𑕔����Ă����ԂȂ�
						if( NowEquipmentKind == 0){//�n���h�K�������̂Ȃ�
										if( Get_UpMotion() == 0){//���ʂ̍\��

												/*���[�V�����œ����������̎w��*/
												MotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�̃{�[�����w��
												MotionList[1] = 0;//�w��I��
							
												/*���[�V�����œ������Ȃ������̎w��*/
												NoMotionList[0] = 0;//�w��I��

												/*���[�V������ݒ肷��*/
												Act->MOAEventNoML( 4, MotionList, NoMotionList);
										}
							}
							if( NowEquipmentKind == 2){//�V���b�g�K�������̂Ȃ�
										if( Get_UpMotion() == 0){//���ʂ̍\��
					
												/*���[�V�����œ����������̎w��*/
												MotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�̃{�[�����w��
												MotionList[1] = 0;//�w��I��
							
												/*���[�V�����œ������Ȃ������̎w��*/
												NoMotionList[0] = 0;//�w��I��

												/*���[�V������ݒ肷��*/
												Act->MOAEventNoML( 3, MotionList, NoMotionList);
										}
							}
							if( NowEquipmentKind == 3){//�A�T���g�����̂Ȃ�
										if( Get_UpMotion() == 0){//���ʂ̍\��
					
												/*���[�V�����œ����������̎w��*/
												MotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�̃{�[�����w��
												MotionList[1] = 0;//�w��I��
							
												/*���[�V�����œ������Ȃ������̎w��*/
												NoMotionList[0] = 0;//�w��I��

												/*���[�V������ݒ肷��*/
												Act->MOAEventNoML( 3, MotionList, NoMotionList);
										}

							}
							if( NowEquipmentKind == 4){//�}�V���K�������̂Ȃ�
										if( Get_UpMotion() == 0){//���ʂ̍\��
					
												/*���[�V�����œ����������̎w��*/
												MotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�̃{�[�����w��
												MotionList[1] = 0;//�w��I��
							
												/*���[�V�����œ������Ȃ������̎w��*/
												NoMotionList[0] = 0;//�w��I��

												/*���[�V������ݒ肷��*/
												Act->MOAEventNoML( 3, MotionList, NoMotionList);
										}
							}
							if( NowEquipmentKind == 5){//���C�t�������̂Ȃ�
										if( Get_UpMotion() == 0){//���ʂ̍\��
					
												/*���[�V�����œ����������̎w��*/
												MotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�̃{�[�����w��
												MotionList[1] = 0;//�w��I��
							
												/*���[�V�����œ������Ȃ������̎w��*/
												NoMotionList[0] = 0;//�w��I��

												/*���[�V������ݒ肷��*/
												Act->MOAEventNoML( 3, MotionList, NoMotionList);
										}
							}
							if( NowEquipmentKind == 7){//�T�|�[�g�֘A�̓����Ȃ�
										if( Get_UpMotion() == 0){//���ʂ̍\��
					
												/*���[�V�����œ����������̎w��*/
												MotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�̃{�[�����w��
												MotionList[1] = 0;//�w��I��
							
												/*���[�V�����œ������Ȃ������̎w��*/
												NoMotionList[0] = 0;//�w��I��

												/*���[�V������ݒ肷��*/
												Act->MOAEventNoML( 33, MotionList, NoMotionList);
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
												Act->MOAEventNoML( 32, MotionList, NoMotionList);
					}
			}

			/**/
			if( Get_Attitude() == 1){//���Ⴊ�݃��[�h���I���Ȃ�
					if( Wp_equipment != -1){//����𑕔����Ă����ԂȂ�
							if( NowEquipmentKind == 0){//�n���h�K�������̂Ȃ�
										if( Get_UpMotion() == 0){//���ʂ̍\��

												/*���[�V�����œ����������̎w��*/
												MotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�̃{�[�����w��
												MotionList[1] = 0;//�w��I��
							
												/*���[�V�����œ������Ȃ������̎w��*/
												NoMotionList[0] = 0;//�w��I��

												/*���[�V������ݒ肷��*/
												
												Act->MOAEventNoML( 4, MotionList, NoMotionList);//�n���h�K���\��
										}
							}
							if( NowEquipmentKind == 3){//�A�T���g�����̂Ȃ�
										if( Get_UpMotion() == 0){//���ʂ̍\��
					
												/*���[�V�����œ����������̎w��*/
												MotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�̃{�[�����w��
												MotionList[1] = 0;//�w��I��
							
												/*���[�V�����œ������Ȃ������̎w��*/
												NoMotionList[0] = 0;//�w��I��

												/*���[�V������ݒ肷��*/
												Act->MOAEventNoML( 3, MotionList, NoMotionList);
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
												Act->MOAEventNoML( 3, MotionList, NoMotionList);
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
								Act->MOAEventNoML( 2, MotionList, NoMotionList);
					}
					if( Get_UnderMotion() == 1){//�O�i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								Act->MOAEventNoML( 1, MotionList, NoMotionList);
					}
					if( Get_UnderMotion() == 2){//�E�i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								Act->MOAEventNoML( 5, MotionList, NoMotionList);
					}
					if( Get_UnderMotion() == 3){//���i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								Act->MOAEventNoML( 6, MotionList, NoMotionList);
					}
					if( Get_UnderMotion() == 4){//���O�i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								Act->MOAEventNoML( 7, MotionList, NoMotionList);
					}
					if( Get_UnderMotion() == 5){//�E�O�i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								Act->MOAEventNoML( 8, MotionList, NoMotionList);
					}
					if( Get_UnderMotion() == 6){//����i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								Act->MOAEventNoML( 9, MotionList, NoMotionList);
					}
					if( Get_UnderMotion() == 7){//�E��i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								Act->MOAEventNoML( 7, MotionList, NoMotionList);
					}
					if( Get_UnderMotion() == 8){//��i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								Act->MOAEventNoML( 11, MotionList, NoMotionList);
					}
					if( Get_UnderMotion() == 9){//�W�����v�ɂ���̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								Act->MOAEventNoML( 24, MotionList, NoMotionList);
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
								Act->MOAEventNoML( 13, MotionList, NoMotionList);
					}
					if( Get_UnderMotion() == 1){//�O�i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								Act->MOAEventNoML( 14, MotionList, NoMotionList);
					}
					if( Get_UnderMotion() == 2){//�E�i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								Act->MOAEventNoML( 16, MotionList, NoMotionList);
					}
					if( Get_UnderMotion() == 3){//���i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								Act->MOAEventNoML( 17, MotionList, NoMotionList);
					}
					if( Get_UnderMotion() == 4){//���O�i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								Act->MOAEventNoML( 19, MotionList, NoMotionList);
					}
					if( Get_UnderMotion() == 5){//�E�O�i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								Act->MOAEventNoML( 18, MotionList, NoMotionList);
					}
					if( Get_UnderMotion() == 6){//����i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								Act->MOAEventNoML( 21, MotionList, NoMotionList);
					}
					if( Get_UnderMotion() == 7){//�E��i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								Act->MOAEventNoML( 20, MotionList, NoMotionList);
					}
					if( Get_UnderMotion() == 8){//��i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								Act->MOAEventNoML( 15, MotionList, NoMotionList);
					}
					if( Get_UnderMotion() == 9){//�W�����v�ɂ���̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								Act->MOAEventNoML( 26, MotionList, NoMotionList);
					}
			}
	}
	if( Get_MyState() == KICK){//�L�b�N�t���O���I���Ȃ�
			/*���[�V�����œ����������̎w��*/
			MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
			MotionList[1] = 0;//�w��I��

			/*���[�V�����œ������Ȃ������̎w��*/
			NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
			NoMotionList[1] = 0;//�w��I��

			/*���[�V������ݒ肷��*/
			Act->MOAEventNoML( 22, MotionList, NoMotionList);
	}
	if( Get_MyState() == RUN){//�_�b�V���t���O���I���Ȃ�
			if( Get_AirOnPC() == 0){//�W�����v���Ă��Ȃ��Ȃ�
					/*���[�V�����œ����������̎w��*/
					MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
					MotionList[1] = 0;//�w��I��

					/*���[�V�����œ������Ȃ������̎w��*/
					NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
					NoMotionList[1] = 0;//�w��I��

					/*���[�V������ݒ肷��*/
					Act->MOAEventNoML( 23, MotionList, NoMotionList);
			}
			if( Get_AirOnPC() == 1){//�W�����v���Ă���̂Ȃ�
					/*���[�V�����œ����������̎w��*/
					MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
					MotionList[1] = 0;//�w��I��

					/*���[�V�����œ������Ȃ������̎w��*/
					NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
					NoMotionList[1] = 0;//�w��I��

					/*���[�V������ݒ肷��*/
					Act->MOAEventNoML( 25, MotionList, NoMotionList);
			}
			if( Wp_equipment != -1){
								if( NowEquipmentKind == 3){//�ێ��̍\��
					
										/*���[�V�����œ����������̎w��*/
										MotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�̃{�[�����w��
										MotionList[1] = 0;//�w��I��
							
										/*���[�V�����œ������Ȃ������̎w��*/
										NoMotionList[0] = 0;//�w��I��

										/*���[�V������ݒ肷��*/
										Act->MOAEventNoML( 31, MotionList, NoMotionList);
								}
			}
			else{
						/*���[�V�����œ����������̎w��*/
						MotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�̃{�[�����w��
						MotionList[1] = 0;//�w��I��
							
						/*���[�V�����œ������Ȃ������̎w��*/
						NoMotionList[0] = 0;//�w��I��

						/*���[�V������ݒ肷��*/
						Act->MOAEventNoML( 32, MotionList, NoMotionList);


		}
	}
	if( Get_MyState() == LEFT_SJUMP){//��������я�ԂȂ�
					/*���[�V�����œ����������̎w��*/
					MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
					MotionList[1] = 0;//�w��I��

					/*���[�V�����œ������Ȃ������̎w��*/
					NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
					NoMotionList[1] = 0;//�w��I��

					/*���[�V������ݒ肷��*/
					Act->MOAEventNoML( 12, MotionList, NoMotionList);
	}
	if( Get_MyState() == RIGHT_SJUMP){//�E������я�ԂȂ�
					/*���[�V�����œ����������̎w��*/
					MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
					MotionList[1] = 0;//�w��I��

					/*���[�V�����œ������Ȃ������̎w��*/
					NoMotionList[0] = Get_Bone_ID(5);//�u���Ȃ��v�{�[�����w��
					NoMotionList[1] = 0;//�w��I��

					/*���[�V������ݒ肷��*/
					Act->MOAEventNoML( 12, MotionList, NoMotionList);
	}
	if( Get_MyState() == DEAD){//���S��ԂȂ�
					/*���[�V�����œ����������̎w��*/
					MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
					MotionList[1] = 0;//�w��I��

					/*���[�V�����œ������Ȃ������̎w��*/
					NoMotionList[0] = 0;//�w��I��

					/*���[�V������ݒ肷��*/
					Act->MOAEventNoML( 30, MotionList, NoMotionList);
	}
	if( Get_MyState() == S_JUMP){//�J�^�p���g��ԂȂ�
					/*���[�V�����œ����������̎w��*/
					MotionList[0] = Get_Bone_ID(6);//�u�ړ���v�̃{�[�����w��
					MotionList[1] = 0;//�w��I��

					/*���[�V�����œ������Ȃ������̎w��*/
					NoMotionList[0] = 0;//�w��I��

					/*���[�V������ݒ肷��*/
					Act->MOAEventNoML( 25, MotionList, NoMotionList);
	}

	Act->MotionFinalize( "", );
	///*�}���`���C���[�ɉ����ĐV���[�V�����𓖂Ă�*/
	//ech = E3DSetNewPoseML( Get_BodyModel());
	//_ASSERT( ech != 1 );//�G���[�`�F�b�N

	///*�u��t�����v�����̃��[�V�����͂ǂ������ׂ܂�*/
	//ech = E3DGetMotionFrameNoML( Get_BodyModel(), Get_Bone_ID(2), &MotionID, &FrameNo);
	//_ASSERT( ech != 1 );//�G���[�`�F�b�N

	///*�v�Z�����N�H�[�^�[�j�I���������܂�*/
	//ech = E3DSetBoneQ( Get_BodyModel(), Get_Bone_ID(2), MotionID, FrameNo, Get_Quaternion(3));
	//_ASSERT( ech != 1 );//�G���[�`�F�b�N

	///*�}���`���C���[���[�V�����̌v�Z���s���܂�*/
	//ech = E3DCalcMLMotion( Get_BodyModel());
	//_ASSERT( ech != 1 );//�G���[�`�F�b�N


	return 0;
}

/*  */
//int Soldier::

/*�R���X�g���N�^�A���m���f���̃��[�h�����s�Ȃ��܂�*/
Soldier::Soldier( const int selchara, const int Wpselect_equipment){

	//�ϐ��̏�����
	int ech = 0;
	/*int DummyModel = 0;*/
	int ModelID = 0;
	/*int Bone[10];*/
	//int Qid[10];
	char loadname[256] = "";

	/* �X�e�[�^�X���Z�b�g */
	StatusReset();
	
	// �X�L����ǉ�����
	Add_Skill(Creature::COMMANDO);
	
	Add_Skill(Creature::VAN_POUCH);


	//�L�����N�^�[���f���̃��[�h

	if(selchara == 0){//�A�[�e�B�[���f��

			
			//wsprintf( loadname, "%s\\data\\3d\\model\\demo\\hito.sig", System::path);//�A�[�e�B�[���f����sig���o�^
			//ech = E3DSigLoad( loadname, 0, 0, &ModelID);//���f���̓ǂݍ��݁Acha_hsid�փ��f��������B
			//if(ech != 0 ){//�G���[�`�F�b�N
			//		_ASSERT( ech != 1 );//�G���[�_�C�A���O
			//};
			//�A�[�e�B�[���f���̎擾			
			Act = Act->LoadModel( "data\\3d\\model\\demo\\hito.sig");
			Act->SetScale( 0.0f);

			////�_�~�[���f���̎擾
			//wsprintf( loadname, "%s\\data\\3d\\model\\other\\demo.sig", System::path);//�����f����sig���o�^
			//ech = E3DSigLoad( loadname, 0, 1, &DummyModel);//���f���̓ǂݍ��݁Asubmodid�փ��f��������B
			//_ASSERT( ech != 1 );//�G���[�`�F�b�N

	}

	if(selchara == 1){//WF��1���f��

			//WF��1���f���̎擾
			Act = Act->LoadModel( "data\\3d\\chara\\wf1\\model.sig");
			Act->SetScale( 0.15f);

			Act->LoadMOA( "data\\3d\\chara\\motion\\pc_motion.moa");

			Act->BoneNoByName( "�e������_X+");
			Act->BoneNoByName( "�e�������_X+");
			Act->BoneNoByName( "��t����");
			Act->BoneNoByName( "���t����_X+");
			Act->BoneNoByName( "���t����_X-");
			Act->BoneNoByName( "���Ȃ�");
			Act->BoneNoByName( "�ړ���");

			Act->CreateQ( "");
			////WF��1���f���̎擾
			//wsprintf( loadname, "%s\\data\\3d\\chara\\wf1\\model.sig", System::path);//�A�[�e�B�[���f����sig���o�^
			//ech = E3DSigLoad( loadname, 0, 0.15f, &ModelID);//���f���̓ǂݍ��݁Acha_hsid�փ��f��������B
			//if(ech != 0 ){//�G���[�`�F�b�N
			//		_ASSERT( ech != 1 );//�G���[�_�C�A���O
			//};

			////�_�~�[���f���̎擾
			//wsprintf( loadname, "%s\\data\\3d\\model\\other\\demo.sig", System::path);//�����f����sig���o�^
			//ech = E3DSigLoad( loadname, 0, 0.01f, &DummyModel);//���f���̓ǂݍ��݁Asubmodid�փ��f��������B
			//_ASSERT( ech != 1 );//�G���[�`�F�b�N

			////���[�V�����f�[�^�\��
			//wsprintf( loadname, "%s\\data\\3d\\chara\\motion\\pc_motion.moa", System::path);//�����f����sig���o�^
			//ech = E3DLoadMOAFile( ModelID, loadname, 3, 1.0f); 
			//_ASSERT( ech != 1 );//�G���[�`�F�b�N

			////�{�[���l�[������{�[��ID�̎擾�u�e������_X+�v
			//ech = E3DGetBoneNoByName( ModelID, "�e������_X+", &Bone[0]);
			//_ASSERT( ech != 1 );//�G���[�`�F�b�N
			////�{�[���l�[������{�[��ID�̎擾�u�e�������_X+�v
			//ech = E3DGetBoneNoByName( ModelID, "�e�������_X+", &Bone[1]);
			//_ASSERT( ech != 1 );//�G���[�`�F�b�N
			////�{�[���l�[������{�[��ID�̎擾�u��t�����v
			//ech = E3DGetBoneNoByName( ModelID, "��t����", &Bone[2]);
			//_ASSERT( ech != 1 );//�G���[�`�F�b�N
			////�{�[���l�[������{�[��ID�̎擾�u���t����_X+�v
			//ech = E3DGetBoneNoByName( ModelID, "���t����_X+", &Bone[3]);
			//_ASSERT( ech != 1 );//�G���[�`�F�b�N
			////�{�[���l�[������{�[��ID�̎擾�u���t����_X-�v
			//ech = E3DGetBoneNoByName( ModelID, "���t����_X-", &Bone[4]);
			//_ASSERT( ech != 1 );//�G���[�`�F�b�N
			////�{�[���l�[������{�[��ID�̎擾�u���Ȃ��v
			//ech = E3DGetBoneNoByName( ModelID, "���Ȃ�", &Bone[5]);
			//_ASSERT( ech != 1 );//�G���[�`�F�b�N
			////�{�[���l�[������{�[��ID�̎擾�u�ړ���v
			//ech = E3DGetBoneNoByName( ModelID, "�ړ���", &Bone[6]);
			//_ASSERT( ech != 1 );//�G���[�`�F�b�N


	}


	/**/
	//�N�H�[�^�j�I�����쐬���܂�
	/**/	
	//for(int i = 0; i<10; i++){
	//			ech = E3DCreateQ( &Qid[i]);
	//			_ASSERT( ech != 1 );//�G���[�`�F�b�N
	//			ech = E3DInitQ( Qid[i]);
	//			_ASSERT( ech != 1 );//�G���[�`�F�b�N
	//			Set_Quaternion( i, Qid[i]);
	//}



	/*������������̒��ōŏ��ɉ��������Ă��邩�ݒ肵�܂�*/
	Set_Wp_equipment(Wpselect_equipment);
	
	/* ///////////////////////////// */
	// �܂Ƃ߂Ċe�����o�ϐ��ɑ�����܂�
	/* ///////////////////////////// */

	//Set_BodyModel( ModelID);// ���f��ID�̑��
	//Set_DummyModel( DummyModel);// �_�~�[���f��ID�̑��
	//for( int i=0; i<7; i++){
	//		Set_Bone_ID( i, Bone[i]);
	//}





	return;
}

/* �f�X�g���N�^ */
Soldier::~Soldier(){

	/* ������ */
	int ech;

	//�L�����N�^�[���f�����폜���܂�
	//ech = E3DDestroyHandlerSet( Get_BodyModel());
	//_ASSERT( ech != 1 );//�G���[�`�F�b�N

	//1�ڂ̃L�����N�^�[�_�~�[���f�����폜���܂�
	ech = E3DDestroyHandlerSet( Get_DummyModel());
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	//�X�L���i�[�ϐ��̍폜
	Delete_Skill();

	/**/
	//�N�H�[�^�j�I�����폜���܂�
	/**/	
	for(int i = 0; i<4; i++){
				ech = E3DDestroyQ( Get_Quaternion(i));
				_ASSERT( ech != 1 );//�G���[�`�F�b�N
	}


	return;
}

/* �\���W���[�N���X�̏�Ԃ������ɖ߂��܂�(���X�^�[�g���ŗ��p) */
int Soldier::StatusReset()
{

	/* �����܂łɁA��������߂Ă����ׂ�(�K���i�[�Ƃ�) */
	Set_StateFromBranch( DEFAULT);//  ������m�[�}���ɂ��Ă���

	//�N���X�����o�ϐ��̏�����
	Set_PC_Deg_XZ(0.0f);// �����̌����iXZ���W�������j
	Set_PC_Deg_Y(0.0f);// �����̌����iY���W�������j
	Set_UpMotion(0);// �㔼�g�̃��[�V�����̏�����
	Set_UnderMotion(0);// �����g�̃��[�V�����̏�����
	Set_Attitude(0);// �����̎p�����u�����v�Ɏw��
	Set_MyState( People::NORMAL);// �����̓����Ԃ�������
	Set_AirOnPC(0);// �����̋󒆏�Ԃ�ʏ�ɂ���
	Set_Acceleration(0.0);// �d�͉����x��0�ɂ���
	Set_MoveSpeed(0.0);// ���ʉ����x��0�ɂ���
	BeforeAirOnPC = 0;
	Set_Skill( NULL);// �X�L���X���b�g�̃X�L���i�[�ϐ���NULL�|�C���^�[�ɂ��Ă���
	Set_EquipmentSkillSum( 0 );// �������X�L���̍��v��0�ɂ���

	Set_HP( Get_MaxHP());//�ő�HP�܂ő��
	Set_Stamina( Get_MaxStamina() );//�Œ�X�^�~�i





	return 0;
}