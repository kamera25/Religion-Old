#pragma once
/*カメラに関することのヘッダファイル
//
*/

//プロトタイプ宣言
class Stage;

//カメラクラス
class Camera{
private:
		//変数の宣言
		int ShoulderComMode;// 肩内状態でのカメラモードを格納します(移動中:-1 キャラ右:0 キャラ左:1)
		int ShoulderComCounter;// 肩内状態での移動カウンター
		int ShoulderComMoveDeg;// 肩内状態でのカメラ移動に対する、移動方向指定変数(カメラを右へ:1 カメラを左へ:-1)

public:
		//変数の宣言
		int DummyModel;//ダミーモデルを格納するID変数


		//関数の宣言
		Camera();//カメラクラスのコンストラクタ、ダミーモデルのロードなどをします
		~Camera();//カメラクラスのデストラクタ、ダミーモデルなどを破棄します
		int CamShoulderGunBack( const int cha_hsid, const int Qid, const int bone, const float PC_Deg_XZ, const Stage *Stg);//肩打ち視点でのカメラを設定します

};