/* �I�y���[�V�����~�b�V�����֐��n�̈ꕔ�ł���A����"cOpsmission1_Shinryoku.cpp"�R�[�h��
// �~�b�V�����u�V�΂̃u���X���b�h�v�ɂ��Ă̂��Ƃ�������Ă��܂��B
/* /////////////////////////////////////////////////////////////////////////// */

#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "coperation.h"//�I�y���[�V�����J�n�֌W�̃N���X�w�b�_�t�@�C��
#include "clive.h"//�G��L�����̐錾�w�b�_�t�@�C��
#include "cweapon.h"//����Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��
#include "cstage.h"//�X�e�[�W�֌W�̃N���X�w�b�_�t�@�C��
#include "cenemy.h"//�G�N���X�̐錾�w�b�_�t�@�C��
#include "ccamera.h"//�J�����֌W�̃N���X�w�b�_�t�@�C��
#include "c_batch_preparat.h"//�`��ɕK�v�ȃN���X�̐錾�w�b�_�t�@�C��
#include "cPoseMenu.h"//���j���[�N���X�Ɋւ���w�b�_�t�@�C��
#include "cnetplay.h"//�l�b�g���[�N�ڑ��Ɋւ���w�b�_�t�@�C��
#include "citem.h"//�A�C�e���̐錾�w�b�_�t�@�C��]
#include "cStory.h"
#include "Ask.h"// �ʐM�⏕DLL�AAsk�Ɋւ���w�b�_�t�@�C��

/* �Q�[���{�̂̂܂Ƃߍ\���� */
struct GameManage{
	PlayerChara *PC;
	Stage *STG;
	NPC_Head *NPC_H;
};


/* �I�y���[�V�����~�b�V����1�u�V�΂̏����v�ɂ��Ă̏������s�Ȃ��܂� */
int Operation::OpsMission1_Shinryoku(){

		/* �萔�̐錾 */
		int ech = 0;//�G���[�`�F�b�N�p�̕ϐ��錾
		int ScreenPosArray[2] ={0};
		const int EnemyOnNaviLine[6] = { 2, 1, 1, 0, 0};
		const int EnemyOnNaviPoint[6] = { 17, 10, 6, 3, 1};
		const char EnemyNames[6][20] = { "WF0", "WF1", "WF2", "WF3", "WF4", "WF5"} ;
		GameManage GMG;//�܂Ƃߍ\����

		/* �v���O���X�o�[�����܂� */
		E3DCreateProgressBar();

		/* �N���X�̎��̉����s�� */
		PlayerChara Player(1,1);
		pPly = &Player;
		Stage Stg;
		NPC_Head Npc_h;


		/* �܂Ƃߍ\���̂ɑ�� */
		GMG.PC = &Player;
		GMG.STG = &Stg;
		GMG.NPC_H = &Npc_h;

		/* �v���O���X�o�[��i�������� */
		E3DSetProgressBar( 10);

		/* �������t���O���I���ɂ��� */
		System::SetUpdataSoundSys( 1);

		/**/E3DSetProgressBar( 20);// �v���O���X�o�[��i��������
	
		/* Weapon�֌W���� */		
		GMG.PC->Wpn.WpLoad(1,0,0);// �e�̃��[�h
		GMG.PC->Wpn.WpLoad(0,3,1);// �e�̃��[�h
		GMG.PC->Wpn.WpLoad(2,7,0);// �e�̃��[�h
		GMG.PC->Wpn.SetInitWeapon( Weapon_Head::RESET);// �e��̏�����

		/* �v���O���X�o�[��i�������� */
		E3DSetProgressBar( 40); 
		
		/* �X�e�[�W�����[�h���܂� */
		Stg.LoadStage( 6, 0, Stage::NIGHT);

		/**/E3DSetProgressBar( 60);// �v���O���X�o�[��i��������

		/* �G�̐ݒ� */

		for( int i=0; i<5; i++){
			GMG.NPC_H->LoadEnemyModelAddName( EnemyNames[i], 0, 0);// �G�����[�h���܂�
		}

//		GMG.NPC_H->SetEnemyPosByNaviPointArray( &Stg, EnemyNames[0], EnemyOnNaviLine, EnemyOnNaviPoint, 5);//�G�̍��W��ݒ�
		/* �G�̐ݒ肱���܂� */


		/**/E3DSetProgressBar( 90);// �v���O���X�o�[��i��������

		Batch_Render BatProc( &Player, &Stg, GMG.NPC_H, &Cam);// �o�b�`�v���p���[�g�ɂ��ׂĂ̕`�揀���������܂��B
		pBatP = &BatProc;
		
		E3DDestroyProgressBar();// �v���O���X�o�[���󂵂܂�
		pBatP->BatchEnableBumpMap(0);// �o���v�}�b�v��L���ɂ��܂� 
		//BatP.BatchCreateShadow();// �e��L���ɂ��܂�

		

		/* ****** �X�g�[���̊J�n *** */
		Story StoryS;
		StoryS.LoadStoryFromSTD( "test.std");
		StoryS.StartStory(1);
		/* ************************ */


		System::SetMouseCursol( 320, 240);//�}�E�X���E�B���h�E�^�񒆂ɐݒu


		pBatP->BacthGunTrade( Player.Get_Wp_equipment());
		pBatP->BatchChkInView();
		GMG.STG->Navi.SetPosByNaviPoint( Player.Get_BodyModel(), 0, 0);
		

		while( WM_QUIT != System::msg.message ){

				System::MsgQ(30);//���b�Z�[�W���[�v
				System::KeyRenewalFromWp( &Player.Wpn, Player.Get_Wp_equipment());


				pBatP->BatchChkInView();

				// ����֌W
				Player.Wpn.ChkWeaponsLaunch( Player.Get_Wp_equipment());
				Player.NormallyPCSystem( &Stg, pBatP, GMG.NPC_H, &Cam, ScreenPosArray);
				Player.Wpn.AttackEnemys( GMG.NPC_H, &Player, ScreenPosArray, &Stg);
				Player.Wpn.WeaponsTreatment( Player.Get_Wp_equipment(), &Stg);
				GMG.NPC_H->MoveEnemys( &Stg);

				// �`��֘A
				NormalBatchProces();

				// �㏈���֌W
				Menu.FarstInMenu( pBatP, &Player);
				pBatP->BatchBeforePos();
				Player.Batch_PeopleMotion();

		}



	return 0;
}