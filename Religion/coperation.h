#pragma once
/* ����"coperation.h"�w�b�_�̓I�y���[�V�����N���X�ɂ��ď�����Ă��܂��B
// �I�y���[�V�����N���X�͎�ɃQ�[���{�҂̃V�X�e���̓����A�C��������s�Ȃ��܂�
/* /////////////////////////////////////////////////////////////////// */

#include "cPoseMenu.h"//���j���[�N���X�Ɋւ���w�b�_�t�@�C��
#include "ccamera.h"//�J�����֌W�̃N���X�w�b�_�t�@�C��

class Operation{

private:

	/* �Q�[���{�҂Ŏg���N���X */
	Camera Cam; //�J�����N���X�̎���
	PoseMenu Menu; // ���j���[�N���X�̎���

	/* �~�b�V�����֐��錾 */
	int OpsMission1_Shinryoku();// �~�b�V����1 �V�΂̏���



public:

	/* �֐��̐錾 */
	int OpsMissionBranchStart( const int MissionNumber);


};