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

