#pragma once
/*����N���X�̃L����������w�b�_�t�@�C���B
//
*/

//�v���g�^�C�v�錾
class Enemy;
class PlayerChara;

/*����N���X�Ɋւ��邱�Ƃ��L�q*/
class Weapon{

private:

	/*�ϐ��̐錾*/

	/*����*/
	// �ŏ��̗v�f�ɂ͕���̎�ނɂ��ꍇ����������Ă��܂�  [0]���C���E�F�|�� [1]�T�u�E�F�|�� [2]�O���l�[�h
	int WeaponModel[3];// ���탂�f��
	int WeaponSprite[3];// ����̃X�v���C�g�摜 

	// �擪�v�f�͓���  WeaponData�ϐ��ɂ͈ȉ��̂悤�Ƀf�[�^�������Ă܂�
	// [0]����̎�� [1]����̃i���o�[ [2]�e��̍ő�l
	// [3]�}�K�W���̍ő�l [4]�˒��\�� [5]�З� [6]�����Ă�܂ł̎���
	// [7]�A�ː��̂��镐�킩 
	int WeaponData[3][8];

	// �Q�[�����̕���������܂�	
	// [0]�e�򐔁@[1]�}�K�W����
	int WeaponDataWhileGame[3][6];

	// �{�[�������i�[���܂�
	// [0]�e����O [1]�e���� [2]��e�� [3]�e�e�ۃX�g�b�N [4]�����蔻�胂�f����Ԑ� [5]�����蔻�胂�f����Ԏ�O
	int WeaponBone[3][6];
	int WeaponOtherModel[3][4];

	// ����̃G�t�F�N�g���i�[���܂� [0]�}�Y���t���b�V��
	int WeaponEffect[3][2];

	// ����̃}�Y���t���b�V�����C�g��ݒ�
	int WeaponMuzzleLight[3];

	// �����f�[�^���i�[���܂�
	int WeaponSoundEfeect[3][6];

	// ����̘A�˃J�E���^
	int WeaponRapidFire;

	// ����������Ă��邩�̃t���O
	int WeaponFireFlag;

	/*�֐��̐錾*/
	int GunLoad_Assault( int Selectkind, int Wpno);//�A�T���g���C�t���̏������[�h����֐�
	int GunLoad_Hand( int Selectkind, int Wpno);//�n���h�K���̏������[�h����֐�
	int GunLoad_Data( int Selectkind, int Wpkind, int Wpno);//����Ɋւ�������i�[����֐�

public:

	/*�֐��̐錾*/
	int GunLoad( int Selectkind, int Wpkind, int Wpno);//��������[�h���邽�߂̊֐�
	int GetWeaponModelID( int ItemNumber, int DataNumber);//���f��ID�̎擾���s���֐�
	int GetWeaponData( int ItemNumber, int DataNumber);//���f���̏ڍ׃f�[�^���擾���܂�
	int GetWeaponDataWhileGame( int ItemNumber, int DataNumber);//�Q�[�����̕���̏ڍ׃f�[�^���擾���܂�
	int GetSpriteData( int ItemNumber);//����X�v���C�g���擾���܂�
	int GetWeaponRapidFire();//����̘A�˃J�E���^���擾���܂�
	int SetInitWeaponData();//����̏�Ԃ����������A�e�e��}�K�W������t�ɂ���֐�
	int TreatmentWhileGame( int Wp_equipment);// �Q�[�����̏e�̑���Ɋւ��邱�Ƃ�����֐�
	int PlayWeaponSound( int Wp_equipment, int PlayNo, float MuzzlePosArray[3]);// *����̉������Đ�����֐�(3DSE��p)
	int ChkWeaponLaunch( int Wp_equipment);//����𔭎˂������ǂ����̊m�F���s���܂�
	int GetWeaponFireFlag();//���픭�˃t���O�ϐ����擾����֐�
	int AttackEnemy( Enemy *Ene, PlayerChara *PC, int ScreenPosArray[2]);//�Q�[�����̓G�Ƃ̂�����&�U��������s���܂�
	Weapon();//�R���X�g���N�^�A�ϐ��̏��������s���܂�
	~Weapon();//�f�X�g���N�^�A���f���̔j�������s���܂�




};