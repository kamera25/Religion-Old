#pragma once
/*
 * model.h
 * モデル操作に関する記述を行います
 *
 *
 */
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "cModel.h"
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

/* 座標の取得 */
D3DXVECTOR3 Model::GetPos()
{
	/* 初期化 */
	int ech ;
	D3DXVECTOR3 ModelPos;

	ech = E3DGetPos( ID, &ModelPos);
	_ASSERT( ech != 1 );//エラーチェック


	return ModelPos;
}

void Model::SetPos( D3DXVECTOR3 ModelPos)
{
	/* 初期化 */
	int ech;

	ech = E3DSetPos( ID, ModelPos);
	_ASSERT( ech != 1 );//エラーチェック


	return;
}

void Model::SetPos( const float X, const float Y, const float Z)
{
	/* 初期化 */
	int ech;

	ech = E3DSetPos( ID, D3DXVECTOR3( X, Y, Z));
	_ASSERT( ech != 1 );//エラーチェック

	return;
}

template<class T>* template<class T>::LoadModel( const char *ModelPath)
{
	/* 初期化 */
	int ech;
	int ID;
	char loadname[256] = "";

	template<class T> *pModel = new Model() ;

	//モデルデータのロード
	wsprintf( loadname, "%s\\%s", System::path, ModelPath);
	ech = E3DSigLoad( loadname, 0, 1.0f, &ID);
	_ASSERT( ech != 1 );//エラーチェック

	pModel->SetID( ID);

	return pModel;
}

void Model::SetScale( const float Scale)
{
	/* 初期化 */
	int ech;

	ech = E3DSetScale( ID, -1, D3DXVECTOR3( Scale, Scale, Scale), 0);
	_ASSERT( ech != 1 );//エラーチェック

	return;
}

void Model::SetID( int ModelID)
{
	ID = ModelID;

	return;
}

void Model::Destroy()
{
	/* 初期化 */
	int ech;
	
	ech = E3DDestroyHandlerSet( ID);
	_ASSERT( ech != 1 );//エラーチェック

	return;
}

/* モデルの表示 */
void Model::Reparent()
{
	/* 初期化 */
	int ech;	

	ech = E3DSetValidFlag( ID, -1, 1);
	_ASSERT( ech != 1 );//エラーチェック	
		
	return ;
}

/* モデルの非表示 */
void Model::Detach()
{
	/* 初期化 */
	int ech;

	ech = E3DSetValidFlag( ID, -1, 0);
	_ASSERT( ech != 1 );//エラーチェック

	return ;
}

/* 初期化 */
void Model::Initialize()
{

	/* ダミーモデルのロード */
	LoadModel( "data\\3d\\model\\other\\demo.sig");


	return;
}

/* 向きの初期化 */
void Model::RotateInit()
{
	/* 初期化 */
	int ech;

	ech = E3DRotateInit ( ID);
	_ASSERT( ech != 1 );//エラーチェック

	return;
}

/* 前進する */
void Model::Forward( const double SumSpeed)
{
	/* 初期化 */
	int ech;

	ech = E3DPosForward( ID, (float)SumSpeed);
	_ASSERT( ech != 1 );//エラーチェック

	return;
}

void Model::RotateY( const double Deg)
{
	/* 初期化 */
	int ech;

	ech = E3DRotateY( ID, (float)Deg);
	_ASSERT( ech != 1 );//エラーチェック

	return;
}

int Model::ConflictOBB( const int ModelID)
{
	/* 初期化 */
	int ech;
	int Conflict;
	int Garbage;

	ech = E3DChkConflictOBB( ID, -1, ModelID, -1, &Conflict, &Garbage);
	_ASSERT( ech != 1 );//エラーチェック


	return Conflict;
}