/* ////////////////////////////////////////////////////////////////////////// */
// cMenu2�N���X�\�[�X�t�@�C���ł��B
// cMenu2�N���X���p�����邱�ƂŁA���j���[�����̋��ʃV�X�e�����Ȍ��ɑg�ݍ��߂܂��B
/* ////////////////////////////////////////////////////////////////////////// */
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "cMenu.h"
#include "cGUI.h"// GUI�̃T�u�Z�b�g���g���܂�

Menu::Menu() {

	/* �ϐ��̏�����&�錾 */
	int ech = 0;// ������
	char loadname[256] = "";//���[�h����t�@�C�����̕�����z��

	///* �����o�ϐ��̏����� */
	//SpriteSum = 0;
	//for( int i=0; i<10; i++){
	//		SpriteID[i] = -1;
	//		Btn[i].X = -1;
	//		Bal[i].X = -1;
	//}



	/*�X�v���C�g�����[�h���܂�*/
	wsprintf( loadname, "%s\\data\\img\\menu\\menubg.png", System::path);//���j���[��ʂł̔w�i�����[�h���܂��B
	ech = E3DCreateSprite( loadname, 0, 0, &Foundation_BG[0]);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	wsprintf( loadname, "%s\\data\\img\\menu\\menuber.png", System::path);//���j���[��ʂł̏\���o�[�����[�h���܂��B
	ech = E3DCreateSprite( loadname, 0, 0, &Foundation_BG[1]);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	wsprintf( loadname, "%s\\data\\img\\menu\\menu_up_ber.png", System::path);//���j���[��ʂł̏㕔�����o�[�����[�h���܂��B
	ech = E3DCreateSprite( loadname, 0, 0, &Foundation_BG[2]);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N


	///* ���j���[�Ŏg������ID��ݒ肵�܂��B*/
	//ech = E3DCreateFont( 35, 0, 800, 0, 0, 0, "MS P�S�V�b�N", &Font[0]);//�啶��
	//_ASSERT( ech != 1 );//�G���[�`�F�b�N

	//ech = E3DCreateFont( 30, 0, 800, 0, 0, 0, "MS P�S�V�b�N", &Font[1]);//������
	//_ASSERT( ech != 1 );//�G���[�`�F�b�N

	//ech = E3DCreateFont( 25, 0, 800, 0, 0, 0, "MS P�S�V�b�N", &Font[2]);//������
	//_ASSERT( ech != 1 );//�G���[�`�F�b�N


	return;
}

//int Menu::LoadImg( const char *FilePath, int *SpriteID){
//
//	/* �ϐ��̏�����&�錾 */
//	int ech = 0;// 
//	int IDNum = 0;//  
//	char loadname[256] = "";
//
//
//	if( SpriteSum == 10){		
//			return -1;
//	}
//
//	/* ��̔z����������āA */
//	for( int i=0; i<10; i++){
//			if( SpriteID[i] = 0){
//					IDNum = i;
//					break;
//			}
//	}
//
//	wsprintf( loadname, "%s\\%s", FilePath, System::path);//���j���[��ʂł̏㕔�����o�[�����[�h���܂��B
//	ech = E3DCreateSprite( loadname, 0, 0, &SpriteID[IDNum]);
//	_ASSERT( ech != 1 );//�G���[�`�F�b�N
//
//	/* ������ꂽID��SpriteID�ɕԂ��܂� */
//	*SpriteID = IDNum;
//
//	return 0;
//}
//
//int Menu::MakeFontButton( const char *Message, int *ButtonID, const int X, const int Y, const int MaxX, const int MaxY){
//
//	/* �ϐ��̏�����&�錾 */
//	int ech = 0;// ������
//	int InputID = -1;
//	
//	for( int i=0; i<10; i++){
//			if( Btn[i].X == -1){// �J���Ă�ϐ��������
//					InputID = i;
//					break;
//			}
//	}
//	if( InputID == -1){// �J���Ă���z�񂪂Ȃ����
//			return -1;
//	}
//
//	/* �z��ɑ������ */
//	Btn[InputID].X = X;
//	Btn[InputID].Y = Y;
//	Btn[InputID].MaxX = MaxX;
//	Btn[InputID].MaxY = MaxY;
//
//	wsprintf( Btn[InputID].String, "%s" , Message);//������̃R�s�[
//
//	/* �{�^��ID���Ăяo�����֐��֕Ԃ� */
//	*ButtonID = InputID;
//	
//
//
//
//	return 0;
//}
//
//int Menu::MakeFontButton_Auto( const char *Message, int *ButtonID, const int X, const int Y){
//
//
//	MakeFontButton( Message, ButtonID, X, Y, X + 150, Y + 50);
//
//	return 0;
//}
//
//int Menu::ChkFontButton( const int MouseX, const int MouseY){
//
//	/* �萔�̐錾 */
//	int SelectedButton = -1;
//
//
//	for( int i=0; i<10; i++){
//
//
//			if( Btn[i].X == -1) continue;//���݂��Ȃ��{�^�����I�����ꂽ��
//			
//			/* �J�[�\�����{�^���͈͓̔��ɂ���� */
//			if( ( ( Btn[i].X < MouseX) && (MouseX < Btn[i].MaxX)) // X���W
//				&& ( Btn[i].Y + 20  < MouseY) && ( MouseY < Btn[i].MaxY)){
//
//					/* �I������Ă���F�̕�����\�� */
//					PutString( Btn[i].String, Btn[i].X, Btn[i].Y, F_SMALL, BLUE);
//					SelectedButton = i;
//			}
//			else{
//					PutString( Btn[i].String, Btn[i].X, Btn[i].Y, F_SMALL, WHITE);
//					
//			}
//	}
//
//
//	return SelectedButton;
//}
//
//int Menu::MakeBalloonFromButton( const char *Message, int *BalloonID, int *ButtonID, const int X, const int Y){
//
//	MakeBalloon( Message, BalloonID, X, Y, Btn[*ButtonID].X, Btn[*ButtonID].Y + 20, Btn[*ButtonID].MaxX, Btn[*ButtonID].MaxY);
//
//	return 0;
//}
//
//int Menu::MakeBalloon( const char *Message, int *BalloonID, const int X, const int Y , const int MouseX, const int MouseY, const int MouseMaxX, const int MouseMaxY){
//
//	/* �ϐ��̏�����&�錾 */
//	int ech = 0;// ������
//	int InputID = -1;
//	SIZE FontSize;
//
//	for( int i=0; i<10; i++){
//			if( Bal[i].X == -1){// �J���Ă�ϐ��������
//					InputID = i;
//					break;
//			}
//	}
//	if( InputID == -1){// �J���Ă���z�񂪂Ȃ����
//			return -1;
//	}
//
//	/* �t�H���g�̃T�C�Y�𑪂� */
//	ech = E3DGetStrSizeByFontID( F_SMALL, Message, &FontSize);
//	_ASSERT( ech != 1 );//�G���[�`�F�b�N
//
//
//	/* �z��ɑ������ */
//	Bal[InputID].X = X;
//	Bal[InputID].Y = Y;
//	Bal[InputID].MouseX = MouseX;
//	Bal[InputID].MouseY = MouseY;
//	Bal[InputID].MouseMaxX = MouseMaxX;
//	Bal[InputID].MouseMaxY = MouseMaxY;
//	Bal[InputID].Width = FontSize.cx;
//
//	wsprintf( Bal[InputID].String, "%s" , Message);//������̃R�s�[
//
//	/* �{�^��ID���Ăяo�����֐��֕Ԃ� */
//	*BalloonID = InputID;
//
//
//	return 0;
//}
//
//int Menu::PutBalloon_Auto( const int MouseX, const int MouseY){
//
//	for( int i=0; i< 10; i++){
//		if( Bal[i].X != -1){
//			if( ( Bal[i].MouseX < MouseX) && ( MouseX < Bal[i].MouseMaxX) &&
//				( Bal[i].MouseY < MouseY) && ( MouseY < Bal[i].MouseMaxY)){
//					PutString( Bal[i].String, 620 - Bal[i].Width, Bal[i].Y, F_SMALL, WHITE);
//			}
//		}
//	}
//
//	return 0;
//}
//
//int Menu::PutBalloon( const int MouseX, const int MouseY){
//
//	for( int i=0; i< 10; i++){
//		if( Bal[i].X != -1){
//			if( ( Bal[i].MouseX < MouseX) && ( MouseX < Bal[i].MouseMaxX) &&
//				( Bal[i].MouseY < MouseY) && ( MouseY < Bal[i].MouseMaxY)){
//					PutString( Bal[i].String, Bal[i].X, Bal[i].Y, F_SMALL, WHITE);
//			}
//		}
//	}
//
//	return 0;
//}

int Menu::RenderBG(){

	/* �ϐ��̏�����&�錾 */
	E3DCOLOR4UC Alpha = { 255,255,255,255};

	RenderBG_Alpha(Alpha);

	return 0;
}

int Menu::RenderBG_Alpha( const E3DCOLOR4UC Alpha){

	/* �萔�̐錾 */
	int ech = 0;//�G���[�`�F�b�N�p�̕ϐ��錾

	const D3DXVECTOR3 SpritePos1( 0.0, 0.0, 0.0);//�w�i�̈ʒu
	const D3DXVECTOR3 SpritePos2( 0.0, -20.0, 0.0);//�\���o�[�̈ʒu
	const D3DXVECTOR3 SpritePos3( 380.0, 45.0, 0.0);//�㕔�̔����o�[

	for( int i=0; i<3; i++){
			ech = E3DSetSpriteARGB( Foundation_BG[i], Alpha);
			_ASSERT( ech != 1 );//�G���[�`�F�b�N
	}


	ech = E3DRenderSprite( Foundation_BG[0], 640.0/1024.0, 480.0/512.0, SpritePos1);//�w�i�̈ʒu
	_ASSERT( ech != 1 );//�G���[�`�F�b�N
					
	ech = E3DRenderSprite( Foundation_BG[1], 1, 1, SpritePos2);//�\���o�[�̈ʒu
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	ech = E3DRenderSprite( Foundation_BG[2], 1, 1, SpritePos3);//�㕔�̔����o�[
	_ASSERT( ech != 1 );//�G���[�`�F�b�N


	return 0;
}

//int Menu::PutString( const char *Message, const int X, const int Y, const int FontID, const int Color){
//
//	/* �ϐ��̏�����&�錾 */
//	POINT TextPos = { X, Y};//�����̈ʒu���i�[����\����
//	char PutMesseage[256] = "";
//
//	wsprintf( PutMesseage, "%s" , Message);//�X�^�~�i�̕\��
//	E3DDrawTextByFontID( System::scid1, Font[FontID], TextPos, PutMesseage, Get_Color(Color) );//������������Ă��镶�����\������
//
//
//	return 0;
//}
//
//E3DCOLOR4UC Menu::Get_Color( const int ColorNum){
//
//	 E3DCOLOR4UC Color = { 0, 0, 0, 0};
//
//	 switch( ColorNum){
//			case 0:{// ��
//					Color.a = 255;
//					Color.r = 255;
//					Color.g = 255;
//					Color.b = 255;
//					break;
//			}
//			case 1:{// ��
//					Color.a = 255;
//					Color.r = 200;
//					Color.g = 220;
//					Color.b = 90;
//					break;
//			}
//			case 2:{// ��
//					Color.a = 255;
//					Color.r = 100;
//					Color.g = 180;
//					Color.b = 240;
//					break;
//			}
//	 }
//
//	 return Color;
// }

Menu::~Menu(){

	/* �ϐ��̏�����&�錾 */
	int ech = 0;// 

	for( int i=0; i<3; i++){
			ech = E3DDestroySprite( Foundation_BG[i]);// �w�i�̍폜
			_ASSERT( ech != 1 );//�G���[�`�F�b�N

	}



	return;
}