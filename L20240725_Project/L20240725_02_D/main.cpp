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
		cout << "DamAndHeal " << i << "�� �Է� : ";
		cin >> DamAndHeal[i];
	}
	cout << "�Է� ����" << endl;
	cout << "\n";
		
	int LevelCnt = 0;
	for (int element : DamAndHeal)
	{
		cout << "���� Level" << LevelCnt << "�� ü���� " << Hp << "����Ʈ �Դϴ�." << endl;
		HpArr[LevelCnt] = Hp + element;
		Hp = HpArr[LevelCnt];

		cout << "���� �� Level " << LevelCnt << "ü���� " << HpArr[LevelCnt] << "����Ʈ �Դϴ�." << endl;
		cout << "\n";
		

		if (HpArr[LevelCnt] <= 0)
			break;

		LevelCnt++;
	}
	
	if (HpArr[LevelCnt] <= 0)
		cout << "ĳ���Ͱ� �׾����ϴ�.";
	else
		cout << "ĳ���ʹ� " << HpArr[LevelCnt] << "ü�� ����Ʈ�� �����մϴ�.";

	return 0;
}