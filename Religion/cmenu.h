#pragma once
/*�����ł́A�Q�[�����̃��j���[�Ɋւ��邱�Ƃ̃N���X�w�b�_�ł��B
//��Ƀ|�[�Y���j���[�N���X�ƃh�b�O���j���[�N���X�ɂ��ď�����Ă��܂��B
*/

//�v���g�^�C�v�錾
class Batch_Preparat;
class PlayerChara;
class Weapon;
class Item;


class Menu{

public:

	//�ϐ��̐錾
	int MenuSpriteIDs[4];//���j���[�ł����X�v���C�g�摜��ID�z��
	int TextID[2];//�����̎��ʂ��i�[����ID�z��

	//�A�C�e���摜�̎��ʕϐ�
	int BackPack_Ammo[4];
	int BackPack_Recovery[5];
	int BackPack_Key[10];
	int BackPack_Weapon[4];
	int BackPack_Equipment[3];



	//�֐��̐錾
	Menu();//�R���X�g���N�^�A���j���[��ʂŎg���X�v���C�g�����[�h���܂�
	~Menu();//�f�R���g���N�^�A���j���[��ʂŎg�����X�v���C�g�Ȃǂ��폜���܂�
	int FarstInMenu( Batch_Preparat *BatchPre, PlayerChara *PC);//���j���[��ʂɓ����āA�����I�ɒʏ�`�惂�[�h���烁�j���[��ʂɔ����߂��Ă����܂��B
	int PoseMenu( PlayerChara *PC, Batch_Preparat *BatchPre);//�|�[�Y���j���[�ɓ���܂��A�K�v�Œ���̃��j���[�ł��B
	int PutStetus( PlayerChara *PC);//���̃X�e�[�^�X�̕\��

};