#pragma once
/*�J�����Ɋւ��邱�Ƃ̃w�b�_�t�@�C��
//
*/

//�v���g�^�C�v�錾
class Stage;

//�J�����N���X
class Camera{
private:
		//�ϐ��̐錾
		int ShoulderComMode;// ������Ԃł̃J�������[�h���i�[���܂�(�ړ���:-1 �L�����E:0 �L������:1)
		int ShoulderComCounter;// ������Ԃł̈ړ��J�E���^�[
		int ShoulderComMoveDeg;// ������Ԃł̃J�����ړ��ɑ΂���A�ړ������w��ϐ�(�J�������E��:1 �J����������:-1)

public:
		//�ϐ��̐錾
		int DummyModel;//�_�~�[���f�����i�[����ID�ϐ�


		//�֐��̐錾
		Camera();//�J�����N���X�̃R���X�g���N�^�A�_�~�[���f���̃��[�h�Ȃǂ����܂�
		~Camera();//�J�����N���X�̃f�X�g���N�^�A�_�~�[���f���Ȃǂ�j�����܂�
		int CamShoulderGunBack( const int cha_hsid, const int Qid, const int bone, const float PC_Deg_XZ, const Stage *Stg);//���ł����_�ł̃J������ݒ肵�܂�

};