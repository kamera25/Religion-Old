/*ここでは、生物クラスのキャラ・敵の関数を定義するクラスコードファイルです。
//特に向き移動関係で必要な関数が多く書かれています。
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "cstage.h"//ステージ関係のクラスヘッダファイル
#include "clive.h"//敵やキャラのクラスヘッダファイル
#include "c_batch_preparat.h"//描画に必要なクラスの宣言ヘッダファイル
#include <math.h>//数学計算を使うためのヘッダファイル
#include "cweapon.h"//武器に関することのクラスヘッダファイル
#include "cenemy.h"//敵クラスの宣言ヘッダファイル

int PlayerChara::TurnBackDir( int Qid, D3DXVECTOR3 WantDeg, int FixFlag){

	/* 初期化 */
	const D3DXVECTOR3 BASEVEC( 0.0, 0.0, -1.0);//向きの初期方向ベクトル

	int ech = 0;
	int MotionID = 0;
	int FrameNo = 0; 

	/* //////////////////////////// */
	/* キャラクタの向きを変更します */
	/* //////////////////////////// */


	/*キャラクターモデルの方向を初期化します*/
	ech = E3DRotateInit( Get_BodyModel());
	_ASSERT( ech != 1 );//エラーチェック

	/*「首付け根」部分のモーションはどうか調べます*/
	ech = E3DGetMotionFrameNoML( Get_BodyModel(), Get_Bone_ID(2), &MotionID, &FrameNo);
	_ASSERT( ech != 1 );//エラーチェック

	/*「首付け根」部分のクォータニオンを調べます*/
	ech = E3DGetCurrentBoneQ( Get_BodyModel(), Get_Bone_ID(2), 2, Qid);
	_ASSERT( ech != 1 );//エラーチェック

	/*向きたい方向への計算を行います*/
	ech = E3DLookAtQ( Qid, WantDeg, BASEVEC, 0, 0);
	_ASSERT( ech != 1 );//エラーチェック


	/*向きたい方向の修正を加えます*/
	if( FixFlag == 1) ech = E3DRotateQY( Qid, -Get_PC_Deg_XZ());
	_ASSERT( ech != 1 );//エラーチェック

	/*計算したクォーターニオンを代入します*/
	ech = E3DSetBoneQ( Get_BodyModel(), Get_Bone_ID(2), MotionID, FrameNo, Qid);
	_ASSERT( ech != 1 );//エラーチェック

	/*マルチレイヤーモーションの計算を行います*/
	ech = E3DCalcMLMotion( Get_BodyModel());
	_ASSERT( ech != 1 );//エラーチェック

	/*キャラクターを回転させます*/
	ech = E3DRotateY( Get_BodyModel(), Get_PC_Deg_XZ());
	_ASSERT( ech != 1 );//エラーチェック


	return 0;
}




/*肩射ち視点からの銃関連まとめ関数*/
int PlayerChara::ShoulderGunSys( Batch_Render *BatPre, int ScreenPos[2]){

	/*全体で使う変数の初期化*/
	int ech = 0;//エラー確認変数
	const D3DXVECTOR3 BaseVec( 0.0, 0.0, -1.0);//向きの初期方向ベクトル
	const D3DXVECTOR3 CameraUpVec( 0.0, 1.0, 0.0);//カメラの上部のベクトル

	/*キャラクターの位置を設定します*/
	int MotionID = 0;//MLから取得した現在の「首付け根」モーションID
	int FrameNo = 0;//MLから取得した現在の「首付け根」モーションが現在再生している番号
	static double Tm_DegQ_Y = 0.50;//ブレがある前の角度変数Y
	double Sin_Y  = 0.0;//Y座標サイン変数
	const double Sin_XZ = sin(4.8);//XZ座標サイン変数
	double Cos_Y  = 0.0;//Y座標コサイン変数
	const double Cos_XZ = cos(4.8);//XZ座標コサイン変数
	D3DXVECTOR3 TurnPos( 0.0, 0.0, 0.0);//向くべきYベクトル
	D3DXVECTOR3 StomachPos( 0.0, 0.0, 0.0);//「首つけ根」の座標
	D3DXVECTOR3 WantDeg( 0.0, 0.0, 0.0);//向きたい方向へのベクトル
//	D3DXVECTOR3 OriginPos( 0.0, 0.0, 0.0);//キャラクターをおくべき原点座標

	/**/
	//自分の向きを回転させます。
	/**/

	//最初に回転の計算します
	if(( Get_MyState() == 0) || ( (Get_MyState() == 2) && ( Get_AirOnPC() == 0))){//通常・空中ダッシュモードでなければ、以下取得せず
				Set_PC_Deg_XZ( Get_PC_Deg_XZ() + float(0.30*(System::MousePos.x - System::BeforeMousePos.x)) );
				Tm_DegQ_Y = Tm_DegQ_Y - 0.0020* float( System::MousePos.y - System::BeforeMousePos.y);
	}

	if( ( Get_MyState() == 3) || ( Get_MyState() == 4)){//よっこ飛びの時は
//				Tm_DegQ_Y = Tm_DegQ_Y - 0.0020* float( System::MousePos.y - System::BeforeMousePos.y + System::rewin.top);
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
	System::SetMouseCursol( 320, 240);//マウス座標を真ん中へ
	System::SetMouseBeforePos();//マウス座標を格納します

	Sin_Y = sin(Tm_DegQ_Y);//Y座標サインの取得
	Cos_Y = cos(Tm_DegQ_Y);//Y座標のコサインの取得
	TurnPos.x = float(Cos_XZ * Cos_Y * 2000);//向くべき方向のX座標
	TurnPos.y = float(Sin_Y * 2000);//向くべき方向のY座標を取得
	TurnPos.z = float(Sin_XZ * Cos_Y * 2000);//向くべき方向のZ座標を取得

	/* /////////////////////////////////////////////// */
	//次に座標を取得したりしてモデルのボーンを操作します
	/* /////////////////////////////////////////////// */

	WantDeg.x = float( TurnPos.x );//X座標の向く方向のベクトルを取得
	WantDeg.y = float( TurnPos.y );//Y座標の向く方向のベクトルを取得
	WantDeg.z = float( TurnPos.z );//Z座標の向く方向のベクトルを取得

	TurnBackDir( Get_Quaternion(3), WantDeg, 0);




	
	/*スプライトの位置を決めて終了します*/
	BatPre->Set_SpriteX( "Cursol1", 320 - 25.0f);//カーソルのX座標
	BatPre->Set_SpriteY( "Cursol1", 220 - 27.0f);//カーソルのY座標

	ScreenPos[0] = 320;/**/ScreenPos[1] = 220;

	return 0;
}

/*自分の向くべき方向を調節したり、射撃したりする関数*/
int PlayerChara::GunConflictTarget( int ScreenPosArray[2], Stage *Stg, NPC_Head *NPC_H){
    
	
	/* /////////////////////////////////////////////////////// */
	// キャラクターモデルを壁があれば壁に向ける
	// なければ銃の攻撃が届く範囲までの距離を取得し、そこに向ける
	/* /////////////////////////////////////////////////////// */

	/*変数の初期化*/
	int NowWpKind = 0;//今の武器の種類を取得します
	int ech = 0;//エラー確認変数
	int MotionID = 0;//MLから取得した現在の「首付け根」モーションID
	int FrameNo = 0;//MLから取得した現在の「首付け根」モーションが現在再生している番号
	vector<NPC_t>::iterator NearEnemyID;//一番近い敵キャラの識別番号
	int EnemyConflict = 0;//敵に当たった数の合計
	int Wall_HitResult = 0;//当たり判定モデルが壁に当たっているかどうか調べます
	int EneHitResult = 0;//敵が照準に入っているかの結果を入れます
	int HitResult = 0;//銃を向ける方向があるか入れますかの結果を入れます
	float NowWpRange = 0.0f;//今の武器の射程を代入します
	float Wall_HitDistance = 0.0f;//当たった面のところからの距離が代入されます
	float EneDistance = 0.0f;//当たった敵のところからの距離が代入されます
	float EneNearDistance = 0.0f;//当たっている一番近い敵の距離が代入されます
	D3DXVECTOR3 Wall_ReflectVec( 0.0, 0.0, 0.0);//地面の反射ベクトルの構造体
	D3DXVECTOR3 Wall_GunTargetPos( 0.0, 0.0, 0.0);//銃が向くべき座標
	D3DXVECTOR3 ReflectVec( 0.0, 0.0, 0.0);//反射ベクトルの構造体
	D3DXVECTOR3 GunTargetPos( 0.0, 0.0, 0.0);//銃が向くべき座標
	D3DXVECTOR3 WantVec( 0.0, 0.0, 0.0);//「首つけ根」の向きたい方向へのベクトル
	D3DXVECTOR3 BaseVec( 0.0, 0.0, -1.0);//向きの初期方向ベクトル
	D3DXVECTOR3 StomachPos( 0.0, 0.0, 0.0);//「首つけ根」の座標
	D3DXVECTOR3 MyPos1( 0.0, 0.0, 0.0);//最初自分の座標
	D3DXVECTOR3 OriginPos( 0.0, 0.0, 0.0);//キャラクターをおくべき原点座標
	D3DXVECTOR3 GarbageD3DVec( 0.0, 0.0, 0.0);//要らないXYZのデータの一次入れ
	POINT ScreenPos = { ScreenPosArray[0], ScreenPosArray[1]};//2Dスクリーン座標構造体
	vector<NPC_t>::iterator it;// イテレータ

	/* 装備をきちんとつけていれば */
	if( Get_Wp_equipment() != -1){

			NowWpKind = Wpn.Get_WeaponPointer( Get_Wp_equipment())->Get_Kind();
			NowWpRange = float( Wpn.Get_WeaponPointer( Get_Wp_equipment())->Get_Range() * 500);
			EneNearDistance = float(NowWpRange);
	}

	/* ///////////////////////////////////// */
	//壁の銃取得をどのようにするか指定します */
	/* //////////////////////////////////// */

	/*通常モード( モデル[0]から取得する )*/
	if( Stg->Stage_GunTarget == 0){
			ech = E3DPickFace( System::scid1, Stg->Stage_hsid[0], ScreenPos, NowWpRange, &Wall_HitResult, &HitResult, &Wall_GunTargetPos, &Wall_ReflectVec, &Wall_HitDistance);
			_ASSERT( ech != 1 );//エラーチェック
	}


	if(Get_Wp_equipment() != -1){//装備をきちんとつけていれば
		/*武器の種類が、ハンドガンであれば*/
		switch(NowWpKind){
				case 0:
				case 2:
				case 3:
				case 4:
				{
						/*敵にあたっていないかチェックします*/
						for( it = NPC_H->Get_NPC_begin(); it != NPC_H->NPC_endit(); it++){//エネミーの数だけ

											ech = E3DPickFace( System::scid1, (*it).NPC_Mdl->Get_BodyModel(), ScreenPos, NowWpRange, &EneHitResult
																, &EneHitResult, &GarbageD3DVec, &GarbageD3DVec, &EneDistance);
											_ASSERT( ech != 1 );//エラーチェック
											if( (EneHitResult != 0) && ( EneDistance < EneNearDistance) ){
														EneNearDistance = EneDistance;//一番近い敵の距離に更新します
														NearEnemyID = it;//一番近いモデル番号を入れます
														EnemyConflict = 1;//近い敵がいることを代入します
														HitResult = 1;//ヒットフラグを1にする
											}
						}

						if( (EnemyConflict == 1) && ( Wall_HitDistance > EneNearDistance) ){//敵に銃先を向ける
								ech = E3DPickFace( System::scid1, (*NearEnemyID).NPC_Mdl->Get_BodyModel(), ScreenPos, NowWpRange, &EneHitResult, &EneHitResult, &GunTargetPos, &ReflectVec, &EneDistance);
								_ASSERT( ech != 1 );//エラーチェック
						}
						else{//壁に銃先を向ける
								GunTargetPos = Wall_GunTargetPos;
								ReflectVec = Wall_ReflectVec;
						}
			

						/*壁に当たっていれば*/
						if( HitResult != -1){

								/*「首付け根」部分の座標を取得します*/
								ech = E3DGetCurrentBonePos( Get_BodyModel(), Get_Bone_ID(2), 1, &StomachPos);
								_ASSERT( ech != 1 );//エラーチェック

								WantVec.x =  GunTargetPos.x - StomachPos.x;
								WantVec.y =  GunTargetPos.y - StomachPos.y;
								WantVec.z =  GunTargetPos.z - StomachPos.z;

								TurnBackDir( Get_Quaternion(5), WantVec, 1);




						}
				}
		}
	}
	else{
			/* 武器を持ってないときの処理とかする予定 */
	}


	return 0;
}