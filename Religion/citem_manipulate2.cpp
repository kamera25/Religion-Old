/*�����́A�A�C�e������Ɋւ��邱�Ƃ̃N���X�ł��B
//��Ƀo�b�N�p�b�N��A�C�e�������ɂ��ď�����Ă��܂��B
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "citem_manipulate.h"//�A�C�e������Ɋւ���w�b�_�t�@�C��

//�����ɃO���[�o���ϐ���錾
extern System *sys;//�V�X�e���N���X���w���A�N���X�̃|�C���^


/*�ȈՐ�������\�������鏈�����s���܂�*/
int Item_Manipulate::PutItemDescript( int ChoseItem, int ItemNumber){

	/*�ϐ��̏�����*/
	int ech = 0;//�G���[�`�F�b�N�ϐ�
	char WeaponDetail[64] = "";//���핪�ނ̕�����z��
	POINT TextPos1;//���������̈ʒu���i�[����\����
	E3DCOLOR4UC NormalColor = { 255,50,50,50};//�����̔��F

	//�����̈ʒu����
	if( ( sys->MousePos.x + 256 ) < 640 ){//�����A�C�e���o�[���E�[�𒴂��Ȃ����
			TextPos1.x = sys->MousePos.x + 5;/**/TextPos1.y = sys->MousePos.y + 45;//���������̈ʒu�̓}�E�X�|�C���^����Z�o
	}
	else{//�������
			TextPos1.x = sys->MousePos.x + 5 - 256;/**/TextPos1.y = sys->MousePos.y + 45;//���������̈ʒu�̓}�E�X�|�C���^����Z�o
	}

	/**/
	//�A�C�e���̎�ނɂ���ĕ���
	/**/

	if(ChoseItem == 0){//���쒆�̃A�C�e�����u����v�Ȃ�
			if(BackPack_Weapon[ItemNumber][1] == 1){//���킪�n���h�K���n
					if(BackPack_Weapon[ItemNumber][2] == 0){//M1911
							wsprintf( WeaponDetail, "�č����̈����₷��45���a���e");//��������������܂�
					}
					if(BackPack_Weapon[ItemNumber][2] == 2){//Glock95
							wsprintf( WeaponDetail, "�|���}�[�t���[���̃t���I�[�g���e");//��������������܂�
					}
					if(BackPack_Weapon[ItemNumber][2] == 3){//M92F
							wsprintf( WeaponDetail, "�����₷���ČR�̐����̗p���e");//��������������܂�
					}
			}
			else if(BackPack_Weapon[ItemNumber][1] == 4){//���킪�A�T���g���C�t���n
					if(BackPack_Weapon[ItemNumber][2] == 0){//M4
							wsprintf( WeaponDetail, "���w�T�C�g�𓋍ڂ����A�����J���\���鏬�e");//��������������܂�
					}
			}
			else if( BackPack_Weapon[ItemNumber][1] == -1){//����Ȃ��Ȃ�
							wsprintf( WeaponDetail, "���킪����܂���");//��������������܂�

			}

			/**/
			////
			/**/

			ech = E3DDrawTextByFontID( sys->scid1, TextID[2], TextPos1, WeaponDetail, NormalColor);
			if(ech != 0){//�G���[�`�F�b�N
						_ASSERT(0);//�G���[�_�C�A���O��\��
			}
	}

	if(ChoseItem == 1){//���쒆�̃A�C�e�����u�e��v�Ȃ�

			if( BackPack_Ammo[ItemNumber][1] == 0){//.45ACP
						wsprintf( WeaponDetail, "�č�����^�������e�p�̎���");//��������������܂�
			}
			if( BackPack_Ammo[ItemNumber][1] == -1){//�e��Ȃ��Ȃ�
							wsprintf( WeaponDetail, "�e�򂪂���܂���");//��������������܂�

			}

			ech = E3DDrawTextByFontID( sys->scid1, TextID[2], TextPos1, WeaponDetail, NormalColor);
			if(ech != 0){//�G���[�`�F�b�N
						_ASSERT(0);//�G���[�_�C�A���O��\��
			}

	}

	return 0;
}
/*����A�C�e������\�������鏈�����s���܂�*/
int Item_Manipulate::PutItemName( int ChoseItem, int ItemNumber){

	/*�ϐ��̏�����*/
	int ech = 0;//�G���[�`�F�b�N�ϐ�
	char WeaponName[32] = "";//���햼�O�̕�����z��
	char WeaponKind[32] = "";//���핪�ނ̕�����z��
	POINT TextPos2;//���햼�����̈ʒu���i�[����\����
	POINT TextPos3;//����̎�ނ̖��O�����̈ʒu���i�[����\����
	E3DCOLOR4UC NormalColor = { 255,50,50,50};//�����̔��F

	//�����̈ʒu����
	if( ( sys->MousePos.x + 256 ) < 640 ){//�����A�C�e���o�[���E�[�𒴂��Ȃ����
			TextPos2.x = sys->MousePos.x + 160;/**/TextPos2.y = sys->MousePos.y + 5;//���햼�����̈ʒu�̓}�E�X�|�C���^����Z�o
			TextPos3.x = sys->MousePos.x + 5;/**/TextPos3.y = sys->MousePos.y + 5;//����̎�ނ̖��O�����̈ʒu�̓}�E�X�|�C���^����Z�o
	}
	else{//�������
			TextPos2.x = sys->MousePos.x + 160 - 256;/**/TextPos2.y = sys->MousePos.y + 5;//���햼�����̈ʒu�̓}�E�X�|�C���^����Z�o
			TextPos3.x = sys->MousePos.x + 5 - 256;/**/TextPos3.y = sys->MousePos.y + 5;//����̎�ނ̖��O�����̈ʒu�̓}�E�X�|�C���^����Z�o
	}


	/**/
	//�A�C�e���̎�ނɂ���ĕ���
	/**/

	if(ChoseItem == 0){//���쒆�̃A�C�e�����u����v�Ȃ�
			if(BackPack_Weapon[ItemNumber][1] == 1){//���킪�n���h�K���n
					if(BackPack_Weapon[ItemNumber][2] == 0){//M1911
							wsprintf( WeaponName, "M1911");//���햼�O�������܂�
					}
					if(BackPack_Weapon[ItemNumber][2] == 2){//Glock95
							wsprintf( WeaponName, "Glock95");//���햼�O�������܂�
					}
					if(BackPack_Weapon[ItemNumber][2] == 3){//M92F
							wsprintf( WeaponName, "M92F");//���햼�O�������܂�
					}
			}
			else if(BackPack_Weapon[ItemNumber][1] == 4){//���킪�A�T���g���C�t���n
					if(BackPack_Weapon[ItemNumber][2] == 0){//M4
							wsprintf( WeaponName, "M4");//���햼�O�������܂�
					}
			}
			else if( BackPack_Weapon[ItemNumber][1] == -1){
							wsprintf( WeaponName, "EMPTY");//���햼�O�������܂�

			}

			//���햼�O�̕\���������܂�
			ech = E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos2, WeaponName, NormalColor);
			if(ech != 0){//�G���[�`�F�b�N
						_ASSERT(0);//�G���[�_�C�A���O��\��
			}

		/**//////////
		/**////////


			if(ItemNumber == 0){//�}�E�X�����C���E�F�|���̏�ɂ����
					wsprintf( WeaponKind, "MAINWEAPON");//���햼�O�������܂�
			}
			if(ItemNumber == 1){//�}�E�X���T�u�E�F�|���̏�ɂ����
					wsprintf( WeaponKind, "SUBWEAPON");//���햼�O�������܂�
			}
			if(ItemNumber == 2){//�}�E�X���O���l�[�h�n�̏�ɂ����
					wsprintf( WeaponKind, "GRENADE");//���햼�O�������܂�

			}
			if(ItemNumber == 3){//�}�E�X���C�����K�v�ȕ���̏�ɂ����
					wsprintf( WeaponKind, "NEED REPAIR");//���햼�O�������܂�
			}


			//���핪�ނ�\�������܂�
			ech = E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos3, WeaponKind, NormalColor);
			if(ech != 0){//�G���[�`�F�b�N
						_ASSERT(0);//�G���[�_�C�A���O��\��
			}


	}
	if(ChoseItem == 1){//���쒆�̃A�C�e�����u�e��v�Ȃ�

			if( BackPack_Ammo[ItemNumber][1] == 0){//.45ACP
				wsprintf( WeaponKind, ".45ACP");//���햼�O�������܂�
			}
			else if( BackPack_Ammo[ItemNumber][1] == -1){
							wsprintf( WeaponKind, "EMPTY");//���햼�O�������܂�

			}

			ech = E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos3, WeaponKind, NormalColor);
			if(ech != 0){//�G���[�`�F�b�N
							_ASSERT(0);//�G���[�_�C�A���O��\��
			}


	}




	return 0;
}