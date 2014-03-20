#pragma once
/*�����ł́A���f����X�v���C�g�̕`��ɕK�v�ȏ������W�A�܂��`��ŕK�v��
//�֐��������I�Ɏ��s���邱�Ƃ��ł���悤�ɂ��邽�߂̃N���X�w�b�_�t�@�C��
*/
#include <vector>

using namespace std;


//�v���g�^�C�v�錾
class PlayerChara;
class Stage;
class NPC_Head;
class Camera;
class Weapon;

struct Sprite{// �X�v���C�g�\����
	int ID;
	bool ViewFlag;// �\���t���O
	bool DeleteFromBRFlag;// Batch_Render����X�v���C�g���������̃t���O
	float MagX;// �X�v���C�g�̔{��X
	float MagY;// �X�v���C�g�̔{��Y
	float X;// �X�v���C�g�ʒuX
	float Y;// �X�v���C�g�ʒuY
	float Z;// �X�v���C�g���sZ
	char Name[20];// ���ʂ���閼�O
};

struct Model{// ���f���\����
	int ID;
	bool ViewFlag;
	char Name[20];// ���ʂ���閼�O
};


/*�`�揀���ŕK�v�ȕϐ��Ȃǂ�錾����N���X*/
class Batch_Render{	

private:

	/* ���f���f�[�^�̔z���錾���܂� */
	vector<Model> Mdl;

	/*�X�v���C�g�֌W�̕ϐ���錾���܂�*/
	vector<Sprite> Spt;

	int BumpMapFlag;// �o���v�}�b�v��\�����邩�ǂ����̃t���O�ϐ�
	int ShadowFlag;// �e��\�����邩�ǂ����̃t���O�ϐ�

	/* �e�Ɋ֌W����ϐ� */
	int ShadowScid;// �e�̃X���b�v�`�F�C�����ʕϐ�
	int ShadowTexture;// �e�������_�����O����e�N�X�`�����ʕϐ�


public:



	//�֐��̐錾
	Batch_Render( const PlayerChara *PcC, const Stage *StgC, NPC_Head *NPCC, 
					const Camera *Cam);//�R���X�g���N�^�A�����������܂�
	~Batch_Render();//�f�X�g���N�^�A�X�v���C�g���폜���܂�

	int BatchRender( const int SceneEndFlg) ;//���܂ł̃f�[�^���܂Ƃ߂ĕ`�悷�邽�߂̊֐�
	int BatchChkInView();//���܂ł̃f�[�^���܂Ƃ߂Ď���p���`�F�b�N���邽�߂̊֐�
	int BacthGunTrade( int Wp_equipment);//���������������A�`�F�b�N�ƕ`�悷�郂�f����ύX����֐�
	int BatchReset( const PlayerChara *PcC, const Stage *StgC, NPC_Head *NPCC,
					const Camera *Cam);//�\�z���Ă����A�܂Ƃ߃f�[�^���č\�z����
	int BatchBeforePos();//��O�̍��W���܂Ƃ߂ĕۑ����邽�߂̊֐�
	int BatchFont( const int SceneEndFlg, const PlayerChara *PcC);//������`�悷�邱�Ƃ�ݒ�������肷��֐�
	int BatchEnableBumpMap( const int BumpFlug);//�o���v�}�b�v��L��/�����ɂ��܂�
	int BatchGetBumpMapStatus() const;//�o���v�}�b�v�ϐ��̎擾���s�Ȃ��܂�
	int BatchCreateShadow();// �e���쐬���邽�߂Ɋ֌W���鏈�����s�Ȃ��܂�
	int Batch_Present();// �o�b�N�o�b�t�@�̓��e���A�v���C�}���o�b�t�@�ɓ]�����܂�
	int Batch_BillBoard( const int SceneEndFlg);// �r���{�[�h�̕`�揈�����s���܂��B
	int RenderFont( char *Str, float Posx, float Posy, float MagScl, E3DCOLOR4UC Color);// �p������`�悵�܂�

	/* ���f���֌W�̊֐� */
	int	SetModel( const int ID, const bool ViewFlag);
	int SetModel_AddName( const int ID, const char *Name, const bool ViewFlag);
	// vector<Model>::iterator SearchModelFromName( const char *ObjName);
	int Batch_Render::SearchModelFromName( const char *ObjName, vector<Model>::iterator *it);
	int SetModel_ViewFlag( const char *Name, const bool ViewFlag);

	/* �X�v���C�g�֌W�̊֐� */
	int LoadSprite( const char *ObjPath, const float MagX, const float MagY, const float X, const float Y, const float Z, const int DeleteFromBRFlag);
	int LoadSprite_AddName( const char *ObjPath, const char *Name, const float MagX, const float MagY, const float X, const float Y, const float Z, const int DeleteFromBRFlag);
	int LoadSpriteFromID( const int ID, const char *Name, const float MagX, const float MagY, const float X, const float Y, const float Z, const int DeleteFromBRFlag);
	int SetSpriteAlpha( const char *Name, E3DCOLOR4UC AlfaColor);
	int Set_SpriteMagX( const char *ObjName, const float Value);
	int Set_SpriteMagY( const char *ObjName, const float Value);
	int Set_SpriteX( const char *ObjName, const float Value);
	int Set_SpriteY( const char *ObjName, const float Value);
	int Set_ViewFlag( const char *ObjName, const bool Value);
	//vector<Sprite>::iterator Batch_Render::SearchSpriteFromName( const char *ObjName);
	int SearchSpriteFromName( const char *ObjName, vector<Sprite>::iterator *it);

	int BatchSpriteRender( const int SceneEndFlg);//�܂Ƃ߂�ꂽ�X�v���C�g�������_�����O���邽�߂̊֐�
	int BatchSpriteSet( const PlayerChara *PcC);//�ŏ��Ƀ��[�h�����X�v���C�g�̔{����`��w�肷�邽�߂̊֐�

};