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
		cout << "���� [ " << i + 1 << "]���� �Ұų� ���� ü�� ����Ʈ�� �Է��ϼ��� : ";
		cin >> hpChangePerLevelArray[i];
	}

	for (int hpChange : hpChangePerLevelArray)
	{
		curLevel++;
		cout << "���� [" << curLevel << "] ����" << endl;
		cout << "���� HP : " << hp << endl;
		cout << "���� [" << curLevel << "] ����" << endl;

		hp = max(0, hp + hpChange);

		if (hp <= 0)
			break;
	}

	if (hp > 0)
		cout << "ĳ���ʹ� " << hp << "ü�� ����Ʈ�� �����մϴ�.";
	else
		cout << "ĳ���Ͱ� �׾����ϴ�.";


	return 0;
}