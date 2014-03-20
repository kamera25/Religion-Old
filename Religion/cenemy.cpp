/*�����ł́A�G���f����G�̓����Ɋւ��邱�Ƃ�
//�֐��������I�Ɏ��s���邱�Ƃ��ł���悤�ɂ��邽�߂̃N���X�R�[�h�t�@�C��
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "cenemy.h"//�G�N���X�̐錾�w�b�_�t�@�C��
#include "cstage.h"//�X�e�[�W�֌W�̃N���X�w�b�_�t�@�C��
#include "csoldier.h"// ���m�N���X�̐錾�w�b�_�t�@�C��

#include <math.h>


/*�R���X�g���N�^�A�N���X�ϐ��̏��������s���܂�*/
Enemy::Enemy(){

	/* �ϐ��̏�����*/
	for(int i = 0; i<15; i++){
			Ene[i] = NULL;
			TargetNaviPointID[i] = -1;
			CreatureRace[i] = 0;
			CreatureNumber[i] = 0;
			TargetNaviLineID[i] = 0;
	}

	/*�G�̐���0�ɂ���*/
	EnemyNum = 0;

	/* �e�X�g */
	TargetNaviLineID[0] = 2;
	TargetNaviLineID[1] = 1;
	TargetNaviLineID[2] = 1;
	TargetNaviLineID[3] = 0;
	TargetNaviLineID[4] = 0;

	return;
}
/*�G�����⃂�f�������[�h���邽�߂̊֐�*/
int Enemy::LoadEnemyModel( const int Ene_Kind, const int Ene_No){

	//�ϐ��̏�����
	int ech = 0;//�G���[�`�F�b�N�ϐ��̏�����
	char loadname[256] = "";


	if( Ene_Kind == -1){//�e�X�g���f��
	}
	else if( Ene_Kind == 0){// �l��
			if( Ene_No == 0){// Wf��
					
					/* �N���[�`���[�N���X�|�C���^��ێ�����
					// �ϐ��ɕ��m�N���X�̃|�C���^���� */
					Ene[EnemyNum] = new Soldier( 1, 0);

					/* ���[�V�����w�� */
					Ene[EnemyNum]->Set_UpMotion( 0);
					Ene[EnemyNum]->Set_MyState( 0);
					Ene[EnemyNum]->Set_UnderMotion( 1);

					/* ����̃��[�h */
					Ene[EnemyNum]->Get_WeaponH()->WpLoad(0,0,0);// �A�T���g���C�t���̓���
			}
	}



	/* �푰�Ǝ�ނ������� */
	CreatureRace[EnemyNum] = Ene_Kind;
	CreatureNumber[EnemyNum] = Ene_No;


	/*�G�l�~�[�̐�������₷*/
	EnemyNum = EnemyNum +1;


	return 0;
}
/*�G�̓������܂Ƃ߂ē��������߂̊֐�*/
int Enemy::MoveEnemys( Stage *Stg){

	//�ϐ��̏�����
	int ech = 0;//�G���[�`�F�b�N�ϐ��̏�����
	int GroundResult = 0;

	D3DXVECTOR3 ReflectVec( 0.0, 0.0, 0.0);



	/*�Ƃ肠�����i�r�|�C���g�����œ����悤�Ɏw�肷��A��X���G���\��*/
	if( Stg->Navi.Get_NaviRailAvailable() == 1){
		for( int i=0; i<EnemyNum; i++){

			if( CreatureRace[i] == 0){
				if( CreatureNumber[i] == 0){
					
					if(0 < Ene[i]->Get_HP()){
							// �i�r���[���ɂ����PC�ʒu�����߂܂�
							Stg->Navi.PCControlByNaviRail( Ene[i]->Get_BodyModel(), &TargetNaviPointID[i], Stg->Navi.NaviLineID[ (TargetNaviLineID[i]) ]);
							
							Ene[i]->Set_UpMotion( 0);
							Ene[i]->Set_UnderMotion( 1);
					}
					else{// HP���Ȃ��Ȃ�
							Ene[i]->Set_MyState(5);// ���S��Ԃɂ���
					}

					// PC�̋󒆈ʒu�𐧌䂵�܂�
					//Ene[i]->MovePosOnGround( Stg);

					// ���[�V�����܂Ƃߏ���
					Ene[i]->Batch_PeopleMotion();
						
					// �������ɒu���܂�
					Ene[i]->GunPutOnHand();
				}
			}
		}
	}





	return 0;
}
/* �G�̍��W���i�r�|�C���g����ɐݒ肵�܂�*/
int Enemy::SetEnemyPosByNaviPoint( Stage *Stg, const int EnemyNum, const int NaviLine, const int NaviPoint){

	if( Stg->AvailableNaviLineFlag != true) return 0;// �i�r���C�������p�s�Ȃ�A������

	Stg->Navi.SetPosByNaviPoint( Ene[EnemyNum]->Get_BodyModel(), NaviLine, NaviPoint);

	return 0;
}
/* �G�̍��W���܂Ƃ߂ăi�r�|�C���g����ɐݒ肵�܂� */
int Enemy::SetEnemyPosByNaviPointArray( Stage *Stg, const int *EnemyOnNaviLine, int const *EnemyOnNaviPoint, const int ArrayMax){

	for(int i=0; i<ArrayMax; i++){
			SetEnemyPosByNaviPoint( Stg, i, *(EnemyOnNaviLine + i), *(EnemyOnNaviPoint + i));
	}



	return 0;
}
/*�f�X�g���N�^�A���f���̍폜���s���܂�*/
Enemy::~Enemy(){

	//�ϐ��̏�����
	int ech = 0;

	for( int i=0; i<15; i++){
			delete Ene[i];
	}

	return;
}