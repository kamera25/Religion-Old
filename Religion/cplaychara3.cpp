/*�����ł́A�����N���X�̃L�����E�G�̊֐����`����N���X�R�[�h�t�@�C���ł��B
//���Ɍ��ł����[�h���Ɋ֌W���鎞�ɕK�v�Ȋ֐�������������Ă��܂��B
*/
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_
#include "cstage.h"//�X�e�[�W�֌W�̃N���X�w�b�_�t�@�C��
#include "clive.h"//�G��L�����̃N���X�w�b�_�t�@�C��
#include "c_batch_preparat.h"//�`��ɕK�v�ȃN���X�̐錾�w�b�_�t�@�C��
#include <math.h>//���w�v�Z���g�����߂̃w�b�_�t�@�C��
#include "cweapon.h"//����Ɋւ��邱�Ƃ̃N���X�w�b�_�t�@�C��





/*���˂����_����̏e�֘A�܂Ƃߊ֐�*/
int PlayerChara::ShoulderGunSys( Batch_Preparat *BatPre, int ScreenPos[2]){

	/*�S�̂Ŏg���ϐ��̏�����*/
	int ech = 0;//�G���[�m�F�ϐ�
	const D3DXVECTOR3 BaseVec( 0.0, 0.0, -1.0);//�����̏��������x�N�g��
	const D3DXVECTOR3 CameraUpVec( 0.0, 1.0, 0.0);//�J�����̏㕔�̃x�N�g��

	/*�L�����N�^�[�̈ʒu��ݒ肵�܂�*/
	int MotionID = 0;//ML����擾�������݂́u��t�����v���[�V����ID
	int FrameNo = 0;//ML����擾�������݂́u��t�����v���[�V���������ݍĐ����Ă���ԍ�
	static double Tm_DegQ_Y = 0.50;//�u��������O�̊p�x�ϐ�Y
	double Sin_Y = 0.0;//Y���W�T�C���ϐ�
	double Sin_XZ = 0.0;//XZ���W�T�C���ϐ�
	double Cos_Y = 0.0;//Y���W�R�T�C���ϐ�
	double Cos_XZ = 0.0;//XZ���W�R�T�C���ϐ�
	D3DXVECTOR3 TurnPos( 0.0, 0.0, 0.0);//�����ׂ�Y�x�N�g��
	D3DXVECTOR3 StomachPos( 0.0, 0.0, 0.0);//�u������v�̍��W
	D3DXVECTOR3 WantDeg( 0.0, 0.0, 0.0);//�������������ւ̃x�N�g��
	D3DXVECTOR3 OriginPos( 0.0, 0.0, 0.0);//�L�����N�^�[�������ׂ����_���W
	D3DXVECTOR3 MyPos1( 0.0, 0.0, 0.0);//�ŏ������̍��W
	D3DXVECTOR3 MyPos2( 0.0, 0.0, 0.0);//���̎����̍��W

	/**/
	//�����̌�������]�����܂��B
	/**/

	//�ŏ��ɉ�]�̌v�Z���܂�
	if(( Get_MyState() == 0) || ( (Get_MyState() == 2) && ( Get_AirOnPC() == 0))){//�ʏ�E�󒆃_�b�V�����[�h�łȂ���΁A�ȉ��擾����
				Set_PC_Deg_XZ( Get_PC_Deg_XZ() + float(0.30*(System::MousePos.x - (System::BeforeMousePos.x - System::rewin.left))) );
				Tm_DegQ_Y = Tm_DegQ_Y - 0.0020* float( System::MousePos.y - System::BeforeMousePos.y + System::rewin.top);
	}

	if( ( Get_MyState() == 3) || ( Get_MyState() == 4)){//�������т̎���
				Tm_DegQ_Y = Tm_DegQ_Y - 0.0020* float( System::MousePos.y - System::BeforeMousePos.y + System::rewin.top);
	}

	if( Get_PC_Deg_XZ() < 0){
				Set_PC_Deg_XZ( Get_PC_Deg_XZ() + 360);
	}
	if( 360 < Get_PC_Deg_XZ()){
				Set_PC_Deg_XZ( Get_PC_Deg_XZ() - 360);
	}
	if(Tm_DegQ_Y> 0.9){
				Tm_DegQ_Y = 0.9;
	}
	if(Tm_DegQ_Y< -0.6){
				Tm_DegQ_Y = -0.6;
	}

	SetCursorPos( System::rewin.left + 320, System::rewin.top + 240);//�}�E�X���W��^�񒆂�
	GetCursorPos( &System::BeforeMousePos);//�}�E�X���W���i�[���܂�

	Cos_XZ = cos(4.8);//XZ���W�R�T�C���̎擾
	Sin_XZ = sin(4.8);//XZ���W�T�C���̎擾
	Sin_Y = sin(Tm_DegQ_Y);//Y���W�T�C���̎擾
	Cos_Y = cos(Tm_DegQ_Y);//Y���W�̃R�T�C���̎擾
	TurnPos.x = float(Cos_XZ * Cos_Y * 2000);//�����ׂ�������X���W
	TurnPos.y = float(Sin_Y * 2000);//�����ׂ�������Y���W���擾
	TurnPos.z = float(Sin_XZ * Cos_Y * 2000);//�����ׂ�������Z���W���擾

	/**/
	//���ɍ��W���擾�����肵�ă��f���̃{�[���𑀍삵�܂�
	/**/

	/*�L�����N�^�[���f���̕��������������܂�*/
	ech = E3DRotateInit( Get_BodyModel());
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};

	/*���W���擾����*/
	ech = E3DGetPos( Get_BodyModel(), &MyPos1);
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};

	/*�L�����N�^�[���f���́u������v�̍��W���擾���܂�*/
	ech = E3DGetCurrentBonePos( Get_BodyModel(), Get_Bone_ID(2), 1, &StomachPos);
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};

	MyPos2.x = StomachPos.x * -1;
	MyPos2.y = StomachPos.y * -1;
	MyPos2.z = StomachPos.z * -1;

	/*���W�����_�ɂ���*/
	ech = E3DSetPos( Get_BodyModel(), MyPos2);
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};

	/*�L�����N�^�[���f���́u������v�̍��W���擾���܂�*/
	ech = E3DGetCurrentBonePos( Get_BodyModel(), Get_Bone_ID(2), 1, &StomachPos);
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};

	WantDeg.x = float( TurnPos.x - 0);//X���W�̌��������̃x�N�g�����擾
	WantDeg.y = float( TurnPos.y - 0);//Y���W�̌��������̃x�N�g�����擾
	WantDeg.z = float( TurnPos.z - 0);//Z���W�̌��������̃x�N�g�����擾

	/*�u��t�����v�����̃��[�V�����͂ǂ������ׂ܂�*/
	ech = E3DGetMotionFrameNoML( Get_BodyModel(), Get_Bone_ID(2), &MotionID, &FrameNo);
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};

	/*�u��t�����v�����̃N�H�[�^�j�I���𒲂ׂ܂�*/
	ech = E3DGetCurrentBoneQ( Get_BodyModel(), Get_Bone_ID(2), 2, Get_Quaternion(3));
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};

	/*�������������ւ̌v�Z���s���܂�*/
	ech = E3DLookAtQ( Get_Quaternion(3), WantDeg, BaseVec, 0, 2);
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};

	/*�v�Z�����N�H�[�^�[�j�I���������܂�*/
	ech = E3DSetBoneQ( Get_BodyModel(), Get_Bone_ID(2), MotionID, FrameNo, Get_Quaternion(3));
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};

	/*�}���`���C���[���[�V�����̌v�Z���s���܂�*/
	ech = E3DCalcMLMotion( Get_BodyModel());
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};

	/*�{���̎����̍��W�ɖ߂�*/
	ech = E3DSetPos( Get_BodyModel(), MyPos1);
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};

	/*�L�����N�^�[����]�����܂�*/
	ech = E3DRotateY( Get_BodyModel(), Get_PC_Deg_XZ());
	if(ech != 0 ){//�G���[�`�F�b�N
				_ASSERT( 0 );//�G���[�_�C�A���O
	};

	
	/*�X�v���C�g�̈ʒu�����߂ďI�����܂�*/
	BatPre->SpriteData[0][2] = 320 - 16.0f;//�J�[�\����X���W
	BatPre->SpriteData[0][3] = 220 - 18.0f;//�J�[�\����Y���W

	ScreenPos[0] = 320;/**/ScreenPos[1] = 220;

	return 0;
}

