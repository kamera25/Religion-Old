/*�����ł́A�����N���X�̃L�����E�G�̊֐����`����N���X�R�[�h�t�@�C���ł��B
//���ɃQ�[�����J�n���鎞�ɕK�v�Ȋ֐�������������Ă��܂��B
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include "cstage.h"//�X�e�[�W�֌W�̃N���X�w�b�_�t�@�C��
#include "clive.h"//�G��L�����̐錾�w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_


//�����ɃO���[�o���ϐ���錾
extern System *sys;//�V�X�e���N���X���w���A�N���X�̃|�C���^


/*�v���C���[�L�����N�^�[�̃R���X�g���N�^*/
PlayerChara::PlayerChara( int selchara, int Wpselect_equipment){

	//�ϐ��̏�����
	int ech = 0;
	char loadname[256] = "";


	//�N���X���ϐ��̏�����
	/*�E�F�|���ϐ��̏�����*/
	for(int i = 0; i<3; i++){
		for(int j = 0; j<4; j++){
			for(int k = 0; k<6;k++){
					wp_data[i][j][k] = 0;//���ׂẴE�F�|���ϐ�����ɂ���
			}
		}
	}

	/*���̑��ϐ��̏�����*/

	BringWp = 0;//�E������������������܂�
	PC_Deg_XZ = 0.0f;//�����̌����iXZ���W�������j
	PC_Deg_Y = 0.0f;//�����̌����iY���W�������j
	UpMotion = 0;//�㔼�g�̃��[�V�����̏�����
	UnderMotion = 0;//�����g�̃��[�V�����̏�����
	Attitude = 0;//�����̎p�����u�����v�Ɏw��
	MyState = 0;//�����̓����Ԃ�������
	AirOnPC = 0;//�����̋󒆏�Ԃ�ʏ�ɂ���
	Acceleration = 0.0;//�d�͉����x��0�ɂ���
	MoveSpeed = 0.0;//���ʉ����x��0�ɂ���


	//�L�����N�^�[���f���̃��[�h

	if(selchara == 0){//�A�[�e�B�[���f��

				//�A�[�e�B�[���f���̎擾
				wsprintf( loadname, "%s\\data\\3d\\model\\demo\\hito.sig", sys->path);//�A�[�e�B�[���f����sig���o�^
				ech = E3DSigLoad( loadname, 0, 0, &cha_hsid[0]);//���f���̓ǂݍ��݁Acha_hsid�փ��f��������B
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT(0);//�G���[�_�C�A���O
				};

				//�n���h���f���̎擾
				wsprintf( loadname, "%s\\data\\3d\\model\\hand\\hand.sig", sys->path);//�n���h���f����sig���o�^
				ech = E3DSigLoad( loadname, 0, 1, &cha_hsid[1]);//���f���̓ǂݍ��݁Acha_hsid�փ��f��������B
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				//�_�~�[���f���̎擾
				wsprintf( loadname, "%s\\data\\3d\\model\\other\\demo.sig", sys->path);//�����f����sig���o�^
				ech = E3DSigLoad( loadname, 0, 1, &DummyModel);//���f���̓ǂݍ��݁Asubmodid�փ��f��������B
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

	}

		if(selchara == 1){//WF��1���f��

				//WF��1���f���̎擾
				wsprintf( loadname, "%s\\data\\3d\\chara\\wf1\\model.sig", sys->path);//�A�[�e�B�[���f����sig���o�^
				ech = E3DSigLoad( loadname, 0, 0.15f, &cha_hsid[0]);//���f���̓ǂݍ��݁Acha_hsid�փ��f��������B
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT(0);//�G���[�_�C�A���O
				};

				//�_�~�[���f���̎擾
				wsprintf( loadname, "%s\\data\\3d\\model\\other\\demo.sig", sys->path);//�����f����sig���o�^
				ech = E3DSigLoad( loadname, 0, 0.01f, &DummyModel);//���f���̓ǂݍ��݁Asubmodid�փ��f��������B
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				//���[�V�����f�[�^�\��
				wsprintf( loadname, "%s\\data\\3d\\chara\\motion\\pc_motion.moa", sys->path);//�����f����sig���o�^
				ech = E3DLoadMOAFile( cha_hsid[0], loadname, 3, 1.0f); 
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				//�{�[���l�[������{�[��ID�̎擾�u�e������_X+�v
				ech = E3DGetBoneNoByName( cha_hsid[0], "�e������_X+", &bone[0]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};
				//�{�[���l�[������{�[��ID�̎擾�u�e�������_X+�v
				ech = E3DGetBoneNoByName( cha_hsid[0], "�e�������_X+", &bone[1]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};
				//�{�[���l�[������{�[��ID�̎擾�u��t�����v
				ech = E3DGetBoneNoByName( cha_hsid[0], "��t����", &bone[2]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};
				//�{�[���l�[������{�[��ID�̎擾�u���t����_X+�v
				ech = E3DGetBoneNoByName( cha_hsid[0], "���t����_X+", &bone[3]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};
				//�{�[���l�[������{�[��ID�̎擾�u���t����_X-�v
				ech = E3DGetBoneNoByName( cha_hsid[0], "���t����_X-", &bone[4]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};
				//�{�[���l�[������{�[��ID�̎擾�u���Ȃ��v
				ech = E3DGetBoneNoByName( cha_hsid[0], "���Ȃ�", &bone[5]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};
				//�{�[���l�[������{�[��ID�̎擾�u�ړ���v
				ech = E3DGetBoneNoByName( cha_hsid[0], "�ړ���", &bone[6]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				/*�ϐ��̑��*/
				MaxHP = 150;//�ő�HP�̑���A!���Ƃňړ������邩��!
				HP = MaxHP;//�ő�HP�܂ő���A!����A�ړ������邩��!
				Stamina = 150;//�Œ�X�^�~�i�A���ƂŎd�l�ύX���邩��
	}

	/**/
	//�N�H�[�^�j�I�����쐬���܂�
	/**/	
	for(int i = 0; i<10; i++){
				ech = E3DCreateQ( &Qid[i]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};
				ech = E3DInitQ( Qid[i]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};
	}



	/*������������̒��ōŏ��ɉ��������Ă��邩�ݒ肵�܂�*/
	Wp_equipment = Wpselect_equipment;




}


/*�e�̃��[�h���s���N���X���֐��ł��B*/
int PlayerChara::GunLoad( int selwp_kind, int gunkind, int gunno){

	//�ϐ��̏�����
	int ech = 0;
	char loadname[256] = "";

	//�ꎞ�I�ȕϐ��i���f���i�[���Ȃǁj
	int hsid;//�e���f����ID
	int hit_hsid;//�e�̓����蔻�胂�f��ID
	int g_spid;//�e�X�v���C�g�̃X�v���C�gID
	int ammo;//�e��̍ő�l
	int mag;//�}�K�W���̍ő�l
	int distance;//�˒������̍ő�l
	int attack;//����̍U���l
	int bone[4];//�e�̃{�[��
	int Garbage = 0;//����Ȃ��ϐ����i�[���܂�

	//���łɏe���擾���Ă���A���̏e�f�[�^�ɏ㏑������Ȃ�

	if( wp_data[selwp_kind][0][0] != 0){//�I�𒆂̃J�e�S���Ƀf�[�^������̂Ȃ�
				ech = E3DDestroyHandlerSet( wp_data[selwp_kind][0][0]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				ech = E3DDestroySprite( wp_data[selwp_kind][0][0]);//�X�v���C�g���폜���܂�
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};
		
	}




	//�e�̃��f���̃��[�h

	if(gunkind == 1){//�n���h�K���n

		if(gunno == 0){//M1911

				//���f���f�[�^�̃��[�h
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\m1911\\m1911.sig", sys->path);
				ech = E3DSigLoad( loadname, 0, 0.055f, &hsid);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				//�����蔻�胂�f���̃��[�h
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\hitchk\\hitber.sig", sys->path);
				ech = E3DSigLoad( loadname, 0, 5.0f, &hit_hsid);//���f���̓ǂݍ���
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				//����X�v���C�g�̃��[�h
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\m1911\\pict.png", sys->path);
				ech = E3DCreateSprite( loadname, 1, 0, &g_spid);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				//����̃��[�V������ǂݍ���
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\m1911\\wait.qua", sys->path);
				ech = E3DAddMotion( hsid, loadname, 1, &Garbage, &Garbage);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};


				/**/
				//�{�[���f�[�^�̃��[�h���s���܂�
				/**/

				//�{�[���l�[������{�[��ID�̎擾�u�e������_X+�v
				E3DGetBoneNoByName( hsid, "�e��", &bone[0]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};
				//�{�[���l�[������{�[��ID�̎擾�u�e�������_X+�v
				E3DGetBoneNoByName( hsid, "�e��", &bone[1]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};
				//�{�[���l�[�����瓖���蔻��{�[��ID�̎擾�u�����蔻���v
				E3DGetBoneNoByName( hit_hsid, "�����蔻���", &bone[2]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};
				//�{�[���l�[������{�[��ID�̎擾�u�����蔻�荪�v
				E3DGetBoneNoByName( hit_hsid, "�����蔻�荪", &bone[3]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};


				//M1911�̃f�[�^���i�[���܂��B
				ammo = 7;
				mag = 7;
				distance = 100;
				attack = 100;
		}
		if(gunno == 2){//Glock95

				//���f���f�[�^�̃��[�h
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\glock95\\glock.sig", sys->path);
				ech = E3DSigLoad( loadname, 0, 0.037f, &hsid);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				//�����蔻�胂�f���̃��[�h
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\hitchk\\hitber.sig", sys->path);
				ech = E3DSigLoad( loadname, 0, 5.0f, &hit_hsid);//���f���̓ǂݍ���
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				//����X�v���C�g�̃��[�h
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\glock95\\pict.png", sys->path);
				ech = E3DCreateSprite( loadname, 1, 0, &g_spid);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				//����̃��[�V������ǂݍ���
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\m1911\\wait.qua", sys->path);
				ech = E3DAddMotion( hsid, loadname, 1, &Garbage, &Garbage);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};


				/**/
				//�{�[���f�[�^�̃��[�h���s���܂�
				/**/

				/*//�{�[���l�[������{�[��ID�̎擾�u�e������_X+�v
				E3DGetBoneNoByName( hsid, "�e��", &bone[0]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};
				//�{�[���l�[������{�[��ID�̎擾�u�e�������_X+�v
				E3DGetBoneNoByName( hsid, "�e��", &bone[1]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};*/

				bone[0] = 0;//�e����O�̃{�[�����i�[
				bone[1] = 0;//�e�����̃{�[�����i�[
				//�{�[���l�[�����瓖���蔻��{�[��ID�̎擾�u�����蔻���v
				E3DGetBoneNoByName( hit_hsid, "�����蔻���", &bone[2]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};
				//�{�[���l�[������{�[��ID�̎擾�u�����蔻�荪�v
				E3DGetBoneNoByName( hit_hsid, "�����蔻�荪", &bone[3]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};


				//Glock�̃f�[�^���i�[���܂��B
				ammo = 50;
				mag = 3;
				distance = 60;
				attack = 30;
		}

		if(gunno == 3){//M92F

				//���f���f�[�^�̃��[�h
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\m92f\\m92f.sig", sys->path);
				ech = E3DSigLoad( loadname, 0, 0.039f, &hsid);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				//�����蔻�胂�f���̃��[�h
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\hitchk\\hitber.sig", sys->path);
				ech = E3DSigLoad( loadname, 0, 5.0f, &hit_hsid);//���f���̓ǂݍ���
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				//����X�v���C�g�̃��[�h
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\m92f\\pict.png", sys->path);
				ech = E3DCreateSprite( loadname, 1, 0, &g_spid);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				//����̃��[�V������ǂݍ���
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\m92f\\wait.qua", sys->path);
				ech = E3DAddMotion( hsid, loadname, 1, &Garbage, &Garbage);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};


				/**/
				//�{�[���f�[�^�̃��[�h���s���܂�
				/**/

				//�{�[���l�[������{�[��ID�̎擾�u�e������_X+�v
				E3DGetBoneNoByName( hsid, "�e��", &bone[0]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};
				//�{�[���l�[������{�[��ID�̎擾�u�e�������_X+�v
				E3DGetBoneNoByName( hsid, "�e��", &bone[1]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};
				//�{�[���l�[������{�[��ID�̎擾�u�����蔻���v
				E3DGetBoneNoByName( hit_hsid, "�����蔻���", &bone[2]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};
				//�{�[���l�[������{�[��ID�̎擾�u�����蔻�荪�v
				E3DGetBoneNoByName( hit_hsid, "�����蔻�荪", &bone[3]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				//M92F�̃f�[�^���i�[���܂��B
				ammo = 15;
				mag = 2;
				distance = 120;
				attack = 80;
		}

	}
	if(gunkind == 4){//�A�T���g���C�t���n
	
		if(gunno == 0){//M4

				//���f���f�[�^�̃��[�h
				wsprintf( loadname, "%s\\data\\3d\\weapon\\assault\\m4\\m4a5.sig", sys->path);
				ech = E3DSigLoad( loadname, 0, 0.042f, &hsid);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				//�����蔻�胂�f���̃��[�h
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\hitchk\\hitber.sig", sys->path);
				ech = E3DSigLoad( loadname, 0, 5.0f, &hit_hsid);//���f���̓ǂݍ���
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				//����X�v���C�g�̃��[�h
				wsprintf( loadname, "%s\\data\\3d\\weapon\\assault\\m4\\pict.png", sys->path);
				ech = E3DCreateSprite( loadname, 1, 0, &g_spid);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				//����̃��[�V������ǂݍ���
				wsprintf( loadname, "%s\\data\\3d\\weapon\\handgun\\m1911\\wait.qua", sys->path);
				ech = E3DAddMotion( hsid, loadname, 1, &Garbage, &Garbage);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};


				/**/
				//�{�[���f�[�^�̃��[�h���s���܂�
				/**/

				/*//�{�[���l�[������{�[��ID�̎擾�u�e������_X+�v
				E3DGetBoneNoByName( hsid, "�e��", &bone[0]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};
				//�{�[���l�[������{�[��ID�̎擾�u�e�������_X+�v
				E3DGetBoneNoByName( hsid, "�e��", &bone[1]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};*/

				bone[0] = 0;//�e����O�̃{�[�����i�[
				bone[1] = 0;//�e�����̃{�[�����i�[

				//�{�[���l�[�����瓖���蔻��{�[��ID�̎擾�u�����蔻���v
				E3DGetBoneNoByName( hit_hsid, "�����蔻���", &bone[2]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};
				//�{�[���l�[������{�[��ID�̎擾�u�����蔻�荪�v
				E3DGetBoneNoByName( hit_hsid, "�����蔻�荪", &bone[3]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};


				//M4�̃f�[�^���i�[���܂��B
				ammo = 30;
				mag = 5;
				distance = 160;
				attack = 140;
		}
	}



	//�ϐ��������o�[�ϐ��Ɋi�[���܂�

	
		wp_data[selwp_kind][0][0] = hsid;//����̃��f�����i�[
		wp_data[selwp_kind][0][1] = g_spid;//����X�v���C�g���i�[
		wp_data[selwp_kind][0][2] = hit_hsid;//����̓����胂�f�����i�[
		wp_data[selwp_kind][0][3] = 0;//����̎g�p�ςݒe�򃂃f�����i�[
		wp_data[selwp_kind][1][0] = gunkind;//����̎�ނ��i�[
		wp_data[selwp_kind][1][1] = gunno;//����̃i���o�[���i�[
		wp_data[selwp_kind][1][2] = ammo;//�ő�e�򐔂��i�[
		wp_data[selwp_kind][1][3] = mag;//�ő�}�K�W�������i�[
		wp_data[selwp_kind][1][4] = distance;//�˒��������i�[
		wp_data[selwp_kind][1][5] = attack;//�˒��������i�[
		wp_data[selwp_kind][2][0] = bone[0];//�e����O�̃{�[�����i�[
		wp_data[selwp_kind][2][1] = bone[1];//�e�����̃{�[�����i�[
		wp_data[selwp_kind][2][4] = bone[2];//�e�����̃{�[�����i�[
		wp_data[selwp_kind][2][5] = bone[3];//�e�����̃{�[�����i�[
		wp_data[selwp_kind][3][0] = ammo;//!!��ŕς��邩��!!�e�򐔂������ς��ɂ���
		wp_data[selwp_kind][3][1] = mag;//!!��ŕς��邩��!!�}�K�W�����������ς��ɂ���

	return 0;
}


/*�v���C���[�L�����N�^�[�̃f�R���X�g���N�^*/
PlayerChara::~PlayerChara(){

	int ech = 0;//�G���[�m�F�ϐ��̏�����

	//�L�����N�^�[���f�����폜���܂�
	E3DDestroyHandlerSet( cha_hsid[0]);
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};

	//1�ڂ̃L�����N�^�[�_�~�[���f�����폜���܂�
	E3DDestroyHandlerSet( DummyModel);
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};

	//�e�̃f�[�^�̍폜���܂��i�ŏ����珇�ԂɃ��C���E�T�u�E�O���l�[�h�̏��Ԃł��j
	for(int i = 0;i < 3; i++){
		if( wp_data[i][0][0] != 0){//�I�𒆂̃J�e�S���Ƀf�[�^������̂Ȃ�
					ech = E3DDestroyHandlerSet( wp_data[i][0][0]);//���f�����폜���܂�
					if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
					};

					ech = E3DDestroySprite( wp_data[i][0][0]);//�X�v���C�g���폜���܂�
					if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
					};
		}
	}

	/**/
	//�N�H�[�^�j�I�����폜���܂�
	/**/	
	for(int i = 0; i<4; i++){
				ech = E3DDestroyQ( Qid[i]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};
	}


}