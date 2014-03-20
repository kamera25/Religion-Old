/* ///////////////////////////////////////////////////////// */
// �����ł́A����Ɋւ��邱�Ƃ��L�q����N���X�R�[�h�t�@�C���ł�
// ��ɁA���ꕐ��N���X�֌W�̂��Ƃ�������Ă��܂�
/* /////////////////////////////////////////////////////////  */
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "cweapon.h"// ����Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��
#include "cenemy.h"//�G�N���X�̐錾�w�b�_�t�@�C��
#include "cstage.h"//�X�e�[�W�֌W�̃N���X�w�b�_�t�@�C��
#include "clive.h"//�G��L�����̐錾�w�b�_�t�@�C��

Weapon::Weapon(){

	/* �ϐ��̐錾&������ */
	int ech = 0;
	NowFireFlag = 0;


	return;
}

Weapon::~Weapon(){

	/* �ϐ��̏����� */
	int ech = 0;// �G���[�`�F�b�N�ϐ�

	ech = E3DDestroyHandlerSet( Model);//���f�����폜���܂�
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	ech = E3DDestroySprite( Sprite);//�X�v���C�g���폜���܂�
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	ech = E3DDestroyBillboard( Effects);//�G�t�F�N�g���폜���܂�
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	for( int i=0; i<2; i++){// �T�E���h���폜���܂�

		if( Sounds[i] == -1){
			ech = E3DDestroySound( Sounds[i]);
			_ASSERT( ech != 1 );//�G���[�`�F�b�N
		}
	}

	return;
}

/* �v���Z�b�g���Ă��镐��֘A�������Đ����܂� */
int Weapon::PlayWeaponSound( const int PlayNo, const float MuzzlePosArray[3]){

	/* �ϐ��̏����� */
	int ech = 0;//�G���[�m�F�ϐ�
	D3DXVECTOR3 SoundVelocity( 340.0, 340.0, 340.0);//�����̎w����s���܂�
	D3DXVECTOR3 MuzzlePos( MuzzlePosArray[0], MuzzlePosArray[1], MuzzlePosArray[2]);//�}�Y���t���b�V���T�E���h�̑��xXYZ


	/*���̈ʒu�Ƒ������w�肵�܂�*/
	ech = E3DSet3DSoundMovement( Sounds[PlayNo], MuzzlePos, SoundVelocity);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/*���ˉ���炵�܂�*/
	ech = E3DPlaySound( Sounds[PlayNo], 0, 0, 0);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N


	return 0;
}



