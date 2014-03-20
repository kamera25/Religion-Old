#pragma once
/*武器クラスのキャラをするヘッダファイル。
//
*/

//プロトタイプ宣言
class Enemy;
class PlayerChara;

/*武器クラスに関することを記述*/
class Weapon{

private:

	/*変数の宣言*/

	/*説明*/
	// 最初の要素には武器の種類による場合分けがされています  [0]メインウェポン [1]サブウェポン [2]グレネード
	int WeaponModel[3];// 武器モデル
	int WeaponSprite[3];// 武器のスプライト画像 

	// 先頭要素は同上  WeaponData変数には以下のようにデータが入ってます
	// [0]武器の種類 [1]武器のナンバー [2]弾薬の最大値
	// [3]マガジンの最大値 [4]射程能力 [5]威力 [6]次撃てるまでの時間
	// [7]連射性のある武器か 
	int WeaponData[3][8];

	// ゲーム中の武器情報を入れます	
	// [0]弾薬数　[1]マガジン数
	int WeaponDataWhileGame[3][6];

	// ボーン情報を格納します
	// [0]銃口手前 [1]銃口先 [2]飛弾先 [3]銃弾丸ストック [4]当たり判定モデル一番先 [5]当たり判定モデル一番手前
	int WeaponBone[3][6];
	int WeaponOtherModel[3][4];

	// 武器のエフェクトを格納します [0]マズルフラッシュ
	int WeaponEffect[3][2];

	// 武器のマズルフラッシュライトを設定
	int WeaponMuzzleLight[3];

	// 音声データを格納します
	int WeaponSoundEfeect[3][6];

	// 武器の連射カウンタ
	int WeaponRapidFire;

	// 武器を撃っているかのフラグ
	int WeaponFireFlag;

	/*関数の宣言*/
	int GunLoad_Assault( int Selectkind, int Wpno);//アサルトライフルの情報をロードする関数
	int GunLoad_Hand( int Selectkind, int Wpno);//ハンドガンの情報をロードする関数
	int GunLoad_Data( int Selectkind, int Wpkind, int Wpno);//武器に関する情報を格納する関数

public:

	/*関数の宣言*/
	int GunLoad( int Selectkind, int Wpkind, int Wpno);//武器をロードするための関数
	int GetWeaponModelID( int ItemNumber, int DataNumber);//モデルIDの取得を行う関数
	int GetWeaponData( int ItemNumber, int DataNumber);//モデルの詳細データを取得します
	int GetWeaponDataWhileGame( int ItemNumber, int DataNumber);//ゲーム中の武器の詳細データを取得します
	int GetSpriteData( int ItemNumber);//武器スプライトを取得します
	int GetWeaponRapidFire();//武器の連射カウンタを取得します
	int SetInitWeaponData();//武器の状態を初期化し、銃弾やマガジンを一杯にする関数
	int TreatmentWhileGame( int Wp_equipment);// ゲーム中の銃の操作に関することをする関数
	int PlayWeaponSound( int Wp_equipment, int PlayNo, float MuzzlePosArray[3]);// *武器の音声を再生する関数(3DSE専用)
	int ChkWeaponLaunch( int Wp_equipment);//武器を発射したかどうかの確認を行います
	int GetWeaponFireFlag();//武器発射フラグ変数を取得する関数
	int AttackEnemy( Enemy *Ene, PlayerChara *PC, int ScreenPosArray[2]);//ゲーム中の敵とのあたり&攻撃判定を行います
	Weapon();//コンストラクタ、変数の初期化を行います
	~Weapon();//デストラクタ、モデルの破棄等を行います




};