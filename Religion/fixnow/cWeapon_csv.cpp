/* ////////////////////////////////////////////////////////////////////////// */
   //�����ł́A�������E�I���E�v���[�W���[�ɓn���Ƃ����s�ׂ��s���N���X�R�[�h�t�@�C���ł��B
/* ////////////////////////////////////////////////////////////////////////// */
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_


/* �X�e�[�W�v���t�@�C������X�e�[�W�̓ǂݍ��݂��s���܂� */
int Weapon::LoadEwaponFromCSV( const char *WeaponName){

	/* ������ */
	int Version;
	int ech = 0;
	const int wfindhash = ( WeaponName[0] * 13 + WeaponName[1] * 5) % 17;;// ������̃n�b�V���l
	FILE *fp; // �t�@�C���|�C���^
	char LoadPath[256];
	char Loadstr[256];
	char *pstr;

	wsprintf( LoadPath, "%s\\data\\prof\\weapon\\data.csv", System::path);
	fopen_s( &fp, LoadPath, "r");//�w�肳�ꂽ�t�@�C�����I�[�v�����܂��B 
	if( fp == NULL){
		_ASSERT( 0 );
		return -1;
	}
	
	
	/* ���s��ŏ��̕�������擾 */
	while( ret = fscanf_s( fp, "\n%[^,],", Loadstr, 64) ){
		
		int hash = ( LoadStr[0] * 13 + LoadStr[1] * 5) % 17;
		if( hash == wfindhash){// hash�������Ȃ�
			if( strcmp( Loadstr, WeaponName) != 0){// �����Ȃ�A�f�[�^�ǂݍ��݂�����B
			
				fscanf_s( fp, ",%d,%f,%d,%f,%[^,],%d,%f"
							, );
			}
		}
	}
	Set_Kind( Wpkind);
	Set_Number( Wpno);

	Set_Attack( GunData[Wpno][0]);
	Set_Range( GunData[Wpno][1]);
	Set_Ammo( GunData[Wpno][2]);


	if( fclose(fp) == EOF){
		return -1;
	}
		


	return 0;
}
