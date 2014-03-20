/*�����ł́A���f����X�v���C�g�̕`��ɕK�v�ȏ������W�A�܂��`��ŕK�v��
//�֐��������I�Ɏ��s���邱�Ƃ��ł���悤�ɂ��邽�߂̃N���X�R�[�h�t�@�C��
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "c_batch_preparat.h"//�`��ɕK�v�ȃN���X�̐錾�w�b�_�t�@�C��
#include "clive.h"//�G��L�����̐錾�w�b�_�t�@�C��
#include "cweapon.h"//����Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��


/*�ŏ��Ƀ��[�h�����X�v���C�g�̔{����`��w��*/
int Batch_Render::BatchSpriteSet( const PlayerChara *PcC){

	/* �ϐ��̏�����&�錾 */
	int NowEqip = PcC->Get_Wp_equipment();

	/*�X�v���C�g�̔{����ύX���܂�*/

	//HP�o�[�ɂ��Ă̔{�����
	SpriteData[3][0] = float( PcC->Get_HP()) / float( PcC->Get_MaxHP()) * 100.0f;

	//�X�^�~�i�o�[�ɂ��Ă̔{�����
	SpriteData[4][0] = float( PcC->Get_Stamina()) / (PcC->Get_MaxStamina()) * 100.0f;

	if( PcC->Get_Wp_equipment() == -1){//����Ȃ��Ȃ�

				//�e�̒e��𖳕\����
				SpriteData[5][0] = 0.0f;

				//�e�̃}�K�W���𖳕\����
				SpriteData[6][0] = 0.0f;

				//�X�v���C�g��\�����Ȃ��悤��
				SpriteIDs[9] = 0;

	}
	else{//���킠��Ȃ�
				//�e�̒e��ɂ��Ă̔{���ϊ�
				SpriteData[5][0] = float( PcC->Wpn.Get_WeaponPointer( NowEqip)->Get_NowAmmo()) / float(PcC->Wpn.Get_WeaponPointer( NowEqip)->Get_Ammo()) * 100.0f;

				//�e�̃}�K�W���ɂ��Ă̔{���ϊ�
				SpriteData[6][0] = float( PcC->Wpn.Get_WeaponPointer( NowEqip)->Get_NowMagazine()) / float(PcC->Wpn.Get_WeaponPointer( NowEqip)->Get_Magazine() ) * 100.0f;

				//�\�����ׂ��摜��SpriteIDs�ɑ������
				SpriteIDs[9] = PcC->Wpn.Get_WeaponPointer( NowEqip)->Get_Sprite();
	}
	
	

	return 0;
}

