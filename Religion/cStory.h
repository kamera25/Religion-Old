#pragma once
#include <list>
#include <map>
#include <string>
#include "cGUI.h"

/*
 *
 *
 *
 *
 */
/* 分岐で利用するラベルとテキストの構造体 */
struct SwitchLabel{
	char Text[40];
	char Label[60];
};


/* 1つのストーリテキストを保存するための構造体 */
struct StoryData{
	char Name[32];
	char Text[256];
	std::list<SwitchLabel> SWT;
	int ImgID;
	int Statement;
};


class Story : public cGUI{

private:
	int NamebarID;// 名前バー
	int MessagebarID;// メッセージバー
	int CursorID;// カーソル
	int CharaImg[10];
	int Font;
	int BGID;// 背景の画像ID

	/* ストーリのマップを作成します */
	std::map<std::string, std::list<StoryData>> StoryLabel;

	/* 定数 */
	static const int PUTIMG = 0;
	static const int PUTCHARA = 1;
	static const int EFFECT = 2;
	static const int END = 3;
	static const int NONE = 4;
	static const int SWITCH = 5;
	static const int MKSWITCH = 6;
	static const int DAMMY = 7;

	static const int C_ARTY = 0;
	static const int C_VILL = 1;

	/* 関数 */
	char* ConvertNewLine( char *str1);
	int PutCharaName(const char * ChName);
	int PutMesseageView();
	int PutText( const char * Text);
	int PutBackGround();

public:

	//std::list<StoryData> StoryList;

	Story();// コンストラクタ。スプライトのロード等を行います。
	virtual ~Story();// デストラクタ。
	int LoadStoryFromSTD( char *LoadPath);// Stdファイルから、ストーリに必要なデータの読み出し、準備を行います。
	int StartStory( int StoryID);// ストーリIDの話を開始します。

};


