/*�����́A�A�C�e���Ɋւ��邱�Ƃ̃N���X�̃w�b�_�ł��B
//�Q�[�����ł̃A�C�e���S�ʂɂ��ď�����Ă��܂��B
*/



/* �A�C�e���N���X */
class Item{

private:
	int BringWp;//�X�e�[�W�ŏE��������
	int Ammo[4];//�莝���̒e��f�[�^���i�[
	int Recovery[5][2];//�莝���̉񕜃A�C�e���f�[�^�̊i�[
	int Key[10];//�莝���̉񕜃A�C�e���f�[�^�̊i�[
	int Equipment[3];//�莝���̑����A�C�e���f�[�^�̊i�[


public:

	/* �֐��̐錾 */
	Item();//�R���X�g���N�^�A����������s�Ȃ��܂�
	int GetItemNumber( int ItemKind, int ItemEle1, int ItemEle2);// �i�[����Ă���A�C�e���i���o�[���擾���܂�


};