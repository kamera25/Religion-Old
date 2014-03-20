#pragma once
/*�@�����N���X�̐錾������w�b�_�t�@�C���B
 *�@�����n�N���X�̃X�[�p�[�N���X�ł�
 */

#include "cWeapon_head.h"// ���퓝���Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��
#include "cActor.h"

class Weapon;
class Stage;

/* �����N���X�̐錾 */
class Creature {

private:


	int MaxHP;// �����̍ő�HP
	int HP;// ������HP
	int Stamina;// �����̃X�^�~�i
	int MaxStamina;//�����̍ő�X�^�~�i
	//int BodyModel;// �����̃��f��
	int SkillSlot;// �X�L���X���b�g�̍ő�l
	int Attack;// �����̍U����
	int Branch;// �����̑���
	int *Skill;// �X�L���̊i�[�|�C���^
	int EquipmentSkillSum;// �������X�L���̍��v
	

public:

	/* �N���X�Ó��ϐ� */
	static const int GUNSLINGER = 0;// �K���X�����K�[
	static const int REBELLION = 1;// ���x���I��
	static const int VAN_POUCH = 2;// �o���|�[�`
	static const int POUCH_40MM = 3;// 40mm�|�[�`
	static const int SUPPORTER = 4;// �T�|�[�^�[
	static const int BODYARMOR = 5;// �h�e�`���b�L
	static const int KEVLARVEST = 6;// �P�u���[�x�X�g
	static const int MAGPOUCH = 7;// �}�O�|�[�`
	static const int FRITZHELM = 8;// �t���b�c�w����
	static const int COMMANDO = 9;// �R�}���h�[
	static const int RUNNER = 10;// �����i�[
	static const int PITCHER = 11;// �s�b�`���[
	static const int CRISIS_MNG = 12;// ��@�Ǘ�
	static const int POUCH = 13;// �|�[�`
	static const int SILVER_BULLET = 14;//��̏e�e
	static const int CAMEL = 15;// �L������
	static const int SHOWTIME = 16;// �V���[�^�C��
	static const int SPRINTER = 17;// �X�v�����^�[
	static const int FORCES_RADIO = 18;// ��������
	static const int IRONWALL = 19;// �S��
	static const int FORTITUDESOUL = 20;// �s���̍�
	static const int BOMMER = 21;// ���e��

	static const int NumberSkill = 22;// ���ݑg�ݍ��܂�Ă�X�L����

	static const int DEFAULT = 0;
	static const int RIFLEMAN = 0;
	static const int GRANADER = 1;
	static const int GUNNER = 2;
	static const int SNIPER = 3;
	static const int MEDIC = 4;

	Actor *Act;// �A�N�^�[

	/* ���z�֐��n�� */
	virtual ~Creature(){};//���z�R���X�g���N�^

	/* �q�N���X�ŏo�Ă��鉼�z�֐� */
	virtual int Set_UpMotion( int Number) = 0;
	virtual int Set_MyState( int Number) = 0;
	virtual int Get_MyState() const = 0;
	virtual int Set_UnderMotion( int Number) = 0;
	virtual int Batch_PeopleMotion() = 0;
	virtual int GunPutOnHand() = 0;
	virtual int MovePosOnGround( Stage *Stg) = 0;
	virtual Weapon_Head* Get_WeaponH() = 0;
	virtual int StatusReset(){return 0;};// �\���W���[�N���X�̏�Ԃ������ɖ߂��܂�(���X�^�[�g���ŗ��p)

	/* ���C�t��X�^�~�i�Ȃǂ̑�����������֐� */
	int Set_StateFromBranch( const int Branch);

	/* �X�L���n�̔\�͂�ǉ�����֐� */
	int Add_Skill( const int PlanSkill);
	
	/* �X�L���n�̔\�͂��폜����֐� */
	int Delete_Skill( const int PlanSkill);

	/* �A�V�X�g(�擾�E���)�֐��̐錾 */
	int Get_MaxHP() const;// MaxHP�ϐ��̎擾�֐�
	int Get_HP() const;// HP�ϐ��̎擾�֐�
	//int Get_BodyModel() const;// BodyModel�ϐ��̎擾�֐� 
	int Set_MaxHP( int Number);// MaxHP�ϐ��̑���֐�
	int Set_HP( int Number);// HP�ϐ��̑���֐�
	//int Set_BodyModel( int Number);// BodyModel�ϐ��̑���֐� 
	int Get_Stamina() const;// Stamina�̎擾�֐�
	int Set_Stamina( int Number);// Stamina�̑���֐�
	int Get_MaxStamina() const;// MaxStamina�̎擾�֐�
	int Set_MaxStamina( int Number);// MaxStamina�̑���֐�
	int Get_Attack() const;// Attack�̎擾�֐�
	int Set_Attack( int Number);// Attack�̑���֐�
	int Get_SkillSlot() const;// SkillSlot�̎擾�֐�
	int Set_SkillSlot( int Number);// SkillSlot�̑���֐�
	int Get_Branch() const;// Branch�̎擾�֐�
	int Set_Branch( int Number);// Branch�̑���֐�
	int	Delete_Skill();// Skill�̃|�C���^�[�̍폜�֐�
	int Set_Skill( int *Pointer );// Skill�̃|�C���^�[���w���Ă���e���w�肵�܂�
	int Set_EquipmentSkillSum( int Number );// EquipmentSkillSum�̑���֐�

};