#pragma once
/*�L�����N�^�[�N���X�̃L����������w�b�_�t�@�C���B
//
*/

//�v���g�^�C�v�錾
class Stage;
class Batch_Preparat;
class Camera;
class Weapon;
class Enemy;


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
	0:�ʏ���	1:�L�b�N���  2:�_�b�V�����  3:��������я�ԁ@4:�E������я��
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


	//��{�I�ȏe�̂܂Ƃߊ֐��̐錾
	int ThirdGunSys( Stage *Stg, Batch_Preparat *BatPre);//3�l�̎��_����̏e�֘A�܂Ƃߊ֐�
	int ShoulderGunSys( Batch_Preparat *BatPre, int ScreenPos[2]);//���˂����_����̏e�֘A�܂Ƃߊ֐�
	int GunPutOnHand( Weapon *Wep);//���ݎ����Ă�e�������߂̃��[�V�����E�V�X�e�����Ǌ�����֐�
	int MoveChara();//�L�����𓮂����܂��A�O�㍶�E�ɓ����܂�
	int MovePosOnGround( Stage *Stg);//�L�����N�^�[���O���E���h�̏�ɒu�����߂̊֐�
	int ShoulderGunSysBefore( Weapon *Wep);//�L�����N�^�[�̂̂��������s���֐�
	int GunConflictTarget( int ScreenPosArray[2], Stage *Stg, Enemy *Ene, Weapon *Wep);//�����̌����ׂ������𒲐߂���֐�
	int NormallyPCSystem( Stage *Stg, Batch_Preparat *BatPre, Enemy *Ene, Camera *Cam, Weapon *Wep, int ScreenPos[2]);//���ʂ̃Q�[�����ł̏������s�Ȃ��֐�
	int GunSystem( Enemy *Ene);//�e�ɂ��č쓮������֐��A�����[�h�A���łĂ�܂ł̎��Ԍv�Z�A�G�ւ̂����蔻��A�_���[�W�v�Z�Ȃ�
};
