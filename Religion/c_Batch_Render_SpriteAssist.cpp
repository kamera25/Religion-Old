/* ///////////////////////////////////////////////////////// */
// �����ł́A�o�b�`�����_�[�̃A�V�X�g�֐��Ɋւ��邱��
// ���L�q����N���X�R�[�h�t�@�C���ł��B
/* /////////////////////////////////////////////////////////  */
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include <string.h>
#include "c_batch_preparat.h"//�`��ɕK�v�ȃN���X�̐錾�w�b�_�t�@�C��
#include <string>




int Batch_Render::Set_SpriteMagY( const char *ObjName, const float Value){

	/* �ϐ��̏�����&�錾 */
	int ech = 0;
	map<string, Sprite>::iterator it;
	
	if( Spt.count(ObjName))
	{
		it = Spt.find(ObjName);
	}
	else// ��������������������Ȃ����
	{
			_ASSERT( 1 );//�G���[
			return -1;
	}

	/* MagX�̐ݒ� */
	(*it).second.MagY = Value;
	
	return 0;
}

int Batch_Render::Set_SpriteX( const char *ObjName, const float Value){

	/* �ϐ��̏�����&�錾 */
	int ech = 0;
	map<string, Sprite>::iterator it;
	
	if( Spt.count(ObjName))
	{
		it = Spt.find(ObjName);
	}
	else// ��������������������Ȃ����
	{
			_ASSERT( 1 );//�G���[
			return -1;
	}

	/* MagX�̐ݒ� */
	(*it).second.X = Value;
	
	return 0;
}

int Batch_Render::Set_SpriteY( const char *ObjName, const float Value){

	/* �ϐ��̏�����&�錾 */
	int ech = 0;
	map<string, Sprite>::iterator it;
	
	if( Spt.count(ObjName))
	{
		it = Spt.find(ObjName);
	}
	else// ��������������������Ȃ����
	{
			_ASSERT( 1 );//�G���[
			return -1;
	}

	/* MagX�̐ݒ� */
	(*it).second.Y = Value;
	
	return 0;
}

int Batch_Render::Set_ViewFlag( const char *ObjName, const bool Value){

	/* �ϐ��̏�����&�錾 */
	int ech = 0;
	map<string, Sprite>::iterator it;
	
	if( Spt.count(ObjName))
	{
		it = Spt.find(ObjName);
	}
	else// ��������������������Ȃ����
	{
			_ASSERT( 1 );//�G���[
			return -1;
	}

	/* MagX�̐ݒ� */
	(*it).second.ViewFlag = Value;
	
	return 0;
}

int Batch_Render::test()
{
	
	Spt.count("MainWp");
	PutLog("hello");

	return 0;
}