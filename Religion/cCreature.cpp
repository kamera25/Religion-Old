/*ここでは、生物クラスの関数を定義するクラスコードファイルです。
//
*/
#include <easy3d.h>//Easy3Dを使うためのヘッダを読み込みます。
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "csys.h"//開始・終了・プロージャーなどシステム周りのクラスヘッダ

#include "ccreature.h"//生物クラスの宣言ヘッダファイル


/* ライフやスタミナなどの属性を代入する関数 */
int Creature::Set_StateFromBranch( const int Branch){

	/* 能力 */
	// 兵種名[Branchの数字]
	//
	// ライフルマン[0]
	// グレネーダー[1]
	// ガンナー    [2]
	// スナイパー  [3]
	// メディック  [4]

	// ノーマル[default]

	Set_Branch( Branch);// 生物の属性を代入します

	switch( Branch ){

		case 0:{// ライフルマン
			Set_MaxHP(1000);//最大HPの代入
			Set_MaxStamina(800);//最大スタミナの代入
			Set_Attack(150);//攻撃力の代入
			Set_SkillSlot(6);//スキルスロットの代入
			break;
		}
		case 1:{// グレネーダー
			Set_MaxHP(800);//最大HPの代入
			Set_MaxStamina(900);//最大スタミナの代入
			Set_Attack(160);//攻撃力の代入
			Set_SkillSlot(8);//スキルスロットの代入
			break;
		}
		case 2:{// ガンナー 
			Set_MaxHP(780);//最大HPの代入
			Set_MaxStamina(650);//最大スタミナの代入
			Set_Attack(120);//攻撃力の代入
			Set_SkillSlot(8);//スキルスロットの代入
			break;
		}
		case 3:{// スナイパー
			Set_MaxHP(700);//最大HPの代入
			Set_MaxStamina(600);//最大スタミナの代入
			Set_Attack(90);//攻撃力の代入
			Set_SkillSlot(12);//スキルスロットの代入
			break;
		}
		case 4:{// メディック
			Set_MaxHP(670);//最大HPの代入
			Set_MaxStamina(750);//最大スタミナの代入
			Set_Attack(120);//攻撃力の代入
			Set_SkillSlot(10);//スキルスロットの代入
			break;
		}
		default:{// ノーマル
			Set_MaxHP(750);//最大HPの代入
			Set_MaxStamina(750);//最大スタミナの代入
			Set_Attack(130);//攻撃力の代入
			Set_SkillSlot(1);//スキルスロットの代入
			break;
		}
	}




	return 0;
}
/* スキル系の能力を追加する関数(非アシスト系) */
int Creature::Add_Skill( const int PlanSkill){

	/* 変数の初期化 */
	int SkillCostSum = 0;// 装備中スキルコストの合計
	int SkillCostSumAfter = 0;// 新しいコストを指定した場合の装備中スキルコスト
	int SkillEQMAXSum = 0;// 追加する予定の既に装備中のスキル合計


	// 定数宣言  "スキルコスト"	
	const int SKILL_COST[22] = {
		1,// ガンスリンガー
		1,// リベリオン
		1,// バンポーチ
		2,// 40mmポーチ
		1,// サポーター
		1,// 防弾チョッキ
		2,// ケブラーベスト
		1,// マグポーチ
		1,// フリッツヘルム
		1,// コマンドー
		1,// ランナー
		1,// ピッチャー
		1,// 危機管理
		1,// ポーチ
		2,//銀の銃弾
		1,// キャメル
		0,// ショータイム(マイケル)
		1,// スプリンター
		1,// 部隊無線
		1,// 鉄壁
		5,// 不屈の魂
		3// 爆弾魔
	};


	// 定数宣言  "スキル装備上限数"
	// EQMAX == EQuipment Max 
	const int SKILL_EQMAX[22] = {
		2,// ガンスリンガー
		1,// リベリオン
		3,// バンポーチ
		1,// 40mmポーチ
		2,// サポーター
		1,// 防弾チョッキ
		1,// ケブラーベスト
		2,// マグポーチ
		1,// フリッツヘルム
		1,// コマンドー
		2,// ランナー
		2,// ピッチャー
		1,// 危機管理
		2,// ポーチ
		1,//銀の銃弾
		1,// キャメル
		1,// ショータイム
		1,// スプリンター
		1,// 部隊無線
		1,// 鉄壁
		1,// 不屈の魂
		1 // 爆弾魔
	};


	/* 存在するスキルかどうか確認する、なければ */
	if( ( PlanSkill <= -1 ) || ( NumberSkill <= PlanSkill )){
			return -1;// 失敗でエラー処理
	}


	/* 初回時のスキル追加なら */
	if( EquipmentSkillSum == 0 ){

			SkillCostSumAfter = SKILL_COST[PlanSkill];
			if( SkillCostSumAfter <= SkillSlot ){// コスト確認

					Skill = new int[1];// 初回時のときは、スキル格納変数ポインターに変数を作成
					Skill[0] = PlanSkill;// スキル代入
			}
			else{// 確認し追加できないなら
					return -1;// エラー返し
			}
	}

	/* 2回目以降のスキル追加なら */
	if( 0 < EquipmentSkillSum ){
			
		/* コストがオーバーしていないかチェック */
		for( int i=0; i < EquipmentSkillSum ;i++){
				SkillCostSum = SkillCostSum + SKILL_COST[i];
		}

		/* 装備可能数を超えていないかチェック */
		for( int i=0; i < EquipmentSkillSum ;i++){
				if( PlanSkill == Skill[i] ) SkillEQMAXSum++;
		}

		/* スキル装備することが可能なら */
		if( ( SkillEQMAXSum < SKILL_EQMAX[PlanSkill] ) &&
			( SkillCostSumAfter <= SkillSlot ) ){
					int *p;
					p = new int[(EquipmentSkillSum + 1)];

					/* newで新しく作ったスキル格納変数に元格納変数をコピー */
					for( int i=0; i< EquipmentSkillSum; i++){
						p[i] = Skill[i];
					}
					p[ EquipmentSkillSum ] = PlanSkill;// 次のスキル配列にスキル代入

					delete [] Skill;
					Skill = p;
					

		}
		else{// スキル装備不可なら
				return -1;//  エラー返し
		}
	}


	// もし、スキルコスト合計とスキル装備可能数を超えていなければ
	EquipmentSkillSum++;// スキル装備合計を"1"足す


	return 0;
}
/* スキル系の能力を削除する関数(非アシスト系) */
int Creature::Delete_Skill( const int PlanSkill){

	/* 変数の初期化&宣言 */
	int FindAppropriateSkillFlg = 0;// 検索においてスキルが発見出来たかどうかのフラグ


	/* もし、スキルをつけていないのに削除しようとしたら or  つけたいスキルが見当違いの数字なら */
	if( ( EquipmentSkillSum == 0) ||
		( PlanSkill <= -1 ) ||
		( NumberSkill <= PlanSkill) ){
			return -1;// エラー返し
	}


	/* もし、スキルをひとつしかつけてなかったら */
	if( EquipmentSkillSum == 1){
			
			if( Skill[0] == PlanSkill){// つけてるスキルと消したいスキルが同じなら
					delete [] Skill;
					Skill = NULL;
			}
			else{					 //  つけてるスキルと消したいスキルが異なれば
					return -1;//  エラー返し
			}
	}

	/* もし、スキルを2つ以上つけていたら */
	if( 2 <= EquipmentSkillSum){

			for( int i=0; i < EquipmentSkillSum; i++){// スキルを検索する
					if( Skill[i] == PlanSkill){
							Skill[i] = -1;
							FindAppropriateSkillFlg = 1;
							break;// ループから抜ける
					}
			}

			/* もし、削除したいスキルが発見できなければ */
			if( FindAppropriateSkillFlg == 0){
					return -1;//  エラー返し
			}
			
			/* 以下、スキル削除の処理を行います */
			int *p;
			int j = 0;

			p = new int[(EquipmentSkillSum - 1)];

			/* 新しく作った配列に旧配列の変数をコピー */
			for( int i=0; i < EquipmentSkillSum; i++){
					if( Skill[i] != -1){//  削除されたスキル変数以外は
							p[j] = Skill[i];// スキル変数をコピー
							j++;// p専用ループカウンターを回す
					}
			}

			delete [] Skill;
			Skill = p;
	}

	EquipmentSkillSum--;// スキル装備合計を"1"引く



	return 0;
}