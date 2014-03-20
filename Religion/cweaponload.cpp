/*�����ł́A����Ɋւ��邱�Ƃ��L�q����N���X�R�[�h�t�@�C���ł�
//��ɁA����̃��[�h�ɂ��ď�����Ă��܂�
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "cenemy.h"//�G�N���X�̐錾�w�b�_�t�@�C��
#include "cweapon.h"//����Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��


/*��������[�h���邽�߂̊֐�*/
int Weapon::GunLoad( const int Selectkind, const int Wpkind, const int Wpno){

	//�ϐ��̏�����
	int ech = 0;
	char loadname[256] = "";

	/*���łɏe���擾���Ă���A���̏e�f�[�^�ɏ㏑������Ȃ�*/
	if( WeaponModel[Selectkind] != 0){//�I�𒆂̃J�e�S���Ƀf�[�^������̂Ȃ�
				ech = E3DDestroyHandlerSet( WeaponModel[Selectkind]);
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};

				ech = E3DDestroySprite( WeaponSprite[Selectkind]);//�X�v���C�g���폜���܂�
				if(ech != 0 ){//�G���[�`�F�b�N
							_ASSERT( 0 );//�G���[�_�C�A���O
				};
	}


	/*�e�̃��f���̃��[�h*/
	if(Wpkind == 1) GunLoad_Hand( Selectkind, Wpno);//�n���h�K���n
	if(Wpkind == 3) GunLoad_Shot( Selectkind, Wpno);//�V���b�g�K���n
	if(Wpkind == 4) GunLoad_Assault( Selectkind, Wpno);//�A�T���g���C�t���n
	if(Wpkind == 5) GunLoad_Machine( Selectkind, Wpno);//�}�V���K���n
	if(Wpkind == 6) GunLoad_Rifle( Selectkind, Wpno);//���C�t���n
	if(Wpkind == 7) GunLoad_Grenade( Selectkind, Wpno);//�O���l�[�h�n

	//�G�t�F�N�g�r���{�[�h�����[�h���܂�
	wsprintf( loadname, "%s\\data\\img\\effect\\explosion1.png", System::path);
	ech = E3DCreateBillboard ( loadname, 96, 96, 0, 1, 1, &WeaponEffect[Selectkind][0]);
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};

	//�G�t�F�N�g��\�ߓ��߂��Ă���
	ech = E3DSetBillboardAlpha( WeaponEffect[Selectkind][0], 0.0f);
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};

	//�t���b�V���̌��������(�O���l�[�h�͔�����)
	ech = E3DCreateLight( &WeaponMuzzleLight[Selectkind]);
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};


	/*����f�[�^�̃��[�h������*/
	GunLoad_Data( Selectkind, Wpkind, Wpno);


	return 0;
}
/*����Ɋւ���f�[�^���i�[����֐�*/
int Weapon::GunLoad_Data( const int Selectkind, const int Wpkind, const int Wpno){

	//�ꎞ�I�ȕϐ��i���f���i�[���Ȃǁj
	int ammo = 0;//�e��̍ő�l
	int mag = 0;//�}�K�W���̍ő�l
	int distance = 0;//�˒������̍ő�l
	int attack = 0;//����̍U���l
	int rapid_fire = 0;//�A�ˉ\�e��
	int ammokind = 0;// �e��̎��
	int accuracy = 0;// ����̐��x
	double firecounter = 0.0;//�A�˂̐��l


	switch(Wpkind){

			/* �n���h�K���֌W */
		    case 1:{
					switch(Wpno){
							case 0:{// M1911�̃f�[�^���i�[���܂��B
									ammokind = 0;
									attack = 100;
									firecounter = 2.0;
									distance = 100;
									accuracy = 5;
									ammo = 7;
									mag = 8;

									rapid_fire = 0;

									break;
						    }
							case 1:{// Offisers�̃f�[�^���i�[���܂��B
									ammokind = 0;
									attack = 80;
									firecounter = 2.4;
									distance = 70;
									accuracy = 5;
									ammo = 5;
									mag = 10;

									rapid_fire = 0;

									break;
							}
							case 2:{// Glock95�̃f�[�^���i�[���܂��B
									ammokind = 1;
									attack = 45;
									firecounter = 4.3;
									distance = 60;
									accuracy = 3;
									ammo = 50;
									mag = 4;

									rapid_fire = 1;

									break;
							}
							case 3:{// M92FS�̃f�[�^���i�[���܂��B
									ammokind = 2;
									attack = 80;
									firecounter = 2.8;
									distance = 120;
									accuracy = 3;
									ammo = 15;
									mag = 3;

									rapid_fire = 0;

								break;
							}
							case 4:{// Cz-95�̃f�[�^���i�[���܂��B
									ammokind = 2;
									attack = 80;
									firecounter = 3.2;
									distance = 100;
									accuracy = 1;// �z���g��A-
									ammo = 15;
									mag = 3;

									rapid_fire = 0;

									break;
							}
							case 5:{// PYTHON�̃f�[�^���i�[���܂��B
									ammokind = 6;
									attack = 150;
									firecounter = 1.6;
									distance = 125;
									accuracy = 7;
									ammo = 6;
									mag = 5;

									rapid_fire = 0;

									break;
							}
							case 6:{// sauerP226�̃f�[�^���i�[���܂��B
									ammokind = 2;
									attack = 80;
									firecounter = 2.4;
									distance = 140;
									accuracy = 3;
									ammo = 15;
									mag = 3;

									rapid_fire = 0;

									break;
							}
							case 7:{// LugerP08�̃f�[�^���i�[���܂��B
									ammokind = 2;
									attack = 80;
									firecounter = 3.5;
									distance = 55;
									accuracy = 6;
									ammo = 32;
									mag = 3;

									rapid_fire = 0;
									
									break;
							}
							case 8:{// USP.45�̃f�[�^���i�[���܂��B
									ammokind = 0;
									attack = 80;
									firecounter = 2.8;
									distance = 80;
									accuracy = 5;
									ammo = 13;
									mag = 3;

									rapid_fire = 0;

									break;
							}
					}
					break;
			}

			/* �T�u�}�V���K���֌W */
			case 2:{
					switch(Wpno){
							case 0:{// TMP�̃f�[�^���i�[���܂��B
									ammokind = 2;
									attack = 70;
									firecounter = 15.0;
									distance = 80;
									accuracy = 3;// �z���g��A-
									ammo = 30;
									mag = 5;

									rapid_fire = 1;

									break;
						    }
							case 1:{// INGLAM�̃f�[�^���i�[���܂��B
									ammokind = 0;
									attack = 70;
									firecounter = 20.0;
									distance = 50;
									accuracy = 6;
									ammo = 20;
									mag = 5;

									rapid_fire = 1;

									break;
							}
							case 2:{// SPECTRE M4�̃f�[�^���i�[���܂��B
									ammokind = 2;
									attack = 70;
									firecounter = 14.0;
									distance = 75;
									accuracy = 3;
									ammo = 50;
									mag = 3;

									rapid_fire = 1;

									break;
							}
							case 3:{// UMP�̃f�[�^���i�[���܂��B
									ammokind = 0;
									attack = 90;
									firecounter = 11.0;
									distance = 80;
									accuracy = 2;
									ammo = 25;
									mag = 4;

									rapid_fire = 1;

								break;
							}
							case 4:{// PATIRIOT�̃f�[�^���i�[���܂��B
									ammokind = 9;
									attack = 120;
									firecounter =13.0 ;
									distance = 85;
									accuracy = 8;
									ammo = 30;
									mag = 3;

									rapid_fire = 1;

									break;
							}
							case 5:{// MP5 kruz�̃f�[�^���i�[���܂��B
									ammokind = 2;
									attack = 70;
									firecounter = 15.0;
									distance = 100;
									accuracy = 1;
									ammo = 15;
									mag = 8;

									rapid_fire = 1;

									break;
							}
							case 6:{// P90�̃f�[�^���i�[���܂��B
									ammokind = 3;
									attack = 80;
									firecounter = 15.0;
									distance = 70;
									accuracy = 7;
									ammo = 50;
									mag = 2;

									rapid_fire = 1;

									break;
							}
					}
					break;
			}
			
				  

			/* �V���b�g�K���֌W */
		    case 3:{
					switch(Wpno){
							case 0:{// M1897�̃f�[�^���i�[���܂��B
									ammokind = 7;
									attack = 40;// *9
									firecounter = 1.0;
									distance = 20;
									accuracy = 8;
									ammo = 5;
									mag = 15;

									rapid_fire = 0;

									break;
						    }
							case 1:{// Benel M3�̃f�[�^���i�[���܂��B
									ammokind = 7;
									attack = 40;// *9
									firecounter = 1.8;
									distance = 30;
									accuracy = 7;
									ammo = 7;
									mag = 14;

									rapid_fire = 0;

									break;
							}
							case 2:{// SPAS-12�̃f�[�^���i�[���܂��B
									ammokind = 4;
									attack = 200;
									firecounter = 1.5;
									distance = 120;
									accuracy = 6;
									ammo = 7;
									mag = 14;

									rapid_fire = 0;

									break;
							}
							case 3:{// Gold Stalker�̃f�[�^���i�[���܂��B
									ammokind = 8;
									attack = 50;// *9
									firecounter = 1.5;
									distance = 50;
									accuracy = 5;
									ammo = 2;
									mag = 8;

									rapid_fire = 0;

								break;
							}
							case 4:{// USAS12�̃f�[�^���i�[���܂��B
									ammokind = 7;
									attack = 15;// *9
									firecounter = 2.2;
									distance = 20;
									accuracy = 9;
									ammo = 12;
									mag = 2;

									rapid_fire = 0;

									break;
							}
					}
					break;
		    }

		    /* �A�T���g���C�t���֌W */
		    case 4:{
					switch(Wpno){
							case 0:{// M4�̃f�[�^���i�[���܂��B
									ammokind = 9;
									attack = 140;
									firecounter = 13.0;
									distance = 160;
									accuracy = 3;
									ammo = 30;
									mag = 5;

									rapid_fire = 1;

									break;
						    }
							case 1:{// AK-101�̃f�[�^���i�[���܂��B
									ammokind = 5;
									attack = 160;
									firecounter = 10;
									distance = 190;
									accuracy = 5;
									ammo = 30;
									mag = 4;

									rapid_fire = 1;

									break;
							}
							case 2:{// G11�̃f�[�^���i�[���܂��B
									ammokind = 10;
									attack = 150;
									firecounter = 33.0;
									distance = 160;
									accuracy = 4;
									ammo = 45;
									mag = 4;

									rapid_fire = 1;

									break;
							}
							case 3:{// M14�̃f�[�^���i�[���܂��B
									ammokind = 11;
									attack = 200;
									firecounter = 12.5;
									distance = 210;
									accuracy = 6;
									ammo = 20;
									mag = 5;

									rapid_fire = 1;

								break;
							}
							case 4:{// G36�̃f�[�^���i�[���܂��B
									ammokind = 9;
									attack = 140;
									firecounter = 12.5;
									distance = 170;
									accuracy = 3;// �z���g��A-
									ammo = 30;
									mag = 5;

									rapid_fire = 1;

									break;
							}
							case 5:{// Tabor�̃f�[�^���i�[���܂��B
									ammokind = 9;
									attack = 140;
									firecounter = 12.5;
									distance = 150;
									accuracy = 2;
									ammo = 30;
									mag = 5;

									rapid_fire = 1;

									break;
							}
							case 6:{// HK 416�̃f�[�^���i�[���܂��B
									ammokind = 9;
									attack = 140;
									firecounter = 11.0;
									distance = 170;
									accuracy = 0;
									ammo = 30;
									mag = 5;

									rapid_fire = 1;

									break;
							}
					}
					break;
			}

			/* �}�V���K���֌W */
		    case 5:{
					switch(Wpno){
							case 0:{// BAR A2�̃f�[�^���i�[���܂��B
									ammokind = 11;
									attack = 120;
									firecounter = 5.0;
									distance = 160;
									accuracy = 7;
									ammo = 20;
									mag = 8;

									rapid_fire = 1;

									break;
						    }
							case 1:{// MINIMI�̃f�[�^���i�[���܂��B
									ammokind = 9;
									attack = 90;
									firecounter = 10.0;
									distance = 220;
									accuracy = 9;
									ammo = 150;
									mag = 2;

									rapid_fire = 1;

									break;
							}
							case 2:{// M4machine�̃f�[�^���i�[���܂��B
									ammokind = 9;
									attack = 90;
									firecounter = 13.0;
									distance = 180;
									accuracy = 7;
									ammo = 90;
									mag = 3;

									rapid_fire = 1;

									break;
							}
							case 3:{// RPK�̃f�[�^���i�[���܂��B
									ammokind = 11;
									attack = 110;
									firecounter = 10.0;
									distance = 200;
									accuracy = 8;
									ammo = 75;
									mag = 4;

									rapid_fire = 1;

								break;
							}
					}
					break;
			}

			/* ���C�t���֌W */
		    case 6:{
					switch(Wpno){
							case 0:{// M700�̃f�[�^���i�[���܂��B
									ammokind = 11;
									attack = 300;
									firecounter = 1.0;
									distance = 250;
									accuracy = 0;
									ammo = 5;
									mag = 10;

									rapid_fire = 0;

									break;
						    }
							case 1:{// SR-25�̃f�[�^���i�[���܂��B
									ammokind = 9;
									attack = 250;
									firecounter = 2.0;
									distance = 210;
									accuracy = 2;
									ammo = 10;
									mag = 4;

									rapid_fire = 0;

									break;
							}
							case 2:{// SVD�̃f�[�^���i�[���܂��B
									ammokind = 11;
									attack = 280;
									firecounter = 1.8;
									distance = 220;
									accuracy = 1;
									ammo = 10;
									mag = 4;

									rapid_fire = 0;

									break;
							}
							case 3:{// PSG-1�̃f�[�^���i�[���܂��B
									ammokind = 11;
									attack = 260;
									firecounter = 2.0;
									distance = 130;
									accuracy = 2;
									ammo = 5;
									mag = 6;

									rapid_fire = 0;

								break;
							}
							case 4:{// X BOW�̃f�[�^���i�[���܂��B
									ammokind = 12;
									attack = 250;
									firecounter = 0.8;
									distance = 130;
									accuracy = NULL -1;// �ُ�
									ammo = 1;
									mag = 50;

									rapid_fire = 0;

									break;
							}
							case 5:{// M82�̃f�[�^���i�[���܂��B
									ammokind = 15;
									attack = 850;
									firecounter = 0.5;
									distance = 250;
									accuracy = 3;
									ammo = 5;
									mag = 3;

									rapid_fire = 0;

									break;
							}
					}
					break;
			}
			

			/* �O���l�[�h�֌W */
		    case 7:{
					switch(Wpno){
							case 0:{// MGL�̃f�[�^���i�[���܂��B
									ammokind = 13;
									attack = 350;
									firecounter = 1.0;
									distance = 80;
									accuracy = 3;
									ammo = 6;
									mag = 12;

									rapid_fire = 0;

									break;
						    }
							case 1:{// M79�̃f�[�^���i�[���܂��B
									ammokind = 13;
									attack = 400;
									firecounter = NULL;//�ُ�
									distance = 100;
									accuracy = 3;
									ammo = NULL;//�ُ�
									mag = 18;

									rapid_fire = 0;

									break;
							}
							case 2:{// RPG-7�̃f�[�^���i�[���܂��B
									ammokind = 14;
									attack = 380;
									firecounter = 1.0;
									distance = 180;
									accuracy = 8;
									ammo = 1;
									mag = 5;

									rapid_fire = 0;

									break;
							}
							case 3:{// Panzher�̃f�[�^���i�[���܂��B
									ammokind = 14;
									attack = 410;
									firecounter = NULL;//�ُ�
									distance = 160;
									accuracy = 6;
									ammo = 1;
									mag = 5;

									rapid_fire = 0;

								break;
							}
							case 4:{// M202A1�̃f�[�^���i�[���܂��B
									ammokind = 14;
									attack = 340;
									firecounter = 1.4;
									distance = 140;
									accuracy = 6;
									ammo = 4;
									mag = 8;

									rapid_fire = 0;

									break;
							}
					}
					break;
		    }

			/* �V�[���h�֌W */
		    case 8:{
					switch(Wpno){
							case 0:{// shield + sauer�̃f�[�^���i�[���܂��B
									ammokind = 2;
									attack = 80;
									firecounter = 2.4;
									distance = 140;
									accuracy = 5;
									ammo = 15;
									mag = 3;

									rapid_fire = 0;

									break;
						    }
							case 1:{// shield + TMP�̃f�[�^���i�[���܂��B
									ammokind = 2;
									attack = 80;
									firecounter = 15;
									distance = 80;
									accuracy = 6;
									ammo = 20;
									mag = 2;

									rapid_fire = 1;

									break;
							}
					break;
					}
			}
	}


	WeaponData[Selectkind][0] = Wpkind;
	WeaponData[Selectkind][1] = Wpno;
	WeaponData[Selectkind][2] = ammo;
	WeaponData[Selectkind][3] = mag;
	WeaponData[Selectkind][4] = distance;
	WeaponData[Selectkind][5] = attack;
	WeaponData[Selectkind][6] = int( 30 / firecounter) ;
	WeaponData[Selectkind][7] = rapid_fire;
	WeaponData[Selectkind][8] = ammokind;
	WeaponData[Selectkind][9] = accuracy;

	return 0;
}