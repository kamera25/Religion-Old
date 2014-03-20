#pragma once
/* �i�r���[���N���X�w�b�_�ł���A����"cnavirail.cpp"�R�[�h��
// �L�����N�^��J�����𐧌䂷��v�ɂȂ�"�i�r���C���g��"�֌W�̃N���X���Ƃ�������Ă��܂��B
/* /////////////////////////////////////////////////////////////////////////// */

class Actor;

/* �i�r���[���N���X�̒�` */
class NaviRail{

private:

	/* �ϐ��̐錾 */
	bool NaviRailAvailable;// �i�r���[�����g�p���邩�̕ϐ����i�[����܂� 



public:

	int NaviLineID[10];//�i�r���C�������ʂ��邽�߂�ID�z����i�[���܂�
	int NaviPointID[100];// �i�r�|�C���g��ID�z����i�[���܂�
	int CTPoint[20][2];// ��芷���|�C���g�̔ԍ��ɑΉ�����A�i�r�|�C���g�ԍ����i�[����Ă��܂��B [0]���C�� / [1] �|�C���g
	int PointSum;//�|�C���g�̍��v��\���܂�

	/* �֐��̐錾 */
	NaviRail();// �R���X�g���N�^�A�i�r���[�����̏��������s�Ȃ��܂�
	~NaviRail();// �f�X�g���N�^�A�i�r���[�����̍폜���s�Ȃ��܂�

	// �i�r���C���̒ǉ����s�Ȃ��܂�
	int AddNaviPointToStage( const int NaviPointEdge, const int NaviLineNumberconst, float NaviPointPosx,
							const float NaviPointPosy, const float NaviPointPosz);
	int NaviRailOnOffSwitch( const bool RailOnOrOff);// �i�r���[����L��/�����ɂ����Ƃ��s�Ȃ��܂�
	int PCControlByNaviRail( const int ModelID, int *TargetNaviPointID, int NaviLineID) const;// �i�r���[���ɂ���ăL�����N�^�[���R���g���[�����܂�
	int NRGivenTransfarFromAToB( const int CreateOnNaviLine, const int ANaviLine, const int ANaviPoint, 
							const int BNaviLine, const int BNaviPoint);// �i�r���[���̏抷�|�C���g���쐬���܂�
	int SetPosByNaviPoint( Actor *Act, const int NaviLine, const int NaviPoint);//�i�r�|�C���g�ɂ���ă��f����ݒu���܂�
	int AddConectCTPoint( const int ChangePoint, const int LineNum);// ��芷���|�C���g����A�w�肵���|�C���g�փi�r���C�����Ȃ��� 
	int AddNaviPointAsCT( const int NaviPointEdge, const int NaviLineNumber, const float NaviPointPosx,
									const float NaviPointPosy, const float NaviPointPosz, const int CTNum);// �i�r���C���Ƀi�r�|�C���g��ǉ����܂�
	int NVFLoading( char *File ); // �i�r���[���̃t�@�C����ǂݍ��݂܂�
	//int SetPosByNaviPoint2( const int ModelID, const int NaviLine, const int NaviPoint);
	/* �A�V�X�g�֐��n */
	bool Get_NaviRailAvailable() const;// NaviRailAvailable���擾���܂�

};
