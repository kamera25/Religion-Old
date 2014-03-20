/*
 * cActor.cpp
 * �A�N�^�[�Ɋւ���L�q���s���܂�
 * �敪 : Model
 * 
 */
#include "cActor.h"
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_


void Actor::LoadMOA( const char *Path)
{
	/* ������ */
	int ech;
	char loadname[256] = "";


	wsprintf( loadname, "%s\\%s", System::path, Path);//�����f����sig���o�^
	ech = E3DLoadMOAFile( ID, loadname, 3, 1.0f); 
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	return;
}

void Actor::BoneNoByName( const char *Name)
{
	/* ������ */
	int ech;
	int BoneID;

	ech = E3DGetBoneNoByName( ID, Name, &BoneID);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/* �{�[����o�^���� */
	Bones.insert( make_pair( string(Name), BoneID));

	return ;
}

void Actor::MOAEventNoML( int EventNo, int *List, int *NoList)
{
	/* ������ */
	int ech;

	ech = E3DSetMOAEventNoML( ID, EventNo, List, NoList);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	return;
}

D3DXVECTOR3 Actor::BonePos( const char *Name)
{
	/* ������ */
	int ech;
	D3DXVECTOR3 BonePosittion;
	map<string, int>::iterator it;
	
	if( Bones.count(Name))
	{
		it = Bones.find(Name);
	}
	else// ��������������������Ȃ����
	{
			_ASSERT( 1 );//�G���[
			return BonePosittion;
	}


	ech = E3DGetCurrentBonePos( ID, (*it).second, 1, &BonePosittion);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	return BonePosittion;
}

int Actor::GetBoneQ( const char *BoneName, const char *QName)
{
	/* ������ */
	int ech;
	int BoneID;
	int QID;
	map<string, int>::iterator it;
	
	/* �{�[���̎擾 */
	if( Bones.count(BoneName))
	{
		it = Bones.find(BoneName);
		BoneID = (*it).second;
	}
	else// ��������������������Ȃ����
	{
			_ASSERT( 1 );//�G���[
			return -1;
	}

	/* �N�I�[�^�[�j�I���̎擾 */
	if( Quaternion.count(QName))
	{
		it = Quaternion.find(QName);
		QID = (*it).second;
	}
	else// ��������������������Ȃ����
	{
			_ASSERT( 1 );//�G���[
			return -1;
	}

	ech = E3DGetCurrentBoneQ( ID, BoneID, 2, QID);//���̌������擾
	_ASSERT( ech != 1 );//�G���[�`�F�b�N
	//ech = E3DGetCurrentBoneQ( ID, Get_Bone_ID(1), 2, Get_Quaternion(0));//���̌������擾
	//_ASSERT( ech != 1 );//�G���[�`�F�b�N


	return QID;
}

void Actor::MotionFinalize( const char *BoneName, const char *QName)
{
	/* ������ */
	int ech;
	int MotionID;
	int BoneID;
	int FrameNo;
	map<string, int>::iterator it;

	/*�}���`���C���[�ɉ����ĐV���[�V�����𓖂Ă�*/
	ech = E3DSetNewPoseML( ID);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/*�u��t�����v�����̃��[�V�����͂ǂ������ׂ܂�*/

	/* �{�[���̎擾 */
	if( Bones.count(BoneName))
	{
		it = Bones.find(BoneName);
		BoneID = (*it).second;
	}
	else// ��������������������Ȃ����
	{
			_ASSERT( 1 );//�G���[
			return;
	}


	ech = E3DGetMotionFrameNoML( ID, BoneID, &MotionID, &FrameNo);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/*�v�Z�����N�H�[�^�[�j�I���������܂�*/
	ech = E3DSetBoneQ( ID, BoneID, MotionID, FrameNo, GetBoneQ( BoneName, QName));
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/*�}���`���C���[���[�V�����̌v�Z���s���܂�*/
	ech = E3DCalcMLMotion( ID);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	return;
}

void Actor::CreateQ( const char * QName)
{
	/* ������ */
	int ech;
	int QID;

	ech = E3DCreateQ( &QID);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	ech = E3DInitQ( QID);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/* �N�I�[�^�[�j�I����o�^���� */
	Bones.insert( make_pair( string(QName), QID));


	return;
}

void Actor::MotionFrameNoML( const char *BoneName)
{
	/* ������ */
	int ech;



	//ech = E3DGetMotionFrameNoML( ID, Get_Bone_ID(2), &MotionID, &FrameNo);
	//_ASSERT( ech != 1 );//�G���[�`�F�b�N

	return;
}

