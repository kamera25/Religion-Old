#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include <list>

#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_
#include "cStory.h"

using namespace std;


Story::Story(){

	/* ������ */

	/* �X�v���C�g�̃��[�h */

	LoadImg( "data\\img\\face\\arty\\0.png", &CharaImg[C_ARTY]);
	LoadImg( "data\\img\\face\\vill\\0.png", &CharaImg[C_VILL]);



	LoadImg( "data\\img\\story\\namebar.png", &NamebarID);
	LoadImg( "data\\img\\story\\mesbar.png", &MessagebarID);	
	LoadImg( "data\\img\\story\\cursor.png", &CursorID);
	//wsprintf( loadname, "%s\\data\\img\\story\\cursor.png", System::path);
	//ech = E3DCreateSprite( loadname, 0, 0, &CursorID);
	//_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/* �b��I�ȏ��� */
	//wsprintf( loadname, "%s\\data\\img\\face\\arty\\0.png", System::path);
	//ech = E3DCreateSprite( loadname, 0, 0, &CharaImg[0]);





	//LoadImg( "data\\img\\story\\bg\\missionroom.png", );

	return;
}

Story::~Story()
{
	/* ������ */
	int ech = 0;

	//ech = E3DDestroySprite( NamebarID);
	//_ASSERT( ech != 1 );//�G���[�`�F�b�N
	//
	//ech = E3DDestroySprite( MessagebarID);
	//_ASSERT( ech != 1 );//�G���[�`�F�b�N
	//
	//ech = E3DDestroySprite( CursorID);
	//_ASSERT( ech != 1 );//�G���[�`�F�b�N
	//
	///* �b��I�ȏ��� */
	//ech = E3DDestroySprite( CharaImg[0]);
	//_ASSERT( ech != 1 );//�G���[�`�F�b�N

	//ech = E3DDestroySprite( CharaImg[1]);
	//_ASSERT( ech != 1 );//�G���[�`�F�b�N


	return;
}


int Story::LoadStoryFromSTD( char *LoadPath){

	/* ������ */
	int CharaID;
	int FaceID;
	char Statement[256];
	char NowLabel[60] = "MAIN";

	char LoadFullPath[256];
	FILE *fp;
	
	/* �X�g�[���f�[�^�������Ă��郊�X�g�Ɋi�[���� */
	map<string, std::list<StoryData>>::iterator it;

	/* �t�@�C���̃I�[�v���̏��� */
	wsprintf( LoadFullPath, "%s\\data\\prof\\story\\%s", System::path, LoadPath);
	fopen_s( &fp, LoadFullPath, "r");//�w�肳�ꂽ�t�@�C�����I�[�v�����܂��B 
	if( fp == NULL){
		_ASSERT( 0 );
		return -1;
	}

	/* ////////////////////////////// */
	/* ��������A�f�[�^��ǂݎ��܂� */
	/* ////////////////////////////// */

	while( fscanf_s( fp, "%s", &Statement, 256) !=EOF)
	{
		/* ������ */
		StoryData StrDat;
		StrDat.Statement = NONE;// �X�e�[�g�����g���u�����Ȃ��v�ɂ��Ă���

		if( strcmp( Statement, "PutIMG") == NULL)
		{
			/* �����̓ǂݍ��� */
			fscanf_s( fp, "%s", &LoadFullPath, 256);

			StrDat.Statement = PUTIMG;
			LoadImg( LoadFullPath, &StrDat.ImgID);



			it = StoryLabel.find(NowLabel);
			(*it).second.push_back(StrDat);

		}

		else if( strcmp( Statement, "PutC") == NULL)
		{

			fscanf_s( fp, "%d %d %s %s", &CharaID, &FaceID, &StrDat.Name, 32, &StrDat.Text, 256 );

			/* �ꎞ�I�ȏ��� */
			switch(CharaID){
				case C_ARTY:{ //�A�[�e�B
					StrDat.ImgID = C_ARTY;
					break;
				}
				case C_VILL:{//���B��
					StrDat.ImgID = C_VILL;
					break;
				}
			}

			strcpy_s( StrDat.Text, 256, ConvertNewLine( StrDat.Text));
			StrDat.Statement = PUTCHARA;


			it = StoryLabel.find(NowLabel);
			(*it).second.push_back(StrDat);
		}

		else if( strcmp( Statement, "Switch") == NULL)
		{
			/* �ϐ��̏����� */
			int RepeatTimes;// �I������
			char cParameter[2];
			struct SwitchLabel TempSwt;

			/* �X�C�b�`����閽�� */
			StrDat.Statement = MKSWITCH;

			/* �����̓ǂݍ��� */
			fscanf_s( fp, "%d", &RepeatTimes);
			for( int i = 0; i < RepeatTimes; i++)
			{
				fscanf_s( fp, "%s %s", &TempSwt.Text, 40, &TempSwt.Label, 60);

				StrDat.SWT.push_back(TempSwt) ;
			}


			it = StoryLabel.find(NowLabel);
			(*it).second.push_back(StrDat);

			/* �X�C�b�`�̊m�F�����閽�� */
			StrDat.Statement = SWITCH;
			(*it).second.push_back(StrDat);

		}

		// ���x���o�^�Ȃ�
		else if( strcmp( Statement, "*") == NULL)
		{
			fscanf_s( fp, "%s", &NowLabel, 60);

			/* �v�b�V�����郉�x����V�K�쐬���邽�߂̏��� */
			if( StoryLabel.find(NowLabel) == StoryLabel.end())
			{
				std::list<StoryData> SData;
				StoryData DammyData;// �_�~�[�f�[�^���v�b�V�����Ȃ��ƁA�b��2�Ԗڂ���ɂȂ�
				DammyData.Statement = DAMMY;

				SData.push_back( DammyData);
				StoryLabel.insert( make_pair( string(NowLabel), SData));
			}
			else
			{
				_ASSERT(1);
			}


		}

		else if( strcmp( Statement, "END") == NULL)
		{
			StrDat.Statement = END;


			it = StoryLabel.find(NowLabel);
			(*it).second.push_back(StrDat);

		}

	}

	//for( int i = 0; fscanf_s( fp, "%d %d %s %s", &CharaID, &FaceID, &StrDat.Name, 32, &StrDat.Text, 256 ) !=EOF ; i++){
	//	
	//	/* ������ */


	//	/* �ꎞ�I�ȏ��� */
	//	switch(CharaID){
	//		case 0:{ //�A�[�e�B
	//			StrDat.ImgID = 0;
	//			break;
	//		}
	//		case 1:{//���B��
	//			StrDat.ImgID = 1;
	//			break;
	//		}
	//	}



	//	strcpy_s( StrDat.Text, str2);
	//	/* �ꎞ�I�ȏ����I��� */

	//	StoryList.push_back(StrDat);
	//}



	if( fclose(fp) == EOF){
		return -1;
	}
		


	return 0;
}

char* Story::ConvertNewLine( char *str1)
{
	/* ������ */
	int k = 0;
	static char str2[256];

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




	return str2;
}

int Story::StartStory( int StoryID)
{

	/* ������ */
	int ech;
	const E3DCOLOR4UC Black = Get_Color( BLACK);//�F�\���́A�����w��
	char NowLabel[60] = "MAIN";
	bool NextStepFlag = false;
	bool LockNextLightClickFlag = false;
	bool StoryEndFlag = false;
	struct StoryData StoryD;

	BGID = -1;

	/* �X�g�[���f�[�^�������Ă��郊�X�g�̃C�e���[�^��錾 */
	map<string, std::list<StoryData>>::iterator it = StoryLabel.find(NowLabel);
	list<StoryData>::iterator lit;

	/* //////////// */
	/* ���C�����[�v */
	/* //////////// */
	for( lit = (*it).second.begin(); lit != (*it).second.end() && WM_QUIT != System::msg.message; lit++)
	{


		while( WM_QUIT != System::msg.message)
		{
			System::MsgQ(30);//���b�Z�[�W���[�v
			System::KeyRenewal(1);
			StartBeginScene();

			switch( (*lit).Statement)
			{
				case DAMMY:
				{
					EndSprite();
					NextStepFlag = true;

					break;
				}
				case PUTIMG:
				{
					BGID = (*lit).ImgID;
					PutBackGround();	
					EndSprite();
					NextStepFlag = true;
					break;
				}
				case PUTCHARA:
				{

					PutBackGround();	
					PutMesseageView();
					PutSprite( CharaImg[ (*lit).ImgID ], 35, 280, 1.0f, 1.0f);	
					EndSprite();
					PutCharaName( (*lit).Name);
					PutText( (*lit).Text);

					break;
				}
				case MKSWITCH:
				{
					PutBackGround();	
					PutMesseageView();
					EndSprite();

					int i = 0;
					int Btn;
					std::list<SwitchLabel>::iterator Sit;

					for( Sit = (*lit).SWT.begin(); Sit != (*lit).SWT.end(); Sit++)
					{
						MakeFontButton_Auto( (*Sit).Text, &Btn, 190, 335 + i * 30);
						i++;
					}
					NextStepFlag = true;
					

					break;
				}
				case SWITCH:
				{
					PutBackGround();	
					PutMesseageView();
					EndSprite();

					/* �I�����{�^����\�������܂� */
					std::list<SwitchLabel>::iterator Sit = (*lit).SWT.begin();
					int i = 0;
					LockNextLightClickFlag = true;

					int SelectKind = ChkFontButtonWithColor( System::MousePos.x, System::MousePos.y, BLACK, GRAY) ;

					/* �����A�{�^�����N���b�N���ꂽ�� */
					if( SelectKind != -1 && System::GetKeyData( System::KEY_LEFTMOUSE))
					{
						/* �ʂ̃��x���ɃW�����v���� */
						advance( Sit , SelectKind);
						it = StoryLabel.find( (*Sit).Label);
						lit = (*it).second.begin();
						LockNextLightClickFlag = false;// ���b�N����������
					}

					PutCharaName( "���Ȃ�");

					break;
				}
				case END:
				{
					PutBackGround();	
					EndSprite();
					StoryEndFlag = true;
					NextStepFlag = true;
				}
			}


			EndScene();

			/* ���N���b�N���ꂽ�� */
			if( StoryEndFlag == true)
			{
				return 0;
			}
			else if( ( System::GetKeyData( System::KEY_LEFTMOUSE) == 1 
				|| NextStepFlag == true)  
				&& LockNextLightClickFlag == false) 
			{
				
				NextStepFlag = false;
				break;
			}

			//else if( System::GetKeyData( System::KEY_R) == 1)// �b���X�L�b�v����Ȃ�AR�L�[
			//{
			//	return 0;
			//}
		}



		
	}





	//list<StoryData>::iterator it = StoryList.begin();

	//while( it != StoryList.end() && WM_QUIT != System::msg.message){

	//	System::KeyRenewal(1);

	//	while( WM_QUIT != System::msg.message){
	//		
	//		System::KeyRenewal(1);

	//		ech = E3DBeginScene( System::scid1, 0, -1);
	//		_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

	//		ech = E3DBeginSprite();
	//		_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

	//		/* �X�v���C�g�̕`�� */
	//		D3DXVECTOR3 MesBarPos( 20, 310, 0);//�`��ʒu���w�肷��\����
	//		ech = E3DRenderSprite( MessagebarID, 590.0 /1024.0, 135.0/256.0, MesBarPos);
	//		_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

	//		/* �L�����`�� */
	//		D3DXVECTOR3 CharaImgPos( 35, 280, 0);//�`��ʒu���w�肷��\����
	//		ech = E3DRenderSprite( CharaImg[ (*it).ImgID ], 1.0, 1.0, CharaImgPos);
	//		_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

	//		D3DXVECTOR3 NameBarPos( 25, 408, 0);//�`��ʒu���w�肷��\����
	//		ech = E3DRenderSprite( NamebarID, 141.0 / 256.0, 41.0 / 64.0, NameBarPos);
	//		_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

	//		D3DXVECTOR3 CursorPos( 580, 410, 0);//�`��ʒu���w�肷��\����
	//		ech = E3DRenderSprite( CursorID, 46.0 / 64.0, 1.0, CursorPos);
	//		_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

	//		ech = E3DEndSprite();
	//		_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

	//		/* �����܂ŁA�X�v���C�g�`�� */

	//		/* ��������A�t�H���g�`�� */
	//		PutString( (*it).Text, 178, 340, F_SMALL, BLACK);//������������Ă��镶�����\������
	//		_ASSERT( ech != 1 );//�G���[�`�F�b�N

	//		PutString( (*it).Name, 70, 415, F_SMALL, BLACK);//������������Ă��镶�����\������
	//		_ASSERT( ech != 1 );//�G���[�`�F�b�N

	//		/* �����܂� */

	//		ech = E3DEndScene();
	//		_ASSERT( ech != 1 );//�G���[�`�F�b�N

	//		ech = E3DPresent( System::scid1);
	//		_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

	//		/* ���N���b�N���ꂽ�� */
	//		if( System::GetKeyData( System::KEY_LEFTMOUSE) == 1){
	//			break;
	//		}
	//		else if( System::GetKeyData( System::KEY_R) == 1)// �b���X�L�b�v����Ȃ�AR�L�[
	//		{
	//			return 0;
	//		}

	//		System::MsgQ(30);//���b�Z�[�W���[�v
	//	}

	//	it++;

	//}






	return 0;
}

/* �w�i��\�������� */
int Story::PutBackGround()
{
	
	PutSprite( BGID, 0, 0, 640.0/1024.0, 480.0/512.0);	

	return 0;
}

/* �L��������\�������� */
int Story::PutCharaName(const char * ChName)
{
	
	PutString( ChName, 70, 415, F_SMALL, BLACK);//������������Ă��镶�����\������

	return 0;
}


int Story::PutMesseageView()
{
	/* ������ */
	int ech;

	PutSprite( MessagebarID, 20, 310, 590.0 /1024.0, 135.0/256.0);
	PutSprite( NamebarID, 25, 408, 141.0 / 256.0, 41.0 / 64.0);

	///* ���b�Z�[�W�o�[�摜��\�������� */
	//D3DXVECTOR3 MesBarPos( 20, 310, 0);//�`��ʒu���w�肷��\����
	//ech = E3DRenderSprite( MessagebarID, 590.0 /1024.0, 135.0/256.0, MesBarPos);
	//_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

	///* ���O��\�������镔���̉摜 */
	//D3DXVECTOR3 NameBarPos( 25, 408, 0);//�`��ʒu���w�肷��\����
	//ech = E3DRenderSprite( NamebarID, 141.0 / 256.0, 41.0 / 64.0, NameBarPos);
	//_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��


	return 0;
}

/* �e�L�X�g��\�������܂� */
int Story::PutText( const char * Text)
{
	PutString( Text, 178, 340, F_SMALL, BLACK);//������������Ă��镶�����\������

	return 0;
}

///* �X�g�[�����[�h�̃L�[������s���܂� */
//int Story::KeyControl()
//{
//	System::KeyRenewal(1);
//
//	/* ���N���b�N���ꂽ�� */
//	if( System::GetKeyData( System::KEY_LEFTMOUSE) == 1){
//		break;
//	}
//	else if( System::GetKeyData( System::KEY_R) == 1)// �b���X�L�b�v����Ȃ�AR�L�[
//	{
//		return 0;
//	}
//
//	return 
//}