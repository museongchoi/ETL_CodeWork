#include <iostream>
using namespace std;


int main()
{
	int HP = 100;
	int Num = 0;
	int ch = 0;

	for (int Level = 1; Level <= 5; Level++)
	{
		cout << "���� Level " << Level << endl;
		cout << "������ da �� �� Heal ���� (1, 2) : ";
		cin >> ch;
		
		switch (ch)
		{
			case 1:
				cout << "������ :";
				cin >> Num;
				HP -= Num;
				break;
			case 2:
				cout << "�� :";
				cin >> Num;
				HP += Num;
				break;
			default:
				break;
		}

		cout << "���� HP�� " << HP << "�Դϴ�." << endl;
		if (HP <= 10)
		{
			cout << "���� HP�� ������ �����Դϴ�. Heal�� ���ּ���." << endl;
			if (HP <= 0)
				break;
		}

		cout << "\n" << "--------" << endl;
	}

	if (HP <= 0)
		cout << "ĳ���� �׾����ϴ�." << endl;
	else
		cout << "ĳ���ʹ� " << HP << "ü�� ����Ʈ�� �����մϴ�." << endl;

	return 0;
}



//#include <iostream>
//using namespace std;
//
//int main()
//{
//	int HP = 100;
//
//
//	for (int Level = 0; Level < 5; Level++)
//	{
//		int da = 0;
//		int Heal = 0;
//		cout << "���� Level " << Level << endl;
//		cout << "������ da �� �� Heal �� �Է��ϼ��� (�� 0~30) : ";
//
//		cin >> da >> Heal;
//
//		if (da != 0 && da <= 30)
//			HP -= da;
//
//		if (Heal != 0)
//			HP += Heal;
//
//		cout << "���� HP�� " << HP << "�Դϴ�." << endl;
//		if (HP <= 10)
//		{
//			cout << "���� HP�� ������ �����Դϴ�. Heal�� ���ּ���." << endl;
//			if (HP <= 0)
//				break;
//		}
//
//		cout << "\n" << "--------" << endl;
//	}
//
//	if (HP <= 0)
//		cout << "ĳ���� �׾����ϴ�." << endl;
//	else
//		cout << "ĳ���ʹ� " << HP << "ü�� ����Ʈ�� �����մϴ�." << endl;
//
//	return 0;
//}