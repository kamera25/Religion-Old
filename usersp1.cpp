//�C���N���[�h����t�@�C����
#include <windows.h>
#include "difine.h"

int keyin[20];


//�L�[����͂��ꂽ��z��ɑ������֐��B
int keyout(int keydev, int stuate){

	//���������܂�

	int i = 0;
	while(i <= 20){
			
		keyin[i] = 0;
		i++;
	}
	i=0;


	if(keydev == 0){//�����L�[�{�[�h����̌��o�Ȃ�

		if(stuate == 0){//�������j���[�ł̌��o�Ȃ�
				int imput1;
				int imput2;
				kabaddi( &imput1, &imput2, 0 , 0 );
				if(imput1 & 1<<5){//�G���^�[
						keyin[0] = 1;
				}
				if(imput2 & 1<<19){//�o�b�N�X�y�[�X
						keyin[1] = 1;
				}
				if(imput1 & 1<<0){//��
						keyin[2] = 1;
				}
				if(imput1 & 1<<1){//��
						keyin[3] = 1;
				}
				if(imput1 & 1<<2){//��
						keyin[4] = 1;
				}
				if(imput1 & 1<<3){//��
						keyin[5] = 1;
				}

		}

		/////////////////////
		////////////////////

		if(stuate == 1){//�����Q�[�����ł̌��o�Ȃ�

				int imput1;
				int imput2;

				kabaddi( &imput1, &imput2, (1<<10)+(1<<13)+(1<<28), (1<<2) );
				if(imput1 & (1<<10)){//A�L�[�i���ֈړ��j
					keyin[0] = 1;
				}
				if(imput2 & (1<<2)){//W�L�[�i�O�i����j
						keyin[1] = 1;
				}
				if(imput1 & (1<<13)){//D�L�[�i�E�ֈړ��j
						keyin[2] = 1;
				}
				if(imput1 & (1<<28)){//S�L�[�i��ނ���j
						keyin[3] = 1;
				}
				if(imput1 & (1<<27)){//R�L�[�i�����[�h�j
						keyin[4] = 1;
				}
				if(imput1 & (1<<14)){//E�L�[�i���ׂ�j
						keyin[5] = 1;
				}
				if(imput1 & (1<<10)){//Q�L�[�i�Z���؂�ւ��j
						keyin[6] = 1;
				}
				if(imput2 & (1<<5)){//Z�L�[�i�����g�p�j
						keyin[7] = 1;
				}
				if(imput1 & (1<<13)){//�V�t�g�L�[�i�p���؂�ւ��j
						keyin[8] = 1;
				}
				if(imput1 & (1<<7)){//���N���b�N�i�e�����j
						keyin[9] = 1;
				}
				if(imput1 & (1<<8)){//�E�N���b�N�i�O���l�[�h�j
						keyin[10] = 1;
				}
				if(imput1 & (1<<4)){//�X�y�[�X�i�i���U���j
						keyin[11] = 1;
				}
				if(imput1 & (1<<5)){//�G���^�[�L�[�i���ׂ�j
						keyin[12] = 1;
				}
				if(imput2 & (1<<1)){//V�L�[�i����\�́j
						keyin[13]=1;
				}
				if(imput2 & (1<<17)){//�z�C�[���N���b�N�i���_�ς��j
						keyin[14] = 1;
				}
				if(imput2 & (1<<16)){//ESC�L�[
						keyin[15] = 1;
				}



		}

		

		




	}






	return 0;
}