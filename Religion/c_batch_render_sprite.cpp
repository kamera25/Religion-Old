/*ここでは、モデルやスプライトの描画に必要な情報を収集、また描画で必要な
//関数を自動的に実行することができるようにするためのクラスコードファイル
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "c_batch_preparat.h"//描画に必要なクラスの宣言ヘッダファイル
#include "clive.h"//敵やキャラの宣言ヘッダファイル
#include "cweapon.h"//武器に関することのクラスヘッダファイル


/*最初にロードしたスプライトの倍率や描画指定*/
int Batch_Render::BatchSpriteSet( const PlayerChara *PcC){

	/* 変数の初期化&宣言 */
	int NowEqip = PcC->Get_Wp_equipment();

	/*スプライトの倍率を変更します*/

	//HPバーについての倍率代入
	SpriteData[3][0] = float( PcC->Get_HP()) / float( PcC->Get_MaxHP()) * 100.0f;

	//スタミナバーについての倍率代入
	SpriteData[4][0] = float( PcC->Get_Stamina()) / (PcC->Get_MaxStamina()) * 100.0f;

	if( PcC->Get_Wp_equipment() == -1){//武器なしなら

				//銃の弾薬を無表示に
				SpriteData[5][0] = 0.0f;

				//銃のマガジンを無表示に
				SpriteData[6][0] = 0.0f;

				//スプライトを表示しないように
				SpriteIDs[9] = 0;

	}
	else{//武器ありなら
				//銃の弾薬についての倍率変換
				SpriteData[5][0] = float( PcC->Wpn.Get_WeaponPointer( NowEqip)->Get_NowAmmo()) / float(PcC->Wpn.Get_WeaponPointer( NowEqip)->Get_Ammo()) * 100.0f;

				//銃のマガジンについての倍率変換
				SpriteData[6][0] = float( PcC->Wpn.Get_WeaponPointer( NowEqip)->Get_NowMagazine()) / float(PcC->Wpn.Get_WeaponPointer( NowEqip)->Get_Magazine() ) * 100.0f;

				//表示すべき画像をSpriteIDsに代入する
				SpriteIDs[9] = PcC->Wpn.Get_WeaponPointer( NowEqip)->Get_Sprite();
	}
	
	

	return 0;
}

