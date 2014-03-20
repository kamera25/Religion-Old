#pragma once
/*�����N���X�̃L�����E�G�̐錾������w�b�_�t�@�C���B
//
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "c_batch_preparat.h"//�`��ɕK�v�ȃN���X�̐錾�w�b�_�t�@�C��
#include "cenemy.h"//�G�N���X�̐錾�w�b�_�t�@�C��
#include "ccamera.h"//�J�����Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��
class Batch_Preparat;//�z�ϐ��΍�

//�v���C���[�L�����N�^�[�N���X���쐬�A�������i���̑��L������chara�N���X�ɂč쐬�\�j
class PlayerChara{

public:

	//�ϐ��̐錾

	int MaxHP;//�L�����N�^�̍ő�HP
	int HP;//�L�����N�^��HP
	int Stamina;//�L�����N�^�̃X�^�~�i

	//���f���f�[�^
	int cha_hsid[2];//�L�����N�^�̃��f��ID [0]�m�[�}�����f����hsid [1]��̃��f����hsid
	int DummyModel;//�_�~�[���f���̃��f��ID
	
	/*
	//bone�z��ɂ̓{�[�����i�[����܂� [0]������E [1]�������E [2]���Ȃ�
	// [3] 
	*/
	int bone[10];//�L�����N�^�[�̍����i�[���܂�

	/*
	// [0] �e�̌��� [1] �e�̓����蔻�胂�f���̌���
	// [2] ���f�����W�̌��� [3] �e�̕����APC�̎p�� [4]�����蔻�胂�f���̌���
	*/
	int Qid[10];//�N�I���^�[�j�I���̎���ID���i�[���܂�
	
	/*
	//
	//�e�f�[�^�ɂ͂��ꂼ��̌ŗL�f�[�^��ێ����Ă܂�
	//
	// ��Ԗڂ̗v�f�ɂ͕���̎�ނɖ�f�[�^���i�[����Ă��܂� [0]���C���E�F�|�� [1]�T�u�E�F�|�� [2]�O���l�[�h
	//
	// �擪[0]�Ԃɂ̓��f���f�[�^���i�[����Ă��܂� [0]���f����hsid [1]����̃X�v���C�g�摜 [2]����̓����胂�f����hsid [3]�g�p�ςݒe���hsid
	//
	// �擪[1]�Ԃɂ͏e�ɂ��Ă̏�񂪊i�[����Ă��܂� [0]����̎�� [1]����̃i���o�[ [2]�e��̍ő�l
	//												   [3]�}�K�W���̍ő�l [4]�˒��\�� [5]�З�
	//
	// �擪[2]�Ԃɂ̓{�[���f�[�^���i�[����Ă��܂� [0]�e����O [1]�e���� [2]��e�� [3]�e�e�ۃX�g�b�N [4]�����蔻�胂�f����Ԑ�
	//												[5]�����蔻�胂�f����Ԏ�O
	//
	// �擪[3]�Ԃɂ͒e�򓙂̃Q�[�����̏�񂪊i�[����Ă��܂� [0]���݂̒e�� [1]�}�K�W����
	*/

	int wp_data[3][4][6];//����̏��z��


	//�A�C�e���f�[�^
	int BringWp;//�X�e�[�W�ŏE��������
	int Ammo[4];//�莝���̒e��f�[�^���i�[
	int Recovery[5][2];//�莝���̉񕜃A�C�e���f�[�^�̊i�[
	int Key[10];//�莝���̉񕜃A�C�e���f�[�^�̊i�[
	int Equipment[3];//�莝���̑����A�C�e���f�[�^�̊i�[

	//�v���C���[�L�����N�^�[�̏�ԕϐ�
	int Wp_equipment;//�������Ă��镐��̎��
	int Attitude;//�����̎p����Ԃ�����ϐ�
	int MyState;//�����̓����Ԃ�����ϐ�
	int AirOnPC;//�������󒆂ɂ��邩�w�肷��ϐ�

	/*����*//*
	Atitude�ϐ�
	0:����  1:���Ⴊ��
	//
	MyState�ϐ�
	0:�ʏ���	1:�L�b�N���  2:�_�b�V�����
	//
	AirOnPC�ϐ�
	0:�n��  1:��
	*/


	//�v���C���[�̏��ϐ�
	double Acceleration;//�n�ʂւ̉����x��������ϐ�
	double MoveSpeed;//���ʉ����x������ϐ�

	//���[�V��������Ԃ������ϐ��̎w��
	int UpMotion;//�㔼�g�̃��[�V�����̎w��
	int UnderMotion;//�����g�̃��[�V�����̎w��

	//�v���C���[�L�����N�^�[�̌����̕ϐ�
	float PC_Deg_XZ;
	float PC_Deg_Y;
	
	//�֐��̐錾
	PlayerChara(int selchara, int Wp_equipment);//�R���X�g���N�^
	~PlayerChara();//�f�X�g���N�^

	int GunLoad( int selwp_kind, int gunkind, int gunno);//��������[�h���邽�߂̊֐�

	//��{�I�ȏe�̂܂Ƃߊ֐��̐錾
	int ThirdGunSys( Stage *Stg, Batch_Preparat *BatPre);//3�l�̎��_����̏e�֘A�܂Ƃߊ֐�
	int ShoulderGunSys( Stage *Stg, Batch_Preparat *BatPre, Enemy *Ene, Camera *Cam);//���˂����_����̏e�֘A�܂Ƃߊ֐�
	int GunPutOnHand();//���ݎ����Ă�e�������߂̃��[�V�����E�V�X�e�����Ǌ�����֐�
	int MoveChara();//�L�����𓮂����܂��A�O�㍶�E�ɓ����܂�
	int MovePosOnGround( Stage *Stg);//�L�����N�^�[���O���E���h�̏�ɒu�����߂̊֐�
	int ShoulderGunSysBefore();//�L�����N�^�[�̂̂��������s���֐�
	int GunConflictTarget( POINT ScreenPos, Stage *Stg, Enemy *Ene);//�����̌����ׂ������𒲐߂�����A�ˌ������肷��֐�
	int NormallyPCSystem( Stage *Stg, Batch_Preparat *BatPre, Enemy *Ene, Camera *Cam);//���ʂ̃Q�[�����ł̏������s�Ȃ��֐�
};
