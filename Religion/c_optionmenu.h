/*�����ł́A�I�v�V�������j���[�Ɋւ��邱�Ƃ̃N���X�\�[�X�t�@�C���ł��B
//
*/
#include "cMenu.h"
class Batch_Render;


class OptionMenu: public Menu{

private:

	// �ϐ��̐錾

public:

	// �֐��̐錾
	OptionMenu();// �R���X�g���N�^�A�摜�̃��[�h�Ȃǂ��s�Ȃ��܂��B
	~OptionMenu();// �f�X�g���N�^�A�摜�̔j���Ȃǂ��s�Ȃ��܂�
	int MainOptionMenu( Batch_Render *BatchPre);// �I�v�V�������j���[�̒����������s�Ȃ��܂�

};