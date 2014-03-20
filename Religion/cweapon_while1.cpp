/*�����ł́A����Ɋւ��邱�Ƃ��L�q����N���X�R�[�h�t�@�C���ł�
//
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "cweapon.h"//����Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��

#include "cenemy.h"//�G�N���X�̐錾�w�b�_�t�@�C��
#include "cstage.h"//�X�e�[�W�֌W�̃N���X�w�b�_�t�@�C��
#include "clive.h"//�G��L�����̐錾�w�b�_�t�@�C��


/*����̉������Đ����܂�(3DSE��p)*/
int Weapon::PlayWeaponSound( const int Wp_equipment, const int PlayNo, const float MuzzlePosArray[3]){

	/*�ϐ��̏�����*/
	int ech = 0;//�G���[�m�F�ϐ�
	D3DXVECTOR3 MuzzleFlashSound( 340.0, 340.0, 340.0);//�}�Y���t���b�V���T�E���h�̑��xXYZ
	D3DXVECTOR3 MuzzlePos( MuzzlePosArray[0], MuzzlePosArray[1], MuzzlePosArray[2]);//�}�Y���t���b�V���T�E���h�̑��xXYZ


	/*���̈ʒu�Ƒ������w�肵�܂�*/
	ech = E3DSet3DSoundMovement( WeaponSoundEfeect[Wp_equipment][PlayNo], MuzzlePos, MuzzleFlashSound);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	/*���ˉ���炵�܂�*/
	ech = E3DPlaySound( WeaponSoundEfeect[Wp_equipment][PlayNo], 0, 0, 0);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N


	return 0;
}


// �Q�[�����̏e�̑���Ɋւ��邱�Ƃ����܂�
int Weapon::TreatmentWhileGame( const int Wp_equipment){

	/*�ϐ��̏�����*/
	int ech = 0;
	int keyin[20] = {0};
	float LightDistance = 0.0f;//�����͂�����
	float MuzzleFlashAlpha = 0.0f;//�}�Y���t���b�V���̓����x
	float MuzzlePosArray[3];//�}�Y���t���b�V����\����������W�z�� 
	static int MuzzleFlashConter = 0;//�}�Y���t���b�V���J�E���^�[
	D3DXVECTOR3 MuzzlePos( 0.0, 0.0, 0.0);//�e���ʒu	
	E3DCOLOR4UC MuzzleFlashColor = { 0, 0, 0, 0};//�}�Y���t���b�V���̐F���w��

	/*�L�[���擾����*/
	System::GetKeyData(keyin);



	if( Wp_equipment != -1){//���킪�����

			/*�ϐ��̏�����*/
			const int NowAmmo = WeaponDataWhileGame[Wp_equipment][0]; //���݂̒e��
			const int NowMag = WeaponDataWhileGame[Wp_equipment][1]; //���݂̃}�K�W����
			const int WeaponAmmo = WeaponData[Wp_equipment][2]; //���퐫�\��̒e��



			/*����ɐV�������[�V�����𓖂Ă�*/
			ech = E3DSetNewPoseML( WeaponModel[Wp_equipment]);
			_ASSERT( ech != 1 );//�G���[�`�F�b�N


			if( WeaponBone[Wp_equipment][0] != 0){
				/*�e�̒u���{�[���̍��W�����߂܂�*/
				ech = E3DGetCurrentBonePos( WeaponModel[Wp_equipment], WeaponBone[Wp_equipment][0], 1, &MuzzlePos);
				_ASSERT( ech != 1 );//�G���[�`�F�b�N
			}

			/*�d���̈ʒu�ɔ����G�t�F�N�g��u���܂�*/
			ech = E3DSetBillboardPos( WeaponEffect[Wp_equipment][0], MuzzlePos); 
			_ASSERT( ech != 1 );//�G���[�`�F�b�N

			if( WeaponFireFlag == 1){

						/*�r���{�[�h����]�����܂�*/
						ech = E3DRotateBillboard( WeaponEffect[Wp_equipment][0], float( rand() % 360), 1);
						_ASSERT( ech != 1 );//�G���[�`�F�b�N

						//�ʒu����
						MuzzlePosArray[0] = MuzzlePos.x;
						MuzzlePosArray[1] = MuzzlePos.y;
						MuzzlePosArray[2] = MuzzlePos.z;
						//�T�E���h�̍Đ�
						PlayWeaponSound( Wp_equipment, 0, MuzzlePosArray);

						/*�ϐ�����*/

						// �}�Y���t���b�V���J�E���^�[��\�������܂�
						MuzzleFlashConter = 4;
						//�e����ЂƂ��炵�܂�
						WeaponDataWhileGame[Wp_equipment][0] = WeaponDataWhileGame[Wp_equipment][0] - 1;
						/*�A�˃J�E���^�Ɉ�萔�l�������ˌ�������~�����܂�*/
						WeaponRapidFire = WeaponData[Wp_equipment][6];

			}
			if( WeaponFireFlag == 2){//�e�Ȃ��ŋ󌂂���ԂȂ�

						//�ʒu����
						MuzzlePosArray[0] = MuzzlePos.x;
						MuzzlePosArray[1] = MuzzlePos.y;
						MuzzlePosArray[2] = MuzzlePos.z;
						//�T�E���h�̍Đ�
						PlayWeaponSound( Wp_equipment, 1, MuzzlePosArray);

						/*�ϐ�����*/

						/*�A�˃J�E���^�Ɉ�萔�l�������ˌ�������~�����܂�*/
						WeaponRapidFire = WeaponData[Wp_equipment][6];
			}


			if( ( keyin[4] == 1) && ( 0 < NowMag) && //R�L�[��������Ă� //�����[�h�ł�����(Mag������AAMMO�����^���łȂ����e���g�p)�Ń����[�h����Ȃ�
				/**/ ( ( NowAmmo < WeaponAmmo) || ( NowMag == WeaponData[Wp_equipment][3]))){ 

					if( ( WeaponData[Wp_equipment][0] != 3) && ( WeaponData[Wp_equipment][0] != 7) && //�O���l�[�h�łȂ��A�V���b�g�K���ł��Ȃ����
					/**/( NowAmmo >= WeaponAmmo) && ( NowMag == WeaponData[Wp_equipment][3])){// MAG��AMMO������g���ĂȂ����

							WeaponDataWhileGame[Wp_equipment][0] = WeaponAmmo + 1;//AMMO�𖞃^��+1�ɂ���
					}
					else{//�ʏ�̃����[�h�ł����

							WeaponDataWhileGame[Wp_equipment][0] = WeaponAmmo;//AMMO�𖞃^���ɂ���
					}
					//
					WeaponDataWhileGame[Wp_equipment][1] -= 1;//MAG���ЂƂ��炷
			}	


			/*�}�Y���t���b�V���J�E���^�[���I���Ȃ�*/
			if( 0 < MuzzleFlashConter){

				if( MuzzleFlashConter == 4){
							MuzzleFlashAlpha = 0.7f;
							MuzzleFlashColor.r = 200;
							MuzzleFlashColor.g = 200;
							MuzzleFlashColor.b = 200;
				}
				if( MuzzleFlashConter == 3){
							MuzzleFlashAlpha = 0.9f;
							MuzzleFlashColor.r = 240;
							MuzzleFlashColor.g = 240;
							MuzzleFlashColor.b = 240;
				}
				if( MuzzleFlashConter == 2){
							MuzzleFlashAlpha = 0.6f;
							MuzzleFlashColor.r = 160;
							MuzzleFlashColor.g = 160;
							MuzzleFlashColor.b = 160;
				}
				if( MuzzleFlashConter == 1){
							/*���C�g�𖳌��ɂ���*/
							MuzzleFlashAlpha = 0.2f;
							MuzzleFlashColor.r = 0;
							MuzzleFlashColor.g = 0;
							MuzzleFlashColor.b = 0;
				}

				/*�����x��ύX����*/
				ech = E3DSetBillboardAlpha( WeaponEffect[Wp_equipment][0], MuzzleFlashAlpha);
				_ASSERT( ech != 1 );//�G���[�`�F�b�N
				/*���C�g��t����*/
				if( MuzzleFlashConter != 1){
							ech = E3DSetPointLight( WeaponMuzzleLight[Wp_equipment], MuzzlePos, 700.0f, MuzzleFlashColor);
							_ASSERT( ech != 1 );//�G���[�`�F�b�N
				}
				else{//���C�g�����̂����Ԃł�
							ech = E3DSetPointLight( WeaponMuzzleLight[Wp_equipment], MuzzlePos, 0.0f, MuzzleFlashColor);
							_ASSERT( ech != 1 );//�G���[�`�F�b�N			
				}


				/*�����̃G�t�F�N�g��(���ׂẴr���{�[�h)�̕`��*/
				ech = E3DRenderBillboard( System::scid1, 0);
				_ASSERT( ech != 1 );//�G���[�`�F�b�N

				/*�t���b�V���J�E���g���ЂƂ�����*/
				MuzzleFlashConter = MuzzleFlashConter -1;

				/*�����x��ύX����*/
				if( MuzzleFlashConter == 0){//�J�E���g��0�ɂȂ�����
							ech = E3DSetBillboardAlpha( WeaponEffect[Wp_equipment][0], 0.0f);
							_ASSERT( ech != 1 );//�G���[�`�F�b�N	
				}
			}

			/*�A�˒�~�J�E���^���I���Ȃ�*/
			if( 0 < WeaponRapidFire){
					WeaponRapidFire = WeaponRapidFire - 1;//�A�˒�~�J�E���^����J�艺����
			}
	}

	return 0;
}
/*�Q�[�����̓G�Ƃ̂�����&�U��������s���܂��B*/
int Weapon::AttackEnemy( Enemy *Ene, PlayerChara *PC, int ScreenPosArray[2], Stage *Stg){

	/*�ϐ��̏���*/
	int ech = 0;//�G���[�m�F�ϐ�

	int NowWpKind = 0;//���̕���̎�ނ��擾���܂�
	int NearEnemyID = 0;//��ԋ߂��G�L�����̎��ʔԍ�
	int EnemyConflict = 0;//�G�ɓ����������̍��v
	int EneHitResult = 0;//�G���Ə��ɓ����Ă��邩�̌��ʂ����܂�
	int GarbageInt = 0;//����Ȃ��f�[�^���i�[���܂�
	float NowWpRange = 0.0f;//���̕���̎˒��������܂�
	float EneDistance = 0.0f;//���������G�̂Ƃ��납��̋������������܂�
	float EneNearDistance = 0.0f;//�������Ă����ԋ߂��G�̋������������܂�
	float Wall_HitDistance = 0.0f;//��ԋ߂��ǂ̋������������܂��B
	D3DXVECTOR3 GunTargetPos( 0.0, 0.0, 0.0);//�e�������ׂ����W
	D3DXVECTOR3 WantVec( 0.0, 0.0, 0.0);//�u������v�̌������������ւ̃x�N�g��
	D3DXVECTOR3 BaseVec( 0.0, 0.0, -1.0);//�����̏��������x�N�g��
	D3DXVECTOR3 GarbageD3DVec( 0.0, 0.0, 0.0);//�v��Ȃ�XYZ�̃f�[�^�̈ꎟ����
	POINT ScreenPos = { ScreenPosArray[0], ScreenPosArray[1]};//2D�X�N���[�����W�\����


	/*������������Ƃ��Ă����*/
	if( PC->Get_Wp_equipment() != -1){

			NowWpKind = GetWeaponData( PC->Get_Wp_equipment(), 0);//����̎��
			NowWpRange = float( GetWeaponData( PC->Get_Wp_equipment(), 4) * 500);//
			EneNearDistance = float(NowWpRange);
	}


	/**/
	//�܂��A��ԓI�ɍU�����肳���邩�ǂ������߂܂�
	/**/

	/*���ˏ�ԂŁA�G������Ȃ�*/
	if( ( GetWeaponFireFlag() == 1) && ( 0 < Ene->EnemyNum)){

			//�n���h�K���Ȃ�
			if( ( NowWpKind == 1) || ( NowWpKind == 4) || ( NowWpKind == 5)){

					/*�ʏ탂�[�h( ���f��[0]����擾���� )*/
					if( Stg->Stage_GunTarget == 0){//�ǃf�[�^���G����O�ɂ�����U���\�Ȃ̂ŁA�����ŃJ�[�\����̃X�e�[�W���擾���Ă��܂�
							ech = E3DPickFace( System::scid1, Stg->Stage_hsid[0], ScreenPos, NowWpRange, &GarbageInt, &GarbageInt, &GarbageD3DVec, &GarbageD3DVec, &Wall_HitDistance);
							_ASSERT( ech != 1 );//�G���[�`�F�b�N
					}

					/*�����蔻�蒆�ɂ���G���`�F�b�N���܂�*/
					for( int i=0; i < Ene->EnemyNum; i++){//�G�l�~�[�̐�����

										ech = E3DPickFace( System::scid1, Ene->Ene[i]->Get_BodyModel(), ScreenPos, NowWpRange, &EneHitResult, &EneHitResult, &GarbageD3DVec, &GarbageD3DVec, &EneDistance);
										_ASSERT( ech != 1 );//�G���[�`�F�b�N
										if( (EneHitResult != 0) && ( EneDistance < EneNearDistance) ){
													EneNearDistance = EneDistance;//��ԋ߂��G�̋����ɍX�V���܂�
													NearEnemyID = i;//��ԋ߂����f���ԍ������܂�
													EnemyConflict = 1;//�߂��G�����邱�Ƃ������܂�
										}
					}

					/*�����A�����蔻���ɓG�������*/
					if( ( EnemyConflict == 1) && ( EneNearDistance < Wall_HitDistance)){

							// !!�ǂƂ̓����蔻�肪�K�v!!

							//�G�Ƀ_���[�W��^����
							Ene->Ene[NearEnemyID]->Set_HP( Ene->Ene[NearEnemyID]->Get_HP() - GetWeaponData( PC->Get_Wp_equipment(), 5));
					}
			}
	}



	return 0;
}
/*����𔭎˂������ǂ����̊m�F���s���܂�*/
int Weapon::ChkWeaponLaunch( const int Wp_equipment){

	/*�ϐ��̏�����*/
	int keyin[20];//�L�[���z����쐬
	WeaponFireFlag = 0;//���������t���O���I�t�ɂ���

	/*�L�[���擾����*/
	System::GetKeyData(keyin);

	if( Wp_equipment != -1){//���킪�����

			/*�ϐ��̏�����*/
			int NowAmmo = WeaponDataWhileGame[Wp_equipment][0]; //���݂̒e��

			if( ( keyin[9] == 1) && ( WeaponRapidFire == 0)){//���N���b�N����A���ˉ\���I�t�Ȃ�
					if( 0 < WeaponDataWhileGame[Wp_equipment][0] ){//Ammo���c���Ă����
							WeaponFireFlag = 1;// ���ˏ�Ԃɂ���
					}
					else if( NowAmmo == 0){//�e�Ȃ��ŋ󌂂���ԂȂ�
							WeaponFireFlag = 2;//�󌂂���Ԃ���
					}
			}
	}

	return 0;
}