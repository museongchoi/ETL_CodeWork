#include <iostream>
using namespace std;


int main()
{
	int HP = 100;
	int Num = 0;
	int ch = 0;

	for (int Level = 1; Level <= 5; Level++)
	{
		cout << "현재 Level " << Level << endl;
		cout << "데미지 da 와 힐 Heal 선택 (1, 2) : ";
		cin >> ch;
		
		switch (ch)
		{
			case 1:
				cout << "데미지 :";
				cin >> Num;
				HP -= Num;
				break;
			case 2:
				cout << "힐 :";
				cin >> Num;
				HP += Num;
				break;
			default:
				break;
		}

		cout << "현재 HP는 " << HP << "입니다." << endl;
		if (HP <= 10)
		{
			cout << "현재 HP가 부족한 상태입니다. Heal을 해주세요." << endl;
			if (HP <= 0)
				break;
		}

		cout << "\n" << "--------" << endl;
	}

	if (HP <= 0)
		cout << "캐릭터 죽었습니다." << endl;
	else
		cout << "캐릭터는 " << HP << "체력 포인트로 생존합니다." << endl;

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
//		cout << "현재 Level " << Level << endl;
//		cout << "데미지 da 와 힐 Heal 을 입력하세요 (각 0~30) : ";
//
//		cin >> da >> Heal;
//
//		if (da != 0 && da <= 30)
//			HP -= da;
//
//		if (Heal != 0)
//			HP += Heal;
//
//		cout << "현재 HP는 " << HP << "입니다." << endl;
//		if (HP <= 10)
//		{
//			cout << "현재 HP가 부족한 상태입니다. Heal을 해주세요." << endl;
//			if (HP <= 0)
//				break;
//		}
//
//		cout << "\n" << "--------" << endl;
//	}
//
//	if (HP <= 0)
//		cout << "캐릭터 죽었습니다." << endl;
//	else
//		cout << "캐릭터는 " << HP << "체력 포인트로 생존합니다." << endl;
//
//	return 0;
//}