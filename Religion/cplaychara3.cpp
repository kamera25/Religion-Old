/*�����ł́A�����N���X�̃L�����E�G�̊֐����`����N���X�R�[�h�t�@�C���ł��B
//���Ɍ��ł����[�h���Ɋ֌W���鎞�ɕK�v�Ȋ֐�������������Ă��܂��B
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_
#include "cstage.h"//�X�e�[�W�֌W�̃N���X�w�b�_�t�@�C��
#include "clive.h"//�G��L�����̃N���X�w�b�_�t�@�C��
#include "c_batch_preparat.h"//�`��ɕK�v�ȃN���X�̐錾�w�b�_�t�@�C��
#include <math.h>//���w�v�Z���g�����߂̃w�b�_�t�@�C��
#include "ccamera.h"//�J�����Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��
#include "cweapon.h"//����Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��

//�����ɃO���[�o���ϐ���錾
extern System *sys;//�V�X�e���N���X���w���A�N���X�̃|�C���^


/*���˂����_����̏e�֘A�܂Ƃߊ֐�*/
int PlayerChara::ShoulderGunSys( Batch_Preparat *BatPre, Camera *Cam, int ScreenPos[2]){

	/*�S�̂Ŏg���ϐ��̏�����*/
	int ech = 0;//�G���[�m�F�ϐ�
	D3DXVECTOR3 BaseVec( 0.0, 0.0, -1.0);//�����̏��������x�N�g��
	D3DXVECTOR3 CameraUpVec( 0.0, 1.0, 0.0);//�J�����̏㕔�̃x�N�g��

  /*�L�����N�^�[�̈ʒu��ݒ肵�܂�*/
	int MotionID = 0;//ML����擾�������݂́u��t�����v���[�V����ID
	int FrameNo = 0;//ML����擾�������݂́u��t�����v���[�V���������ݍĐ����Ă���ԍ�
	static double Tm_DegQ_Y = 0.50;//�u��������O�̊p�x�ϐ�Y
	double Sin_Y = 0.0;//Y���W�T�C���ϐ�
	double Sin_XZ = 0.0;//XZ���W�T�C���ϐ�
	double Cos_Y = 0.0;//Y���W�R�T�C���ϐ�
	double Cos_XZ = 0.0;//XZ���W�R�T�C���ϐ�
	D3DXVECTOR3 TurnPos( 0.0, 0.0, 0.0);//�����ׂ�Y�x�N�g��
	D3DXVECTOR3 StomachPos( 0.0, 0.0, 0.0);//�u������v�̍��W
	D3DXVECTOR3 WantDeg( 0.0, 0.0, 0.0);//�������������ւ̃x�N�g��
	D3DXVECTOR3 OriginPos( 0.0, 0.0, 0.0);//�L�����N�^�[�������ׂ����_���W
	D3DXVECTOR3 MyPos1( 0.0, 0.0, 0.0);//�ŏ������̍��W

	//�����̌�������]�����܂��B
		//�ŏ��ɉ�]�̌v�Z���܂�

	if(( MyState == 0) || ( (MyState == 2) && ( AirOnPC == 0))){//�ʏ�E�󒆃_�b�V�����[�h�łȂ���΁A�ȉ��擾����
				PC_Deg_XZ = PC_Deg_XZ + float(0.30*(sys->MousePos.x - (sys->BeforeMousePos.x - sys->rewin.left)));
				Tm_DegQ_Y = Tm_DegQ_Y - 0.0020* float( sys->MousePos.y - sys->BeforeMousePos.y + sys->rewin.top);
	}

	if( ( MyState == 3) || ( MyState == 4)){//�������т̎���
				Tm_DegQ_Y = Tm_DegQ_Y - 0.0020* float( sys->MousePos.y - sys->BeforeMousePos.y + sys->rewin.top);
	}

	if( PC_Deg_XZ < 0){
				PC_Deg_XZ = PC_Deg_XZ + 360;
	}
	if( 360 < PC_Deg_XZ){
				PC_Deg_XZ = PC_Deg_XZ - 360;
	}
	if(Tm_DegQ_Y> 0.9){
				Tm_DegQ_Y = 0.9;
	}
	if(Tm_DegQ_Y< -0.5){
				Tm_DegQ_Y = -0.5;
	}

	SetCursorPos( sys->rewin.left + 320, sys->rewin.top + 240);//�}�E�X���W��^�񒆂�
	GetCursorPos( &sys->BeforeMousePos);//�}�E�X���W���i�[���܂�

	Cos_XZ = cos(4.8);//XZ���W�R�T�C���̎擾
	Sin_XZ = sin(4.8);//XZ���W�T�C���̎擾
	Sin_Y = sin(Tm_DegQ_Y);//Y���W�T�C���̎擾
	Cos_Y = cos(Tm_DegQ_Y);//Y���W�̃R�T�C���̎擾
	TurnPos.x = float(Cos_XZ * Cos_Y * 2000);//�����ׂ�������X���W
	TurnPos.y = float(Sin_Y * 2000);//�����ׂ�������Y���W���擾
	TurnPos.z = float(Sin_XZ * Cos_Y * 2000);//�����ׂ�������Z���W���擾


		//���ɍ��W���擾�����肵�ă��f���̃{�[���𑀍삵�܂�
	/*�L�����N�^�[���f���̕��������������܂�*/
	ech = E3DRotateInit( cha_hsid[0]);
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};

	/*���W���擾����*/
	ech = E3DGetPos( cha_hsid[0], &MyPos1);
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};

	/*���W�����_�ɂ���*/
	ech = E3DSetPos( cha_hsid[0], OriginPos);
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};

	/*�L�����N�^�[���f���́u������v�̍��W���擾���܂�*/
	ech = E3DGetCurrentBonePos( cha_hsid[0], bone[2], 1, &StomachPos);
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};



	WantDeg.x = float( TurnPos.x - StomachPos.x);//X���W�̌��������̃x�N�g�����擾
	WantDeg.y = float( TurnPos.y - StomachPos.y);//Y���W�̌��������̃x�N�g�����擾
	WantDeg.z = float( TurnPos.z - StomachPos.z);//Z���W�̌��������̃x�N�g�����擾

	/*�u��t�����v�����̃��[�V�����͂ǂ������ׂ܂�*/
	ech = E3DGetMotionFrameNoML( cha_hsid[0], bone[2], &MotionID, &FrameNo);
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};

	/*�u��t�����v�����̃N�H�[�^�j�I���𒲂ׂ܂�*/
	ech = E3DGetCurrentBoneQ( cha_hsid[0], bone[2], 2, Qid[3]);
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};

	/*�������������ւ̌v�Z���s���܂�*/
	ech = E3DLookAtQ( Qid[3], WantDeg, BaseVec, 0, 2);
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};

	/*�v�Z�����N�H�[�^�[�j�I���������܂�*/
	ech = E3DSetBoneQ( cha_hsid[0], bone[2], MotionID, FrameNo, Qid[3]);
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};

	/*�}���`���C���[���[�V�����̌v�Z���s���܂�*/
	ech = E3DCalcMLMotion( cha_hsid[0]);
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};

	/*�{���̎����̍��W�ɖ߂�*/
	ech = E3DSetPos( cha_hsid[0], MyPos1);
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};

	/*�L�����N�^�[����]�����܂�*/
	ech = E3DRotateY( cha_hsid[0], PC_Deg_XZ);
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};



  /*�J�����̈ʒu��ݒ肵�܂��A�ʒu�͎����̌��̌��ɐݒu���܂�*/

	/*�L�����N�^�[���f���́u������v�́I���I�̍��W���擾���܂�*/
	ech = E3DGetCurrentBonePos( cha_hsid[0], bone[2], 1, &StomachPos);
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};

	//��������ɃJ�������Z�b�g���܂�
	Cam->CamShoulderGunBack( Qid[3], PC_Deg_XZ, StomachPos);

	



	BatPre->SpriteData[0][2] = 320 - 16.0f;//�J�[�\����X���W
	BatPre->SpriteData[0][3] = 220 - 18.0f;//�J�[�\����Y���W

	ScreenPos[0] = 320;/**/ScreenPos[1] = 220;

	return 0;
}
/*�����̌����ׂ������𒲐߂�����A�ˌ������肷��֐�*/
int PlayerChara::GunConflictTarget( int ScreenPosArray[2], Stage *Stg, Enemy *Ene, Weapon *Wep){
    /*�L�����N�^�[���f����ǂ�����ΕǂɌ�����
	�Ȃ���Ώe�̍U�����͂��͈͂܂ł̋������擾���A�����Ɍ�����*/

	/*�ϐ��̏�����*/


	int NowWpKind = 0;//���̕���̎�ނ��擾���܂�
	int ech = 0;//�G���[�m�F�ϐ�
	int MotionID = 0;//ML����擾�������݂́u��t�����v���[�V����ID
	int FrameNo = 0;//ML����擾�������݂́u��t�����v���[�V���������ݍĐ����Ă���ԍ�
	int NearEnemyID = 0;//��ԋ߂��G�L�����̎��ʔԍ�
	int EnemyConflict = 0;//�G�ɓ����������̍��v
	int Wall_HitResult = 0;//�����蔻�胂�f�����ǂɓ������Ă��邩�ǂ������ׂ܂�
	int EneHitResult = 0;//�G���Ə��ɓ����Ă��邩�̌��ʂ����܂�
	int HitResult = 0;//�e����������������邩����܂����̌��ʂ����܂�
	float NowWpRange = 0.0f;//���̕���̎˒��������܂�
	float Wall_HitDistance = 0.0f;//���������ʂ̂Ƃ��납��̋������������܂�
	float EneDistance = 0.0f;//���������G�̂Ƃ��납��̋������������܂�
	float EneNearDistance = 0.0f;//�������Ă����ԋ߂��G�̋������������܂�
	D3DXVECTOR3 Wall_ReflectVec( 0.0, 0.0, 0.0);//�n�ʂ̔��˃x�N�g���̍\����
	D3DXVECTOR3 Wall_GunTargetPos( 0.0, 0.0, 0.0);//�e�������ׂ����W
	D3DXVECTOR3 ReflectVec( 0.0, 0.0, 0.0);//���˃x�N�g���̍\����
	D3DXVECTOR3 GunTargetPos( 0.0, 0.0, 0.0);//�e�������ׂ����W
	D3DXVECTOR3 WantVec( 0.0, 0.0, 0.0);//�u������v�̌������������ւ̃x�N�g��
	D3DXVECTOR3 BaseVec( 0.0, 0.0, -1.0);//�����̏��������x�N�g��
	D3DXVECTOR3 StomachPos( 0.0, 0.0, 0.0);//�u������v�̍��W
	D3DXVECTOR3 MyPos1( 0.0, 0.0, 0.0);//�ŏ������̍��W
	D3DXVECTOR3 OriginPos( 0.0, 0.0, 0.0);//�L�����N�^�[�������ׂ����_���W
	D3DXVECTOR3 GarbageD3DVec( 0.0, 0.0, 0.0);//�v��Ȃ�XYZ�̃f�[�^�̈ꎟ����
	POINT ScreenPos = { ScreenPosArray[0], ScreenPosArray[1]};//2D�X�N���[�����W�\����

	/*���������Ă��Ȃ��̂Ȃ�*/
	if( Wp_equipment != -1){

			NowWpKind = Wep->GetWeaponData( Wp_equipment, 0);
			NowWpRange = float( Wep->GetWeaponData( Wp_equipment, 4) * 500);
			EneNearDistance = float(NowWpRange);
	}


	  /*�ǂ̏e�擾���ǂ̂悤�ɂ��邩�w�肵�܂�*/

	/*�ʏ탂�[�h( ���f��[0]����擾���� )*/
	if( Stg->Stage_GunTarget == 0){
			ech = E3DPickFace( sys->scid1, Stg->Stage_hsid[0], ScreenPos, NowWpRange, &Wall_HitResult, &HitResult, &Wall_GunTargetPos, &Wall_ReflectVec, &Wall_HitDistance);
			if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
			};
	}


	if(Wp_equipment != -1){//������������Ƃ��Ă����
		/*����̎�ނ��A�n���h�K���ł����*/
		if((NowWpKind == 1) || (NowWpKind == 4)){
			
				/*�G5�ɂ������Ă��Ȃ����`�F�b�N���܂�*/
				for( int i = 0; i < 15; i++){//�G�l�~�[�̐�����
						if( Ene->Enemy_hsid[i] != 0){
									ech = E3DPickFace( sys->scid1, Ene->Enemy_hsid[i], ScreenPos, NowWpRange, &EneHitResult, &EneHitResult, &GarbageD3DVec, &GarbageD3DVec, &EneDistance);
									if(ech != 0 ){//�G���[�`�F�b�N
												_ASSERT( 0 );//�G���[�_�C�A���O
									};
									if( (EneHitResult != 0) && ( EneDistance < EneNearDistance) ){
												EneNearDistance = EneDistance;//��ԋ߂��G�̋����ɍX�V���܂�
												NearEnemyID = i;//��ԋ߂����f���ԍ������܂�
												EnemyConflict = 1;//�߂��G�����邱�Ƃ������܂�
												HitResult = 1;//�q�b�g�t���O��1�ɂ���
									}
						}
				}

				if( (EnemyConflict == 1) && ( Wall_HitDistance > EneNearDistance) ){//�G�ɏe���������
						ech = E3DPickFace( sys->scid1, Ene->Enemy_hsid[NearEnemyID], ScreenPos, NowWpRange, &EneHitResult, &EneHitResult, &GunTargetPos, &ReflectVec, &EneDistance);
						if(ech != 0 ){//�G���[�`�F�b�N
									_ASSERT( 0 );//�G���[�_�C�A���O
						};
				}
				else{//�ǂɏe���������
						GunTargetPos = Wall_GunTargetPos;
						ReflectVec = Wall_ReflectVec;
				}
			

				/*�ǂɓ������Ă����*/
				if( HitResult != -1){

						/*�u��t�����v�����̍��W���擾���܂�*/
						ech = E3DGetCurrentBonePos( cha_hsid[0], bone[2], 1, &StomachPos);
						if(ech != 0 ){//�G���[�`�F�b�N
									_ASSERT( 0 );//�G���[�_�C�A���O
						};

						WantVec.x =  GunTargetPos.x - StomachPos.x;
						WantVec.y =  GunTargetPos.y - StomachPos.y;
						WantVec.z =  GunTargetPos.z - StomachPos.z;

						/*�L�����N�^�[�̌��������������܂�*/
						ech = E3DRotateInit( cha_hsid[0]);
						if(ech != 0 ){//�G���[�`�F�b�N
									_ASSERT( 0 );//�G���[�_�C�A���O
						};

						/*�u��t�����v�����̃N�H�[�^�j�I���𒲂ׂ܂�*/
						ech = E3DGetCurrentBoneQ( cha_hsid[0], bone[2], 2, Qid[5]);
						if(ech != 0 ){//�G���[�`�F�b�N
									_ASSERT( 0 );//�G���[�_�C�A���O
						};

						/*�u��t�����v�����̃��[�V�����͂ǂ������ׂ܂�*/
						ech = E3DGetMotionFrameNoML( cha_hsid[0], bone[2], &MotionID, &FrameNo);
						if(ech != 0 ){//�G���[�`�F�b�N
									_ASSERT( 0 );//�G���[�_�C�A���O
						};

						/*�������������ւ̌v�Z���s���܂�*/
						ech = E3DLookAtQ( Qid[5], WantVec, BaseVec, 0, 0);
						if(ech != 0 ){//�G���[�`�F�b�N
									_ASSERT( 0 );//�G���[�_�C�A���O
						};

						/*�������������̏C���������܂�*/
						ech = E3DRotateQY( Qid[5], -(PC_Deg_XZ));
						if(ech != 0 ){//�G���[�`�F�b�N
									_ASSERT( 0 );//�G���[�_�C�A���O
						};

						/*�v�Z�����N�H�[�^�[�j�I���������܂�*/
						ech = E3DSetBoneQ( cha_hsid[0], bone[2], MotionID, FrameNo, Qid[5]);
						if(ech != 0 ){//�G���[�`�F�b�N
									_ASSERT( 0 );//�G���[�_�C�A���O
						};

						/*�}���`���C���[���[�V�����̌v�Z���s���܂�*/
						ech = E3DCalcMLMotion( cha_hsid[0]);
						if(ech != 0 ){//�G���[�`�F�b�N
									_ASSERT( 0 );//�G���[�_�C�A���O
						};

						/*�L�����N�^�[����]�����܂�*/
						ech = E3DRotateY( cha_hsid[0], PC_Deg_XZ);
						if(ech != 0 ){//�G���[�`�F�b�N
									_ASSERT( 0 );//�G���[�_�C�A���O
						};
			}
		}
	}




	return 0;
}
/*�L�����N�^�[�̌㏈�����s���֐��A���[�V������p���Ȃ�*/
int PlayerChara::ShoulderGunSysBefore( Weapon *Wep){

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

	if( MyState == 0){
			/**/
			/*�㔼�g�̃��[�V�����ݒ�*/

			if( Attitude == 0){//���Ⴊ�݃��[�h���I�t�Ȃ�
					if( Wp_equipment != -1){//����𑕔����Ă����ԂȂ�
						if( Wep->GetWeaponData( Wp_equipment, 0) == 1){//�n���h�K�������̂Ȃ�
										if( UpMotion == 0){//���ʂ̍\��

												/*���[�V�����œ����������̎w��*/
												MotionList[0] = bone[5];//�u���Ȃ��v�̃{�[�����w��
												MotionList[1] = 0;//�w��I��
							
												/*���[�V�����œ������Ȃ������̎w��*/
												NoMotionList[0] = 0;//�w��I��

												/*���[�V������ݒ肷��*/
												ech = E3DSetMOAEventNoML( cha_hsid[0], 4, MotionList, NoMotionList);//�n���h�K���\��
												if(ech != 0){//�G���[�`�F�b�N
															_ASSERT(0);//�G���[�_�C�A���O��\��
												};
										}
							}
							if( Wep->GetWeaponData( Wp_equipment, 0) == 4){//�A�T���g�����̂Ȃ�
										if( UpMotion == 0){//���ʂ̍\��
					
												/*���[�V�����œ����������̎w��*/
												MotionList[0] = bone[5];//�u���Ȃ��v�̃{�[�����w��
												MotionList[1] = 0;//�w��I��
							
												/*���[�V�����œ������Ȃ������̎w��*/
												NoMotionList[0] = 0;//�w��I��

												/*���[�V������ݒ肷��*/
												ech = E3DSetMOAEventNoML( cha_hsid[0], 3, MotionList, NoMotionList);//�n���h�K���\��
												if(ech != 0){//�G���[�`�F�b�N
															_ASSERT(0);//�G���[�_�C�A���O��\��
												};
										}
							}
					}
					else{//����𑕔����Ă��Ȃ���ԂȂ�
							/*���[�V�����œ����������̎w��*/
												/*���[�V�����œ����������̎w��*/
												MotionList[0] = bone[5];//�u���Ȃ��v�̃{�[�����w��
												MotionList[1] = 0;//�w��I��
							
												/*���[�V�����œ������Ȃ������̎w��*/
												NoMotionList[0] = 0;//�w��I��

												/*���[�V������ݒ肷��*/
												ech = E3DSetMOAEventNoML( cha_hsid[0], 3, MotionList, NoMotionList);//�n���h�K���\��
												if(ech != 0){//�G���[�`�F�b�N
															_ASSERT(0);//�G���[�_�C�A���O��\��
												};
					}
			}

			/**/
			if( Attitude == 1){//���Ⴊ�݃��[�h���I���Ȃ�
					if( Wp_equipment != -1){//����𑕔����Ă����ԂȂ�
							if( Wep->GetWeaponData( Wp_equipment, 0) == 1){//�n���h�K�������̂Ȃ�
										if( UpMotion == 0){//���ʂ̍\��

												/*���[�V�����œ����������̎w��*/
												MotionList[0] = bone[5];//�u���Ȃ��v�̃{�[�����w��
												MotionList[1] = 0;//�w��I��
							
												/*���[�V�����œ������Ȃ������̎w��*/
												NoMotionList[0] = 0;//�w��I��

												/*���[�V������ݒ肷��*/
												ech = E3DSetMOAEventNoML( cha_hsid[0], 4, MotionList, NoMotionList);//�n���h�K���\��
												if(ech != 0){//�G���[�`�F�b�N
															_ASSERT(0);//�G���[�_�C�A���O��\��
												};
										}
							}
							if( Wep->GetWeaponData( Wp_equipment, 0) == 4){//�A�T���g�����̂Ȃ�
										if( UpMotion == 0){//���ʂ̍\��
					
												/*���[�V�����œ����������̎w��*/
												MotionList[0] = bone[5];//�u���Ȃ��v�̃{�[�����w��
												MotionList[1] = 0;//�w��I��
							
												/*���[�V�����œ������Ȃ������̎w��*/
												NoMotionList[0] = 0;//�w��I��

												/*���[�V������ݒ肷��*/
												ech = E3DSetMOAEventNoML( cha_hsid[0], 3, MotionList, NoMotionList);//�n���h�K���\��
												if(ech != 0){//�G���[�`�F�b�N
															_ASSERT(0);//�G���[�_�C�A���O��\��
												};
										}
							}
					}
					else{//����𑕔����Ă��Ȃ���ԂȂ�
							/*���[�V�����œ����������̎w��*/
												/*���[�V�����œ����������̎w��*/
												MotionList[0] = bone[5];//�u���Ȃ��v�̃{�[�����w��
												MotionList[1] = 0;//�w��I��
							
												/*���[�V�����œ������Ȃ������̎w��*/
												NoMotionList[0] = 0;//�w��I��

												/*���[�V������ݒ肷��*/
												ech = E3DSetMOAEventNoML( cha_hsid[0], 3, MotionList, NoMotionList);//�n���h�K���\��
												if(ech != 0){//�G���[�`�F�b�N
															_ASSERT(0);//�G���[�_�C�A���O��\��
												};
					}
			}


			

			/*�z��ϐ��̏�����*/
			for( int i=0; i<10; i++){
					MotionList[i] = 0;//�������������w�肷��z���������
					NoMotionList[i] = 0;//�������Ȃ��������w�肷��z���������
			}

			/**/
			/*�����g�̃��[�V�����ݒ�*/
			if( Attitude == 0){//���Ⴊ�݃��[�h���I�t�Ȃ�
					if( UnderMotion == 0){//�~�܂�̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = bone[6];//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = bone[5];//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								ech = E3DSetMOAEventNoML( cha_hsid[0], 2, MotionList, NoMotionList);
								if(ech != 0){//�G���[�`�F�b�N
											_ASSERT(0);//�G���[�_�C�A���O��\��
								};
					}
					if( UnderMotion == 1){//�O�i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = bone[6];//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = bone[5];//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								ech = E3DSetMOAEventNoML( cha_hsid[0], 1, MotionList, NoMotionList);
								if(ech != 0){//�G���[�`�F�b�N
											_ASSERT(0);//�G���[�_�C�A���O��\��
								};
					}
					if( UnderMotion == 2){//�E�i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = bone[6];//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = bone[5];//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								ech = E3DSetMOAEventNoML( cha_hsid[0], 5, MotionList, NoMotionList);
								if(ech != 0){//�G���[�`�F�b�N
											_ASSERT(0);//�G���[�_�C�A���O��\��
								};
					}
					if( UnderMotion == 3){//���i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = bone[6];//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = bone[5];//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								ech = E3DSetMOAEventNoML( cha_hsid[0], 6, MotionList, NoMotionList);
								if(ech != 0){//�G���[�`�F�b�N
											_ASSERT(0);//�G���[�_�C�A���O��\��
								};
					}
					if( UnderMotion == 4){//���O�i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = bone[6];//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = bone[5];//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								ech = E3DSetMOAEventNoML( cha_hsid[0], 7, MotionList, NoMotionList);
								if(ech != 0){//�G���[�`�F�b�N
											_ASSERT(0);//�G���[�_�C�A���O��\��
								};
					}
					if( UnderMotion == 5){//�E�O�i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = bone[6];//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = bone[5];//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								ech = E3DSetMOAEventNoML( cha_hsid[0], 8, MotionList, NoMotionList);
								if(ech != 0){//�G���[�`�F�b�N
											_ASSERT(0);//�G���[�_�C�A���O��\��
								};
					}
					if( UnderMotion == 6){//����i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = bone[6];//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = bone[5];//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								ech = E3DSetMOAEventNoML( cha_hsid[0], 9, MotionList, NoMotionList);
								if(ech != 0){//�G���[�`�F�b�N
											_ASSERT(0);//�G���[�_�C�A���O��\��
								};
					}
					if( UnderMotion == 7){//�E��i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = bone[6];//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = bone[5];//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								ech = E3DSetMOAEventNoML( cha_hsid[0], 10, MotionList, NoMotionList);
								if(ech != 0){//�G���[�`�F�b�N
											_ASSERT(0);//�G���[�_�C�A���O��\��
								};
					}
					if( UnderMotion == 8){//��i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = bone[6];//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = bone[5];//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								ech = E3DSetMOAEventNoML( cha_hsid[0], 11, MotionList, NoMotionList);
								if(ech != 0){//�G���[�`�F�b�N
											_ASSERT(0);//�G���[�_�C�A���O��\��
								};
					}
					if( UnderMotion == 9){//�W�����v�ɂ���̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = bone[6];//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = bone[5];//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								ech = E3DSetMOAEventNoML( cha_hsid[0], 24, MotionList, NoMotionList);
								if(ech != 0){//�G���[�`�F�b�N
											_ASSERT(0);//�G���[�_�C�A���O��\��
								};
					}
			}

			/**/
			if( Attitude == 1){//���Ⴊ�݃��[�h���I���Ȃ�
					if( UnderMotion == 0){//�~�܂�̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = bone[6];//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = bone[5];//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								ech = E3DSetMOAEventNoML( cha_hsid[0], 13, MotionList, NoMotionList);
								if(ech != 0){//�G���[�`�F�b�N
											_ASSERT(0);//�G���[�_�C�A���O��\��
								};
					}
					if( UnderMotion == 1){//�O�i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = bone[6];//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = bone[5];//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								ech = E3DSetMOAEventNoML( cha_hsid[0], 14, MotionList, NoMotionList);
								if(ech != 0){//�G���[�`�F�b�N
											_ASSERT(0);//�G���[�_�C�A���O��\��
								};
					}
					if( UnderMotion == 2){//�E�i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = bone[6];//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = bone[5];//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								ech = E3DSetMOAEventNoML( cha_hsid[0], 16, MotionList, NoMotionList);
								if(ech != 0){//�G���[�`�F�b�N
											_ASSERT(0);//�G���[�_�C�A���O��\��
								};
					}
					if( UnderMotion == 3){//���i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = bone[6];//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = bone[5];//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								ech = E3DSetMOAEventNoML( cha_hsid[0], 17, MotionList, NoMotionList);
								if(ech != 0){//�G���[�`�F�b�N
											_ASSERT(0);//�G���[�_�C�A���O��\��
								};
					}
					if( UnderMotion == 4){//���O�i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = bone[6];//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = bone[5];//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								ech = E3DSetMOAEventNoML( cha_hsid[0], 19, MotionList, NoMotionList);
								if(ech != 0){//�G���[�`�F�b�N
											_ASSERT(0);//�G���[�_�C�A���O��\��
								};
					}
					if( UnderMotion == 5){//�E�O�i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = bone[6];//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = bone[5];//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								ech = E3DSetMOAEventNoML( cha_hsid[0], 18, MotionList, NoMotionList);
								if(ech != 0){//�G���[�`�F�b�N
											_ASSERT(0);//�G���[�_�C�A���O��\��
								};
					}
					if( UnderMotion == 6){//����i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = bone[6];//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = bone[5];//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								ech = E3DSetMOAEventNoML( cha_hsid[0], 21, MotionList, NoMotionList);
								if(ech != 0){//�G���[�`�F�b�N
											_ASSERT(0);//�G���[�_�C�A���O��\��
								};
					}
					if( UnderMotion == 7){//�E��i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = bone[6];//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = bone[5];//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								ech = E3DSetMOAEventNoML( cha_hsid[0], 20, MotionList, NoMotionList);
								if(ech != 0){//�G���[�`�F�b�N
											_ASSERT(0);//�G���[�_�C�A���O��\��
								};
					}
					if( UnderMotion == 8){//��i����̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = bone[6];//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = bone[5];//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								ech = E3DSetMOAEventNoML( cha_hsid[0], 15, MotionList, NoMotionList);
								if(ech != 0){//�G���[�`�F�b�N
											_ASSERT(0);//�G���[�_�C�A���O��\��
								};
					}
					if( UnderMotion == 9){//�W�����v�ɂ���̂Ȃ�

								/*���[�V�����œ����������̎w��*/
								MotionList[0] = bone[6];//�u�ړ���v�̃{�[�����w��
								MotionList[1] = 0;//�w��I��

								/*���[�V�����œ������Ȃ������̎w��*/
								NoMotionList[0] = bone[5];//�u���Ȃ��v�{�[�����w��
								NoMotionList[1] = 0;//�w��I��

								/*���[�V������ݒ肷��*/
								ech = E3DSetMOAEventNoML( cha_hsid[0], 26, MotionList, NoMotionList);
								if(ech != 0){//�G���[�`�F�b�N
											_ASSERT(0);//�G���[�_�C�A���O��\��
								};
					}
			}
	}
	if( MyState == 1){//�L�b�N�t���O���I���Ȃ�
			/*���[�V�����œ����������̎w��*/
			MotionList[0] = bone[6];//�u�ړ���v�̃{�[�����w��
			MotionList[1] = 0;//�w��I��

			/*���[�V�����œ������Ȃ������̎w��*/
			NoMotionList[0] = bone[5];//�u���Ȃ��v�{�[�����w��
			NoMotionList[1] = 0;//�w��I��

			/*���[�V������ݒ肷��*/
			ech = E3DSetMOAEventNoML( cha_hsid[0], 22, MotionList, NoMotionList);
			if(ech != 0){//�G���[�`�F�b�N
						_ASSERT(0);//�G���[�_�C�A���O��\��
			};
	}
	if( MyState == 2){//�_�b�V���t���O���I���Ȃ�
			if( AirOnPC == 0){//�W�����v���Ă��Ȃ��Ȃ�
					/*���[�V�����œ����������̎w��*/
					MotionList[0] = bone[6];//�u�ړ���v�̃{�[�����w��
					MotionList[1] = 0;//�w��I��

					/*���[�V�����œ������Ȃ������̎w��*/
					NoMotionList[0] = bone[5];//�u���Ȃ��v�{�[�����w��
					NoMotionList[1] = 0;//�w��I��

					/*���[�V������ݒ肷��*/
					ech = E3DSetMOAEventNoML( cha_hsid[0], 23, MotionList, NoMotionList);
					if(ech != 0){//�G���[�`�F�b�N
								_ASSERT(0);//�G���[�_�C�A���O��\��
					};
			}
			if( AirOnPC == 1){//�W�����v���Ă���̂Ȃ�
					/*���[�V�����œ����������̎w��*/
					MotionList[0] = bone[6];//�u�ړ���v�̃{�[�����w��
					MotionList[1] = 0;//�w��I��

					/*���[�V�����œ������Ȃ������̎w��*/
					NoMotionList[0] = bone[5];//�u���Ȃ��v�{�[�����w��
					NoMotionList[1] = 0;//�w��I��

					/*���[�V������ݒ肷��*/
					ech = E3DSetMOAEventNoML( cha_hsid[0], 25, MotionList, NoMotionList);
					if(ech != 0){//�G���[�`�F�b�N
								_ASSERT(0);//�G���[�_�C�A���O��\��
					};
			}
	}
	if( MyState == 3){//��������я�ԂȂ�
					/*���[�V�����œ����������̎w��*/
					MotionList[0] = bone[6];//�u�ړ���v�̃{�[�����w��
					MotionList[1] = 0;//�w��I��

					/*���[�V�����œ������Ȃ������̎w��*/
					NoMotionList[0] = bone[5];//�u���Ȃ��v�{�[�����w��
					NoMotionList[1] = 0;//�w��I��

					/*���[�V������ݒ肷��*/
					ech = E3DSetMOAEventNoML( cha_hsid[0], 27, MotionList, NoMotionList);
					if(ech != 0){//�G���[�`�F�b�N
								_ASSERT(0);//�G���[�_�C�A���O��\��
					};
	}
	if( MyState == 4){//�E������я�ԂȂ�
					/*���[�V�����œ����������̎w��*/
					MotionList[0] = bone[6];//�u�ړ���v�̃{�[�����w��
					MotionList[1] = 0;//�w��I��

					/*���[�V�����œ������Ȃ������̎w��*/
					NoMotionList[0] = bone[5];//�u���Ȃ��v�{�[�����w��
					NoMotionList[1] = 0;//�w��I��

					/*���[�V������ݒ肷��*/
					ech = E3DSetMOAEventNoML( cha_hsid[0], 12, MotionList, NoMotionList);
					if(ech != 0){//�G���[�`�F�b�N
								_ASSERT(0);//�G���[�_�C�A���O��\��
					};
	}



	/*�}���`���C���[�ɉ����ĐV���[�V�����𓖂Ă�*/
	ech = E3DSetNewPoseML( cha_hsid[0]);
	if(ech != 0){//�G���[�`�F�b�N
				_ASSERT(0);//�G���[�_�C�A���O��\��
	};

	/*�u��t�����v�����̃��[�V�����͂ǂ������ׂ܂�*/
	ech = E3DGetMotionFrameNoML( cha_hsid[0], bone[2], &MotionID, &FrameNo);
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};

	/*�v�Z�����N�H�[�^�[�j�I���������܂�*/
	ech = E3DSetBoneQ( cha_hsid[0], bone[2], MotionID, FrameNo, Qid[3]);
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};

	/*�}���`���C���[���[�V�����̌v�Z���s���܂�*/
	ech = E3DCalcMLMotion( cha_hsid[0]);
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};


	return 0;
}
/*���ʂ̃Q�[�����ł̏������s���֐��A�e��̏o������A�G�ւ̂�����A�e����ɒu���Ȃǁcetc*/
int PlayerChara::NormallyPCSystem( Stage *Stg, Batch_Preparat *BatPre, Enemy *Ene, Camera *Cam, Weapon *Wep){

	/*�ϐ��̏�����*/
	int ech = 0;
	int MotionID = 0;//���[�V����ID�����܂�
	int Garbage = 0;//�S�~�f�[�^�����܂�
	int MotionFrameNo = 0;//���[�V�����̃t���[���ԍ������܂�
	int ScreenPos[2] = { 0, 0};//�X�N���[�����W�z���������
	int keyin[20];//�L�[���z����쐬 

	/*�L�[���擾����*/
	sys->GetKeyData(keyin);

	/*�L�����N�^�[�𓮂���*/
	MoveChara();

	/*�L�����N�^�[��n�ʂɒu��*/
	MovePosOnGround( Stg);

	/*���_�֘A�̏����A�؂�ւ���֐��Ăяo����*/
	ShoulderGunSys( BatPre, Cam, ScreenPos);//���������_

	//�̂̌�����A�ˌ����s���֐����Ăяo��
	GunConflictTarget( ScreenPos, Stg, Ene, Wep);

	/*�G�ւ̓����蔻��̏���*/


	/*��������ύX�̏���*/
	if( sys->MouseWhole == 1){//�����A�}�E�X�z�C�[������֍s�����̂Ȃ�
		for(int i=0; i<3; i++){//
				Wp_equipment = Wp_equipment - 1;//����������J��グ��
				if( Wp_equipment == -1){//�������u�f��v�ɂȂ�����
						break;//���[�v���甲����A�f��Ɋm��
				}
				if( Wp_equipment == -2){//�������s���߂�����
						Wp_equipment = 1;//�������u�T�u�E�F�|���v�ɂ���
				}
				if( Wep->GetWeaponModelID( Wp_equipment, 0) != 0){//�����A���킪�m�F����Ă���Ȃ�
						break;//���[�v�𔲂���A�����m��
				}
		}
		BatPre->BacthGunTrade( Wp_equipment);//�`��A����p���`�F�b�N�̕���ύX
	}

	if( sys->MouseWhole == 2){//�����A�}�E�X�z�C�[�������֍s�����̂Ȃ�
		for(int i=0; i<3; i++){//
				Wp_equipment = Wp_equipment + 1;//����������J�艺����
				if( Wp_equipment == 2){//�������s���߂�����
						Wp_equipment = -1;//�������u�T�u�E�F�|���v�ɂ���
						break;//���[�v���甲����A�f��Ɋm��
				}
				if( Wep->GetWeaponModelID( Wp_equipment, 0) != 0){//�����A���킪�m�F����Ă���Ȃ�
						break;//���[�v�𔲂���A�����m��
				}
		}
		BatPre->BacthGunTrade( Wp_equipment);//�`��A����p���`�F�b�N�̕���ύX
	}

	/*�p���ϊ��u���̂��Ⴊ�ށv�̏���*/
	if( (keyin[8] == 1) && (AirOnPC == 0)){//�L�[��������A�󒆂łȂ�
				Attitude = Attitude + 1;//�p���ϐ�������₷
				if( Attitude == 2){//�ϐ����s���߂��Ȃ�
						Attitude = 0;//�u���v�ɌŒ�
				}
	}

	/*�i���U�������鏈�����s���܂�*/
	if( ( keyin[11] == 1) && ( Attitude == 0) && ( MyState == 0)){//�L�[��������A���Ⴊ�ݏ�ԂłȂ��A���̓�����s���ĂȂ�
				MyState = 1;//�L�b�N������
	}

	if( MyState == 1){//�L�b�N���Ȃ�
				ech = E3DGetMotionFrameNoML( cha_hsid[0], bone[6], &MotionID, &MotionFrameNo);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT(0);//�G���[�_�C�A���O
				}

				if( MotionFrameNo == 19){//���[�V�������I��������
							MyState = 0;//�����Ԃ�ʏ�ɖ߂�
				}
	}

	/*�_�b�V���֌W�̏������s���܂�*/
	if( ( sys->keyinQuick[1] == 1) && ( Attitude == 0) && ( MyState == 0) && ( AirOnPC == 0)){//�L�[���A���ŉ�����A���Ⴊ�ݏ�ԂłȂ��A���̓�����s���ĂȂ��āA�n��Ȃ�
				MyState = 2;//�_�b�V��������
	}

	if(( sys->keyinQuick[1] == 1) && (( Attitude != 0) || (( MyState != 0) && ( MyState != 2) ))){//����ȊO�̏����ł́A�_�b�V���L�����Z������
				sys->KeyQuickPush[1][2] = 0;//�_�b�V���L�[��������ĂȂ���Ԃɂ���
				sys->keyinQuick[1] = 0;//�Q�[���_�b�V���t���O���I�t�ɂ���
	}


	if( ( MyState == 2) && ( sys->keyinQuick[1] == 0) && ( AirOnPC == 0) ){//�_�b�V�����쒆�ŁA�L�[���������ꂽ��
				MyState = 0;//�_�b�V������������
	}

	if( MyState == 2){//�_�b�V�����Ȃ�
				Stamina = Stamina - 1;//�X�^�~�i�����炷
				if( (Stamina < 1) && (AirOnPC == 0) ){//�̗͂��Ȃ��Ȃ���&�󒆂łȂ��Ȃ�
						MyState = 0;//�_�b�V�����~�߂�
						sys->KeyQuickPush[1][2] = 0;//�_�b�V���L�[��������ĂȂ���Ԃɂ���
						sys->keyinQuick[1] = 0;//�Q�[���_�b�V���t���O���I�t�ɂ���
				}
	}

	/*������ъ֌W�̏������s���܂�*/
	if( ( ( sys->keyinQuick[0] == 1) || ( sys->keyinQuick[2] == 1)) && ( Attitude == 0) //���E�L�[���A���ŉ�����A���Ⴊ�ݏ�ԂłȂ��A
		&& ( MyState == 0) && ( AirOnPC == 0) && ( 0 < Stamina)){//���̓�����s���ĂȂ��āA�n��ŁA�X�^�~�i���Ȃ��Ȃ��ĂȂ��Ȃ�

				if( sys->keyinQuick[0] == 1) MyState = 3;//��������я�Ԃɂ���;
				if( sys->keyinQuick[2] == 1) MyState = 4;//�E������я�Ԃɂ���;
				if(( sys->keyinQuick[0] == 1) && ( sys->keyinQuick[2] == 1)) MyState = 0;//�ʏ��Ԃɂ���
	}

	//������я�ԂȂ�
	if( (MyState == 3) || ( MyState == 4)){
				//�ړ���̃��[�V������Ԃ͂ǂ����m���߂�
				ech = E3DGetMotionFrameNoML( cha_hsid[0], bone[6], &Garbage, &MotionFrameNo);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				Stamina = Stamina - 1;//�X�^�~�i�����炷

				if( MotionFrameNo == 20){//���[�V�������I�����Ă���
							MyState = 0;//�ʏ��Ԃɖ߂�
							sys->KeyQuickPush[0][2] = 0;//�_�b�V���L�[��������ĂȂ���Ԃɂ���
							sys->KeyQuickPush[2][2] = 0;//�_�b�V���L�[��������ĂȂ���Ԃɂ���
							sys->keyinQuick[0] = 0;//������уt���O���I�t�ɂ���
							sys->keyinQuick[2] = 0;//������уt���O���I�t�ɂ���
				}
	}

	/*�X�^�~�i�̐��������*/
	if( Stamina <= 0){//�X�^�~�i���}�C�i�X�Ȃ�
				Stamina = 0;//�X�^�~�i���Œ肷��
	}

	/*�����������̂���ׂ��ꏊ�ֈړ�������*/
	if( Wp_equipment != -1){
				GunPutOnHand( Wep);
	}



	return 0;

}