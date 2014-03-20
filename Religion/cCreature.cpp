/*�����ł́A�����N���X�̊֐����`����N���X�R�[�h�t�@�C���ł��B
//
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "ccreature.h"//�����N���X�̐錾�w�b�_�t�@�C��


/* ���C�t��X�^�~�i�Ȃǂ̑�����������֐� */
int Creature::Set_StateFromBranch( const int Branch){

	/* �\�� */
	// ���햼[Branch�̐���]
	//
	// ���C�t���}��[0]
	// �O���l�[�_�[[1]
	// �K���i�[    [2]
	// �X�i�C�p�[  [3]
	// ���f�B�b�N  [4]

	// �m�[�}��[default]

	Set_Branch( Branch);// �����̑����������܂�

	switch( Branch ){

		case 0:{// ���C�t���}��
			Set_MaxHP(1000);//�ő�HP�̑��
			Set_MaxStamina(800);//�ő�X�^�~�i�̑��
			Set_Attack(150);//�U���͂̑��
			Set_SkillSlot(6);//�X�L���X���b�g�̑��
			break;
		}
		case 1:{// �O���l�[�_�[
			Set_MaxHP(800);//�ő�HP�̑��
			Set_MaxStamina(900);//�ő�X�^�~�i�̑��
			Set_Attack(160);//�U���͂̑��
			Set_SkillSlot(8);//�X�L���X���b�g�̑��
			break;
		}
		case 2:{// �K���i�[ 
			Set_MaxHP(780);//�ő�HP�̑��
			Set_MaxStamina(650);//�ő�X�^�~�i�̑��
			Set_Attack(120);//�U���͂̑��
			Set_SkillSlot(8);//�X�L���X���b�g�̑��
			break;
		}
		case 3:{// �X�i�C�p�[
			Set_MaxHP(700);//�ő�HP�̑��
			Set_MaxStamina(600);//�ő�X�^�~�i�̑��
			Set_Attack(90);//�U���͂̑��
			Set_SkillSlot(12);//�X�L���X���b�g�̑��
			break;
		}
		case 4:{// ���f�B�b�N
			Set_MaxHP(670);//�ő�HP�̑��
			Set_MaxStamina(750);//�ő�X�^�~�i�̑��
			Set_Attack(120);//�U���͂̑��
			Set_SkillSlot(10);//�X�L���X���b�g�̑��
			break;
		}
		default:{// �m�[�}��
			Set_MaxHP(750);//�ő�HP�̑��
			Set_MaxStamina(750);//�ő�X�^�~�i�̑��
			Set_Attack(130);//�U���͂̑��
			Set_SkillSlot(1);//�X�L���X���b�g�̑��
			break;
		}
	}




	return 0;
}
/* �X�L���n�̔\�͂�ǉ�����֐�(��A�V�X�g�n) */
int Creature::Add_Skill( const int PlanSkill){

	/* �ϐ��̏����� */
	int SkillCostSum = 0;// �������X�L���R�X�g�̍��v
	int SkillCostSumAfter = 0;// �V�����R�X�g���w�肵���ꍇ�̑������X�L���R�X�g
	int SkillEQMAXSum = 0;// �ǉ�����\��̊��ɑ������̃X�L�����v


	// �萔�錾  "�X�L���R�X�g"	
	const int SKILL_COST[22] = {
		1,// �K���X�����K�[
		1,// ���x���I��
		1,// �o���|�[�`
		2,// 40mm�|�[�`
		1,// �T�|�[�^�[
		1,// �h�e�`���b�L
		2,// �P�u���[�x�X�g
		1,// �}�O�|�[�`
		1,// �t���b�c�w����
		1,// �R�}���h�[
		1,// �����i�[
		1,// �s�b�`���[
		1,// ��@�Ǘ�
		1,// �|�[�`
		2,//��̏e�e
		1,// �L������
		0,// �V���[�^�C��(�}�C�P��)
		1,// �X�v�����^�[
		1,// ��������
		1,// �S��
		5,// �s���̍�
		3// ���e��
	};


	// �萔�錾  "�X�L�����������"
	// EQMAX == EQuipment Max 
	const int SKILL_EQMAX[22] = {
		2,// �K���X�����K�[
		1,// ���x���I��
		3,// �o���|�[�`
		1,// 40mm�|�[�`
		2,// �T�|�[�^�[
		1,// �h�e�`���b�L
		1,// �P�u���[�x�X�g
		2,// �}�O�|�[�`
		1,// �t���b�c�w����
		1,// �R�}���h�[
		2,// �����i�[
		2,// �s�b�`���[
		1,// ��@�Ǘ�
		2,// �|�[�`
		1,//��̏e�e
		1,// �L������
		1,// �V���[�^�C��
		1,// �X�v�����^�[
		1,// ��������
		1,// �S��
		1,// �s���̍�
		1 // ���e��
	};


	/* ���݂���X�L�����ǂ����m�F����A�Ȃ���� */
	if( ( PlanSkill <= -1 ) || ( NumberSkill <= PlanSkill )){
			return -1;// ���s�ŃG���[����
	}


	/* ���񎞂̃X�L���ǉ��Ȃ� */
	if( EquipmentSkillSum == 0 ){

			SkillCostSumAfter = SKILL_COST[PlanSkill];
			if( SkillCostSumAfter <= SkillSlot ){// �R�X�g�m�F

					Skill = new int[1];// ���񎞂̂Ƃ��́A�X�L���i�[�ϐ��|�C���^�[�ɕϐ����쐬
					Skill[0] = PlanSkill;// �X�L�����
			}
			else{// �m�F���ǉ��ł��Ȃ��Ȃ�
					return -1;// �G���[�Ԃ�
			}
	}

	/* 2��ڈȍ~�̃X�L���ǉ��Ȃ� */
	if( 0 < EquipmentSkillSum ){
			
		/* �R�X�g���I�[�o�[���Ă��Ȃ����`�F�b�N */
		for( int i=0; i < EquipmentSkillSum ;i++){
				SkillCostSum = SkillCostSum + SKILL_COST[i];
		}

		/* �����\���𒴂��Ă��Ȃ����`�F�b�N */
		for( int i=0; i < EquipmentSkillSum ;i++){
				if( PlanSkill == Skill[i] ) SkillEQMAXSum++;
		}

		/* �X�L���������邱�Ƃ��\�Ȃ� */
		if( ( SkillEQMAXSum < SKILL_EQMAX[PlanSkill] ) &&
			( SkillCostSumAfter <= SkillSlot ) ){
					int *p;
					p = new int[(EquipmentSkillSum + 1)];

					/* new�ŐV����������X�L���i�[�ϐ��Ɍ��i�[�ϐ����R�s�[ */
					for( int i=0; i< EquipmentSkillSum; i++){
						p[i] = Skill[i];
					}
					p[ EquipmentSkillSum ] = PlanSkill;// ���̃X�L���z��ɃX�L�����

					delete [] Skill;
					Skill = p;
					

		}
		else{// �X�L�������s�Ȃ�
				return -1;//  �G���[�Ԃ�
		}
	}


	// �����A�X�L���R�X�g���v�ƃX�L�������\���𒴂��Ă��Ȃ����
	EquipmentSkillSum++;// �X�L���������v��"1"����


	return 0;
}
/* �X�L���n�̔\�͂��폜����֐�(��A�V�X�g�n) */
int Creature::Delete_Skill( const int PlanSkill){

	/* �ϐ��̏�����&�錾 */
	int FindAppropriateSkillFlg = 0;// �����ɂ����ăX�L���������o�������ǂ����̃t���O


	/* �����A�X�L�������Ă��Ȃ��̂ɍ폜���悤�Ƃ����� or  �������X�L���������Ⴂ�̐����Ȃ� */
	if( ( EquipmentSkillSum == 0) ||
		( PlanSkill <= -1 ) ||
		( NumberSkill <= PlanSkill) ){
			return -1;// �G���[�Ԃ�
	}


	/* �����A�X�L�����ЂƂ������ĂȂ������� */
	if( EquipmentSkillSum == 1){
			
			if( Skill[0] == PlanSkill){// ���Ă�X�L���Ə��������X�L���������Ȃ�
					delete [] Skill;
					Skill = NULL;
			}
			else{					 //  ���Ă�X�L���Ə��������X�L�����قȂ��
					return -1;//  �G���[�Ԃ�
			}
	}

	/* �����A�X�L����2�ȏ���Ă����� */
	if( 2 <= EquipmentSkillSum){

			for( int i=0; i < EquipmentSkillSum; i++){// �X�L������������
					if( Skill[i] == PlanSkill){
							Skill[i] = -1;
							FindAppropriateSkillFlg = 1;
							break;// ���[�v���甲����
					}
			}

			/* �����A�폜�������X�L���������ł��Ȃ���� */
			if( FindAppropriateSkillFlg == 0){
					return -1;//  �G���[�Ԃ�
			}
			
			/* �ȉ��A�X�L���폜�̏������s���܂� */
			int *p;
			int j = 0;

			p = new int[(EquipmentSkillSum - 1)];

			/* �V����������z��ɋ��z��̕ϐ����R�s�[ */
			for( int i=0; i < EquipmentSkillSum; i++){
					if( Skill[i] != -1){//  �폜���ꂽ�X�L���ϐ��ȊO��
							p[j] = Skill[i];// �X�L���ϐ����R�s�[
							j++;// p��p���[�v�J�E���^�[����
					}
			}

			delete [] Skill;
			Skill = p;
	}

	EquipmentSkillSum--;// �X�L���������v��"1"����



	return 0;
}