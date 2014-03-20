#pragma once
/*カメラに関することのヘッダファイル
//
*/


//カメラクラス
class Camera{

public:
		//変数の宣言
		int DummyModel;//ダミーモデルを格納するID変数


		//関数の宣言
		Camera();//カメラクラスのコンストラクタ、ダミーモデルのロードなどをします
		~Camera();//カメラクラスのデストラクタ、ダミーモデルなどを破棄します
		int CamShoulderGunBack( int Qid, float PC_Deg_XZ, D3DXVECTOR3 StomachPos);//肩打ち視点でのカメラを設定します

};