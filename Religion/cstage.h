#pragma once
/*�����ł́A�X�e�[�W�̓ǂݍ��݁A������s���N���X�w�b�_�t�@�C���ł��B
//
*/
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B


class Stage{

public:

	//�ϐ��̐錾
	int Stage_hsid[3];//�X�e�[�W���f���̃��f��ID���i�[���܂�
	int Wall_hsid[3];//�ǃ��f���̃��f��ID���i�[���܂�
	int Stage_ID;//�X�e�[�W���f���̐U�蕪��ID���i�[���܂�
	int Stage_Kind;//Stage_ID�̃X�e�[�W���f���̎�ނ��i�[���܂�
	int Stage_GndMode;//�n�ʂ̔��肷�鎞�ɂǂ̂悤�ɏ������邩���ʂ��܂�
	int Stage_GunTarget;//�e��n�ʂɌ����鎞�ɂǂ̂悤�ɏ������邩���ʂ��܂�

	 //�i�r���C���n
	int NaviLineID;//�i�r���C�������ʂ��邽�߂�ID���i�[���܂�

	int Light1_ID;//��ڂ̃��C�g�̎���ID
	int Light2_ID;//��ڂ̃��C�g�̎���ID

	//�֐��̐錾
	int LoadStage(int StageID, int StageKind, int LightKind);//�X�e�[�W�����[�h���邽�߂̊֐�
	~Stage();//�X�e�[�W�̃f�R���X�g���N�^�A�}�b�v�Ȃǂ��폜���܂��B


};