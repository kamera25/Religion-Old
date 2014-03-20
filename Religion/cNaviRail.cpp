/* ナビレールクラス系コードの一部である、この"cNaviRail.cpp"コードは
// キャラクタやカメラを制御する要になる"ナビライン拡張"関係のことが書かれています。
/* /////////////////////////////////////////////////////////////////////////// */
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル

#include "cnavirail.h"//ナビレールに関するヘッダファイル

/* NaviRailクラスのコンストラクタ*/
NaviRail::NaviRail(){

	/* 変数の宣言&初期化 */
	int ech = 0;// エラー確認用変数


	// ナビラインを作成します
	for( int i=0; i<10; i++){
			ech = E3DCreateNaviLine( &NaviLineID[i]); 
			if( ech != 0){
						_ASSERT( 0 );
						return;
			};
	}

	// ナビライン利用変数をオフにします
	NaviRailAvailable = 0;


	return;
}
/* NaviRailクラスのデストラクタ*/
NaviRail::~NaviRail(){

	/* 変数の宣言&初期化 */
	int ech = 0;// エラーチェック変数の初期化

	//ナビラインを削除します
	for( int i=0; i<10; i++){
			ech = E3DDestroyNaviLine( NaviLineID[i]);
			if( ech != 0){
						_ASSERT( 0 );
			};
	}


	return;
}
/* ナビラインにナビポイントを追加します */
int NaviRail::AddNaviPointToStage( const int NaviPointEdge, const int NaviLineNumber, const float NaviPointPosx,
									const float NaviPointPosy, const float NaviPointPosz)
{
	/* 変数の宣言&初期化 */
	int ech = 0;// エラーチェック変数の初期化
	int NaviPoint = 0;//新しく追加したナビポイントのIDを代入
	D3DXVECTOR3 NaviPointPos( NaviPointPosx, NaviPointPosy, NaviPointPosz);//ナビポイント座標を代入する構造体


	/* /////////////////////////////////// */
	// ナビライン上にナビポイントを設置します
	/* /////////////////////////////////// */

	ech = E3DAddNaviPoint( NaviLineID[NaviLineNumber], NaviPointEdge, &NaviPoint);//ナビポイントを追加
	if( ech != 0){
				_ASSERT( 0 );
				return 1;
	};
	ech = E3DSetNaviPointPos( NaviLineID[NaviLineNumber], NaviPoint, NaviPointPos);//ナビポイントの座標を指定
	if( ech != 0){
				_ASSERT( 0 );
				return 1;
	};



	return NaviPoint;
}
/* ナビラインの使用を有効/無効にします */
int NaviRail::NaviRailOnOffSwitch( const int RailOnOrOff){

	NaviRailAvailable = RailOnOrOff;

	return 0;
}
/* NaviRailAvailableを取得します */
int NaviRail::Get_NaviRailAvailable() const{

	return NaviRailAvailable;
}
/* ナビレールによってキャラクターをコントロールします */
int NaviRail::PCControlByNaviRail( const int ModelID, int *TargetNaviPointID, int NaviLineID) const{

	/* 変数の初期化&宣言 */
	D3DXQUATERNION NewhsidQ;//移動後のクォータニオンを代入します
	D3DXVECTOR3 NewhsidPos( 0.0, 0.0, 0.0);//移動後の座標を代入します
	int ech = 0;// エラーチェック変数

	ech = E3DControlByNaviLine( ModelID, NaviLineID, 4, 1, 0, 10.0f, 30.0f, 100.0f, &NewhsidPos, &NewhsidQ, TargetNaviPointID );
	_ASSERT( ech != 1 );//エラーチェック
	ech = E3DSetPos( ModelID, NewhsidPos);
	_ASSERT( ech != 1 );//エラーチェック
	ech = E3DSetDirQ( ModelID, NewhsidQ);
	_ASSERT( ech != 1 );//エラーチェック


	return 0;
}
/* ナビポイントによってモデルを設置します */
int NaviRail::SetPosByNaviPoint( const int ModelID, const int NaviLine, const int NaviPoint){

	/* 変数の宣言&初期化 */
	int ech = 0;// エラーチェック変数の初期化
	D3DXVECTOR3 NaviPointPos( 0.0f, 0.0f, 0.0f);//ナビポイント座標を代入する構造体

	// ナビポイントの座標を取得します
	ech = E3DGetNaviPointPos( NaviLine, NaviPoint, &NaviPointPos);
	if( ech != 0){
				_ASSERT( 0 );
				return 1;
	};

	// 座標にモデルを設置します
	ech = E3DSetPos( ModelID, NaviPointPos);
	if( ech != 0){
				_ASSERT( 0 );
				return 1;
	};


	return 0;
}

/* ナビレールの乗換ポイントを作成します */
int NaviRail::NRGivenTransfarFromAToB( const int CreateOnNaviLine, const int ANaviLine, const int ANaviPoint, 
							const int BNaviLine, const int BNaviPoint)
{

	/* 変数の宣言&初期化 */
	int ech = 0;// エラーチェック変数の初期化
	int NaviPoint = 0;//新しく追加したナビポイントのIDを代入
	D3DXVECTOR3 NaviPointPos( 0.0f, 0.0f, 0.0f);//ナビポイント座標を代入する構造体


	/* /////////////////////////////////// */
	// ナビライン上にナビポイントを設置します
	/* /////////////////////////////////// */


	/* 後ろナビポイントの設定を行ないます */
	ech = E3DAddNaviPoint( NaviLineID[CreateOnNaviLine], -2, &NaviPoint);//ナビポイントを追加
	if( ech != 0){
				_ASSERT( 0 );
				return 1;
	};
	ech = E3DGetNaviPointPos( NaviLineID[ANaviLine], ANaviPoint, &NaviPointPos);// From座標の取得を行ないます
	if( ech != 0){
				_ASSERT( 0 );
				return 1;
	};
	ech = E3DSetNaviPointPos( NaviLineID[CreateOnNaviLine], NaviPoint, NaviPointPos);//ナビポイントの座標を指定
	if( ech != 0){
				_ASSERT( 0 );
				return 1;
	};


	/* 前ナビポイントの設定を行ないます */
	ech = E3DAddNaviPoint( NaviLineID[CreateOnNaviLine], -1, &NaviPoint);//ナビポイントを追加
	if( ech != 0){
				_ASSERT( 0 );
				return 1;
	};
	ech = E3DGetNaviPointPos( NaviLineID[BNaviLine], BNaviPoint, &NaviPointPos);// From座標の取得を行ないます
	if( ech != 0){
				_ASSERT( 0 );
				return 1;
	};
	ech = E3DSetNaviPointPos( NaviLineID[CreateOnNaviLine], NaviPoint, NaviPointPos);//ナビポイントの座標を指定
	if( ech != 0){
				_ASSERT( 0 );
				return 1;
	};




	return 0;
}