#include <iostream>
using namespace std;

void Study_Code()
{
	int hp = 100;
	int numLevel = 5;
	int curLevel = 0;

	//for (int i = 0; i < numLevel; i++)
	//{
	//	curLevel = i + 1;
	//	cout << "레벨 [" << curLevel << "] 시작" << endl;
	//	cout << "현재 HP : " << hp << endl;

	//	int hpChange = 0;
	//	cout << "레벨 [" << "] 에서 읽거나 얻은 체력 포인트를 입력하세요.";
	//	cin >> hpChange;

	//	cout << "레벨 [" << curLevel << "] 종료" << endl;
	//	
	//	int tmp = hp + hpChange;
	//	hp = max(0, tmp);

	//	if (hp <= 0)
	//		break;
	//}

	while (hp > 0)
	{
		curLevel++;
		cout << "레벨 [" << curLevel << "] 시작" << endl;
		cout << "현재 HP : " << hp << endl;

		int hpChange = 0;
		cout << "레벨 [" << "] 에서 읽거나 얻은 체력 포인트를 입력하세요.";
		cin >> hpChange;

		cout << "레벨 [" << curLevel << "] 종료" << endl;

		int tmp = hp + hpChange;
		hp = max(0, tmp);
	}

	if (hp <= 0)
		cout << "캐릭터가 죽었습니다." << endl;
	else
		cout << "캐릭터는 " << hp << "체력 포인트로 셍존합니다.";
}