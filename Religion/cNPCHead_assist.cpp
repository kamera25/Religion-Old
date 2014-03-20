/*
 * ここでは、NPCモデルクラスのアシスト関数に関することが記述されている、
 * C++クラスソースコードです
 */
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル

#include "cenemy.h"//NPCクラスの宣言ヘッダファイル

/* NPC構造体リスト最後部を示すイテレータを返します */
vector<NPC_t>::iterator NPC_Head::NPC_endit(){

	return NPC.end();
}

/* NPC構造体リスト最初部を示すイテレータを返します */
vector<NPC_t>::iterator NPC_Head::Get_NPC_begin(){

	return NPC.begin();
}

/* NPC構造体リストが空であるかというフラグを返します */
bool NPC_Head::Get_NPC_empty() const{

	return NPC.empty();
}