/*ここは、アイテム操作に関することのクラスです。
//主にバックパックやアイテム売買について書かれています。
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "citem_manipulate.h"//アイテム操作に関するヘッダファイル





/*簡易説明文を表示させる処理を行います*/
int Item_Manipulate::PutItemDescript( int ChoseItem, int ItemNumber){

	/*変数の初期化*/
	int ech = 0;//エラーチェック変数
	char WeaponDetail[64] = "";//武器分類の文字列配列
	POINT TextPos1;//説明文字の位置を格納する構造体
	E3DCOLOR4UC NormalColor = { 255,50,50,50};//文字の白色

	//文字の位置決め
	if( ( System::MousePos.x + 256 ) < 640 ){//もしアイテムバーを右端を超えなければ
			TextPos1.x = System::MousePos.x + 5;/**/TextPos1.y = System::MousePos.y + 45;//説明文字の位置はマウスポインタから算出
	}
	else{//超えれば
			TextPos1.x = System::MousePos.x + 5 - 256;/**/TextPos1.y = System::MousePos.y + 45;//説明文字の位置はマウスポインタから算出
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

			ech = E3DDrawTextByFontID( System::scid1, TextID[2], TextPos1, WeaponDetail, NormalColor);
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

			ech = E3DDrawTextByFontID( System::scid1, TextID[2], TextPos1, WeaponDetail, NormalColor);
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
	if( ( System::MousePos.x + 256 ) < 640 ){//もしアイテムバーを右端を超えなければ
			TextPos2.x = System::MousePos.x + 160;/**/TextPos2.y = System::MousePos.y + 5;//武器名文字の位置はマウスポインタから算出
			TextPos3.x = System::MousePos.x + 5;/**/TextPos3.y = System::MousePos.y + 5;//武器の種類の名前文字の位置はマウスポインタから算出
	}
	else{//超えれば
			TextPos2.x = System::MousePos.x + 160 - 256;/**/TextPos2.y = System::MousePos.y + 5;//武器名文字の位置はマウスポインタから算出
			TextPos3.x = System::MousePos.x + 5 - 256;/**/TextPos3.y = System::MousePos.y + 5;//武器の種類の名前文字の位置はマウスポインタから算出
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
			ech = E3DDrawTextByFontID( System::scid1, TextID[1], TextPos2, WeaponName, NormalColor);
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
			ech = E3DDrawTextByFontID( System::scid1, TextID[1], TextPos3, WeaponKind, NormalColor);
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

			ech = E3DDrawTextByFontID( System::scid1, TextID[1], TextPos3, WeaponKind, NormalColor);
			if(ech != 0){//エラーチェック
							_ASSERT(0);//エラーダイアログを表示
			}


	}




	return 0;
}
/*アイテム種類のメニューの表示・選択を行います*/
int Item_Manipulate::PutBackPackText( int *ChoseItem, int *ExitFlag){


		/* 変数の宣言 */
		int ech = 0;//エラーチェック変数
		int keyin[20];//キー情報配列を作成
		const char ItemKindName[5][12] = { "WEAPON" , "AMMO" , "RECOVERY" , "KEY" , "EQUIPMENT" };
		const char ItemKindDetal[5][50] = { "武器の操作をします" , "弾薬の操作をします" , "回復系品の操作をします" 
											, "重要品の操作をします" , "装備品の操作をします" };
		E3DCOLOR4UC NormalColor = { 255,255,255,255};//白色の選ばれていない色
		E3DCOLOR4UC SetColor = { 255,0,120,170};//青色の武器が選ばれている色
		E3DCOLOR4UC SelectColor = { 255,200,220,20};//黄色の選ばれている色
		POINT TextPos;//文字の位置を格納する構造体


		System::GetKeyData(keyin);

		//一番上のポーズメニュー
		TextPos.x = 440;/**/TextPos.y = 5;
		E3DDrawTextByFontID( System::scid1, TextID[0], TextPos, "バックパック", NormalColor);


		/* ////////////////////// //
		// アイテム種類文字を表示 //
		// ////////////////////// */
		TextPos.x = 100;/**/TextPos.y = 100;
		for( int i=0; i<5; i++){
				ech = E3DDrawTextByFontID( System::scid1, TextID[1], TextPos, ItemKindName[i], NormalColor);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
							return 1;//問題ありで終了
				};
				TextPos.y = TextPos.y + 40;//40ずつ下げる
		}


		/* //////////////////////////////////////// //
		// "バックアップを閉じる"の表示を行ないます //
		// //////////////////////////////////////// */

		TextPos.y = 320;//60下げる
		ech = E3DDrawTextByFontID( System::scid1, TextID[1], TextPos, "バックパックを閉じる", NormalColor);
		if(ech != 0 ){//エラーチェック
			_ASSERT( 0 );//エラーダイアログ
			return 1;//問題ありで終了
		};



		/* /////////////////////////////////////////  //
		// マウスが選択部にあるとき、文字を変更します //
		// /////////////////////////////////////////  */
		if((100< System::MousePos.x)&&(System::MousePos.x<250)){//マウスX座標がメニュー群の所にあるなら

			for( int i=0; i<5; i++){
				if((120 + (40 * i) < System::MousePos.y)&&( System::MousePos.y< 150 + (40 * i) )){
					
						/* マウスポインタが置いてある文字を光らせる */
						TextPos.x = 100;/**/TextPos.y = 100 + (40 * i);
						E3DDrawTextByFontID( System::scid1, TextID[1], TextPos, ItemKindName[i], SelectColor);//選択されている文字にする
						if(ech != 0){//エラーチェック
									_ASSERT(0);//エラーダイアログを表示
						};

						/* 下側にポインタを置いているところの説明を記述する */
						TextPos.x = 400;/**/TextPos.y = 330;
						E3DDrawTextByFontID( System::scid1, TextID[1], TextPos, ItemKindDetal[i], NormalColor);//説明が書かれている文字列を表示する
						if(ech != 0){//エラーチェック
									_ASSERT(0);//エラーダイアログを表示
						};

						/* クリックしたら選択アイテムを変える */
						if(keyin[9] == 1){
									*ChoseItem = i;//ループ脱出フラグをオンにする。
						}
				}
			}

			if((340< System::MousePos.y)&&( System::MousePos.y<370)){//マウス座標が「バックパックを閉じる」の上なら
					TextPos.x = 100;/**/TextPos.y = 320;
					E3DDrawTextByFontID( System::scid1, TextID[1], TextPos, "バックパックを閉じる", SelectColor);//選択されている文字にする
					if(ech != 0){//エラーチェック
						_ASSERT(0);//エラーダイアログを表示
					};

					TextPos.x = 400;/**/TextPos.y = 330;
					E3DDrawTextByFontID( System::scid1, TextID[1], TextPos, "ポーズメニューに戻ります", NormalColor);//説明が書かれている文字列を表示する
					if(ech != 0){//エラーチェック
						_ASSERT(0);//エラーダイアログを表示
					};

					if(keyin[9] == 1){//クリックしたら
						*ExitFlag = 1;//ループ脱出フラグをオンにする。
					}
			}	
		}



		/* //////////////////////////////////////////////////// //
		// 青色でどのアイテムの種類が選択されているを変更します //
		// //////////////////////////////////////////////////// */
		TextPos.x = 100;/**/TextPos.y = 100;
		for( int i=0; i<5; i++){
				if( *ChoseItem == i){
						ech = E3DDrawTextByFontID( System::scid1, TextID[1], TextPos, ItemKindName[i], SetColor);
						if(ech != 0 ){//エラーチェック
									_ASSERT( 0 );//エラーダイアログ
									return 1;//問題ありで終了
						};
				}
				TextPos.y = TextPos.y + 40;//40ずつ下げる
		}



	return 0;
}