//�C���N���[�h����t�@�C����

#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <usercoef.h>//Easy3D�ŕK�v�Ȓǉ��w�b�_
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "resource1.h"//���\�[�X�t�@�C���Ƃ��̊֘A�t���w�b�_
#include <string.h>//�����񑀍�ŕK�v

#include "difine.h"


//�O���[�o���ϐ��̐錾




int SpriteRed(){

	int ech;
	int usewpno;
	int usewpkind;
	char metor[MAX_PATH] = "";


	D3DXVECTOR3 ldpos1( 0.0, 390.0, 0.0);
	D3DXVECTOR3 ldpos2( 508.0, 325.0, 0.0);
	D3DXVECTOR3 ldpos3( 508.0, 390.0, 0.0);
	D3DXVECTOR3 ldpos4( 23.0, 413.0, 0.0);
	D3DXVECTOR3 ldpos5( 23.0, 432.0, 0.0);
	D3DXVECTOR3 ldpos6( 532.0, 405.0, 0.0);
	D3DXVECTOR3 ldpos7( 532.0, 434.0, 0.0);
	D3DXVECTOR2 ftpos1( 555.0, 393.0);
	D3DXVECTOR2 ftpos2( 590.0, 395.0);
	D3DXVECTOR2 ftpos3( 555.0, 423.0);
	D3DXVECTOR2 ftpos4( 590.0, 425.0);
	D3DXVECTOR2 ftpos5( 30.0, 392.0);



	

	ech = E3DBeginScene( scid1,1);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI
	};


  E3DBeginSprite();

	//�{�҂Ŏg���摜�����_�����O

	ech = E3DRenderSprite( lddata[12], 1.0, 1.0, ldpos1);//�o�b�NHP&ST�p�����[�^�[
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI
	};

	ech = E3DRenderSprite( lddata[8], (double)Iinfo[3][1]/100.0*100.0, 1.0, ldpos4);//HP�o�[
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI
	};

	ech = E3DRenderSprite( lddata[9], (double)Iinfo[3][2]/100.0*100.0, 1.0, ldpos5);//STAMINA�o�[
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI
	};

	ech = E3DRenderSprite( lddata[6], 1.0, 1.0, ldpos1);//HP&ST�p�����[�^�[
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI
	};


	if(Iinfo[3][3] != -1){//�f��łȂ�������

			usewpkind = Iinfo[(Iinfo[3][3])][0];//�g���Ă镐��̎��
			usewpno = Iinfo[(Iinfo[3][3])][1];//�g���Ă镐��̃i���o�[

			ech = E3DRenderSprite( lddata[13], 1.0, 1.0, ldpos3);//�o�b�NAMM&MAG�p�����[�^�[
			if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
							return 1;//��肠��ŏI
			};
			

			ech = E3DRenderSprite( lddata[10], (double)Iinfo[ (Iinfo[3][3]) ][3] / wpitem[usewpkind][usewpno][5]*100.0, 1.0, ldpos6);//AMMO�o�[
			if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
							return 1;//��肠��ŏI
			};

			ech = E3DRenderSprite( lddata[11], (double)Iinfo[ (Iinfo[3][3]) ][4] / wpitem[usewpkind][usewpno][6]*100.0, 1.0, ldpos7);//MAG�o�[
			if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
							return 1;//��肠��ŏI
			};


			ech = E3DRenderSprite( wpitem[usewpkind][usewpno][0], 1.0, 1.0, ldpos2);//�e�I��IMG�̔z�u
			if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
							return 1;//��肠��ŏI
			};

			ech = E3DRenderSprite( lddata[7], 1.0, 1.0, ldpos3);//AMM&MAG�p�����[�^�[
			if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
							return 1;//��肠��ŏI
			};

	}

	E3DEndSprite();

	//�����̃����_�����O

	if(Iinfo[3][3] != -1){//�f��łȂ�������

					E3DCOLOR4UC col1= { 0,255,255,255};
					E3DCOLOR4UC col2= { 0,255,255,255};
					E3DCOLOR4UC col3= { 0,255,255,255};


					if(Iinfo[ (Iinfo[3][3]) ][3] <= (wpitem[usewpkind][usewpno][5] / 2)){//AMM�������ɂȂ�����
										col2.b = 0;
										col2.g = 255;
										col2.r = 255;
					}
					if(Iinfo[ (Iinfo[3][3]) ][3] == 0){//AMM��0�ɂȂ�����
										col2.b = 0;
										col2.g = 0;
										col2.r = 255;
					}
					if(Iinfo[ (Iinfo[3][3]) ][3] == wpitem[usewpkind][usewpno][5] + 1){//AMM��+1���ꂽ��
										col2.b = 255;
										col2.g = 150;
										col2.r = 0;
					}


					wsprintf( metor, "%d", (Iinfo[ (Iinfo[3][3]) ][3]));//�����Ă镐��̍���AMM
					E3DDrawText( ftpos1, 1.4, col2, metor);
					if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
								return 1;//��肠��ŏI
					};

					wsprintf( metor, "%d", (wpitem[usewpkind][usewpno][5]));//�����Ă镐��̍ő�AMM
					E3DDrawText( ftpos2, 1.5, col1, metor);
					if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
								return 1;//��肠��ŏI
					};

					wsprintf( metor, "%d", Iinfo[ (Iinfo[3][3]) ][4]);//�����Ă镐���MAG
					E3DDrawText( ftpos3, 1.4, col1, metor);
					if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
								return 1;//��肠��ŏI
					};

					wsprintf( metor, "%d", (wpitem[usewpkind][usewpno][6]));//�����Ă镐��̍ő�MAG
					E3DDrawText( ftpos4, 1.5, col1, metor);
					if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
								return 1;//��肠��ŏI
					};
	}

	if(Iinfo[3][0] == 0){
						E3DCOLOR4UC col= { 0,40,40,40};
						wsprintf( metor, "Arty" );
						E3DDrawText( ftpos5, 1.35, col, metor);
						if(ech != 0 ){//�G���[�`�F�b�N
									_ASSERT( 0 );//�G���[�_�C�A���O
									return 1;//��肠��ŏI
						};
	}

	
	ech = E3DEndScene();
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
				return 1;//��肠��ŏI		
	};
	

	E3DEndScene();



	return 0;
}




//�Q�[���̊j�̕����ł��B

int Ops1Render(){
	
	int render[15];
	int ech;

	render[0] = Iinfo[(Iinfo[3][3])][2];
	render[1] = grd1;
	render[2] = modelId[0];
	render[3] = modelId[1];
	render[3] = modelId[10];
	render[5] = modelId[11];
	render[6] = Eneinfo[0][2];//�e�X�g�ł��I



	ech = E3DRenderBatch( scid1, &render[0], 8, 1, 0);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI
					
	};

	return 0;

}

int Ops1Main(){

	int ech;
	int a;
	static int subjemode = 0;//��σ��[�h�ϐ�
	static int Weaponmode = 0;//����ύX���[�h�ϐ�


	//�e�֌W�̃V�X�e��

	if(keyin[14] == 1){//������σ��[�h�`�F���W�L�[�������ꂽ��
					Iinfo[3][4]++;
					if(Iinfo[3][4] == 1){
								SetCursorPos( recwindow.left + 320, recwindow.top + 240);//�}�E�X���E�B���h�E�^�񒆂ɐݒu
					}
					if(Iinfo[3][4] == 2){
								Iinfo[3][4] = 0;
					}
	}

	if(keyin[7] == 1){//������������L�[�������ꂽ��(z)
					Iinfo[3][3]++;
					if(Iinfo[3][3] == 1){
								Iinfo[3][3] = -1;//�f��̏�Ԃɖ߂�
					}
	}





	//E3DChkInView�Ń`�F�b�N!

	ech = E3DChkInView( scid1, grd1,&a);//�n�ʂ̓����蔻��
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};
	ech = E3DChkInView( scid1, wal1,&a);//�ǂ̓����蔻��
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};
	ech = E3DChkInView( scid1, modelId[11],&a);//�e�̓����蔻��
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};
	ech = E3DChkInView( scid1, modelId[0],&a);//��̓����蔻��
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};
	ech = E3DChkInView( scid1, modelId[1],&a);//�A�[�e�B�[�̔���
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};
	ech = E3DChkInView( scid1, modelId[10],&a);//�T�u���f��1�̔���
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};
	ech = E3DChkInView( scid1, modelId[12],&a);//�T�u���f��2�̔���
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};

	ech = E3DChkInView( scid1, Eneinfo[0][2],&a);//�I�e�X�g�ł��I
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};


	if((Iinfo[3][3]) != -1){
				ech = E3DChkInView( scid1, Iinfo[(Iinfo[3][3])][2],&a);//�������Ă��镐��̔���
				if(ech != 0 ){//�G���[�`�F�b�N
						_ASSERT( 0 );//�G���[�_�C�A���O
						return 1;//��肠��ŏI��
				};
	}




	
	Lunchergun( Iinfo[3][4], Iinfo[3][4], 0);//�ꎞ�I�ȏ����A�{�҂ł͊��ʏ���





	//��ʂ̃����_�����O
	Ops1Render();
	SpriteRed();

	E3DPresent(scid1);
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};


	E3DSetBeforePos( modelId[12]);//�ړ����f���̑O���W���擾
	if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
	};


	

	return 0;
}





//�I�y���[�V�������[�h��1�Ԗڂ̔C��
int Ops1HQ(){

	int ech;
	static int loaddt = 0;//�f�[�^�̃��[�h�󋵗p�̕ϐ�
	static int scmode = 0;//�Q�[�����[�h�̊m�F�ϐ�

	if(loaddt == 0){

			ech = loadimg();//���[�h��ʂ�\��
			if(ech != 0){//�G���[�`�F�b�N
					_ASSERT(0);//�G���[�_�C�A���O��\��
					return 1;//��肠��Ŋ֐��I��
			};
			grdload( 0, 1, 2, 0);//�n�ʂ����[�h
			gunload( 0, 0, 0);//�e�uM1911�v�����[�h
			Eneload();//�e�X�g�A�G�l�~�[�L���[�u�����[�h
			Iinfo[3][0] = 0;//������ID
			Iinfo[3][1] = 75;//HP
			Iinfo[3][2] = 75;//�X�^�~�i
			Iinfo[1][0] = -1;//�T�u������Ȃ���
			Iinfo[2][0] = -1;//�O���l�[�h������Ȃ���
			Iinfo[3][3] = -1;//����̎�ނ��u�f��v��
			Iinfo[3][4] = 0;//���샂�[�h���u3�l�́v��

			loaddt++;

	}
	
	keyout( 0, 1);//�L�[���͂��擾

	if(scmode == 0){//���[�h���Q�[�����[�h�Ȃ�
					
					if(keyin[15] == 1){//�����|�[�Y�L�[���������
									scmode = 1;
									int a = 250;
					}
					ech = Ops1Main();
					if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
								return 1;//��肠��ŏI��
					};

	}
	if(scmode == 1){//���[�h��؂�ւ����Ȃ�

			int static altime = 0;
			altime++;

			Ops1Render();//�Q�[����ʂ������_�����O

			E3DCOLOR4UC col= { 15*altime ,255,255,255};
			ech = E3DSetSpriteARGB( lddata[15], col);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			};
			ech = E3DSetSpriteARGB( lddata[16], col);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			};
			ech = E3DSetSpriteARGB( lddata[17], col);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			};

			E3DBeginScene(scid1,1);
			E3DBeginSprite();

			D3DXVECTOR3 ldpos1( 0.0, -25.0, 0.0);
			ech = E3DRenderSprite( lddata[15], 640.0/1024.0, 480.0/512.0, ldpos1);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			};
			D3DXVECTOR3 ldpos2( 0.0, -60.0, 0.0);
			ech = E3DRenderSprite( lddata[16], 1, 1, ldpos2);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			};

			D3DXVECTOR3 ldpos3( 380.0, 45.0, 0.0);
			ech = E3DRenderSprite( lddata[17], 1, 1, ldpos3);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			};

			E3DEndSprite();
			E3DEndScene();
			E3DPresent(scid1);

			if(altime == 17){
						scmode = 2;//���[�h���u�|�[�Y���j���[�Ɂv
						altime = 0;//�^�C����������
			}

	}
	if(scmode == 2){//�|�[�Y���[�h�Ȃ�
					Posemenu(&scmode);
	}

	if(scmode == 3){//�|�[�Y����Q�[���֐؂�ւ����Ȃ�

			int static altime = 17;
			altime--;

			Ops1Render();//�Q�[����ʂ������_�����O

			E3DCOLOR4UC col= { 15*altime ,255,255,255};
			ech = E3DSetSpriteARGB( lddata[15], col);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			};
			ech = E3DSetSpriteARGB( lddata[16], col);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			};
			ech = E3DSetSpriteARGB( lddata[17], col);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			};

			E3DBeginScene(scid1,1);
			E3DBeginSprite();

			D3DXVECTOR3 ldpos1( 0.0, -25.0, 0.0);
			ech = E3DRenderSprite( lddata[15], 640.0/1024.0, 480.0/512.0, ldpos1);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			};
			D3DXVECTOR3 ldpos2( 0.0, -60.0, 0.0);
			ech = E3DRenderSprite( lddata[16], 1, 1, ldpos2);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			};

			D3DXVECTOR3 ldpos3( 380.0, 45.0, 0.0);
			ech = E3DRenderSprite( lddata[17], 1, 1, ldpos3);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			};

			E3DEndSprite();
			E3DEndScene();
			E3DPresent(scid1);

			if(altime == 0){
						scmode = 0;//���[�h���Q�[���{�҂�
						altime = 17;//�^�C����������
			}

	}






	return 0;
}





