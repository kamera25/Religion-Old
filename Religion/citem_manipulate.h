#pragma once
/*�����́A�A�C�e������Ɋւ��邱�Ƃ̃N���X�ł��B
//��Ƀo�b�N�p�b�N��A�C�e�������ɂ��ď�����Ă��܂��B
*/

//�v���g�^�C�v�錾
class PlayerChara;
class Weapon;

class Item_Manipulate{

private:
	//�֐��̐錾
	int MainBackPack( PlayerChara *PC);//�o�b�N�p�b�N�̃��C���������s���܂�
	int PutItemDescript( int ChoseItem, int ItemNumber);//��������\�������鏈�����s���܂�
	int PutItemName( int ChoseItem, int ItemNumber);//����A�C�e������\�������鏈�����s���܂�


public:

	//�A�C�e���摜�̎��ʕϐ�
	int BackPack_Ammo[4][2];
	int BackPack_Recovery[5][2];
	int BackPack_Key[10][2];
	int BackPack_Weapon[4][3];
	int BackPack_Equipment[3][2];


	int TextID[3];
	int MenuSpriteIDs[10];

	//�֐��̐錾
	Item_Manipulate( PlayerChara *PC, Weapon *Wep);//�R���X�g���N�^�A�A�C�e���̃X�v���C�g�Ȃǂ����[�h���܂�
	~Item_Manipulate();//�f�R���g���N�^�A���[�h�����X�v���C�g�Ȃǂ��폜���܂�
	int InItemPack( PlayerChara *PC);//�A�C�e�������ɓ���摜�����Ȃǂ��s���܂�



};