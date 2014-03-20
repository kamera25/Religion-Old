#pragma once
/*�@�����N���X�̐錾������w�b�_�t�@�C���B
//�@�����n�N���X�̃X�[�p�[�N���X�ł�
*/

class Weapon;
class Stage;

/* �����N���X�̐錾 */
class Creature{

private:

	int MaxHP;// �����̍ő�HP
	int HP;// ������HP
	int BodyModel;// �����̃��f��

public:

	/* ���z�֐��n�� */
	virtual ~Creature(){};//���z�R���X�g���N�^

	/* �q�N���X�ŏo�Ă��鉼�z�֐� */
	virtual int Set_UpMotion( int Number) = 0;
	virtual int Set_MyState( int Number) = 0;
	virtual int Set_UnderMotion( int Number) = 0;
	virtual int Batch_PeopleMotion() = 0;
	virtual int GunPutOnHand() = 0;
	virtual int MovePosOnGround( Stage *Stg) = 0;
	virtual Weapon* Get_Weapon() = 0;


	/* �A�V�X�g(�擾�E���)�֐��̐錾 */
	int Get_MaxHP() const;// MaxHP�ϐ��̎擾�֐�
	int Get_HP() const;// HP�ϐ��̎擾�֐�
	int Get_BodyModel() const;// BodyModel�ϐ��̎擾�֐� 
	int Set_MaxHP( int Number);// MaxHP�ϐ��̑���֐�
	int Set_HP( int Number);// HP�ϐ��̑���֐�
	int Set_BodyModel( int Number);// BodyModel�ϐ��̑���֐� 

};