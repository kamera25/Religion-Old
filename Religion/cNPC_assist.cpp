/*
 * �����ł́ANPC���f���N���X�̃A�V�X�g�֐��Ɋւ��邱�Ƃ��L�q����Ă���A
 * C++�N���X�\�[�X�R�[�h�ł�
 */
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��

#include "cenemy.h"//NPC�N���X�̐錾�w�b�_�t�@�C��

/* NPC�\���̃��X�g�Ō㕔�������C�e���[�^��Ԃ��܂� */
vector<NPC_t>::iterator NPC_Head::NPC_endit(){

	return NPC.end();
}

/* NPC�\���̃��X�g�ŏ����������C�e���[�^��Ԃ��܂� */
vector<NPC_t>::iterator NPC_Head::Get_NPC_begin(){

	return NPC.begin();
}

/* NPC�\���̃��X�g����ł��邩�Ƃ����t���O��Ԃ��܂� */
bool NPC_Head::Get_NPC_empty() const{

	return NPC.empty();
}