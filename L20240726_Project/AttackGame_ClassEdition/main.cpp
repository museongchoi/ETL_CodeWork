#include <iostream>
using namespace std;

namespace unreal
{

}

class Actor {
	// 접근 제어자
	// 외부에서 접근 가능
public:
	int Hp;
	int Ap;
	int Dp;

	Actor() // 생성자
	{
		initialize(0, 0, 0);
	}

	void initialize(int newhp, int newap, int newdp)
	{
		Hp = newhp;
		Ap = newap;
		Dp = newdp;
	}

	void DisplayStats()
	{
		cout << "정보 [hp : " << Hp << ", ap : " << Ap << ", dp : " << Dp << "] 입니다." << endl;
	}

	// 접근 하지 않는 방법
	// virtual : 덮어 씌운다.
	virtual int GetDeal(Actor other)
	{
		cout << "공격!" << endl;
		//other.Hp = max(0, other.Hp + DeductDpFromAp(other.Dp, Ap));
		//return DeductDpFromAp(other.Dp, Ap);
		//return DeductDpFromAp(other->Dp, Ap); // == return DeductDpFromAp((*other).Dp, Ap);
		return max(0, DeductDpFromAp(other.Dp, Ap));

	}

	//int Attack(int hp, int dp, int ap)
	//{
	//	cout << "공격!" << endl;
	//	character_hp = max(0, character_hp + DeductDpFromAp(character_dp, monster_ap));
	//	cout << "캐릭터 남은 HP : " << character_hp << endl;
	//	return 0;
	//}


	// 해당 클래스 메소드와 상속을 받을 파생 클래스에서만 접근이 가능하다.
	// 접근 불가능 + 내부에서만 접근.
protected:
	int DeductDpFromAp(int dp, int ap)
	{
		return max(0, ap - dp);
	}

private:
	// Attack 안에서 사용하는 함수 이므로 class 내에 private에 선언하여, 해당 함수는 다른 곳에서 사용하지 않는다는 것을 알 수 있다.
	// 상속받은 클래스가 접근하기 위한 함수이므로 자리를 protected로 옮겼다.
	//int DeductDpFromAp(int dp, int ap)
	//{
	//	return min(0, dp - ap);
	//}
};

// 상속
class Character : public Actor
{
public:

	Character() // 생성자
	{
		attackCount = 0;
		skillAp = 30;
	}

	int GetDeal(Actor other) override
	{
		// virtual Function 사용
		//Actor::GetDeal(other);

		cout << "공격!" << endl;
		//other.Hp = max(0, other.Hp + DeductDpFromAp(other.Dp, Ap));
		attackCount++;
		if (attackCount % 3 == 0) // attackCount 3번째 마다 skillAp 사용
		{
			return DeductDpFromAp(other.Dp, skillAp);
		}
		else
		{
			return DeductDpFromAp(other.Dp, Ap);
		}
	}

private:
	int attackCount;
	int skillAp;
};

int main()
{

	//Actor character; // Actor 클래스형 character
	Character character; // Character 클래스형 character : 만약 Character 클래스가 비어있다고 해도 동작한다. 이유는
	Actor monster;

	character.initialize(100, 15, 5);
	monster.initialize(150, 10, 20);

	while (character.Hp > 0 && monster.Hp > 0)
	{
		cout << "캐릭터";
		character.DisplayStats();
		cout << "몬스터";
		monster.DisplayStats();
		cout << endl;

		// 값을 복제해서 넘기는 pass by value : 원본 데이터 수정 x
		// 주소 값을 전달하여 실제 값에 대한 Alias(별명)를 구성하는 방식 pass by regerence : 원본 데이터 수정 o

		cout << "캐릭터";
		//int newHP = character.GetDeal(monster);
		//character.GetDeal(monster);
		monster.Hp = max(0, monster.Hp - character.GetDeal(monster)); // GetDeal에 monster.Dp 필요한 값만 넘겨주는 방법도 존재.
		if (monster.Hp <= 0)
			break;
		cout << "몬스터의 남은 Hp : " << monster.Hp << endl;

		cout << "몬스터";
		character.Hp = max(0, character.Hp - monster.GetDeal(character));
		if (character.Hp <= 0)
			break;
		cout << "캐릭터의 남은 Hp : " << character.Hp << endl;
		cout << endl;
	}

	cout << "전투 종료. 승자 : ";
	if (character.Hp <= 0)
		cout << "몬스터" << endl;
	else
		cout << "플레이어" << endl;

	return 0;
}