/*�����ł́A�����N���X�̃L�����̊֐����`����N���X�R�[�h�t�@�C���ł��B
//�ʏ퓮��Ɋ֌W���鎞�ɕK�v�Ȋ֐�������������Ă��܂��B
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "clive.h"//�G��L�����̐錾�w�b�_�t�@�C��
#include "cenemy.h"//�G�N���X�̐錾�w�b�_�t�@�C��
#include "cweapon.h"//����N���X�̐錾�w�b�_�t�@�C��
#include "cstage.h"//�X�e�[�W�֌W�̃N���X�w�b�_�t�@�C��
#include "c_batch_preparat.h"//�`��ɕK�v�ȃN���X�̐錾�w�b�_�t�@�C��
#include "ccamera.h"//�J�����֌W�̃N���X�w�b�_�t�@�C��




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

	/*������������Ƃ��Ă����*/
	if( Wp_equipment != -1){

			NowWpKind = Wep->GetWeaponData( Wp_equipment, 0);
			NowWpRange = float( Wep->GetWeaponData( Wp_equipment, 4) * 500);
			EneNearDistance = float(NowWpRange);
	}

	/**/
	//�ǂ̏e�擾���ǂ̂悤�ɂ��邩�w�肵�܂�*/
	/**/

	/*�ʏ탂�[�h( ���f��[0]����擾���� )*/
	if( Stg->Stage_GunTarget == 0){
			ech = E3DPickFace( System::scid1, Stg->Stage_hsid[0], ScreenPos, NowWpRange, &Wall_HitResult, &HitResult, &Wall_GunTargetPos, &Wall_ReflectVec, &Wall_HitDistance);
			if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
			};
	}


	if(Wp_equipment != -1){//������������Ƃ��Ă����
		/*����̎�ނ��A�n���h�K���ł����*/
		if((NowWpKind == 1) || (NowWpKind == 4)){
			
				/*�G�ɂ������Ă��Ȃ����`�F�b�N���܂�*/
				for( int i = 0; i < 15; i++){//�G�l�~�[�̐�����
						if( Ene->Enemy_hsid[i] != 0){
									ech = E3DPickFace( System::scid1, Ene->Enemy_hsid[i], ScreenPos, NowWpRange, &EneHitResult, &EneHitResult, &GarbageD3DVec, &GarbageD3DVec, &EneDistance);
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
						ech = E3DPickFace( System::scid1, Ene->Enemy_hsid[NearEnemyID], ScreenPos, NowWpRange, &EneHitResult, &EneHitResult, &GunTargetPos, &ReflectVec, &EneDistance);
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
		else{



		}
	}




	return 0;
}
/*���ʂ̃Q�[�����ł̏������s���֐��A�e��̏o������A�G�ւ̂�����A�e����ɒu���Ȃǁcetc*/
int PlayerChara::NormallyPCSystem( Stage *Stg, Batch_Preparat *BatPre, Enemy *Ene, Camera *Cam, Weapon *Wep, int ScreenPos[2]){

	/*�ϐ��̏�����*/
	int ech = 0;
	int MotionID = 0;//���[�V����ID�����܂�
	int Garbage = 0;//�S�~�f�[�^�����܂�
	int MotionFrameNo = 0;//���[�V�����̃t���[���ԍ������܂�
	int keyin[20];//�L�[���z����쐬 

	/*�L�[���擾����*/
	System::GetKeyData(keyin);

	/*�L�����N�^�[�𓮂���*/
	MoveChara();

	/*�L�����N�^�[��n�ʂɒu��*/
	MovePosOnGround( Stg);

	/*���_�֘A�̏����A�؂�ւ���֐��Ăяo����*/
	ShoulderGunSys( BatPre, ScreenPos);//���������_
	/**/
	//�J�����̈ʒu��ݒ肵�܂��A�ʒu�͎����̌��̌��ɐݒu���܂�
	/**/

	//��������ɃJ�������Z�b�g���܂�
	Cam->CamShoulderGunBack( cha_hsid[0], Qid[3], bone[2], PC_Deg_XZ, Stg);



	//�̂̌�����A�ˌ����s���֐����Ăяo��
	GunConflictTarget( ScreenPos, Stg, Ene, Wep);

	/*�G�ւ̓����蔻��̏���*/


	/*��������ύX�̏���*/
	if( Wep->GetWeaponRapidFire() == 0){// ����U���\�Ȃ�
		if( System::MouseWhole == 1){//�����A�}�E�X�z�C�[������֍s�����̂Ȃ�
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

		if( System::MouseWhole == 2){//�����A�}�E�X�z�C�[�������֍s�����̂Ȃ�
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
	if( ( System::keyinQuick[1] == 1) && ( Attitude == 0) && ( MyState == 0) && ( AirOnPC == 0)){//�L�[���A���ŉ�����A���Ⴊ�ݏ�ԂłȂ��A���̓�����s���ĂȂ��āA�n��Ȃ�
				MyState = 2;//�_�b�V��������
	}

	if(( System::keyinQuick[1] == 1) && (( Attitude != 0) || (( MyState != 0) && ( MyState != 2) ))){//����ȊO�̏����ł́A�_�b�V���L�����Z������
				System::KeyQuickPush[1][2] = 0;//�_�b�V���L�[��������ĂȂ���Ԃɂ���
				System::keyinQuick[1] = 0;//�Q�[���_�b�V���t���O���I�t�ɂ���
	}


	if( ( MyState == 2) && ( System::keyinQuick[1] == 0) && ( AirOnPC == 0) ){//�_�b�V�����쒆�ŁA�L�[���������ꂽ��
				MyState = 0;//�_�b�V������������
	}

	if( MyState == 2){//�_�b�V�����Ȃ�
				Stamina = Stamina - 1;//�X�^�~�i�����炷
				if( (Stamina < 1) && (AirOnPC == 0) ){//�̗͂��Ȃ��Ȃ���&�󒆂łȂ��Ȃ�
						MyState = 0;//�_�b�V�����~�߂�
						System::KeyQuickPush[1][2] = 0;//�_�b�V���L�[��������ĂȂ���Ԃɂ���
						System::keyinQuick[1] = 0;//�Q�[���_�b�V���t���O���I�t�ɂ���
				}
	}

	/*������ъ֌W�̏������s���܂�*/
	if( ( ( System::keyinQuick[0] == 1) || ( System::keyinQuick[2] == 1)) && ( Attitude == 0) //���E�L�[���A���ŉ�����A���Ⴊ�ݏ�ԂłȂ��A
		&& ( MyState == 0) && ( AirOnPC == 0) && ( 0 < Stamina)){//���̓�����s���ĂȂ��āA�n��ŁA�X�^�~�i���Ȃ��Ȃ��ĂȂ��Ȃ�

				if( System::keyinQuick[0] == 1) MyState = 3;//��������я�Ԃɂ���;
				if( System::keyinQuick[2] == 1) MyState = 4;//�E������я�Ԃɂ���;
				if(( System::keyinQuick[0] == 1) && ( System::keyinQuick[2] == 1)) MyState = 0;//�ʏ��Ԃɂ���
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
							System::KeyQuickPush[0][2] = 0;//�_�b�V���L�[��������ĂȂ���Ԃɂ���
							System::KeyQuickPush[2][2] = 0;//�_�b�V���L�[��������ĂȂ���Ԃɂ���
							System::keyinQuick[0] = 0;//������уt���O���I�t�ɂ���
							System::keyinQuick[2] = 0;//������уt���O���I�t�ɂ���
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