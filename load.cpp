//�C���N���[�h����t�@�C����

#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <usercoef.h>//Easy3D�ŕK�v�Ȓǉ��w�b�_
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "resource1.h"//���\�[�X�t�@�C���Ƃ��̊֘A�t���w�b�_
#include <string.h>//�����񑀍�ŕK�v

#include "difine.h"


//�O���[�o���ϐ��̐錾

int wpitem[10][10][10];//�e��z��
int lddata[100];
int modelId[30];
int motionId[30];
int QId[30];
int BoneId[30];
int litid1;
int litid2;
int opimg;
int grd1;
int wal1;
int wpbone[30][15];
int Iinfo[5][15];
int FontID[5];


//���[�h�֐��̍쐬

int firstload(){
	
	//������
	char loadname[MAX_PATH] = "";
	int ech;
	int mult;
	int mov;


	//3D���f���̃��[�h


	//��֘A

	wsprintf( loadname, "%s\\3d\\model\\hand\\hand.sig", pat);//�O�Ƃ������s���̃p�X��sig���o�^
	ech = E3DSigLoad( loadname, 0, 0.4, &modelId[0]);//���f���̓ǂݍ��݁Ahsid1�փ��f��������B
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wsprintf( loadname, "%s\\3d\\model\\hand\\wait.qua", pat);//�O�Ƃ������s���̃p�X��sig���o�^
	ech = E3DAddMotion( modelId[0], loadname, 1.0, &motionId[0], &mult);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};


	 //�A�[�e�B�[�֘A
	



	wsprintf( loadname, "%s\\3d\\model\\demo\\hito.sig", pat);//�O�Ƃ������s���̃p�X��sig���o�^
	ech = E3DSigLoad( loadname, 0, 2.0, &modelId[1]);//���f���̓ǂݍ��݁Ahsid1�փ��f��������B
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};





	  //���̑��K�v�Ȃ���

	//�T�u���f���̃��[�h �I10��12�ł��I
	wsprintf( loadname, "%s\\3d\\model\\other\\demo.sig", pat);//�O�Ƃ������s���̃p�X��sig���o�^
	ech = E3DSigLoad( loadname, 0, 0.3, &modelId[10]);//���f���̓ǂݍ��݁Ahsid1�փ��f��������B
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wsprintf( loadname, "%s\\3d\\model\\other\\demo.sig", pat);//�O�Ƃ������s���̃p�X��sig���o�^
	ech = E3DSigLoad( loadname, 0, 1.0, &modelId[12]);//���f���̓ǂݍ��݁Ahsid1�փ��f��������B
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	//�����蔻�胂�f���̃��[�h
	wsprintf( loadname, "%s\\3d\\model\\demo\\hitber.sig", pat);//�O�Ƃ������s���̃p�X��sig���o�^
	ech = E3DSigLoad( loadname, 0, 200.0, &modelId[11]);//���f���̓ǂݍ��݁Ahsid1�փ��f��������B
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};


	 //�N�I���^�[�j�I���A�{�[���l�[���Ȃ�


	E3DCreateQ(&QId[0]);//��̏e�̌���
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};
	E3DCreateQ(&QId[1]);//�e���̌���
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};
	E3DCreateQ(&QId[2]);//�A�[�e�B�̎�̂ނ�
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};
	E3DCreateQ(&QId[3]);//�A�[�e�B�̏e�̌���
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};
	E3DCreateQ(&QId[4]);//�ړ�������ݒ肷��Q
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};


	//�{�[�����O


	//��̃{�[���l�[���擾
	E3DGetBoneNoByName( modelId[0], "������_X+", &BoneId[0]);//�E��̏e�茳�̈ʒu
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	E3DGetBoneNoByName( modelId[0], "�������_X+", &BoneId[1]);//�E��̏e��̈ʒu
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	

	//�A�[�e�B�[�̃{�[���l�[�����擾
	E3DGetBoneNoByName( modelId[1], "��̕���", &BoneId[2]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};



	//////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////


   //�X�v���C�g�����[�h&�e��̃f�[�^�����[�h

	//�e�E����n


	//�e�� 0:.45ACP 1:22L 2:9mm 3:5.7mm 4:�g�J���t�e 5:PMM 6:.357Mag 7:12GAGE 8:10GAGE
	//	   9:5.56mm 10:5.54mm 11:7.62mm 12:�� 13:40mm 14:HEAT 15:4.73


	// S+:3     S:5     A:8		A-:10  B+:13   B:15   B-:18	  C+:25   C:30   C-:35
	// S+:1100  S:1000  A+:800  A:700  B+:600  B:500  B-:450  C+:400  C:350  C-:300




	//�n���h�K��


	//M1911
	wsprintf( loadname, "%s\\3d\\weapon\\handgun\\m1911\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[0][0][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wpitem[0][0][1] = 0;//�e����
	wpitem[0][0][2] = 100;//�З�
	wpitem[0][0][3] = 15;//�A�˔\��
	wpitem[0][0][4] = 450;//�˒��\��
	wpitem[0][0][5] = 7;//���e��
	wpitem[0][0][6] = 10;//�}�K�W��

	
	//D.E
	wsprintf( loadname, "%s\\3d\\weapon\\handgun\\de\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[0][1][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wpitem[0][1][1] = 0;//�e����
	wpitem[0][1][2] = 100;//�З�
	wpitem[0][1][3] = 13;//�A�˔\��
	wpitem[0][1][4] = 400;//�˒��\��
	wpitem[0][1][5] = 5;//���e��
	wpitem[0][1][6] = 14;//�}�K�W��


	//Glock95
	wsprintf( loadname, "%s\\3d\\weapon\\handgun\\glock95\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[0][2][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wpitem[0][2][1] = 1;//�e����
	wpitem[0][2][2] = 30;//�З�
	wpitem[0][2][3] = 3;//�A�˔\��
	wpitem[0][2][4] = 400;//�˒��\��
	wpitem[0][2][5] = 50;//���e��
	wpitem[0][2][6] = 5;//�}�K�W��


	//M92F
	wsprintf( loadname, "%s\\3d\\weapon\\handgun\\m92f\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[0][3][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wpitem[0][3][1] = 2;//�e����
	wpitem[0][3][2] = 80;//�З�
	wpitem[0][3][3] = 10;//�A�˔\��
	wpitem[0][3][4] = 600;//�˒��\��
	wpitem[0][3][5] = 15;//���e��
	wpitem[0][3][6] = 6;//�}�K�W��


	//Five-seveN
	wsprintf( loadname, "%s\\3d\\weapon\\handgun\\five-seven\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[0][4][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wpitem[0][4][1] = 3;//�e����
	wpitem[0][4][2] = 60;//�З�
	wpitem[0][4][3] = 10;//�A�˔\��
	wpitem[0][4][4] = 350;//�˒��\��
	wpitem[0][4][5] = 17;//���e��
	wpitem[0][4][6] = 6;//�}�K�W��


	//�g�J���t
	wsprintf( loadname, "%s\\3d\\weapon\\handgun\\tokarev\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[0][5][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wpitem[0][5][1] = 4;//�e����
	wpitem[0][5][2] = 110;//�З�
	wpitem[0][5][3] = 15;//�A�˔\��
	wpitem[0][5][4] = 650;//�˒��\��
	wpitem[0][5][5] = 8;//���e��
	wpitem[0][5][6] = 8;//�}�K�W��


	//�}�J���t
	wsprintf( loadname, "%s\\3d\\weapon\\handgun\\makarova\\pict.bmp", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[0][6][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wpitem[0][6][1] = 5;//�e����
	wpitem[0][6][2] = 90;//�З�
	wpitem[0][6][3] = 13;//�A�˔\��
	wpitem[0][6][4] = 600;//�˒��\��
	wpitem[0][6][5] = 8;//���e��
	wpitem[0][6][6] = 9;//�}�K�W��


	//PYTHON
	wsprintf( loadname, "%s\\3d\\weapon\\handgun\\python\\pict.bmp", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[0][7][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wpitem[0][7][1] = 6;//�e����
	wpitem[0][7][2] = 130;//�З�
	wpitem[0][7][3] = 18;//�A�˔\��
	wpitem[0][7][4] = 600;//�˒��\��
	wpitem[0][7][5] = 6;//���e��
	wpitem[0][7][6] = 8;//�}�K�W��


	//SauerP22
	wsprintf( loadname, "%s\\3d\\weapon\\handgun\\sauerp226\\pict.bmp", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[0][8][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wpitem[0][8][1] = 2;//�e����
	wpitem[0][8][2] = 80;//�З�
	wpitem[0][8][3] = 13;//�A�˔\��
	wpitem[0][8][4] = 650;//�˒��\��
	wpitem[0][8][5] = 15;//���e��
	wpitem[0][8][6] = 5;//�}�K�W��

	
	//LugerP08
	wsprintf( loadname, "%s\\3d\\weapon\\handgun\\lugerp08\\pict.bmp", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[0][9][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wpitem[0][9][1] = 2;//�e����
	wpitem[0][9][2] = 80;//�З�
	wpitem[0][9][3] = 8;//�A�˔\��
	wpitem[0][9][4] = 300;//�˒��\��
	wpitem[0][9][5] = 32;//���e��
	wpitem[0][9][6] = 2;//�}�K�W��



	//�T�u�}�V���K��


	//TMP
	wsprintf( loadname, "%s\\3d\\weapon\\submachinegun\\tmp\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[1][0][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wpitem[1][0][1] = 2;//�e����
	wpitem[1][0][2] = 80;//�З�
	wpitem[1][0][3] = 8;//�A�˔\��
	wpitem[1][0][4] = 450;//�˒��\��
	wpitem[1][0][5] = 30;//���e��
	wpitem[1][0][6] = 5;//�}�K�W��


	//INGLAM
	wsprintf( loadname, "%s\\3d\\weapon\\submachinegun\\inglam\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[1][1][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wpitem[1][1][1] = 0;//�e����
	wpitem[1][1][2] = 100;//�З�
	wpitem[1][1][3] = 3;//�A�˔\��
	wpitem[1][1][4] = 300;//�˒��\��
	wpitem[1][1][5] = 20;//���e��
	wpitem[1][1][6] = 6;//�}�K�W��


	//TEC-9
	wsprintf( loadname, "%s\\3d\\weapon\\submachinegun\\tec-9\\pict.bmp", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[1][2][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wpitem[1][2][1] = 2;//�e����
	wpitem[1][2][2] = 80;//�З�
	wpitem[1][2][3] = 3;//�A�˔\��
	wpitem[1][2][4] = 300;//�˒��\��
	wpitem[1][2][5] = 20;//���e��
	wpitem[1][2][6] = 8;//�}�K�W��


	//UMP
	wsprintf( loadname, "%s\\3d\\weapon\\submachinegun\\ump\\pict.bmp", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[1][3][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wpitem[1][3][1] = 0;//�e����
	wpitem[1][3][2] = 100;//�З�
	wpitem[1][3][3] = 3;//�A�˔\��
	wpitem[1][3][4] = 450;//�˒��\��
	wpitem[1][3][5] = 25;//���e��
	wpitem[1][3][6] = 5;//�}�K�W��


	//PATRIOT
	wsprintf( loadname, "%s\\3d\\weapon\\submachinegun\\patriot\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[1][4][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};


	//�킩��Ȃ��B�_�~�[�f�[�^
	wpitem[1][4][1] = 0;//�e����
	wpitem[1][4][2] = 100;//�З�
	wpitem[1][4][3] = 8;//�A�˔\��
	wpitem[1][4][4] = 450;//�˒��\��
	wpitem[1][4][5] = 25;//���e��
	wpitem[1][4][6] = 5;//�}�K�W��



	//�V���b�g�K��


	//M1897
	wsprintf( loadname, "%s\\3d\\weapon\\shotgun\\m1897\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[2][0][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wpitem[2][0][1] = 7;//�e����
	wpitem[2][0][2] = 45;//�З�
	wpitem[2][0][3] = 25;//�A�˔\��
	wpitem[2][0][4] = 300;//�˒��\��
	wpitem[2][0][5] = 5;//���e��
	wpitem[2][0][6] = 63;//�}�K�W��


	//Benel M3
	wsprintf( loadname, "%s\\3d\\weapon\\shotgun\\benelm3\\pict.bmp", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[2][1][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};


	//////�����܂ō�ƏI��
	wpitem[2][1][1] = 7;//�e����
	wpitem[2][1][2] = 45;//�З�
	wpitem[2][1][3] = 18;//�A�˔\��
	wpitem[2][1][4] = 300;//�˒��\��
	wpitem[2][1][5] = 7;//���e��
	wpitem[2][1][6] = 61;//�}�K�W��


	//SPAS-12
	wsprintf( loadname, "%s\\3d\\weapon\\shotgun\\sppas-12\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[2][2][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wpitem[2][2][1] = 7;//�e����
	wpitem[2][2][2] = 45;//�З�
	wpitem[2][2][3] = 15;//�A�˔\��
	wpitem[2][2][4] = 500;//�˒��\��
	wpitem[2][2][5] = 7;//���e��
	wpitem[2][2][6] = 61;//�}�K�W��


	//Gold Stalke
	wsprintf( loadname, "%s\\3d\\weapon\\shotgun\\goldstalke\\pict.bmp", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[2][3][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wpitem[2][3][1] = 8;//�e����
	wpitem[2][3][2] = 72;//�З�
	wpitem[2][3][3] = 30;//�A�˔\��
	wpitem[2][3][4] = 650;//�˒��\��
	wpitem[2][3][5] = 2;//���e��
	wpitem[2][3][6] = 48;//�}�K�W��



	//�A�T���g���C�t��


	//M4
	wsprintf( loadname, "%s\\3d\\weapon\\assault\\m4\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[3][0][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wpitem[3][0][1] = 9;//�e����
	wpitem[3][0][2] = 140;//�З�
	wpitem[3][0][3] = 8;//�A�˔\��
	wpitem[3][0][4] = 700;//�˒��\��
	wpitem[3][0][5] = 30;//���e��
	wpitem[3][0][6] = 5;//�}�K�W��


	//RIS
	wsprintf( loadname, "%s\\3d\\weapon\\assault\\ris\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[3][1][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wpitem[3][1][1] = 9;//�e����
	wpitem[3][1][2] = 140;//�З�
	wpitem[3][1][3] = 8;//�A�˔\��
	wpitem[3][1][4] = 700;//�˒��\��
	wpitem[3][1][5] = 20;//���e��
	wpitem[3][1][6] = 7;//�}�K�W��


	//ATRAS  5.56
	wsprintf( loadname, "%s\\3d\\weapon\\assault\\atras\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[3][2][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wpitem[3][2][1] = 9;//�e����
	wpitem[3][2][2] = 140;//�З�
	wpitem[3][2][3] = 8;//�A�˔\��
	wpitem[3][2][4] = 700;//�˒��\��
	wpitem[3][2][5] = 20;//���e��
	wpitem[3][2][6] = 5;//�}�K�W��


	//ATRAS  5.7
	wsprintf( loadname, "%s\\3d\\weapon\\assault\\atras\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[3][3][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wpitem[3][3][1] = 3;//�e����
	wpitem[3][3][2] = 60;//�З�
	wpitem[3][3][3] = 5;//�A�˔\��
	wpitem[3][3][4] = 400;//�˒��\��
	wpitem[3][3][5] = 10;//���e��
	wpitem[3][3][6] = 10;//�}�K�W��


	//AK-101
	wsprintf( loadname, "%s\\3d\\weapon\\assault\\ak-101\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[3][4][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wpitem[3][4][1] = 10;//�e����
	wpitem[3][4][2] = 170;//�З�
	wpitem[3][4][3] = 10;//�A�˔\��
	wpitem[3][4][4] = 800;//�˒��\��
	wpitem[3][4][5] = 30;//���e��
	wpitem[3][4][6] = 4;//�}�K�W��


	//G11
	wsprintf( loadname, "%s\\3d\\weapon\\assault\\g11\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[3][5][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wpitem[3][5][1] = 15;//�e����
	wpitem[3][5][2] = 120;//�З�
	wpitem[3][5][3] = 8;//�A�˔\��
	wpitem[3][5][4] = 700;//�˒��\��
	wpitem[3][5][5] = 45;//���e��
	wpitem[3][5][6] = 4;//�}�K�W��


	//M14
	wsprintf( loadname, "%s\\3d\\weapon\\assault\\m14\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[3][6][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wpitem[3][6][1] = 11;//�e����
	wpitem[3][6][2] = 200;//�З�
	wpitem[3][6][3] = 13;//�A�˔\��
	wpitem[3][6][4] = 900;//�˒��\��
	wpitem[3][6][5] = 20;//���e��
	wpitem[3][6][6] = 5;//�}�K�W��


	//G36
	wsprintf( loadname, "%s\\3d\\weapon\\assault\\g36\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[3][7][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wpitem[3][7][1] = 9;//�e����
	wpitem[3][7][2] = 140;//�З�
	wpitem[3][7][3] = 8;//�A�˔\��
	wpitem[3][7][4] = 700;//�˒��\��
	wpitem[3][7][5] = 30;//���e��
	wpitem[3][7][6] = 5;//�}�K�W��


	//�}�V���K��


	//BAR A2
	wsprintf( loadname, "%s\\3d\\weapon\\machinegun\\bara2\\pict.bmp", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[4][0][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wpitem[4][0][1] = 11;//�e����
	wpitem[4][0][2] = 200;//�З�
	wpitem[4][0][3] = 3;//�A�˔\��
	wpitem[4][0][4] = 700;//�˒��\��
	wpitem[4][0][5] = 20;//���e��
	wpitem[4][0][6] = 5;//�}�K�W��


	//MINIMI
	wsprintf( loadname, "%s\\3d\\weapon\\machinegun\\minimi\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[4][1][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wpitem[4][1][1] = 9;//�e����
	wpitem[4][1][2] = 140;//�З�
	wpitem[4][1][3] = 5;//�A�˔\��
	wpitem[4][1][4] = 1000;//�˒��\��
	wpitem[4][1][5] = 150;//���e��
	wpitem[4][1][6] = 1;//�}�K�W��


	//M2
	wsprintf( loadname, "%s\\3d\\weapon\\machinegun\\m2\\pict.bmp", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[4][2][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wpitem[4][2][1] = 11;//�e����
	wpitem[4][2][2] = 200;//�З�
	wpitem[4][2][3] = 8;//�A�˔\��
	wpitem[4][2][4] = 900;//�˒��\��
	wpitem[4][2][5] = 500;//���e��
	wpitem[4][2][6] = 1;//�}�K�W��


	//���C�t��


	//M700
	wsprintf( loadname, "%s\\3d\\weapon\\rifle\\m700\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[5][0][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wpitem[5][0][1] = 11;//�e����
	wpitem[5][0][2] = 200;//�З�
	wpitem[5][0][3] = 18;//�A�˔\��
	wpitem[5][0][4] = 1100;//�˒��\��
	wpitem[5][0][5] = 5;//���e��
	wpitem[5][0][6] = 30;//�}�K�W��


	//SR-25
	wsprintf( loadname, "%s\\3d\\weapon\\rifle\\sr-25\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[5][1][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wpitem[5][1][1] = 9;//�e����
	wpitem[5][1][2] = 140;//�З�
	wpitem[5][1][3] = 8;//�A�˔\��
	wpitem[5][1][4] = 1000;//�˒��\��
	wpitem[5][1][5] = 10;//���e��
	wpitem[5][1][6] = 21;//�}�K�W��


	//S.V.D
	wsprintf( loadname, "%s\\3d\\weapon\\rifle\\svd\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[5][2][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wpitem[5][2][1] = 11;//�e����
	wpitem[5][2][2] = 200;//�З�
	wpitem[5][2][3] = 13;//�A�˔\��
	wpitem[5][2][4] = 900;//�˒��\��
	wpitem[5][2][5] = 10;//���e��
	wpitem[5][2][6] = 15;//�}�K�W��


	//PSG-1
	wsprintf( loadname, "%s\\3d\\weapon\\rifle\\psg-1\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[5][3][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wpitem[5][3][1] = 11;//�e����
	wpitem[5][3][2] = 200;//�З�
	wpitem[5][3][3] = 13;//�A�˔\��
	wpitem[5][3][4] = 1100;//�˒��\��
	wpitem[5][3][5] = 5;//���e��
	wpitem[5][3][6] = 25;//�}�K�W��


	//X BOW
	wsprintf( loadname, "%s\\3d\\weapon\\rifle\\xbow\\pict.bmp", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[5][4][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wpitem[5][4][1] = 12;//�e����
	wpitem[5][4][2] = 30;//�З�
	wpitem[5][4][3] = 35;//�A�˔\��
	wpitem[5][4][4] = 1000;//�˒��\��
	wpitem[5][4][5] = 1;//���e��
	wpitem[5][4][6] = 300;//�}�K�W��



	//�O���l�[�h


	//GRENADE
	wsprintf( loadname, "%s\\3d\\weapon\\grenade\\grenade\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[6][0][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wpitem[6][0][1] = 16;//�e����
	wpitem[6][0][2] = 300;//�З�
	wpitem[6][0][3] = 0;//�A�˔\��
	wpitem[6][0][4] = 300;//�˒��\��
	wpitem[6][0][5] = 1;//���e��
	wpitem[6][0][6] = 5;//�}�K�W��


	//MGL
	wsprintf( loadname, "%s\\3d\\weapon\\grenade\\mgl\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[6][1][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wpitem[6][1][1] = 13;//�e����
	wpitem[6][1][2] = 250;//�З�
	wpitem[6][1][3] = 25;//�A�˔\��
	wpitem[6][1][4] = 700;//�˒��\��
	wpitem[6][1][5] = 6;//���e��
	wpitem[6][1][6] = 2;//�}�K�W��


	//M79
	wsprintf( loadname, "%s\\3d\\weapon\\grenade\\m79\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[6][2][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wpitem[6][2][1] = 13;//�e����
	wpitem[6][2][2] = 250;//�З�
	wpitem[6][2][3] = 30;//�A�˔\��
	wpitem[6][2][4] = 800;//�˒��\��
	wpitem[6][2][5] = 1;//���e��
	wpitem[6][2][6] = 12;//�}�K�W��



	//�����ށi���j


	//RPG-7
	wsprintf( loadname, "%s\\3d\\weapon\\other\\rpg-7\\pict.png", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[7][0][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wpitem[7][0][1] = 14;//�e����
	wpitem[7][0][2] = 280;//�З�
	wpitem[7][0][3] = 30;//�A�˔\��
	wpitem[7][0][4] = 1100;//�˒��\��
	wpitem[7][0][5] = 1;//���e��
	wpitem[7][0][6] = 10;//�}�K�W��


	//PANZER FAUST
	wsprintf( loadname, "%s\\3d\\weapon\\other\\panzer\\pict.png\0", pat);
	ech = E3DCreateSprite( loadname, 1, 0, &wpitem[7][1][0]);

	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wpitem[7][1][1] = 14;//�e����
	wpitem[7][1][2] = 310;//�З�
	wpitem[7][1][3] = 25;//�A�˔\��
	wpitem[7][1][4] = 400;//�˒��\��
	wpitem[7][1][5] = 1;//���e��
	wpitem[7][1][6] = 5;//�}�K�W��



   //����E����X�v���C�g�̃��[�h�I��

	//���j���[�Ŏg���X�v���C�g�����[�h
	wsprintf( loadname, "%s\\img\\ops\\op1.png\0", pat);
	ech = E3DCreateSprite( loadname, 0, 0, &opimg);

	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};



	//�X�^�[�g�\���ł̃��[�h
	wsprintf( loadname, "%s\\img\\ops\\pushkey.png\0", pat);
	ech = E3DCreateSprite( loadname, 0, 0, &lddata[0]);

	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wsprintf( loadname, "%s\\img\\ops\\1.png\0", pat);
	ech = E3DCreateSprite( loadname, 0, 0, &lddata[1]);

	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wsprintf( loadname, "%s\\img\\ops\\2.png\0", pat);
	ech = E3DCreateSprite( loadname, 0, 0, &lddata[2]);

	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wsprintf( loadname, "%s\\img\\ops\\3.png\0", pat);
	ech = E3DCreateSprite( loadname, 0, 0, &lddata[3]);

	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wsprintf( loadname, "%s\\img\\ops\\4.png\0", pat);
	ech = E3DCreateSprite( loadname, 0, 0, &lddata[4]);

	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	 //�I�y���[�V�������[�h�Ŏg�����̂����[�h

	wsprintf( loadname, "%s\\img\\opration\\yazirusi.png\0", pat);
	ech = E3DCreateSprite( loadname, 0, 0, &lddata[5]);

	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};



	 //�Q�[���{�Ғ��Ŏg�����̂����[�h

	wsprintf( loadname, "%s\\img\\main\\parometa1.png\0", pat);//HP&ST�p�����[�^�[
	ech = E3DCreateSprite( loadname, 1, 0, &lddata[6]);

	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wsprintf( loadname, "%s\\img\\main\\parometa2.png\0", pat);//AMM&MAG�p�����[�^�[
	ech = E3DCreateSprite( loadname, 1, 0, &lddata[7]);

	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wsprintf( loadname, "%s\\img\\main\\hpber.png\0", pat);//HP�o�[
	ech = E3DCreateSprite( loadname, 0, 0, &lddata[8]);

	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wsprintf( loadname, "%s\\img\\main\\stnber.png\0", pat);//�X�^�~�i�o�[
	ech = E3DCreateSprite( loadname, 0, 0, &lddata[9]);

	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wsprintf( loadname, "%s\\img\\main\\ammber.png\0", pat);//�e�e�o�[
	ech = E3DCreateSprite( loadname, 0, 0, &lddata[10]);

	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};


	wsprintf( loadname, "%s\\img\\main\\magber.png\0", pat);//�}�K�W���o�[
	ech = E3DCreateSprite( loadname, 0, 0, &lddata[11]);

	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};



	wsprintf( loadname, "%s\\img\\main\\parometa3.png\0", pat);//�o�b�NHP&ST�p�����[�^�[
	ech = E3DCreateSprite( loadname, 1, 0, &lddata[12]);

	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wsprintf( loadname, "%s\\img\\main\\parometa4.png\0", pat);//�o�b�NAMM&MAG�p�����[�^�[
	ech = E3DCreateSprite( loadname, 1, 0, &lddata[13]);

	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wsprintf( loadname, "%s\\img\\main\\+1.png\0", pat);//+1�V�X�e��
	ech = E3DCreateSprite( loadname, 1, 0, &lddata[14]);

	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wsprintf( loadname, "%s\\img\\pose\\posebg.png\0", pat);//�|�[�Y���j���[�ł̔w�i
	ech = E3DCreateSprite( loadname, 1, 0, &lddata[15]);

	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wsprintf( loadname, "%s\\img\\pose\\poseber.png\0", pat);//�|�[�Y���j���[�̔���
	ech = E3DCreateSprite( loadname, 1, 0, &lddata[16]);

	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	wsprintf( loadname, "%s\\img\\pose\\upposeber.png\0", pat);//�|�[�Y���j���[�̏㕔����
	ech = E3DCreateSprite( loadname, 1, 0, &lddata[17]);

	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};



	////////////////////////////////////////////////////
	///////////////////////////////////////////////////
	//////////////////////////////////////////////////



   //���̑����
	
	//�������܂��i�L���b���j

	ech = E3DCreateLight( &litid1 );//���C�g�����
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	ech = E3DCreateLight( &litid2 );//���C�g�����
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	//��id�쐬�I��

	//�����ݒ�����܂�

	ech = E3DSetProjection(100.0, 100000.0, 60.0);//�v���W�F�N�V�����̐ݒ�
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	//�ϐ��̏�����

	Iinfo[4][0] = 0;//�G�̐���0�ɂ���


	//�t�H���g�ԍ������܂��B

	E3DCreateFont( 35, 0, 800, 0, 0, 0, "MS P�S�V�b�N", &FontID[0]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	E3DCreateFont( 25, 0, 800, 0, 0, 0, "MS P�S�V�b�N", &FontID[1]);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};



	return 0;
}







int grdload(int grdid, int grdkd, int lightkd, int shodowkd){


	//�}�b�v�f�[�^�̃��[�h


	int ech;
	char loadname[MAX_PATH] = "";

	
	if(grdid == 0){//�g�����v�[��

		if(grdkd == 0){//����MAP
						wsprintf( loadname, "%s\\3d\\map\\st_trom\\trom.sig", pat);
						ech = E3DLoadSigFileAsGround(loadname, 50.0, 0, &grd1);
						if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
								return 1;//��肠��ŏI��
						};

						wsprintf( loadname, "%s\\3d\\map\\st_trom\\trom_wl2.mqo", pat);
						ech = E3DLoadMQOFileAsMovableArea(loadname, 50.0, &wal1);
						if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
								return 1;//��肠��ŏI��
						};
		};

		if(grdkd == 1){//���K�pMAP
						wsprintf( loadname, "%s\\3d\\map\\st_trom\\trom_tr.sig", pat);
						ech = E3DLoadSigFileAsGround(loadname, 50.0, 0, &grd1);
						if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
								return 1;//��肠��ŏI��
						};

						wsprintf( loadname, "%s\\3d\\map\\st_trom\\trom_trwall.mqo", pat);
						ech = E3DLoadMQOFileAsMovableArea(loadname, 50.0, &wal1);
						if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
								return 1;//��肠��ŏI��
						};
		};

		//*************//
		E3DCOLOR4UC col= {255,255,255,255};
		E3DSetLinearFogParams(1, col, 15000, 100000, -1);//�t�@�O�������܂��B
		if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
		};

	};

	/////////////////

	if(grdid == 1){//���r�[

		if(grdkd == 0){//����MAP
						wsprintf( loadname, "%s\\3d\\map\\st_trom\\trom.sig", pat);
						ech = E3DLoadSigFileAsGround(loadname, 50.0, 0, &grd1);
						if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
								return 1;//��肠��ŏI��
						};

						wsprintf( loadname, "%s\\3d\\map\\st_trom\\trom_wl2.mqo", pat);
						ech = E3DLoadMQOFileAsMovableArea(loadname, 50.0, &wal1);
						if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
								return 1;//��肠��ŏI��
						};
		};

		//*************//
		E3DCOLOR4UC col= {255,255,255,255};
		E3DSetLinearFogParams(1, col, 15000, 100000, -1);//�t�@�O�������܂��B
		if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
								return 1;//��肠��ŏI��
		}
	};


	 //�X�e�[�W���[�h����////////////////////////////
	////////////////////////////////////////////////



	//���C�g�̐ݒ�����܂��B

	if(lightkd == 0){//����

					D3DXVECTOR3 ldir1( -1.0, -1.0, -1.0);
					D3DXVECTOR3 ldir2( 1.0, 1.0, 1.0);
					E3DCOLOR4UC col= { 255, 255, 255, 255};

					//��ڂ̃��C�g�쐬
					ech = E3DSetDirectionalLight( litid1, ldir1, col);
					if( ech != 0){
								_ASSERT( 0 );
								return 1;
					};

					//��ڂ̃��C�g�쐬
					ech = E3DSetDirectionalLight( litid2, ldir2, col);
					if( ech != 0){
								_ASSERT( 0 );
								return 1;
					};

					//�w�i�����܂�
					wsprintf( loadname, "%s\\3d\\map\\360\\hare.jpg", pat);
					ech = E3DCreateBG(scid1, loadname, "", 0, 0, 1, 1000);
					if( ech != 0){
								_ASSERT( 0 );
								return 1;
					};
	}

	/////////////////
	if(lightkd == 1){//�[��

					D3DXVECTOR3 ldir1( -1.0, -1.0, -1.0);
					D3DXVECTOR3 ldir2( 1.0, 1.0, 1.0);
					E3DCOLOR4UC col= { 200, 50, 50, 255};

					//��ڂ̃��C�g��ݒ肷��B
					ech = E3DSetDirectionalLight( litid1, ldir1, col);
					if( ech != 0){
								_ASSERT( 0 );
								return 1;
					};

					//��ڂ̃��C�g��ݒ肷��B
					ech = E3DSetDirectionalLight( litid2, ldir2, col);
					if( ech != 0){
								_ASSERT( 0 );
								return 1;
					};

					//�w�i�����܂�
					wsprintf( loadname, "%s\\3d\\map\\360\\sunset.jpg", pat);
					ech = E3DCreateBG(scid1, loadname, "", 0, 0, 1, 1000);
					if( ech != 0){
								_ASSERT( 0 );
								return 1;
					};
	}

	////////////////
	if(lightkd == 2){//��

					D3DXVECTOR3 ldir1( -1.0, -1.0, -1.0);
					D3DXVECTOR3 ldir2( 1.0, 1.0, 1.0);
					E3DCOLOR4UC col= { 50, 50, 50, 255};

					//��ڂ̃��C�g��ݒ肷��B
					ech = E3DSetDirectionalLight( litid1, ldir1, col);
					if( ech != 0){
								_ASSERT( 0 );
								return 1;
					};

					//��ڂ̃��C�g��ݒ肷��B
					ech = E3DSetDirectionalLight( litid2, ldir2, col);
					if( ech != 0){
								_ASSERT( 0 );
								return 1;
					};

					//�w�i�����܂�
					wsprintf( loadname, "%s\\3d\\map\\360\\night.jpg", pat);
					ech = E3DCreateBG(scid1, loadname, "", 0, 0, 1, 1000);
					if( ech != 0){
								_ASSERT( 0 );
								return 1;
					};
	}




	return 0;
}



int gunload(int wpkind, int wpno, int wpmin_sub_gl){
//�e��̃��[�h�����܂��B
//�֐��f�[�^�@�e��̎��,�e��̃i���o�[,�e��͎�or��or�e



	char loadname[MAX_PATH] = "";
	int ech;
	int a;

	//�Q�[���{�҂ŕK�v�ȃf�[�^���i�[
	Iinfo[(wpmin_sub_gl)][0] = wpkind;//����̎�ނ��i�[
	Iinfo[(wpmin_sub_gl)][1] = wpno;//����̃i���o�[���i�[
	// 2: ���f�����i�[ 
	Iinfo[(wpmin_sub_gl)][3] = wpitem[(wpkind)][(wpno)][5];//����̑��e�����i�[
	Iinfo[(wpmin_sub_gl)][4] = wpitem[(wpkind)][(wpno)][6];//����̃}�K�W�������i�[
	Iinfo[(wpmin_sub_gl)][5] = 1;//����̎g�p��Ԃ��i�[ !1�Ȃ疢�g�p!

	/*
		Iinfo�̂���

		0:���C���E�F�|�� 1:�T�u�E�F�|�� 2:�O���l�[�h�n�@3:�������g�̃f�[�^ 4:���̑��̏�񂪓����Ă܂��B

		//���C���E�T�u�E�F�|���E�O���l�[�h�n�̃f�[�^�֌W
		0:����̎�� 1:����̃i���o�[ 2:Sig�̏�� 3:AMM�̃f�[�^ 4:MAG�̃f�[�^ 5:����̎g�p���

		//�������g
		0:�L������ID 1:������HP 2:�����̃X�^�~�i 3:���݂̑������ 4:���샂�[�h�̏��

		//���̑��̏��
		0:�G�̑���

	*/

	if(wpkind == 0){//�n���h�K��

		if(wpno == 0){//M1911�Ȃ�

						wsprintf( loadname, "%s\\3d\\weapon\\handgun\\m1911\\m1911.sig", pat);//�O�Ƃ������s���̃p�X��sig���o�^
						ech = E3DSigLoad( loadname, 0, 0.1, &Iinfo[(wpmin_sub_gl)][2]);//���f���̓ǂݍ��݁AIinfo�փ��f��������B
						if(ech != 0 ){//�G���[�`�F�b�N
									_ASSERT( 0 );//�G���[�_�C�A���O
									return 1;//��肠��ŏI��
						};

						//�{�[���擾
						ech = E3DGetBoneNoByName( Iinfo[(wpmin_sub_gl)][2], "�e��", &Iinfo[(wpmin_sub_gl)][6]);
						if(ech != 0 ){//�G���[�`�F�b�N
									_ASSERT( 0 );//�G���[�_�C�A���O
									return 1;//��肠��ŏI��
						};
						ech = E3DGetBoneNoByName( Iinfo[(wpmin_sub_gl)][2], "�e��", &Iinfo[(wpmin_sub_gl)][7]);
						if(ech != 0 ){//�G���[�`�F�b�N
									_ASSERT( 0 );//�G���[�_�C�A���O
									return 1;//��肠��ŏI��
						};
						ech = E3DGetBoneNoByName( Iinfo[(wpmin_sub_gl)][2], "��i��", &Iinfo[(wpmin_sub_gl)][8]);
						if(ech != 0 ){//�G���[�`�F�b�N
									_ASSERT( 0 );//�G���[�_�C�A���O
									return 1;//��肠��ŏI��
						};
						ech = E3DGetBoneNoByName( Iinfo[(wpmin_sub_gl)][2], "�e�ۍ�", &Iinfo[(wpmin_sub_gl)][9]);
						if(ech != 0 ){//�G���[�`�F�b�N
									_ASSERT( 0 );//�G���[�_�C�A���O
									return 1;//��肠��ŏI��
						};
						ech = E3DGetBoneNoByName( Iinfo[(wpmin_sub_gl)][2], "�X���C�h��", &Iinfo[(wpmin_sub_gl)][10]);
						if(ech != 0 ){//�G���[�`�F�b�N
									_ASSERT( 0 );//�G���[�_�C�A���O
									return 1;//��肠��ŏI��
						};
						ech = E3DGetBoneNoByName( Iinfo[(wpmin_sub_gl)][2], "�X���C�h��", &Iinfo[(wpmin_sub_gl)][11]);
						if(ech != 0 ){//�G���[�`�F�b�N
									_ASSERT( 0 );//�G���[�_�C�A���O
									return 1;//��肠��ŏI��
						};



						wsprintf( loadname, "%s\\3d\\weapon\\handgun\\m1911\\wait1.qua", pat);//�O�Ƃ������s���̃p�X��sig���o�^
						ech = E3DAddMotion( Iinfo[(wpmin_sub_gl)][2], loadname, 1.0, &Iinfo[(wpmin_sub_gl)][14], &a);
						if(ech != 0 ){//�G���[�`�F�b�N
									_ASSERT( 0 );//�G���[�_�C�A���O
									return 1;//��肠��ŏI��
						};




		}
		if(wpno == 2){//M92fs�Ȃ�


						//���f���ǂݍ���
						wsprintf( loadname, "%s\\3d\\weapon\\handgun\\m92f\\m92f.sig", pat);//�O�Ƃ������s���̃p�X��sig���o�^
						ech = E3DSigLoad( loadname, 0, 0.1, &Iinfo[(wpmin_sub_gl)][2]);//���f���̓ǂݍ��݁Ahsid1�փ��f��������B
						if(ech != 0 ){//�G���[�`�F�b�N
									_ASSERT( 0 );//�G���[�_�C�A���O
									return 1;//��肠��ŏI��
						};

						//�{�[���擾
						ech = E3DGetBoneNoByName( Iinfo[(wpmin_sub_gl)][2], "�e��", &Iinfo[(wpmin_sub_gl)][6]);
						if(ech != 0 ){//�G���[�`�F�b�N
									_ASSERT( 0 );//�G���[�_�C�A���O
									return 1;//��肠��ŏI��
						};
						ech = E3DGetBoneNoByName( Iinfo[(wpmin_sub_gl)][2], "�e��", &Iinfo[(wpmin_sub_gl)][7]);
						if(ech != 0 ){//�G���[�`�F�b�N
									_ASSERT( 0 );//�G���[�_�C�A���O
									return 1;//��肠��ŏI��
						};
						ech = E3DGetBoneNoByName( Iinfo[(wpmin_sub_gl)][2], "��i��", &Iinfo[(wpmin_sub_gl)][8]);
						if(ech != 0 ){//�G���[�`�F�b�N
									_ASSERT( 0 );//�G���[�_�C�A���O
									return 1;//��肠��ŏI��
						};
						ech = E3DGetBoneNoByName( Iinfo[(wpmin_sub_gl)][2], "�e�ۍ�", &Iinfo[(wpmin_sub_gl)][9]);
						if(ech != 0 ){//�G���[�`�F�b�N
									_ASSERT( 0 );//�G���[�_�C�A���O
									return 1;//��肠��ŏI��
						};
		
						wsprintf( loadname, "%s\\3d\\weapon\\handgun\\m92f\\wait.qua", pat);//�O�Ƃ������s���̃p�X��sig���o�^
						ech = E3DAddMotion( Iinfo[(wpmin_sub_gl)][2], loadname, 1.0, &Iinfo[(wpmin_sub_gl)][10], &a);
						if(ech != 0 ){//�G���[�`�F�b�N
									_ASSERT( 0 );//�G���[�_�C�A���O
									return 1;//��肠��ŏI��
						};


		}


	}


	return 0;
}