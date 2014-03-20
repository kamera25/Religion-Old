/* ///////////////////////////////////////////////////////// */
// �����ł́A�o�b�`�����_�[�̃A�V�X�g�֐��Ɋւ��邱��
// ���L�q����N���X�R�[�h�t�@�C���ł��B
/* /////////////////////////////////////////////////////////  */
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include <string.h>
#include "c_batch_preparat.h"//�`��ɕK�v�ȃN���X�̐錾�w�b�_�t�@�C��





int Batch_Render::Set_SpriteMagY( const char *ObjName, const float Value){

	/* �ϐ��̏�����&�錾 */
	int ech = 0;
	vector<Sprite>::iterator it;
	
	ech = SearchSpriteFromName( ObjName, &it);// �C�e���[�^
	
	if( ech != 0){
			_ASSERT( 1);
			return -1;
	}

	/* MagX�̐ݒ� */
	(*it).MagY = Value;
	
	return 0;
}

int Batch_Render::Set_SpriteX( const char *ObjName, const float Value){

	/* �ϐ��̏�����&�錾 */
	int ech = 0;
	vector<Sprite>::iterator it;
	
	ech = SearchSpriteFromName( ObjName, &it);// �C�e���[�^
	
	if( ech != 0){
			_ASSERT( 1);
			return -1;
	}

	/* MagX�̐ݒ� */
	(*it).X = Value;
	
	return 0;
}

int Batch_Render::Set_SpriteY( const char *ObjName, const float Value){

	/* �ϐ��̏�����&�錾 */
	int ech = 0;
	vector<Sprite>::iterator it;
	
	ech = SearchSpriteFromName( ObjName, &it);// �C�e���[�^
	
	if( ech != 0){
			_ASSERT( 1);
			return -1;
	}

	/* MagX�̐ݒ� */
	(*it).Y = Value;
	
	return 0;
}

int Batch_Render::Set_ViewFlag( const char *ObjName, const bool Value){

	/* �ϐ��̏�����&�錾 */
	int ech = 0;
	vector<Sprite>::iterator it;
	
	ech = SearchSpriteFromName( ObjName, &it);// �C�e���[�^
	
	if( ech != 0){
			_ASSERT( 1);
			return -1;
	}

	/* MagX�̐ݒ� */
	(*it).ViewFlag = Value;
	
	return 0;
}