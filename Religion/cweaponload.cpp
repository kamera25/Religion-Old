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
	if( WeaponModel[Selectkind] != -1){//�I�𒆂̃J�e�S���Ƀf�[�^������̂Ȃ�
				ech = E3DDestroyHandlerSet( WeaponModel[Selectkind]);
				_ASSERT( ech != 1 );//�G���[�`�F�b�N

				ech = E3DDestroySprite( WeaponSprite[Selectkind]);//�X�v���C�g���폜���܂�
				_ASSERT( ech != 1 );//�G���[�`�F�b�N
	}


	/*�e�̃��f���̃��[�h*/
	if(Wpkind == 0) GunLoad_Hand( Selectkind, Wpno);//�n���h�K���n
	if(Wpkind == 2) GunLoad_Shot( Selectkind, Wpno);//�V���b�g�K���n
	if(Wpkind == 3) GunLoad_Assault( Selectkind, Wpno);//�A�T���g���C�t���n
	if(Wpkind == 4) GunLoad_Machine( Selectkind, Wpno);//�}�V���K���n
	if(Wpkind == 5) GunLoad_Rifle( Selectkind, Wpno);//���C�t���n
	if(Wpkind == 6) GunLoad_Grenade( Selectkind, Wpno);//�O���l�[�h�n
	if(Wpkind == 7) WpLoad_Support( Selectkind, Wpno);//�T�|�[�g�n

	//�G�t�F�N�g�r���{�[�h�����[�h���܂�
	wsprintf( loadname, "%s\\data\\img\\effect\\explosion1.png", System::path);
	ech = E3DCreateBillboard ( loadname, 96, 96, 0, 1, 1, &WeaponEffect[Selectkind][0]);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	//�G�t�F�N�g��\�ߓ��߂��Ă���
	ech = E3DSetBillboardAlpha( WeaponEffect[Selectkind][0], 0.0f);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	//�t���b�V���̌��������(�O���l�[�h�͔�����)
	ech = E3DCreateLight( &WeaponMuzzleLight[Selectkind]);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N


	/*����f�[�^�̃��[�h������*/
	GunLoad_Data( Selectkind, Wpkind, Wpno);


	return 0;
}
/*����Ɋւ���f�[�^���i�[����֐�*/
int Weapon::GunLoad_Data( const int Selectkind, const int Wpkind, const int Wpno){

	/* �ϐ��̐錾�E������ */

	// �萔��  "�e�e���"
	const int _45ACP = 0;// .45ACP
	const int _22L = 1;//  .22L
	const int _9MM = 2;//  .9mm
	const int _5_56MM = 3;// 5.56mm
	const int _5_75MM = 4;// 5.75mm 
	const int _12GAGE = 5;// 12GAGE
	const int _SLUG_SHOT = 6;// Slug Shot
	const int _10GAGE = 7;// 10GAGE
	const int _5_45MM = 8;// 5.45mm
	const int _7_62MM = 9;// 7.62mm
	const int _50BMG = 10;// .50BMG
	const int _40MM = 11;//  40mm
	const int _HEAT = 12;//  HEAT


	// �萔��  "�e���x"
	const int S_PULS = 0;	// S+
	const int S = 1;		// S
	const int S_MINUS = 2;	// S-

	const int A_PULS = 3;	// A+
	const int A = 4;		// A
	const int A_MINUS = 5;	// A-

	const int B_PULS = 6;	// B+
	const int B = 7;		// B
	const int B_MINUS = 8;	// B-

	const int C_PULS = 9;	// C+
	const int C = 10;		// C
	const int C_MINUS = 11;	// C-

	// �萔��  "�A�ˉ\�E�s��"
	const int Enable_Rapid_Fire = 0;// �\
	const int Disable_Rapid_Fire = 1;// �s�\


	// �����܂�//

	const int GunData[7][6][7] = {

		//�i�ځF�g�p�e��, �З�, �˒�����, ���x, ���e��, �}�K�W����,  �A�˂ł���e��
		
		// �n���h�K��
		{	 
			{ _45ACP, 100, 150,	B,		  7,  8, Disable_Rapid_Fire},// M1911
			{ _45ACP,  80, 105,	B,		  5, 10, Disable_Rapid_Fire},// Offficers
			{ _22L,   45,   90,	A,		 50,  4, Enable_Rapid_Fire},// Glock95
			{ _9MM,   80,  180,	A,		 15,  3, Disable_Rapid_Fire},// M92F
			{ _9MM,   80,  150, S_MINUS, 15,  3, Disable_Rapid_Fire},// Cz-75
			{ _9MM,   80,  230,	A,		 15,  3, Disable_Rapid_Fire} // sauerP226
		},

		// �T�u�}�V���K��
		{
			{ _9MM,     70,  120,	A,		 30,  5, Enable_Rapid_Fire}, // TMP
			{ _45ACP,   70,   75,	B,		 20,  5, Enable_Rapid_Fire}, // INGLAM
			{ _45ACP,   90,  120,	S_MINUS, 25,  4, Enable_Rapid_Fire}, // UMP
			{ _5_56MM, 120,  130,	C_PULS,	 30,  3, Enable_Rapid_Fire}, // PATORIOT
			{ _9MM,     70,  150,	S_PULS,  15,  8, Enable_Rapid_Fire}, // MP5kruz
			{ _5_75MM,  80,  110,	B_MINUS, 50,  2, Enable_Rapid_Fire} // P90
		},

		// �V���b�g�K��
		{
			{ _12GAGE,     50,  60,	 C,		  5,  4, Disable_Rapid_Fire}, // M31
			{ _12GAGE,     40,  90,	 C_PULS,  7,  3, Disable_Rapid_Fire}, // Benel M3
			{ _SLUG_SHOT, 280,  270, B_MINUS, 7,  3, Disable_Rapid_Fire}, // SPAS-12
			{ _10GAGE,     58,  135, B,		  2,  5, Disable_Rapid_Fire}, // Gold Stalker
			{ _12GAGE,     35,  45,	 C,		  7,  3, Disable_Rapid_Fire} // M870

		},

		// �A�T���g���C�t��
		{
			{ _5_56MM, 140,  320, A,	   30,  5, Enable_Rapid_Fire}, // M4 A5
			{ _5_45MM, 160,  380, B,	   30,  4, Enable_Rapid_Fire}, // AK-74
			{ _7_62MM, 200,  410, B_MINUS, 20,  5, Enable_Rapid_Fire}, // M14
			{ _5_56MM, 140,  340, A_MINUS, 30,  5, Enable_Rapid_Fire}, // G36
			{ _5_56MM, 140,  340, S_PULS,  30,  5, Enable_Rapid_Fire} // HK 416
		},

		// �}�V���K��
		{
			{ _5_56MM,  90,  440, C_MINUS, 150,  2, Enable_Rapid_Fire}, // MINIMI
			{ _5_56MM,  90,  360, C_PULS,	90,  3, Enable_Rapid_Fire}, // M4 machine
			{ _7_62MM, 110,  400, C,		75,  4, Enable_Rapid_Fire} // RPK
		},

		// ���C�t��
		{
			{ _7_62MM, 300,  500, A,	   5, 10, Disable_Rapid_Fire}, // M700
			{ _5_56MM, 140,  420, B_PULS, 20,  4, Disable_Rapid_Fire}, // SPR Mk12
			{ _7_62MM, 280,  440, B,	  10,  4, Disable_Rapid_Fire}, // SVD
			{ _7_62MM, 260,  460, B_PULS,  5,  8, Disable_Rapid_Fire}, // PSG-1
			{ _50BMG,  850,  500, C,	   5,  3, Disable_Rapid_Fire} // M82
		},

		// �O���l�[�h
		{
			{ _40MM, 350,  80,  A,	      6,   2, Disable_Rapid_Fire}, // MGL
			{ _40MM, 400,  100, A,	      1,  15, Disable_Rapid_Fire}, // M79
			{ _HEAT, 280,  180, C,		  1,   4, Disable_Rapid_Fire}, // RPG-7
			{ _HEAT, 340,  140, B_MINUS,  4,   2, Disable_Rapid_Fire} // M202A1
		}
	};

	const double GunDoubleData[7][6][2] = {

		//�i�ځF�A�ˎ���, �����[�h����
		
		// �n���h�K��
		{	 
			{ 2.0, 1.0},// M1911
			{ 2.4, 1.0},// Offficers
			{ 4.3, 0.8},// Glock95
			{ 2.8, 1.3},// M92F
			{ 3.2, 1.3},// Cz-75
			{ 2.4, 1.7} // sauerP226
		},

		// �T�u�}�V���K��
		{
			{ 15.0, 2.0}, // TMP
			{ 20.0, 1.4}, // INGLAM
			{ 11.0, 1.3}, // UMP
			{ 13.0, 1.2}, // PATORIOT
			{ 15.0, 1.0}, // MP5kruz
			{ 15.0, 2.8} // P90
		},

		// �V���b�g�K��
		{
			{ 1.0,     1.0}, // M31
			{ 1.8,     1.8}, // Benel M3
			{ 1.5, 1.8}, // SPAS-12
			{ 2.0,     2.7}, // Gold Stalker
			{ 1.0,     1.0} // M870

		},

		// �A�T���g���C�t��
		{
			{ 13.0, 1.2}, // M4 A5
			{ 10.0, 1.1}, // AK-74
			{ 12.5, 1.3}, // M14
			{ 12.5, 1.5}, // G36
			{ 11.0, 1.3} // HK 416
		},

		// �}�V���K��
		{
			{ 10.0,  4.0}, // MINIMI
			{ 13.0,  3.4}, // M4 machine
			{ 10.0, 3.7} // RPK
		},

		// ���C�t��
		{
			{ 1.0, 2.0}, // M4 A5
			{ 2.0, 2.4}, // AK-74
			{ 1.8, 1.9}, // M14
			{ 2.0, 2.7}, // G36
			{ 0.5, 3.2} // HK 416
		},

		// �O���l�[�h
		{
			{ 1.0, 5.7}, // MGL
			{  -1, 2.4}, // M79
			{  -1, 4.5}, // RPG-7
			{ 1.4, 6.4} // M202A1
		}
	};





	WeaponData[Selectkind][0] = Wpkind;
	WeaponData[Selectkind][1] = Wpno;

	WeaponData[Selectkind][2] = GunData[Wpkind][Wpno][4];
	WeaponData[Selectkind][3] = GunData[Wpkind][Wpno][5];
	WeaponData[Selectkind][4] = GunData[Wpkind][Wpno][2];
	WeaponData[Selectkind][5] = GunData[Wpkind][Wpno][1];

	WeaponData[Selectkind][6] = int( 30 / GunDoubleData[Wpkind][Wpno][0] );
	WeaponData[Selectkind][7] = int( 30 * GunDoubleData[Wpkind][Wpno][1] );

	WeaponData[Selectkind][8] = GunData[Wpkind][Wpno][0];
	WeaponData[Selectkind][9] = GunData[Wpkind][Wpno][3];

	return 0;
}