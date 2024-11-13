#include <iostream>
using namespace std;

namespace unreal
{

};

class Actor {
	// 접근 제어자
	// 외부에서 접근 가능
public:
	int hp;
	int ap;
	int dp;

	void DisplayStats()
	{

	}

	void Attack()
	{

	}


	// 해당 클래스 메소드와 상속을 받을 파생 클래스에서만 접근이 가능하다
protected:
	// 접근 불가능 + 내부에서만 접근
private:
};

int character_hp;
int character_ap;
int character_dp;

int monster_hp;
int monster_ap;
int monster_dp;

// Attack 안에서 사용하는 함수 이므로 class 내에 private에 선언하여, 해당 함수는 다른 곳에서 사용하지 않는다는 것을 알 수 있다.
int DeductDpFromAp(int dp, int ap)
{
	return min(0, dp - ap);
}

void initializeCharacter()
{
	character_hp = 100;
	character_ap = 10;
	character_dp = 5;
}

void initializeMonster()
{
	monster_hp = 120;
	monster_ap = 5;
	monster_dp = 1;
}

void displayCharacterStats()
{
	cout << "플레이어 정보 [hp : " << character_hp << ", ap : " << character_ap << "dp : " << character_dp << "] 입니다." << endl;
}

void displayMonsterStats()
{
	cout << "몬스터 정보 [hp : " << monster_hp << ", ap : " << monster_ap << "dp : " << monster_dp << "] 입니다." << endl;
}

void characterAttack()
{
	cout << "캐릭터 공격!" << endl;
	//monster_hp = max(0, monster_hp + min(0, monster_dp - character_ap));
	monster_hp = max(0, monster_hp + DeductDpFromAp(monster_dp, character_ap));
	cout << "몬스터 남은 HP : " << monster_hp << endl;
}



void monsterAttack()
{
	cout << "몬스터 공격!" << endl;
	// character_hp = max(0, character_hp + min(0, character_dp - monster_ap));
	character_hp = max(0, character_hp + DeductDpFromAp(character_dp, monster_ap));
	cout << "캐릭터 남은 HP : " << character_hp << endl;
}


int main()
{
	Actor monster;
	Actor character;

	monster.hp;
	monster.ap;
	monster.dp;
	monster.Attack();


	initializeCharacter();
	initializeMonster();

	while (character_hp > 0 && monster_hp > 0)
	{
		displayCharacterStats();
		displayMonsterStats();

		characterAttack();
		if (monster_hp <= 0)
			break;

		monsterAttack();
		if (character_hp <= 0)
			break;
	}


	cout << "전투 종료. 승자 : ";
	if (character_hp <= 0)
		cout << "몬스터" << endl;
	else
		cout << "플레이어" << endl;

	return 0;
}