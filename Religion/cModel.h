#pragma once
/*
 * model.h
 * ���f������Ɋւ���L�q���s���܂�
 *
 *
 */
#include <easy3d.h>

class Model{

protected:

	/* �ϐ� */
	int ID;

private:
	


	/* �֐� */
	void SetID( int ModelID);
	void Destroy();

public:

	Model *Dummy;// �_�~�[���f��

	/* �֐� */
	void SetPos( float X, float Y, float Z);
	D3DXVECTOR3 GetPos();
	void SetPos( D3DXVECTOR3 ModelPos);
	void SetScale( const float Scale);
	void Reparent();// ���f���̕\��
	void Detach();// ���f���̔�\��
	void RotateInit();
	void Forward( const double SumSpeed);
	void RotateY( const double Deg);
	int ConflictOBB( const int ModelID);

	virtual void LoadMOA( const char *Path) {};
	virtual void BoneNoByName( const char *Name) {};

	/* ���֐� */
	static void Initialize(); // ������
	static void Finalize();// �t�@�C�i���C�Y
	static Model* LoadModel( const char *ModelPath);

};