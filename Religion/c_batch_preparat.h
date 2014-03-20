#pragma once
/*ここでは、モデルやスプライトの描画に必要な情報を収集、また描画で必要な
//関数を自動的に実行することができるようにするためのクラスヘッダファイル
*/
#include <vector>

using namespace std;


//プロトタイプ宣言
class PlayerChara;
class Stage;
class NPC_Head;
class Camera;
class Weapon;

struct Sprite{// スプライト構造体
	int ID;
	bool ViewFlag;// 表示フラグ
	bool DeleteFromBRFlag;// Batch_Renderからスプライトを消すかのフラグ
	float MagX;// スプライトの倍率X
	float MagY;// スプライトの倍率Y
	float X;// スプライト位置X
	float Y;// スプライト位置Y
	float Z;// スプライト奥行Z
	char Name[20];// 識別される名前
};

struct Model{// モデル構造体
	int ID;
	bool ViewFlag;
	char Name[20];// 識別される名前
};


/*描画準備で必要な変数などを宣言するクラス*/
class Batch_Render{	

private:

	/* モデルデータの配列を宣言します */
	vector<Model> Mdl;

	/*スプライト関係の変数を宣言します*/
	vector<Sprite> Spt;

	int BumpMapFlag;// バンプマップを表示するかどうかのフラグ変数
	int ShadowFlag;// 影を表示するかどうかのフラグ変数

	/* 影に関係する変数 */
	int ShadowScid;// 影のスワップチェイン識別変数
	int ShadowTexture;// 影をレンダリングするテクスチャ識別変数


public:



	//関数の宣言
	Batch_Render( const PlayerChara *PcC, const Stage *StgC, NPC_Head *NPCC, 
					const Camera *Cam);//コンストラクタ、初期化をします
	~Batch_Render();//デストラクタ、スプライトを削除します

	int BatchRender( const int SceneEndFlg) ;//今までのデータをまとめて描画するための関数
	int BatchChkInView();//今までのデータをまとめて視野角内チェックするための関数
	int BacthGunTrade( int Wp_equipment);//武器を交換した後、チェックと描画するモデルを変更する関数
	int BatchReset( const PlayerChara *PcC, const Stage *StgC, NPC_Head *NPCC,
					const Camera *Cam);//構築していた、まとめデータを再構築する
	int BatchBeforePos();//一つ前の座標をまとめて保存するための関数
	int BatchFont( const int SceneEndFlg, const PlayerChara *PcC);//文字を描画することや設定をしたりする関数
	int BatchEnableBumpMap( const int BumpFlug);//バンプマップを有効/無効にします
	int BatchGetBumpMapStatus() const;//バンプマップ変数の取得を行ないます
	int BatchCreateShadow();// 影を作成するために関係する処理を行ないます
	int Batch_Present();// バックバッファの内容を、プライマリバッファに転送します
	int Batch_BillBoard( const int SceneEndFlg);// ビルボードの描画処理を行います。
	int RenderFont( char *Str, float Posx, float Posy, float MagScl, E3DCOLOR4UC Color);// 英文字を描画します

	/* モデル関係の関数 */
	int	SetModel( const int ID, const bool ViewFlag);
	int SetModel_AddName( const int ID, const char *Name, const bool ViewFlag);
	// vector<Model>::iterator SearchModelFromName( const char *ObjName);
	int Batch_Render::SearchModelFromName( const char *ObjName, vector<Model>::iterator *it);
	int SetModel_ViewFlag( const char *Name, const bool ViewFlag);

	/* スプライト関係の関数 */
	int LoadSprite( const char *ObjPath, const float MagX, const float MagY, const float X, const float Y, const float Z, const int DeleteFromBRFlag);
	int LoadSprite_AddName( const char *ObjPath, const char *Name, const float MagX, const float MagY, const float X, const float Y, const float Z, const int DeleteFromBRFlag);
	int LoadSpriteFromID( const int ID, const char *Name, const float MagX, const float MagY, const float X, const float Y, const float Z, const int DeleteFromBRFlag);
	int SetSpriteAlpha( const char *Name, E3DCOLOR4UC AlfaColor);
	int Set_SpriteMagX( const char *ObjName, const float Value);
	int Set_SpriteMagY( const char *ObjName, const float Value);
	int Set_SpriteX( const char *ObjName, const float Value);
	int Set_SpriteY( const char *ObjName, const float Value);
	int Set_ViewFlag( const char *ObjName, const bool Value);
	//vector<Sprite>::iterator Batch_Render::SearchSpriteFromName( const char *ObjName);
	int SearchSpriteFromName( const char *ObjName, vector<Sprite>::iterator *it);

	int BatchSpriteRender( const int SceneEndFlg);//まとめられたスプライトをレンダリングするための関数
	int BatchSpriteSet( const PlayerChara *PcC);//最初にロードしたスプライトの倍率や描画指定するための関数

};