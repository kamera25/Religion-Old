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

/* �ǂݍ��܂ꂽMIS�t�@�C���ɂ���āA�������s���܂��B */
int Mission::MainProc()
{
	// �C�e���[�^ �y�� �ϐ��̐錾
	list<MisOrder>::iterator it; 

	// �C�e���[�^�̒��g����ɂȂ�܂ŌJ��Ԃ�
	for( it = MisList.begin(); it != MisList.end(); it++)
	{

		
		// �I�[�_�[��WInit(Weapon INITialize)�Ȃ�
		if( (*it).Statement == Mission::WINIT)
		{
			// �e��̏�����
			pPlayer->Wpn.SetInitWeapon( Weapon_Head::RESET);
		}

		// �I�[�_�[��PStory(Play Story)�Ȃ�
		if( (*it).Statement == Mission::PSTORY)
		{
			Story StoryS;
			StoryS.LoadStoryFromSTD( (*it).cParameter);
			StoryS.StartStory(1);
		}


		// �I�[�_�[��PTPS(Play TPS)�Ȃ�
		if( (*it).Statement == Mission::PTPS)
		{
			System::SetMouseCursol( 320, 240);//�}�E�X���E�B���h�E�^�񒆂ɐݒu

			// �Q�[���J�n
			while(  WM_QUIT != System::msg.message ){
				System::MsgQ(30);//���b�Z�[�W���[�v
				TPSMainLoop();
			}
		}
	}

	return 0;
}

int Mission::Loading( char *File)
{

	/* ������ */
	int Parameter[6] = {0};
	int i = 0;
	int MaxStep = 1;
	int ech = 0;
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

		}

		// SMyPos( Set MYmodel POSition)�Ȃ�A�����̐ݒu
		else if( strcmp( Statement, "SMyPos") == NULL)
		{

			/* ������ */
			fscanf_s( fp, " %c", &CParameter);

			
			switch( CParameter)
			{
				// �i�r���[���Ŏ����ݒu�ʒu�����߂�Ȃ�
				case 'n':
				{
					fscanf_s( fp, "%d %d", &Parameter[1], &Parameter[2]);
					pStg->Navi.SetPosByNaviPoint( pPlayer->Get_BodyModel(), Parameter[1], Parameter[2]);
					break;
				}
				case 'w':{
					fscanf_s( fp, "%d %d %d", &Parameter[1], &Parameter[2], &Parameter[3]);
					ech = E3DSetPos( pPlayer->Get_BodyModel(), D3DXVECTOR3( Parameter[1], Parameter[2], Parameter[3]));
					if( ech != 0){
						_ASSERT( 0 );
						return 1;
					};
					break;
				}
			}
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

		/* �v���O���X�o�[��i�������� */ 
		E3DSetProgressBar( double(i) / double(MaxStep) * 100.0);

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
	ScreenPosArray[0] = 0;
	ScreenPosArray[1] = 0;

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

	return 0;
}

int Mission::TPSMainLoop()
{


				System::KeyRenewalFromWp( &pPlayer->Wpn, pPlayer->Get_Wp_equipment());


				pBatP->BatchChkInView();

				// ����֌W
				pPlayer->Wpn.ChkWeaponsLaunch( pPlayer->Get_Wp_equipment());
				pPlayer->NormallyPCSystem( pStg, pBatP, pNPC, pCam, ScreenPosArray);
				pPlayer->Wpn.AttackEnemys( pNPC, pPlayer, ScreenPosArray, pStg);
				pPlayer->Wpn.WeaponsTreatment( pPlayer->Get_Wp_equipment(), pStg);
				pNPC->MoveEnemys( pStg);

				// �`��֘A
				NormalBatchProces();

				// �㏈���֌W
				pMenu->FarstInMenu( pBatP, pPlayer);
				pBatP->BatchBeforePos();
				pPlayer->Batch_PeopleMotion();



	return 0;
}

// ��{�I�� BatchPreprate �̏�����S�čs���܂�
int Mission::NormalBatchProces(){

	pBatP->BatchSpriteSet( pPlayer);
	pBatP->BatchRender( 0);
	pBatP->Batch_BillBoard( 0);
	pBatP->BatchSpriteRender( 0);
	pBatP->BatchFont( 1, pPlayer);
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