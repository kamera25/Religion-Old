/*�����ł́A�����N���X�̃L�����E�G�̊֐����`����N���X�R�[�h�t�@�C���ł��B
//���Ɍ����ړ��֌W�ŕK�v�Ȋ֐�������������Ă��܂��B
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "cstage.h"//�X�e�[�W�֌W�̃N���X�w�b�_�t�@�C��
#include "clive.h"//�G��L�����̃N���X�w�b�_�t�@�C��
#include "c_batch_preparat.h"//�`��ɕK�v�ȃN���X�̐錾�w�b�_�t�@�C��
#include <math.h>//���w�v�Z���g�����߂̃w�b�_�t�@�C��
#include "cweapon.h"//����Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��
#include "cenemy.h"//�G�N���X�̐錾�w�b�_�t�@�C��




/*���˂����_����̏e�֘A�܂Ƃߊ֐�*/
int PlayerChara::ShoulderGunSys( Batch_Render *BatPre, int ScreenPos[2]){

	/*�S�̂Ŏg���ϐ��̏�����*/
	int ech = 0;//�G���[�m�F�ϐ�
	const D3DXVECTOR3 BaseVec( 0.0, 0.0, -1.0);//�����̏��������x�N�g��
	const D3DXVECTOR3 CameraUpVec( 0.0, 1.0, 0.0);//�J�����̏㕔�̃x�N�g��

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
	D3DXVECTOR3 MyPos2( 0.0, 0.0, 0.0);//���̎����̍��W

	/**/
	//�����̌�������]�����܂��B
	/**/

	//�ŏ��ɉ�]�̌v�Z���܂�
	if(( Get_MyState() == 0) || ( (Get_MyState() == 2) && ( Get_AirOnPC() == 0))){//�ʏ�E�󒆃_�b�V�����[�h�łȂ���΁A�ȉ��擾����
				Set_PC_Deg_XZ( Get_PC_Deg_XZ() + float(0.30*(System::MousePos.x - (System::BeforeMousePos.x - System::rewin.left))) );
				Tm_DegQ_Y = Tm_DegQ_Y - 0.0020* float( System::MousePos.y - System::BeforeMousePos.y + System::rewin.top);
	}

	if( ( Get_MyState() == 3) || ( Get_MyState() == 4)){//�������т̎���
				Tm_DegQ_Y = Tm_DegQ_Y - 0.0020* float( System::MousePos.y - System::BeforeMousePos.y + System::rewin.top);
	}

	if( Get_PC_Deg_XZ() < 0){
				Set_PC_Deg_XZ( Get_PC_Deg_XZ() + 360);
	}
	if( 360 < Get_PC_Deg_XZ()){
				Set_PC_Deg_XZ( Get_PC_Deg_XZ() - 360);
	}
	if(Tm_DegQ_Y> 0.9){
				Tm_DegQ_Y = 0.9;
	}
	if(Tm_DegQ_Y< -0.6){
				Tm_DegQ_Y = -0.6;
	}

	SetCursorPos( System::rewin.left + 320, System::rewin.top + 240);//�}�E�X���W��^�񒆂�
	GetCursorPos( &System::BeforeMousePos);//�}�E�X���W���i�[���܂�

	Cos_XZ = cos(4.8);//XZ���W�R�T�C���̎擾
	Sin_XZ = sin(4.8);//XZ���W�T�C���̎擾
	Sin_Y = sin(Tm_DegQ_Y);//Y���W�T�C���̎擾
	Cos_Y = cos(Tm_DegQ_Y);//Y���W�̃R�T�C���̎擾
	TurnPos.x = float(Cos_XZ * Cos_Y * 2000);//�����ׂ�������X���W
	TurnPos.y = float(Sin_Y * 2000);//�����ׂ�������Y���W���擾
	TurnPos.z = float(Sin_XZ * Cos_Y * 2000);//�����ׂ�������Z���W���擾

	/**/
	//���ɍ��W���擾�����肵�ă��f���̃{�[���𑀍삵�܂�
	/**/

	/*�L�����N�^�[���f���̕��������������܂�*/
	ech = E3DRotateInit( Get_BodyModel());
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/*���W���擾����*/
	ech = E3DGetPos( Get_BodyModel(), &MyPos1);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/*�L�����N�^�[���f���́u������v�̍��W���擾���܂�*/
	ech = E3DGetCurrentBonePos( Get_BodyModel(), Get_Bone_ID(2), 1, &StomachPos);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	MyPos2.x = StomachPos.x * -1;
	MyPos2.y = StomachPos.y * -1;
	MyPos2.z = StomachPos.z * -1;

	/*���W�����_�ɂ���*/
	ech = E3DSetPos( Get_BodyModel(), MyPos2);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/*�L�����N�^�[���f���́u������v�̍��W���擾���܂�*/
	ech = E3DGetCurrentBonePos( Get_BodyModel(), Get_Bone_ID(2), 1, &StomachPos);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	WantDeg.x = float( TurnPos.x - 0);//X���W�̌��������̃x�N�g�����擾
	WantDeg.y = float( TurnPos.y - 0);//Y���W�̌��������̃x�N�g�����擾
	WantDeg.z = float( TurnPos.z - 0);//Z���W�̌��������̃x�N�g�����擾

	/*�u��t�����v�����̃��[�V�����͂ǂ������ׂ܂�*/
	ech = E3DGetMotionFrameNoML( Get_BodyModel(), Get_Bone_ID(2), &MotionID, &FrameNo);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/*�u��t�����v�����̃N�H�[�^�j�I���𒲂ׂ܂�*/
	ech = E3DGetCurrentBoneQ( Get_BodyModel(), Get_Bone_ID(2), 2, Get_Quaternion(3));
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/*�������������ւ̌v�Z���s���܂�*/
	ech = E3DLookAtQ( Get_Quaternion(3), WantDeg, BaseVec, 0, 2);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/*�v�Z�����N�H�[�^�[�j�I���������܂�*/
	ech = E3DSetBoneQ( Get_BodyModel(), Get_Bone_ID(2), MotionID, FrameNo, Get_Quaternion(3));
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/*�}���`���C���[���[�V�����̌v�Z���s���܂�*/
	ech = E3DCalcMLMotion( Get_BodyModel());
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/*�{���̎����̍��W�ɖ߂�*/
	ech = E3DSetPos( Get_BodyModel(), MyPos1);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/*�L�����N�^�[����]�����܂�*/
	ech = E3DRotateY( Get_BodyModel(), Get_PC_Deg_XZ());
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	
	/*�X�v���C�g�̈ʒu�����߂ďI�����܂�*/
	BatPre->SpriteData[0][2] = 320 - 16.0f;//�J�[�\����X���W
	BatPre->SpriteData[0][3] = 220 - 18.0f;//�J�[�\����Y���W

	ScreenPos[0] = 320;/**/ScreenPos[1] = 220;

	return 0;
}

/*�����̌����ׂ������𒲐߂�����A�ˌ������肷��֐�*/
int PlayerChara::GunConflictTarget( int ScreenPosArray[2], Stage *Stg, Enemy *Ene){
    
	
	/* /////////////////////////////////////////////////////// */
	// �L�����N�^�[���f����ǂ�����ΕǂɌ�����
	// �Ȃ���Ώe�̍U�����͂��͈͂܂ł̋������擾���A�����Ɍ�����
	/* /////////////////////////////////////////////////////// */

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

	/* ������������Ƃ��Ă���� */
	if( Get_Wp_equipment() != -1){

			NowWpKind = Wpn.Get_WeaponPointer( Get_Wp_equipment())->Get_Kind();
			NowWpRange = float( Wpn.Get_WeaponPointer( Get_Wp_equipment())->Get_Range() * 500);
			EneNearDistance = float(NowWpRange);
	}

	/* ///////////////////////////////////// */
	//�ǂ̏e�擾���ǂ̂悤�ɂ��邩�w�肵�܂� */
	/* //////////////////////////////////// */

	/*�ʏ탂�[�h( ���f��[0]����擾���� )*/
	if( Stg->Stage_GunTarget == 0){
			ech = E3DPickFace( System::scid1, Stg->Stage_hsid[0], ScreenPos, NowWpRange, &Wall_HitResult, &HitResult, &Wall_GunTargetPos, &Wall_ReflectVec, &Wall_HitDistance);
			_ASSERT( ech != 1 );//�G���[�`�F�b�N
	}


	if(Get_Wp_equipment() != -1){//������������Ƃ��Ă����
		/*����̎�ނ��A�n���h�K���ł����*/
		switch(NowWpKind){
				case 0:
				case 3:
				case 4:
				{
						/*�G�ɂ������Ă��Ȃ����`�F�b�N���܂�*/
						for( int i=0; i< Ene->EnemyNum; i++){//�G�l�~�[�̐�����
											ech = E3DPickFace( System::scid1, Ene->Ene[i]->Get_BodyModel(), ScreenPos, NowWpRange, &EneHitResult, &EneHitResult, &GarbageD3DVec, &GarbageD3DVec, &EneDistance);
											_ASSERT( ech != 1 );//�G���[�`�F�b�N
											if( (EneHitResult != 0) && ( EneDistance < EneNearDistance) ){
														EneNearDistance = EneDistance;//��ԋ߂��G�̋����ɍX�V���܂�
														NearEnemyID = i;//��ԋ߂����f���ԍ������܂�
														EnemyConflict = 1;//�߂��G�����邱�Ƃ������܂�
														HitResult = 1;//�q�b�g�t���O��1�ɂ���
											}
						}

						if( (EnemyConflict == 1) && ( Wall_HitDistance > EneNearDistance) ){//�G�ɏe���������
								ech = E3DPickFace( System::scid1, Ene->Ene[NearEnemyID]->Get_BodyModel(), ScreenPos, NowWpRange, &EneHitResult, &EneHitResult, &GunTargetPos, &ReflectVec, &EneDistance);
								_ASSERT( ech != 1 );//�G���[�`�F�b�N
						}
						else{//�ǂɏe���������
								GunTargetPos = Wall_GunTargetPos;
								ReflectVec = Wall_ReflectVec;
						}
			

						/*�ǂɓ������Ă����*/
						if( HitResult != -1){

								/*�u��t�����v�����̍��W���擾���܂�*/
								ech = E3DGetCurrentBonePos( Get_BodyModel(), Get_Bone_ID(2), 1, &StomachPos);
								_ASSERT( ech != 1 );//�G���[�`�F�b�N

								WantVec.x =  GunTargetPos.x - StomachPos.x;
								WantVec.y =  GunTargetPos.y - StomachPos.y;
								WantVec.z =  GunTargetPos.z - StomachPos.z;

								/*�L�����N�^�[�̌��������������܂�*/
								ech = E3DRotateInit( Get_BodyModel());
								_ASSERT( ech != 1 );//�G���[�`�F�b�N


								/*�u��t�����v�����̃N�H�[�^�j�I���𒲂ׂ܂�*/
								ech = E3DGetCurrentBoneQ( Get_BodyModel(), Get_Bone_ID(2), 2, Get_Quaternion(5));
								_ASSERT( ech != 1 );//�G���[�`�F�b�N

								/*�u��t�����v�����̃��[�V�����͂ǂ������ׂ܂�*/
								ech = E3DGetMotionFrameNoML( Get_BodyModel(), Get_Bone_ID(2), &MotionID, &FrameNo);
								_ASSERT( ech != 1 );//�G���[�`�F�b�N

								/*�������������ւ̌v�Z���s���܂�*/
								ech = E3DLookAtQ( Get_Quaternion(5), WantVec, BaseVec, 0, 0);
								_ASSERT( ech != 1 );//�G���[�`�F�b�N



								/*�������������̏C���������܂�*/
								ech = E3DRotateQY( Get_Quaternion(5), -(Get_PC_Deg_XZ()));
								_ASSERT( ech != 1 );//�G���[�`�F�b�N

								/*�v�Z�����N�H�[�^�[�j�I���������܂�*/
								ech = E3DSetBoneQ( Get_BodyModel(), Get_Bone_ID(2), MotionID, FrameNo, Get_Quaternion(5));
								_ASSERT( ech != 1 );//�G���[�`�F�b�N

								/*�}���`���C���[���[�V�����̌v�Z���s���܂�*/
								ech = E3DCalcMLMotion( Get_BodyModel());
								_ASSERT( ech != 1 );//�G���[�`�F�b�N

								/*�L�����N�^�[����]�����܂�*/
								ech = E3DRotateY( Get_BodyModel(), Get_PC_Deg_XZ());
								_ASSERT( ech != 1 );//�G���[�`�F�b�N
						}
				}
		}
	}
	else{
			/* ����������ĂȂ��Ƃ��̏����Ƃ�����\�� */
	}


	return 0;
}