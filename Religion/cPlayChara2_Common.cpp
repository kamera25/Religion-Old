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





/*���ʂ̃Q�[�����ł̏������s���֐��A�e��̏o������A�G�ւ̂�����A�e����ɒu���Ȃǁcetc*/
int PlayerChara::NormallyPCSystem( Stage *Stg, Batch_Render *BatPre, Enemy *Ene, Camera *Cam, int ScreenPos[2]){

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

	/* ////////////////////////////////////////////////////// */
	//�J�����̈ʒu��ݒ肵�܂��A�ʒu�͎����̌��̌��ɐݒu���܂�
	/* ////////////////////////////////////////////////////// */

	//��������ɃJ�������Z�b�g���܂�
	Cam->CamShoulderGunBack( Get_BodyModel(), Get_Quaternion(3), Get_Bone_ID(2), Get_PC_Deg_XZ(), Stg);

	//�̂̌�����A�ˌ����s���֐����Ăяo��
	GunConflictTarget( ScreenPos, Stg, Ene);

	// �����ύX����ۂ̏���
	ChangeWeapon( BatPre);

	/*�p���ϊ��u���̂��Ⴊ�ށv�̏���*/
	if( (keyin[8] == 1) && (Get_AirOnPC() == 0)){//�L�[��������A�󒆂łȂ�
				Set_Attitude( Get_Attitude() + 1);//�p���ϐ�������₷
				if( Get_Attitude() == 2){//�ϐ����s���߂��Ȃ�
						Set_Attitude( 0 );//�u���v�ɌŒ�
				}
	}

	/*�i���U�������鏈�����s���܂�*/
	if( ( keyin[11] == 1) && ( Get_Attitude() == 0) && ( Get_MyState() == 0)){//�L�[��������A���Ⴊ�ݏ�ԂłȂ��A���̓�����s���ĂȂ�
				Set_MyState( 1 );//�L�b�N������
	}

	if( Get_MyState() == 1){//�L�b�N���Ȃ�
				ech = E3DGetMotionFrameNoML( Get_BodyModel(), Get_Bone_ID(6), &MotionID, &MotionFrameNo);
				_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

				if( MotionFrameNo == 19){//���[�V�������I��������
							Set_MyState( 0 );//�����Ԃ�ʏ�ɖ߂�
				}
	}

	/*�_�b�V���֌W�̏������s���܂�*/
	if( ( System::keyinQuick[1] == 1) && ( Get_Attitude() == 0) && ( Get_MyState() == 0) && ( Get_AirOnPC() == 0)){//�L�[���A���ŉ�����A���Ⴊ�ݏ�ԂłȂ��A���̓�����s���ĂȂ��āA�n��Ȃ�
				Set_MyState( 2 );//�_�b�V��������
	}

	if(( System::keyinQuick[1] == 1) && (( Get_Attitude() != 0) || (( Get_MyState() != 0) && ( Get_MyState() != 2) ))){//����ȊO�̏����ł́A�_�b�V���L�����Z������
				System::KeyQuickPush[1][2] = 0;//�_�b�V���L�[��������ĂȂ���Ԃɂ���
				System::keyinQuick[1] = 0;//�Q�[���_�b�V���t���O���I�t�ɂ���
	}


	if( ( Get_MyState() == 2) && ( System::keyinQuick[1] == 0) && ( Get_AirOnPC() == 0) ){//�_�b�V�����쒆�ŁA�L�[���������ꂽ��
				Set_MyState( 0 );//�_�b�V������������
	}

	if( Get_MyState() == 2){//�_�b�V�����Ȃ�
				Set_Stamina( Get_Stamina() - 1);//�X�^�~�i�����炷
				if( (Get_Stamina() < 1) && (Get_AirOnPC() == 0) ){//�̗͂��Ȃ��Ȃ���&�󒆂łȂ��Ȃ�
						Set_MyState(0);//�_�b�V�����~�߂�
						System::KeyQuickPush[1][2] = 0;//�_�b�V���L�[��������ĂȂ���Ԃɂ���
						System::keyinQuick[1] = 0;//�Q�[���_�b�V���t���O���I�t�ɂ���
				}
	}

	/*������ъ֌W�̏������s���܂�*/
	if( ( ( System::keyinQuick[0] == 1) || ( System::keyinQuick[2] == 1)) && ( Get_Attitude() == 0) //���E�L�[���A���ŉ�����A���Ⴊ�ݏ�ԂłȂ��A
		&& ( Get_MyState() == 0) && ( Get_AirOnPC() == 0) && ( 0 < Get_Stamina())){//���̓�����s���ĂȂ��āA�n��ŁA�X�^�~�i���Ȃ��Ȃ��ĂȂ��Ȃ�

				if( System::keyinQuick[0] == 1) Set_MyState( 3 );//��������я�Ԃɂ���;
				if( System::keyinQuick[2] == 1) Set_MyState( 4 );//�E������я�Ԃɂ���;
				if(( System::keyinQuick[0] == 1) && ( System::keyinQuick[2] == 1)) Set_MyState( 0 );//�ʏ��Ԃɂ���
	}

	//������я�ԂȂ�
	if( (Get_MyState() == 3) || ( Get_MyState() == 4)){
				//�ړ���̃��[�V������Ԃ͂ǂ����m���߂�
				ech = E3DGetMotionFrameNoML( Get_BodyModel(), Get_Bone_ID(6), &Garbage, &MotionFrameNo);
				_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

				Set_Stamina( Get_Stamina() - 1);//�X�^�~�i�����炷

				if( MotionFrameNo == 20){//���[�V�������I�����Ă���
							Set_MyState( 0 );//�ʏ��Ԃɖ߂�
							System::KeyQuickPush[0][2] = 0;//�_�b�V���L�[��������ĂȂ���Ԃɂ���
							System::KeyQuickPush[2][2] = 0;//�_�b�V���L�[��������ĂȂ���Ԃɂ���
							System::keyinQuick[0] = 0;//������уt���O���I�t�ɂ���
							System::keyinQuick[2] = 0;//������уt���O���I�t�ɂ���
				}
	}

	/*�X�^�~�i�̐��������*/
	if( Get_Stamina() <= 0){//�X�^�~�i���}�C�i�X�Ȃ�
				Set_Stamina( 0 );//�X�^�~�i���Œ肷��
	}

	/*�����������̂���ׂ��ꏊ�ֈړ�������*/
	if( Get_Wp_equipment() != -1){
				GunPutOnHand();
	}



	return 0;

}
/*�����ύX���邳����ۂɎg�p����֐�*/
int PlayerChara::ChangeWeapon( Batch_Render *BatPre){

	/* �ϐ��̐錾&������ */
	int Eqipment = Get_Wp_equipment();


	/*��������ύX�̏���*/
	if( Eqipment != -1){//���݂̏�Ԃ����펝��
			if( Wpn.Get_WeaponPointer( Eqipment)->Get_NowFireFlag() != 0){// ����U���\�łȂ����
							return -1;//�s�l�Ԃ�
			}
	}


	

	/* ����̕ύX���s�� */
	switch(System::MouseWhole){
			case 1:{
					for(int i=0; i<3; i++){//
							Set_Wp_equipment( Get_Wp_equipment() - 1);//����������J��グ��
							if( Get_Wp_equipment() == -1){//�������u�f��v�ɂȂ�����
									break;//���[�v���甲����A�f��Ɋm��
							}
							if( Get_Wp_equipment() == -2){//�������s���߂�����
									Set_Wp_equipment(1);//�������u�T�u�E�F�|���v�ɂ���
							}
							if( Wpn.Get_WeaponPointer( Get_Wp_equipment()) != 0){//�����A���킪�m�F����Ă���Ȃ�
									break;//���[�v�𔲂���A�����m��
							}
					}

					break;
			}
			case 2:{//�����A�}�E�X�z�C�[�������֍s�����̂Ȃ�
					for(int i=0; i<3; i++){//
								Set_Wp_equipment( Get_Wp_equipment() + 1);//����������J�艺����
								if( Get_Wp_equipment() == 2){//�������s���߂�����
										Set_Wp_equipment(-1);//�������u�T�u�E�F�|���v�ɂ���
										break;//���[�v���甲����A�f��Ɋm��
								}
								if( Wpn.Get_WeaponPointer( Get_Wp_equipment()) != 0){//�����A���킪�m�F����Ă���Ȃ�
										break;//���[�v�𔲂���A�����m��
								}
					}
							
					break;
			}
	}

	// �`��A����p���`�F�b�N�̕���ύX
	BatPre->BacthGunTrade( Get_Wp_equipment());




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
				WantDeg = -90.0f + Get_PC_Deg_XZ();
				MovOn = 1;

				/*���[�V�������u�������v�ɂ���*/
				Set_UnderMotion(3);
	}
	if(KeyMov == 3){//����
				WantDeg = -45.0f + Get_PC_Deg_XZ(); 
				MovOn = 1;

				/*���[�V�������u���O�i�v�ɂ���*/
				Set_UnderMotion(4);
	}
	if(KeyMov == 2){//��
				WantDeg = Get_PC_Deg_XZ(); 
				MovOn = 1;

				/*���[�V�������u���s�v�ɂ���*/
				Set_UnderMotion(1);//�ʏ�

	}
	if(KeyMov == 6){//�E��
				WantDeg = 45.0f + Get_PC_Deg_XZ(); 
				MovOn = 1;

				/*���[�V�������u���O�i�v�ɂ���*/
				Set_UnderMotion(5);
	}
	if(KeyMov == 4){//�E
				WantDeg = 90.0f + Get_PC_Deg_XZ(); 
				MovOn = 1;

				/*���[�V�������u�E�����v�ɂ���*/
				Set_UnderMotion(2);
	}
	if(KeyMov == 12){//�E��
				WantDeg = 135.0f + Get_PC_Deg_XZ(); 
				MovOn = 1;

				/*���[�V�������u�E��i�v�ɂ���*/
				Set_UnderMotion(7);
	}
	if(KeyMov == 8){//��
				WantDeg = 180.0f + Get_PC_Deg_XZ(); 
				MovOn = 1;

				/*���[�V�������u��i�v�ɂ���*/
				Set_UnderMotion(8);
	}
	if(KeyMov == 9){//����
				WantDeg = -135.0f + Get_PC_Deg_XZ(); 
				MovOn = 1;

				/*���[�V�������u����i�v�ɂ���*/
				Set_UnderMotion(6);

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


	/*�������������߂��*/
	if(MovOn == 1){

					if( Get_MyState() == 0){//�ʏ��ԂȂ�
							if( Get_AirOnPC() == 0){//�󒆂łȂ����
									if(Get_Attitude() == 0){//�p�����u�����Ă����ԁv�Ȃ�
											/*�X�s�[�h�𑝉�������*/
											Set_MoveSpeed( Get_MoveSpeed() + 0.8f);

											//�X�s�[�h�ɐ�����������
											if( 25.0f <= Get_MoveSpeed() ){
														Set_MoveSpeed( 25.0f);
											}

											//�Œ�X�s�[�h�̐ݒ�i�����j
											FixedMoveSpeed = 50.0f;
									}

									if(Get_Attitude() == 1){//�p�����u���Ⴊ�ݏ�ԁv�Ȃ�
											/*�X�s�[�h�𑝉�������*/
											Set_MoveSpeed( Get_MoveSpeed() + 0.4f);

											//�X�s�[�h�ɐ�����������
											if( 20.0f <= Get_MoveSpeed() ){
														Set_MoveSpeed( 20.0f);
											}

											//�Œ�X�s�[�h�̐ݒ�i���Ⴊ�݁j
											FixedMoveSpeed = 30.0f;
									}
							}
							if( Get_AirOnPC() == 1){//�󒆂ɂ���Ȃ�
									
									/*�X�s�[�h�𑝉�������*/
									Set_MoveSpeed(Get_MoveSpeed() + 0.3f);

									//�X�s�[�h�ɐ�����������
									if( 10.0f <= Get_MoveSpeed() ){
												Set_MoveSpeed( 10.0f);
									}

									//�Œ�X�s�[�h�̐ݒ�i���Ⴊ�݁j
									FixedMoveSpeed = 20.0f;
							}

					}
					if( Get_MyState() == 2){//�_�b�V����ԂȂ�

							if( Get_AirOnPC() == 0){//�n��ɂ���Ȃ�
									/*�X�s�[�h�𑝉�������*/
									Set_MoveSpeed( Get_MoveSpeed() + 2.0f);

									//�X�s�[�h�ɐ�����������
									if( 40.0f <= Get_MoveSpeed() ){
												Set_MoveSpeed(40.0f);
									}

									//�Œ�X�s�[�h�̐ݒ�i���Ⴊ�݁j
									FixedMoveSpeed = 70.0f;
							}
							if( Get_AirOnPC() == 1){//�󒆂ɂ���Ȃ�
									/*�X�s�[�h�𑝉�������*/
									Set_MoveSpeed( Get_MoveSpeed() + 2.0f);

									//�X�s�[�h�ɐ�����������
									if( 40.0f <= Get_MoveSpeed() ){
												Set_MoveSpeed(40.0f);
									}

									//�Œ�X�s�[�h�̐ݒ�i���Ⴊ�݁j
									FixedMoveSpeed = 70.0f;
							}
					}
					if( ( Get_MyState() == 3) || ( Get_MyState() == 4)){//����я�ԂȂ�
									/*�X�s�[�h���Œ�*/
									Set_MoveSpeed(0.0f);

									//�Œ�X�s�[�h�̐ݒ�i���Ⴊ�݁j
									FixedMoveSpeed = 90.0f;
					}



					/*�_�~�[���f���̍��W�ɐݒ�*/
					ech = E3DRotateInit ( Get_DummyModel());
					_ASSERT( ech != 1 );//�G���[�`�F�b�N

					ech = E3DGetPos( Get_BodyModel(), &PCPos);
					_ASSERT( ech != 1 );//�G���[�`�F�b�N

					ech = E3DSetPos( Get_DummyModel(), PCPos);
					_ASSERT( ech != 1 );//�G���[�`�F�b�N

					ech = E3DRotateY( Get_DummyModel(), WantDeg);
					_ASSERT( ech != 1 );//�G���[�`�F�b�N

					ech = E3DPosForward( Get_DummyModel(), (float)Get_MoveSpeed() + FixedMoveSpeed);
					_ASSERT( ech != 1 );//�G���[�`�F�b�N

					ech = E3DGetPos( Get_DummyModel(), &SubPos);
					_ASSERT( ech != 1 );//�G���[�`�F�b�N

					ech = E3DSetPos( Get_BodyModel(), SubPos);
					_ASSERT( ech != 1 );//�G���[�`�F�b�N
	}
	else{//�����������Ȃ���΂Ȃ�Ȃ��Ȃ�
					if( Get_AirOnPC() == 0){//�󒆂ɂ���Ȃ�
								if( Get_Attitude() == 0) Set_MoveSpeed( Get_MoveSpeed() - 0.8f);//�p�����u�ʏ��ԁv�Ȃ�
								if( Get_Attitude() == 1) Set_MoveSpeed( Get_MoveSpeed() - 1.0f);//�p�����u���Ⴊ�ݏ�ԁv�Ȃ�
					}
					if( Get_AirOnPC() == 1) Set_MoveSpeed( Get_MoveSpeed() - 0.6f);//�p�����u���Ⴊ�ݏ�ԁv�Ȃ�


					//�X�s�[�h�ɐ�����������
					if( Get_MoveSpeed() <= 0.0 ){
								Set_MoveSpeed( 0.0f);
					}


					Set_UnderMotion(0);
	}




	return 0;
}
