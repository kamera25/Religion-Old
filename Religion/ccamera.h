#pragma once
/*�J�����Ɋւ��邱�Ƃ̃w�b�_�t�@�C��
//
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��

//�J�����N���X
class Camera{

public:
		//�ϐ��̐錾
		int DummyModel;//�_�~�[���f�����i�[����ID�ϐ�


		//�֐��̐錾
		Camera();//�J�����N���X�̃R���X�g���N�^�A�_�~�[���f���̃��[�h�Ȃǂ����܂�
		~Camera();//�J�����N���X�̃f�X�g���N�^�A�_�~�[���f���Ȃǂ�j�����܂�
		int CamShoulderGunBack( int Qid, float PC_Deg_XZ, D3DXVECTOR3 StomachPos);//���ł����_�ł̃J������ݒ肵�܂�

};