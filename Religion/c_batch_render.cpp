/*�����ł́A���f����X�v���C�g�̕`��ɕK�v�ȏ������W�A�܂��`��ŕK�v��
//�֐��������I�Ɏ��s���邱�Ƃ��ł���悤�ɂ��邽�߂̃N���X�R�[�h�t�@�C��
*/

#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "c_batch_preparat.h"//�`��ɕK�v�ȃN���X�̐錾�w�b�_�t�@�C��
#include "clive.h"//�G��L�����̐錾�w�b�_�t�@�C��


/*�R���X�g���N�^�A�X�e�[�W��v���C���[�N���X�����ɏ������W�A�\�����܂�*/
Batch_Render::Batch_Render( const PlayerChara *PcC, const Stage *StgC, const Enemy *EneC, 
								const Camera *Cam)
{

	/* //////////////////////////////////// */
	// �܂��͂��߂ɂ��ׂĂ̕ϐ������������܂��B
	/* //////////////////////////////////// */
	int ech = 0;//�G���[�`�F�b�N�p�̊m�F�ϐ� 
	const E3DCOLOR4UC AlfaColor = { 100,255,255,255};//�J���[�\���̂̔����߂̃f�[�^
	char loadname[256] = "";//�ǂݍ��ސ�̃p�X�̕�����ϐ�
	
	BumpMapFlag = 0;
	ShadowFlag = 0;

	/*�`��A����p�f�[�^�̍\�z���s���܂�*/
	BatchReset( PcC, StgC, EneC, Cam);


	/* /////////////////////////////////////////////////////// */
	//���ɃX�v���C�g�̃��[�h���s���܂��A�����Ƀf�[�^��������܂�
	/* /////////////////////////////////////////////////////// */

	/*�J�[�\���摜�̃��[�h���s�� �z���[0]��*/
	LoadSprite_AddName( "data\\img\\cursol\\cursol1.png", "Cursol1", 0.7f, 0.7f, 0.0f, 0.0f, 0.0f, true);

	/*�����������܂�*/
	SetSpriteAlpha( "Cursol1", AlfaColor);


	/*�E�X�e�[�^�X�摜�̔w�i�̃��[�h���s��*/
	LoadSprite( "data\\img\\parameter\\parameter3.png", 1.0f, 1.0f, 0.0f, 390.0f, 0.0f, true);

	/*�E�X�e�[�^�X�摜�̔w�i�̃��[�h���s��*/
	LoadSprite( "data\\img\\parameter\\parameter4.png", 1.0f, 1.0f, 506.0f, 390.0f, 0.0f, true);

	/*��HP�̃o�[�̃��[�h���s��*/
	LoadSprite_AddName( "data\\img\\parameter\\hpber.png", "HPber", 100.0f, 1.0f, 24.0f, 412.0f, 0.0f, true);

	/*���X�^�~�i�̃o�[�̃��[�h���s��*/
	LoadSprite_AddName( "data\\img\\parameter\\stnber.png", "Staminaber", 100.0f, 0.5f, 24.0f, 435.0f, 0.0f, true);

	/*�E�e�򐔂̃o�[�̃��[�h���s��*/
	LoadSprite_AddName( "data\\img\\parameter\\ammber.png", "Ammober", 100.0f, 0.8125f, 530.0f, 407.0f, 0.0f, true);

	/*�E�}�K�W�����̃o�[�̃��[�h���s��*/
	LoadSprite_AddName( "data\\img\\parameter\\magber.png", "Magber",100.0f, 0.8125f, 530.0f, 436.0f, 0.0f, true);

	/*���X�e�[�^�X�摜�̃��[�h���s��*/
	LoadSprite( "data\\img\\parameter\\parameter1.png", 1.0f, 1.0f, 0.0f, 390.0f, 0.0f, true);

	/*�E�X�e�[�^�X�摜�̃��[�h���s��*/
	LoadSprite( "data\\img\\parameter\\parameter2.png", 1.0f, 1.0f, 506.0f, 390.0f, 0.0f, true);

	/* ///////////////////////////////////////////////////
	/* PC�N���X����̕���X�v���C�g��ID����ǂݍ��݂܂� */
	/* ///////////////////////////////////////////////////

	/* ���C���E�F�|��*/
	if( PcC->Wpn.Get_WeaponPointer(0) != NULL) LoadSpriteFromID( PcC->Wpn.Get_WeaponPointer(0)->Get_Sprite(), "MainWp", 1.0f, 1.0f, 506.0f, 326.0f, 0.0f, false);

	/* �T�u�E�F�|��*/
	if( PcC->Wpn.Get_WeaponPointer(1) != NULL) LoadSpriteFromID( PcC->Wpn.Get_WeaponPointer(1)->Get_Sprite(), "SubWp", 1.0f, 1.0f, 506.0f, 326.0f, 0.0f, false);

	/* �O���l�[�h*/
	if( PcC->Wpn.Get_WeaponPointer(2) != NULL) LoadSpriteFromID( PcC->Wpn.Get_WeaponPointer(2)->Get_Sprite(), "SupportWp", 1.0f, 1.0f, 506.0f, 326.0f, 0.0f, false);


	return ;
};



/* �f�X�g���N�^�A�X�v���C�g���폜���܂� */
Batch_Render::~Batch_Render(){

	/*�ϐ��̏�����*/
	int ech = 0;//�G���[�`�F�b�N�p�̊m�F�ϐ� 
	vector<Sprite>::iterator it;// �C�e���[�^	

	for( it = Spt.begin(); it != Spt.end(); it++){//���[�h�����X�v���C�g�̍폜
			if( (*it).DeleteFromBRFlag == true){// Batch_Render��������Ă��悢�X�v���C�g�Ȃ�
					ech = E3DDestroySprite( (*it).ID);
					_ASSERT( ech != 1 );//�G���[�`�F�b�N
			}
	}

	if( ShadowFlag == 1){// �e�p�����_�[�e�N�X�`������������Ă���Ȃ�
			ech = E3DDestroyRenderTargetTexture( ShadowScid, ShadowTexture);
			_ASSERT( ech != 1 );//�G���[�`�F�b�N
	}

}

int Batch_Render::BatchBeforePos(){

	/*�ϐ��̏�����*/
	int ech = 0;//�G���[�`�F�b�N�p�̊m�F�ϐ� 
	vector<Model>::iterator it;// �C�e���[�^


	for( it = Mdl.begin(); it != Mdl.end(); it++ ){
			if( (*it).ID != 0){
					ech = E3DSetBeforePos( (*it).ID);
					_ASSERT( ech != 1 );//�G���[�`�F�b�N
			}
	}


	return 0;
}