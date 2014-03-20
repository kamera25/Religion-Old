/* ///////////////////////////////////////////////////////// */
// �����ł́A����Ɋւ��邱�Ƃ��L�q����N���X�R�[�h�t�@�C���ł�
// ��ɁA�e����֌W�̂��Ƃ�������Ă��܂�
/* /////////////////////////////////////////////////////////  */
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "cWeapon_Gun.h"//�e�Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��
#include "cenemy.h"//�G�N���X�̐錾�w�b�_�t�@�C��
#include "cWeapon_Support.h"//�T�|�[�g����Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��
#include "cstage.h"//�X�e�[�W�֌W�̃N���X�w�b�_�t�@�C��
#include "clive.h"//�G��L�����̐錾�w�b�_�t�@�C��

// �e����N���X�̃R���X�g���N�^(���[�h���s���܂�) //
Weapon_Gun::Weapon_Gun( const int Selectkind, const int Wpkind, const int Wpno){

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

	/* ���[�h����������ɂ���đI�𕪊� */
	switch( Wpkind ){
			case 0:{
					GunLoad_Hand( Wpno);//�n���h�K���n
					break;
			}
			case 1:{
					GunLoad_SMG( Wpno);//�T�u�}�V���K���n
					break;
		   }
			case 2:{
					GunLoad_Shot( Wpno);//�V���b�g�K���n
					break;
			}
			case 3:{
					GunLoad_Assault( Wpno);//�A�T���g���C�t���n
					break;
			}
			case 4:{
					GunLoad_Machine( Wpno);//�}�V���K���n
					break;
			}
			case 5:{
					GunLoad_Rifle( Wpno);//���C�t���n
					break;
			}
			case 6:{
					GunLoad_Grenade( Wpno);//�O���l�[�h�n
			}
	}

	
	/* �G�t�F�N�g�r���{�[�h�����[�h���܂� */
	wsprintf( loadname, "%s\\data\\img\\effect\\explosion1.png", System::path);
	ech = E3DCreateBillboard ( loadname, 96, 96, 0, 1, 1, &EffectNo);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/* �G�t�F�N�g��\�ߓ��߂��Ă��� */
	ech = E3DSetBillboardAlpha( EffectNo, 0.0f);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/* �G�t�F�N�gID�������o�ϐ��ɑ�� */
	Set_Effects( EffectNo);

	/*����f�[�^�̃��[�h������*/
	GunLoad_Data( Wpkind, Wpno);

	return;
}

//  �e����N���X�̃f�X�g���N�^(�A�����[�h���s���܂�) //
Weapon_Gun::~Weapon_Gun(){




	return;
}

/* �Q�[�����̏e�̑���Ɋւ��邱�Ƃ����܂� */
int Weapon_Gun::WeaponTreatment( const int WeaponLight){

	/* �ϐ��̐錾&������ */
	int ech = 0;// �G���[�`�F�b�N�ϐ�
	float MuzzleFlashAlpha = 0.0f;//�}�Y���t���b�V���X�v���C�g�̓����x
	float MuzzlePosArray[3] = {0};// �e�������Ă���e�����W������ϐ�
	D3DXVECTOR3 MuzzlePos( 0.0, 0.0, 0.0);// �e���ʒu
	E3DCOLOR4UC MuzzleFlashColor = { 0, 0, 0, 0};// �}�Y���t���b�V���̐F���w��

	int Ammo = Get_Ammo();
	int Model = Get_Model();

	/* �����܂� */



	/* ��������A�{�i�I�ȏ������s���܂� */
	

	/* �e���̈ʒu�̍��W���擾���܂� */
	ech = E3DGetCurrentBonePos( Model, Get_Bones(0), 1, &MuzzlePos);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/* �e���̈ʒu�ɔ����G�t�F�N�g��u���܂� */
	ech = E3DSetBillboardPos(  Get_Effects(), MuzzlePos); 
	_ASSERT( ech != 1 );//�G���[�`�F�b�N


	/* �ǂ��e�𔭎˂��������ŕ��� */
	switch( Get_NowFireFlag() ){
			case 1:{// ���ʂ̏�ԂŔ���

					/*�r���{�[�h����]�����܂�*/
					ech = E3DRotateBillboard( Get_Effects(), float( rand() % 360), 1);
					_ASSERT( ech != 1 );//�G���[�`�F�b�N

					/* �ʒu���� */
					MuzzlePosArray[0] = MuzzlePos.x;
					MuzzlePosArray[1] = MuzzlePos.y;
					MuzzlePosArray[2] = MuzzlePos.z;
					/* SE�̍Đ� */
					PlayWeaponSound( 0, MuzzlePosArray);

					
					/* �}�Y���t���b�V���J�E���^�[��\�������܂� */
					Set_FlashCounter(4);

					/*�A�˃J�E���^�Ɉ�萔�l�������ˌ�������~�����܂�*/
					Set_WaitingTime( RapidTime);

					Set_NowFireFlag(3);
					
					break;
		   }
		   case 2:{// ��̏�ԂŔ���

			   		//�ʒu����
					MuzzlePosArray[0] = MuzzlePos.x;
					MuzzlePosArray[1] = MuzzlePos.y;
					MuzzlePosArray[2] = MuzzlePos.z;
					//�T�E���h�̍Đ�
					PlayWeaponSound( 1, MuzzlePosArray);

					/*�A�˃J�E���^�Ɉ�萔�l�������ˌ�������~�����܂�*/
					Set_WaitingTime( RapidTime);
					Set_NowFireFlag(3);					

					break;
		  }
	}

	/* �}�Y���t���b�V���J�E���^�[���I���Ȃ� */
	if( 0 < Get_FlashCounter()){

			/* �ŏ��ɓ_���������Ԃ���A���񂾂�ƌ��������Ă����悤�ɂ��܂� */
			switch( Get_FlashCounter() ){
					case 4:{
							MuzzleFlashAlpha = 0.7f;
							MuzzleFlashColor.r = 200;
							MuzzleFlashColor.g = 200;
							MuzzleFlashColor.b = 200;
							break;
				    }
					case 3:{
							MuzzleFlashAlpha = 0.9f;
							MuzzleFlashColor.r = 240;
							MuzzleFlashColor.g = 240;
							MuzzleFlashColor.b = 240;
							break;
					}
					case 2:{
							MuzzleFlashAlpha = 0.6f;
							MuzzleFlashColor.r = 160;
							MuzzleFlashColor.g = 160;
							MuzzleFlashColor.b = 160;
							break;
					}
					case 1:{
							MuzzleFlashAlpha = 0.2f;
							MuzzleFlashColor.r = 50;
							MuzzleFlashColor.g = 50;
							MuzzleFlashColor.b = 50;
					}
					case 0:{// ���C�g�������܂�
							MuzzleFlashAlpha = 0.0f;
							MuzzleFlashColor.r = 0;
							MuzzleFlashColor.g = 0;
							MuzzleFlashColor.b = 0;
					}
			}


			/* �����x��ύX���� */
			ech = E3DSetBillboardAlpha( Get_Effects(), MuzzleFlashAlpha);
			_ASSERT( ech != 1 );//�G���[�`�F�b�N

			/* ���C�g��t���� */
			ech = E3DSetPointLight( WeaponLight, MuzzlePos, 700.0f, MuzzleFlashColor);
			_ASSERT( ech != 1 );//�G���[�`�F�b�N
			

			/*�t���b�V���J�E���g���ЂƂ�����*/
			Set_FlashCounter( Get_FlashCounter() - 1);

	}


	/* �A�˃J�E���^��0�ȏ�(�ł̂��s�\)�Ȃ� */
	if( 0 < Get_WaitingTime()){
			Set_WaitingTime( Get_WaitingTime() - 1);// �A�˃J�E���^����J�艺����
			if( Get_WaitingTime() == 0){
					Set_NowFireFlag(0);
			}
	}


	return 0;
}

/* ����̏�Ԃ������ɂ���֐� */
int Weapon_Gun::InitWeapon(){

	/* ���ꂼ��̕����������Ԃɂ��� */
	NowMagazine = Magazine;
	Set_NowAmmo( Get_Ammo());


	return 0;
}

/*�Q�[�����̓G�Ƃ̂�����&�U��������s���܂��B*/
int Weapon_Gun::AttackEnemy( NPC_Head *NPC_H, PlayerChara *PC, int ScreenPosArray[2], Stage *Stg){

	/*�ϐ��̏���*/
	int ech = 0;//�G���[�m�F�ϐ�
	int EneHitResult = 0;//�G���Ə��ɓ����Ă��邩�̌��ʂ����܂�
	int GarbageInt = 0;//����Ȃ��f�[�^���i�[���܂�
	int NowWpKind = 0;//���̕���̎�ނ��擾���܂�
	bool EnemyConflict = false;//�G�ɓ����������̍��v
	float NowWpRange = 0.0f;//���̕���̎˒��������܂�
	float EneDistance = 0.0f;//���������G�̂Ƃ��납��̋������������܂�
	float EneNearDistance = 0.0f;//�������Ă����ԋ߂��G�̋������������܂�
	float Wall_HitDistance = 0.0f;//��ԋ߂��ǂ̋������������܂��B
	D3DXVECTOR3 GunTargetPos( 0.0, 0.0, 0.0);//�e�������ׂ����W
	D3DXVECTOR3 WantVec( 0.0, 0.0, 0.0);//�u������v�̌������������ւ̃x�N�g��
	D3DXVECTOR3 BaseVec( 0.0, 0.0, -1.0);//�����̏��������x�N�g��
	D3DXVECTOR3 GarbageD3DVec( 0.0, 0.0, 0.0);//�v��Ȃ�XYZ�̃f�[�^�̈ꎟ����
	POINT ScreenPos = { ScreenPosArray[0], ScreenPosArray[1]};//2D�X�N���[�����W�\����
	vector<NPC_t>::iterator it;// �C�e���[�^
	vector<NPC_t>::iterator NearEnemyID;//��ԋ߂��G�L�����̎��ʔԍ�

	/*�����蔻��v�����ȊO AND */
	if( ( Get_NowFireFlag() != 1) || ( NPC_H->Get_NPC_empty() == true)){
			return 0;
	}

	/*������������Ƃ��Ă����*/
	NowWpKind = Get_Kind();//����̎��
	NowWpRange = float( Get_Range() * 500);
	EneNearDistance = float(NowWpRange);
	


	/* ///////////////////////////////////////// */
	//�܂��A��ԓI�ɍU�����肳���邩�ǂ������߂܂�
	/* //////////////////////////////////////// */
	
	/* ����̎�ނɂ���ĕ���̏����𕪊򂳂��܂��B */
	switch(NowWpKind){
			case 0://�n���h�K���Ȃ�
			case 2:
			case 3:
			case 4:
			{
					/*�ʏ탂�[�h( ���f��[0]����擾���� )*/
					if( Stg->Stage_GunTarget == 0){//�ǃf�[�^���G����O�ɂ�����U���\�Ȃ̂ŁA�����ŃJ�[�\����̃X�e�[�W���擾���Ă��܂�
							ech = E3DPickFace( System::scid1, Stg->Stage_hsid[0], ScreenPos, NowWpRange, &GarbageInt, &GarbageInt, &GarbageD3DVec, &GarbageD3DVec, &Wall_HitDistance);
							_ASSERT( ech != 1 );//�G���[�`�F�b�N
					}

					/*�����蔻�蒆�ɂ���G���`�F�b�N���܂�*/
					for( it = NPC_H->Get_NPC_begin(); it != NPC_H->NPC_endit(); it++){//�G�l�~�[�̐�����

										ech = E3DPickFace( System::scid1, (*it).NPC_Mdl->Get_BodyModel(), ScreenPos, NowWpRange, &EneHitResult, 
															&EneHitResult, &GarbageD3DVec, &GarbageD3DVec, &EneDistance);
										_ASSERT( ech != 1 );//�G���[�`�F�b�N

										if( (EneHitResult != 0) && ( EneDistance < EneNearDistance) ){
													EneNearDistance = EneDistance;//��ԋ߂��G�̋����ɍX�V���܂�
													NearEnemyID = it;//��ԋ߂����f���ԍ������܂�
													EnemyConflict = true;//�߂��G�����邱�Ƃ������܂�
										}
					}

					/*�����A�����蔻���ɓG�������*/
					if( ( EnemyConflict == true) && ( EneNearDistance < Wall_HitDistance)){

							// !!�����ɕǂƂ̓����蔻�肪�K�v!!

							//�G�Ƀ_���[�W��^����

							(*NearEnemyID).NPC_Mdl->Set_HP( (*NearEnemyID).NPC_Mdl->Get_HP() - Get_Attack());
					}
			}
	}




	return 0;
}

/* ����(�����ł͏e)�𔭖C���Ă��悢���m�F���AOK�Ȃ甭�˃t���O�����Ă܂� */
int Weapon_Gun::ChkWeaponLaunch(){

	/* �ϐ��̏����� */



	/* ���ˉ\�Ȃ�t���O�𗧂Ă܂� */

	if( ( System::GetKeyData( System::KEY_LEFTMOUSE)) && ( Get_NowFireFlag() == 0)){//���N���b�N����A���ˉ\���I�t�Ȃ�
			if( 0 < Get_NowAmmo() ){//Ammo���c���Ă����
					Set_NowFireFlag(1);// ���ˏ�Ԃɂ���
					Set_NowAmmo( Get_NowAmmo() -1 );// �e����ЂƂ��炵�܂�
			}
			else{//�e�Ȃ��ŋ󌂂���ԂȂ�
					Set_NowFireFlag(2);//�󌂂���Ԃ���
			}
	}


	return 0;
}

/* ����̃����[�h���s���܂� */
int Weapon_Gun::ReloadWeapon(){

	
	/* �����[�h�̏������s���܂� */
	if( ( System::GetKeyData( System::KEY_R) == 1) && ( 0 < NowMagazine)){//R�L�[��������ĂāA�}�K�W��������̂Ȃ�

					if( ( Get_Ammo() <= Get_NowAmmo() ) && ( NowMagazine == Magazine)){// MAG��AMMO������g���ĂȂ����
							Set_NowAmmo( Get_Ammo() + 1);//AMMO�𖞃^��+1�ɂ���
							NowMagazine =  NowMagazine - 1;// �}�K�W�����g�p�����̂�-1����
					}
					else if( ( Get_Ammo() != Get_NowAmmo()) && ( Get_NowAmmo() != Get_Ammo() +1 )){//�ʏ�̃����[�h�ł����
							Set_NowAmmo( Get_Ammo());//AMMO�𖞃^���ɂ���
							NowMagazine =  NowMagazine - 1;// �}�K�W�����g�p�����̂�-1����
					}
	}

	return 0;
}