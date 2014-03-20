#pragma once
/*　生物クラスの宣言をするヘッダファイル。
 *　生物系クラスのスーパークラスです
 */

#include "cWeapon_head.h"// 武器統括に関することのクラスヘッダファイル
#include "cActor.h"

class Weapon;
class Stage;

/* 生物クラスの宣言 */
class Creature {

private:


	int MaxHP;// 生物の最大HP
	int HP;// 生物のHP
	int Stamina;// 生物のスタミナ
	int MaxStamina;//生物の最大スタミナ
	//int BodyModel;// 生物のモデル
	int SkillSlot;// スキルスロットの最大値
	int Attack;// 生物の攻撃力
	int Branch;// 生物の属性
	int *Skill;// スキルの格納ポインタ
	int EquipmentSkillSum;// 装備中スキルの合計
	

public:

	/* クラス静動変数 */
	static const int GUNSLINGER = 0;// ガンスリンガー
	static const int REBELLION = 1;// リベリオン
	static const int VAN_POUCH = 2;// バンポーチ
	static const int POUCH_40MM = 3;// 40mmポーチ
	static const int SUPPORTER = 4;// サポーター
	static const int BODYARMOR = 5;// 防弾チョッキ
	static const int KEVLARVEST = 6;// ケブラーベスト
	static const int MAGPOUCH = 7;// マグポーチ
	static const int FRITZHELM = 8;// フリッツヘルム
	static const int COMMANDO = 9;// コマンドー
	static const int RUNNER = 10;// ランナー
	static const int PITCHER = 11;// ピッチャー
	static const int CRISIS_MNG = 12;// 危機管理
	static const int POUCH = 13;// ポーチ
	static const int SILVER_BULLET = 14;//銀の銃弾
	static const int CAMEL = 15;// キャメル
	static const int SHOWTIME = 16;// ショータイム
	static const int SPRINTER = 17;// スプリンター
	static const int FORCES_RADIO = 18;// 部隊無線
	static const int IRONWALL = 19;// 鉄壁
	static const int FORTITUDESOUL = 20;// 不屈の魂
	static const int BOMMER = 21;// 爆弾魔

	static const int NumberSkill = 22;// 現在組み込まれてるスキル数

	static const int DEFAULT = 0;
	static const int RIFLEMAN = 0;
	static const int GRANADER = 1;
	static const int GUNNER = 2;
	static const int SNIPER = 3;
	static const int MEDIC = 4;

	Actor *Act;// アクター

	/* 仮想関数系統 */
	virtual ~Creature(){};//仮想コンストラクタ

	/* 子クラスで出てくる仮想関数 */
	virtual int Set_UpMotion( int Number) = 0;
	virtual int Set_MyState( int Number) = 0;
	virtual int Get_MyState() const = 0;
	virtual int Set_UnderMotion( int Number) = 0;
	virtual int Batch_PeopleMotion() = 0;
	virtual int GunPutOnHand() = 0;
	virtual int MovePosOnGround( Stage *Stg) = 0;
	virtual Weapon_Head* Get_WeaponH() = 0;
	virtual int StatusReset(){return 0;};// ソルジャークラスの状態を初期に戻します(リスタート等で利用)

	/* ライフやスタミナなどの属性を代入する関数 */
	int Set_StateFromBranch( const int Branch);

	/* スキル系の能力を追加する関数 */
	int Add_Skill( const int PlanSkill);
	
	/* スキル系の能力を削除する関数 */
	int Delete_Skill( const int PlanSkill);

	/* アシスト(取得・代入)関数の宣言 */
	int Get_MaxHP() const;// MaxHP変数の取得関数
	int Get_HP() const;// HP変数の取得関数
	//int Get_BodyModel() const;// BodyModel変数の取得関数 
	int Set_MaxHP( int Number);// MaxHP変数の代入関数
	int Set_HP( int Number);// HP変数の代入関数
	//int Set_BodyModel( int Number);// BodyModel変数の代入関数 
	int Get_Stamina() const;// Staminaの取得関数
	int Set_Stamina( int Number);// Staminaの代入関数
	int Get_MaxStamina() const;// MaxStaminaの取得関数
	int Set_MaxStamina( int Number);// MaxStaminaの代入関数
	int Get_Attack() const;// Attackの取得関数
	int Set_Attack( int Number);// Attackの代入関数
	int Get_SkillSlot() const;// SkillSlotの取得関数
	int Set_SkillSlot( int Number);// SkillSlotの代入関数
	int Get_Branch() const;// Branchの取得関数
	int Set_Branch( int Number);// Branchの代入関数
	int	Delete_Skill();// Skillのポインターの削除関数
	int Set_Skill( int *Pointer );// Skillのポインターが指してる内容を指定します
	int Set_EquipmentSkillSum( int Number );// EquipmentSkillSumの代入関数

};