#pragma once
/* ����"coperation.h"�w�b�_�̓I�y���[�V�����N���X�ɂ��ď�����Ă��܂��B
// �I�y���[�V�����N���X�͎�ɃQ�[���{�҂̃V�X�e���̓����A�C��������s�Ȃ��܂�
/* /////////////////////////////////////////////////////////////////// */

#include "c_batch_preparat.h"//�`��ɕK�v�ȃN���X�̐錾�w�b�_�t�@�C��
#include "cPoseMenu.h"//���j���[�N���X�Ɋւ���w�b�_�t�@�C��
#include "ccamera.h"//�J�����֌W�̃N���X�w�b�_�t�@�C��


class Batch_Render;

class Operation{

private:

	/* �Q�[���{�҂Ŏg���N���X */
	Camera Cam; //�J�����N���X�̎���
	PoseMenu Menu; // ���j���[�N���X�̎���
	PlayerChara *pPly;// �v���C���[�L�����N�^�N���X�̃|�C���^
	Batch_Render *pBatP;// �o�b�`�v���p���[�g�N���X�̃|�C���^

	/* �~�b�V�����֐��錾 */
	int OpsMission1_Shinryoku();// �~�b�V����1 �V�΂̏���



public:

	/* �֐��̐錾 */
	int OpsMissionBranchStart( const int MissionNumber);
	int NormalBatchProces();//
	int OpsMissionFromFile( char *File);
};