#pragma once
/*�����ł́A�X�e�[�W�̓ǂݍ��݁A������s���N���X�w�b�_�t�@�C���ł��B
//
*/
#include "cnavirail.h"//�i�r���[���Ɋւ���w�b�_�t�@�C��



class Stage{

private:



	/* ���ꂼ��̃X�e�[�W���[�h�֐��̐錾 */
	int LoadStage_Tronp( const int StageKind);// �g�����v�[���̓ǂݍ���
	int LoadStage_IRoby( const int StageKind);// �C���^�[�l�b�g���r�[�̓ǂݍ���
	int LoadStage_Mall( const int StageKind);// �����M�I�����[���̓ǂݍ��� 
	int LoadStage_Retolis( const int StageKind, float *FogDist);// ���g���X�̓ǂݍ���
	int LoadStage_Forest( const int StageKind, float *FogDist);// �X�т̓ǂݍ���
	int LoadStage_Kamigaichi( const int StageKind);// �_���꒬�̓ǂݍ���
	int LoadStage_BaseFront( const int StageKind);// ��n�O�̓ǂݍ���

	/* �֐��̐錾 */
	int SetStageLight( const int LightKind, const float FogDist);// �X�e�[�W�ɃZ�b�g���郉�C�g�̐ݒ���s�Ȃ��܂�
	int SetStageFog( const int LightKind);// ���̐ݒ���s���܂�

	int LoadStageFromProfile( const char *ProfPath);// �X�e�[�W�v���t�@�C������X�e�[�W�̓ǂݍ��݂��s���܂�

public:

	//�ϐ��̐錾
	int Stage_hsid[3];//�X�e�[�W���f���̃��f��ID���i�[���܂�
	int Wall_hsid[3];//�ǃ��f���̃��f��ID���i�[���܂�
	int Stage_ID;//�X�e�[�W���f���̐U�蕪��ID���i�[���܂�
	int Stage_Kind;//Stage_ID�̃X�e�[�W���f���̎�ނ��i�[���܂�
	int Stage_GndMode;//�n�ʂ̔��肷�鎞�ɂǂ̂悤�ɏ������邩���ʂ��܂�
	int Stage_GunTarget;//�e��n�ʂɌ����鎞�ɂǂ̂悤�ɏ������邩���ʂ��܂�
	bool AvailableBGFlag;// �w�i�����[�h����g����悤�ɂȂ��Ă��邩�̃t���O 

	int Light1_ID;//��ڂ̃��C�g�̎���ID
	int Light2_ID;//��ڂ̃��C�g�̎���ID

	//�����o�N���X�̐錾
	NaviRail Navi;

	/* �Ó������o�ϐ� */	
	static const int Morning = 0;// ��
	static const int Evening = 1;// �[��
	static const int Night = 2;// ��

	//�֐��̐錾
	int LoadStage( const int StageID, const int StageKind, const int LightKind);//�X�e�[�W�����[�h���邽�߂̊֐�
	Stage();// �X�e�[�W�N���X�̃R���X�g���N�^�A�������������s���܂�
	~Stage();// �X�e�[�W�̃f�R���X�g���N�^�A�}�b�v�Ȃǂ��폜���܂��B




};