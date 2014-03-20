#include <list>
/*
 *
 *
 *
 *
 */

/* 1つのストーリテキストを保存するための構造体 */
struct StoryData{
	char Name[32];
	char Text[256];
	int ImgID;
};


class Story{

private:
	int NamebarID;// 名前バー
	int MessagebarID;// メッセージバー
	int CursorID;// カーソル
	int CharaImg[10];
	int Font;

public:

	std::list<StoryData> StoryList;

	Story();// コンストラクタ。スプライトのロード等を行います。
	int LoadStoryFromSTD( char *LoadPath);// Stdファイルから、ストーリに必要なデータの読み出し、準備を行います。
	int StartStory( int StoryID);// ストーリIDの話を開始します。

};


