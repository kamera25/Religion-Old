/*�����ł́A�X�e�[�W�̓ǂݍ��݁A������s���֐����`����N���X�R�[�h�t�@�C���ł��B
//
*/
#include "cstage.h"//�X�e�[�W��ǂ̐錾�w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

//�����Ŏg���O���[�o���ϐ���錾
extern System *sys;//�V�X�e���N���X���w���A�N���X�̃|�C���^


/*�X�e�[�W�����[�h�E�ݒ肷��֐��ł�*/
int Stage::LoadStage(int StageID, int StageKind, int LightKind){

	int ech = 0;//�G���[�`�F�b�N�ϐ��̏�����
	int NaviPoint = 0;//�V�����ǉ������i�r�|�C���g��ID����
	float FogDist = 1000.0;//�w�i�̋������w�肷��ϐ��A�ʏ��1000(�߂�)
	char loadname[256] = "";//�ǂݍ��݃f�[�^�p�̕�����z��
	D3DXVECTOR3 NaviPointPos( 0.0, 0.0, 0.0);//�i�r�|�C���g���W��������\����


	//�X�e�[�W��̃f�[�^�����������܂��B
	for(int i = 0; i < 3; i++){
		Stage_hsid[i]= 0;//�X�e�[�W�z������������܂�
		Wall_hsid[i] = 0;//�ǔz������������܂�
	};

	//�i�r���C�����쐬���܂�
	ech = E3DCreateNaviLine( &NaviLineID); 
	if( ech != 0){
				_ASSERT( 0 );
	};




	/*
		�ȉ����A�}�b�v��p�ӂ��܂��B
	*/

	if(StageID == 0){//�g�����v�[��

		if(StageKind == 0){//����MAP

						wsprintf( loadname, "%s\\data\\3d\\map\\st_trom\\trom.sig", sys->path);
						ech = E3DLoadSigFileAsGround(loadname, 30.0, 0, &Stage_hsid[0]);
						if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
								return 1;//��肠��ŏI��
						};

						wsprintf( loadname, "%s\\data\\3d\\map\\st_trom\\trom_wl2.mqo", sys->path);
						ech = E3DLoadMQOFileAsMovableArea(loadname, 50.0, &Wall_hsid[0]);
						if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
								return 1;//��肠��ŏI��
						};
		};

		if(StageKind == 1){//���K�pMAP
						wsprintf( loadname, "%s\\data\\3d\\map\\st_trom\\trom_tr.sig", sys->path);
						ech = E3DLoadSigFileAsGround(loadname, 50.0, 0, &Stage_hsid[0]);
						if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
								return 1;//��肠��ŏI��
						};

						wsprintf( loadname, "%s\\data\\3d\\map\\st_trom\\trom_trwall.mqo", sys->path);
						ech = E3DLoadMQOFileAsMovableArea(loadname, 50.0, &Wall_hsid[0]);
						if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
								return 1;//��肠��ŏI��
						};
		};

		E3DCOLOR4UC FogColor = {255,255,255,255};
		E3DSetLinearFogParams(1, FogColor, 15000, 100000, -1);//�t�@�O�������܂��B
		if(ech != 0 ){//�G���[�`�F�b�N
					_ASSERT( 0 );//�G���[�_�C�A���O
					return 1;//��肠��ŏI��
		}

		Stage_GunTarget = 0;//�X�e�[�W�̏e�����"�ʏ�"�ɂ���
		Stage_GndMode = 0;//�L�����n�ʑ����"�ʏ�ɂ���"

	};

	/////////////////

	if(StageID == 1){//���r�[

		if(StageKind == 0){//����MAP
						wsprintf( loadname, "%s\\data\\3d\\map\\st_trom\\trom.sig", sys->path);
						ech = E3DLoadSigFileAsGround(loadname, 50.0, 0, &Stage_hsid[0]);
						if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
								return 1;//��肠��ŏI��
						};

						wsprintf( loadname, "%s\\data\\3d\\map\\st_trom\\trom_wl2.mqo", sys->path);
						ech = E3DLoadMQOFileAsMovableArea(loadname, 50.0, &Wall_hsid[0]);
						if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
								return 1;//��肠��ŏI��
						};
		};

		E3DCOLOR4UC FogColor = {255,255,255,255};
		E3DSetLinearFogParams(1, FogColor, 15000, 100000, -1);//�t�@�O�������܂��B
		if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
								return 1;//��肠��ŏI��
		}

		Stage_GunTarget = 0;//�X�e�[�W�̏e�����"�ʏ�"�ɂ���
		Stage_GndMode = 0;//�L�����n�ʑ����"�ʏ�ɂ���"

	};

	////////////////

	if(StageID == 2){//�X��

		if(StageKind == 0){
						wsprintf( loadname, "%s\\data\\3d\\map\\st_forest\\st_forest.sig", sys->path);
						ech = E3DLoadSigFileAsGround(loadname, 40.0, 0, &Stage_hsid[0]);
						if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
								return 1;//��肠��ŏI��
						};
		
						wsprintf( loadname, "%s\\data\\3d\\map\\st_forest\\gwl_forest.mqo", sys->path);
						ech = E3DLoadMQOFileAsMovableArea( loadname, 40.0, &Wall_hsid[1]);
						if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
								return 1;//��肠��ŏI��
						};

		};

		E3DCOLOR4UC FogColor = {100,100,100,100};
		E3DSetLinearFogParams(1, FogColor, 4000, 8000, -1);//�t�@�O�������܂��B
		if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
								return 1;//��肠��ŏI��
		}

		FogDist = 8000.0f;//�w�i�̂���Ō����ɂ�������B
		Stage_GunTarget = 0;//�X�e�[�W�̏e�����"�ʏ�"�ɂ���
		Stage_GndMode = 0;//�L�����n�ʑ����"�ʏ�ɂ���"

	};

	////////////////

	if(StageID == 3){//�_���꒬�i�r���X�j

		if(StageKind == 0){
						wsprintf( loadname, "%s\\data\\3d\\map\\st_kamigaichi\\st_kamigaichi.sig", sys->path);
						ech = E3DLoadSigFileAsGround(loadname, 40.0, 0, &Stage_hsid[0]);
						if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
								return 1;//��肠��ŏI��
						};

		};

		/*�����̐ݒ�*/
		E3DCOLOR4UC FogColor = {100,100,100,100};
		E3DSetLinearFogParams(1, FogColor, 15000, 100000, -1);//�t�@�O�������܂��B
		if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
								return 1;//��肠��ŏI��
		}

		//������ݒ�
		Stage_GunTarget = 0;//�X�e�[�W�̏e�����"�ʏ�"�ɂ���
		Stage_GndMode = 0;//�L�����n�ʑ����"�ʏ�ɂ���"

		//�i�r���C���̍쐬
		NaviPointPos.x = -12300.0;/**/NaviPointPos.y = 0.0;/**/NaviPointPos.z = -3400.0;//���̃i�r�|�C���g�̍��W���w��
		ech = E3DAddNaviPoint( NaviLineID, -1, &NaviPoint);//�i�r�|�C���g��ǉ�
		if( ech != 0){
					_ASSERT( 0 );
		};
		ech = E3DSetNaviPointPos( NaviLineID, NaviPoint, NaviPointPos);//�i�r�|�C���g�̍��W���w��
		if( ech != 0){
					_ASSERT( 0 );
		};//

		NaviPointPos.x = -12000.0;/**/NaviPointPos.y = 0.0;/**/NaviPointPos.z = 7200.0;//���̃i�r�|�C���g�̍��W���w��
		ech = E3DAddNaviPoint( NaviLineID, -1, &NaviPoint);//�i�r�|�C���g��ǉ�
		if( ech != 0){
					_ASSERT( 0 );
		};
		ech = E3DSetNaviPointPos( NaviLineID, NaviPoint, NaviPointPos);//�i�r�|�C���g�̍��W���w��
		if( ech != 0){
					_ASSERT( 0 );
		};//

		NaviPointPos.x = 4000.0;/**/NaviPointPos.y = 0.0;/**/NaviPointPos.z = 7200.0;//���̃i�r�|�C���g�̍��W���w��
	//	ech = E3DAddNaviPoint( NaviLineID, -1, &NaviPoint);//�i�r�|�C���g��ǉ�
		if( ech != 0){
					_ASSERT( 0 );
		};
	//	ech = E3DSetNaviPointPos( NaviLineID, NaviPoint, NaviPointPos);//�i�r�|�C���g�̍��W���w��
		if( ech != 0){
					_ASSERT( 0 );
		};//

	//	NaviPointPos.x = 3200.0;/**/NaviPointPos.y = 0.0;/**/NaviPointPos.z = -3500.0;//���̃i�r�|�C���g�̍��W���w��
		ech = E3DAddNaviPoint( NaviLineID, -1, &NaviPoint);//�i�r�|�C���g��ǉ�
		if( ech != 0){
					_ASSERT( 0 );
		};
	//	ech = E3DSetNaviPointPos( NaviLineID, NaviPoint, NaviPointPos);//�i�r�|�C���g�̍��W���w��
		if( ech != 0){
					_ASSERT( 0 );
		};//

		NaviPointPos.x = -12300.0;/**/NaviPointPos.y = 0.0;/**/NaviPointPos.z = -3400.0;//���̃i�r�|�C���g�̍��W���w��
	//	ech = E3DAddNaviPoint( NaviLineID, -1, &NaviPoint);//�i�r�|�C���g��ǉ�
		if( ech != 0){
					_ASSERT( 0 );
		};
	//	ech = E3DSetNaviPointPos( NaviLineID, NaviPoint, NaviPointPos);//�i�r�|�C���g�̍��W���w��
		if( ech != 0){
					_ASSERT( 0 );
		};//

		/*//*/

	};

	/////////////////

	if(StageID == 4){//ReligionMall�i�����M�I�����[���j

		if(StageKind == 0){
						wsprintf( loadname, "%s\\data\\3d\\map\\st_rm\\rm.sig", sys->path);
						ech = E3DLoadSigFileAsGround(loadname, 55.0, 0, &Stage_hsid[0]);
						if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
								return 1;//��肠��ŏI��
						};
		

		};

		/*�����̐ݒ�*/
		E3DCOLOR4UC FogColor = {100,100,100,100};
		E3DSetLinearFogParams(1, FogColor, 15000, 100000, -1);//�t�@�O�������܂��B
		if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
								return 1;//��肠��ŏI��
		}

		Stage_GunTarget = 0;//�X�e�[�W�̏e�����"�ʏ�"�ɂ���
		Stage_GndMode = 0;//�L�����n�ʑ����"�ʏ�ɂ���"

	};

	////////////////

	if(StageID == 5){//��n�O

		if(StageKind == 0){
						wsprintf( loadname, "%s\\data\\3d\\map\\st_kichimae\\kichimae.sig", sys->path);
						ech = E3DLoadSigFileAsGround(loadname, 20.0, 0, &Stage_hsid[0]);
						if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
								return 1;//��肠��ŏI��
						};
		

		};

		/*�����̐ݒ�*/
		E3DCOLOR4UC FogColor = {100,100,100,100};
		E3DSetLinearFogParams(1, FogColor, 15000, 100000, -1);//�t�@�O�������܂��B
		if(ech != 0 ){//�G���[�`�F�b�N
								_ASSERT( 0 );//�G���[�_�C�A���O
								return 1;//��肠��ŏI��
		}

		Stage_GunTarget = 0;//�X�e�[�W�̏e�����"�ʏ�"�ɂ���
		Stage_GndMode = 0;//�L�����n�ʑ����"�ʏ�ɂ���"

	};

	/*
		�ȉ����A������p�ӂ��܂��B
	*/

	//�������쐬���܂��B
	ech = E3DCreateLight( &Light1_ID);//����1���쐬���܂��B
	if( ech != 0){
				_ASSERT( 0 );
	};
	ech = E3DCreateLight( &Light2_ID);//����2���쐬���܂��B
	if( ech != 0){
				_ASSERT( 0 );
	};

	//�����̑��������肵�܂��B

	if(LightKind == 0){//����

					D3DXVECTOR3 ldir1( -1.0, -1.0, -1.0);
					D3DXVECTOR3 ldir2( 1.0, 1.0, 1.0);
					E3DCOLOR4UC LightColor = { 255, 255, 255, 255};

					//��ڂ̃��C�g�ݒ�w
					ech = E3DSetDirectionalLight( Light1_ID, ldir1, LightColor);
					if( ech != 0){
								_ASSERT( 0 );
					};

					//��ڂ̃��C�g�ݒ�
					ech = E3DSetDirectionalLight( Light2_ID, ldir2, LightColor);
					if( ech != 0){
								_ASSERT( 0 );
					};

					//�w�i�����܂�
					wsprintf( loadname, "%s\\data\\3d\\map\\360\\hare.jpg", sys->path);
					ech = E3DCreateBG( sys->scid1, loadname, "", 0, 0, 1, FogDist);
					if( ech != 0){
								_ASSERT( 0 );
					};
	}

	/////////////////
	if(LightKind == 1){//�[��

					D3DXVECTOR3 ldir1( -1.0, -1.0, -1.0);
					D3DXVECTOR3 ldir2( 1.0, 1.0, 1.0);
					E3DCOLOR4UC LightColor= { 200, 50, 50, 255};

					//��ڂ̃��C�g��ݒ肷��B
					ech = E3DSetDirectionalLight( Light1_ID, ldir1, LightColor);
					if( ech != 0){
								_ASSERT( 0 );
					};

					//��ڂ̃��C�g��ݒ肷��B
					ech = E3DSetDirectionalLight( Light2_ID, ldir2, LightColor);
					if( ech != 0){
								_ASSERT( 0 );
					};

					//�w�i�����܂�
					wsprintf( loadname, "%s\\data\\3d\\map\\360\\sunset.jpg", sys->path);
					ech = E3DCreateBG( sys->scid1, loadname, "", 0, 0, 1, FogDist);
					if( ech != 0){
								_ASSERT( 0 );
					};
	}

	////////////////
	if(LightKind == 2){//��

					D3DXVECTOR3 ldir1( -1.0, -1.0, -1.0);
					D3DXVECTOR3 ldir2( 1.0, 1.0, 1.0);
					E3DCOLOR4UC LightColor = { 50, 50, 50, 255};

					//��ڂ̃��C�g��ݒ肷��B
					ech = E3DSetDirectionalLight( Light1_ID, ldir1, LightColor);
					if( ech != 0){
								_ASSERT( 0 );
					};

					//��ڂ̃��C�g��ݒ肷��B
					ech = E3DSetDirectionalLight( Light2_ID, ldir2, LightColor);
					if( ech != 0){
								_ASSERT( 0 );
					};

					//�w�i�����܂�
					wsprintf( loadname, "%s\\data\\3d\\map\\360\\night.jpg", sys->path);
					ech = E3DCreateBG( sys->scid1, loadname, "", 0, 0, 1, FogDist);
					if( ech != 0){
								_ASSERT( 0 );
					};
	}

	/**/
	//�Ō�ɕϐ�������s���܂��B
	/**/

	Stage_ID = StageID;//�X�e�[�WID����
	Stage_Kind = StageKind;//�X�e�[�W�̎�ނ���



	return 0;
}

/*Stage�N���X�̃f�R���X�g���N�^�A���[�h�������Ȃǂ��폜���܂��B*/
Stage::~Stage(){

	//�ϐ��̏��������s���܂�
	int ech = 0;//�G���[�`�F�b�N�ϐ��̏�����
	

	//�X�e�[�W�ƕǂ��폜���܂�
	for(int i = 0; i < 3; i++){
		if(Stage_hsid[i] != 0){//�X�e�[�W���폜���܂�
				ech = E3DDestroyHandlerSet( Stage_hsid[i]);
				if( ech != 0){
							_ASSERT( 0 );
				};
		}
		if(Wall_hsid[i] != 0){//�ǂ��폜���܂�
				ech = E3DDestroyHandlerSet( Wall_hsid[i]);
				if( ech != 0){
							_ASSERT( 0 );
				};
		}
	};




	/*�������폜�����*/

	//��ڂ̌����̍폜
	ech = E3DDestroyLight( Light1_ID);
	if( ech != 0){
				_ASSERT( 0 );
	};
	//��ڂ̌����̍폜
	ech = E3DDestroyLight( Light2_ID);
	if( ech != 0){
				_ASSERT( 0 );
	};


	//�w�i���폜���܂�
	ech = E3DDestroyBG( sys->scid1);
	if( ech != 0){
				_ASSERT( 0 );
	};

	//�i�r���C�����폜���܂�
	ech = E3DDestroyNaviLine( NaviLineID);
	if( ech != 0){
				_ASSERT( 0 );
	};


}