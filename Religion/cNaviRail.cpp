/* �i�r���[���N���X�n�R�[�h�̈ꕔ�ł���A����"cNaviRail.cpp"�R�[�h��
// �L�����N�^��J�����𐧌䂷��v�ɂȂ�"�i�r���C���g��"�֌W�̂��Ƃ�������Ă��܂��B
/* /////////////////////////////////////////////////////////////////////////// */
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include <stdio.h>
#include <string.h>
#include "cActor.h"
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_
#include "cnavirail.h"//�i�r���[���Ɋւ���w�b�_�t�@�C��

/* NaviRail�N���X�̃R���X�g���N�^*/
NaviRail::NaviRail(){

	/* �ϐ��̐錾&������ */
	int ech = 0;// �G���[�m�F�p�ϐ�
	PointSum = 0;//�|�C���g�̍��v��\���܂�

	// �i�r���C�����쐬���܂�
	for( int i=0; i<10; i++){
			ech = E3DCreateNaviLine( &NaviLineID[i]); 
			if( ech != 0){
						_ASSERT( 0 );
						return;
			};
	}

	// �i�r���C�����p�ϐ����I�t�ɂ��܂�
	NaviRailAvailable = false;


	return;
}
/* NaviRail�N���X�̃f�X�g���N�^*/
NaviRail::~NaviRail(){

	/* �ϐ��̐錾&������ */
	int ech = 0;// �G���[�`�F�b�N�ϐ��̏�����

	//�i�r���C�����폜���܂�
	for( int i=0; i<10; i++){
			ech = E3DDestroyNaviLine( NaviLineID[i]);
			if( ech != 0){
						_ASSERT( 0 );
			};
	}


	return;
}
/* �i�r���C���Ƀi�r�|�C���g��ǉ����܂� */
int NaviRail::AddNaviPointToStage( const int NaviPointEdge, const int NaviLineNumber, const float NaviPointPosx,
									const float NaviPointPosy, const float NaviPointPosz)
{
	/* �ϐ��̐錾&������ */
	int ech = 0;// �G���[�`�F�b�N�ϐ��̏�����
	int NaviPoint = 0;//�V�����ǉ������i�r�|�C���g��ID����
	D3DXVECTOR3 NaviPointPos( NaviPointPosx, NaviPointPosy, NaviPointPosz);//�i�r�|�C���g���W��������\����


	/* /////////////////////////////////// */
	// �i�r���C����Ƀi�r�|�C���g��ݒu���܂�
	/* /////////////////////////////////// */

	ech = E3DAddNaviPoint( NaviLineID[NaviLineNumber], NaviPointEdge, &NaviPoint);//�i�r�|�C���g��ǉ�
	if( ech != 0){
				_ASSERT( 0 );
				return 1;
	};
	ech = E3DSetNaviPointPos( NaviLineID[NaviLineNumber], NaviPoint, NaviPointPos);//�i�r�|�C���g�̍��W���w��
	if( ech != 0){
				_ASSERT( 0 );
				return 1;
	};

	NaviPointID[PointSum] = NaviPoint;
	PointSum++;

	return NaviPoint;
}
/* �i�r���C���̎g�p��L��/�����ɂ��܂� */
int NaviRail::NaviRailOnOffSwitch( const bool RailOnOrOff){

	NaviRailAvailable = RailOnOrOff;

	return 0;
}
/* NaviRailAvailable���擾���܂� */
bool NaviRail::Get_NaviRailAvailable() const{

	return NaviRailAvailable;
}
/* �i�r���[���ɂ���ăL�����N�^�[���R���g���[�����܂� */
int NaviRail::PCControlByNaviRail( const int ModelID, int *TargetNaviPointID, int NaviLineID) const{

	/* �ϐ��̏�����&�錾 */
	D3DXQUATERNION NewhsidQ;//�ړ���̃N�H�[�^�j�I���������܂�
	D3DXVECTOR3 NewhsidPos( 0.0, 0.0, 0.0);//�ړ���̍��W�������܂�
	int ech = 0;// �G���[�`�F�b�N�ϐ�

	ech = E3DControlByNaviLine( ModelID, NaviLineID, 4, 1, 0, 10.0f, 30.0f, 100.0f, &NewhsidPos, &NewhsidQ, TargetNaviPointID );
	_ASSERT( ech != 1 );//�G���[�`�F�b�N
	ech = E3DSetPos( ModelID, NewhsidPos);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N
	ech = E3DSetDirQ( ModelID, NewhsidQ);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N


	return 0;
}
/* �i�r�|�C���g�ɂ���ă��f����ݒu���܂� */
int NaviRail::SetPosByNaviPoint( Actor *Act, const int NaviLine, const int NaviPoint){

	/* �ϐ��̐錾&������ */
	int ech = 0;// �G���[�`�F�b�N�ϐ��̏�����
	D3DXVECTOR3 NaviPointPos( 0.0f, 0.0f, 0.0f);//�i�r�|�C���g���W��������\����

	// �i�r�|�C���g�̍��W���擾���܂�
	ech = E3DGetNaviPointPos( NaviLineID[NaviLine], NaviPointID[NaviPoint], &NaviPointPos);
	if( ech != 0){
				_ASSERT( 0 );
				return 1;
	};

	// ���W�Ƀ��f����ݒu���܂�
	Act->SetPos( NaviPointPos);
	//ech = E3DSetPos( ModelID, NaviPointPos);
	//if( ech != 0){
	//			_ASSERT( 0 );
	//			return 1;
	//};


	return 0;
}

/* �i�r�|�C���g�ɂ���ă��f����ݒu���܂�(�i�r���[���Ή�) */
//int NaviRail::SetPosByNaviPoint2( const int ModelID, const int NaviLine, const int NaviPoint){
//
//	/* �ϐ��̐錾&������ */
//	int ech = 0;// �G���[�`�F�b�N�ϐ��̏�����
//	D3DXVECTOR3 NaviPointPos( 0.0f, 0.0f, 0.0f);//�i�r�|�C���g���W��������\����
//
//	// �i�r�|�C���g�̍��W���擾���܂�
//	ech = E3DGetNaviPointPos( NaviLineID[NaviLine], NaviPointID[NaviPoint], &NaviPointPos);
//	if( ech != 0){
//				_ASSERT( 0 );
//				return 1;
//	};
//
//	// ���W�Ƀ��f����ݒu���܂�
//	ech = E3DSetPos( ModelID, NaviPointPos);
//	if( ech != 0){
//				_ASSERT( 0 );
//				return 1;
//	};
//
//
//	return 0;
//}


/* �i�r���[���̏抷�|�C���g���쐬���܂� */
int NaviRail::NRGivenTransfarFromAToB( const int CreateOnNaviLine, const int ANaviLine, const int ANaviPoint, 
							const int BNaviLine, const int BNaviPoint)
{

	/* �ϐ��̐錾&������ */
	int ech = 0;// �G���[�`�F�b�N�ϐ��̏�����
	int NaviPoint = 0;//�V�����ǉ������i�r�|�C���g��ID����
	D3DXVECTOR3 NaviPointPos( 0.0f, 0.0f, 0.0f);//�i�r�|�C���g���W��������\����


	/* /////////////////////////////////// */
	// �i�r���C����Ƀi�r�|�C���g��ݒu���܂�
	/* /////////////////////////////////// */


	/* ���i�r�|�C���g�̐ݒ���s�Ȃ��܂� */
	ech = E3DAddNaviPoint( NaviLineID[CreateOnNaviLine], -2, &NaviPoint);//�i�r�|�C���g��ǉ�
	if( ech != 0){
				_ASSERT( 0 );
				return 1;
	};
	ech = E3DGetNaviPointPos( NaviLineID[ANaviLine], ANaviPoint, &NaviPointPos);// From���W�̎擾���s�Ȃ��܂�
	if( ech != 0){
				_ASSERT( 0 );
				return 1;
	};
	ech = E3DSetNaviPointPos( NaviLineID[CreateOnNaviLine], NaviPoint, NaviPointPos);//�i�r�|�C���g�̍��W���w��
	if( ech != 0){
				_ASSERT( 0 );
				return 1;
	};


	/* �O�i�r�|�C���g�̐ݒ���s�Ȃ��܂� */
	ech = E3DAddNaviPoint( NaviLineID[CreateOnNaviLine], -1, &NaviPoint);//�i�r�|�C���g��ǉ�
	if( ech != 0){
				_ASSERT( 0 );
				return 1;
	};
	ech = E3DGetNaviPointPos( NaviLineID[BNaviLine], BNaviPoint, &NaviPointPos);// From���W�̎擾���s�Ȃ��܂�
	if( ech != 0){
				_ASSERT( 0 );
				return 1;
	};
	ech = E3DSetNaviPointPos( NaviLineID[CreateOnNaviLine], NaviPoint, NaviPointPos);//�i�r�|�C���g�̍��W���w��
	if( ech != 0){
				_ASSERT( 0 );
				return 1;
	};




	return 0;
}


/* ��芷���|�C���g����A�w�肵���|�C���g�փi�r���C�����Ȃ��� */
int NaviRail::AddConectCTPoint( const int ChangePoint, const int LineNum){
	
	
	/* ������ */
	D3DXVECTOR3 NaviPointPos( 0.0f, 0.0f, 0.0f);//�i�r�|�C���g���W��������\����
	int ech = 0;
	
	ech = E3DGetNaviPointPos( CTPoint[ChangePoint][0], CTPoint[ChangePoint][1], &NaviPointPos);// From���W�̎擾���s�Ȃ��܂�
	if( ech != 0){
				_ASSERT( 0 );
				return 1;
	};
	AddNaviPointToStage( -1, LineNum, NaviPointPos.x, NaviPointPos.y, NaviPointPos.z);
	
	
	
	
	
	return 0;
}

/* �i�r���C���Ƀi�r�|�C���g��ǉ����܂� */
int NaviRail::AddNaviPointAsCT( const int NaviPointEdge, const int NaviLineNumber, const float NaviPointPosx,
									const float NaviPointPosy, const float NaviPointPosz, const int CTNum)
{
	/* �ϐ��̐錾&������ */
	int ech = 0;// �G���[�`�F�b�N�ϐ��̏�����
	int NaviPoint = 0;//�V�����ǉ������i�r�|�C���g��ID����
	D3DXVECTOR3 NaviPointPos( NaviPointPosx, NaviPointPosy, NaviPointPosz);//�i�r�|�C���g���W��������\����


	/* /////////////////////////////////// */
	// �i�r���C����Ƀi�r�|�C���g��ݒu���܂�
	/* /////////////////////////////////// */

	ech = E3DAddNaviPoint( NaviLineID[NaviLineNumber], NaviPointEdge, &NaviPoint);//�i�r�|�C���g��ǉ�
	if( ech != 0){
				_ASSERT( 0 );
				return 1;
	};
	ech = E3DSetNaviPointPos( NaviLineID[NaviLineNumber], NaviPoint, NaviPointPos);//�i�r�|�C���g�̍��W���w��
	if( ech != 0){
				_ASSERT( 0 );
				return 1;
	};

	CTPoint[CTNum][0] = NaviLineID[NaviLineNumber];// ���C���ԍ�
	CTPoint[CTNum][1] = NaviPoint; // �|�C���g�ԍ�

	return NaviPoint;
}


/* �i�r���[���̃t�@�C����ǂݍ��݂܂� */
int NaviRail::NVFLoading( char *File )
{
	
	/* ������ */
	int Parameter[6] = {0};
	double dParameter[6] = {0};
	int LineNum = -1;
	int i = 0;
	int ech = 0;
//	char CParameter;
	char LoadFullPath[256];
	char Statement[32];
	FILE *fp;

	/* �t�@�C���̃I�[�v���̏��� */
	wsprintf( LoadFullPath, "%s\\data\\prof\\navi\\%s", System::path, File);
	fopen_s( &fp, LoadFullPath, "r");//�w�肳�ꂽ�t�@�C�����I�[�v�����܂��B 
	if( fp == NULL){
		_ASSERT( 0 );
		return -1;
	}

	/* �v���O���X�o�[�����܂� */
	E3DCreateProgressBar();
	
	/* �i�r���[�����g�p���� */
	NaviRailOnOffSwitch( true);

	/* �ǂݎ�����X�e�[�g�����g�ŕ��� */
	while( fscanf_s( fp, "%s", &Statement, 32) !=EOF)
	{
		// Line�Ȃ�A����I��
		if( strcmp( Statement, "line") == NULL)
		{
			
			fscanf_s( fp, "%d", &Parameter[0]);

			LineNum = Parameter[0];

		}

		// add�Ȃ�A�i�r�|�C���g��ǉ�
		else if( strcmp( Statement, "add") == NULL)
		{
			
			fscanf_s( fp, "%lf %lf %lf", &dParameter[0], &dParameter[1], &dParameter[2]);

			AddNaviPointToStage( -1, LineNum, (float)dParameter[0], (float)dParameter[1], (float)dParameter[2]);

		}
		
		// addct�Ȃ�A�w��̃|�C���g����芷���|�C���g�Ƃ��ēo�^
		else if( strcmp( Statement, "addct") == NULL)
		{
			
			fscanf_s( fp, "%lf %lf %lf %d", &dParameter[0], &dParameter[1], &dParameter[2], &Parameter[0]);

			AddNaviPointAsCT( -1, LineNum, (float)dParameter[0], (float)dParameter[1], (float)dParameter[2], Parameter[0]);

		}
		
		// addcct�Ȃ�A���łɂ���|�C���g�����݂̃��C���̏�芷���|�C���g�Ƃ��Ēǉ�
		else if( strcmp( Statement, "addcct") == NULL)
		{
			
			fscanf_s( fp, "%d", &Parameter[0]);

			AddConectCTPoint( Parameter[0], LineNum);
		}

	
	}
	
	
	/* FILE�̊J�� */
	fclose(fp);
	
	
	
	return 0;
}

