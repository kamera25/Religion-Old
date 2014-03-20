#pragma once
/*�����ł́A�G���f����G�̓����Ɋւ��邱�Ƃ�
//�֐��������I�Ɏ��s���邱�Ƃ��ł���悤�ɂ��邽�߂̃N���X�w�b�_�t�@�C��
*/
#include <vector>
#include "cweapon.h"//����Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��
#include "ccreature.h"// �����N���X�̃w�b�_�t�@�C��

using namespace std;

//�v���g�^�C�v�錾
class Stage;

class NPC_t{

	friend class NPC_Head;

private:

	/* �ϐ� */
	int TargetNaviPointID;// NPC���ڎw���i�r�|�C���g���i�[����Ă���ϐ�
	int TargetNaviLineID;// NPC���ڎw���i�r���C�����i�[����Ă���ϐ�
	int NPCRace;// NPC�̎푰��������ϐ�
	int NPCNumber;// NPC�̎�ނ�������ϐ�

	int NPCBelongingKind;// NPC���������Ă���Ƃ����������ϐ�( 0.���� 1.�G )

	int NPCBehavior; // PC�̍s���ɂ��ď�Ԃ������܂�

	char NPCName[20];// NPC�̖��O�������܂�

	/* �֐� */

public:
	/* �ϐ� */
	Creature* NPC_Mdl;

};


class NPC_Head{

private:

	vector<NPC_t> NPC;

	/* �ϐ��̐錾 */
//	int TargetNaviPointID[15];// �G���ڎw���i�r�|�C���g���i�[����Ă���ϐ�
//	int TargetNaviLineID[15];// �G���ڎw���i�r���C�����i�[����Ă���ϐ�
//	int CreatureRace[15];// �G�̎푰��������ϐ�
//	int CreatureNumber[15];// �G�̎�ނ�������ϐ�
	/* �R���e�i */



public:

	// �����o���ێ����Ă���N���X�n�ϐ�
//	Creature* Ene[15];

	//�ϐ��̐錾
//	int EnemyNum;//���݃��[�h����Ă��郂�f���̐�






	//�֐��̐錾
	NPC_Head();//�R���X�g���N�^�A�N���X�ϐ��̏��������s���܂�
	~NPC_Head();//�f�X�g���N�^�A���f���̍폜���s���܂�
	int LoadEnemyModel( const int Ene_Kind, const int Ene_No);// �G�����⃂�f�������[�h���邽�߂̊֐�(���O�Ȃ�)
	int LoadEnemyModelAddName( const char *Name, const int Ene_Kind, const int Ene_No);// �G�����⃂�f�������[�h���邽�߂̊֐�(���O�t��)
	int MoveEnemys( Stage *Stg);//�G�̓������܂Ƃ߂ē��������߂̊֐�
	int EnemySetPos();
	int SetEnemyPosByNaviPoint( Stage *Stg, const char *Name, const int NaviLine, const int NaviPoint);// �G�̍��W���i�r�|�C���g����ɐݒ肵�܂�
	int SetEnemyPosByNaviPointArray( Stage *Stg, const char *Name, const int *EnemyOnNaviLine, int const *EnemyOnNaviPoint, const int ArrayMax);// �G�̍��W���܂Ƃ߂ăi�r�|�C���g����ɐݒ肵�܂�
	int SearchNPCFromName( const char *ObjName, vector<NPC_t>::iterator *it);

	/* �A�V�X�g�֐� */
	vector<NPC_t>::iterator NPC_endit();
	vector<NPC_t>::iterator Get_NPC_begin();
	bool Get_NPC_empty() const;

};

