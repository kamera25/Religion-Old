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
#include "cMission.h"


int PlayerChara::ThreePersonGunSys( Batch_Render *BatPre, int ScreenPos[2]){

	/*�S�̂Ŏg���ϐ��̏�����*/
	int ech = 0;//�G���[�m�F�ϐ�
	const D3DXVECTOR3 BaseVec( 0.0, 0.0, -1.0);//�����̏��������x�N�g��
	const D3DXVECTOR3 CameraUpVec( 0.0, 1.0, 0.0);//�J�����̏㕔�̃x�N�g��

	/*�L�����N�^�[�̈ʒu��ݒ肵�܂�*/
	int MotionID = 0;//ML����擾�������݂́u��t�����v���[�V����ID
	int FrameNo = 0;//ML����擾�������݂́u��t�����v���[�V���������ݍĐ����Ă���ԍ�
	static double Tm_DegQ_Y = 0.50;//�u��������O�̊p�x�ϐ�Y
	double Sin_Y = 0.0;//Y���W�T�C���ϐ�
	const  double Sin_XZ = sin(4.8);//XZ���W�T�C���ϐ�
	double Cos_Y = 0.0;//Y���W�R�T�C���ϐ�
	const double Cos_XZ = cos(4.8);//XZ���W�R�T�C���ϐ�
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

				if( ( System::MousePos.x < 100) || (  580< System::MousePos.x)){

						Set_PC_Deg_XZ( Get_PC_Deg_XZ() + float(0.30*(System::MousePos.x - System::BeforeMousePos.x) ));
						System::SetMouseCursol( System::BeforeMousePos.x, System::BeforeMousePos.y);// �}�E�X���W��^�񒆂�

				}
				Tm_DegQ_Y = Tm_DegQ_Y - 0.0020* float( System::MousePos.y - System::BeforeMousePos.y);
	}

	if( ( Get_MyState() == 3) || ( Get_MyState() == 4)){//�������т̎���
				Tm_DegQ_Y = Tm_DegQ_Y - 0.0020* float( System::MousePos.y - System::BeforeMousePos.y);
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



	Sin_Y = sin(Tm_DegQ_Y);//Y���W�T�C���̎擾
	Cos_Y = cos(Tm_DegQ_Y);//Y���W�̃R�T�C���̎擾
	TurnPos.x = float(Cos_XZ * Cos_Y * 2000);//�����ׂ�������X���W
	TurnPos.y = float(Sin_Y * 2000);//�����ׂ�������Y���W���擾
	TurnPos.z = float(Sin_XZ * Cos_Y * 2000);//�����ׂ�������Z���W���擾

	/**/
	//���ɍ��W���擾�����肵�ă��f���̃{�[���𑀍삵�܂�
	/**/
	System::SetMouseBeforePos();// �}�E�X���W���i�[���܂�


	/*�L�����N�^�[���f���̕��������������܂�*/
	Act->RotateInit();
	//ech = E3DRotateInit( Get_BodyModel());
	//_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/*���W���擾����*/
	MyPos1 = Act->GetPos();
	//ech = E3DGetPos( Get_BodyModel(), &MyPos1);
	//_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/*�L�����N�^�[���f���́u������v�̍��W���擾���܂�*/
	StomachPos = Act->BonePos( "��t����");
	//ech = E3DGetCurrentBonePos( Get_BodyModel(), Get_Bone_ID(2), 1, &StomachPos);
	//_ASSERT( ech != 1 );//�G���[�`�F�b�N

	MyPos2.x = StomachPos.x * -1;
	MyPos2.y = StomachPos.y * -1;
	MyPos2.z = StomachPos.z * -1;

	/*���W�����_�ɂ���*/
	Act->SetPos( MyPos2);
	//ech = E3DSetPos( Get_BodyModel(), MyPos2);
	//_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/*�L�����N�^�[���f���́u������v�̍��W���擾���܂�*/
	Act->BonePos( "�����");
	//ech = E3DGetCurrentBonePos( Get_BodyModel(), Get_Bone_ID(2), 1, &StomachPos);
	//_ASSERT( ech != 1 );//�G���[�`�F�b�N

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
	Act->SetPos( MyPos1);
	//ech = E3DSetPos( Get_BodyModel(), MyPos1);
	//_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/*�L�����N�^�[����]�����܂�*/
	Act->RotateY( Get_PC_Deg_XZ());
	//ech = E3DRotateY( Get_BodyModel(), Get_PC_Deg_XZ());
	//_ASSERT( ech != 1 );//�G���[�`�F�b�N




	BatPre->Set_SpriteX( "Cursol1", System::MousePos.x - 25.0f);//�J�[�\����X���W
	BatPre->Set_SpriteY( "Cursol1", System::MousePos.y - 48.0f);//�J�[�\����Y���W
	ScreenPos[0] = System::MousePos.x;/**/ScreenPos[1] = System::MousePos.y;


	return 0;
}

// �_�b�V���֌W�̏������s���܂�
int PlayerChara::PCDashControl()
{


	/* //////////////////////////// */
	/* �_�b�V���֌W�̏������s���܂� */
	/* //////////////////////////// */

	//�L�[���A���ŉ�����A���Ⴊ�ݏ�ԂłȂ��A���̓�����s���ĂȂ��āA�n��Ȃ�
	if( ( System::Get_DoublePush(0) == 1) && ( Get_Attitude() == 0) 
		&& ( Get_MyState() == 0) && ( Get_AirOnPC() == 0)){
			Set_MyState( People::RUN );//�_�b�V��������
	}



	// �_�b�V�����쒆�ŁA�L�[���������ꂽ��
	if( ( Get_MyState() == 2) && ( System::Get_DoublePush(0) == 0) 
		&& ( Get_AirOnPC() == 0) ){
			Set_MyState( People::NORMAL );//�_�b�V������������
	}

	if( Get_MyState() == People::RUN){//�_�b�V�����Ȃ�
				Set_Stamina( Get_Stamina() - 1);//�X�^�~�i�����炷
				if( (Get_Stamina() == 0) && (Get_AirOnPC() == 0) ){//�̗͂��Ȃ��Ȃ���&�󒆂łȂ��Ȃ�
						Set_MyState( People::NORMAL);//�_�b�V�����~�߂�

						//�_�b�V���L�[��������ĂȂ���Ԃɂ���
						System::ResetKeyDoublePush(0);
				}
	}

	return 0;
}

/* ������т̏����������܂��B */
int PlayerChara::PCSideAvoidanceControl(){

	/* ������ */
	int ech;
	int Garbage;
	int MotionFrameNo;


	/* //////////////////////////// */
	/* ������ъ֌W�̏������s���܂� */
	/* //////////////////////////// */
	if( ( ( System::Get_DoublePush(2) == 1) || ( System::Get_DoublePush(1) == 1)) && ( Get_Attitude() == 0) //���E�L�[���A���ŉ�����A���Ⴊ�ݏ�ԂłȂ��A
		&& ( Get_MyState() == People::NORMAL) && ( Get_AirOnPC() == 0) && ( 0 < Get_Stamina())){//���̓�����s���ĂȂ��āA�n��ŁA�X�^�~�i���Ȃ��Ȃ��ĂȂ��Ȃ�

				if( System::Get_DoublePush(2) == 1) Set_MyState( People::LEFT_SJUMP );//��������я�Ԃɂ���;
				if( System::Get_DoublePush(1) == 1) Set_MyState( People::RIGHT_SJUMP );//�E������я�Ԃɂ���;
				if(( System::Get_DoublePush(2) == 1) && ( System::Get_DoublePush(1) == 1)) Set_MyState( People::NORMAL );//�ʏ��Ԃɂ���
	}

	/* //////////////// */
	/* ������я�ԂȂ� */
	/* //////////////// */
	if( (Get_MyState() == People::LEFT_SJUMP) || ( Get_MyState() == People::RIGHT_SJUMP)){
				//�ړ���̃��[�V������Ԃ͂ǂ����m���߂�
				ech = E3DGetMotionFrameNoML( Get_BodyModel(), Get_Bone_ID(6), &Garbage, &MotionFrameNo);
				_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

				Set_Stamina( Get_Stamina() - 1);//�X�^�~�i�����炷

				if( MotionFrameNo == 20){//���[�V�������I�����Ă���
							Set_MyState( People::NORMAL );//�ʏ��Ԃɖ߂�
							System::ResetKeyDoublePush(1);
							System::ResetKeyDoublePush(2);
				}
	}



	return 0;
}

/*���ʂ̃Q�[�����ł̏������s���֐��A�e��̏o������A�G�ւ̂�����A�e����ɒu���Ȃǁcetc*/
int PlayerChara::NormallyPCSystem( Stage *Stg, Batch_Render *BatPre, NPC_Head *NPC_H, Camera *Cam, int ScreenPos[2]){

	/*�ϐ��̏�����*/
	int ech = 0;
	int MotionID = 0;//���[�V����ID�����܂�
	int Garbage = 0;//�S�~�f�[�^�����܂�
	int MotionFrameNo = 0;//���[�V�����̃t���[���ԍ������܂�


	/*�L�����N�^�[�𓮂���*/
	MoveChara();

	/*�L�����N�^�[��n�ʂɒu��*/
	MovePosOnGround( Stg);


	switch(ChangePerspectiveMode){
			case 0:{
					/*���_�֘A�̏����A�؂�ւ���֐��Ăяo����*/
					ThreePersonGunSys( BatPre, ScreenPos);//���������_

					break;		
			}
			case 1:{// ���������[�h

					/*���_�֘A�̏����A�؂�ւ���֐��Ăяo����*/
					ShoulderGunSys( BatPre, ScreenPos);//���������_

					//��������ɃJ�������Z�b�g���܂�
					Cam->CamShoulderGunBack( Get_BodyModel(), Get_Quaternion(3), Get_Bone_ID(2), Get_PC_Deg_XZ(), Stg);

					break;
			}
	}


	//�̂̌�����A�ˌ����s���֐����Ăяo��
	GunConflictTarget( ScreenPos, Stg, NPC_H);

	// �����ύX����ۂ̏���
	ChangeWeapon( BatPre);

	/*�p���ϊ��u���̂��Ⴊ�ށv�̏���*/
	if( ( System::GetKeyData( System::KEY_SHIFT) == 1) && (Get_AirOnPC() == 0)){//�L�[��������A�󒆂łȂ�
				Set_Attitude( Get_Attitude() + 1);//�p���ϐ�������₷
				if( Get_Attitude() == 2){//�ϐ����s���߂��Ȃ�
						Set_Attitude( 0 );//�u���v�ɌŒ�
				}
	}

	/* //////////////////////////// */
	/* �i���U�������鏈�����s���܂� */
	/* //////////////////////////// */
	if( ( System::GetKeyData( System::KEY_SPACE) == 1) && ( Get_Attitude() == 0) && ( Get_MyState() == 0)){//�L�[��������A���Ⴊ�ݏ�ԂłȂ��A���̓�����s���ĂȂ�
		Set_MyState( People::KICK );//�L�b�N������
	}

	if( Get_MyState() == 1){//�L�b�N���Ȃ�
				ech = E3DGetMotionFrameNoML( Get_BodyModel(), Get_Bone_ID(6), &MotionID, &MotionFrameNo);
				_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

				if( MotionFrameNo == 19){//���[�V�������I��������
					Set_MyState( People::NORMAL );//�����Ԃ�ʏ�ɖ߂�
				}
	}


	/* �_�b�V���֌W�̏������s���܂� */
	PCDashControl();

	/*������ъ֌W�̏������s���܂�*/
	PCSideAvoidanceControl();



	/* ���_�ς��̐؂�ւ�������s�� */
	if( System::GetKeyData( System::KEY_WHILEMOUSE) == 1){// �z�C�[���N���b�N�������ꂽ��
				ChangePerspectiveMode++;// ���_���[�h��i�߂�
				if( ChangePerspectiveMode == 2){// ���_���s���߂�����
						ChangePerspectiveMode = 0;
				}
	}


	/*�����������̂���ׂ��ꏊ�ֈړ�������*/
	GunPutOnHand();




	return 0;

}
/*�����ύX���邳����ۂɎg�p����֐�*/
int PlayerChara::ChangeWeapon( Batch_Render *BatPre){

	/* �ϐ��̐錾&������ */
	const int EQIPMENT = Get_Wp_equipment();


	/*��������ύX�̏���*/
	if( EQIPMENT != -1){//���݂̏�Ԃ����펝��
			if( Wpn.Get_WeaponPointer( EQIPMENT)->Get_NowFireFlag() != 0){// ���킪�����s���ԂȂ�
							return -1;//�ύX�͂ł��܂���B
			}
	}


	/* //////////////// */
	// ����̕ύX���s��
	/* //////////////// */
	switch(System::MouseWhole){
			case 1:{
					if( Get_Wp_equipment() == 3){
							Set_Wp_equipment(-1);//�������u�f��v�ɂ���
							break;
					}

					for(int i=0; i<3; i++){//
							Set_Wp_equipment( Get_Wp_equipment() - 1);//����������J��グ��
							if( Get_Wp_equipment() == -1){//�������u�f��v�ɂȂ�����
									break;//���[�v���甲����A�f��Ɋm��
							}
							if( Get_Wp_equipment() == -2){//�������s���߂�����
									Set_Wp_equipment(2);//�������u�O���l�[�h�v�ɂ���
							}
							if( Wpn.Get_WeaponPointer( Get_Wp_equipment()) != 0){//�����A���킪�m�F����Ă���Ȃ�
									break;//���[�v�𔲂���A�����m��
							}
					}

					break;
			}
			case 2:{//�����A�}�E�X�z�C�[�������֍s�����̂Ȃ�
					if( Get_Wp_equipment() == 3){
							Set_Wp_equipment(-1);//�������u�f��v�ɂ���
							break;
					}

					for(int i=0; i<3; i++){//
								Set_Wp_equipment( Get_Wp_equipment() + 1);//����������J�艺����
								if( Get_Wp_equipment() == 3){//�������s���߂�����
										Set_Wp_equipment(-1);//�������u�f��v�ɂ���
										break;//���[�v���甲����A�f��Ɋm��
								}
								if( Wpn.Get_WeaponPointer( Get_Wp_equipment()) != 0){//�����A���킪�m�F����Ă���Ȃ�
										break;//���[�v�𔲂���A�����m��
								}
					}
							
					break;
			}
	}

	/* ///////////////////////// */
	// �T�|�[�g����̕ύX���s���܂�
	/* ///////////////////////// */

	/* �T�|�[�g����ւ̕ύX�m�F�ƕύX���s�� */
	//if( ( keyin[10] == 1) && ( Wpn.Get_WeaponPointer(2) != NULL)){//�E�N���b�N�ƃT�|�[�g������������Ă����
	//		Set_Wp_equipment(2);// �T�|�[�g����ɑ����m��
	//}

	/* �T�|�[�g����𑕔����Ă���Ƃ��ɁA���N���b�N�������Ƃ� */
	//if( ( Get_Wp_equipment() == 2) && ( System::GetKeyData( System::KEY_LEFTMOUSE)) ){
	//		Set_Wp_equipment(-1);//�������u�f��v�ɂ���
	//}

	// �`��A����p���`�F�b�N�̕���ύX
	if( EQIPMENT != Get_Wp_equipment()){
			BatPre->BacthGunTrade( Get_Wp_equipment());
	}




	return 0;
}

/* �L�����N�^�̓����X�s�[�h��ݒ�A�������܂� */
float PlayerChara::RegulateMoveSpeed( float Acceleration, float FixedMoveSpeed, float LimitSpeed)
{
	/* ������ */
	float TempSpeed = (float)Get_MoveSpeed();

	/* ���x�����葬�x���x����� */
	if( TempSpeed <= FixedMoveSpeed)
	{
		TempSpeed = FixedMoveSpeed;
	}

	if( LimitSpeed < TempSpeed){
		TempSpeed = TempSpeed - 1 * abs(Acceleration);
	}
	else
	{
		TempSpeed = TempSpeed + Acceleration;
	}
	



	
	/* �X�s�[�h�ɐ����������� */
	if( LimitSpeed - Acceleration/2.0f <= TempSpeed 
		&& TempSpeed <= LimitSpeed + Acceleration/2.0f)
	{
		TempSpeed = LimitSpeed;
	}
	else if( -1 * abs(Acceleration) + 0.0f <= TempSpeed
		&& TempSpeed <= 0.0f + abs(Acceleration))
	{
		TempSpeed =  0.0f;
	}


	Set_MoveSpeed( TempSpeed);

	return TempSpeed;

	///* ������ */
	//float SumSpeed = 0.0f;
	////.....

	///*�X�s�[�h�𑝉�������*/
	//Set_MoveSpeed( Get_MoveSpeed() + Speed);
	//if( )
	//{

	//}


	////
	//if( LimitSpeed - Speed/2.0f <= Get_MoveSpeed() && Get_MoveSpeed() <= LimitSpeed + Speed/2.0f )
	//{
	//	Set_MoveSpeed( LimitSpeed);
	//}
	//else if( Get_MoveSpeed() <= 0.0f)
	//{
	//	Set_MoveSpeed( 0.0f);
	//}

	//SumSpeed = FixedMoveSpeed + Get_MoveSpeed();

	//return float( SumSpeed );
}

/*�L�����𓮂����܂��A�O�㍶�E�ɓ����܂�*/
int PlayerChara::MoveChara(){

	/*�ϐ��̏�����*/
	int ech = 0;//�G���[�m�F�ϐ�
	int KeyMov = 0;//�L�[�������Ăǂ̕����ɓ������̕ϐ�
	int MovOn = 0;//�����Ă������̃t���O
	static float WantDeg = 0;//�������������̕ϐ�
	float FixedMoveSpeed = 0.0f;//���ꂼ��̏�Ԃ̌Œ葬�x
	float SumSpeed = 0.0f;// ���v�̑��� 
	//D3DXVECTOR3 SubPos( 0.0, 0.0, 0.0);//�L�����N�^�[��u���ꏊ�̍��W
	//D3DXVECTOR3 PCPos( 0.0, 0.0, 0.0);//�v���C���[�L�����N�^�[�̈ʒu�̍��W

	/*�_�b�V�����삪�I���ɂȂ��Ă��Ȃ����`�F�b�N*/

	/* �L�[�̏�Ԃ��擾���� */
	if( System::GetKeyData( System::KEY_A) == 1){//��
				KeyMov = KeyMov +1;
	}
	if( System::GetKeyData( System::KEY_W) == 1){//��
				KeyMov = KeyMov +2;
	}
	if( System::GetKeyData( System::KEY_D) == 1){//�E
				KeyMov = KeyMov +4;
	}
	if( System::GetKeyData( System::KEY_S) == 1){//��
				KeyMov = KeyMov +8;
	}

	/*�L�[����擾��������ϊ�*/
	switch(KeyMov){//��
		case 1:{
				WantDeg = -90.0f + Get_PC_Deg_XZ();
				MovOn = 1;

				/*���[�V�������u�������v�ɂ���*/
				Set_UnderMotion(3);
				break;
		}
		case 2:{//��
				WantDeg = Get_PC_Deg_XZ(); 
				MovOn = 1;

				/*���[�V�������u���s�v�ɂ���*/
				Set_UnderMotion(1);//�ʏ�
				break;
		}
		case 3:{//����
				WantDeg = -45.0f + Get_PC_Deg_XZ(); 
				MovOn = 1;

				/*���[�V�������u���O�i�v�ɂ���*/
				Set_UnderMotion(4);
				break;
		}
		case 4:{//�E
				WantDeg = 90.0f + Get_PC_Deg_XZ(); 
				MovOn = 1;

				/*���[�V�������u�E�����v�ɂ���*/
				Set_UnderMotion(2);
				break;
		}
		case 6:{//�E��
				WantDeg = 45.0f + Get_PC_Deg_XZ(); 
				MovOn = 1;

				/*���[�V�������u���O�i�v�ɂ���*/
				Set_UnderMotion(5);
				break;
		}
		case 8:{//��
				WantDeg = 180.0f + Get_PC_Deg_XZ(); 
				MovOn = 1;

				/*���[�V�������u��i�v�ɂ���*/
				Set_UnderMotion(8);
				break;
		}
		case 9:{//����
				WantDeg = -135.0f + Get_PC_Deg_XZ(); 
				MovOn = 1;

				/*���[�V�������u����i�v�ɂ���*/
				Set_UnderMotion(6);
				break;

	    }
		case 12:{//�E��
				WantDeg = 135.0f + Get_PC_Deg_XZ(); 
				MovOn = 1;

				/*���[�V�������u�E��i�v�ɂ���*/
				Set_UnderMotion(7);
				break;
		}
	}

	//�L�[�����͂���Ă��Ă��A�L�b�N���Ȃ�
	if( Get_MyState() == 1) {
				MovOn = 0;//��Γ����Ȃ�
	}

	//�󒆂ŁA�_�b�V����ԂȂ�
	if( ( Get_AirOnPC() == 1) && ( Get_MyState() == 2)){
				WantDeg = Get_PC_Deg_XZ();//�܂������i��
				MovOn = 1;//��Γ���
	}

	//����я�ԂȂ�
	if( Get_MyState() == 3) {
				WantDeg = -90.0f + Get_PC_Deg_XZ();
				MovOn = 1;//��Γ���
	}

	//�E��я�ԂȂ�
	if( Get_MyState() == 4) {
				WantDeg = 90.0f + Get_PC_Deg_XZ(); 
				MovOn = 1;//��Γ���
	}

	// �J�^�p���g�W�����v�𗘗p���Ȃ�
	if( Get_MyState() == S_JUMP)
	{
		WantDeg = Get_PC_Deg_XZ();
		MovOn = 0;//��΂ɓ����Ȃ�
	}

	/*�������������߂��*/
	switch(MovOn){
			case 1:{
					switch(Get_MyState()){
							case 0:{//�ʏ��ԂȂ�

									if( Get_AirOnPC() == AirOff){//�n��ɂ����
											if(Get_Attitude() == 0){//�p�����u�����Ă����ԁv�Ȃ�
													SumSpeed = RegulateMoveSpeed( 1.2f, 25.0f, 70.0f);
											}
											else if(Get_Attitude() == 1){//�p�����u���Ⴊ�ݏ�ԁv�Ȃ�
													SumSpeed = RegulateMoveSpeed( 0.8f, 20.0f, 50.0f);
											}
									}
									if( Get_AirOnPC() == AirOn){//�󒆂ɂ���Ȃ�
											SumSpeed = RegulateMoveSpeed( 0.3f, 10.0f, 20.0f);
									}
									break;
						    }
							case 2:{//�_�b�V���̎�

									if( Get_AirOnPC() == AirOff)//�n��ɂ���Ȃ�
									{
											SumSpeed = RegulateMoveSpeed( 2.0f, 60.0f, 120.0f);
									}
									else if( Get_AirOnPC() == AirOn)//�󒆂ɂ���Ȃ�
									{
											SumSpeed = RegulateMoveSpeed( 2.0f, 40.0f, 70.0f);
									}
									break;
							}
							case 3:// ������т̂Ƃ�
							case 4:{
									SumSpeed = RegulateMoveSpeed( 5.0f, 50.0f, 120.0f);
									break;
							}
					}

					MoveModel( WantDeg, SumSpeed);

					break;
		    }
			default:{
					if( Get_AirOnPC() == AirOff){// �n��ɂ���Ȃ�

								if( Get_Attitude() == 0)//�p�����u�ʏ��ԁv�Ȃ�
								{
									SumSpeed = RegulateMoveSpeed( -14.0f, 0.0f, 500.0f);
								}
								else if( Get_Attitude() == 1)//�p�����u���Ⴊ�ݏ�ԁv�Ȃ�
								{
									SumSpeed = RegulateMoveSpeed( -14.0f, 0.0f, 500.0f);
								}
					}
					else if( Get_AirOnPC() == AirOn)// �󒆂ɂ���Ȃ�
					{
						if( Get_MyState() == S_JUMP)
						{
							SumSpeed = RegulateMoveSpeed( 0.0f, 0.0f, 500.0f);
						}
						else
						{
							SumSpeed = RegulateMoveSpeed( -2.0f, 0.0f, 500.0f);
						}


					}

					MoveModel( WantDeg, SumSpeed);

					Set_UnderMotion(0);
			}
	}

	return 0;
}

int PlayerChara::MoveModel( double WantDeg, double SumSpeed)
{
	/* ������ */
	int ech;
	D3DXVECTOR3 SubPos( 0.0, 0.0, 0.0);//�L�����N�^�[��u���ꏊ�̍��W
	D3DXVECTOR3 PCPos( 0.0, 0.0, 0.0);//�v���C���[�L�����N�^�[�̈ʒu�̍��W

	/*�_�~�[���f���̍��W�ɐݒ�*/
	Act->RotateInit();
	PCPos = Act->GetPos();

	Act->Dummy->SetPos( PCPos);
	Act->Dummy->RotateY( WantDeg);
	Act->Dummy->Forward( SumSpeed);
	SubPos = Act->Dummy->GetPos();

	Act->SetPos(SubPos);

	return 0;
}


/* �Q�[���I�[�o��N���A�Ȃǂ̃C�x���g�𔭍s���܂� */
int PlayerChara::EventPublish()
{
	/* �ϐ��̏����� */
	int ech;

	int Event = Mission::NORMAL;// �C�x���g�ϐ�

	D3DXVECTOR3 MyPos1( 0.0, 0.0, 0.0);

	/* �Q�[���I�[�o�̊֌W */

	/* �����̈ʒu���Œ�ӂ�Y���W�𒴂����� */
	ech = E3DGetPos( Get_BodyModel(), &MyPos1);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N
	if( MyPos1.y < -10000.0f)
	{
		return Mission::GAMEOVER;
	}





	return Event;
}

/* ���W���w�肵�āA�W�����v�������� */
int PlayerChara::JumpPosition( D3DXVECTOR3 CatPos, const double Degree, const double UpAcceleration, const double Speed)
{
	double WantDeg;

	//WantDeg = Degree + Get_PC_Deg_XZ(); 
	Set_MyState( S_JUMP);
	Set_AirOnPC( AirOn );
	Set_MoveSpeed( Speed );
	Set_PC_Deg_XZ( (float)Degree);

	//E3DSetPos( Get_BodyModel(), CatPos);

	Set_Acceleration( Get_Acceleration() + UpAcceleration);

	return 0;
}