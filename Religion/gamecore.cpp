/*�����ł́A�Q�[�����C�����[�v�����A����ъe�V�X�e�����Ăяo���܂��B
//
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_
#include "cstage.h"//�X�e�[�W�֌W�̃N���X�w�b�_�t�@�C��
#include "clive.h"//�G��L�����̃N���X�w�b�_�t�@�C��
#include "c_batch_preparat.h"//�`��ɕK�v�ȃN���X�̐錾�w�b�_�t�@�C��
#include "cmenu.h"//���j���[�N���X�Ɋւ���w�b�_�t�@�C��
#include "cenemy.h"//�G�N���X�̐錾�w�b�_�t�@�C��


//�����Ŏg���O���[�o���ϐ���錾
extern System *sys;//�V�X�e���N���X���w���A�N���X�̃|�C���^


//�Q�[�����X�^�[�g���܂��B
int GMStart(){

	sys->WaitRender();//�ǂݍ��݉�ʂ�\�������܂�
	E3DCreateProgressBar();//�v���O���X�o�[�����܂�
	
	PlayerChara wfarmy(1,0);
		E3DSetProgressBar( 20);//�v���O���X�o�[��i��������
	wfarmy.GunLoad(0,4,0);
	wfarmy.GunLoad(1,1,0);
		E3DSetProgressBar( 40);//�v���O���X�o�[��i��������
	Stage trm;
	trm.LoadStage(3,0,0);
		E3DSetProgressBar( 80);//�v���O���X�o�[��i��������
	Enemy ene;
	ene.LoadEnemyModel( -1, 0);
		E3DSetProgressBar( 90);//�v���O���X�o�[��i��������
	Camera cam;
	Batch_Preparat bp( &wfarmy, &trm, &ene, &cam);
	Menu menu;


	E3DDestroyProgressBar();//�v���O���X�o�[���󂵂܂�

	sys->MsgQ(30);//���b�Z�[�W���[�v
	SetCursorPos( sys->rewin.left + 320, sys->rewin.top + 240);//�}�E�X���E�B���h�E�^�񒆂ɐݒu
	sys->MsgQ(30);//���b�Z�[�W���[�v

	/**/
	D3DXVECTOR3 GroundOnPos( 23000.0, 1200.0, 0.0);//
	E3DSetPos( wfarmy.cha_hsid[0], GroundOnPos);
	/**/



	do{

		//�Ƃ肠���������ɏ����Ă݂�A��ŕ��G�ɂ��肱�܂���B
		//�ϐ��̐錾
		int ech = 0;//�G���[�`�F�b�N�p�̕ϐ��錾

		sys->Keyget(1);
		bp.BatchChkInView();

		//wfarmy.ThirdGunSys( &trm, &bp);
		wfarmy.NormallyPCSystem( &trm, &bp, &ene, &cam);

		ene.MoveEnemys( &trm);

		bp.BatchSpriteSet( &wfarmy);
		bp.BatchRender( 0);
		bp.BatchSpriteRender( 0);
		bp.BatchFont( 1);

		ech = E3DPresent( sys->scid1);
		if(ech != 0){//�G���[�`�F�b�N
					_ASSERT(0);//�G���[�_�C�A���O��\��
		};

		menu.FarstInMenu( &bp, &wfarmy);


		bp.BatchBeforePos();
		wfarmy.ShoulderGunSysBefore();

		sys->MsgQ(30);//���b�Z�[�W���[�v

	}while( WM_QUIT != sys->msg.message );



	return 0;
}