/*�����ł́A�Q�[�����C�����[�v�����A����ъe�V�X�e�����Ăяo���܂��B
//
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "cfirstmenu.h"//���C�����j���[�Ɋւ��郁�j���N���X�w�b�_�t�@�C��
#include "copsmenu.h"//�I�y���[�V�������[�h�Ɋւ���N���X�w�b�_
#include "coperation.h"//�I�y���[�V�����J�n�֌W�̃N���X�w�b�_�t�@�C��


//�Q�[�����X�^�[�g���܂��B
int GMStart(){

	/*�ϐ��̏�����&�錾*/
	int MenuSelectNo = 0;//�ǂ̃��j���[���I�����ꂽ���i�[���܂�

	while( WM_QUIT != System::msg.message){

			/*���C�����j���[���ɓ���܂�*/
			{
				MainMenu MainMenu;
				MenuSelectNo = MainMenu.InMainMenu();
			}

			/*�Z���N�g�ϐ��ɂ���ĕ��򂵂܂�*/
			switch( MenuSelectNo){
				case 1:{//�I�y���[�V�������[�h���I�����ꂽ��
					OperationMenu OpsMenu;//�I�v�X���j���[�N���X���쐬
					OpsMenu.InOpsMenu();
					break;
				}
				case 0:{
						Operation OPS;//�I�y���[�V���������
						OPS.OpsMissionBranchStart( 0);// �V�΂̏������Ă�
						break;
				}
			}
	}


	return 0;
}