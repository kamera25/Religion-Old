#pragma once
/* �l�ԃN���X�̐錾������w�b�_�t�@�C���B
// !�l��!�N���X�͐����N���X���p�����Ă����Ă��܂�
*/
#include "ccreature.h"// �����N���X�̃w�b�_�t�@�C��

/* �l�ԃN���X */
class People: public Creature{

private:

	/* �ϐ��̐錾 */

	// ���[�V��������Ԃ������ϐ��̎w��
	int UpMotion;//�㔼�g�̃��[�V�����̎w��
	int UnderMotion;//�����g�̃��[�V�����̎w��

	/*����*//*
	Atitude�ϐ�
	0:����  1:���Ⴊ��
	//
	MyState�ϐ�
	0:�ʏ���	1:�L�b�N���  2:�_�b�V�����  3:��������я�ԁ@4:�E������я��
	//
	AirOnPC�ϐ�
	0:�n��  1:��
	*/

	// �v���C���[�L�����N�^�[�̏�ԕϐ�
	int Attitude;//�����̎p����Ԃ�����ϐ�
	int MyState;//�����̓����Ԃ�����ϐ�
	int AirOnPC;//�������󒆂ɂ��邩�w�肷��ϐ�

	//�v���C���[�L�����N�^�[�̌����̕ϐ�
	float PC_Deg_XZ;
	float PC_Deg_Y;

	//�v���C���[�̏��ϐ�
	double Acceleration;//�n�ʂւ̉����x��������ϐ�
	double MoveSpeed;//���ʉ����x������ϐ�

public:

	virtual int Batch_PeopleMotion() = 0;// �l�Ԃ̃��[�V������p���Ȃǂ�ݒ肵�܂�(���z�֐�)
	virtual ~People(){};//���z�R���X�g���N�^

	/* �N���X�Ó��ϐ� */
	static const int NORMAL = 0;// �ʏ���
	static const int KICK = 1;// �L�b�N���
	static const int RUN = 2;// �_�b�V�����
	static const int LEFT_SJUMP = 3;// ���������
	static const int RIGHT_SJUMP = 4;// �E�������

	/* �A�V�X�g(�擾�E���)�֐��̐錾 */
	int Get_UpMotion() const;
	int Set_UpMotion( int Number);
	int Get_UnderMotion() const;
	int Set_UnderMotion( int Number);
	int Get_Attitude() const;
	int Set_Attitude( int Number);
	int Get_MyState() const;
	int Set_MyState( int Number);
	int Set_AirOnPC( int Number);
	float Get_PC_Deg_XZ() const;
	float Set_PC_Deg_XZ( float Number);
	float Get_PC_Deg_Y() const;
	float Set_PC_Deg_Y( float Number);
	double Get_Acceleration() const;
	double Set_Acceleration( double Number);
	double Get_MoveSpeed() const;
	double Set_MoveSpeed( double Number);

	int Get_AirOnPC();

};