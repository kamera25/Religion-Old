/*
// �~�b�V�����N���X�̏����ɂ��ċL�q���܂�(whileGame�t�@�C���́A�Q�[�����̏��������S)
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
	bool RPModelUseFlag = false;// ����̏ꏊ�ɏW�܂�̂ɗ��p����A���f�������[�h����Ă��邩
	int NextFlag = NORMAL;
	int ech;
	list<MisOrder>::iterator it; 
	int Event = NORMAL;
	GameState = NORMAL;// �Q�[����Ԃ��m�[�}���ɂ���
	RPModelID = -1;// ����̏ꏊ�ɏW�܂�̂ɗ��p���郂�f��

	// �C�e���[�^�̒��g���󂩁A�Q�[����Ԃ��ɂȂ�܂ŌJ��Ԃ�
	for( it = MisList.begin(); it != MisList.end() ; it++)
	{
		/* �Ē���̃C�x���g�����s����Ă���� */
		if( Event == RETRY)
		{
			it = MisList.begin();
			Event = NORMAL;// �Q�[����Ԃ��m�[�}���ɂ���
		}
		
		/* ////////////////////////////// */
		/* �I�[�_�[�ɂ���ď���������s�� */
		/* ////////////////////////////// */

		switch( (*it).Statement )
		{
			// �I�[�_�[��SMyPos(Set MY POSition)�Ȃ�
			case SMYPOS:
			{
				switch( (*it).iParameter[0])
				{
					// �i�r���[���Ŏ����ݒu�ʒu�����߂�Ȃ�
					case NAVI:
					{
						pStg->Navi.SetPosByNaviPoint( pPlayer->Act, (*it).iParameter[1], (*it).iParameter[2]);
						break;
					}
					case WORLD:
					{
						pPlayer->Act->SetPos( (float)(*it).iParameter[1], (float)(*it).iParameter[2], (float)(*it).iParameter[3]));

						pBatP->test();
						break;
					}
				}
				break;
			}


			// �I�[�_�[��PInit(Player INITialize)�Ȃ�
			case PINIT:
			{
				/* ���Z�b�g */
				pPlayer->StatusReset();
				break;
			}

			// �I�[�_�[��NPCInit(NPC INITialize)�Ȃ�
			case NPCINIT:
			{
				/* ���Z�b�g */
				pNPC->StatusReset();
				break;
			}

			// �I�[�_�[��WInit(Weapon INITialize)�Ȃ�
			case WINIT:
			{
				// �e��̏�����
				pPlayer->Wpn.SetInitWeapon( Weapon_Head::RESET);
				break;
			}

			// �I�[�_�[��PStory(Play Story)�Ȃ�
			case PSTORY:
			{
				Story StoryS;
				StoryS.LoadStoryFromSTD( (*it).cParameter);
				StoryS.StartStory(1);
				System::WaitRender();
				break;
			}

			// �I�[�_�[��REGWIN(REGister WINning condition)�Ȃ�
			case REGWIN:
			{
				switch((*it).iParameter[0])
				{
					/* �S�łȂ� */
					case ALLKILL:
					{
						WinningFlag[COD_ALLKILL] = true;
						break;
					}
					/* ����̃|�C���g�ɂ����� */
					case REACHPOINT:
					{
						WinningFlag[COD_REACHPOINT] = true;
						pBatP->SetModel( (*it).iParameter[1], true);
						RPModelID = (*it).iParameter[1];// ���f��ID�̑��
						RPModelUseFlag = true;

						break;
					}
				}
				break;
			}

			// �I�[�_�[��WININIT(WINning condition INITialize)�Ȃ�
			case WININIT:
			{
				for( int i = 0; i < 8; i++){
					WinningFlag[i] = false;
					LosingFlag[i] = false;
					NowWinConditionFlag[i] = false;
					NowLosingConditionFlag[i] = false;
					CatapultFlag = false;
				}
				break;
			}

			// �I�[�_�[��PTPS(Play TPS)�Ȃ�
			case PTPS:
			{
				System::SetMouseCursol( 320, 240);//�}�E�X���E�B���h�E�^�񒆂ɐݒu
				
				/* ���Ԑ�������Ȃ� */
				if( LosingFlag[COD_TIMEUP] == true)
				{
					Timer.FirstTime = clock();
				}
				pBatP->ResetLog();
				pBatP->BacthGunTrade( pPlayer->Get_Wp_equipment());

				// �Q�[���J�n
				do{
					System::MsgQ(30);//���b�Z�[�W���[�v
					TPSMainLoop();
					Event = CheckBattle();
				}while( WM_QUIT != System::msg.message && Event != GAMEOVER && Event != CLEAR && Event != GIVEUP);

				//�Q�[���I�[�o�[�ɂȂ�����
				if( Event == GAMEOVER)
				{
					Event = GameOver();
				}
			



				break;
			}

			// �I�[�_�[��End�Ȃ�
			case END:
			{
				/* �����A����̏ꏊ�ɏW�܂邱�Ƃ������Ȃ�*/
				if( RPModelUseFlag == true)
				{
				
					ech = E3DDestroyHandlerSet( RPModelID);
					_ASSERT( ech != 1 );//�G���[�`�F�b�N
				
					RPModelUseFlag = false;
				}
				break;
			}

			// �I�[�_�[��RegLose�Ȃ�
			case REGLOSE:
			{

				// �s�k�����ɂ���ď�������
				switch( (*it).iParameter[0])
				{
					// ���Ԏw��Ȃ�
					case TIMEUP:
					{
						LosingFlag[COD_TIMEUP] = true;
						break;
					}
				}


				break;
			}
			
			case INSTOBJ:
			{
				switch((*it).iParameter[0])
				{
					/* �J�^�p���g�W�����v�ɂ����� */
					case CATAPULT:
					{
						pBatP->SetModel( (*it).iParameter[1], true);
						CatapultFlag = true;
						break;
					}
				}
				break;
			}
		}


		


	
	}

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

				/* �J�^�p���g�W�����v���� */
				ChkCatapult();

				pNPC->MoveEnemys( pStg);

				// �`��֘A
				NormalBatchProces();

				// �㏈���֌W
				pMenu->FarstInMenu( pBatP, pPlayer);
				pBatP->BatchBeforePos();
				pPlayer->Batch_PeopleMotion();

				//�C�x���g����
				EventSupervision();


	return 0;
}



// �C�x���g�֘A�̓������s��
int Mission::EventSupervision()
{
	/* ������ */
	int Conflict;
	int Garbage;
	int ech;
	
	GameState = pPlayer->EventPublish();
	if( GameState == NORMAL) GameState = pMenu->EventPublish();
	if( GameState == NORMAL) GameState = pNPC->EventPublish();
	if( GameState == NORMAL)
	{
		/* ����̏ꏊ�ɏW�܂�Ȃ� */
		if( WinningFlag[COD_REACHPOINT] == true )
		{
			Conflict = pPlayer->Act->ConflictOBB( RPModelID);
			/*ech = E3DChkConflictOBB( pPlayer->Get_BodyModel(), -1, RPModelID, -1, &Conflict, &Garbage);*/
			if( Conflict == 1){// �Փ˂����m������
				GameState = REACHPOINT;
			}
		}

	}

	/* ���O�e�X�g */
	if( GameState == ALLKILL) pBatP->PutLog("Congratulations! You killed all Enemy around here!");
	if( System::GetKeyData(System::KEY_Z) == 1)
	{
		D3DXVECTOR3 MyPos;
		char LogText[120];
		MyPos = pPlayer->Act->GetPos();
		/*E3DGetPos( pPlayer->Get_BodyModel(), &MyPos);*/
		wsprintf( LogText, " %d %d %d(MyPos)", (int)MyPos.x, (int)MyPos.y, (int)MyPos.z);
		pBatP->PutLog(LogText);
	}

	return 0;
}

// �����E���������𖞂����Ă��邩�`�F�b�N����
int Mission::CheckBattle()
{
	/* ������ */
	int Event;
	
	if( GAMEOVER == GameState || GameState == GIVEUP)
	{
		return GameState;
	}

	/* ////////////////// */
	/* ���������̃`�F�b�N */
	/* ////////////////// */

	// �S�łȂ�
	if( WinningFlag[COD_ALLKILL] == true && GameState == ALLKILL)
	{
		NowWinConditionFlag[COD_ALLKILL] = true;
	}

	// ����̏ꏊ�ɏW�܂�Ȃ�
	if( WinningFlag[COD_REACHPOINT] == true && GameState == REACHPOINT)
	{
		NowWinConditionFlag[COD_REACHPOINT] = true;
	}

	/* ////////////////// */
	/* �s�k�����̃`�F�b�N */
	/* ////////////////// */
	// ���Ԑ����Ȃ�
	if( LosingFlag[COD_TIMEUP] == true &&  ( (double)( clock() - Timer.FirstTime) / (double)CLOCKS_PER_SEC) > Timer.LimitTime)
	{
		return GAMEOVER;
	}


	/* �S�Ă̏��������𖞂����Ă��邩�`�F�b�N */
	Event = CLEAR;
	for( int i = 0; i < 8; i++)
	{
		/* �K�v�������������ݖ������Ă��Ȃ���� */
		if( WinningFlag[i] == true && NowWinConditionFlag[i] == false)
		{
			Event = NORMAL;
			break;
		}

	}

	return Event;
}

int Mission::ChkCatapult()
{
	/* ������ */
	int ech;
	int Garbage;
	int Conflict;
	D3DXVECTOR3 CatPos;

	/* �J�^�p���g�𗘗p���Ă��Ȃ���� */
	if( CatapultFlag == false)
	{
		return 1;
	} 

	for( int i = 0; i < 8; i++)
	{
		if( CatapultData[i].CatapultID == -1) continue;// ID��-1�ɂȂ��Ă���΁A��������

		Conflict = pPlayer->Act->ConflictOBB( CatapultData[i].CatapultID);
		//ech = E3DChkConflictOBB( pPlayer->Get_BodyModel(), -1, CatapultData[i].CatapultID, -1, &Conflict, &Garbage);
		
		if( Conflict == 1){// �Փ˂����m������

			ech = E3DGetPos( CatapultData[i].CatapultID, &CatPos);
			_ASSERT( ech != 1 );//�G���[�`�F�b�N

			pPlayer->JumpPosition( CatPos, CatapultData[i].Degree, CatapultData[i].UpAcceleration, CatapultData[i].Speed);
		}
	}



	return 0;
}