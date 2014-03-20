/*ここでは、生物クラスのキャラ・敵の関数を定義するクラスコードファイルです。
//特に肩打ちモード時に関係する時に必要な関数が多く書かれています。
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ
#include "cstage.h"//ステージ関係のクラスヘッダファイル
#include "clive.h"//敵やキャラのクラスヘッダファイル
#include "c_batch_preparat.h"//描画に必要なクラスの宣言ヘッダファイル
#include <math.h>//数学計算を使うためのヘッダファイル
#include "cweapon.h"//武器に関することのクラスヘッダファイル





/*肩射ち視点からの銃関連まとめ関数*/
int PlayerChara::ShoulderGunSys( Batch_Preparat *BatPre, int ScreenPos[2]){

	/*全体で使う変数の初期化*/
	int ech = 0;//エラー確認変数
	const D3DXVECTOR3 BaseVec( 0.0, 0.0, -1.0);//向きの初期方向ベクトル
	const D3DXVECTOR3 CameraUpVec( 0.0, 1.0, 0.0);//カメラの上部のベクトル

	/*キャラクターの位置を設定します*/
	int MotionID = 0;//MLから取得した現在の「首付け根」モーションID
	int FrameNo = 0;//MLから取得した現在の「首付け根」モーションが現在再生している番号
	static double Tm_DegQ_Y = 0.50;//ブレがある前の角度変数Y
	double Sin_Y = 0.0;//Y座標サイン変数
	double Sin_XZ = 0.0;//XZ座標サイン変数
	double Cos_Y = 0.0;//Y座標コサイン変数
	double Cos_XZ = 0.0;//XZ座標コサイン変数
	D3DXVECTOR3 TurnPos( 0.0, 0.0, 0.0);//向くべきYベクトル
	D3DXVECTOR3 StomachPos( 0.0, 0.0, 0.0);//「首つけ根」の座標
	D3DXVECTOR3 WantDeg( 0.0, 0.0, 0.0);//向きたい方向へのベクトル
	D3DXVECTOR3 OriginPos( 0.0, 0.0, 0.0);//キャラクターをおくべき原点座標
	D3DXVECTOR3 MyPos1( 0.0, 0.0, 0.0);//最初自分の座標
	D3DXVECTOR3 MyPos2( 0.0, 0.0, 0.0);//次の自分の座標

	/**/
	//自分の向きを回転させます。
	/**/

	//最初に回転の計算します
	if(( Get_MyState() == 0) || ( (Get_MyState() == 2) && ( Get_AirOnPC() == 0))){//通常・空中ダッシュモードでなければ、以下取得せず
				Set_PC_Deg_XZ( Get_PC_Deg_XZ() + float(0.30*(System::MousePos.x - (System::BeforeMousePos.x - System::rewin.left))) );
				Tm_DegQ_Y = Tm_DegQ_Y - 0.0020* float( System::MousePos.y - System::BeforeMousePos.y + System::rewin.top);
	}

	if( ( Get_MyState() == 3) || ( Get_MyState() == 4)){//よっこ飛びの時は
				Tm_DegQ_Y = Tm_DegQ_Y - 0.0020* float( System::MousePos.y - System::BeforeMousePos.y + System::rewin.top);
	}

	if( Get_PC_Deg_XZ() < 0){
				Set_PC_Deg_XZ( Get_PC_Deg_XZ() + 360);
	}
	if( 360 < Get_PC_Deg_XZ()){
				Set_PC_Deg_XZ( Get_PC_Deg_XZ() - 360);
	}
	if(Tm_DegQ_Y> 0.9){
				Tm_DegQ_Y = 0.9;
	}
	if(Tm_DegQ_Y< -0.6){
				Tm_DegQ_Y = -0.6;
	}

	SetCursorPos( System::rewin.left + 320, System::rewin.top + 240);//マウス座標を真ん中へ
	GetCursorPos( &System::BeforeMousePos);//マウス座標を格納します

	Cos_XZ = cos(4.8);//XZ座標コサインの取得
	Sin_XZ = sin(4.8);//XZ座標サインの取得
	Sin_Y = sin(Tm_DegQ_Y);//Y座標サインの取得
	Cos_Y = cos(Tm_DegQ_Y);//Y座標のコサインの取得
	TurnPos.x = float(Cos_XZ * Cos_Y * 2000);//向くべき方向のX座標
	TurnPos.y = float(Sin_Y * 2000);//向くべき方向のY座標を取得
	TurnPos.z = float(Sin_XZ * Cos_Y * 2000);//向くべき方向のZ座標を取得

	/**/
	//次に座標を取得したりしてモデルのボーンを操作します
	/**/

	/*キャラクターモデルの方向を初期化します*/
	ech = E3DRotateInit( Get_BodyModel());
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/*座標を取得する*/
	ech = E3DGetPos( Get_BodyModel(), &MyPos1);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/*キャラクターモデルの「首つけ根」の座標を取得します*/
	ech = E3DGetCurrentBonePos( Get_BodyModel(), Get_Bone_ID(2), 1, &StomachPos);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	MyPos2.x = StomachPos.x * -1;
	MyPos2.y = StomachPos.y * -1;
	MyPos2.z = StomachPos.z * -1;

	/*座標を原点にする*/
	ech = E3DSetPos( Get_BodyModel(), MyPos2);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/*キャラクターモデルの「首つけ根」の座標を取得します*/
	ech = E3DGetCurrentBonePos( Get_BodyModel(), Get_Bone_ID(2), 1, &StomachPos);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	WantDeg.x = float( TurnPos.x - 0);//X座標の向く方向のベクトルを取得
	WantDeg.y = float( TurnPos.y - 0);//Y座標の向く方向のベクトルを取得
	WantDeg.z = float( TurnPos.z - 0);//Z座標の向く方向のベクトルを取得

	/*「首付け根」部分のモーションはどうか調べます*/
	ech = E3DGetMotionFrameNoML( Get_BodyModel(), Get_Bone_ID(2), &MotionID, &FrameNo);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/*「首付け根」部分のクォータニオンを調べます*/
	ech = E3DGetCurrentBoneQ( Get_BodyModel(), Get_Bone_ID(2), 2, Get_Quaternion(3));
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/*向きたい方向への計算を行います*/
	ech = E3DLookAtQ( Get_Quaternion(3), WantDeg, BaseVec, 0, 2);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/*計算したクォーターニオンを代入します*/
	ech = E3DSetBoneQ( Get_BodyModel(), Get_Bone_ID(2), MotionID, FrameNo, Get_Quaternion(3));
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/*マルチレイヤーモーションの計算を行います*/
	ech = E3DCalcMLMotion( Get_BodyModel());
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/*本来の自分の座標に戻す*/
	ech = E3DSetPos( Get_BodyModel(), MyPos1);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	/*キャラクターを回転させます*/
	ech = E3DRotateY( Get_BodyModel(), Get_PC_Deg_XZ());
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	
	/*スプライトの位置を決めて終了します*/
	BatPre->SpriteData[0][2] = 320 - 16.0f;//カーソルのX座標
	BatPre->SpriteData[0][3] = 220 - 18.0f;//カーソルのY座標

	ScreenPos[0] = 320;/**/ScreenPos[1] = 220;

	return 0;
}

