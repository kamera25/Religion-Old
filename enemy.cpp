#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <usercoef.h>//Easy3D�ŕK�v�Ȓǉ��w�b�_
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "resource1.h"//���\�[�X�t�@�C���Ƃ��̊֘A�t���w�b�_
#include <string.h>//�����񑀍�ŕK�v
#include <math.h>//���w�v�Z�Ŏg�p
#include <stdlib.h>//��������邽�߂̃w�b�_

#include "difine.h"


int Eneinfo[20][5];

int Eneload(){
	//�G�����[�h�����

	int Enekind = 3;
	int Eneno = 0;
	int ech;
	char loadname[MAX_PATH] = "";
	int Enenow = Iinfo[4][0];


	/*
	
	Eneinfo�̐���

	0:�G�̑��� 1:�G�̔ԍ� 2:���f���ԍ� 3:�K�E����

	*/

	Eneinfo[(Iinfo[4][0])][0] = Enekind;
	Eneinfo[(Iinfo[4][0])][1] = Eneno;

	if(Enekind ==3){//���@��
		if(Eneno == 0){//�����������[�h����Ȃ�

						wsprintf( loadname, "%s\\3d\\enemy\\Enecube.sig", pat);//�O�Ƃ������s���̃p�X��sig���o�^
						ech = E3DSigLoad( loadname, 0, 5, &Eneinfo[Enenow][2]);//���f���̓ǂݍ��݁AIinfo�փ��f��������B
						if(ech != 0 ){//�G���[�`�F�b�N
									_ASSERT( 0 );//�G���[�_�C�A���O
									return 1;//��肠��ŏI��
						};
						E3DGetPartNoByName ( Eneinfo[Enenow][2], "�K�E����", &Eneinfo[Enenow][3]);//�N���e�B�J�����o�镔�ʂ�ݒ�
						if(ech != 0 ){//�G���[�`�F�b�N
									_ASSERT( 0 );//�G���[�_�C�A���O
									return 1;//��肠��ŏI��
						};

		}

	}




	Iinfo[4][0]++;//�G�̑����ɑ���


	return 0;
}