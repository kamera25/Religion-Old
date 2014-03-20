#pragma once
/*　生物クラスの宣言をするヘッダファイル。
//　生物系クラスのスーパークラスです
*/

class Weapon;
class Stage;

/* 生物クラスの宣言 */
class Creature{

private:

	int MaxHP;// 生物の最大HP
	int HP;// 生物のHP
	int BodyModel;// 生物のモデル

public:

	/* 仮想関数系統 */
	virtual ~Creature(){};//仮想コンストラクタ

	/* 子クラスで出てくる仮想関数 */
	virtual int Set_UpMotion( int Number) = 0;
	virtual int Set_MyState( int Number) = 0;
	virtual int Set_UnderMotion( int Number) = 0;
	virtual int Batch_PeopleMotion() = 0;
	virtual int GunPutOnHand() = 0;
	virtual int MovePosOnGround( Stage *Stg) = 0;
	virtual Weapon* Get_Weapon() = 0;


	/* アシスト(取得・代入)関数の宣言 */
	int Get_MaxHP() const;// MaxHP変数の取得関数
	int Get_HP() const;// HP変数の取得関数
	int Get_BodyModel() const;// BodyModel変数の取得関数 
	int Set_MaxHP( int Number);// MaxHP変数の代入関数
	int Set_HP( int Number);// HP変数の代入関数
	int Set_BodyModel( int Number);// BodyModel変数の代入関数 

};