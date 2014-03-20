/*
// �~�b�V�����N���X�̏����ɂ��ċL�q���܂�
//
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include "cMission.h"
#include "clive.h"//�G��L�����̐錾�w�b�_�t�@�C��
#include "cPoseMenu.h"//���j���[�N���X�Ɋւ���w�b�_�t�@�C��
#include "c_batch_preparat.h"//�`��ɕK�v�ȃN���X�̐錾�w�b�_�t�@�C��
#include "cstage.h"//�X�e�[�W�֌W�̃N���X�w�b�_�t�@�C��
#include "cenemy.h"//�G�N���X�̐錾�w�b�_�t�@�C��
#include "ccamera.h"//�J�����֌W�̃N���X�w�b�_�t�@�C��
#include "cStory.h"

#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_



int Mission::Loading( char *File)
{

	/* ������ */
	int Parameter[7] = {0};
	int i = 0;
	int MaxStep = 1;
	int ech = 0;
	bool NPCStatementFlg = false;// NPC����x�ł��ǂݍ��݂������̃t���O�ϐ�
	bool WeaponStatementFlg = false;// Weapon����x�ł��ǂݍ��݂������̃t���O�ϐ�
	bool WinningStatementFlg = false;// ������������x�ł��ݒ肵�����̃t���O
	char CParameter;
	char LoadFullPath[256];
	char Statement[32];
	FILE *fp;

	/* �t�@�C���̃I�[�v���̏��� */
	wsprintf( LoadFullPath, "%s\\data\\prof\\mis\\%s", System::path, File);
	fopen_s( &fp, LoadFullPath, "r");//�w�肳�ꂽ�t�@�C�����I�[�v�����܂��B 
	if( fp == NULL){
		_ASSERT( 0 );
		return -1;
	}
	
	/* �v���O���X�o�[�����܂� */
	E3DCreateProgressBar();

	/* �ǂݎ�����X�e�[�g�����g�ŕ��� */
	while( fscanf_s( fp, "%s", &Statement, 32) !=EOF)
	{
		// MaxStep�Ȃ�A�X�e�b�v���̍ő����
		if( strcmp( Statement, "MaxStep") == NULL)
		{
			
			fscanf_s( fp, "%d", &Parameter[0]);

			MaxStep = Parameter[0];

		}

		// MkPly( Make Player)�Ȃ�A�L�����N�^���쐬
		else if( strcmp( Statement, "MkPly") == NULL)
		{
			
			fscanf_s( fp, "%d %d", &Parameter[0], &Parameter[1]);

			if( pPlayer != 0)
			{
				delete pPlayer;
			}

			pPlayer = new PlayerChara( Parameter[0], Parameter[1]);

			/* �v���C���[���Z�b�g���v�b�V������ */
			struct MisOrder MiO;

			MiO.Statement = Mission::PINIT;
			MisList.push_back( MiO);

		}

		// WLoad( Weapon Load)�Ȃ�A����ǂݍ���(�������A��Ƀv���C���[�̎��̂��Ȃ���΃_��)
		else if( strcmp( Statement, "WLoad") == NULL )
		{

			fscanf_s( fp, "%d %d %d", &Parameter[0], &Parameter[1], &Parameter[2]);

			if( pPlayer == NULL){// �v���C���[�C���X�^���X���Ȃ����
				_ASSERT( 0 );
				return -1;
			}

			pPlayer->Wpn.WpLoad( Parameter[0], Parameter[1], Parameter[2]);// �e�̃��[�h

			/* ���탊�Z�b�g���v�b�V������ */
			if( WeaponStatementFlg == false)
			{
				struct MisOrder MiO;
				MiO.Statement = Mission::WINIT;
				MisList.push_back( MiO);

				WeaponStatementFlg = true;
			}
		}

		// SLoad( Stage Load)�Ȃ�A�n�`�ǂݍ���
		else if( strcmp( Statement, "SLoad") == NULL)
		{

			/* ������ */
			int Time = 0;

			fscanf_s( fp, "%d %d %c", &Parameter[0], &Parameter[1], &Parameter[2]);
			
			switch( Parameter[2])
			{
				case 'n':
				{
						Time = Stage::NIGHT;
						break;
				}
				case 'e':
				{
						Time = Stage::EVENING;
						break;
				}
				case 'm':
				{
						Time = Stage::MORNING;
						break;
				}

			}
			
			
			pStg->LoadStage( Parameter[0], Parameter[1], Time);

		}

		// ELoad( Enemy Load)�Ȃ�A�G�ǂݍ���
		else if( strcmp( Statement, "ELoad") == NULL)
		{

			/* ������ */
			char EneName[64];

			fscanf_s( fp, "%s %d %d %d %d", &EneName, 64, &Parameter[0], &Parameter[1], &Parameter[2], &Parameter[3]);
			
			// �G�����[�h���܂�
			pNPC->LoadEnemyModelAddName( EneName, Parameter[0], Parameter[1]);
			pNPC->SetEnemyPosByNaviPoint( pStg, EneName, Parameter[2], Parameter[3]);

			/* ���탊�Z�b�g���v�b�V������ */
			if( NPCStatementFlg == false)
			{
				struct MisOrder MiO;
				MiO.Statement = Mission::NPCINIT;
				MisList.push_back( MiO);

				NPCStatementFlg = true;
			}

		}

		// SMyPos( Set MYmodel POSition)�Ȃ�A�����̐ݒu
		else if( strcmp( Statement, "SMyPos") == NULL)
		{

			struct MisOrder MiO;
			MiO.Statement = Mission::SMYPOS;


			/* 1�Ԗڂ̃p�����[�^���Ăяo�� */
			fscanf_s( fp, " %c", &CParameter);
			switch (CParameter)
			{
				// �i�r���[���Ŏ����ݒu�ʒu�����߂�Ȃ�
				case 'n':
				{
					fscanf_s( fp, "%d %d", &Parameter[1], &Parameter[2]);
					MiO.iParameter[0] = NAVI;
					break;
				}
				case 'w':
				{
					fscanf_s( fp, "%d %d %d", &Parameter[1], &Parameter[2], &Parameter[3]);
					MiO.iParameter[0] = WORLD;
				}
			}

			MiO.iParameter[1] = Parameter[1];
			MiO.iParameter[2] = Parameter[2];
			MiO.iParameter[3] = Parameter[3];
			
			MisList.push_back( MiO);

			///* ������ */
			//fscanf_s( fp, " %c", &CParameter);

			//
			//switch( CParameter)
			//{
			//	// �i�r���[���Ŏ����ݒu�ʒu�����߂�Ȃ�
			//	case 'n':
			//	{
			//		fscanf_s( fp, "%d %d", &Parameter[1], &Parameter[2]);
			//		pStg->Navi.SetPosByNaviPoint( pPlayer->Get_BodyModel(), Parameter[1], Parameter[2]);
			//		break;
			//	}
			//	case 'w':
			//	{
			//		fscanf_s( fp, "%d %d %d", &Parameter[1], &Parameter[2], &Parameter[3]);
			//		ech = E3DSetPos( pPlayer->Get_BodyModel(), D3DXVECTOR3( (float)Parameter[1], (float)Parameter[2], (float)Parameter[3]));
			//		if( ech != 0){
			//			_ASSERT( 0 );
			//			return 1;
			//		};
			//		break;
			//	}
			//}
		}

		// WInit(Weapon INITialize)�Ȃ�A�e�򏉊���
		else if( strcmp( Statement, "WInit") == NULL)
		{
			struct MisOrder MiO;

			MiO.Statement = Mission::WINIT;
			MisList.push_back( MiO);
	
		}

		// PStory(Play Story)�Ȃ�A�X�g�[���𗬂�
		else if( strcmp( Statement, "PStory") == NULL)
		{
			struct MisOrder MiO;

			fscanf_s( fp, "%s", &MiO.cParameter, 30);

			MiO.Statement = Mission::PSTORY;
			MisList.push_back( MiO);

		}

		// PTPS(Play TPS)�Ȃ�A�Q�[���{�҂Ɉڍs����
		else if( strcmp( Statement, "PTPS") == NULL)
		{
			struct MisOrder MiO;

			MiO.Statement = Mission::PTPS;
			MisList.push_back( MiO);
			
		}

		// RegWin(REGister WINning condition)�Ȃ�A�����������w�肷��
		else if( strcmp( Statement, "RegWin") == NULL)
		{

			struct MisOrder MiO;

			/* �K���������������Z�b�g����悤�ɂ��� */
			if( WinningStatementFlg == false)
			{
				MiO.Statement = Mission::WININIT;
				MisList.push_back( MiO);
				WinningStatementFlg = true;
			}

			/* �����������w�肷�� */
			fscanf_s( fp, " %c", &CParameter);
			
			switch( CParameter)
			{
				
				case 'a':// �S�ł����������ɂ���Ȃ�
				{
					MiO.iParameter[0] = ALLKILL;
					break;
				}
				case 'p':// ����̏ꏊ�ɒ�������
				{
					/* ������ */
					char loadname[256];

					fscanf_s( fp, "%d %d %d", &Parameter[1], &Parameter[2], &Parameter[3]);

					MiO.iParameter[0] = REACHPOINT;

					/* �E�o�ꏊ���f����ǂݍ��� */
					wsprintf( loadname, "%s\\data\\3d\\model\\install\\Exitpoint.sig", System::path);//�A�[�e�B�[���f����sig���o�^
					ech = E3DSigLoad( loadname, 0, 1.8f, &(MiO.iParameter[1]));//���f���̓ǂݍ��݁Acha_hsid�փ��f��������B
					if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( ech != 1 );//�G���[�_�C�A���O
					};

					/* �����}�[�N�r���{�[�h�����[�h���܂� */
					wsprintf( loadname, "%s\\data\\img\\identifier\\exit.png", System::path);
					ech = E3DCreateBillboard ( loadname, 512, 512, 0, 1, 1, &MiO.iParameter[2]);
					_ASSERT( ech != 1 );//�G���[�`�F�b�N

					ech = E3DSetBillboardPos( MiO.iParameter[2],  D3DXVECTOR3( (float)Parameter[1], (float)Parameter[2] + 2000.0f, (float)Parameter[3]));/* !!�I�����Ƀr���{�[�h���f�������������邱��!! */
					_ASSERT( ech != 1 );//�G���[�`�F�b�N

					/* �E�o�ꏊ���f�����W���w�肷�� */
					ech = E3DSetPos( MiO.iParameter[1], D3DXVECTOR3( (float)Parameter[1], (float)Parameter[2], (float)Parameter[3]));
					_ASSERT( ech !=1);


					break;
				}
			}


			MiO.Statement = Mission::REGWIN;
			MisList.push_back( MiO);
			
		}

		// RegLose(REGister Losing condition)�Ȃ�A�s�k���������߂�
		else if( strcmp( Statement, "RegLose") == NULL)
		{

			struct MisOrder MiO;

			/* �K���s�k���������Z�b�g����悤�ɂ��� */
			if( WinningStatementFlg == false)
			{
				MiO.Statement = Mission::WININIT;
				MisList.push_back( MiO);
				WinningStatementFlg = true;
			}

			/* �����������w�肷�� */
			fscanf_s( fp, " %c", &CParameter);
			
			switch( CParameter)
			{
				
				case 't':// ���Ԑ�����s�k�����ɂ���Ȃ�
				{
					fscanf_s( fp, "%d", &Parameter[1]);
					
					MiO.iParameter[0] = Mission::TIMEUP;
					Timer.LimitTime = Parameter[1];// �������Ԃ̎擾(�b�P��)
					Timer.IndicateTimeNormal = false;
					break;
				}
			}


			MiO.Statement = Mission::REGLOSE;
			MisList.push_back( MiO);




		}

		// WinInit(WINning condition Init)�Ȃ�A����������������
		else if( strcmp( Statement, "WinInit") == NULL)
		{

			struct MisOrder MiO;

			MiO.Statement = Mission::WININIT;
			MisList.push_back( MiO);
			
		}

		// InstOBJ�Ȃ�A�X�e�[�W�ɃI�u�W�F�N�g��u���Ƃ���
		else if( strcmp( Statement, "InstOBJ") == NULL)
		{
		
			/* ������ */
			struct MisOrder MiO;
			char loadname[256];
			
			fscanf_s( fp, " %c", &CParameter);
			
			switch( CParameter)
			{
				case 'j':// �J�^�p���g�W�����v��ݒu���� 
				{

					

					fscanf_s( fp, "%d %d %d %d %d %d", &Parameter[1], &Parameter[2], &Parameter[3], &Parameter[4], &Parameter[5], &Parameter[6]);

					MiO.iParameter[0] = CATAPULT;

					/* �J�^�p���g�W�����v��ǂݍ��� */
					wsprintf( loadname, "%s\\data\\3d\\model\\install\\catapult.sig", System::path);//
					ech = E3DSigLoad( loadname, 0, 0.5f, &(MiO.iParameter[1]));//���f���̓ǂݍ��݁Acha_hsid�փ��f��������B
					if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( ech != 1 );//�G���[�_�C�A���O
					};

					/* �J�^�p���g�W�����v���w�肷�� */
					ech = E3DSetPos( MiO.iParameter[1], D3DXVECTOR3( (float)Parameter[1], (float)Parameter[2], (float)Parameter[3]));
					_ASSERT( ech !=1);

					///* �����}�[�N�r���{�[�h�����[�h���܂� */
					//wsprintf( loadname, "%s\\data\\img\\identifier\\exit.png", System::path);
					//ech = E3DCreateBillboard ( loadname, 512, 512, 0, 1, 1, &MiO.iParameter[2]);
					//_ASSERT( ech != 1 );//�G���[�`�F�b�N

					//ech = E3DSetBillboardPos( MiO.iParameter[2],  D3DXVECTOR3( (float)Parameter[1], (float)Parameter[2] + 2000.0f, (float)Parameter[3]));/* !!�I�����Ƀr���{�[�h���f�������������邱��!! */
					//_ASSERT( ech != 1 );//�G���[�`�F�b�N

					RegisterCatapult( MiO.iParameter[1], Parameter[4], Parameter[5], Parameter[6]);


					break;
				}
			}

			MiO.Statement = Mission::INSTOBJ;
			MisList.push_back( MiO);
			
		}

		// END�Ȃ�A�Q�[�����I���Ƃ���
		else if( strcmp( Statement, "END") == NULL)
		{
			struct MisOrder MiO;

			MiO.Statement = Mission::END;
			MisList.push_back( MiO);
			
		}

		/* �v���O���X�o�[��i�������� */ 
		E3DSetProgressBar( int( double(i) / double(MaxStep) * 100.0));

		i++;
	}

	/* �v���O���X�o�[���󂵂܂� */
	E3DDestroyProgressBar();

	/* �s���n�p�v���O���� !Debug���Ɏg�p! 

	char StepStrings[100];
	wsprintf( StepStrings, "�X�e�b�v����%d��ł�", i);	
	MessageBox( NULL, StepStrings, "���̃t�@�C���̃X�e�b�v��", MB_OK );
	/* �����܂� */

	/* FILE�̊J�� */
	fclose(fp);

	/* ���̑��K�v�ȏ��� */

	// �o�b�`�v���p���[�g�ɂ��ׂĂ̕`�揀���������܂��B
	pBatP = new Batch_Render( pPlayer, pStg, pNPC, pCam);

	/* �������t���O���I���ɂ��� */
	System::SetUpdataSoundSys( 1);

	/* �o���v�}�b�v��L���ɂ��܂� */
	pBatP->BatchEnableBumpMap(0);


	return 0;
}

int Mission::Intialize()
{

	/* �ϐ��̏����� */
	int ech;
	int ButtonID = 0;
	int Garbage = 0;
	char loadname[256] = "";//�ǂݍ��ސ�̃p�X�̕�����ϐ�
	const char MenuKindName[2][32] = {  "�ďo��" , "�P��"  };
	ScreenPosArray[0] = 0;
	ScreenPosArray[1] = 0;
	
	for( int i = 0; i<8; i++)
	{
		CatapultData[i].CatapultID = -1;
	}

	pPlayer = 0; 
	pBatP = 0;
	pStg = 0;

	/* �J�����C���X�^���X�̐��� */
	pCam = new Camera ;

	/* NPC�C���X�^���X�̍쐬 */;
	pNPC = new NPC_Head;

	/* �X�e�[�W�C���X�^���X�̍쐬 */
	pStg = new Stage;

	/* ���j���[�C���X�^���X�̍쐬 */
	pMenu = new PoseMenu;

	/* �^�C�}�[�\���̂Ƀ|�C���^�̑�� */
	Timer.TimeUsing = &LosingFlag[COD_TIMEUP];

	/* �Q�[���I�[�o�[�X�v���C�g�̃��[�h */
	wsprintf( loadname, "%s\\data\\img\\sys\\gameover.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &SpGameOver);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/* �{�^������鏈�� */
	MakeFontButton_Auto(  MenuKindName[0], &ButtonID, 210, 300);
	MakeFontButton_Auto(  MenuKindName[1], &ButtonID, 380, 300);



	return 0;
}

// ��{�I�� BatchPreprate �̏�����S�čs���܂�
int Mission::NormalBatchProces(){

	pBatP->BatchSpriteSet( pPlayer);

	pBatP->BatchRender( 0);
	pBatP->BatchSpriteRender( 0);
	pBatP->Batch_BillBoard( 0);
	pBatP->BatchFont( 1, pPlayer, Timer);



	pBatP->Batch_Present();

	return 0;
}

// �f�X�g���N�^ �����̉�������܂�
Mission::~Mission(){

	/* �����̊J�� */
	delete pCam;
	delete pNPC;
	delete pMenu;

	if( pPlayer != NULL){
		delete pPlayer;
	}

	if( pBatP != NULL){
		delete pBatP;
	}

	if( pStg != NULL){
		delete pStg;
	}


	return ;
}

//�Q�[���I�[�o�[�������A�Ē��킷�邩�q�˂�B
int Mission::GameOver(){

	/* ������ */
	int ech = 0;
	int NextFlag = -1;// ���[�U�[�̑I��������܂�
	 int SelectKind = -1;// �I�����Ă���A�C�e�������ʂ���ϐ�

	D3DXVECTOR3 SpritePos1( 0.0, 0.0, 0.0);//�w�i�̈ʒu
	//POINT TextPos;//�e�L�X�g�̍��W�ϐ�


	/*�܂��͂��߂ɁA�ʏ��ʁ����j���[��ʂɂ��Ă����܂��B*/
	for(int i = 0; i<17; i++){

			/*�ϐ��̏�����*/

			E3DCOLOR4UC AlfaColor = { 15*i ,255,255,255};
			
			/*�����������܂�*/
			ech = E3DSetSpriteARGB( SpGameOver, AlfaColor);
			_ASSERT( ech != 1 );//�G���[�`�F�b�N

			/*�ʏ��ʂ̃����_�����O*/
			pBatP->BatchRender( 0);//�����_�����O

			/*�`�揀�����s���܂�*/
			E3DBeginScene( System::scid1, 1, -1);;
			E3DBeginSprite();

			ech = E3DRenderSprite( SpGameOver, 640.0/1024.0, 1, SpritePos1);
			_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

			/*�����ŁA�`�抮��*/
			E3DEndSprite();
			E3DEndScene();
			E3DPresent(System::scid1);

			
	}/*�����܂�*/

	while( NextFlag == -1 && WM_QUIT != System::msg.message){

			System::MsgQ(30);//���b�Z�[�W���[�v
			System::KeyRenewal(1);

			/*�`�揀�����s���܂�*/
			E3DBeginScene( System::scid1, 1, -1);;
			E3DBeginSprite();

			ech = E3DRenderSprite( SpGameOver, 640.0/1024.0, 1, SpritePos1);
			_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

			E3DEndSprite();


			// �o���[���̕\�����s���܂�
			PutBalloon_Auto( System::MousePos.x, System::MousePos.y);

			//�ȉ��A���j���[�l�[��(�ʏ펞�E�I����)��\��
			SelectKind = ChkFontButton( System::MousePos.x, System::MousePos.y);

			/* ////////////////////////////////// */
			/* �N���b�N���ꂽ���̓����ݒ肵�܂� 
			/* ////////////////////////////////// */
			if( System::GetKeyData( System::KEY_LEFTMOUSE)){
					switch(SelectKind){
							case 0:{// �Ē���
									NextFlag = RETRY;
									break;
							}
							case 1:{// ������߂�
									NextFlag = GIVEUP;
									break;
							}
					}
			}




			E3DEndScene();
			E3DPresent(System::scid1);

	}




	return NextFlag;
}

int Mission::RegisterCatapult( const int ModelID, const double UpAcceleration, const double Degree, const double Speed)
{
	/* ������ */
	int IDNum;

	/* ��̔z����������āA */
	for( int i=0; i<8; i++){
			if( CatapultData[i].CatapultID == -1){
					IDNum = i;
					break;
			}
	}

	CatapultData[IDNum].CatapultID = ModelID;
	/*CatapultData[IDNum].X = X;
	CatapultData[IDNum].Y = Y;
	CatapultData[IDNum].Z = Z;*/
	CatapultData[IDNum].UpAcceleration = UpAcceleration;
	CatapultData[IDNum].Degree = Degree;
	CatapultData[IDNum].Speed = Speed;

	return 0;
}