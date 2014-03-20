#pragma once
/* �i�r���[���N���X�w�b�_�ł���A����"cnavirail.cpp"�R�[�h��
// �L�����N�^��J�����𐧌䂷��v�ɂȂ�"�i�r���C���g��"�֌W�̃N���X���Ƃ�������Ă��܂��B
/* /////////////////////////////////////////////////////////////////////////// */


/* �i�r���[���N���X�̒�` */
class NaviRail{

private:

	/* �ϐ��̐錾 */
	int NaviRailAvailable;// �i�r���[�����g�p���邩�̕ϐ����i�[����܂� 



public:

	int NaviLineID[10];//�i�r���C�������ʂ��邽�߂�ID�z����i�[���܂�

	/* �֐��̐錾 */
	NaviRail();// �R���X�g���N�^�A�i�r���[�����̏��������s�Ȃ��܂�
	~NaviRail();// �f�X�g���N�^�A�i�r���[�����̍폜���s�Ȃ��܂�

	// �i�r���C���̒ǉ����s�Ȃ��܂�
	int AddNaviPointToStage( const int NaviPointEdge, const int NaviLineNumberconst, float NaviPointPosx,
							const float NaviPointPosy, const float NaviPointPosz);
	int NaviRailOnOffSwitch( const int RailOnOrOff);// �i�r���[����L��/�����ɂ����Ƃ��s�Ȃ��܂�
	int PCControlByNaviRail( const int ModelID, int *TargetNaviPointID, int NaviLineID) const;// �i�r���[���ɂ���ăL�����N�^�[���R���g���[�����܂�
	int NRGivenTransfarFromAToB( const int CreateOnNaviLine, const int ANaviLine, const int ANaviPoint, 
							const int BNaviLine, const int BNaviPoint);// �i�r���[���̏抷�|�C���g���쐬���܂�
	int SetPosByNaviPoint( const int ModelID, const int NaviLine, const int NaviPoint);//�i�r�|�C���g�ɂ���ă��f����ݒu���܂�

	/* �A�V�X�g�֐��n */
	int Get_NaviRailAvailable() const;// NaviRailAvailable���擾���܂�

};