/*�����́A�l�b�g�ڑ��Ɋւ��邱�Ƃ̃N���X�ł��B
//��ɐڑ������A�ʐM�J�n�ɂ��ď�����Ă��܂��B
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_
#include "cnetplay.h"//�l�b�g���[�N�ڑ��Ɋւ���w�b�_�t�@�C��


/*�R���X�g���N�^�A�ڑ����������܂�*/
NetPlay::NetPlay( int NetMode){
/*
	//�ϐ��̐錾
	int ech = 0;//�G���[�`�F�b�N�p�̕ϐ��錾
	SwitchNetWork = 1;

	//�����o�ϐ��̏�����
	for( int i=0; i<16; i++){
			ClientDPNID[i] = 0;
	}

	if( NetMode == 0){

			ech = gHost( "NETTEST" , 50000 , 0 , 0 );
			if(ech != 0){//�G���[�`�F�b�N
						_ASSERT(0);//�G���[�_�C�A���O��\��
						SwitchNetWork = 0;
						return;
			};
	}
	if( NetMode == 1){
			ech = gConnect( "127.0.0.1" , 50000 ,  0, 0 );
			if(ech != 0){//�G���[�`�F�b�N
						_ASSERT(0);//�G���[�_�C�A���O��\��
						SwitchNetWork = 0;
						return;
			};
	}

	/*������DPNID���擾����*/
/*	MyDPNID = gGetMyDPNID();

	/*�ڑ��䐔�𐧌�����*/
	/*ech = gSetMaxPlayers( 16);
	if(ech != 0){//�G���[�`�F�b�N
				_ASSERT(0);//�G���[�_�C�A���O��\��
				return;
	};

	*/

	return;
};
/*�f�X�g���N�^�A�l�b�g���[�N����ؒf�����܂�*/
NetPlay::~NetPlay(){

	//�ϐ��̐錾
	int ech = 0;//�G���[�`�F�b�N�p�̕ϐ��錾

	//ech = gDisConnect();
	if(ech != 0){//�G���[�`�F�b�N
				_ASSERT(0);//�G���[�_�C�A���O��\��
				return;
	};

	return;
}
/*�l�b�g���[�N����ڑ�����Ă��邩�A�m�F���܂�*/
int NetPlay::NetMessage(){

	//�ϐ��̐錾
	int ech = 0;
	int DataOnSys = 0;
	int NetData = 0;
	int DPNID = 0;
	char Mes[256] = "";// ���������b�Z�[�W�z�����

	while( 1 ){//
			if( SwitchNetWork == 1){//�l�b�g���[�N�֘A���߂����s���ėǂ��Ȃ�

					/*�f�[�^���͂��Ă��邩�`�F�b�N���܂�*/
			//		DataOnSys = gCheckBufferText();
					if(DataOnSys < 0){//�G���[�`�F�b�N
								_ASSERT(0);//�G���[�_�C�A���O��\��
								return 1;
					}
					else if( DataOnSys == 0){//��M�f�[�^���Ȃ��Ȃ�
							break;//���[�v���甲����
					}

					/*�����f�[�^���͂��Ă����*/
					if( 0 < DataOnSys ){
		//					ech = gGetText( Mes, 256);
							if(ech < 0){//�G���[�`�F�b�N
										_ASSERT(0);//�G���[�_�C�A���O��\��
										return 1;
							};

							//�������ꂪ�A���炩�̃��b�Z�[�W�������ꍇ
			//				NetData = gMessageToID( Mes);
							if( NetData == 0x0001 ){//���b�Z�[�W���u�ڑ��J�n�v�Ȃ�

//									ech = gGetText( Mes, 256);//DPNID���擾���܂�
									if(ech < 0){//�G���[�`�F�b�N
												_ASSERT(0);//�G���[�_�C�A���O��\��
												return 1;
									};

									//������𐔎��ɕϊ�
									DPNID = atoi( Mes);

									//������DPNID�ƈႤ�Ȃ�
									if( DPNID != MyDPNID){
										for( int i=0; i<16; i++){//16��m�F
											if( ClientDPNID[i] == 0){//�󂫂̃l�b�g���[�N�X�y�[�X���L���
													ClientDPNID[i] = DPNID;//���
													break;
											}
										}
									}
							}
							if( NetData== 0x0002){//���b�Z�[�W���u�N���C�A���g���ؒf�v�Ȃ�

//									ech = gGetText( Mes, 256);//DPNID���擾���܂�
									if(ech < 0){//�G���[�`�F�b�N
												_ASSERT(0);//�G���[�_�C�A���O��\��
												return 1;
									};

									//������𐔎��ɕϊ�
									DPNID = atoi( Mes);

									for( int i=0; i<16; i++){//16��m�F
										if( ClientDPNID[i] == DPNID){//�Y��DPNID�������
													ClientDPNID[i] = 0;//�폜����
													break;
										}
									}
							}
							if( NetData== 0x0004){//���b�Z�[�W���u�z�X�g����ؒf�v�Ȃ�

									for( int i=0; i<16; i++){//16��
												ClientDPNID[i] = 0;//�폜����
									}

									//�l�b�g���[�N���[�h���I��������
									SwitchNetWork = 0;
							}
					}
			}
			else{//�l�b�g���[�N���[�h�����p�ł��Ȃ�
					break;//���[�v���甲����
			}
	}



	return 0;
}