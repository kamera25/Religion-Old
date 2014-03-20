#pragma once
/*�L�����N�^�[�N���X�̐錾������w�b�_�t�@�C���B
//
*/

#include "csoldier.h"// ���m�N���X�̐錾�w�b�_�t�@�C��

//�v���g�^�C�v�錾
class Stage;
class Batch_Render;
class Camera;
class Weapon;
class NPC_Head;


//�v���C���[�L�����N�^�[�N���X���쐬�A�������i���̑��L������People�N���X�ɂč쐬�\�j
class PlayerChara: public Soldier{

private:
	/* �ϐ��̐錾 */
	int ChangePerspectiveMode;// ���_�ύX�̏�ԕϐ�


public:
	
	//�֐��̐錾
	PlayerChara( int selchara, int Wpselect_equipment);//�R���X�g���N�^

	~PlayerChara();//�f�X�g���N�^


	//��{�I�ȏe�̂܂Ƃߊ֐��̐錾
	int ThirdGunSys( Stage *Stg, Batch_Render *BatPre);//3�l�̎��_����̏e�֘A�܂Ƃߊ֐�
	int ShoulderGunSys( Batch_Render *BatPre, int ScreenPos[2]);//���˂����_����̏e�֘A�܂Ƃߊ֐�
	int ThreePersonGunSys( Batch_Render *BatPre, int ScreenPos[2]);// �O�l�̎��_����̏e�֘A�܂Ƃߊ֐�
	int MoveChara();//�L�����𓮂����܂��A�O�㍶�E�ɓ����܂�
	int ShoulderGunSysBefore();//�L�����N�^�[�̂̂��������s���֐�
	int GunConflictTarget( int ScreenPosArray[2], Stage *Stg, NPC_Head *NPC_H);//�����̌����ׂ������𒲐߂���֐�
	int NormallyPCSystem( Stage *Stg, Batch_Render *BatPre, NPC_Head *NPC_H, Camera *Cam, int ScreenPos[2]);//���ʂ̃Q�[�����ł̏������s�Ȃ��֐�
	int ChangeWeapon( Batch_Render *BatPre);//�����ύX���邳����ۂɎg�p����֐�
	int GunSystem( NPC_Head *NPC_H);//�e�ɂ��č쓮������֐��A�����[�h�A���łĂ�܂ł̎��Ԍv�Z�A�G�ւ̂����蔻��A�_���[�W�v�Z�Ȃ�
	int TurnBackDir(  int Qid, D3DXVECTOR3 WantDeg, int FixFlag);// ������]������
	int PCDashControl();// �_�b�V���֌W�̏������s���܂�
	int PCSideAvoidanceControl();// ������т̏����������܂��B
	float RegulateMoveSpeed( float Acceleration, float FixedMoveSpeed, float LimitSpeed);// �L�����N�^�̓����X�s�[�h��ݒ�A�������܂�
	int EventPublish();//�Q�[���I�[�o��N���A�Ȃǂ̃C�x���g�𔭍s���܂�
	int StatusReset();// �\���W���[�N���X�̏�Ԃ������ɖ߂��܂�(���X�^�[�g���ŗ��p)
	int JumpPosition( D3DXVECTOR3 CatPos, const double Degree, const double UpAcceleration, const double Speed);// ���W���w�肵�āA�W�����v��������
	int MoveModel( double WantDeg, double SumSpeed);
};
