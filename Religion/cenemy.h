#pragma once
/*�����ł́A�G���f����G�̓����Ɋւ��邱�Ƃ�
//�֐��������I�Ɏ��s���邱�Ƃ��ł���悤�ɂ��邽�߂̃N���X�w�b�_�t�@�C��
*/
#include "cweapon.h"//����Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��

#include "ccreature.h"// �����N���X�̃w�b�_�t�@�C��

//�v���g�^�C�v�錾
class Stage;

class Enemy{

private:

	/* �ϐ��̐錾 */
	int TargetNaviPointID[15];// �G���ڎw���i�r�|�C���g���i�[����Ă���ϐ�
	int TargetNaviLineID[15];// �G���ڎw���i�r���C�����i�[����Ă���ϐ�
	int CreatureRace[15];// �G�̎푰��������ϐ�
	int CreatureNumber[15];// �G�̎�ނ�������ϐ�

public:

	// �����o���ێ����Ă���N���X�n�ϐ�
	Creature* Ene[15];

	//�ϐ��̐錾
	int EnemyNum;//���݃��[�h����Ă��郂�f���̐�



	//�֐��̐錾
	Enemy();//�R���X�g���N�^�A�N���X�ϐ��̏��������s���܂�
	~Enemy();//�f�X�g���N�^�A���f���̍폜���s���܂�
	int LoadEnemyModel( const int Ene_Kind, const int Ene_No);//�G�����⃂�f�������[�h���邽�߂̊֐�
	int MoveEnemys( Stage *Stg);//�G�̓������܂Ƃ߂ē��������߂̊֐�
	int EnemySetPos();
	int SetEnemyPosByNaviPoint( Stage *Stg, const int EnemyNum, const int NaviLine, const int NaviPoint);// �G�̍��W���i�r�|�C���g����ɐݒ肵�܂�
	int SetEnemyPosByNaviPointArray( Stage *Stg, const int *EnemyOnNaviLine, int const *EnemyOnNaviPoint, const int ArrayMax);// �G�̍��W���܂Ƃ߂ăi�r�|�C���g����ɐݒ肵�܂�

};

