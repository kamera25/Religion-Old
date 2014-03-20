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

	/* ///////////////////////////// */
	// �X�v���C�g�̔{����ύX���܂� 
	/* ///////////////////////////// */

	//HP�o�[�ɂ��Ă̔{�����
	Set_SpriteMagX( "HPber", float( PcC->Get_HP()) / float( PcC->Get_MaxHP()) * 100.0f);

	//�X�^�~�i�o�[�ɂ��Ă̔{�����
	Set_SpriteMagX( "Staminaber", float( PcC->Get_Stamina()) / (PcC->Get_MaxStamina()) * 100.0f);



	// ���킪�Ȃ���΂��̐�̓G���[
	if( PcC->Get_Wp_equipment() == -1) return -1;

	//�e�̒e��ɂ��Ă̔{���ϊ�
	Set_SpriteMagX( "Ammober", float( PcC->Wpn.Get_WeaponPointer( NowEqip)->Get_NowAmmo()) / float(PcC->Wpn.Get_WeaponPointer( NowEqip)->Get_Ammo()) * 100.0f);

	//�e�̃}�K�W���ɂ��Ă̔{���ϊ�
	Set_SpriteMagX( "Magber", float( PcC->Wpn.Get_WeaponPointer( NowEqip)->Get_NowMagazine()) / float(PcC->Wpn.Get_WeaponPointer( NowEqip)->Get_Magazine() ) * 100.0f);


	
	

	return 0;
}

int Batch_Render::LoadSprite( const char *ObjPath, const float MagX, const float MagY, const float X, const float Y, const float Z, const int DeleteFromBRFlag){

	LoadSprite_AddName( ObjPath, "", MagX, MagY, X, Y, Z, DeleteFromBRFlag);

	return 0;
}

int Batch_Render::LoadSprite_AddName( const char *ObjPath, const char *Name, const float MagX, const float MagY, const float X, const float Y, const float Z, const int DeleteFromBRFlag){

	/* �ϐ��̐錾&������ */
	int ech = 0;
	char loadname[256] = "";//�ǂݍ��ސ�̃p�X�̕�����ϐ�
	int SpID;// �X�v���C�g��ID���i�[����ϐ�


	/* �X�v���C�g�̃��[�h */
	wsprintf( loadname, "%s\\%s", System::path, ObjPath);
	ech = E3DCreateSprite( loadname, 0, 0, &SpID);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	LoadSpriteFromID( SpID, Name, MagX, MagY, X, Y, Z, DeleteFromBRFlag);



	return 0;
}

int Batch_Render::LoadSpriteFromID( const int ID, const char *Name, const float MagX, const float MagY, const float X, const float Y, const float Z, const int DeleteFromBRFlag){

	/* �ϐ��̐錾&������ */
	Sprite SptC;

	SptC.ID = ID;
	SptC.MagX = MagX;
	SptC.MagY = MagY;
	SptC.X = X;
	SptC.Y = Y;
	SptC.Z = Z;
	SptC.ViewFlag = 1;
	wsprintf( SptC.Name, "%s", Name);

	Spt.push_back( SptC);


	return 0;
}



int Batch_Render::Set_SpriteMagX( const char *ObjName, const float Value){

	/* �ϐ��̏�����&�錾 */
	int ech = 0;
	vector<Sprite>::iterator it;
	
	ech = SearchSpriteFromName( ObjName, &it);// �C�e���[�^

	if( ech != 0){
			_ASSERT( 1);
			return -1;
	}
	
	/* MagX�̐ݒ� */
	(*it).MagX = Value;
	
	return 0;
}

int Batch_Render::SearchSpriteFromName( const char *ObjName, vector<Sprite>::iterator *it){

	/* �ϐ��̏�����&�錾 */
	vector<Sprite>::iterator iit;// �C�e���[�^

	for( iit = Spt.begin(); iit != Spt.end(); iit++){
			if( strcmp( ObjName, (*iit).Name) == 0){
					*it = iit;
					return 0;// ���[�v�𔲂��o��
			}
	}

	// ��������������������Ȃ����
	_ASSERT( 1 );//�G���[�`�F�b�N


	return -1;
}

int Batch_Render::SetSpriteAlpha( const char *Name, E3DCOLOR4UC AlfaColor){

	/* �ϐ��̏�����&�錾 */
	int ech = 0;
	vector<Sprite>::iterator it;
	
	ech = SearchSpriteFromName( Name, &it);// �C�e���[�^

	if( ech != 0){
			_ASSERT( 1 );
			return -1;
	}

	/*�����������܂�*/
	ech = E3DSetSpriteARGB( (*it).ID, AlfaColor);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N


	return 0;
}