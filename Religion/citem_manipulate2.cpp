/*ここは、アイテム操作に関することのクラスです。
//主にバックパックやアイテム売買について書かれています。
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "citem_manipulate.h"//アイテム操作に関するヘッダファイル

//ここにグローバル変数を宣言
extern System *sys;//システムクラスを指す、クラスのポインタ


/*簡易説明文を表示させる処理を行います*/
int Item_Manipulate::PutItemDescript( int ChoseItem, int ItemNumber){

	/*変数の初期化*/
	int ech = 0;//エラーチェック変数
	char WeaponDetail[64] = "";//武器分類の文字列配列
	POINT TextPos1;//説明文字の位置を格納する構造体
	E3DCOLOR4UC NormalColor = { 255,50,50,50};//文字の白色

	//文字の位置決め
	if( ( sys->MousePos.x + 256 ) < 640 ){//もしアイテムバーを右端を超えなければ
			TextPos1.x = sys->MousePos.x + 5;/**/TextPos1.y = sys->MousePos.y + 45;//説明文字の位置はマウスポインタから算出
	}
	else{//超えれば
			TextPos1.x = sys->MousePos.x + 5 - 256;/**/TextPos1.y = sys->MousePos.y + 45;//説明文字の位置はマウスポインタから算出
	}

	/**/
	//アイテムの種類によって分岐
	/**/

	if(ChoseItem == 0){//操作中のアイテムが「武器」なら
			if(BackPack_Weapon[ItemNumber][1] == 1){//武器がハンドガン系
					if(BackPack_Weapon[ItemNumber][2] == 0){//M1911
							wsprintf( WeaponDetail, "米国製の扱いやすい45口径拳銃");//武器説明を代入します
					}
					if(BackPack_Weapon[ItemNumber][2] == 2){//Glock95
							wsprintf( WeaponDetail, "ポリマーフレームのフルオート拳銃");//武器説明を代入します
					}
					if(BackPack_Weapon[ItemNumber][2] == 3){//M92F
							wsprintf( WeaponDetail, "扱いやすい米軍の正式採用拳銃");//武器説明を代入します
					}
			}
			else if(BackPack_Weapon[ItemNumber][1] == 4){//武器がアサルトライフル系
					if(BackPack_Weapon[ItemNumber][2] == 0){//M4
							wsprintf( WeaponDetail, "光学サイトを搭載したアメリカを代表する小銃");//武器説明を代入します
					}
			}
			else if( BackPack_Weapon[ItemNumber][1] == -1){//武器なしなら
							wsprintf( WeaponDetail, "武器がありません");//武器説明を代入します

			}

			/**/
			////
			/**/

			ech = E3DDrawTextByFontID( sys->scid1, TextID[2], TextPos1, WeaponDetail, NormalColor);
			if(ech != 0){//エラーチェック
						_ASSERT(0);//エラーダイアログを表示
			}
	}

	if(ChoseItem == 1){//操作中のアイテムが「弾薬」なら

			if( BackPack_Ammo[ItemNumber][1] == 0){//.45ACP
						wsprintf( WeaponDetail, "米国製大型自動拳銃用の実包");//武器説明を代入します
			}
			if( BackPack_Ammo[ItemNumber][1] == -1){//弾薬なしなら
							wsprintf( WeaponDetail, "弾薬がありません");//武器説明を代入します

			}

			ech = E3DDrawTextByFontID( sys->scid1, TextID[2], TextPos1, WeaponDetail, NormalColor);
			if(ech != 0){//エラーチェック
						_ASSERT(0);//エラーダイアログを表示
			}

	}

	return 0;
}
/*武器アイテム名を表示させる処理を行います*/
int Item_Manipulate::PutItemName( int ChoseItem, int ItemNumber){

	/*変数の初期化*/
	int ech = 0;//エラーチェック変数
	char WeaponName[32] = "";//武器名前の文字列配列
	char WeaponKind[32] = "";//武器分類の文字列配列
	POINT TextPos2;//武器名文字の位置を格納する構造体
	POINT TextPos3;//武器の種類の名前文字の位置を格納する構造体
	E3DCOLOR4UC NormalColor = { 255,50,50,50};//文字の白色

	//文字の位置決め
	if( ( sys->MousePos.x + 256 ) < 640 ){//もしアイテムバーを右端を超えなければ
			TextPos2.x = sys->MousePos.x + 160;/**/TextPos2.y = sys->MousePos.y + 5;//武器名文字の位置はマウスポインタから算出
			TextPos3.x = sys->MousePos.x + 5;/**/TextPos3.y = sys->MousePos.y + 5;//武器の種類の名前文字の位置はマウスポインタから算出
	}
	else{//超えれば
			TextPos2.x = sys->MousePos.x + 160 - 256;/**/TextPos2.y = sys->MousePos.y + 5;//武器名文字の位置はマウスポインタから算出
			TextPos3.x = sys->MousePos.x + 5 - 256;/**/TextPos3.y = sys->MousePos.y + 5;//武器の種類の名前文字の位置はマウスポインタから算出
	}


	/**/
	//アイテムの種類によって分岐
	/**/

	if(ChoseItem == 0){//操作中のアイテムが「武器」なら
			if(BackPack_Weapon[ItemNumber][1] == 1){//武器がハンドガン系
					if(BackPack_Weapon[ItemNumber][2] == 0){//M1911
							wsprintf( WeaponName, "M1911");//武器名前を代入します
					}
					if(BackPack_Weapon[ItemNumber][2] == 2){//Glock95
							wsprintf( WeaponName, "Glock95");//武器名前を代入します
					}
					if(BackPack_Weapon[ItemNumber][2] == 3){//M92F
							wsprintf( WeaponName, "M92F");//武器名前を代入します
					}
			}
			else if(BackPack_Weapon[ItemNumber][1] == 4){//武器がアサルトライフル系
					if(BackPack_Weapon[ItemNumber][2] == 0){//M4
							wsprintf( WeaponName, "M4");//武器名前を代入します
					}
			}
			else if( BackPack_Weapon[ItemNumber][1] == -1){
							wsprintf( WeaponName, "EMPTY");//武器名前を代入します

			}

			//武器名前の表示をさせます
			ech = E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos2, WeaponName, NormalColor);
			if(ech != 0){//エラーチェック
						_ASSERT(0);//エラーダイアログを表示
			}

		/**//////////
		/**////////


			if(ItemNumber == 0){//マウスがメインウェポンの上にあれば
					wsprintf( WeaponKind, "MAINWEAPON");//武器名前を代入します
			}
			if(ItemNumber == 1){//マウスがサブウェポンの上にあれば
					wsprintf( WeaponKind, "SUBWEAPON");//武器名前を代入します
			}
			if(ItemNumber == 2){//マウスがグレネード系の上にあれば
					wsprintf( WeaponKind, "GRENADE");//武器名前を代入します

			}
			if(ItemNumber == 3){//マウスが修理が必要な武器の上にあれば
					wsprintf( WeaponKind, "NEED REPAIR");//武器名前を代入します
			}


			//武器分類を表示させます
			ech = E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos3, WeaponKind, NormalColor);
			if(ech != 0){//エラーチェック
						_ASSERT(0);//エラーダイアログを表示
			}


	}
	if(ChoseItem == 1){//操作中のアイテムが「弾薬」なら

			if( BackPack_Ammo[ItemNumber][1] == 0){//.45ACP
				wsprintf( WeaponKind, ".45ACP");//武器名前を代入します
			}
			else if( BackPack_Ammo[ItemNumber][1] == -1){
							wsprintf( WeaponKind, "EMPTY");//武器名前を代入します

			}

			ech = E3DDrawTextByFontID( sys->scid1, TextID[1], TextPos3, WeaponKind, NormalColor);
			if(ech != 0){//エラーチェック
							_ASSERT(0);//エラーダイアログを表示
			}


	}




	return 0;
}