/*�����ł́A���f����X�v���C�g�̕`��ɕK�v�ȏ������W�A�܂��`��ŕK�v��
//�֐��������I�Ɏ��s���邱�Ƃ��ł���悤�ɂ��邽�߂̃N���X�R�[�h�t�@�C��
*/

#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "c_batch_preparat.h"//�`��ɕK�v�ȃN���X�̐錾�w�b�_�t�@�C��


/* �o���v�}�b�v�ϐ��̎擾���s�Ȃ��܂� */
int Batch_Render::BatchGetBumpMapStatus() const{

	return BumpMapFlag;
}