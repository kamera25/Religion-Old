#pragma once
/*�����ł́A�Q�[�����̃��j���[�Ɋւ��邱�Ƃ̃N���X�w�b�_�ł��B
//��Ƀ|�[�Y���j���[�N���X�ƃh�b�O���j���[�N���X�ɂ��ď�����Ă��܂��B
*/
#include "cMenu.h"

//�v���g�^�C�v�錾
class Batch_Render;
class PlayerChara;
class Weapon;
class Item;


class PoseMenu: public Menu{

public:

	int MenuEvent;// ���j���[�̃C�x���g��߂�l�Ƃ��Ď󂯎��܂�

	//�֐��̐錾
	PoseMenu();//�R���X�g���N�^�A���j���[��ʂŎg���X�v���C�g�����[�h���܂�
	virtual ~PoseMenu();//�f�R���g���N�^�A���j���[��ʂŎg�����X�v���C�g�Ȃǂ��폜���܂�
	int FarstInMenu( Batch_Render *BatchPre, PlayerChara *PC);//���j���[��ʂɓ����āA�����I�ɒʏ�`�惂�[�h���烁�j���[��ʂɔ����߂��Ă����܂��B
	int MainPoseMenu( PlayerChara *PC, Batch_Render *BatchPre);//�|�[�Y���j���[�ɓ���܂��A�K�v�Œ���̃��j���[�ł��B
	int PutStetus( PlayerChara *PC);//���̃X�e�[�^�X�̕\��
	int EventPublish();// �C�x���g�𔭍s���܂�

};