#pragma once
/*�����ł́A���f����X�v���C�g�̕`��ɕK�v�ȏ������W�A�܂��`��ŕK�v��
//�֐��������I�Ɏ��s���邱�Ƃ��ł���悤�ɂ��邽�߂̃N���X�w�b�_�t�@�C��
*/
#include "clive.h"//�G��L�����̃N���X�w�b�_�t�@�C��
#include "cenemy.h"//�G�N���X�̐錾�w�b�_�t�@�C��
#include "ccamera.h"//�J�����Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��
class PlayerChara;//�z�ϐ��΍�

/*�`�揀���ŕK�v�ȕϐ��Ȃǂ�錾����N���X*/
class Batch_Preparat{	

public:
	//�ϐ��̐錾
	int PCWp_hsids[2][3][4];//�v���C���[�L�����N�^�[�������Ă��镐�탂�f���f�[�^�̔z��

	/*�ȉ��A�����郂�f���f�[�^�̃����_�����O*/
	int PCmodel_hsid[2];//���[�h���Ă���v���C���[���f���f�[�^�Ń����_�����O���K�v�ȃf�[�^�̕ϐ�
	int Wp_hsids[2][4];//���[�h���Ă��镐�탂�f���f�[�^�Ń����_�����O���K�v�ȃf�[�^�̔z��
	int Stage_hsids[3];//���[�h���Ă���X�e�[�W���f���f�[�^�Ń����_�����O���K�v�ȃf�[�^�̔z��
	int Enemy_hsids[15];//���[�h���Ă���G�f�[�^�Ń����_�����O���K�v�ȃf�[�^�̔z��

	/*�ȉ��A�����Ȃ����f���f�[�^��E3DChkInView���K�v�ȃf�[�^*/
	int Wall_hsids[3];//���[�h���Ă���ǃ��f���f�[�^�Ŏ���p���`�F�b�N���K�v�ȃf�[�^�̔z��
	int PCDummyModel_hsids[2];//���[�h���Ă���PC�_�~�[���f���f�[�^�Ŏ���p���`�F�b�N���K�v�ȃf�[�^�̔z��
	int Hitmodel_hsids[2];//����̓����蔻��ŕK�v�ȃ��f���f�[�^�Ŏ���p���`�F�b�N���K�v�ȃf�[�^�̕ϐ�
	int CamDummyModel_hsid;//���[�h���Ă���J�����_�~�[���f���f�[�^�Ŏ���p���`�F�b�N���K�v�ȃf�[�^�̔z��

	/*�ȉ��A�����I�Ƀ����_�����O���K�v�ȃ��f���f�[�^�̔z��*/
	int Render_hsids[30];

	/*�ȉ��A�����I��E3DChkInView���K�v�ȃ��f���f�[�^�̔z��*/
	int ChkIn_hsids[40];

	/*�X�v���C�g�֌W�̕ϐ���錾���܂�*/

	/*	SpriteData�z��ɂ͈ȉ��̂悤�ȃf�[�^���i�[����Ă��܂�
	//	��Ԗڂ̔z�� �X�v���C�gID�Ɠ����ԍ��Ƀf�[�^���i�[����Ă��܂�
	//	��Ԗڂ̔z�� [0]�X�v���C�g�̔{��X [1]�X�v���C�g�̔{��Y
	//				 [2]�X�v���C�g�ʒuX [3]�X�v���C�g�ʒuY [4]�X�v���C�g���sZ
	*/
	float SpriteData[15][5];//�X�v���C�g�̃f�[�^���i�[���܂�
	int SpriteIDs[15];//�X�v���C�g��ID���i�[���܂�


	/**/
	/*�f�[�^�̕ύX���������ۂɕK�v�ȃN���X�|�C���^*/
	PlayerChara *PcC1;


	

	//�֐��̐錾
	Batch_Preparat( PlayerChara *PcC, Stage *StgC, Enemy *EneC, Camera *Cam);//�R���X�g���N�^�A�����������܂�
	~Batch_Preparat();//�f�X�g���N�^�A�X�v���C�g���폜���܂�
	int BatchRender( int SceneEndFlg);//���܂ł̃f�[�^���܂Ƃ߂ĕ`�悷�邽�߂̊֐�
	int BatchChkInView();//���܂ł̃f�[�^���܂Ƃ߂Ď���p���`�F�b�N���邽�߂̊֐�
	int BacthGunTrade( int Wp_equipment);//���������������A�`�F�b�N�ƕ`�悷�郂�f����ύX����֐�
	int BatchReset();//�\�z���Ă����A�܂Ƃ߃f�[�^���č\�z����
	int BatchBeforePos();//��O�̍��W���܂Ƃ߂ĕۑ����邽�߂̊֐�
	int BatchSpriteRender( int SceneEndFlg);//�܂Ƃ߂�ꂽ�X�v���C�g�������_�����O���邽�߂̊֐�
	int BatchSpriteSet( PlayerChara *PcC);//�ŏ��Ƀ��[�h�����X�v���C�g�̔{����`��w�肷�邽�߂̊֐�
	int BatchFont( int SceneEndFlg);//������`�悷�邱�Ƃ�ݒ�������肷��֐�
	
	/*�f�R���X�g���N�^���K�v�I�I�I*/

};