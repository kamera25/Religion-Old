//�C���N���[�h����t�@�C����

#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <usercoef.h>//Easy3D�ŕK�v�Ȓǉ��w�b�_
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "resource1.h"//���\�[�X�t�@�C���Ƃ��̊֘A�t���w�b�_
#include <string.h>//�����񑀍�ŕK�v

#include "difine.h"


//�O���[�o���ϐ��̐錾



//�Q�[�����ł̃|�[�Y���j���[�ł̃��[�v

int Posemenu(int *modsc){


			int ech;
			static int selemd = 0;
			D3DXVECTOR3 ldpos1( 0.0, -25.0, 0.0);
			D3DXVECTOR3 ldpos2( 0.0, -60.0, 0.0);
			D3DXVECTOR3 ldpos3( 380.0, 45.0, 0.0);
			E3DCOLOR4UC col= { 255,255,255,255};//���F�̑I�΂�Ă��Ȃ��F
			E3DCOLOR4UC selcol= { 255,200,220,20};//���F�̑I�΂�Ă���F
			POINT fontpos;
			POINT moupos;

			E3DBeginScene(scid1,0);
			E3DBeginSprite();
			
			ech = E3DRenderSprite( lddata[15], 640.0/1024.0, 480.0/512.0, ldpos1);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			};
			
			ech = E3DRenderSprite( lddata[16], 1, 1, ldpos2);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			};


			ech = E3DRenderSprite( lddata[17], 1, 1, ldpos3);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			};

			E3DEndSprite();


			//����
			fontpos.x = 440;
			fontpos.y = 5;
			E3DDrawTextByFontID( scid1, FontID[0], fontpos, "�|�[�Y���j���[", col);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			};



			fontpos.x = 100;


			fontpos.y = 140;//40��������
			E3DDrawTextByFontID( scid1, FontID[1], fontpos, "�Q�[���ɖ߂�", col);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			};

			fontpos.y = 180;//40��������
			E3DDrawTextByFontID( scid1, FontID[1], fontpos, "�o�b�N�p�b�N", col);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			};

			fontpos.y = 220;
			E3DDrawTextByFontID( scid1, FontID[1], fontpos, "�I�v�V����", col);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			};

			fontpos.y = 260;
			E3DDrawTextByFontID( scid1, FontID[1], fontpos, "�~�b�V�����𒆒f����", col);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			};

			fontpos.y = 300;
			E3DDrawTextByFontID( scid1, FontID[1], fontpos, "�Q�[�����I������", col);
			if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
			};


			//�ȉ��A���j���[�ł̏���

			GetCursorPos( &moupos );//�}�E�X���W���i�[

			moupos.x = moupos.x - recwindow.left;//�E�B���h�EX���W�̎擾
			moupos.y = moupos.y - recwindow.top;//�E�B���h�EY���W�̎擾

					if((100<moupos.x)&&(moupos.x<250)){	

								if((160<moupos.y)&&(moupos.y<190)){//�}�E�X���W���u�Q�[���ɖ߂�v�̏�Ȃ�
														selemd = 1;	//�I��ł郂�[�h��4�ɂ���
														fontpos.x = 100;
														fontpos.y = 140;
														E3DDrawTextByFontID( scid1, FontID[1], fontpos, "�Q�[���ɖ߂�", selcol);//�I������Ă��镶���ɂ���
														if(ech != 0 ){//�G���[�`�F�b�N
																_ASSERT( 0 );//�G���[�_�C�A���O
																return 1;//��肠��ŏI��
														};

														if(keyin[9] == 1){//�E�N���b�N����������
																*modsc = 3;//���[�h�`�F���W������
														}
								}

								if((320<moupos.y)&&(moupos.y<350)){//�}�E�X���W���u�Q�[�����I������v�̏�Ȃ�
														selemd = 5;	//�I��ł郂�[�h��4�ɂ���
														fontpos.x = 100;
														fontpos.y = 300;
														E3DDrawTextByFontID( scid1, FontID[1], fontpos, "�Q�[�����I������", selcol);//�I������Ă��镶���ɂ���
														if(ech != 0 ){//�G���[�`�F�b�N
																_ASSERT( 0 );//�G���[�_�C�A���O
																return 1;//��肠��ŏI��
														};

														if(keyin[9] == 1){//�E�N���b�N����������
																PostQuitMessage(0);//�Q�[�����I������
														}
								}
					}

			E3DEndScene();
			E3DPresent(scid1);



			return 0;
}