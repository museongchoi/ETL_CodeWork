#include <iostream>
using namespace std;

int main()
{
	int ch;
	int a, b, c;
	cout << "1. �հ�, 2. ��, 3. ��� �� ���� �۾��� ���� �Ͻÿ�. : ";
	cin >> ch;
	cout << "a, b, c �� �Է��Ͻÿ�. : ";
	cin >> a >> b >> c;


	switch (ch)
	{
		case 1:
			cout << "�հ� : " << a + b + c << endl;
			break;
		case 2:
			cout << "�� : " << a * b * c << endl;
			break;
		case 3:
			//cout << "��� : " << float (a + b + c) / 3 << endl; // c ��Ÿ�� (float)
			cout << "��� : " << (a + b + c) / 3.f << endl;
			break;
		default:
			cout << "�߸��� ������ ���� �Ǿ����ϴ�.";
			break;
		break;
	}


	return 0;
}