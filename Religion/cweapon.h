#pragma once
/*����N���X�̃L����������w�b�_�t�@�C���B
//
*/

//�v���g�^�C�v�錾
class Enemy;
class PlayerChara;
class Stage;

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
	// [7]�A�ː��̂��镐�킩 [8] �g�p�e�� [9] ���x
	int WeaponData[3][10];

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
	int GunLoad_Assault( const int Selectkind, const int Wpno);//�A�T���g���C�t���̏������[�h����֐�
	int GunLoad_Machine( const int Selectkind, const int Wpno);//�}�V���K���̏������[�h����֐�
	int GunLoad_Hand( const int Selectkind, const int Wpno);//�n���h�K���̏������[�h����֐�
	int GunLoad_Shot( const int Selectkind, const int Wpno);// �V���b�g�K���̏������[�h����֐�
	int GunLoad_Rifle( const int Selectkind, const int Wpno);//���C�t���̏������[�h����֐�
	int GunLoad_Grenade( const int Selectkind, const int Wpno);//�O���l�[�h�̏������[�h����֐�
	int GunLoad_Data( const int Selectkind, const int Wpkind, const int Wpno);//����Ɋւ�������i�[����֐�



public:

	/*�֐��̐錾*/
	int GunLoad( const int Selectkind, const int Wpkind, const int Wpno);//��������[�h���邽�߂̊֐�
	int SetInitWeaponData();//����̏�Ԃ����������A�e�e��}�K�W������t�ɂ���֐�
	int TreatmentWhileGame( const int Wp_equipment);// �Q�[�����̏e�̑���Ɋւ��邱�Ƃ�����֐�
	int PlayWeaponSound( const int Wp_equipment, const int PlayNo, const float MuzzlePosArray[3]);// *����̉������Đ�����֐�(3DSE��p)
	int ChkWeaponLaunch( const int Wp_equipment);//����𔭎˂������ǂ����̊m�F���s���܂�

	int AttackEnemy( Enemy *Ene, PlayerChara *PC, int ScreenPosArray[2], Stage *Stg);//�Q�[�����̓G�Ƃ̂�����&�U��������s���܂�
	Weapon();//�R���X�g���N�^�A�ϐ��̏��������s���܂�
	~Weapon();//�f�X�g���N�^�A���f���̔j�������s���܂�


	/* �A�V�X�g�֐� */
	int GetWeaponModelID( const int ItemNumber, const int DataNumber) const;//���f��ID�̎擾���s���֐�
	int GetWeaponData( const int ItemNumber, const int DataNumber) const;//���f���̏ڍ׃f�[�^���擾���܂�
	int GetWeaponDataWhileGame( const int ItemNumber, const int DataNumber) const;//�Q�[�����̕���̏ڍ׃f�[�^���擾���܂�
	int GetSpriteData( const int ItemNumber) const;//����X�v���C�g���擾���܂�
	int GetWeaponRapidFire() const;//����̘A�˃J�E���^���擾���܂�
	int GetWeaponFireFlag() const;//���픭�˃t���O�ϐ����擾����֐�





};