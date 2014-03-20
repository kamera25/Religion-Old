#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include <list>

#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_
#include "cStory.h"

using namespace std;


Story::Story(){

	/* ������ */
	int ech;
	char loadname[256];

	/* �X�v���C�g�̃��[�h */
	wsprintf( loadname, "%s\\data\\img\\story\\namebar.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &NamebarID);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	wsprintf( loadname, "%s\\data\\img\\story\\mesbar.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &MessagebarID);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	wsprintf( loadname, "%s\\data\\img\\story\\cursor.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &CursorID);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/* �b��I�ȏ��� */
	wsprintf( loadname, "%s\\data\\img\\face\\arty\\0.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &CharaImg[0]);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	wsprintf( loadname, "%s\\data\\img\\face\\vill\\0.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &CharaImg[1]);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N
	/* �b��I�ȏ����@�����܂� */

	ech = E3DCreateFont( 25, 0, 800, 0, 0, 0, "MS P�S�V�b�N", &Font);//�啶��
	_ASSERT( ech != 1 );//�G���[�`�F�b�N


	return;
}


int Story::LoadStoryFromSTD( char *LoadPath){

	/* ������ */
	int CharaID;
	int FaceID;

	char LoadFullPath[256];
	FILE *fp;
	StoryData StrDat;

	/* �t�@�C���̃I�[�v���̏��� */
	wsprintf( LoadFullPath, "%s\\data\\prof\\story\\%s", System::path, LoadPath);
	fopen_s( &fp, LoadFullPath, "r");//�w�肳�ꂽ�t�@�C�����I�[�v�����܂��B 
	if( fp == NULL){
		_ASSERT( 0 );
		return -1;
	}


	for( int i = 0; fscanf_s( fp, "%d %d %s %s", &CharaID, &FaceID, &StrDat.Name, 32, &StrDat.Text, 256 ) !=EOF ; i++){
		
		/* ������ */
		int k = 0;
		char *str1;
		char str2[256];

		/* �ꎞ�I�ȏ��� */
		switch(CharaID){
			case 0:{ //�A�[�e�B
				StrDat.ImgID = 0;
				break;
			}
			case 1:{//���B��
				StrDat.ImgID = 1;
				break;
			}
		}

		str1 = &StrDat.Text[0];
		/* \n �� 'NewLine�R�[�h'�ɕϊ����� */
		while( *str1 != '\0'){
			if( *str1 == '\\' && *(str1 + 1) == 'n'){

				str2[k] = '\n';
				str1++;
			}
			else{
				str2[k] = *str1;
			}


			k++;
			str1++;

		}
		str2[k] = '\0';

		strcpy_s( StrDat.Text, str2);
		/* �ꎞ�I�ȏ����I��� */

		StoryList.push_back(StrDat);
	}

	if( fclose(fp) == EOF){
		return -1;
	}
		


	return 0;
}

int Story::StartStory( int StoryID){

	/* ������ */
	int ech;
	const E3DCOLOR4UC Black = { 255, 0, 0, 0};//�F�\���́A�����w��
	list<StoryData>::iterator it = StoryList.begin();

	while( it != StoryList.end() && WM_QUIT != System::msg.message){

		System::KeyRenewal(1);

		while( WM_QUIT != System::msg.message){
			
			System::KeyRenewal(1);

			ech = E3DBeginScene( System::scid1, 0, -1);
			_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

			ech = E3DBeginSprite();
			_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

			/* �X�v���C�g�̕`�� */
			D3DXVECTOR3 MesBarPos( 20, 310, 0);//�`��ʒu���w�肷��\����
			ech = E3DRenderSprite( MessagebarID, 590.0 /1024.0, 135.0/256.0, MesBarPos);
			_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

			/* �L�����`�� */
			D3DXVECTOR3 CharaImgPos( 35, 280, 0);//�`��ʒu���w�肷��\����
			ech = E3DRenderSprite( CharaImg[ (*it).ImgID ], 1.0, 1.0, CharaImgPos);
			_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

			D3DXVECTOR3 NameBarPos( 25, 408, 0);//�`��ʒu���w�肷��\����
			ech = E3DRenderSprite( NamebarID, 141.0 / 256.0, 41.0 / 64.0, NameBarPos);
			_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

			D3DXVECTOR3 CursorPos( 580, 410, 0);//�`��ʒu���w�肷��\����
			ech = E3DRenderSprite( CursorID, 46.0 / 64.0, 1.0, CursorPos);
			_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

			ech = E3DEndSprite();
			_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

			/* �����܂ŁA�X�v���C�g�`�� */

			/* ��������A�t�H���g�`�� */
			POINT Pos = { 178, 340};//���W��������\����
			ech = E3DDrawTextByFontID( System::scid1, Font, Pos, (*it).Text, Black );//������������Ă��镶�����\������
			_ASSERT( ech != 1 );//�G���[�`�F�b�N

			POINT NamePos = { 70, 415};//���W��������\����
			ech = E3DDrawTextByFontID( System::scid1, Font, NamePos, (*it).Name, Black );//������������Ă��镶�����\������
			_ASSERT( ech != 1 );//�G���[�`�F�b�N

			/* �����܂� */


			ech = E3DEndScene();
			_ASSERT( ech != 1 );//�G���[�`�F�b�N

			ech = E3DPresent( System::scid1);
			_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

			/* ���N���b�N���ꂽ�� */
			if( System::GetKeyData( System::KEY_LEFTMOUSE) == 1){
				break;
			}

			System::MsgQ(30);//���b�Z�[�W���[�v
		}

		it++;

	}






	return 0;
}
