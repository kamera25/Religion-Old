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
#include "cweapon.h"//����Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��





/*���˂����_����̏e�֘A�܂Ƃߊ֐�*/
int PlayerChara::ShoulderGunSys( Batch_Preparat *BatPre, int ScreenPos[2]){

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

	/**/
	//�����̌�������]�����܂��B
	/**/

	//�ŏ��ɉ�]�̌v�Z���܂�
	if(( MyState == 0) || ( (MyState == 2) && ( AirOnPC == 0))){//�ʏ�E�󒆃_�b�V�����[�h�łȂ���΁A�ȉ��擾����
				PC_Deg_XZ = PC_Deg_XZ + float(0.30*(System::MousePos.x - (System::BeforeMousePos.x - System::rewin.left)));
				Tm_DegQ_Y = Tm_DegQ_Y - 0.0020* float( System::MousePos.y - System::BeforeMousePos.y + System::rewin.top);
	}

	if( ( MyState == 3) || ( MyState == 4)){//�������т̎���
				Tm_DegQ_Y = Tm_DegQ_Y - 0.0020* float( System::MousePos.y - System::BeforeMousePos.y + System::rewin.top);
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

	
	/*�X�v���C�g�̈ʒu�����߂ďI�����܂�*/
	BatPre->SpriteData[0][2] = 320 - 16.0f;//�J�[�\����X���W
	BatPre->SpriteData[0][3] = 220 - 18.0f;//�J�[�\����Y���W

	ScreenPos[0] = 320;/**/ScreenPos[1] = 220;

	return 0;
}

/*�L�����N�^�[�̌㏈�����s���֐��A���[�V������p���Ȃ�*/
int PlayerChara::ShoulderGunSysBefore( ){

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
						if( Wpn.GetWeaponData( Wp_equipment, 0) == 1){//�n���h�K�������̂Ȃ�
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
							if( Wpn.GetWeaponData( Wp_equipment, 0) == 4){//�A�T���g�����̂Ȃ�
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
							if( Wpn.GetWeaponData( Wp_equipment, 0) == 1){//�n���h�K�������̂Ȃ�
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
							if( Wpn.GetWeaponData( Wp_equipment, 0) == 4){//�A�T���g�����̂Ȃ�
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
					ech = E3DSetMOAEventNoML( cha_hsid[0], 12, MotionList, NoMotionList);
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