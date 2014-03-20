/*�����́A�A�C�e���Ɋւ��邱�Ƃ̃N���X�̃w�b�_�ł��B
//�Q�[�����ł̃A�C�e���S�ʂɂ��ď�����Ă��܂��B
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "citem.h"//�A�C�e���̐錾�w�b�_�t�@�C��


/* �R���X�g���N�^�A����������s�Ȃ��܂� */
Item::Item(){

	/* ********
	// ������
	// ********
	*/

	BringWp = 0;//�E������������������܂�

	// Ammo���̃f�[�^�����������܂�
	for( int i=0; i<4; i++){
			Ammo[i] = -1;		
	}

	/* !!�ȉ��A�e�X�g����!! */
	Ammo[0] = 0;


	return;
}
/* �i�[����Ă���A�C�e���i���o�[���擾���܂� */
int Item::GetItemNumber( const int ItemKind, const int ItemEle1, const int ItemEle2){

	/* �ϐ��̏����� */
	int Value = 0;// �Ԃ�l�A

	switch( ItemKind ){
		case 0:{
			Value = BringWp;
			break;
		}
		case 1:{
			Value = Ammo[ItemEle1];
			break;
		}
		case 2:{
			Value = Recovery[ItemEle1][ItemEle2];
			break;
		}
		case 3:{
			Value = Key[ItemEle1];
			break;
	    }
		case 4:{
			Value = Equipment[ItemEle1];
			break;
		}
		default:{
			Value = 0;
			_ASSERT(0);//�G���[�_�C�A���O��\��
		}
	}


	return Value;
}

