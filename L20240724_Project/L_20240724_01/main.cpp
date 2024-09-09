#include <iostream>
using namespace std;

int main()
{
	//int a, b, c;
	int a = 0;
	int b = 0;
	int c = 0;

	cin >> a >> b >> c;
	bool Check = false;
	

	if (a > 0 && b > 0 && c > 0)
	{
		cout << "모든 숫자가 양수입니다." << endl;
	}
	else if (a == 0 || b == 0 || c == 0)
	{
		cout << "적어도 하나의 숫자는 0입니다." << endl;
	}
	else if (a > b && b > c)
	{
		cout << "a가 b보다 크고 b가 c보다 큽니다." << endl;
	}
	else if (a < b || b < c)
	{
		cout << "a가 b보다 작거나 b가 c보다 작습니다." << endl;
	}
	else if (a == b and b == c)
	{
		cout << "모든 숫자가 같습니다." << endl;
	}
	else
		cout << "특정 조건을 충족하지 않습니다." << endl;
	
	switch (a)
	{
		case 0:
			cout << "B = " << b << endl;
		case 1:
			cout << "C = " << c << endl;
		case 2:
			cout << "B = " << b << "C = " << c << endl;
		default:
			cout << "Invalid input a." << endl;
		break;
	}

	return 0;
}

//#include <iostream>
//using namespace std;
//
//int main()
//{
//	//int a, b, c;
//	int a = 0;
//	int b = 0;
//	int c = 0;
//
//	cin >> a >> b >> c;
//	bool Check = false;
//
//	if (!Check)
//	{
//		if (a > 0 && b > 0 && c > 0)
//		{
//			cout << "모든 숫자가 양수입니다." << endl;
//			Check = true;
//		}
//		else if (a == 0 || b == 0 || c == 0)
//		{
//			cout << "적어도 하나의 숫자는 0입니다." << endl;
//			Check = true;
//		}
//
//		if (a > b and b > c)
//		{
//			cout << "a가 b보다 크고 b가 c보다 큽니다." << endl;
//			Check = true;
//		}
//		else if (a < b or b < c)
//		{
//			cout << "a가 b보다 작거나 b가 c보다 작습니다." << endl;
//			Check = true;
//		}
//		else if (a == b and b == c)
//		{
//			cout << "모든 숫자가 같습니다." << endl;
//			Check = true;
//		}
//	}
//	if (!Check)
//		cout << "특정 조건을 충족하지 않습니다." << endl;
//
//
//	return 0;
//}