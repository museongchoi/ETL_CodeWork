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
	//	cout << "���� [" << curLevel << "] ����" << endl;
	//	cout << "���� HP : " << hp << endl;

	//	int hpChange = 0;
	//	cout << "���� [" << "] ���� �аų� ���� ü�� ����Ʈ�� �Է��ϼ���.";
	//	cin >> hpChange;

	//	cout << "���� [" << curLevel << "] ����" << endl;
	//	
	//	int tmp = hp + hpChange;
	//	hp = max(0, tmp);

	//	if (hp <= 0)
	//		break;
	//}

	while (hp > 0)
	{
		curLevel++;
		cout << "���� [" << curLevel << "] ����" << endl;
		cout << "���� HP : " << hp << endl;

		int hpChange = 0;
		cout << "���� [" << "] ���� �аų� ���� ü�� ����Ʈ�� �Է��ϼ���.";
		cin >> hpChange;

		cout << "���� [" << curLevel << "] ����" << endl;

		int tmp = hp + hpChange;
		hp = max(0, tmp);
	}

	if (hp <= 0)
		cout << "ĳ���Ͱ� �׾����ϴ�." << endl;
	else
		cout << "ĳ���ʹ� " << hp << "ü�� ����Ʈ�� �����մϴ�.";
}