/*�����ł́A���f����X�v���C�g�̕`��ɕK�v�ȏ������W�A�܂��`��ŕK�v��
//�֐��������I�Ɏ��s���邱�Ƃ��ł���悤�ɂ��邽�߂̃N���X�R�[�h�t�@�C��
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "c_batch_preparat.h"//�`��ɕK�v�ȃN���X�̐錾�w�b�_�t�@�C��
#include "clive.h"//�G��L�����̐錾�w�b�_�t�@�C��
#include "cweapon.h"//����Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��

/*������`�悷�邱�Ƃ�ݒ�������肵�܂�*/
int Batch_Render::BatchFont( const int SceneEndFlg, const PlayerChara *PcC){

	/*�ϐ��̏�����*/
	int ech = 0;//�G���[�`�F�b�N�p�̊m�F�ϐ�
	float Scale = 1.6f;//�����̑傫�����i�[����ϐ�
	char ParometaString[64] = "";//�\�������镶�������܂�
	D3DXVECTOR2 Pos( 0.0, 0.0);//���W��������\����
	E3DCOLOR4UC Color = { 255, 50, 50, 50};//��̍\����
	const E3DCOLOR4UC Gray = { 255, 50, 50, 50};//�F�\���́A�O���[���w��
	const E3DCOLOR4UC White = { 255, 230, 230, 230};//�F�\���́A�����w��
	const E3DCOLOR4UC Red = { 255, 255, 100, 100};//�F�\���́A�Ԃ��w��
	const E3DCOLOR4UC Bule = { 255, 100, 100, 250};//�F�\���́A���w��
	const E3DCOLOR4UC Yellow = { 255, 255, 255, 100};//�F�\���́A�����w��

	/*�����̕`��*/
	//HP�����̕`��
	Pos.x = 28.0f;/**/Pos.y = 394.0f;
	ech = E3DDrawText( Pos, Scale, Gray, "F19");
	
			_ASSERT( ech != 1 );//�G���[�`�F�b�N


	if( PcC->Get_Wp_equipment() != -1){ //���킪�Ȃ��ȊO�Ȃ�

			/*���݂�Ammo�̐���\�����܂�*/
			if( PcC->Wpn.GetWeaponDataWhileGame( PcC->Get_Wp_equipment(), 0) == 0){//�e�򂪂Ȃ��Ȃ�����
					Color = Red;// �ԐF�ɂ��܂�
			}
			else if( PcC->Wpn.GetWeaponData( PcC->Get_Wp_equipment(), 2) < PcC->Wpn.GetWeaponDataWhileGame( PcC->Get_Wp_equipment(), 0)){//�e�������Ă���Ȃ�Ȃ�
					Color = Bule;// �ɂ��܂�
			}
			else if( double(PcC->Wpn.GetWeaponDataWhileGame( PcC->Get_Wp_equipment(), 0)) / double(PcC->Wpn.GetWeaponData( PcC->Get_Wp_equipment(), 2)) < 0.3){//�e��3���ȉ��Ȃ�
					Color = Yellow;// ���ɂ��܂�
			}
			else{//�ʏ탂�[�h�Ȃ�
					Color = White;// ���ɂ��܂�
			}
			wsprintf( ParometaString, "%d", PcC->Wpn.GetWeaponDataWhileGame( PcC->Get_Wp_equipment(), 0));
			Pos.x = 558.0f;/**/Pos.y = 394.0f;
			ech = E3DDrawText( Pos, 1.4f, Color, ParometaString);
			
				_ASSERT( ech != 1 );//�G���[�`�F�b�N

			/*Ammo�̐���\�����܂�*/
			wsprintf( ParometaString, "%d", PcC->Wpn.GetWeaponData( PcC->Get_Wp_equipment(), 2));
			Pos.x = 588.0f;/**/Pos.y = 394.0f;
			ech = E3DDrawText( Pos, 1.4f, White, ParometaString);
			
				_ASSERT( ech != 1 );//�G���[�`�F�b�N

			/*���݂�Mag�̐���\�����܂�*/
			if( PcC->Wpn.GetWeaponDataWhileGame( PcC->Get_Wp_equipment(), 1) == 0){//�}�K�W�����Ȃ��Ȃ�����
					Color = Red;// �ԐF�ɂ��܂�
			}
			else if( double(PcC->Wpn.GetWeaponDataWhileGame( PcC->Get_Wp_equipment(), 1)) / double(PcC->Wpn.GetWeaponData( PcC->Get_Wp_equipment(), 3)) < 0.3){//�e��3���ȉ��Ȃ�
					Color = Yellow;// ���ɂ��܂�
			}
			else{//�ʏ탂�[�h�Ȃ�
					Color = White;// ���ɂ��܂�
			}
			wsprintf( ParometaString, "%d", PcC->Wpn.GetWeaponDataWhileGame( PcC->Get_Wp_equipment(), 1));
			Pos.x = 558.0f;/**/Pos.y = 424.0f;
			ech = E3DDrawText( Pos, 1.4f, Color, ParometaString);
			
				_ASSERT( ech != 1 );//�G���[�`�F�b�N

			/*Mag�̐���\�����܂�*/
			wsprintf( ParometaString, "%d", PcC->Wpn.GetWeaponData( PcC->Get_Wp_equipment(), 3));
			Pos.x = 588.0f;/**/Pos.y = 424.0f;
			ech = E3DDrawText( Pos, 1.4f, White, ParometaString);
			
				_ASSERT( ech != 1 );//�G���[�`�F�b�N

	}


	/*
	//�`��̏I������
	*/
	if( SceneEndFlg == 1){

		ech = E3DEndScene();
		
				_ASSERT( ech != 1 );//�G���[�`�F�b�N
	}

	return 0;
}

