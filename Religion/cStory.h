#include <list>
/*
 *
 *
 *
 *
 */

/* 1�̃X�g�[���e�L�X�g��ۑ����邽�߂̍\���� */
struct StoryData{
	char Name[32];
	char Text[256];
	int ImgID;
};


class Story{

private:
	int NamebarID;// ���O�o�[
	int MessagebarID;// ���b�Z�[�W�o�[
	int CursorID;// �J�[�\��
	int CharaImg[10];
	int Font;

public:

	std::list<StoryData> StoryList;

	Story();// �R���X�g���N�^�B�X�v���C�g�̃��[�h�����s���܂��B
	int LoadStoryFromSTD( char *LoadPath);// Std�t�@�C������A�X�g�[���ɕK�v�ȃf�[�^�̓ǂݏo���A�������s���܂��B
	int StartStory( int StoryID);// �X�g�[��ID�̘b���J�n���܂��B

};


