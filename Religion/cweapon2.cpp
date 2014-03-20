/*�����ł́A����Ɋւ��邱�Ƃ��L�q����N���X�R�[�h�t�@�C���ł�
//
*/
#include "cweapon.h"//����Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include "cstage.h"//�X�e�[�W�֌W�̃N���X�w�b�_�t�@�C��
#include "clive.h"//�G��L�����̐錾�w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_
#include <stdlib.h>//���������̂Ɏg�p���܂�

//�����ɃO���[�o���ϐ���錾
extern System *sys;//�V�X�e���N���X���w���A�N���X�̃|�C���^

// �Q�[�����̏e�̑���Ɋւ��邱�Ƃ����܂�
int Weapon::TreatmentWhileGame( int Wp_equipment){

	/*�ϐ��̏�����*/
	int ech = 0;
	int keyin[20] = {0};
	float LightDistance = 0.0f;//�����͂�����
	float MuzzleFlashAlpha = 0.0f;//�}�Y���t���b�V���̓����x
	static int MuzzleFlashConter = 0;//�}�Y���t���b�V���J�E���^�[
	D3DXVECTOR3 MuzzlePos( 0.0, 0.0, 0.0);//�e���ʒu
	D3DXVECTOR3 MuzzleFlashSound( 340.0, 340.0, 340.0);//�}�Y���t���b�V���T�E���h�̑��xXYZ
	E3DCOLOR4UC MuzzleFlashColor = { 0, 0, 0, 0};//�}�Y���t���b�V���̐F���w��

	/*�L�[���擾����*/
	sys->GetKeyData(keyin);



	if( Wp_equipment != -1){//���킪�����

		/*����ɐV�������[�V�����𓖂Ă�*/
		ech = E3DSetNewPoseML( WeaponModel[Wp_equipment]);
		if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
		};

		if( WeaponBone[Wp_equipment][0] != 0){
			/*�e�̒u���{�[���̍��W�����߂܂�*/
			ech = E3DGetCurrentBonePos( WeaponModel[Wp_equipment], WeaponBone[Wp_equipment][0], 1, &MuzzlePos);
			if(ech != 0 ){//�G���[�`�F�b�N
						_ASSERT( 0 );//�G���[�_�C�A���O
			};
		}

		/*�d���̈ʒu�ɔ����G�t�F�N�g��u���܂�*/
		ech = E3DSetBillboardPos( WeaponEffect[Wp_equipment][0], MuzzlePos); 
		if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
		};

		if( keyin[9] == 1){
			if( 0 < WeaponDataWhileGame[Wp_equipment][0] ){
					MuzzleFlashConter = 4;

					/*�r���{�[�h����]�����܂�*/
					ech = E3DRotateBillboard( WeaponEffect[Wp_equipment][0], float( rand() % 360), 1);
					if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
					};

					/*���̈ʒu�Ƒ������w�肵�܂�*/
					ech = E3DSet3DSoundMovement( WeaponSoundEfeect[Wp_equipment][0], MuzzlePos, MuzzleFlashSound);
					if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
					};

					/*���ˉ���炵�܂�*/
					ech = E3DPlaySound( WeaponSoundEfeect[Wp_equipment][0], 0, 0, 0);
					if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
					};

					/*�ϐ�����*/

					//�e����ЂƂ��炵�܂�
					WeaponDataWhileGame[Wp_equipment][0] = WeaponDataWhileGame[Wp_equipment][0] - 1;
			}
			else{//�󌂂���ԂȂ�
					/*���̈ʒu�Ƒ������w�肵�܂�*/
					ech = E3DSet3DSoundMovement( WeaponSoundEfeect[Wp_equipment][1], MuzzlePos, MuzzleFlashSound);
					if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
					};

					/*���ˉ���炵�܂�*/
					ech = E3DPlaySound( WeaponSoundEfeect[Wp_equipment][1], 0, 0, 0);
					if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
					};
			}
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
			if(ech != 0 ){//�G���[�`�F�b�N
						_ASSERT( 0 );//�G���[�_�C�A���O
			};
			/*���C�g��t����*/
			if( MuzzleFlashConter != 1){
						ech = E3DSetPointLight( WeaponMuzzleLight[Wp_equipment], MuzzlePos, 700.0f, MuzzleFlashColor);
						if(ech != 0 ){//�G���[�`�F�b�N
									_ASSERT( 0 );//�G���[�_�C�A���O
						};
			}
			else{//���C�g�����̂����Ԃł�
						ech = E3DSetPointLight( WeaponMuzzleLight[Wp_equipment], MuzzlePos, 0.0f, MuzzleFlashColor);
						if(ech != 0 ){//�G���[�`�F�b�N
									_ASSERT( 0 );//�G���[�_�C�A���O
						};			
			}


			/*�����̃G�t�F�N�g��(���ׂẴr���{�[�h)�̕`��*/
			ech = E3DRenderBillboard( sys->scid1, 0);
			if(ech != 0 ){//�G���[�`�F�b�N
						_ASSERT( 0 );//�G���[�_�C�A���O
			};

			/*�t���b�V���J�E���g���ЂƂ�����*/
			MuzzleFlashConter = MuzzleFlashConter -1;

			/*�����x��ύX����*/
			if( MuzzleFlashConter == 0){//�J�E���g��0�ɂȂ�����
						ech = E3DSetBillboardAlpha( WeaponEffect[Wp_equipment][0], 0.0f);
						if(ech != 0 ){//�G���[�`�F�b�N
									_ASSERT( 0 );//�G���[�_�C�A���O
						};	
			}



		}
	}

	return 0;
}