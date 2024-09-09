#include <iostream>
using namespace std;

int main()
{
	int hp = 100;
	int curLevel = 0;
	int numLevel = 5;
	int hpChangePerLevelArray[5];

	for (int i = 0; i < numLevel; i++)
	{
		cout << "레벨 [ " << i + 1 << "]에서 잃거나 얻을 체력 포인트를 입력하세요 : ";
		cin >> hpChangePerLevelArray[i];
	}

	for (int hpChange : hpChangePerLevelArray)
	{
		curLevel++;
		cout << "레벨 [" << curLevel << "] 시작" << endl;
		cout << "현재 HP : " << hp << endl;
		cout << "레벨 [" << curLevel << "] 시작" << endl;

		hp = max(0, hp + hpChange);

		if (hp <= 0)
			break;
	}

	if (hp > 0)
		cout << "캐릭터는 " << hp << "체력 포인트로 생존합니다.";
	else
		cout << "캐릭터가 죽었습니다.";


	return 0;
}