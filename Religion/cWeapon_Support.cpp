/* ///////////////////////////////////////////////////////// */
// �����ł́A����Ɋւ��邱�Ƃ��L�q����N���X�R�[�h�t�@�C���ł�
// ��ɁA�T�|�[�g����֌W�̂��Ƃ�������Ă��܂�
/* /////////////////////////////////////////////////////////  */
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "cWeapon_Support.h"//�T�|�[�g����Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��



// �T�|�[�g����N���X�̃R���X�g���N�^(���[�h���s���܂�) //
Weapon_Support::Weapon_Support( const int Wpno){

	/* �ϐ��̏����� */
	int ech = 0;
	int EffectNo = 0;
	char loadname[256] = "";


	/*���łɏe���擾���Ă���A���̏e�f�[�^�ɏ㏑������Ȃ�*/
	/*if( Get_Model() != -1){//�I�𒆂̃J�e�S���Ƀf�[�^������̂Ȃ�
				ech = E3DDestroyHandlerSet( Get_Model());
				_ASSERT( ech != 1 );//�G���[�`�F�b�N

				ech = E3DDestroySprite( Get_Sprite());//�X�v���C�g���폜���܂�
				_ASSERT( ech != 1 );//�G���[�`�F�b�N
	}*/

	/* �T�|�[�g��������[�h */
	WpLoad_Support( Wpno);

	
	/* �G�t�F�N�g�r���{�[�h�����[�h���܂� */
	wsprintf( loadname, "%s\\data\\img\\effect\\explosion1.png", System::path);
	ech = E3DCreateBillboard ( loadname, 96, 96, 0, 1, 1, &EffectNo);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/* �G�t�F�N�g��\�ߓ��߂��Ă��� */
	ech = E3DSetBillboardAlpha( EffectNo, 0.0f);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/* �G�t�F�N�gID�������o�ϐ��ɑ�� */
	Set_Effects( EffectNo);

	/* �T�|�[�g����f�[�^�̃��[�h������ */
	

	return;
}

// �T�|�[�g����N���X�̃f�X�g���N�^(�A�����[�h���s���܂�) //
Weapon_Support::~Weapon_Support(){




	return;
}