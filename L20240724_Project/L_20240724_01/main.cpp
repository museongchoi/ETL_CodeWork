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
		cout << "��� ���ڰ� ����Դϴ�." << endl;
	}
	else if (a == 0 || b == 0 || c == 0)
	{
		cout << "��� �ϳ��� ���ڴ� 0�Դϴ�." << endl;
	}
	else if (a > b && b > c)
	{
		cout << "a�� b���� ũ�� b�� c���� Ů�ϴ�." << endl;
	}
	else if (a < b || b < c)
	{
		cout << "a�� b���� �۰ų� b�� c���� �۽��ϴ�." << endl;
	}
	else if (a == b and b == c)
	{
		cout << "��� ���ڰ� �����ϴ�." << endl;
	}
	else
		cout << "Ư�� ������ �������� �ʽ��ϴ�." << endl;
	
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
//			cout << "��� ���ڰ� ����Դϴ�." << endl;
//			Check = true;
//		}
//		else if (a == 0 || b == 0 || c == 0)
//		{
//			cout << "��� �ϳ��� ���ڴ� 0�Դϴ�." << endl;
//			Check = true;
//		}
//
//		if (a > b and b > c)
//		{
//			cout << "a�� b���� ũ�� b�� c���� Ů�ϴ�." << endl;
//			Check = true;
//		}
//		else if (a < b or b < c)
//		{
//			cout << "a�� b���� �۰ų� b�� c���� �۽��ϴ�." << endl;
//			Check = true;
//		}
//		else if (a == b and b == c)
//		{
//			cout << "��� ���ڰ� �����ϴ�." << endl;
//			Check = true;
//		}
//	}
//	if (!Check)
//		cout << "Ư�� ������ �������� �ʽ��ϴ�." << endl;
//
//
//	return 0;
//}