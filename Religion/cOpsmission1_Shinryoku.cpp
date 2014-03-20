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
#include "cmenu.h"//���j���[�N���X�Ɋւ���w�b�_�t�@�C��
#include "cnetplay.h"//�l�b�g���[�N�ڑ��Ɋւ���w�b�_�t�@�C��
#include "citem.h"//�A�C�e���̐錾�w�b�_�t�@�C��
#include "Ask.h"// �ʐM�⏕DLL�AAsk�Ɋւ���w�b�_�t�@�C��

/* �I�y���[�V�����~�b�V����1�u�V�΂̏����v�ɂ��Ă̏������s�Ȃ��܂� */
int Operation::OpsMission1_Shinryoku(){

		/* �萔�̐錾 */
		int ech = 0;//�G���[�`�F�b�N�p�̕ϐ��錾
		int ScreenPosArray[2] ={0};
		const int EnemyOnNaviLine[6] = { 2, 1, 1, 0, 0};
		const int EnemyOnNaviPoint[6] = { 17, 10, 6, 3, 1};

		/* �N���X�̎��̉����s�� */
		PlayerChara Player(1,1);
		Stage Stg;
		Enemy Ene;

		E3DCreateProgressBar();// �v���O���X�o�[�����܂�
		/**/E3DSetProgressBar( 10);// �v���O���X�o�[��i��������

		System::SetUpdataSoundSys( 1);// �������t���O���I���ɂ���

		/**/E3DSetProgressBar( 20);// �v���O���X�o�[��i��������
	
		/* Weapon�֌W���� */		
		Player.Wpn.WpLoad(1,0,0);// �e�̃��[�h
		Player.Wpn.SetInitWeapon( -1);// �e��̏�����

		/**/E3DSetProgressBar( 40);// �v���O���X�o�[��i��������

		Stg.LoadStage(6,0,2);// �X�e�[�W�����[�h���܂�
		/**/E3DSetProgressBar( 60);// �v���O���X�o�[��i��������
		for( int i=0; i<5; i++){
			Ene.LoadEnemyModel( 0, 0);// �G�����[�h���܂�
		}
		Ene.SetEnemyPosByNaviPointArray( &Stg, EnemyOnNaviLine, EnemyOnNaviPoint, 5);//�G�̍��W��ݒ�
		



		/**/E3DSetProgressBar( 90);// �v���O���X�o�[��i��������

		Batch_Render BatP( &Player, &Stg, &Ene, &Cam);// �o�b�`�v���p���[�g�ɂ��ׂĂ̕`�揀���������܂��B
		E3DDestroyProgressBar();// �v���O���X�o�[���󂵂܂�		
		BatP.BatchEnableBumpMap(0);// �o���v�}�b�v��L���ɂ��܂� 
		//BatP.BatchCreateShadow();// �e��L���ɂ��܂�

		SetCursorPos( System::rewin.left + 320, System::rewin.top + 240);//�}�E�X���E�B���h�E�^�񒆂ɐݒu



		
		BatP.BatchChkInView();
		D3DXVECTOR3 GroundOnPos( 0.0, 10000.0, 0.0);
		E3DSetPos( Player.Get_BodyModel(), GroundOnPos);
		



		while( WM_QUIT != System::msg.message ){

				System::MsgQ(30);//���b�Z�[�W���[�v

			//	if( Player.Get_Wp_equipment() != -1 ) System::KeyRenewal( Player.Wpn.GetWeaponData( Player.Get_Wp_equipment(), 7) + 1);
				/*else*/ System::KeyRenewal(1);
				BatP.BatchChkInView();
				Player.Wpn.ChkWeaponsLaunch( Player.Get_Wp_equipment());

				Player.NormallyPCSystem( &Stg, &BatP, &Ene, &Cam, ScreenPosArray);
				Player.Wpn.AttackEnemys( &Ene, &Player, ScreenPosArray, &Stg);
				Ene.MoveEnemys( &Stg);

				BatP.BatchSpriteSet( &Player);
				BatP.BatchRender( 0);
				Player.Wpn.WeaponsTreatment( Player.Get_Wp_equipment());
				BatP.BatchSpriteRender( 0);
				BatP.BatchFont( 1, &Player);


				BatP.Batch_Present();

				Menu.FarstInMenu( &BatP, &Player);
				BatP.BatchBeforePos();
				Player.Batch_PeopleMotion();

		}



	return 0;
}