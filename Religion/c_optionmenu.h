/*�����ł́A�I�v�V�������j���[�Ɋւ��邱�Ƃ̃N���X�\�[�X�t�@�C���ł��B
//
*/
class Batch_Render;


class OptionMenu{

private:

	// �ϐ��̐錾
	int TextID[3];
	int MenuSpriteIDs[10];

public:

	// �֐��̐錾
	OptionMenu();// �R���X�g���N�^�A�摜�̃��[�h�Ȃǂ��s�Ȃ��܂��B
	~OptionMenu();// �f�X�g���N�^�A�摜�̔j���Ȃǂ��s�Ȃ��܂�
	int MainOptionMenu( Batch_Render *BatchPre);// �I�v�V�������j���[�̒����������s�Ȃ��܂�

};