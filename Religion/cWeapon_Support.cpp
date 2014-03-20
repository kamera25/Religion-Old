/* ///////////////////////////////////////////////////////// */
// �����ł́A����Ɋւ��邱�Ƃ��L�q����N���X�R�[�h�t�@�C���ł�
// ��ɁA�T�|�[�g����֌W�̂��Ƃ�������Ă��܂�
/* /////////////////////////////////////////////////////////  */
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "cWeapon_Support.h"//�T�|�[�g����Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��
#include "cstage.h"//�X�e�[�W�֌W�̃N���X�w�b�_�t�@�C��


// �T�|�[�g����N���X�̃R���X�g���N�^(���[�h���s���܂�) //
Weapon_Support::Weapon_Support( const int Wpno){

	/* �ϐ��̏����� */
	int ech = 0;
	int EffectNo = 0;
	char loadname[256] = "";


	/*���łɏe���擾���Ă���A���̏e�f�[�^�ɏ㏑������Ȃ�*/
	/*if( Get_Model() != -1){//�I�𒆂̃J�e�S���Ƀf�[�^������̂Ȃ�
				ech = E3DDestroyHandlerSet( Get_Model());
				_ASSERT( ech != 1 );//�G���[�`�F�b�N

				ech = E3DDestroySprite( Get_Sprite());//�X�v���C�g���폜���܂�
				_ASSERT( ech != 1 );//�G���[�`�F�b�N
	}*/

	/* �T�|�[�g��������[�h */
	WpLoad_Support( Wpno);

	
	/* �G�t�F�N�g�r���{�[�h�����[�h���܂� */
	wsprintf( loadname, "%s\\data\\img\\effect\\explosion1.png", System::path);
	ech = E3DCreateBillboard ( loadname, 96, 96, 0, 1, 1, &EffectNo);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/* �G�t�F�N�g��\�ߓ��߂��Ă��� */
	ech = E3DSetBillboardAlpha( EffectNo, 0.0f);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/* �G�t�F�N�gID�������o�ϐ��ɑ�� */
	Set_Effects( EffectNo);

	/* �T�|�[�g����f�[�^�̃��[�h������ */
	SupportLoad_Data( 7, Wpno);

	return;
}

// �T�|�[�g����N���X�̃f�X�g���N�^(�A�����[�h���s���܂�) //
Weapon_Support::~Weapon_Support(){




	return;
}

int Weapon_Support::SupportLoad_Data( int Wpkind, int Wpno){

		/* �ϐ��̐錾�E������ */

	// �萔��  "�A�ˉ\�E�s��"
	const int Enable_Rapid_Fire = 0;// �\
	const int Disable_Rapid_Fire = 1;// �s�\


	// �����܂�//

	const int GunData[4][3] = {

		//�i�ځF �З�, �˒�����, ���e��
		
		// �n���h�K��

			{ 350,  15, 5},// M26
			{ 280,  18, 5},// M67
			{  50,  60, 5},// M18
			{ 420,   3, 3},// C4
	};



	Set_Kind( Wpkind);
	Set_Number( Wpno);

	Set_Attack( GunData[Wpno][0]);
	Set_Range( GunData[Wpno][1]);
	Set_Ammo( GunData[Wpno][2]);


	return 0;
}

/* ����̏������������� */
int Weapon_Support::InitWeapon(){

	/* ���ꂼ��̕����������Ԃɂ��� */
	Set_NowAmmo( Get_Ammo());

	return 0;
}

/* �Q�[�����̓G�Ƃ̂�����&�U��������s���܂��B */
int Weapon_Support::AttackEnemy( NPC_Head *NPC_H, PlayerChara *PC, int ScreenPosArray[2], Stage *Stg){



	return 0;
}

/* �Q�[�����̕���̑���Ɋւ��邱�Ƃ����܂� */
int Weapon_Support::WeaponTreatment( const int WeaponLight, Stage *Stg){

	int ech = 0;// �G���[�`�F�b�N�ϐ�
	static float Acceleration = 0.0f;//�O���l�[�h�̗���������x
	//static int sw=0;
	static bool HitGranadeOnGround = false;// �O���l�[�h���n�ʂɂ���������
	int Garbage;
	int Revface;// ���ʂ��ǂ���
	int GroundResult = 0;//�n�ʂ̓����蔻��̌���
	D3DXVECTOR3 BefGranadePos( 0.0, 0.0, 0.0);
	D3DXVECTOR3 AftGranadePos( 0.0, 0.0, 0.0);//�O���l�[�h��u����
	D3DXVECTOR3 GranadePos( 0.0, 0.0, 0.0);
	D3DXVECTOR3 GroundOnPos( 0.0, 0.0, 0.0);//�n�ʂ̍��W
	D3DXVECTOR3 ReflectVec( 0.0, 0.0, 0.0);//���ˍ��W

	/* �O���l�[�h�݂̂̏����Ȃ̂ł��I�I */
	if( Get_NowFireFlag() == 0){// �O���l�[�h���\���Ă���Ƃ��Ȃ�
			Acceleration = 0.0f;
	}
	else if( Get_NowFireFlag() == 1){// �O���l�[�h�𓊂��Ă���Ƃ��Ȃ�
		

			/* �O���l�[�h�̋O�����v�Z���܂� */
			ech = E3DGetPos( Get_Model(), &BefGranadePos);
			_ASSERT( ech != 1 );//�G���[�`�F�b�N

			Acceleration = Acceleration - 7.0f;

			if( HitGranadeOnGround == false)
			{
				AftGranadePos = BefGranadePos;
				AftGranadePos.y = BefGranadePos.y + Acceleration;

			}

			ech = E3DSetPos( Get_Model(), AftGranadePos);
			_ASSERT( ech != 1 );//�G���[�`�F�b�N

		
			/* �n�ʂƂ̓����蔻������܂� */
			//ech = E3DChkConfGround( Get_Model(), Stg->Stage_hsid[0], 1, 100000, -1000, &GroundResult, &GroundOnPos, &ReflectVec);
			//_ASSERT( ech != 1 );//�G���[�`�F�b�N
			ech = E3DChkConfLineAndFace( BefGranadePos, AftGranadePos, Stg->Stage_hsid[0], 1, &GroundResult
										, &Garbage, &GroundOnPos, &ReflectVec, &Revface);


			/* �n�ʂ���قƂ�Ǘ���ĂȂ��A�\�ʂȂ� */
			//float HeightFromGround = GranadePos.y - GroundOnPos.y;
			if( GroundResult != -1 && Revface == 0){

					AftGranadePos.y = GroundOnPos.y;

					/* �����̉����x�������� */
					Acceleration = ReflectVec.y * abs(Acceleration) ;
			}



			//Acceleration = Acceleration + 7.0f;
			//if( 100.0f <= Acceleration) Acceleration = 100.0f;// ��C��R���l������

	}





	return 0;
}



/* ����𔭖C�E�������Ă��悢���m�F���AOK�Ȃ甭�˃t���O�����Ă܂� */
int Weapon_Support::ChkWeaponLaunch(){;

	/* �ϐ��̏����� */
	 ;//�L�[���z����쐬
	static int KeyContinuity = 0;


	/* ���ˉ\�Ȃ�t���O�𗧂Ă܂� */
	if( 10 <= KeyContinuity ){
				KeyContinuity = 10;
				if( ( System::GetKeyData( System::KEY_LEFTMOUSE) == 0) && ( Get_NowFireFlag() == 0)){//���N���b�N���b���ꂽ��
						Set_NowFireFlag(1);// ���ˏ�Ԃɂ���
						Set_NowAmmo( Get_NowAmmo() -1 );// �e����ЂƂ��炵�܂�
				}
	}

	/* �L�[�̃`�F�b�N���s���܂� */
	if( System::GetKeyData( System::KEY_LEFTMOUSE)){
			KeyContinuity = KeyContinuity + 1;
	}
	else{
			KeyContinuity = 0;
	}




	return 0;
}