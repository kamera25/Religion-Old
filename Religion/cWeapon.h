#pragma once
/* /////////////////////////////////////// */
// ����N���X�̃L����������w�b�_�t�@�C���B
/* /////////////////////////////////////// */
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��


//�v���g�^�C�v�錾
class Enemy;
class PlayerChara;
class Stage;

/* ����N���X(Gun/Support�̃X�[�p�[�N���X) */
class Weapon{

private:

	/* �ϐ��̐錾 */
	/* �f�[�^�� */
	int Model;//  ���탂�f��ID
	int Sprite;// �X�v���C�g�摜ID
	int Effects;//  ����̃G�t�F�N�g���i�[���܂�
	int Sounds[2];//  ����֘A�̉����f�[�^���i�[���܂�

	int Kind;//  ����̎��
	int Number;//�@����̎��ʔԍ�
	int Attack;//  ����̈З�
	int Ammo;//  ����̏e�e�� or �����\��

		
	// [0]�e����O [1]�e���� [2]��e�� [3]�e�e�ۃX�g�b�N [4]�����蔻�胂�f����Ԑ� [5]�����蔻�胂�f����Ԏ�O
	int Bones[6];// �{�[�������i�[���܂�

	/* �Q�[�����̕ϐ� */
	int NowAmmo;// �Q�[�����̏e�e�� or �����\��
	int NowFireFlag;//  �Q�[�����ŕ����ł��Ă��邩�̃t���O
	int FlashCounter;// ����̌����Ă��镔��(�r���{�[�h&���C�g)���J�E���g����ϐ�
	int WaitingTime;// �e���������Ƃ��̎����˂ł���܂ł̑ҋ@����

public:

	/* �Ó������o�ϐ� */	
	static const int PlayerSide = 0;// �v���C���[�L�����N�^��
	static const int EnemySide = 1;// �G�l�~�[�L�����N�^��


	/* �q�N���X�ŏo�Ă��鉼�z�֐� */
	//virtual int WpLoad( const int Selectkind, const int Wpkind, const int Wpno) = 0;//��������[�h���邽�߂̊֐�(���z)
	Weapon();
	virtual ~Weapon();// ���z�R���X�g���N�^

	int PlayWeaponSound( const int PlayNo, const float MuzzlePosArray[3]);// �v���Z�b�g���Ă��镐��֘A�������Đ����܂�
	virtual int ChkWeaponLaunch(){ _ASSERT( 0 );return -1;};// ����𔭖C�E�������Ă��悢���m�F���AOK�Ȃ甭�˃t���O�����Ă܂�
	virtual int AttackEnemy( Enemy *Ene, PlayerChara *PC, int ScreenPosArray[2], Stage *Stg){ _ASSERT( 0 );return -1;};// �Q�[�����̓G�Ƃ̂�����&�U��������s���܂��B
	virtual int InitWeapon(){ _ASSERT( 0 );return -1;};// ����̏�Ԃ������ɂ���
	virtual int ReloadWeapon(){ _ASSERT( 0 );return -1;}// ����̃����[�h���s���܂�
	virtual int WeaponTreatment( const int WeaponLight){ _ASSERT( 0 );return -1;};

	/* �A�V�X�g�֐� */
	int Set_Model( const int Number);
	int Get_Model() const;
	int Set_Sprite( const int Number);
	int Get_Sprite() const;
	int Set_Effects( const int Number);
	int Get_Effects() const;
	int Set_Sounds( const int Number, const int ArrayNum);
	int Get_Sounds( const int ArrayNum) const;
	int Set_Bones( const int Number, const int ArrayNum);
	int Get_Bones( const int ArrayNum) const;
	int Set_Kind( const int Number);
	int Get_Kind() const;
	int Set_Number( const int Numbers);
	int Get_Number() const;
	int Set_Attack( const int Number);
	int Get_Attack() const;
	int Set_Ammo( const int Number);
	int Get_Ammo() const;
	int Get_FlashCounter();
	int Set_FlashCounter( const int Number);
	int Get_NowAmmo();
	int Set_NowAmmo( const int Number);
	int Get_WaitingTime() const;
	int Set_WaitingTime( const int Number);
	int Get_NowFireFlag() const;
	int Set_NowFireFlag( int Number);

	/* ���z�֐� */
	virtual int Get_NowMagazine() const;
	virtual int Get_Magazine() const;
	virtual int Get_Range() const;
};


