#pragma once
/*
 * model.h
 * モデル操作に関する記述を行います
 *
 *
 */
#include <easy3d.h>

class Model{

protected:

	/* 変数 */
	int ID;

private:
	


	/* 関数 */
	void SetID( int ModelID);
	void Destroy();

public:

	Model *Dummy;// ダミーモデル

	/* 関数 */
	void SetPos( float X, float Y, float Z);
	D3DXVECTOR3 GetPos();
	void SetPos( D3DXVECTOR3 ModelPos);
	void SetScale( const float Scale);
	void Reparent();// モデルの表示
	void Detach();// モデルの非表示
	void RotateInit();
	void Forward( const double SumSpeed);
	void RotateY( const double Deg);
	int ConflictOBB( const int ModelID);

	virtual void LoadMOA( const char *Path) {};
	virtual void BoneNoByName( const char *Name) {};

	/* 大域関数 */
	static void Initialize(); // 初期化
	static void Finalize();// ファイナライズ
	static Model* LoadModel( const char *ModelPath);

};