//�C���N���[�h����t�@�C����

#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <usercoef.h>//Easy3D�ŕK�v�Ȓǉ��w�b�_
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "resource1.h"//���\�[�X�t�@�C���Ƃ��̊֘A�t���w�b�_
#include <string.h>//�����񑀍�ŕK�v
#include <math.h>//���w�v�Z�Ŏg�p
#include <stdlib.h>//��������邽�߂̃w�b�_

#include "difine.h"


//�O���[�o���ϐ��̐錾



int Lunchergun(int subject, int Moveflg, int Gndflg){
//���̊֐��͏e�ɂ��G�ւ̓����蔻��A�e�̈ړ���S�����S�I�Ȋ֐��ł��B



	//�ȉ��A���_���[�h���ꂼ��̏e�̈ړ�

	//�����_�ł̎�σ��[�h�͂ǂꂩ�B!�_�~�[�Ŏ�ςɂ��Ă��܂��B!

	double handdeg_XZ;


	//��σ��[�h���̏e�̍\��
	if(subject == 1){

					D3DXVECTOR3 ldpos1( 0.0, 0.0, 0.0);//���W�擾Vec���i�[
					D3DXVECTOR3 ldpos2;
					D3DXVECTOR3 ldpos3;
					D3DXVECTOR3 ldpos4( 0.0, 0.0, -1.0);
					D3DXVECTOR3 ldpos5;
					POINT pos;//�}�E�X�̃f�[�^�i�[�̃|�C���^�[
					static double Tm_handdeg_XZ = 0;
					static double Tm_handdeg_Y = 0;
					
					double handdeg_Y = 0.0;

					double handcos_XZ = 0.0;
					double handsin_XZ = 0.0;
					double handcos_Y = 0.0;
					double handsin_Y = 0.0;

					double hdturnpos_X = 0.0;
					double hdturnpos_Y = 0.0;
					double hdturnpos_Z = 0.0;

					static int befMou_X = 0;
					static int befMou_Y = 0;
					int blur_X = 0;
					int blur_Y = 0;

					int ech = 0;

					ech = E3DGetPos( modelId[0], &ldpos5);//��̌����W���擾
					if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
								return 1;//��肠��ŏI��
					};
					ech = E3DSetPos(modelId[0], ldpos1);//��_�Ɉړ��Z�b�g
					if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
								return 1;//��肠��ŏI��
					};
					GetCursorPos( &pos );//�}�E�X���W���i�[

					Tm_handdeg_XZ = Tm_handdeg_XZ + 0.001*(befMou_X - pos.x);//X���W��O�}�E�X-�}�E�X����p�x
					Tm_handdeg_Y = Tm_handdeg_Y - 0.001*(befMou_Y - pos.y);//Y���W��O�}�E�X-�}�E�X�p�x

					SetCursorPos( recwindow.left + 320, recwindow.top + 240);//�}�E�X���E�B���h�E�^�񒆂ɐݒu
					GetCursorPos( &pos );//�}�E�X���W���i�[
					befMou_X = pos.x;//�O�̃}�E�X���W���擾
					befMou_Y = pos.y;//�O�̃}�E�X���W���擾

					blur_X = rand()%2;//X���̃u���𗐐��Ō���
					blur_Y = rand()%2;//Y���̂Ԃ�𗐐��Ō���
					if(blur_X == 0){
								blur_X = -1;//�u����0�Ȃ�A-�̕����ɂԂ��B
					}
					if(blur_Y == 0){
								blur_Y = -1;//�u����0�Ȃ�A-�̕����ɂԂ��B
					}


					if(Tm_handdeg_XZ>6.0){
											Tm_handdeg_XZ = Tm_handdeg_XZ - 6.0;
					}
					if(Tm_handdeg_XZ<0.0){
											Tm_handdeg_XZ = Tm_handdeg_XZ + 6.0;
					}
					if(Tm_handdeg_Y>0.8){
											Tm_handdeg_Y = 0.8;
					}
					if(Tm_handdeg_Y<-0.7){
											Tm_handdeg_Y = -0.7;
					}




					handdeg_XZ = Tm_handdeg_XZ;
					handdeg_Y = Tm_handdeg_Y;



					handcos_XZ = cos(handdeg_XZ);
					handsin_XZ = sin(handdeg_XZ);
					handcos_Y = cos(handdeg_Y);
					handsin_Y = sin(handdeg_Y);


					hdturnpos_X = handcos_XZ * handcos_Y * 2000;//�����ׂ�������X���W
					hdturnpos_Y = handsin_Y * 2000;//�����ׂ�������Y���W���擾
					hdturnpos_Z = handsin_XZ * handcos_Y * 2000;//�����ׂ�������Z���W���擾

					ech = E3DGetPos( modelId[0], &ldpos2);//��̍��W���擾
					if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
								return 1;//��肠��ŏI��
					};

					ldpos3.x = ldpos2.x - hdturnpos_X;//X���W�̌��������̃x�N�g�����擾
					ldpos3.y = ldpos2.y - hdturnpos_Y;//Y���W�̌��������̃x�N�g�����擾
					ldpos3.z = ldpos2.z - hdturnpos_Z;//Z���W�̌��������̃x�N�g�����擾

					//�u���������Ԃ�

					ech = E3DGetDirQ2( modelId[0], QId[0]);
					if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
								return 1;//��肠��ŏI��
					};
					ech = E3DLookAtQ( QId[0], ldpos3, ldpos4, 0, 10);
					if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
								return 1;//��肠��ŏI��
					};
					ech = E3DSetDirQ2( modelId[0], QId[0]);
					if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
								return 1;//��肠��ŏI��
					};

					
					ech = E3DSetPos( modelId[10], ldpos3);//��̌����W�ֈړ�
					if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
								return 1;//��肠��ŏI��
					};



					ech = E3DSetPos( modelId[0], ldpos5);//��̌����W�ֈړ�
					if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
								return 1;//��肠��ŏI��
					};



	}


	//�ȉ��A�ړ����邽�߂̃��[�h�쐬

	if(Moveflg == 1){
					int ech = 0;
					int KeyMov = 0;
					int MovOn = 0;
					static int Speed = 0;
					double Mov_XZ = handdeg_XZ;
					double WantDeg = 0.0;
					double Movsin_XZ = 0.0;
					double Movcos_XZ = 0.0;
					double MovDeg_X = 0.0;
					double MovDeg_Z = 0.0;
					D3DXVECTOR3 ldpos1( 0.0, 0.0, -1.0);
					D3DXVECTOR3 ldpos2;
					D3DXVECTOR3 ldpos3( 0.0, 0.0, 0.0);

					//�L�[�ɂ�镪��
					if(keyin[0] == 1){//��
									KeyMov = KeyMov +1;
					}
					if(keyin[1] == 1){//��
									KeyMov = KeyMov +2;
					}
					if(keyin[2] == 1){//�E
									KeyMov = KeyMov +4;
					}
					if(keyin[3] == 1){//��
									KeyMov = KeyMov +8;
					}

					//�L�[����擾��������ϊ�
					if(KeyMov == 1){//��
									WantDeg = 1.5;
									MovOn = 1;
					}
					if(KeyMov == 3){//����
									WantDeg = 0.75; 
									MovOn = 1;
					}
					if(KeyMov == 2){//��
									MovOn = 1;
					}
					if(KeyMov == 6){//�E��
									WantDeg = -0.75; 
									MovOn = 1;
					}
					if(KeyMov == 4){//�E
									WantDeg = -1.5;
									MovOn = 1;
					}
					if(KeyMov == 12){//�E��
									WantDeg = -2.25; 
									MovOn = 1;
					}
					if(KeyMov == 8){//��
									WantDeg = -3.0;
									MovOn = 1;
					}
					if(KeyMov == 9){//����
									WantDeg = 2.25; 
									MovOn = 1;
					}

					//�ړ����x�̌���
					if(MovOn ==0 ){
							Speed = 0;
					}
					

					///�������������߂��
					if(MovOn == 1){

								Mov_XZ = Mov_XZ + WantDeg;//��������������ݒ�
								if(Mov_XZ>6.0){
											Mov_XZ = Mov_XZ - 6.0;
								}
								if(Mov_XZ<0.0){
											Mov_XZ = Mov_XZ + 6.0;
								}

								Movcos_XZ = cos(Mov_XZ);//XZ��̃R�T�C�������߂�
								Movsin_XZ = sin(Mov_XZ);//XZ��̃T�C�������߂�

								MovDeg_X = Movcos_XZ * 2000;//�����ׂ�������X���W
								MovDeg_Z = Movsin_XZ * 2000;//�����ׂ�������Z���W���擾

								ldpos3.x = 0.0 - MovDeg_X;//X���W�̃x�N�g�������߂�
								ldpos3.z = 0.0 - MovDeg_Z;//Z���W�̃x�N�g�������߂�

								//�ړ����x�̐ݒ�
								Speed = Speed + 4;
								if(Speed >= 100){
										Speed = 100;
								}


								ech = E3DGetPos( modelId[0], &ldpos2);//��̃��f���̍��W���擾
								if(ech != 0 ){//�G���[�`�F�b�N
											_ASSERT( 0 );//�G���[�_�C�A���O
											return 1;//��肠��ŏI��
								};

								ech = E3DSetPos( modelId[10], ldpos2);//�T�u���f���̍��W�ɐݒ�
								if(ech != 0 ){//�G���[�`�F�b�N
											_ASSERT( 0 );//�G���[�_�C�A���O
											return 1;//��肠��ŏI��
								};

								ech = E3DLookAtQ( QId[4], ldpos3, ldpos1, 0, 0);//Q�̌������s�����������ɐݒ�
								if(ech != 0 ){//�G���[�`�F�b�N
											_ASSERT( 0 );//�G���[�_�C�A���O
											return 1;//��肠��ŏI��
								};

								ech = E3DSetDirQ2( modelId[10], QId[4]);//�T�u���f����Q���Z�b�g
								if(ech != 0 ){//�G���[�`�F�b�N
											_ASSERT( 0 );//�G���[�_�C�A���O
											return 1;//��肠��ŏI��
								};
								ech = E3DPosForward( modelId[10], Speed);//�T�u���f����O�i������
								if(ech != 0 ){//�G���[�`�F�b�N
											_ASSERT( 0 );//�G���[�_�C�A���O
											return 1;//��肠��ŏI��
								};
								ech = E3DGetPos( modelId[10], &ldpos2);//�T�u���f���̍��W���擾
								if(ech != 0 ){//�G���[�`�F�b�N
											_ASSERT( 0 );//�G���[�_�C�A���O
											return 1;//��肠��ŏI��
								};

								ech = E3DSetPos( modelId[0], ldpos2);//��̃��f�����T�u���f���̈ʒu�ɐݒ�
								if(ech != 0 ){//�G���[�`�F�b�N
											_ASSERT( 0 );//�G���[�_�C�A���O
											return 1;//��肠��ŏI��
								};

				}

	}


	//�ȉ����A�n�ʂƂ̓����蔻���ݒ肵�܂��B

	

	if(Gndflg = 1){

			int ech = 0;
			int ChkGnd = 0; 
			D3DXVECTOR3 ldpos1( 0.0, 0.0, 0.0);
			D3DXVECTOR3 ldpos2( 0.0, 0.0, 0.0);


			ech = E3DGetPos( modelId[0], &ldpos1);//��̍��W���擾
			if(ech != 0 ){//�G���[�`�F�b�N
						_ASSERT( 0 );//�G���[�_�C�A���O
						return 1;//��肠��ŏI��
			};

			ech = E3DSetPos( modelId[12], ldpos1);//��̍��W�ɃT�u���f����ݒu
			if(ech != 0 ){//�G���[�`�F�b�N
						_ASSERT( 0 );//�G���[�_�C�A���O
						return 1;//��肠��ŏI��
			};


			E3DChkConfGround( modelId[12], grd1, 1, 1500, 0, &ChkGnd, &ldpos1, &ldpos2);//�n�ʂƃT�u���f���̍��W�`�F�b�N
			if(ech != 0 ){//�G���[�`�F�b�N
						_ASSERT( 0 );//�G���[�_�C�A���O
						return 1;//��肠��ŏI��
			};

			if(ChkGnd != 0){
						ldpos1.y = ldpos1.y +1000;//���W���L�����Ɠ������炢�ɂ���B
						ech = E3DSetPos( modelId[0], ldpos1);
						if(ech != 0 ){//�G���[�`�F�b�N
									_ASSERT( 0 );//�G���[�_�C�A���O
									return 1;//��肠��ŏI��
						};
			}
	}


	



	//���L���A�e�̑�����@��ݒ�

	int usewpkind = Iinfo[(Iinfo[3][3])][0];//�g���Ă镐��̎��
	int usewpno = Iinfo[(Iinfo[3][3])][1];//�g���Ă镐��̃i���o�[
	int lunchflg = 0;
	int ech;
	D3DXVECTOR3 ldpos1;
	D3DXVECTOR3 ldpos2( 0.0, 1.0, 0.0);//������̃x�N�g���i�J�����Ŏg�p��A���ł��{�b�N�X���j

	//�ȉ����A�e�̕��������肵�܂�

	if(Iinfo[3][3] != -1){//�f��łȂ���
	//��Ϗ�ԂȂ��
		if(subject == 1){




			if(usewpkind == 0){//�����A�g���Ă�e���n���h�K���Ȃ�


							//�ȉ��A�e�̎蕔���̐ݒu
							ech = E3DSetNewPoseML(modelId[0]);
							if(ech != 0 ){//�G���[�`�F�b�N
										_ASSERT( 0 );//�G���[�_�C�A���O
										return 1;//��肠��ŏI��
							};

							ech = E3DGetCurrentBonePos( modelId[0], BoneId[0], 1, &ldpos1);//��̃|�W�V�����擾
							if(ech != 0 ){//�G���[�`�F�b�N
										_ASSERT( 0 );//�G���[�_�C�A���O
										return 1;//��肠��ŏI��
							};

							ech = E3DSetPos( Iinfo[(Iinfo[3][3])][2], ldpos1);//�e��������ɐݒu
							if(ech != 0 ){//�G���[�`�F�b�N
										_ASSERT( 0 );//�G���[�_�C�A���O
										return 1;//��肠��ŏI��
							};

							
							ech = E3DGetCurrentBoneQ( modelId[0], BoneId[2], 2, QId[2]);//���̌������擾
							if(ech != 0 ){//�G���[�`�F�b�N
										_ASSERT( 0 );//�G���[�_�C�A���O
										return 1;//��肠��ŏI��
							};
							ech = E3DSetDirQ2( Iinfo[(Iinfo[3][3])][2], QId[2]);
							if(ech != 0 ){//�G���[�`�F�b�N
										_ASSERT( 0 );//�G���[�_�C�A���O
										return 1;//��肠��ŏI��
							};
							
							//�ȉ����J������ݒ�
							//

							ech = E3DGetCurrentBonePos( Iinfo[(Iinfo[3][3])][2], Iinfo[(Iinfo[3][3])][7], 1, &ldpos1);//�J�����̐�̃|�W�V�����擾
							if(ech != 0 ){//�G���[�`�F�b�N
										_ASSERT( 0 );//�G���[�_�C�A���O
										return 1;//��肠��ŏI��
							};

							E3DSetCameraTarget(ldpos1,ldpos2);//�J�����̒����_��ݒ肷��B
							if(ech != 0 ){//�G���[�`�F�b�N
										_ASSERT( 0 );//�G���[�_�C�A���O
										return 1;//��肠��ŏI��
							};


							//�ȉ��A�e�R���W�����̐ݒu
							//

							ech = E3DSetNewPoseML(Iinfo[(Iinfo[3][3])][2]);
							if(ech != 0 ){//�G���[�`�F�b�N
										_ASSERT( 0 );//�G���[�_�C�A���O
										return 1;//��肠��ŏI��
							};

							ech = E3DGetCurrentBonePos( Iinfo[(Iinfo[3][3])][2], Iinfo[(Iinfo[3][3])][6], 1, &ldpos1);//�e��̃|�W�V�����擾
							if(ech != 0 ){//�G���[�`�F�b�N
										_ASSERT( 0 );//�G���[�_�C�A���O
										return 1;//��肠��ŏI��
							};

							ech = E3DSetPos( modelId[11], ldpos1);//�e�̃R���W�������f����ݒu
							if(ech != 0 ){//�G���[�`�F�b�N
										_ASSERT( 0 );//�G���[�_�C�A���O
										return 1;//��肠��ŏI��
							};

							ech = E3DGetCurrentBoneQ( Iinfo[(Iinfo[3][3])][2], Iinfo[(Iinfo[3][3])][7], 2, QId[1]);//�e���̌������擾
							if(ech != 0 ){//�G���[�`�F�b�N
										_ASSERT( 0 );//�G���[�_�C�A���O
										return 1;//��肠��ŏI��
							};
							ech = E3DSetDirQ2( modelId[11], QId[1]);
							if(ech != 0 ){//�G���[�`�F�b�N
										_ASSERT( 0 );//�G���[�_�C�A���O
										return 1;//��肠��ŏI��
							};

							ech = E3DPosForward( modelId[11], -300);//�R���W�������f������ނ�����
							if(ech != 0 ){//�G���[�`�F�b�N
										_ASSERT( 0 );//�G���[�_�C�A���O
										return 1;//��肠��ŏI��
							};

							E3DGetPos( modelId[11], &ldpos1);//�R���W�������f���̈ʒu���擾
							if(ech != 0 ){//�G���[�`�F�b�N
										_ASSERT( 0 );//�G���[�_�C�A���O
										return 1;//��肠��ŏI��
							};


							//�o�b�N�����Ƃ���ɃJ������ݒu
							//

							ech = E3DSetCameraPos( ldpos1);//�J�����̈ʒu���Z�b�g����
							if(ech != 0 ){//�G���[�`�F�b�N
										_ASSERT( 0 );//�G���[�_�C�A���O
										return 1;//��肠��ŏI��
							};


			}
		}
	}






	//�ȉ����A�e�̃����[�h��}�O�̃V�X�e�������肵�܂�

	//��Ԃ��f��o�Ȃ����
	if((Iinfo[3][3]) != -1){

				if(keyin[9] == 1){//�����e����������
									Iinfo[ (Iinfo[3][3]) ][3]--;//�e�e�����炷
									Iinfo[ (Iinfo[3][3]) ][5] = 0;//�������̂ŁA���U���Ă��������Ȃ�
									lunchflg = 1;//�e���������Ƃ����t���O

									if((Iinfo[ (Iinfo[3][3]) ][4] == 0)&&(Iinfo[ (Iinfo[3][3]) ][3] == -1)){//�}�K�W���Ȃ��ŏe����������
																Iinfo[ (Iinfo[3][3]) ][3] = 0;//
																lunchflg = 0;
									}
									if(Iinfo[ (Iinfo[3][3]) ][3] == -1){//�����A�e�e���Ȃ��̂Ɍ��������ƂɂȂ��Ă���Ȃ�
																lunchflg = 0;//�t���O����
									}
				}


				if((keyin[4] == 1)&&(Iinfo[ (Iinfo[3][3]) ][4] != 0 )){//���������[�h�L�[����������
									//�����ɔ����n�A���C�t���n�ŏꍇ�킯��

									if(Iinfo[ (Iinfo[3][3]) ][5] == 1){//�����AMAG��AMM�����^���Ȃ�
																Iinfo[ (Iinfo[3][3]) ][4]--;//�}�K�W�������炷
																Iinfo[ (Iinfo[3][3]) ][3] = wpitem[usewpkind][usewpno][5] + 1;//�e�e�𑝂₷+ 1	
																Iinfo[ (Iinfo[3][3]) ][5] = 0;
									}
									else{
																Iinfo[ (Iinfo[3][3]) ][4]--;//�}�K�W�������炷
																Iinfo[ (Iinfo[3][3]) ][3] = wpitem[usewpkind][usewpno][5];//�e�e�𑝂₷
									}
				}
				if((keyin[9] == 1) && (Iinfo[ (Iinfo[3][3]) ][3] == -1 ) && (keyin[4] == 0) && (Iinfo[ (Iinfo[3][3]) ][4] != 0)){//�����e�e0�ŁA���˃L�[����������
																Iinfo[ (Iinfo[3][3]) ][4]--;//�}�K�W�������炷
																Iinfo[ (Iinfo[3][3]) ][3] = wpitem[usewpkind][usewpno][5];//�e�e�𑝂₷
				}


	}


	//�ȉ����A�����ł��Ă�Ȃ炻�ꂼ��ʂ̏������s���܂��B

	if((lunchflg == 1)&&(Iinfo[4][0] != 0)){//�����e�����˂��Ă��āA�G�̐���0�łȂ����

				if((usewpkind != 6)&&(usewpkind != 7)){//����ȕ���łȂ����
							
									int Conchk;//�������Ă邩��܂��Ȍv�Z
									int inview;//����p���ɂ��邩
									int Nearmodelid;//�߂����f����ID
									int suita;//�K���Ɏg��ȕϐ����Ԃ�����
									D3DXVECTOR3 MyPos;//�����̈ʒu���擾
									D3DXVECTOR3 suitavec3;//�K���Ȏg��Ȃ��ϐ����Ԃ�����
									double EneDistance = 0.0;//�G�̋���
									double NearmodelVec = 1000000.0;//��ԋ߂��G�܂ł̋���
									double Nearidytofar[30][2];//�����Ǝ����̋�����ID

		
									//�������������f�����ȈՓI�Ƀ`�F�b�N��������ϐ��ց�


									int i = 0;//�J�E���^
									int hitnum = 0;//�G�ɓ����������J�E���g
									ech = E3DGetPos( modelId[11], &MyPos);
									if(ech != 0 ){//�G���[�`�F�b�N
												_ASSERT( 0 );//�G���[�_�C�A���O
												return 1;//��肠��ŏI��
									};

									while(i<=Iinfo[4][0] - 1){

													//���f���Ƃ������Ă��邩�ǂ������ׂ�
													E3DChkConflictOBB( modelId[11], -1, Eneinfo[i][2], -1, &Conchk, &inview);
													ech = E3DGetPos( modelId[11], &MyPos);
													if(ech != 0 ){//�G���[�`�F�b�N
																	_ASSERT( 0 );//�G���[�_�C�A���O
																	return 1;//��肠��ŏI��
													};


													if(Conchk == 1){
																	D3DXVECTOR3 EnePos;//�G���W�̍\����
																	int i = 0;//�J�E���^�̐ݒu
																	double EneVecPlus[3];//�G�̐�Βl�x�N�g��

																	ech = E3DGetPos( Eneinfo[i][2], &EnePos);//�G�̍��W���擾
																	if(ech != 0 ){//�G���[�`�F�b�N
																				_ASSERT( 0 );//�G���[�_�C�A���O
																				return 1;//��肠��ŏI��
																	};


																	//�x�N�g�����`�F�b�N
																	
																	EneVecPlus[0] = fabs( EnePos.x - MyPos.x );//X���W�̐�Βl�x�N�g��
																	EneVecPlus[1] = fabs( EnePos.y - MyPos.y );//Y���W�̐�Βl�x�N�g��
																	EneVecPlus[2] = fabs( EnePos.z - MyPos.z );//Z���W�̐�Βl�x�N�g��


																	//��ԋ߂����f�����ǂ����`�F�b�N			
																	EneDistance = EneVecPlus[0] + EneVecPlus[1] + EneVecPlus[2];
																	
																	
																	while(i<=Iinfo[4][0] - 1){
																			if(EneDistance <  Nearidytofar[i][1]){
																					Nearidytofar[i][0] = Eneinfo[i][2]
																			
																			
																			
																					hitnum = 1;
																			}

																			i++;
																	}	
													}
									i++;
									}
									i = 0;

									//�����A�����郂�f��������A�g�p���̏e�̓�����͈̔͂𒴂��Ȃ����
									if((hitnum != 0)&&(wpitem[usewpkind][usewpno][4] * 100 > NearmodelVec)){

																	int Clticalhit = 0;//�N���e�B�J���̕ϐ�������
																	int Wallconf = 0;//�ǂƂ������Ă邩�`�F�b�N
																	int bodyconf;//�{���ɂ������Ă��邩�ǂ��������ȓ����蔻��̕ϐ�
																	D3DXVECTOR3 LineCnfPos;//�����Ŏg�����W���擾
																	D3DXVECTOR3 ModelCnfPos;//�e�ƃ��f�������������Ƃ���
																	
																	ech = E3DChkConflictOBB( modelId[11], -1, Eneinfo[Nearmodelid][2], Eneinfo[Nearmodelid][3], &Clticalhit, &suita);
																	if(ech != 0 ){//�G���[�`�F�b�N
																				_ASSERT( 0 );//�G���[�_�C�A���O
																				return 1;//��肠��ŏI��
																	};

																	//�ǂɓ������ĂȂ����`�F�b�N���܂��B
																	E3DPosForward(  modelId[11], 50000);//�_����O��
																	if(ech != 0 ){//�G���[�`�F�b�N
																				_ASSERT( 0 );//�G���[�_�C�A���O
																				return 1;//��肠��ŏI��
																	};
																	E3DGetPos(  modelId[11], &LineCnfPos);//�����_�̍��W�Q�b�c�I
																	if(ech != 0 ){//�G���[�`�F�b�N
																				_ASSERT( 0 );//�G���[�_�C�A���O
																				return 1;//��肠��ŏI��
																	};
																	E3DPosForward(  modelId[11], -500000);//�_����O��
																	if(ech != 0 ){//�G���[�`�F�b�N
																				_ASSERT( 0 );//�G���[�_�C�A���O
																				return 1;//��肠��ŏI��
																	};

																	//�����f���Ƃ̕��ʂ�������W���Q�b�g��
																	E3DChkConfLineAndFace( MyPos, LineCnfPos, Eneinfo[Nearmodelid][2], 1, &bodyconf, &suita, &ModelCnfPos, &suitavec3, &suita);
																	if(ech != 0 ){//�G���[�`�F�b�N
																				_ASSERT( 0 );//�G���[�_�C�A���O
																				return 1;//��肠��ŏI��
																	};

																	//���ǂƂ̂�������`�F�b�N��
																	//E3DChkConfWallVec( MyPos, ModelCnfPos, �O���E���h��ID, 0, &Wallconf, &suitavec3, &suitavec3);
																	/*if(ech != 0 ){//�G���[�`�F�b�N
																				_ASSERT( 0 );//�G���[�_�C�A���O
																				return 1;//��肠��ŏI��
																	};*/

																	if(Wallconf == 0){
																		int a;
																		a = 30;
																		//�������Ă��Ȃ��̂Ń_���[�W����ɍs���܂��傤
																	}
									}
				}
	}
	lunchflg = 0;




	return 0;
}