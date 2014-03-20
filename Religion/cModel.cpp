#pragma once
/*
 * model.h
 * ���f������Ɋւ���L�q���s���܂�
 *
 *
 */
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "cModel.h"
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

/* ���W�̎擾 */
D3DXVECTOR3 Model::GetPos()
{
	/* ������ */
	int ech ;
	D3DXVECTOR3 ModelPos;

	ech = E3DGetPos( ID, &ModelPos);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N


	return ModelPos;
}

void Model::SetPos( D3DXVECTOR3 ModelPos)
{
	/* ������ */
	int ech;

	ech = E3DSetPos( ID, ModelPos);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N


	return;
}

void Model::SetPos( const float X, const float Y, const float Z)
{
	/* ������ */
	int ech;

	ech = E3DSetPos( ID, D3DXVECTOR3( X, Y, Z));
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	return;
}

template<class T>* template<class T>::LoadModel( const char *ModelPath)
{
	/* ������ */
	int ech;
	int ID;
	char loadname[256] = "";

	template<class T> *pModel = new Model() ;

	//���f���f�[�^�̃��[�h
	wsprintf( loadname, "%s\\%s", System::path, ModelPath);
	ech = E3DSigLoad( loadname, 0, 1.0f, &ID);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	pModel->SetID( ID);

	return pModel;
}

void Model::SetScale( const float Scale)
{
	/* ������ */
	int ech;

	ech = E3DSetScale( ID, -1, D3DXVECTOR3( Scale, Scale, Scale), 0);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	return;
}

void Model::SetID( int ModelID)
{
	ID = ModelID;

	return;
}

void Model::Destroy()
{
	/* ������ */
	int ech;
	
	ech = E3DDestroyHandlerSet( ID);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	return;
}

/* ���f���̕\�� */
void Model::Reparent()
{
	/* ������ */
	int ech;	

	ech = E3DSetValidFlag( ID, -1, 1);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N	
		
	return ;
}

/* ���f���̔�\�� */
void Model::Detach()
{
	/* ������ */
	int ech;

	ech = E3DSetValidFlag( ID, -1, 0);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	return ;
}

/* ������ */
void Model::Initialize()
{

	/* �_�~�[���f���̃��[�h */
	LoadModel( "data\\3d\\model\\other\\demo.sig");


	return;
}

/* �����̏����� */
void Model::RotateInit()
{
	/* ������ */
	int ech;

	ech = E3DRotateInit ( ID);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	return;
}

/* �O�i���� */
void Model::Forward( const double SumSpeed)
{
	/* ������ */
	int ech;

	ech = E3DPosForward( ID, (float)SumSpeed);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	return;
}

void Model::RotateY( const double Deg)
{
	/* ������ */
	int ech;

	ech = E3DRotateY( ID, (float)Deg);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	return;
}

int Model::ConflictOBB( const int ModelID)
{
	/* ������ */
	int ech;
	int Conflict;
	int Garbage;

	ech = E3DChkConflictOBB( ID, -1, ModelID, -1, &Conflict, &Garbage);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N


	return Conflict;
}