#pragma once
/*�I�y���[�V�������[�h�̊ւ��邱�ƒ�`������w�b�_�t�@�C���B
//
*/


/*�I�y���[�V�������[�h�N���X*/
class OperationMenu{

private:

	//�ϐ��̐錾
	int OpsImgIDs[4];//�I�y���[�V�������[�h�̉摜��������ϐ�
	int OpsBGImg;//�I�y���[�V�������[�h�̔w�i������܂�
	int TextID[3];//�e�L�X�g�̃t�H���g�f�[�^���i�[���܂�

public:

	//�ϐ��̐錾




	//�֐��̐錾
	OperationMenu();//�R���X�g���N�^�A�摜�̓ǂݍ��݂Ȃ�
	~OperationMenu();//�f�X�R���g���N�^�A�摜�̔j�����s���܂�
	int InOpsMenu();//�I�y���[�V�������[�h�̏������s���܂�

};