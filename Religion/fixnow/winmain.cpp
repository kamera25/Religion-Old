/*�����ł́A�A�v���P�[�V�����̊�b���쐬��WinMain���쐬�����֊֐���n����Ƃ����܂��B
//
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include <cstring>//�����񑀍�Ŏg���w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_


//WinMain�֐��쐬
int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd){

	System system;
	system -> Intialize( hInst);//E3D���쐬
	system -> Start();//�Q�[�����X�^�[�g���܂��B�悤�����AReligion�ցB


	return 0;
};
