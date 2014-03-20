#pragma once
/*
 * cActor.h
 * アクター(モーションを持ったモデル)に関する記述を行います
 * 区分 : Model
 * 
 */
#include "cModel.h"
#include <map>

using namespace std;

class Actor : public Model
{

private:
	map<string, int> Bones;
	map<string, int> Quaternion; // クォータニオン

public:

	void LoadMOA( const char *Path);
	void BoneNoByName( const char *Name);
	void MOAEventNoML( int EventNo, int *List, int *NoList);
	D3DXVECTOR3 BonePos( const char *Name);
	void MotionFinalize( const char *BoneName, const char *QName);
	void CreateQ( const char * QName);
	int GetBoneQ( const char *BoneName, const char *QName);
	void MotionFrameNoML( const char *BoneName);
};