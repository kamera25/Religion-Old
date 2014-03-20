#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include <list>

#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ
#include "cStory.h"

using namespace std;


Story::Story(){

	/* 初期化 */

	/* スプライトのロード */

	LoadImg( "data\\img\\face\\arty\\0.png", &CharaImg[C_ARTY]);
	LoadImg( "data\\img\\face\\vill\\0.png", &CharaImg[C_VILL]);



	LoadImg( "data\\img\\story\\namebar.png", &NamebarID);
	LoadImg( "data\\img\\story\\mesbar.png", &MessagebarID);	
	LoadImg( "data\\img\\story\\cursor.png", &CursorID);
	//wsprintf( loadname, "%s\\data\\img\\story\\cursor.png", System::path);
	//ech = E3DCreateSprite( loadname, 0, 0, &CursorID);
	//_ASSERT( ech != 1 );//エラーチェック

	/* 暫定的な処理 */
	//wsprintf( loadname, "%s\\data\\img\\face\\arty\\0.png", System::path);
	//ech = E3DCreateSprite( loadname, 0, 0, &CharaImg[0]);





	//LoadImg( "data\\img\\story\\bg\\missionroom.png", );

	return;
}

Story::~Story()
{
	/* 初期化 */
	int ech = 0;

	//ech = E3DDestroySprite( NamebarID);
	//_ASSERT( ech != 1 );//エラーチェック
	//
	//ech = E3DDestroySprite( MessagebarID);
	//_ASSERT( ech != 1 );//エラーチェック
	//
	//ech = E3DDestroySprite( CursorID);
	//_ASSERT( ech != 1 );//エラーチェック
	//
	///* 暫定的な処理 */
	//ech = E3DDestroySprite( CharaImg[0]);
	//_ASSERT( ech != 1 );//エラーチェック

	//ech = E3DDestroySprite( CharaImg[1]);
	//_ASSERT( ech != 1 );//エラーチェック


	return;
}


int Story::LoadStoryFromSTD( char *LoadPath){

	/* 初期化 */
	int CharaID;
	int FaceID;
	char Statement[256];
	char NowLabel[60] = "MAIN";

	char LoadFullPath[256];
	FILE *fp;
	
	/* ストーリデータが入っているリストに格納する */
	map<string, std::list<StoryData>>::iterator it;

	/* ファイルのオープンの処理 */
	wsprintf( LoadFullPath, "%s\\data\\prof\\story\\%s", System::path, LoadPath);
	fopen_s( &fp, LoadFullPath, "r");//指定されたファイルをオープンします。 
	if( fp == NULL){
		_ASSERT( 0 );
		return -1;
	}

	/* ////////////////////////////// */
	/* ここから、データを読み取ります */
	/* ////////////////////////////// */

	while( fscanf_s( fp, "%s", &Statement, 256) !=EOF)
	{
		/* 初期化 */
		StoryData StrDat;
		StrDat.Statement = NONE;// ステートメントを「何もなし」にしておく

		if( strcmp( Statement, "PutIMG") == NULL)
		{
			/* 文字の読み込み */
			fscanf_s( fp, "%s", &LoadFullPath, 256);

			StrDat.Statement = PUTIMG;
			LoadImg( LoadFullPath, &StrDat.ImgID);



			it = StoryLabel.find(NowLabel);
			(*it).second.push_back(StrDat);

		}

		else if( strcmp( Statement, "PutC") == NULL)
		{

			fscanf_s( fp, "%d %d %s %s", &CharaID, &FaceID, &StrDat.Name, 32, &StrDat.Text, 256 );

			/* 一時的な処理 */
			switch(CharaID){
				case C_ARTY:{ //アーティ
					StrDat.ImgID = C_ARTY;
					break;
				}
				case C_VILL:{//ヴィル
					StrDat.ImgID = C_VILL;
					break;
				}
			}

			strcpy_s( StrDat.Text, 256, ConvertNewLine( StrDat.Text));
			StrDat.Statement = PUTCHARA;


			it = StoryLabel.find(NowLabel);
			(*it).second.push_back(StrDat);
		}

		else if( strcmp( Statement, "Switch") == NULL)
		{
			/* 変数の初期化 */
			int RepeatTimes;// 選択肢数
			char cParameter[2];
			struct SwitchLabel TempSwt;

			/* スイッチを作る命令 */
			StrDat.Statement = MKSWITCH;

			/* 文字の読み込み */
			fscanf_s( fp, "%d", &RepeatTimes);
			for( int i = 0; i < RepeatTimes; i++)
			{
				fscanf_s( fp, "%s %s", &TempSwt.Text, 40, &TempSwt.Label, 60);

				StrDat.SWT.push_back(TempSwt) ;
			}


			it = StoryLabel.find(NowLabel);
			(*it).second.push_back(StrDat);

			/* スイッチの確認をする命令 */
			StrDat.Statement = SWITCH;
			(*it).second.push_back(StrDat);

		}

		// ラベル登録なら
		else if( strcmp( Statement, "*") == NULL)
		{
			fscanf_s( fp, "%s", &NowLabel, 60);

			/* プッシュするラベルを新規作成するための処理 */
			if( StoryLabel.find(NowLabel) == StoryLabel.end())
			{
				std::list<StoryData> SData;
				StoryData DammyData;// ダミーデータをプッシュしないと、話が2番目からになる
				DammyData.Statement = DAMMY;

				SData.push_back( DammyData);
				StoryLabel.insert( make_pair( string(NowLabel), SData));
			}
			else
			{
				_ASSERT(1);
			}


		}

		else if( strcmp( Statement, "END") == NULL)
		{
			StrDat.Statement = END;


			it = StoryLabel.find(NowLabel);
			(*it).second.push_back(StrDat);

		}

	}

	//for( int i = 0; fscanf_s( fp, "%d %d %s %s", &CharaID, &FaceID, &StrDat.Name, 32, &StrDat.Text, 256 ) !=EOF ; i++){
	//	
	//	/* 初期化 */


	//	/* 一時的な処理 */
	//	switch(CharaID){
	//		case 0:{ //アーティ
	//			StrDat.ImgID = 0;
	//			break;
	//		}
	//		case 1:{//ヴィル
	//			StrDat.ImgID = 1;
	//			break;
	//		}
	//	}



	//	strcpy_s( StrDat.Text, str2);
	//	/* 一時的な処理終わり */

	//	StoryList.push_back(StrDat);
	//}



	if( fclose(fp) == EOF){
		return -1;
	}
		


	return 0;
}

char* Story::ConvertNewLine( char *str1)
{
	/* 初期化 */
	int k = 0;
	static char str2[256];

	/* \n を 'NewLineコード'に変換する */
	while( *str1 != '\0'){
		if( *str1 == '\\' && *(str1 + 1) == 'n'){

			str2[k] = '\n';
			str1++;
		}
		else{
			str2[k] = *str1;
		}


		k++;
		str1++;
	}
	str2[k] = '\0';




	return str2;
}

int Story::StartStory( int StoryID)
{

	/* 初期化 */
	int ech;
	const E3DCOLOR4UC Black = Get_Color( BLACK);//色構造体、黒を指定
	char NowLabel[60] = "MAIN";
	bool NextStepFlag = false;
	bool LockNextLightClickFlag = false;
	bool StoryEndFlag = false;
	struct StoryData StoryD;

	BGID = -1;

	/* ストーリデータが入っているリストのイテレータを宣言 */
	map<string, std::list<StoryData>>::iterator it = StoryLabel.find(NowLabel);
	list<StoryData>::iterator lit;

	/* //////////// */
	/* メインループ */
	/* //////////// */
	for( lit = (*it).second.begin(); lit != (*it).second.end() && WM_QUIT != System::msg.message; lit++)
	{


		while( WM_QUIT != System::msg.message)
		{
			System::MsgQ(30);//メッセージループ
			System::KeyRenewal(1);
			StartBeginScene();

			switch( (*lit).Statement)
			{
				case DAMMY:
				{
					EndSprite();
					NextStepFlag = true;

					break;
				}
				case PUTIMG:
				{
					BGID = (*lit).ImgID;
					PutBackGround();	
					EndSprite();
					NextStepFlag = true;
					break;
				}
				case PUTCHARA:
				{

					PutBackGround();	
					PutMesseageView();
					PutSprite( CharaImg[ (*lit).ImgID ], 35, 280, 1.0f, 1.0f);	
					EndSprite();
					PutCharaName( (*lit).Name);
					PutText( (*lit).Text);

					break;
				}
				case MKSWITCH:
				{
					PutBackGround();	
					PutMesseageView();
					EndSprite();

					int i = 0;
					int Btn;
					std::list<SwitchLabel>::iterator Sit;

					for( Sit = (*lit).SWT.begin(); Sit != (*lit).SWT.end(); Sit++)
					{
						MakeFontButton_Auto( (*Sit).Text, &Btn, 190, 335 + i * 30);
						i++;
					}
					NextStepFlag = true;
					

					break;
				}
				case SWITCH:
				{
					PutBackGround();	
					PutMesseageView();
					EndSprite();

					/* 選択肢ボタンを表示させます */
					std::list<SwitchLabel>::iterator Sit = (*lit).SWT.begin();
					int i = 0;
					LockNextLightClickFlag = true;

					int SelectKind = ChkFontButtonWithColor( System::MousePos.x, System::MousePos.y, BLACK, GRAY) ;

					/* もし、ボタンがクリックされたら */
					if( SelectKind != -1 && System::GetKeyData( System::KEY_LEFTMOUSE))
					{
						/* 別のラベルにジャンプする */
						advance( Sit , SelectKind);
						it = StoryLabel.find( (*Sit).Label);
						lit = (*it).second.begin();
						LockNextLightClickFlag = false;// ロックを解除する
					}

					PutCharaName( "あなた");

					break;
				}
				case END:
				{
					PutBackGround();	
					EndSprite();
					StoryEndFlag = true;
					NextStepFlag = true;
				}
			}


			EndScene();

			/* 左クリックされた時 */
			if( StoryEndFlag == true)
			{
				return 0;
			}
			else if( ( System::GetKeyData( System::KEY_LEFTMOUSE) == 1 
				|| NextStepFlag == true)  
				&& LockNextLightClickFlag == false) 
			{
				
				NextStepFlag = false;
				break;
			}

			//else if( System::GetKeyData( System::KEY_R) == 1)// 話をスキップするなら、Rキー
			//{
			//	return 0;
			//}
		}



		
	}





	//list<StoryData>::iterator it = StoryList.begin();

	//while( it != StoryList.end() && WM_QUIT != System::msg.message){

	//	System::KeyRenewal(1);

	//	while( WM_QUIT != System::msg.message){
	//		
	//		System::KeyRenewal(1);

	//		ech = E3DBeginScene( System::scid1, 0, -1);
	//		_ASSERT( ech != 1 );//エラーダイアログを表示

	//		ech = E3DBeginSprite();
	//		_ASSERT( ech != 1 );//エラーダイアログを表示

	//		/* スプライトの描画 */
	//		D3DXVECTOR3 MesBarPos( 20, 310, 0);//描画位置を指定する構造体
	//		ech = E3DRenderSprite( MessagebarID, 590.0 /1024.0, 135.0/256.0, MesBarPos);
	//		_ASSERT( ech != 1 );//エラーダイアログを表示

	//		/* キャラ描画 */
	//		D3DXVECTOR3 CharaImgPos( 35, 280, 0);//描画位置を指定する構造体
	//		ech = E3DRenderSprite( CharaImg[ (*it).ImgID ], 1.0, 1.0, CharaImgPos);
	//		_ASSERT( ech != 1 );//エラーダイアログを表示

	//		D3DXVECTOR3 NameBarPos( 25, 408, 0);//描画位置を指定する構造体
	//		ech = E3DRenderSprite( NamebarID, 141.0 / 256.0, 41.0 / 64.0, NameBarPos);
	//		_ASSERT( ech != 1 );//エラーダイアログを表示

	//		D3DXVECTOR3 CursorPos( 580, 410, 0);//描画位置を指定する構造体
	//		ech = E3DRenderSprite( CursorID, 46.0 / 64.0, 1.0, CursorPos);
	//		_ASSERT( ech != 1 );//エラーダイアログを表示

	//		ech = E3DEndSprite();
	//		_ASSERT( ech != 1 );//エラーダイアログを表示

	//		/* ここまで、スプライト描画 */

	//		/* ここから、フォント描画 */
	//		PutString( (*it).Text, 178, 340, F_SMALL, BLACK);//説明が書かれている文字列を表示する
	//		_ASSERT( ech != 1 );//エラーチェック

	//		PutString( (*it).Name, 70, 415, F_SMALL, BLACK);//説明が書かれている文字列を表示する
	//		_ASSERT( ech != 1 );//エラーチェック

	//		/* ここまで */

	//		ech = E3DEndScene();
	//		_ASSERT( ech != 1 );//エラーチェック

	//		ech = E3DPresent( System::scid1);
	//		_ASSERT( ech != 1 );//エラーダイアログを表示

	//		/* 左クリックされた時 */
	//		if( System::GetKeyData( System::KEY_LEFTMOUSE) == 1){
	//			break;
	//		}
	//		else if( System::GetKeyData( System::KEY_R) == 1)// 話をスキップするなら、Rキー
	//		{
	//			return 0;
	//		}

	//		System::MsgQ(30);//メッセージループ
	//	}

	//	it++;

	//}






	return 0;
}

/* 背景を表示させる */
int Story::PutBackGround()
{
	
	PutSprite( BGID, 0, 0, 640.0/1024.0, 480.0/512.0);	

	return 0;
}

/* キャラ名を表示させる */
int Story::PutCharaName(const char * ChName)
{
	
	PutString( ChName, 70, 415, F_SMALL, BLACK);//説明が書かれている文字列を表示する

	return 0;
}


int Story::PutMesseageView()
{
	/* 初期化 */
	int ech;

	PutSprite( MessagebarID, 20, 310, 590.0 /1024.0, 135.0/256.0);
	PutSprite( NamebarID, 25, 408, 141.0 / 256.0, 41.0 / 64.0);

	///* メッセージバー画像を表示させる */
	//D3DXVECTOR3 MesBarPos( 20, 310, 0);//描画位置を指定する構造体
	//ech = E3DRenderSprite( MessagebarID, 590.0 /1024.0, 135.0/256.0, MesBarPos);
	//_ASSERT( ech != 1 );//エラーダイアログを表示

	///* 名前を表示させる部分の画像 */
	//D3DXVECTOR3 NameBarPos( 25, 408, 0);//描画位置を指定する構造体
	//ech = E3DRenderSprite( NamebarID, 141.0 / 256.0, 41.0 / 64.0, NameBarPos);
	//_ASSERT( ech != 1 );//エラーダイアログを表示


	return 0;
}

/* テキストを表示させます */
int Story::PutText( const char * Text)
{
	PutString( Text, 178, 340, F_SMALL, BLACK);//説明が書かれている文字列を表示する

	return 0;
}

///* ストーリモードのキー操作を行います */
//int Story::KeyControl()
//{
//	System::KeyRenewal(1);
//
//	/* 左クリックされた時 */
//	if( System::GetKeyData( System::KEY_LEFTMOUSE) == 1){
//		break;
//	}
//	else if( System::GetKeyData( System::KEY_R) == 1)// 話をスキップするなら、Rキー
//	{
//		return 0;
//	}
//
//	return 
//}