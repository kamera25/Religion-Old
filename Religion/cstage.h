#pragma once
/*ここでは、ステージの読み込み、制御を行うクラスヘッダファイルです。
//
*/
#include "cnavirail.h"//ナビレールに関するヘッダファイル



class Stage{

private:



	/* それぞれのステージロード関数の宣言 */
	int LoadStage_Tronp( const int StageKind);// トロンプールの読み込み
	int LoadStage_IRoby( const int StageKind);// インターネットロビーの読み込み
	int LoadStage_Mall( const int StageKind);// レリギオンモールの読み込み 
	int LoadStage_Retolis( const int StageKind, float *FogDist);// レトリスの読み込み
	int LoadStage_Forest( const int StageKind, float *FogDist);// 森林の読み込み
	int LoadStage_Kamigaichi( const int StageKind);// 神ヶ一町の読み込み
	int LoadStage_BaseFront( const int StageKind);// 基地前の読み込み

	/* 関数の宣言 */
	int SetStageLight( const int LightKind, const float FogDist);// ステージにセットするライトの設定を行ないます

public:

	//変数の宣言
	int Stage_hsid[3];//ステージモデルのモデルIDを格納します
	int Wall_hsid[3];//壁モデルのモデルIDを格納します
	int Stage_ID;//ステージモデルの振り分けIDを格納します
	int Stage_Kind;//Stage_IDのステージモデルの種類を格納します
	int Stage_GndMode;//地面の判定する時にどのように処理するか識別します
	int Stage_GunTarget;//銃を地面に向ける時にどのように処理するか識別します

	int Light1_ID;//一つ目のライトの識別ID
	int Light2_ID;//二つ目のライトの識別ID

	//メンバクラスの宣言
	NaviRail Navi;

	//関数の宣言
	int LoadStage( const int StageID, const int StageKind, const int LightKind);//ステージをロードするための関数
	~Stage();//ステージのデコンストラクタ、マップなどを削除します。




};