#pragma once
/*�L�����N�^�[�N���X�̐錾������w�b�_�t�@�C���B
//
*/

#include "csoldier.h"// ���m�N���X�̐錾�w�b�_�t�@�C��

//�v���g�^�C�v�錾
class Stage;
class Batch_Preparat;
class Camera;
class Weapon;
class Enemy;


//�v���C���[�L�����N�^�[�N���X���쐬�A�������i���̑��L������People�N���X�ɂč쐬�\�j
class PlayerChara: public Soldier{

private:
	/* N/A */
public:
	
	//�֐��̐錾
	PlayerChara( int selchara, int Wpselect_equipment) : Soldier(  selchara, Wpselect_equipment){};//�R���X�g���N�^

	~PlayerChara();//�f�X�g���N�^


	//��{�I�ȏe�̂܂Ƃߊ֐��̐錾
	int ThirdGunSys( Stage *Stg, Batch_Preparat *BatPre);//3�l�̎��_����̏e�֘A�܂Ƃߊ֐�
	int ShoulderGunSys( Batch_Preparat *BatPre, int ScreenPos[2]);//���˂����_����̏e�֘A�܂Ƃߊ֐�
	int MoveChara();//�L�����𓮂����܂��A�O�㍶�E�ɓ����܂�
	int ShoulderGunSysBefore();//�L�����N�^�[�̂̂��������s���֐�
	int GunConflictTarget( int ScreenPosArray[2], Stage *Stg, Enemy *Ene);//�����̌����ׂ������𒲐߂���֐�
	int NormallyPCSystem( Stage *Stg, Batch_Preparat *BatPre, Enemy *Ene, Camera *Cam, int ScreenPos[2]);//���ʂ̃Q�[�����ł̏������s�Ȃ��֐�
	int ChangeWeapon( Batch_Preparat *BatPre);//�����ύX���邳����ۂɎg�p����֐�
	int GunSystem( Enemy *Ene);//�e�ɂ��č쓮������֐��A�����[�h�A���łĂ�܂ł̎��Ԍv�Z�A�G�ւ̂����蔻��A�_���[�W�v�Z�Ȃ�

};
