#include <iostream>
using namespace std;

int main()
{
	int Hp = 100;
	int MaxLevel = 5;

	int DamAndHeal[5];
	int HpArr[5];

	for (int i = 0; i < MaxLevel; i++)
	{
		cout << "DamAndHeal " << i << "번 입력 : ";
		cin >> DamAndHeal[i];
	}
	cout << "입력 종료" << endl;
	cout << "\n";
		
	int LevelCnt = 0;
	for (int element : DamAndHeal)
	{
		cout << "현재 Level" << LevelCnt << "에 체력은 " << Hp << "포인트 입니다." << endl;
		HpArr[LevelCnt] = Hp + element;
		Hp = HpArr[LevelCnt];

		cout << "진행 후 Level " << LevelCnt << "체력은 " << HpArr[LevelCnt] << "포인트 입니다." << endl;
		cout << "\n";
		

		if (HpArr[LevelCnt] <= 0)
			break;

		LevelCnt++;
	}
	
	if (HpArr[LevelCnt] <= 0)
		cout << "캐릭터가 죽었습니다.";
	else
		cout << "캐릭터는 " << HpArr[LevelCnt] << "체력 포인트로 생존합니다.";

	return 0;
}