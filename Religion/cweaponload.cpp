/*ここでは、武器に関することを記述するクラスコードファイルです
//主に、武器のロードについて書かれています
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "cenemy.h"//敵クラスの宣言ヘッダファイル
#include "cweapon.h"//武器に関することのクラスヘッダファイル


/*武器をロードするための関数*/
int Weapon::GunLoad( const int Selectkind, const int Wpkind, const int Wpno){

	//変数の初期化
	int ech = 0;
	char loadname[256] = "";

	/*すでに銃を取得しており、その銃データに上書きするなら*/
	if( WeaponModel[Selectkind] != 0){//選択中のカテゴリにデータがあるのなら
				ech = E3DDestroyHandlerSet( WeaponModel[Selectkind]);
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};

				ech = E3DDestroySprite( WeaponSprite[Selectkind]);//スプライトを削除します
				if(ech != 0 ){//エラーチェック
							_ASSERT( 0 );//エラーダイアログ
				};
	}


	/*銃のモデルのロード*/
	if(Wpkind == 1) GunLoad_Hand( Selectkind, Wpno);//ハンドガン系
	if(Wpkind == 3) GunLoad_Shot( Selectkind, Wpno);//ショットガン系
	if(Wpkind == 4) GunLoad_Assault( Selectkind, Wpno);//アサルトライフル系
	if(Wpkind == 5) GunLoad_Machine( Selectkind, Wpno);//マシンガン系
	if(Wpkind == 6) GunLoad_Rifle( Selectkind, Wpno);//ライフル系
	if(Wpkind == 7) GunLoad_Grenade( Selectkind, Wpno);//グレネード系

	//エフェクトビルボードをロードします
	wsprintf( loadname, "%s\\data\\img\\effect\\explosion1.png", System::path);
	ech = E3DCreateBillboard ( loadname, 96, 96, 0, 1, 1, &WeaponEffect[Selectkind][0]);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	//エフェクトを予め透過しておく
	ech = E3DSetBillboardAlpha( WeaponEffect[Selectkind][0], 0.0f);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};

	//フラッシュの光源を作る(グレネードは爆発光)
	ech = E3DCreateLight( &WeaponMuzzleLight[Selectkind]);
	if(ech != 0 ){//エラーチェック
				_ASSERT( 0 );//エラーダイアログ
	};


	/*武器データのロードをする*/
	GunLoad_Data( Selectkind, Wpkind, Wpno);


	return 0;
}
/*武器に関するデータを格納する関数*/
int Weapon::GunLoad_Data( const int Selectkind, const int Wpkind, const int Wpno){

	//一時的な変数（モデル格納等など）
	int ammo = 0;//弾薬の最大値
	int mag = 0;//マガジンの最大値
	int distance = 0;//射程距離の最大値
	int attack = 0;//武器の攻撃値
	int rapid_fire = 0;//連射可能銃か
	int ammokind = 0;// 弾薬の種類
	int accuracy = 0;// 武器の精度
	double firecounter = 0.0;//連射の数値


	switch(Wpkind){

			/* ハンドガン関係 */
		    case 1:{
					switch(Wpno){
							case 0:{// M1911のデータを格納します。
									ammokind = 0;
									attack = 100;
									firecounter = 2.0;
									distance = 100;
									accuracy = 5;
									ammo = 7;
									mag = 8;

									rapid_fire = 0;

									break;
						    }
							case 1:{// Offisersのデータを格納します。
									ammokind = 0;
									attack = 80;
									firecounter = 2.4;
									distance = 70;
									accuracy = 5;
									ammo = 5;
									mag = 10;

									rapid_fire = 0;

									break;
							}
							case 2:{// Glock95のデータを格納します。
									ammokind = 1;
									attack = 45;
									firecounter = 4.3;
									distance = 60;
									accuracy = 3;
									ammo = 50;
									mag = 4;

									rapid_fire = 1;

									break;
							}
							case 3:{// M92FSのデータを格納します。
									ammokind = 2;
									attack = 80;
									firecounter = 2.8;
									distance = 120;
									accuracy = 3;
									ammo = 15;
									mag = 3;

									rapid_fire = 0;

								break;
							}
							case 4:{// Cz-95のデータを格納します。
									ammokind = 2;
									attack = 80;
									firecounter = 3.2;
									distance = 100;
									accuracy = 1;// ホントはA-
									ammo = 15;
									mag = 3;

									rapid_fire = 0;

									break;
							}
							case 5:{// PYTHONのデータを格納します。
									ammokind = 6;
									attack = 150;
									firecounter = 1.6;
									distance = 125;
									accuracy = 7;
									ammo = 6;
									mag = 5;

									rapid_fire = 0;

									break;
							}
							case 6:{// sauerP226のデータを格納します。
									ammokind = 2;
									attack = 80;
									firecounter = 2.4;
									distance = 140;
									accuracy = 3;
									ammo = 15;
									mag = 3;

									rapid_fire = 0;

									break;
							}
							case 7:{// LugerP08のデータを格納します。
									ammokind = 2;
									attack = 80;
									firecounter = 3.5;
									distance = 55;
									accuracy = 6;
									ammo = 32;
									mag = 3;

									rapid_fire = 0;
									
									break;
							}
							case 8:{// USP.45のデータを格納します。
									ammokind = 0;
									attack = 80;
									firecounter = 2.8;
									distance = 80;
									accuracy = 5;
									ammo = 13;
									mag = 3;

									rapid_fire = 0;

									break;
							}
					}
					break;
			}

			/* サブマシンガン関係 */
			case 2:{
					switch(Wpno){
							case 0:{// TMPのデータを格納します。
									ammokind = 2;
									attack = 70;
									firecounter = 15.0;
									distance = 80;
									accuracy = 3;// ホントはA-
									ammo = 30;
									mag = 5;

									rapid_fire = 1;

									break;
						    }
							case 1:{// INGLAMのデータを格納します。
									ammokind = 0;
									attack = 70;
									firecounter = 20.0;
									distance = 50;
									accuracy = 6;
									ammo = 20;
									mag = 5;

									rapid_fire = 1;

									break;
							}
							case 2:{// SPECTRE M4のデータを格納します。
									ammokind = 2;
									attack = 70;
									firecounter = 14.0;
									distance = 75;
									accuracy = 3;
									ammo = 50;
									mag = 3;

									rapid_fire = 1;

									break;
							}
							case 3:{// UMPのデータを格納します。
									ammokind = 0;
									attack = 90;
									firecounter = 11.0;
									distance = 80;
									accuracy = 2;
									ammo = 25;
									mag = 4;

									rapid_fire = 1;

								break;
							}
							case 4:{// PATIRIOTのデータを格納します。
									ammokind = 9;
									attack = 120;
									firecounter =13.0 ;
									distance = 85;
									accuracy = 8;
									ammo = 30;
									mag = 3;

									rapid_fire = 1;

									break;
							}
							case 5:{// MP5 kruzのデータを格納します。
									ammokind = 2;
									attack = 70;
									firecounter = 15.0;
									distance = 100;
									accuracy = 1;
									ammo = 15;
									mag = 8;

									rapid_fire = 1;

									break;
							}
							case 6:{// P90のデータを格納します。
									ammokind = 3;
									attack = 80;
									firecounter = 15.0;
									distance = 70;
									accuracy = 7;
									ammo = 50;
									mag = 2;

									rapid_fire = 1;

									break;
							}
					}
					break;
			}
			
				  

			/* ショットガン関係 */
		    case 3:{
					switch(Wpno){
							case 0:{// M1897のデータを格納します。
									ammokind = 7;
									attack = 40;// *9
									firecounter = 1.0;
									distance = 20;
									accuracy = 8;
									ammo = 5;
									mag = 15;

									rapid_fire = 0;

									break;
						    }
							case 1:{// Benel M3のデータを格納します。
									ammokind = 7;
									attack = 40;// *9
									firecounter = 1.8;
									distance = 30;
									accuracy = 7;
									ammo = 7;
									mag = 14;

									rapid_fire = 0;

									break;
							}
							case 2:{// SPAS-12のデータを格納します。
									ammokind = 4;
									attack = 200;
									firecounter = 1.5;
									distance = 120;
									accuracy = 6;
									ammo = 7;
									mag = 14;

									rapid_fire = 0;

									break;
							}
							case 3:{// Gold Stalkerのデータを格納します。
									ammokind = 8;
									attack = 50;// *9
									firecounter = 1.5;
									distance = 50;
									accuracy = 5;
									ammo = 2;
									mag = 8;

									rapid_fire = 0;

								break;
							}
							case 4:{// USAS12のデータを格納します。
									ammokind = 7;
									attack = 15;// *9
									firecounter = 2.2;
									distance = 20;
									accuracy = 9;
									ammo = 12;
									mag = 2;

									rapid_fire = 0;

									break;
							}
					}
					break;
		    }

		    /* アサルトライフル関係 */
		    case 4:{
					switch(Wpno){
							case 0:{// M4のデータを格納します。
									ammokind = 9;
									attack = 140;
									firecounter = 13.0;
									distance = 160;
									accuracy = 3;
									ammo = 30;
									mag = 5;

									rapid_fire = 1;

									break;
						    }
							case 1:{// AK-101のデータを格納します。
									ammokind = 5;
									attack = 160;
									firecounter = 10;
									distance = 190;
									accuracy = 5;
									ammo = 30;
									mag = 4;

									rapid_fire = 1;

									break;
							}
							case 2:{// G11のデータを格納します。
									ammokind = 10;
									attack = 150;
									firecounter = 33.0;
									distance = 160;
									accuracy = 4;
									ammo = 45;
									mag = 4;

									rapid_fire = 1;

									break;
							}
							case 3:{// M14のデータを格納します。
									ammokind = 11;
									attack = 200;
									firecounter = 12.5;
									distance = 210;
									accuracy = 6;
									ammo = 20;
									mag = 5;

									rapid_fire = 1;

								break;
							}
							case 4:{// G36のデータを格納します。
									ammokind = 9;
									attack = 140;
									firecounter = 12.5;
									distance = 170;
									accuracy = 3;// ホントはA-
									ammo = 30;
									mag = 5;

									rapid_fire = 1;

									break;
							}
							case 5:{// Taborのデータを格納します。
									ammokind = 9;
									attack = 140;
									firecounter = 12.5;
									distance = 150;
									accuracy = 2;
									ammo = 30;
									mag = 5;

									rapid_fire = 1;

									break;
							}
							case 6:{// HK 416のデータを格納します。
									ammokind = 9;
									attack = 140;
									firecounter = 11.0;
									distance = 170;
									accuracy = 0;
									ammo = 30;
									mag = 5;

									rapid_fire = 1;

									break;
							}
					}
					break;
			}

			/* マシンガン関係 */
		    case 5:{
					switch(Wpno){
							case 0:{// BAR A2のデータを格納します。
									ammokind = 11;
									attack = 120;
									firecounter = 5.0;
									distance = 160;
									accuracy = 7;
									ammo = 20;
									mag = 8;

									rapid_fire = 1;

									break;
						    }
							case 1:{// MINIMIのデータを格納します。
									ammokind = 9;
									attack = 90;
									firecounter = 10.0;
									distance = 220;
									accuracy = 9;
									ammo = 150;
									mag = 2;

									rapid_fire = 1;

									break;
							}
							case 2:{// M4machineのデータを格納します。
									ammokind = 9;
									attack = 90;
									firecounter = 13.0;
									distance = 180;
									accuracy = 7;
									ammo = 90;
									mag = 3;

									rapid_fire = 1;

									break;
							}
							case 3:{// RPKのデータを格納します。
									ammokind = 11;
									attack = 110;
									firecounter = 10.0;
									distance = 200;
									accuracy = 8;
									ammo = 75;
									mag = 4;

									rapid_fire = 1;

								break;
							}
					}
					break;
			}

			/* ライフル関係 */
		    case 6:{
					switch(Wpno){
							case 0:{// M700のデータを格納します。
									ammokind = 11;
									attack = 300;
									firecounter = 1.0;
									distance = 250;
									accuracy = 0;
									ammo = 5;
									mag = 10;

									rapid_fire = 0;

									break;
						    }
							case 1:{// SR-25のデータを格納します。
									ammokind = 9;
									attack = 250;
									firecounter = 2.0;
									distance = 210;
									accuracy = 2;
									ammo = 10;
									mag = 4;

									rapid_fire = 0;

									break;
							}
							case 2:{// SVDのデータを格納します。
									ammokind = 11;
									attack = 280;
									firecounter = 1.8;
									distance = 220;
									accuracy = 1;
									ammo = 10;
									mag = 4;

									rapid_fire = 0;

									break;
							}
							case 3:{// PSG-1のデータを格納します。
									ammokind = 11;
									attack = 260;
									firecounter = 2.0;
									distance = 130;
									accuracy = 2;
									ammo = 5;
									mag = 6;

									rapid_fire = 0;

								break;
							}
							case 4:{// X BOWのデータを格納します。
									ammokind = 12;
									attack = 250;
									firecounter = 0.8;
									distance = 130;
									accuracy = NULL -1;// 異常
									ammo = 1;
									mag = 50;

									rapid_fire = 0;

									break;
							}
							case 5:{// M82のデータを格納します。
									ammokind = 15;
									attack = 850;
									firecounter = 0.5;
									distance = 250;
									accuracy = 3;
									ammo = 5;
									mag = 3;

									rapid_fire = 0;

									break;
							}
					}
					break;
			}
			

			/* グレネード関係 */
		    case 7:{
					switch(Wpno){
							case 0:{// MGLのデータを格納します。
									ammokind = 13;
									attack = 350;
									firecounter = 1.0;
									distance = 80;
									accuracy = 3;
									ammo = 6;
									mag = 12;

									rapid_fire = 0;

									break;
						    }
							case 1:{// M79のデータを格納します。
									ammokind = 13;
									attack = 400;
									firecounter = NULL;//異常
									distance = 100;
									accuracy = 3;
									ammo = NULL;//異常
									mag = 18;

									rapid_fire = 0;

									break;
							}
							case 2:{// RPG-7のデータを格納します。
									ammokind = 14;
									attack = 380;
									firecounter = 1.0;
									distance = 180;
									accuracy = 8;
									ammo = 1;
									mag = 5;

									rapid_fire = 0;

									break;
							}
							case 3:{// Panzherのデータを格納します。
									ammokind = 14;
									attack = 410;
									firecounter = NULL;//異常
									distance = 160;
									accuracy = 6;
									ammo = 1;
									mag = 5;

									rapid_fire = 0;

								break;
							}
							case 4:{// M202A1のデータを格納します。
									ammokind = 14;
									attack = 340;
									firecounter = 1.4;
									distance = 140;
									accuracy = 6;
									ammo = 4;
									mag = 8;

									rapid_fire = 0;

									break;
							}
					}
					break;
		    }

			/* シールド関係 */
		    case 8:{
					switch(Wpno){
							case 0:{// shield + sauerのデータを格納します。
									ammokind = 2;
									attack = 80;
									firecounter = 2.4;
									distance = 140;
									accuracy = 5;
									ammo = 15;
									mag = 3;

									rapid_fire = 0;

									break;
						    }
							case 1:{// shield + TMPのデータを格納します。
									ammokind = 2;
									attack = 80;
									firecounter = 15;
									distance = 80;
									accuracy = 6;
									ammo = 20;
									mag = 2;

									rapid_fire = 1;

									break;
							}
					break;
					}
			}
	}


	WeaponData[Selectkind][0] = Wpkind;
	WeaponData[Selectkind][1] = Wpno;
	WeaponData[Selectkind][2] = ammo;
	WeaponData[Selectkind][3] = mag;
	WeaponData[Selectkind][4] = distance;
	WeaponData[Selectkind][5] = attack;
	WeaponData[Selectkind][6] = int( 30 / firecounter) ;
	WeaponData[Selectkind][7] = rapid_fire;
	WeaponData[Selectkind][8] = ammokind;
	WeaponData[Selectkind][9] = accuracy;

	return 0;
}