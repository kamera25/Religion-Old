/*
 *  �V�X�e���N���X�̐Ó��ϐ��E�֐�������܂Ƃ߂��w�b�_�t�@�C��
 */


/* *****************
 * �Ó��ϐ��̐錾
 * *****************
 */

int System::UpdataSoundflag;//���������X�V���邩�̃t���O
bool System::keyin[20];//�L�[��������Ă��邩�̏��z��
int System::scid2;// �t�F�[�h�A�E�g�Ŏg���X���b�v�`�F�C��

BOOL System::GotMes;//PeekMessage�̏�Ԃ��i�[����B
bool GetKeyData( const int KeyNum);

int System::scid1;//���C���X���b�v�`�F�C����ID
int System::keyinQuick[3];//�L�[��2�����ꂽ���i�[����z��ϐ�
int System::KeyQuickEnd;//�_�b�V�����삪�I�������Ƃ����ׂẴv�b�V�������Z�b�g����t���O�ϐ�
int System::MouseWhole;//�}�E�X�z�C�[���̈ړ��ʂ��i�[����ϐ�
int System::KeyQuickPush[3][3];//�L�[��2��A�ł����Ƃ��̏�������ϐ�
int System::SpriteID[2];//���[�h�����X�v���C�g���i�[���܂�

char System::path[256];//�v���O�������N�����Ă���p�X�̕�����

MSG System::msg;//���b�Z�[�W���i�[����\���́B
HWND System::hwnd;//�n���h���E�B���h�E���i�[����B
RECT System::rewin;//4�����W�̍\����
POINT System::MousePos;//�}�E�X�̈ʒu���i�[����Point�\����
POINT System::BeforeMousePos;//�O��̃}�E�X�̈ʒu���i�[����\����