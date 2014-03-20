/*�����ł́A�G���f����G�̓����Ɋւ��邱�Ƃ�
//�֐��������I�Ɏ��s���邱�Ƃ��ł���悤�ɂ��邽�߂̃N���X�R�[�h�t�@�C��
*/

#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_
#include "cstage.h"//�X�e�[�W�֌W�̃N���X�w�b�_�t�@�C��
#include "clive.h"//�G��L�����̃N���X�w�b�_�t�@�C��
#include "c_batch_preparat.h"//�`��ɕK�v�ȃN���X�̐錾�w�b�_�t�@�C��
#include "cenemy.h"//�G�N���X�̐錾�w�b�_�t�@�C��

//�����ɃO���[�o���ϐ���錾
extern System *sys;//�V�X�e���N���X���w���A�N���X�̃|�C���^


/*�R���X�g���N�^�A�N���X�ϐ��̏��������s���܂�*/
Enemy::Enemy(){

	/*���f���f�[�^������uEnemy_hsid�v�̏�����*/
	for(int i = 0; i<15; i++){
			Enemy_hsid[i] = 0;
	}

	/*�G�̐���0�ɂ���*/
	EnemyNum = 0;

}
/*�G�����⃂�f�������[�h���邽�߂̊֐�*/
int Enemy::LoadEnemyModel( int Ene_Kind, int Ene_No){

	//�ϐ��̏�����
	int ech = 0;//�G���[�`�F�b�N�ϐ��̏�����
	char loadname[256] = "";


	if( Ene_Kind == -1){//�e�X�g���f��
		if( Ene_No == 0){
				//�{���{�b�N�X�̎擾
				wsprintf( loadname, "%s\\data\\3d\\enemy\\valentine\\honmei\\honmeibox.sig", sys->path);
				ech = E3DSigLoad( loadname, 0, 0.3f, &Enemy_hsid[EnemyNum]);//���f���̓ǂݍ��݁AEnemy_hsid�փ��f��������B
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT(0);//�G���[�_�C�A���O
				};
		}
	};

	/*�e�X�g*/
	D3DXVECTOR3 CharaPos( 0.0, 1500.0, 0.0);//�G�l�~�[���ꉞ�u���ʒu
	/*���W���擾����*/
	ech = E3DSetPos( Enemy_hsid[EnemyNum], CharaPos);
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};

	/**/

	/*�G�l�~�[�̐�������₷*/
	EnemyNum = EnemyNum +1;


	return 0;
}
/*�G�̓������܂Ƃ߂ē��������߂̊֐�*/
int Enemy::MoveEnemys( Stage *Stg){

	//�ϐ��̏�����
	int ech = 0;//�G���[�`�F�b�N�ϐ��̏�����
	int TargetNaviPointID;//���ڎw���Ă���i�r�|�C���g���w�肵�܂�
	D3DXQUATERNION NewhsidQ;//�ړ���̃N�H�[�^�j�I���������܂�
	D3DXVECTOR3 NewhsidPos( 0.0, 0.0, 0.0);//�ړ���̍��W�������܂�

	/*�Ƃ肠�����i�r�|�C���g�����œ����悤�Ɏw�肷��A��X���G���\��*/
	if( Stg->Stage_ID == 3){
		for( int i=0; i<15; i++){
				if( Enemy_hsid[i] != 0){
						ech = E3DControlByNaviLine( Enemy_hsid[i], Stg->NaviLineID, 5, 1, 0, 200.0f, 50.0f, 200.0f, &NewhsidPos, &NewhsidQ, &TargetNaviPointID);
						if(ech != 0 ){//�G���[�`�F�b�N
									_ASSERT( 0 );//�G���[�_�C�A���O
						};
						ech = E3DSetPos( Enemy_hsid[i], NewhsidPos);
						if(ech != 0 ){//�G���[�`�F�b�N
									_ASSERT( 0 );//�G���[�_�C�A���O
						};
				}	
		}
	}




	return 0;
}
/*�f�X�g���N�^�A���f���̍폜���s���܂�*/
Enemy::~Enemy(){

	//�ϐ��̏�����
	int ech = 0;

	for(int i=0; i<EnemyNum; i++){//���[�h�������f���̐�����
			ech = E3DDestroyHandlerSet( Enemy_hsid[i]);//���f�����폜���܂�
			if(ech != 0 ){//�G���[�`�F�b�N
						_ASSERT( 0 );//�G���[�_�C�A���O
			};
	}

}