/*�����́A�l�b�g�ڑ��Ɋւ��邱�Ƃ̃w�b�_�N���X�t�@�C���ł��B
//
*/



//�����ɃO���[�o���ϐ���錾
extern System *sys;//�V�X�e���N���X���w���A�N���X�̃|�C���^

class NetPlay{
private:

	//�ϐ��̐錾
	int MyDPNID;//������DPNID�������܂�
	int ClientDPNID[16];//���̐l��DPNID�������܂�
	int SwitchNetWork;//�l�b�g���[�N�֘A�����s���Ă��悢���̃t���O

public:

	//�֐��̐錾
	NetPlay( int NetMode);//�R���X�g���N�^�A�ڑ����������܂�
	~NetPlay();//�f�X�g���N�^�A�l�b�g���[�N����ؒf�����܂�

	int NetMessage();//�l�b�g���[�N����ڑ�����Ă��邩�A�m�F���܂�

};