#pragma once
/*�����ł́A�G���f����G�̓����Ɋւ��邱�Ƃ�
//�֐��������I�Ɏ��s���邱�Ƃ��ł���悤�ɂ��邽�߂̃N���X�w�b�_�t�@�C��
*/

//�v���g�^�C�v�錾
class Stage;

class Enemy{

public:

	//�ϐ��̐錾
	int Enemy_hsid[15];//�G�̃��f��������z��ϐ�
	int Enemy_HP[15];//�G��HP��������z��ϐ�
	int Enemy_State[15];//�G�����񂾌�̏������w�肷��ϐ�
	int EnemyNum;//���݃��[�h����Ă��郂�f���̐�



	//�֐��̐錾
	Enemy();//�R���X�g���N�^�A�N���X�ϐ��̏��������s���܂�
	~Enemy();//�f�X�g���N�^�A���f���̍폜���s���܂�
	int LoadEnemyModel( int Ene_Kind, int Ene_No);//�G�����⃂�f�������[�h���邽�߂̊֐�
	int MoveEnemys( const Stage *Stg);//�G�̓������܂Ƃ߂ē��������߂̊֐�

};

