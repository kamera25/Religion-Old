#pragma once
#include <list>
#include <map>
#include <string>
#include "cGUI.h"

/*
 *
 *
 *
 *
 */
/* ����ŗ��p���郉�x���ƃe�L�X�g�̍\���� */
struct SwitchLabel{
	char Text[40];
	char Label[60];
};


/* 1�̃X�g�[���e�L�X�g��ۑ����邽�߂̍\���� */
struct StoryData{
	char Name[32];
	char Text[256];
	std::list<SwitchLabel> SWT;
	int ImgID;
	int Statement;
};


class Story : public cGUI{

private:
	int NamebarID;// ���O�o�[
	int MessagebarID;// ���b�Z�[�W�o�[
	int CursorID;// �J�[�\��
	int CharaImg[10];
	int Font;
	int BGID;// �w�i�̉摜ID

	/* �X�g�[���̃}�b�v���쐬���܂� */
	std::map<std::string, std::list<StoryData>> StoryLabel;

	/* �萔 */
	static const int PUTIMG = 0;
	static const int PUTCHARA = 1;
	static const int EFFECT = 2;
	static const int END = 3;
	static const int NONE = 4;
	static const int SWITCH = 5;
	static const int MKSWITCH = 6;
	static const int DAMMY = 7;

	static const int C_ARTY = 0;
	static const int C_VILL = 1;

	/* �֐� */
	char* ConvertNewLine( char *str1);
	int PutCharaName(const char * ChName);
	int PutMesseageView();
	int PutText( const char * Text);
	int PutBackGround();

public:

	//std::list<StoryData> StoryList;

	Story();// �R���X�g���N�^�B�X�v���C�g�̃��[�h�����s���܂��B
	virtual ~Story();// �f�X�g���N�^�B
	int LoadStoryFromSTD( char *LoadPath);// Std�t�@�C������A�X�g�[���ɕK�v�ȃf�[�^�̓ǂݏo���A�������s���܂��B
	int StartStory( int StoryID);// �X�g�[��ID�̘b���J�n���܂��B

};


