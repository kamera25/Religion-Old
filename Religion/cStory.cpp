#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include <list>

#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ
#include "cStory.h"

using namespace std;


Story::Story(){

	/* 初期化 */
	int ech;
	char loadname[256];

	/* スプライトのロード */
	wsprintf( loadname, "%s\\data\\img\\story\\namebar.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &NamebarID);
	_ASSERT( ech != 1 );//エラーチェック

	wsprintf( loadname, "%s\\data\\img\\story\\mesbar.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &MessagebarID);
	_ASSERT( ech != 1 );//エラーチェック

	wsprintf( loadname, "%s\\data\\img\\story\\cursor.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &CursorID);
	_ASSERT( ech != 1 );//エラーチェック

	/* 暫定的な処理 */
	wsprintf( loadname, "%s\\data\\img\\face\\arty\\0.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &CharaImg[0]);
	_ASSERT( ech != 1 );//エラーチェック

	wsprintf( loadname, "%s\\data\\img\\face\\vill\\0.png", System::path);
	ech = E3DCreateSprite( loadname, 0, 0, &CharaImg[1]);
	_ASSERT( ech != 1 );//エラーチェック
	/* 暫定的な処理　ここまで */

	ech = E3DCreateFont( 25, 0, 800, 0, 0, 0, "MS Pゴシック", &Font);//大文字
	_ASSERT( ech != 1 );//エラーチェック


	return;
}


int Story::LoadStoryFromSTD( char *LoadPath){

	/* 初期化 */
	int CharaID;
	int FaceID;

	char LoadFullPath[256];
	FILE *fp;
	StoryData StrDat;

	/* ファイルのオープンの処理 */
	wsprintf( LoadFullPath, "%s\\data\\prof\\story\\%s", System::path, LoadPath);
	fopen_s( &fp, LoadFullPath, "r");//指定されたファイルをオープンします。 
	if( fp == NULL){
		_ASSERT( 0 );
		return -1;
	}


	for( int i = 0; fscanf_s( fp, "%d %d %s %s", &CharaID, &FaceID, &StrDat.Name, 32, &StrDat.Text, 256 ) !=EOF ; i++){
		
		/* 初期化 */
		int k = 0;
		char *str1;
		char str2[256];

		/* 一時的な処理 */
		switch(CharaID){
			case 0:{ //アーティ
				StrDat.ImgID = 0;
				break;
			}
			case 1:{//ヴィル
				StrDat.ImgID = 1;
				break;
			}
		}

		str1 = &StrDat.Text[0];
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

		strcpy_s( StrDat.Text, str2);
		/* 一時的な処理終わり */

		StoryList.push_back(StrDat);
	}

	if( fclose(fp) == EOF){
		return -1;
	}
		


	return 0;
}

int Story::StartStory( int StoryID){

	/* 初期化 */
	int ech;
	const E3DCOLOR4UC Black = { 255, 0, 0, 0};//色構造体、黒を指定
	list<StoryData>::iterator it = StoryList.begin();

	while( it != StoryList.end() && WM_QUIT != System::msg.message){

		System::KeyRenewal(1);

		while( WM_QUIT != System::msg.message){
			
			System::KeyRenewal(1);

			ech = E3DBeginScene( System::scid1, 0, -1);
			_ASSERT( ech != 1 );//エラーダイアログを表示

			ech = E3DBeginSprite();
			_ASSERT( ech != 1 );//エラーダイアログを表示

			/* スプライトの描画 */
			D3DXVECTOR3 MesBarPos( 20, 310, 0);//描画位置を指定する構造体
			ech = E3DRenderSprite( MessagebarID, 590.0 /1024.0, 135.0/256.0, MesBarPos);
			_ASSERT( ech != 1 );//エラーダイアログを表示

			/* キャラ描画 */
			D3DXVECTOR3 CharaImgPos( 35, 280, 0);//描画位置を指定する構造体
			ech = E3DRenderSprite( CharaImg[ (*it).ImgID ], 1.0, 1.0, CharaImgPos);
			_ASSERT( ech != 1 );//エラーダイアログを表示

			D3DXVECTOR3 NameBarPos( 25, 408, 0);//描画位置を指定する構造体
			ech = E3DRenderSprite( NamebarID, 141.0 / 256.0, 41.0 / 64.0, NameBarPos);
			_ASSERT( ech != 1 );//エラーダイアログを表示

			D3DXVECTOR3 CursorPos( 580, 410, 0);//描画位置を指定する構造体
			ech = E3DRenderSprite( CursorID, 46.0 / 64.0, 1.0, CursorPos);
			_ASSERT( ech != 1 );//エラーダイアログを表示

			ech = E3DEndSprite();
			_ASSERT( ech != 1 );//エラーダイアログを表示

			/* ここまで、スプライト描画 */

			/* ここから、フォント描画 */
			POINT Pos = { 178, 340};//座標を代入する構造体
			ech = E3DDrawTextByFontID( System::scid1, Font, Pos, (*it).Text, Black );//説明が書かれている文字列を表示する
			_ASSERT( ech != 1 );//エラーチェック

			POINT NamePos = { 70, 415};//座標を代入する構造体
			ech = E3DDrawTextByFontID( System::scid1, Font, NamePos, (*it).Name, Black );//説明が書かれている文字列を表示する
			_ASSERT( ech != 1 );//エラーチェック

			/* ここまで */


			ech = E3DEndScene();
			_ASSERT( ech != 1 );//エラーチェック

			ech = E3DPresent( System::scid1);
			_ASSERT( ech != 1 );//エラーダイアログを表示

			/* 左クリックされた時 */
			if( System::GetKeyData( System::KEY_LEFTMOUSE) == 1){
				break;
			}

			System::MsgQ(30);//メッセージループ
		}

		it++;

	}






	return 0;
}
