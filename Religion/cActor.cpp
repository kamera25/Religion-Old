/*
 * cActor.cpp
 * アクターに関する記述を行います
 * 区分 : Model
 * 
 */
#include "cActor.h"
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ


void Actor::LoadMOA( const char *Path)
{
	/* 初期化 */
	int ech;
	char loadname[256] = "";


	wsprintf( loadname, "%s\\%s", System::path, Path);//仮モデルのsig名登録
	ech = E3DLoadMOAFile( ID, loadname, 3, 1.0f); 
	_ASSERT( ech != 1 );//エラーチェック

	return;
}

void Actor::BoneNoByName( const char *Name)
{
	/* 初期化 */
	int ech;
	int BoneID;

	ech = E3DGetBoneNoByName( ID, Name, &BoneID);
	_ASSERT( ech != 1 );//エラーチェック

	/* ボーンを登録する */
	Bones.insert( make_pair( string(Name), BoneID));

	return ;
}

void Actor::MOAEventNoML( int EventNo, int *List, int *NoList)
{
	/* 初期化 */
	int ech;

	ech = E3DSetMOAEventNoML( ID, EventNo, List, NoList);
	_ASSERT( ech != 1 );//エラーチェック

	return;
}

D3DXVECTOR3 Actor::BonePos( const char *Name)
{
	/* 初期化 */
	int ech;
	D3DXVECTOR3 BonePosittion;
	map<string, int>::iterator it;
	
	if( Bones.count(Name))
	{
		it = Bones.find(Name);
	}
	else// 検索した文字が見つからなければ
	{
			_ASSERT( 1 );//エラー
			return BonePosittion;
	}


	ech = E3DGetCurrentBonePos( ID, (*it).second, 1, &BonePosittion);
	_ASSERT( ech != 1 );//エラーチェック

	return BonePosittion;
}

int Actor::GetBoneQ( const char *BoneName, const char *QName)
{
	/* 初期化 */
	int ech;
	int BoneID;
	int QID;
	map<string, int>::iterator it;
	
	/* ボーンの取得 */
	if( Bones.count(BoneName))
	{
		it = Bones.find(BoneName);
		BoneID = (*it).second;
	}
	else// 検索した文字が見つからなければ
	{
			_ASSERT( 1 );//エラー
			return -1;
	}

	/* クオーターニオンの取得 */
	if( Quaternion.count(QName))
	{
		it = Quaternion.find(QName);
		QID = (*it).second;
	}
	else// 検索した文字が見つからなければ
	{
			_ASSERT( 1 );//エラー
			return -1;
	}

	ech = E3DGetCurrentBoneQ( ID, BoneID, 2, QID);//手先の向きを取得
	_ASSERT( ech != 1 );//エラーチェック
	//ech = E3DGetCurrentBoneQ( ID, Get_Bone_ID(1), 2, Get_Quaternion(0));//手先の向きを取得
	//_ASSERT( ech != 1 );//エラーチェック


	return QID;
}

void Actor::MotionFinalize( const char *BoneName, const char *QName)
{
	/* 初期化 */
	int ech;
	int MotionID;
	int BoneID;
	int FrameNo;
	map<string, int>::iterator it;

	/*マルチレイヤーに沿って新モーションを当てる*/
	ech = E3DSetNewPoseML( ID);
	_ASSERT( ech != 1 );//エラーチェック

	/*「首付け根」部分のモーションはどうか調べます*/

	/* ボーンの取得 */
	if( Bones.count(BoneName))
	{
		it = Bones.find(BoneName);
		BoneID = (*it).second;
	}
	else// 検索した文字が見つからなければ
	{
			_ASSERT( 1 );//エラー
			return;
	}


	ech = E3DGetMotionFrameNoML( ID, BoneID, &MotionID, &FrameNo);
	_ASSERT( ech != 1 );//エラーチェック

	/*計算したクォーターニオンを代入します*/
	ech = E3DSetBoneQ( ID, BoneID, MotionID, FrameNo, GetBoneQ( BoneName, QName));
	_ASSERT( ech != 1 );//エラーチェック

	/*マルチレイヤーモーションの計算を行います*/
	ech = E3DCalcMLMotion( ID);
	_ASSERT( ech != 1 );//エラーチェック

	return;
}

void Actor::CreateQ( const char * QName)
{
	/* 初期化 */
	int ech;
	int QID;

	ech = E3DCreateQ( &QID);
	_ASSERT( ech != 1 );//エラーチェック

	ech = E3DInitQ( QID);
	_ASSERT( ech != 1 );//エラーチェック

	/* クオーターニオンを登録する */
	Bones.insert( make_pair( string(QName), QID));


	return;
}

void Actor::MotionFrameNoML( const char *BoneName)
{
	/* 初期化 */
	int ech;



	//ech = E3DGetMotionFrameNoML( ID, Get_Bone_ID(2), &MotionID, &FrameNo);
	//_ASSERT( ech != 1 );//エラーチェック

	return;
}

