/* ////////////////////////////////////////////////////////////////////////// */
// cGUI�N���X�\�[�X�t�@�C���ł��B
// cGUI�N���X���p�����邱�ƂŁAGUI�̃p�[�c���ȒP�ɑg�ݍ��߂�T�u�Z�b�g�𗘗p�ł��܂��B
/* ////////////////////////////////////////////////////////////////////////// */
#include <easy3d.h>//Easy3D���g�����߂̃w�b�_��ǂݍ��݂܂��B
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "csys.h"//�J�n�E�I���E�v���[�W���[�ȂǃV�X�e������̃N���X�w�b�_

#include "cGUI.h"// GUI�̃T�u�Z�b�g���g���܂�

/* �Ó��ϐ� */
int cGUI::Font[3];


// �������֐�
int cGUI::Initialize()
{
	int ech;

	/* ���j���[�Ŏg������ID��ݒ肵�܂��B*/
	ech = E3DCreateFont( 35, 0, 800, 0, 0, 0, "MS P�S�V�b�N", &Font[0]);//�啶��
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	ech = E3DCreateFont( 30, 0, 800, 0, 0, 0, "MS P�S�V�b�N", &Font[1]);//������
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	ech = E3DCreateFont( 25, 0, 800, 0, 0, 0, "MS P�S�V�b�N", &Font[2]);//������
	_ASSERT( ech != 1 );//�G���[�`�F�b�N



	return 0;
}

cGUI::cGUI()
{
	/* ������ */
	/* �ϐ��̏�����&�錾 */
	int ech = 0;// ������
	char loadname[256] = "";//���[�h����t�@�C�����̕�����z��

	/* �����o�ϐ��̏����� */
	SpriteSum = 0;
	for( int i=0; i<10; i++){
			Btn[i].X = -1;
			Bal[i].X = -1;
	}

	for( int i=0; i < 20; i++)
	{
		SpriteID[i] = -1;
	}


}

int cGUI::LoadImg( const char *FilePath, int *ID){

	/* �ϐ��̏�����&�錾 */
	int ech = 0;// 
	int IDNum = 0;//  
	char loadname[256] = "";


	if( SpriteSum == 10){		
			return -1;
	}

	/* ��̔z����������āA */
	for( int i=0; i<20; i++){
			if( SpriteID[i] == -1){
					IDNum = i;
					break;
			}
	}

	wsprintf( loadname, "%s\\%s",  System::path, FilePath);//���j���[��ʂł̏㕔�����o�[�����[�h���܂��B
	ech = E3DCreateSprite( loadname, 0, 0, &SpriteID[IDNum]);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N


	/* ������ꂽID��SpriteID�ɕԂ��܂� */
	*ID = IDNum;

	return 0;
}

int cGUI::MakeFontButton( const char *Message, int *ButtonID, const int X, const int Y, const int MaxX, const int MaxY){

	/* �ϐ��̏�����&�錾 */
	int ech = 0;// ������
	int InputID = -1;
	
	for( int i=0; i<10; i++){
			if( Btn[i].X == -1){// �J���Ă�ϐ��������
					InputID = i;
					break;
			}
	}
	if( InputID == -1){// �J���Ă���z�񂪂Ȃ����
			return -1;
	}

	/* �z��ɑ������ */
	Btn[InputID].X = X;
	Btn[InputID].Y = Y;
	Btn[InputID].MaxX = MaxX;
	Btn[InputID].MaxY = MaxY;

	wsprintf( Btn[InputID].String, "%s" , Message);//������̃R�s�[

	/* �{�^��ID���Ăяo�����֐��֕Ԃ� */
	*ButtonID = InputID;
	



	return 0;
}

int cGUI::MakeFontButton_Auto( const char *Message, int *ButtonID, const int X, const int Y){


	MakeFontButton( Message, ButtonID, X, Y, X + 150, Y + 50);

	return 0;
}

int cGUI::ChkFontButtonWithColor( const int MouseX, const int MouseY, const int NonSelectedColor, const int SelectedColor)
{
	/* �萔�̐錾 */
	int SelectedButton = -1;


	for( int i=0; i<10; i++){


			if( Btn[i].X == -1) continue;//���݂��Ȃ��{�^�����I�����ꂽ��
			
			/* �J�[�\�����{�^���͈͓̔��ɂ���� */
			if( ( ( Btn[i].X < MouseX) && (MouseX < Btn[i].MaxX)) // X���W
				&& ( Btn[i].Y + 20  < MouseY) && ( MouseY < Btn[i].MaxY)){

					/* �I������Ă���F�̕�����\�� */
					PutString( Btn[i].String, Btn[i].X, Btn[i].Y, F_SMALL, SelectedColor);
					SelectedButton = i;
			}
			else{
					PutString( Btn[i].String, Btn[i].X, Btn[i].Y, F_SMALL, NonSelectedColor);
					
			}
	}


	return SelectedButton;


}

/* �����{�^����`��A�`�F�b�N����֐� */
int cGUI::ChkFontButton( const int MouseX, const int MouseY)
{

	return ChkFontButtonWithColor( MouseX, MouseY, WHITE, BLUE);
}

int cGUI::MakeBalloonFromButton( const char *Message, int *BalloonID, int *ButtonID, const int X, const int Y){

	MakeBalloon( Message, BalloonID, X, Y, Btn[*ButtonID].X, Btn[*ButtonID].Y + 20, Btn[*ButtonID].MaxX, Btn[*ButtonID].MaxY);

	return 0;
}

int cGUI::MakeBalloon( const char *Message, int *BalloonID, const int X, const int Y , const int MouseX, const int MouseY, const int MouseMaxX, const int MouseMaxY){

	/* �ϐ��̏�����&�錾 */
	int ech = 0;// ������
	int InputID = -1;
	SIZE FontSize;

	for( int i=0; i<10; i++){
			if( Bal[i].X == -1){// �J���Ă�ϐ��������
					InputID = i;
					break;
			}
	}
	if( InputID == -1){// �J���Ă���z�񂪂Ȃ����
			return -1;
	}

	/* �t�H���g�̃T�C�Y�𑪂� */
	ech = E3DGetStrSizeByFontID( Font[F_SMALL], Message, &FontSize);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N


	/* �z��ɑ������ */
	Bal[InputID].X = X;
	Bal[InputID].Y = Y;
	Bal[InputID].MouseX = MouseX;
	Bal[InputID].MouseY = MouseY;
	Bal[InputID].MouseMaxX = MouseMaxX;
	Bal[InputID].MouseMaxY = MouseMaxY;
	Bal[InputID].Width = FontSize.cx;

	wsprintf( Bal[InputID].String, "%s" , Message);//������̃R�s�[

	/* �{�^��ID���Ăяo�����֐��֕Ԃ� */
	*BalloonID = InputID;


	return 0;
}

int cGUI::PutBalloon_Auto( const int MouseX, const int MouseY){

	for( int i=0; i< 10; i++){
		if( Bal[i].X != -1){
			if( ( Bal[i].MouseX < MouseX) && ( MouseX < Bal[i].MouseMaxX) &&
				( Bal[i].MouseY < MouseY) && ( MouseY < Bal[i].MouseMaxY)){
					PutString( Bal[i].String, 620 - Bal[i].Width, Bal[i].Y, Font[F_SMALL], WHITE);
			}
		}
	}

	return 0;
}

int cGUI::PutBalloon( const int MouseX, const int MouseY){

	for( int i=0; i< 10; i++){
		if( Bal[i].X != -1){
			if( ( Bal[i].MouseX < MouseX) && ( MouseX < Bal[i].MouseMaxX) &&
				( Bal[i].MouseY < MouseY) && ( MouseY < Bal[i].MouseMaxY)){
					PutString( Bal[i].String, Bal[i].X, Bal[i].Y, Font[F_SMALL], WHITE);
			}
		}
	}

	return 0;
}



int cGUI::PutString( const char *Message, const int X, const int Y, const int FontID, const int Color)
{

	/* �ϐ��̏�����&�錾 */
	POINT TextPos = { X, Y};//�����̈ʒu���i�[����\����

	E3DDrawTextByFontID( System::scid1, Font[FontID], TextPos, Message, Get_Color(Color) );//������������Ă��镶�����\������


	return 0;
}

E3DCOLOR4UC cGUI::Get_Color( const int ColorNum){

	 E3DCOLOR4UC Color = { 0, 0, 0, 0};

	 switch( ColorNum){
			case WHITE:{// ��
					Color.a = 255;
					Color.r = 255;
					Color.g = 255;
					Color.b = 255;
					break;
			}
			case YELOW:{// ��
					Color.a = 255;
					Color.r = 200;
					Color.g = 220;
					Color.b = 90;
					break;
			}
			case BLUE:{// ��
					Color.a = 255;
					Color.r = 100;
					Color.g = 180;
					Color.b = 240;
					break;
			}
			case BLACK:{// ��
					Color.a = 255;
					Color.r = 0;
					Color.g = 0;
					Color.b = 0;
					break;
			}
			case GRAY:{// �O���[
					Color.a = 255;
					Color.r = 130;
					Color.g = 130;
					Color.b = 130;
					break;
			}
	 }

	 return Color;
 }

cGUI::~cGUI()
{
	/* �ϐ��̏�����&�錾 */
	int ech = 0;// 

		
	for( int i=0; i<20; i++){
			if( SpriteID[i] != -1){
					DestorySprite(i);
			}
	}

	return;
}

int cGUI::DestorySprite( const int SpID)
{
	/* ������ */
	int ech = 0;

	ech = E3DDestroySprite( SpriteID[SpID]);
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	return 0;
}

/* �t�@�C�i���C�Y�֐� */
int cGUI::Finalize()
{
	/* �ϐ��̏�����&�錾 */
	int ech = 0;// 

	for( int i=0; i<3; i++){

			ech = E3DDestroyFont( Font[i]);// �����̍폜
			_ASSERT( ech != 1 );//�G���[�`�F�b�N
	}

	return 0;
}

/* �`��̂��߂̏��������� */
int cGUI::StartBeginScene()
{
	/* ������ */
	int ech;
	
	ech = E3DBeginScene( System::scid1, 0, -1);
	_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

	ech = E3DBeginSprite();
	_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��


	return 0;
}

/* �`��̂��߂̏��������� */
int cGUI::EndScene()
{
	/* ������ */
	int ech;
	
	ech = E3DEndScene();
	_ASSERT( ech != 1 );//�G���[�`�F�b�N

	ech = E3DPresent( System::scid1);
	_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��


	return 0;
}

/* �X�v���C�g�̕`����I������ */
int cGUI::EndSprite()
{
	/* ������ */
	int ech;

	ech = E3DEndSprite();
	_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��

	return 0;
}

/* �X�v���C�g��`�悷�� */
int cGUI::PutSprite( const int ID, const int X, const int Y, const double MagX, const double MagY)
{
	/* ������ */
	int ech;
	
	/* �X�v���C�g�̕`�� */
	D3DXVECTOR3 MesBarPos( X, Y, 0);//�`��ʒu���w�肷��\����
	ech = E3DRenderSprite( SpriteID[ID], MagX, MagY, MesBarPos);
	_ASSERT( ech != 1 );//�G���[�_�C�A���O��\��


	return 0;
}