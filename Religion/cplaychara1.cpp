/*�����ł́A�����N���X�̃L�����E�G�̊֐����`����N���X�R�[�h�t�@�C���ł��B
//���ɃQ�[�����J�n���鎞�ɕK�v�Ȋ֐�������������Ă��܂��B
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "clive.h"//�G��L�����̐錾�w�b�_�t�@�C��





/*�v���C���[�L�����N�^�[�̃R���X�g���N�^*/
PlayerChara::PlayerChara( int selchara, int Wpselect_equipment){

	//�ϐ��̏�����
	int ech = 0;
	char loadname[256] = "";


	//�N���X�����o�ϐ��̏�����

	
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
				wsprintf( loadname, "%s\\data\\3d\\model\\demo\\hito.sig", System::path);//�A�[�e�B�[���f����sig���o�^
				ech = E3DSigLoad( loadname, 0, 0, &cha_hsid[0]);//���f���̓ǂݍ��݁Acha_hsid�փ��f��������B
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT(0);//�G���[�_�C�A���O
				};

				//�n���h���f���̎擾
				wsprintf( loadname, "%s\\data\\3d\\model\\hand\\hand.sig", System::path);//�n���h���f����sig���o�^
				ech = E3DSigLoad( loadname, 0, 1, &cha_hsid[1]);//���f���̓ǂݍ��݁Acha_hsid�փ��f��������B
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				//�_�~�[���f���̎擾
				wsprintf( loadname, "%s\\data\\3d\\model\\other\\demo.sig", System::path);//�����f����sig���o�^
				ech = E3DSigLoad( loadname, 0, 1, &DummyModel);//���f���̓ǂݍ��݁Asubmodid�փ��f��������B
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

	}

		if(selchara == 1){//WF��1���f��

				//WF��1���f���̎擾
				wsprintf( loadname, "%s\\data\\3d\\chara\\wf1\\model.sig", System::path);//�A�[�e�B�[���f����sig���o�^
				ech = E3DSigLoad( loadname, 0, 0.15f, &cha_hsid[0]);//���f���̓ǂݍ��݁Acha_hsid�փ��f��������B
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT(0);//�G���[�_�C�A���O
				};

				//�_�~�[���f���̎擾
				wsprintf( loadname, "%s\\data\\3d\\model\\other\\demo.sig", System::path);//�����f����sig���o�^
				ech = E3DSigLoad( loadname, 0, 0.01f, &DummyModel);//���f���̓ǂݍ��݁Asubmodid�փ��f��������B
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				//���[�V�����f�[�^�\��
				wsprintf( loadname, "%s\\data\\3d\\chara\\motion\\pc_motion.moa", System::path);//�����f����sig���o�^
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