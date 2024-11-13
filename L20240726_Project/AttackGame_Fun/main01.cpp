#include <iostream>
using namespace std;

int CharacterHp; // 체력
int CharacterDam; // 공격력
int CharacterDefence; // 방어력

int MonsterHp;
int MonsterDam;
int MonsterDefence;

void initializeCharacter();
void cininitializeCharacter();

void initializeMonster();
void cininitializeMonster();

void displayCharacterStats();
void displayMonsterStats();
void characterAttack(); // 캐릭터가 몬스터를 공격하여 몬스터의 체력을 감소
void monsterAttack();	// 몬스터가 캐릭터를 공격하여 캐릭터의 체력을 감소

int main()
{
	initializeCharacter();
	initializeMonster();
	displayCharacterStats();
	displayMonsterStats();
	cout << "\n";


	while (true)
	{
		cout << "캐릭터가 몬스터를 공격합니다." << "\n";
		characterAttack();
		displayMonsterStats();
		cout << "몬스터가 캐릭터를 공격합니다." << "\n";
		monsterAttack();
		displayCharacterStats();

		if (CharacterHp <= 0 || MonsterHp <= 0)
			break;
	}

	if (CharacterHp <= 0)
		cout << "Monster 승리";
	else if (MonsterHp <= 0)
		cout << "Character 승리";

	return 0;
}

// 캐릭터 초기화
void initializeCharacter()
{
	CharacterHp = 100;
	CharacterDam = 20;
	CharacterDefence = 10;
}
void cininitializeCharacter()
{
	cout << "캐릭터 Hp | Dam | Defence : ";
	cin >> CharacterHp >> CharacterDam >> CharacterDefence;
}

// 몬스터 초기화
void initializeMonster()
{
	MonsterHp = 100;
	MonsterDam = 30;
	MonsterDefence = 5;
}

void cininitializeMonster()
{
	cout << "몬스터 Hp | Dam | Defence : ";
	cin >> CharacterHp >> CharacterDam >> CharacterDefence;
}

void displayCharacterStats()
{
	cout << "캐릭터의 현재 체력 | 공격력 | 방어력 : " << CharacterHp << " | " << CharacterDam << " | " << CharacterDefence << endl;
}

void displayMonsterStats()
{
	cout << "몬스터의 현재 체력 | 공격력 | 방어력 : " << MonsterHp << " | " << MonsterDam << " | " << MonsterDefence << endl;

}

void characterAttack()
{
	int chDam = max(0, CharacterDam - MonsterDefence);
	MonsterHp -= chDam;
}

void monsterAttack()
{
	int monDam = (0, MonsterDam - CharacterDefence);
	CharacterHp -= monDam;
}
