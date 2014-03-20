/*ここは、アイテム操作に関することのクラスです。
//主にバックパックやアイテム売買について書かれています。
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "citem_manipulate.h"//アイテム操作に関するヘッダファイル





/*簡易説明文を表示させる処理を行います*/
int Item_Manipulate::PutItemDescript( const int ChoseItem, const int ItemNumber){

	/*変数の初期化*/
	int ech = 0;//エラーチェック変数
	char WeaponDetail[64] = "";//武器分類の文字列配列

	/* 武器説明データ */
	const char ItemDetailData[8][9][70] ={

		/* ハンドガン */
		{ "米国製の扱いやすい45口径拳銃", "M1911を消音化、小型化したモデル", "ポリマーフレームのフルオート拳銃",
		"扱いやすい米軍の正式採用拳銃", "命中精度の高いチェコ製の拳銃", ".357マグナム弾を使うリヴォルバー", 
		"スイス製の拳銃。レーザーサイトを装備する", "旧ドイツ軍の9mm拳銃。8インチバレルを持つ", "サプレッサー付きの45口径拳銃"},
		/* サブマシンガン */
		{ "小柄で軽量、扱いやすい短機関銃", "最高の連射力を誇り、消音化された短機関銃", "イタリア製の、命中精度の高い短機関銃",
		"光学サイト付きの対テロ用ドイツ製短機関銃", "突撃銃を短縮化した光学サイト付き短機関銃", "傑作短機関銃、MP5シリーズの最短モデル",
		"人間工学を駆使した対テロ用短機関銃"},
		/* ショットガン */
		{ "第一次大戦から使われる、塹壕戦無敵の散弾銃", "米警察やSWATが採用するイタリア製半自動散弾銃", "スラッグ弾を撃ち出すフランキ社製戦闘用散弾銃",
		"日本製のスポーツ用二連装散弾銃。集弾性が高い", "フルオート射撃が可能な韓国製の散弾銃"},
		/* アサルトライフル */
		{ "光学サイトを搭載したアメリカを代表する小銃", "ロシア製の傑作小銃AKシリーズの輸出向けモデル", "薬莢を排出しない、ドイツ製の次世代自動小銃",
		"命中精度の高いライフル弾を使う米国製の自動小銃", "レーザーサイトを装備した高水準な自動小銃",
		"ブルパップ式自動小銃。LAM、ダットサイトを装備", "M4を改修し、命中精度を大きく上げた自動小銃"},
		/* マシンガン */
		{ "多くの国で正式採用されている、FN社の軽機関銃", "M4小銃をカスタムした、光学サイト付き軽機関銃",
		"AKベースの軽機関銃。安価ながら安定した性能", "WWⅠからWWⅡまで使われた、古参軽機関銃"},
		/* ライフル */
		{ "米国一番人気の、消音器つき狙撃銃", "M16をベースにした半自動狙撃銃", "中距離戦を想定した、銃剣つき半自動長銃", 
		"非常に高い命中精度を持つ半自動狙撃銃", "先端に特殊炸薬を取り付けた矢を放つボウガン", "大型の対物狙撃銃。反動がすさまじい"},
		/* グレネード */
		{ "ベトナム戦争で重宝された榴弾発射筒", "半自動榴弾発射筒。6発の榴弾を素早く発射できる",
		"高性能成型炸薬弾を使う対戦車ロケット発射機", "使い捨ての対戦車榴弾。旧ドイツ軍のコピー品"}
	};

	POINT TextPos1;//説明文字の位置を格納する構造体
	E3DCOLOR4UC NormalColor = { 255,50,50,50};//文字の白色

	//文字の位置決め
	if( ( System::MousePos.x + 256 ) < 640 ){//もしアイテムバーを右端を超えなければ
			TextPos1.x = System::MousePos.x + 5;/**/TextPos1.y = System::MousePos.y + 45;//説明文字の位置はマウスポインタから算出
	}
	else{//超えれば
			TextPos1.x = 5 + 384;/**/TextPos1.y = System::MousePos.y + 45;//説明文字の位置はマウスポインタから算出
	}

	/* //////////////////////// */
	// アイテムの種類によって分岐
	/* /////////////////////// */

	if(ChoseItem == 0){//操作中のアイテムが「武器」なら
			if( BackPack_Weapon[ItemNumber][1] == -1){//武器なしなら
					wsprintf( WeaponDetail, "武器がありません");//武器説明を代入します
			}
			else{
					wsprintf( WeaponDetail, ItemDetailData[ (BackPack_Weapon[ItemNumber][1] - 1) ][ (BackPack_Weapon[ItemNumber][2]) ]);//武器説明を代入します
			}

			ech = E3DDrawTextByFontID( System::scid1, TextID[2], TextPos1, WeaponDetail, NormalColor);
			
					_ASSERT( ech != 1 );//エラーチェック
	}

	if(ChoseItem == 1){//操作中のアイテムが「弾薬」なら

			if( BackPack_Ammo[ItemNumber][1] == 0){//.45ACP
						wsprintf( WeaponDetail, "米国製大型自動拳銃用の実包");//武器説明を代入します
			}
			if( BackPack_Ammo[ItemNumber][1] == -1){//弾薬なしなら
							wsprintf( WeaponDetail, "弾薬がありません");//武器説明を代入します

			}

			ech = E3DDrawTextByFontID( System::scid1, TextID[2], TextPos1, WeaponDetail, NormalColor);
			
					_ASSERT( ech != 1 );//エラーチェック

	}

	return 0;
}
/*武器アイテム名を表示させる処理を行います*/
int Item_Manipulate::PutItemName( const int ChoseItem, const int ItemNumber){

	/*変数の初期化*/
	int ech = 0;//エラーチェック変数
	char WeaponName[32] = "";//武器名前の文字列配列
	char WeaponKind[32] = "";//武器分類の文字列配列

	/* 武器名前配列データ */
	const char WeaponNameData[8][9][15] = {
		{ "M1911", "Offisers", "Glock95", "M92F", "Cz-75", "PYTHON", "sauerP226", "LugerP08", "USP.45"},// ハンドガン
		{ "TMP", "INGLAM", "SPECTER", "UMP", "PATIRIOT", "MP5 kruz", "P90"},// サブマシンガン
		{ "M1897", "Benel M3", "SPAS-12", "Gold Stalker", "USAS12", "M700", "M82"},// ショットガン
		{ "M4", "AK-74", "G11", "M14", "G36", "Tabor", "HK 416"},// アサルトライフル
		{ "BAR A2", "MINIMI", "M4machine", "RPK"},// マシンガン
		{ "M700", "SR-25", "SVD", "PSG-1", "X BOW", "M82"},// ライフル
		{ "MGL", "M79", "RPG-7", "Panzher", "M201A1"},// グレネード
		{ "shild sauer", "shild TMP"}// その他
	};

	POINT TextPos3;//武器の種類の名前文字の位置を格納する構造体
	E3DCOLOR4UC NormalColor = { 255,50,50,50};//文字の白色

	//文字の位置決め
	if( MenuMode == 0){// メニューモードが通常なら
			if( ( System::MousePos.x + 256 ) < 640 ){//もしアイテムバーを右端を超えなければ
					TextPos3.x = System::MousePos.x + 5;/**/TextPos3.y = System::MousePos.y + 5;//武器の種類の名前文字の位置はマウスポインタから算出
			}
			else{//超えれば
					TextPos3.x = 5 + 384;/**/TextPos3.y = System::MousePos.y + 5;//武器の種類の名前文字の位置はマウスポインタから算出
			}
	}
	else if( MenuMode == 1){// メニューモードが選択中なら
			TextPos3.x = ItemSysSetPos.x + 5;/**/TextPos3.y = ItemSysSetPos.y + 5;//武器の種類の名前文字の位置はマウスポインタから算出
	}



	/**/
	//アイテムの種類によって分岐
	/**/

	if(ChoseItem == 0){//操作中のアイテムが「武器」なら

			if( BackPack_Weapon[ItemNumber][1] == -1){
					wsprintf( WeaponName, "EMPTY");//武器名前を代入します
			}
			else{// 武器名前を代入します
					wsprintf( WeaponName, WeaponNameData[(BackPack_Weapon[ItemNumber][1] - 1)][(BackPack_Weapon[ItemNumber][2])]);
			}

		/**//////////
		/**////////
			if(ItemNumber == 0){//マウスがメインウェポンの上にあれば
					wsprintf( WeaponKind, "MainWeapon  %s", WeaponName);//武器名前を代入します
			}
			if(ItemNumber == 1){//マウスがサブウェポンの上にあれば
					wsprintf( WeaponKind, "SubWeapon  %s", WeaponName);//武器名前を代入します
			}
			if(ItemNumber == 2){//マウスがグレネード系の上にあれば
					wsprintf( WeaponKind, "Grenade  %s", WeaponName);//武器名前を代入します
			}
			if(ItemNumber == 3){//マウスが修理が必要な武器の上にあれば
					wsprintf( WeaponKind, "Need Repiar  %s", WeaponName);//武器名前を代入します
			}


			//武器分類を表示させます
			ech = E3DDrawTextByFontID( System::scid1, TextID[1], TextPos3, WeaponKind, NormalColor);
			
					_ASSERT( ech != 1 );//エラーチェック


	}
	if(ChoseItem == 1){//操作中のアイテムが「弾薬」なら

			if( BackPack_Ammo[ItemNumber][1] == 0){//.45ACP
				wsprintf( WeaponKind, ".45ACP");//武器名前を代入します
			}
			else if( BackPack_Ammo[ItemNumber][1] == -1){
							wsprintf( WeaponKind, "EMPTY");//武器名前を代入します

			}

			ech = E3DDrawTextByFontID( System::scid1, TextID[1], TextPos3, WeaponKind, NormalColor);
			
						_ASSERT( ech != 1 );//エラーチェック
	}




	return 0;
}
/*アイテム種類のメニューの表示・選択を行います*/
int Item_Manipulate::PutBackPackText( int *ChoseItem, int *ExitFlag){


		/* 変数の宣言 */
		int ech = 0;//エラーチェック変数
		 ;//キー情報配列を作成
		const char ItemKindName[5][12] = { "WEAPON" , "AMMO" , "RECOVERY" , "KEY" , "EQUIPMENT" };
		const char ItemKindDetal[5][50] = { "武器の操作をします" , "弾薬の操作をします" , "回復系品の操作をします" 
											, "重要品の操作をします" , "装備品の操作をします" };
		const E3DCOLOR4UC NormalColor = { 255,255,255,255};//白色の選ばれていない色
		const E3DCOLOR4UC SetColor = { 255,0,120,170};//青色の武器が選ばれている色
		const E3DCOLOR4UC SelectColor = { 255,200,220,20};//黄色の選ばれている色
		POINT TextPos;//文字の位置を格納する構造体

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
		if((100< System::MousePos.x)&&(System::MousePos.x<250) && ( MenuMode == 0)) {//マウスX座標がメニュー群の所にあるなら

			for( int i=0; i<5; i++){
				if((120 + (40 * i) < System::MousePos.y)&&( System::MousePos.y< 150 + (40 * i) )){
					
						/* マウスポインタが置いてある文字を光らせる */
						TextPos.x = 100;/**/TextPos.y = 100 + (40 * i);
						E3DDrawTextByFontID( System::scid1, TextID[1], TextPos, ItemKindName[i], SelectColor);//選択されている文字にする
						
								_ASSERT( ech != 1 );//エラーチェック

						/* 下側にポインタを置いているところの説明を記述する */
						TextPos.x = 400;/**/TextPos.y = 330;
						E3DDrawTextByFontID( System::scid1, TextID[1], TextPos, ItemKindDetal[i], NormalColor);//説明が書かれている文字列を表示する
						
								_ASSERT( ech != 1 );//エラーチェック

						/* クリックしたら選択アイテムを変える */
						if( (System::GetKeyData( System::KEY_LEFTMOUSE)) && ( MenuMode == 0)){
									*ChoseItem = i;//ループ脱出フラグをオンにする。
						}
				}
			}

			if((340< System::MousePos.y)&&( System::MousePos.y<370)){//マウス座標が「バックパックを閉じる」の上なら
					TextPos.x = 100;/**/TextPos.y = 320;
					E3DDrawTextByFontID( System::scid1, TextID[1], TextPos, "バックパックを閉じる", SelectColor);//選択されている文字にする
					
					_ASSERT( ech != 1 );//エラーチェック

					TextPos.x = 400;/**/TextPos.y = 330;
					E3DDrawTextByFontID( System::scid1, TextID[1], TextPos, "ポーズメニューに戻ります", NormalColor);//説明が書かれている文字列を表示する
					
					_ASSERT( ech != 1 );//エラーチェック

					if(System::GetKeyData( System::KEY_LEFTMOUSE)){//クリックしたら
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
/*アイテム画像の表示、制御を行ないます*/
int Item_Manipulate::PutItemSprite( const int ChoseItem, const int MenuMode, const POINT ItemSysSetPos){

	/* 変数の宣言 */
	int ech = 0;// エラーチェック変数
	int ItemNumber = -1;//どのアイテムを選んだか、代入します

	/* 武器画像位置配列変数 */
	const float ItemSpritePosition[3][2][6] = {
		{ { 280, 440, 280, 440} , {100 , 100, 190, 190} },// 武器メニュー
		{ { 280, 440, 280, 440} , {100 , 100, 190, 190}  },// 弾薬メニュー
		{ { 280, 440, 280, 440 , 360} , {90 , 90, 170, 170 , 250}  } // 回復系メニュー
	};
	D3DXVECTOR3 ItemSpritePos( 0.0, 0.0, 0.0);// アイテム画像の位置
	D3DXVECTOR3 DatilSpritePos( 0.0, 0.0, 0.0);//説明バーの位置



	/* ///////////////////////////////////// */
	// すべての画像スプライトの描画を行ないます
	/* ///////////////////////////////////// */
	switch( ChoseItem ){
		case 0:{//武器のメニュー
				for(int i=0; i<4; i++){
						ItemSpritePos.x = ItemSpritePosition[0][0][i];/**/ItemSpritePos.y = ItemSpritePosition[0][1][i];
						ech = E3DRenderSprite( BackPack_Weapon[i][0], 1, 1, ItemSpritePos);//上部の白いバー
						_ASSERT( ech != 1 );//エラーチェック
				}					
				break;
		}
		case 1:{//弾薬のメニュー
				for(int i=0; i<4; i++){
						ItemSpritePos.x = ItemSpritePosition[1][0][i];/**/ItemSpritePos.y = ItemSpritePosition[1][1][i];
						ech = E3DRenderSprite( BackPack_Ammo[i][0], 1, 1, ItemSpritePos);//上部の白いバー
						_ASSERT( ech != 1 );//エラーチェック
				}
				break;
		}
		case 2:{//回復系のメニュー
				for(int i=0; i<5; i++){
						ItemSpritePos.x = ItemSpritePosition[2][0][i];/**/ItemSpritePos.y = ItemSpritePosition[2][1][i];
						ech = E3DRenderSprite( BackPack_Recovery[i][0], 1, 1, ItemSpritePos);//上部の白いバー
						_ASSERT( ech != 1 );//エラーチェック
				}
				break;
			}
	}

	/* ここまで */


	/* ///////////////////////////////////////// */
	//  アイテム画像の上にマウスポインタがあるなら。
	//	その、画像IDを取得する
	// ///////////////////////////////////////// */
	if( MenuMode == 0){// モードが「アイテムを選択してない」なら
			switch( ChoseItem ){
					case 0:{//武器のメニュー
						for(int i=0; i<4; i++){
							if(( ItemSpritePosition[0][0][i] < System::MousePos.x ) && ( System::MousePos.x < ItemSpritePosition[0][0][i] + 128.0f )
									&& ( ItemSpritePosition[0][1][i]  + 16.0f < System::MousePos.y ) && ( System::MousePos.y < ItemSpritePosition[0][1][i] + 90.0f)){
										ItemNumber = i;//カーソルと重なっていた画像のIDを代入
							}
						}
						break;
					}
					case 1:{//弾薬のメニュー
						for(int i=0; i<4; i++){
							if(( ItemSpritePosition[1][0][i] < System::MousePos.x ) && ( System::MousePos.x < ItemSpritePosition[1][0][i] + 128.0f )
									&& ( ItemSpritePosition[1][1][i] + 16.0f < System::MousePos.y ) && ( System::MousePos.y < ItemSpritePosition[1][1][i] + 90.0f)){
										ItemNumber = i;//カーソルと重なっていた画像のIDを代入
							}
						}
						break;
					}
					case 2:{//回復系のメニュー
						for(int i=0; i<5; i++){
							if(( ItemSpritePosition[2][0][i] < System::MousePos.x ) && ( System::MousePos.x < ItemSpritePosition[2][0][i] + 128.0f )
									&& ( ItemSpritePosition[2][1][i] + 16.0f < System::MousePos.y ) && ( System::MousePos.y < ItemSpritePosition[2][1][i] + 90.0f)){
										ItemNumber = i;//カーソルと重なっていた画像のIDを代入
							}
						}
						break;
					}
			}

			/* //////////////////////////////////// */
			//  説明バーを表示させないといけないならば
			/* //////////////////////////////////// */
			if( ItemNumber != -1 ){

					//バーが右にはみ出ないのなら
					if( ( System::MousePos.x + 256 ) < 640 ){
							DatilSpritePos.x = float( System::MousePos.x ); /**/ DatilSpritePos.y = float( System::MousePos.y );
					}
					//バーが右にはみ出るのなら
					else{
							DatilSpritePos.x = 384.0f; /**/ DatilSpritePos.y = float( System::MousePos.y );
					}
					/* スプライトの描画 */
					ech = E3DRenderSprite( MenuSpriteIDs[4], 1, 1, DatilSpritePos);//上部の白いバー
					_ASSERT( ech != 1 );//エラーチェック
			};
	}
	else if( MenuMode == 1){// モードが「アイテムを選択している」なら

			/* 座標の指定 */
			DatilSpritePos.x = float( ItemSysSetPos.x ); /**/ DatilSpritePos.y = float( ItemSysSetPos.y );
			
			/* スプライトの描画 */
			ech = E3DRenderSprite( MenuSpriteIDs[4], 1, 1, DatilSpritePos);//上部の白いバー
			_ASSERT( ech != 1 );//エラーチェック
	}


	/* ここまで */



	return ItemNumber;
}
/*アイテムを使う、削除、確認などを行ないます*/
int Item_Manipulate::ItemUsingSystem( const int ChoseItem){

	/* 変数の宣言 */
	int ech = 0;//エラーチェック変数
	D3DXVECTOR3 ItemIconPos( 0.0, 0.0, 0.0);//アイテム操作アイコンの位置
	
	/* アイテムアイコンを左からどの画像を描画するか決める変数 */
	const int ItemIconIDToRight[5][4] = {
		{ 8, 6, 7},
		{ 6, 7},
		{ 5, 6, 7},
		{ 7},
		{ 8, 6, 7}
	};

	/* アイテムアイコンを何個表示させるのか定義する変数 */
	const int ItemIconNumber[5] = { 3, 2, 3, 1, 3};

	// 座標操作
	ItemIconPos.x = ItemSysSetPos.x + 10.0f;
	ItemIconPos.y = ItemSysSetPos.y + 30.0f;

	//アイテム操作アイコンの描画
	for( int i=0; i < ItemIconNumber[(ChoseItem)]; i++ ){

			ech = E3DRenderSprite( MenuSpriteIDs[(ItemIconIDToRight[(ChoseItem)][i])], 1, 1, ItemIconPos);//背景の位置
			_ASSERT( ech != 1 );//エラーチェック
			
			ItemIconPos.x = ItemIconPos.x + 40;
	 }




	return 0;
}